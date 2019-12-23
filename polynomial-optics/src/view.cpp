#include "lenssystem.h"
#include "raytrace.h"
#include "raytrace_draw.h"
#include "poly.h"
#include <vector>

#include <gtk/gtk.h>
#include <cairo.h>
#include <cairo-svg.h>
#include <cmath>

//json parsing
#include "../ext/json.hpp"
#include <string>
#include <fstream>
using json = nlohmann::json;

#include "../../fmt/include/fmt/format.h"

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif


static double zoom = 0.0f; // zoom, if the lens supports it.
static int num_rays = 500;
static int dim_up = 0; // xz (top - 0) or plot yz (side - 1) of the lens in 2d?
static poly_system_t poly, poly_aperture;
static double aperture_rad;
static std::vector<lens_element_t> lenses;
static int lenses_cnt = 0;
static double lens_pupil_dist = 0.0f;
static double lens_pupil_rad = 0.0f;
static double lens_length = 0;
static double aperture_pos = 0;

static int screenshot = 0;
static int draw_raytraced = 1;
static int draw_polynomials = 0;
static int draw_aspheric = 1;
static int draw_focallength = 0;
static int mode_visual_debug = 0;
static int trace_forward = 0;

const int width = 900;
const int height = 550;
const int gridsize = 10; //10 mm

static double global_scale = 20.0f;
static double window_aspect_ratio = static_cast<double>(width)/static_cast<double>(height);

const std::vector<float> black = {0.1, 0.1, 0.1, 1.0};
const std::vector<float> darkgrey = {0.15, 0.15, 0.15, 1.0};
const std::vector<float> grey = {0.5, 0.5, 0.5, 1.0};
const std::vector<float> lightgrey = {0.825, 0.825, 0.825, 1.0};
const std::vector<float> yellow = {0.949, 0.882, 0.749, 0.65};
const std::vector<float> green = {0.749, 0.949, 0.874, 1.0};
const std::vector<float> white50 = {1.0, 1.0, 1.0, 0.5};
const std::vector<float> white = {1.0, 1.0, 1.0, 1.0};
const std::vector<float> mint = {0.631, 1.0, 0.78, 0.5};
const std::vector<float> salmon = {232.0/255.0, 121.0/255.0, 121.0/255.0, 1.0};

std::string lens_svg_path = "";


gboolean on_keypress (GtkWidget *widget, GdkEventKey *event, gpointer data) {
  if(event->keyval == GDK_KEY_Escape) {
    gtk_main_quit();
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_s) {
    screenshot = !screenshot;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_a) {
    draw_aspheric = !draw_aspheric;
    fmt::print("Using {}spherical lenses\n", draw_aspheric ? "a" : "");
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_f) {
    draw_focallength = !draw_focallength;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_plus) {
    global_scale /= 0.95;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_minus) {
    global_scale *= 0.95;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_m) {
    num_rays += 10;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_l) {
    num_rays -= 10;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_x) {
    dim_up = !dim_up;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_p) {
    draw_polynomials = !draw_polynomials;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }  
  else if(event->keyval == GDK_KEY_v) {
    mode_visual_debug = !mode_visual_debug;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_equal) {
    trace_forward = !trace_forward;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }

  return FALSE;
}

static inline float hue_2_rgb(float v1, float v2, float vH) {
  if (vH < 0.0f) vH += 1.0f;
  if (vH > 1.0f) vH -= 1.0f;
  if ((6.0f * vH) < 1.0f) return (v1 + (v2 - v1) * 6.0f * vH);
  if ((2.0f * vH) < 1.0f) return (v2);
  if ((3.0f * vH) < 2.0f) return (v1 + (v2 - v1) * ((2.0f / 3.0f) - vH) * 6.0f);
  return (v1);
}

static inline void hsl_2_rgb(const std::vector<float> HSL, std::vector<float> &RGB) {
  float H = HSL[0];
  float S = HSL[1];
  float L = HSL[2];

  float var_1, var_2;

  if (S < 1e-6f) {
    RGB[0] = RGB[1] = RGB[2] = L;
  } else {
    if (L < 0.5f) var_2 = L * (1.0f + S);
    else          var_2 = (L + S) - (S * L);

    var_1 = 2.0f * L - var_2;

    RGB[0] = hue_2_rgb(var_1, var_2, H + (1.0f / 3.0f));
    RGB[1] = hue_2_rgb(var_1, var_2, H);
    RGB[2] = hue_2_rgb(var_1, var_2, H - (1.0f / 3.0f));
  }
}

static void stroke_with_pencil(cairo_t *cr, const double scale, const double line_width) {
  cairo_save(cr);
  cairo_scale(cr, 1./scale, 1./scale);
  cairo_set_line_width(cr, line_width);
  cairo_stroke(cr);
  cairo_restore(cr);
}

void draw_optical_axis(cairo_t *cr) {
  cairo_set_line_width(cr, 4.0f);
  cairo_set_source_rgba(cr, lightgrey[0], lightgrey[1], lightgrey[2], 0.5);
  cairo_move_to(cr, 0, height/2.0);
  cairo_line_to(cr, width, height/2.0);
  cairo_stroke(cr);
}

void draw_sensor(cairo_t *cr) {
  double sensor_size = 0.0;
  if (dim_up) sensor_size = 24.0;
  else        sensor_size = 35.0;

  cairo_move_to(cr, -1.0, -sensor_size/2.0);
  cairo_line_to(cr, -1.0,  sensor_size/2.0);
  cairo_line_to(cr,  0.0,  sensor_size/2.0);
  cairo_line_to(cr,  0.0, -sensor_size/2.0);
  cairo_close_path(cr);
  cairo_set_source_rgb(cr, grey[0], grey[1], grey[2]);
  cairo_fill(cr);
}

void draw_grid(cairo_t *cr) {
  cairo_set_line_width(cr, 200.0/width);
  cairo_set_source_rgb(cr, black[0], black[1], black[2]);
  for (int i = -width; i<width; i += gridsize){
    cairo_move_to(cr, i, -height);
    cairo_line_to(cr, i, height);
    cairo_stroke(cr);
  }

  for (int i = -height/2; i<height; i += gridsize){
    cairo_move_to(cr, -width, i);
    cairo_line_to(cr, width, i);
    cairo_stroke(cr);
  }
}

void draw_rulers(cairo_t *cr, const double max_housing_radius, const double ruler_padding) {
  double ruler_height = 2.5;
  cairo_set_source_rgb(cr, grey[0], grey[1], grey[2]);
  cairo_set_line_width(cr, 200.0/width);

  // x axis
  cairo_move_to(cr, -ruler_padding, max_housing_radius + ruler_padding);
  cairo_line_to(cr, lens_length, max_housing_radius + ruler_padding);
  cairo_stroke(cr);
  for (int i = 0; i<lens_length + ruler_padding; i += gridsize){
    cairo_move_to(cr, i, max_housing_radius + ruler_padding);
    cairo_line_to(cr, i, max_housing_radius + ruler_padding - ruler_height);
    cairo_stroke(cr);

    cairo_move_to(cr, i, max_housing_radius + ruler_padding*1.5);
    std::string number = std::to_string(i);
    char const *pchar = number.c_str();
    cairo_set_font_size(cr, 2.5);
    cairo_show_text(cr, pchar);
    cairo_new_path(cr);
  }

  // y axis down
  cairo_move_to(cr, 0.0 - ruler_padding, max_housing_radius + ruler_padding);
  cairo_line_to(cr, 0.0 - ruler_padding, -max_housing_radius);
  cairo_stroke(cr);
  for (int i = 0; i < max_housing_radius + ruler_padding; i += gridsize){
    cairo_move_to(cr, -ruler_padding, i);
    cairo_line_to(cr, -ruler_padding + ruler_height, i);
    cairo_stroke(cr);

    cairo_move_to(cr, -ruler_padding*1.5, i);
    std::string number = std::to_string(-i);
    char const *pchar = number.c_str();
    cairo_set_font_size(cr, 2.5);
    cairo_show_text(cr, pchar);
    cairo_new_path(cr);
  }
  for (int i = gridsize; i < max_housing_radius + ruler_padding; i += gridsize){
    cairo_move_to(cr, -ruler_padding, -i);
    cairo_line_to(cr, -ruler_padding + ruler_height, -i);
    cairo_stroke(cr);

    cairo_move_to(cr, -ruler_padding*1.5, -i);
    std::string number = std::to_string(i);
    char const *pchar = number.c_str();
    cairo_set_font_size(cr, 2.5);
    cairo_show_text(cr, pchar);
    cairo_new_path(cr);
  }
}

void draw_axis_text(cairo_t *cr, const double max_housing_radius, const double ruler_padding) {
  cairo_move_to(cr, 0.0 - ruler_padding, max_housing_radius + ruler_padding*2);
  std::string dim_up_text;
  if (dim_up) dim_up_text = "dim_up = 1 [side]";
  else        dim_up_text = "dim_up = 0 [top]";
  char const *pchar = dim_up_text.c_str();
  cairo_set_font_size(cr, 2.5);
  cairo_show_text(cr, pchar);
  cairo_new_path(cr);
}

void draw_aperture(cairo_t *cr) {
  int aperture_element = lens_get_aperture_element(lenses, lenses_cnt-1);
  double aperture_pos = lens_get_aperture_pos_reverse(lenses, lenses_cnt-1, 0.0);
  double housing_radius = lenses[aperture_element].housing_radius;

  cairo_set_source_rgba(cr, lightgrey[0], lightgrey[1], lightgrey[2], lightgrey[3]);
  cairo_set_line_width(cr, 500.0/width);

  cairo_move_to(cr, aperture_pos, housing_radius+10);
  cairo_line_to(cr, aperture_pos, housing_radius);
  cairo_stroke(cr);
  cairo_move_to(cr, aperture_pos, -housing_radius-10);
  cairo_line_to(cr, aperture_pos, -housing_radius);
  cairo_stroke(cr);
}

void draw_focal_length(cairo_t *cr, const double scale) {

  Eigen::Vector3d cam_pos(0,0,0);
  Eigen::Vector3d cam_dir(0,0,0);
  cam_pos[dim_up] = lenses[lenses_cnt-1].housing_radius * 0.5;
  cam_dir[2] = cam_pos[2] + 99999;
  cam_dir[dim_up] = cam_pos[dim_up];

  const double lambda = 0.55;
  Eigen::VectorXd in(5); in << 0,0,0,0,lambda;
  Eigen::VectorXd out(5); out << 0,0,0,0,lambda;
  Eigen::VectorXd ap(5); ap <<  0,0,0,0,lambda;
  Eigen::VectorXd inrt(5); inrt << cam_pos[0], cam_pos[1], cam_pos[2], 0.0, lambda;
  Eigen::VectorXd outrt(5); outrt << cam_dir[0], cam_dir[1], cam_dir[2], 0.0, lambda;

  int error = 0;
  Eigen::Vector3d pos(0,0,0);
  Eigen::Vector3d dir(0,0,0);
  error = evaluate_draw(lenses, lenses_cnt, zoom, inrt, outrt, cr, scale, dim_up, draw_aspheric, pos, dir);

  Eigen::Vector3d ray_origin(pos[0], pos[1], pos[2]);
  Eigen::Vector3d pp_line1start(0,0,0);
  Eigen::Vector3d pp_line1end(0.0, 0.0, 99999.0);
  Eigen::Vector3d pp_line2end(0.0, 0.0, pos[2] + (dir[2] * 1000.0));
  pp_line1start[dim_up] = inrt[dim_up];
  pp_line1end[dim_up] = inrt[dim_up];
  pp_line2end[dim_up] = pos[dim_up] + (dir[dim_up] * 1000.0);
  double principlePlaneDistance = lineLineIntersection_x(pp_line1start, pp_line1end, ray_origin, pp_line2end, dim_up);

  Eigen::Vector3d focalPointLineStart(0,0,0);
  Eigen::Vector3d focalPointLineEnd(0.0, 0.0, 99999.0);
  double focalPointDistance = lineLineIntersection_x(focalPointLineStart, focalPointLineEnd, ray_origin, pp_line2end, dim_up);
  
  double tracedFocalLength = focalPointDistance - principlePlaneDistance;
  fmt::print("Traced Focal Length = {}\n", tracedFocalLength);
  
  cairo_new_path(cr);
  cairo_set_source_rgba(cr, 0.2, 1.0, 0.2, 1.0);
  cairo_arc(cr, principlePlaneDistance, 0.0, 1, 0, 2 * M_PI);
  cairo_fill(cr);
  
  cairo_new_path(cr);
  cairo_set_source_rgba(cr, 0.2, 1.0, 1.0, 1.0);
  cairo_arc(cr, focalPointDistance, 0.0, 1, 0, 2 * M_PI);
  cairo_fill(cr);

  double max_housing_radius = 70.0;
  cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 1.0);
  cairo_set_line_width(cr, 0.75);
  cairo_move_to(cr, principlePlaneDistance, max_housing_radius);
  cairo_line_to(cr, principlePlaneDistance + tracedFocalLength, max_housing_radius);
  cairo_stroke(cr);

  cairo_move_to(cr, principlePlaneDistance + tracedFocalLength/2.0, max_housing_radius+5);
  std::string number = fmt::format("f = {}", tracedFocalLength);
  char const *pchar = number.c_str();
  cairo_set_font_size(cr, 2.5);
  cairo_show_text(cr, pchar);
  cairo_new_path(cr);
  cairo_stroke(cr);
}


void draw_lenses(cairo_t *cr, double scale){
  double pos = lens_length;
  double line_width = 70.0/static_cast<double>(width);

  for(int i=0; i<lenses_cnt; i++){
    double rad = lenses[i].lens_radius;
    if (stringcmp(lenses[i].geometry, "cyl-y") && dim_up) rad = 99999.0;
    else if (stringcmp(lenses[i].geometry, "cyl-x") && !dim_up) rad = 99999.0;
    
    double hrad = lenses[i].housing_radius;
    double t = lens_get_thickness(lenses[i], zoom);

    // skip aperture drawing
    if(stringcmp(lenses[i].material, "iris")) {
      pos -= t;
      continue;
    }

    if(stringcmp(lenses[i].material, "iris")) aperture_pos = pos;

    if(lenses[i].ior != 1.0 && i < lenses_cnt-1) {
      cairo_save(cr);

      double rad2 = lenses[i+1].lens_radius;
      if (stringcmp(lenses[i+1].geometry, "cyl-y") && dim_up) rad2 = 99999.0;
      else if (stringcmp(lenses[i+1].geometry, "cyl-x") && !dim_up) rad2 = 99999.0;
    
      double hrad2 = lenses[i+1].housing_radius;
      double off  = rad  > 0.0 ? 0.0 : M_PI;
      double off2 = rad2 > 0.0 ? 0.0 : M_PI;
      double alpha  = asin(fminf(1.0, fmax(-1.0, fabs(hrad/rad))));
      double alpha2 = asin(fminf(1.0, fmax(-1.0, fabs(hrad2/rad2))));

      if(draw_aspheric) {
        const int num_steps = 100;

        for(int j = 0; j <= num_steps; j++)
        {
          Eigen::Vector2d y(hrad*(2 * j / (double)num_steps - 1), 0); //float y[] = {hrad*(2 * j / (float)num_steps - 1), 0};
          Eigen::Vector4d coeff(0,0,0,0);
          for (int i = 0; i < 4; i++) coeff(i) = lenses[i].aspheric_correction_coefficients[i];
          double x = pos-evaluate_aspherical(y, rad, lenses[i].aspheric, coeff);
          cairo_line_to(cr, x, y[0]);
        }

        for(int j = num_steps; j >= 0; j--)
        {
          Eigen::Vector2d y(hrad2*(2 * j / (double)num_steps - 1), 0); //float y[] = {hrad2*(2 * j / (float)num_steps - 1), 0};
          Eigen::Vector4d coeff(0,0,0,0);
          for (int i = 0; i < 4; i++) coeff(i) = lenses[i+1].aspheric_correction_coefficients[i];
          double x = pos-t-evaluate_aspherical(y, rad2, lenses[i+1].aspheric, coeff);
          cairo_line_to(cr, x, y[0]);
        }
      } else {
        cairo_arc(cr, pos-rad, 0.0, std::abs(rad), off-alpha, off+alpha);
        if(rad * rad2 > 0.0)
          cairo_arc_negative(cr, pos-t-rad2, 0.0, std::abs(rad2), off2+alpha2, off2-alpha2);
        else
          cairo_arc(cr, pos-t-rad2, 0.0, std::abs(rad2), off2-alpha2, off2+alpha2);
      }

      cairo_close_path(cr);
      
      if (stringcmp(lenses[i+1].geometry, "cyl-y") || stringcmp(lenses[i+1].geometry, "cyl-x")) cairo_set_source_rgba(cr, mint[0], mint[1], mint[2], 0.85);
      else if (stringcmp(lenses[i+1].geometry, "aspherical")) cairo_set_source_rgba(cr, green[0], green[1], green[2], 0.85);
      else cairo_set_source_rgba(cr, grey[0], grey[1], grey[2], 0.85);
      cairo_fill_preserve(cr);

      cairo_set_source_rgba(cr, lightgrey[0], lightgrey[1], lightgrey[2], lightgrey[3]);
      stroke_with_pencil(cr, scale, line_width);

      cairo_restore(cr);

    } else {
      // backside (air-facing), actually drawn double most of the time
      cairo_save(cr);
      cairo_rectangle(cr, pos-rad-2, -hrad, 2*rad+4, 2*hrad);
      cairo_clip(cr);
      
      if(draw_aspheric) {
        const int num_steps = 100;

        for(int j = 0; j <= num_steps; j++) {
          Eigen::Vector2d y(hrad*(2 * j / (double)num_steps - 1), 0); //float y[] = {hrad*(2 * j / (float)num_steps - 1), 0};
          Eigen::Vector4d coeff(0,0,0,0);
          for (int i = 0; i < 4; i++) coeff(i) = lenses[i].aspheric_correction_coefficients[i];
          double x = pos-evaluate_aspherical(y, rad, lenses[i].aspheric, coeff);
          cairo_line_to(cr, x, y[0]);
        }
      } else {
        cairo_arc(cr, pos-rad, 0.0, std::abs(rad), 0.0, 2.0*M_PI);
      }

      if (stringcmp(lenses[i].geometry, "cyl-y") || stringcmp(lenses[i].geometry, "cyl-x")) cairo_set_source_rgba(cr, mint[0], mint[1], mint[2], 0.85);
      else if (stringcmp(lenses[i].geometry, "aspherical")) cairo_set_source_rgba(cr, green[0], green[1], green[2], 0.85);
      else cairo_set_source_rgba(cr, grey[0], grey[1], grey[2], 0.85);

      cairo_set_source_rgba(cr, lightgrey[0], lightgrey[1], lightgrey[2], lightgrey[3]);
      stroke_with_pencil(cr, scale, line_width);
      cairo_close_path(cr);
      cairo_fill(cr);

      cairo_restore(cr);
    }

    pos -= t;
  }
}


gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
  cairo_surface_t *svg_surface = 0;
  if(screenshot) { 
    svg_surface = cairo_svg_surface_create(lens_svg_path.c_str(), width, height);
    cairo_svg_surface_restrict_to_version (svg_surface, CAIRO_SVG_VERSION_1_2);
    cr = cairo_create(svg_surface);
  } 

  cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
  cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
  cairo_set_source_rgb(cr, darkgrey[0], darkgrey[1], darkgrey[2]);
  cairo_paint(cr);
  cairo_set_line_width(cr, 1.0f);

  draw_optical_axis(cr);

  cairo_translate(cr, 0, height/2.0);
  if (!mode_visual_debug){
    cairo_translate(cr, width/2.0, 0);
  }

  cairo_scale(cr, ((double)width/window_aspect_ratio)/20.0, (double)height/20.0);
  cairo_set_line_width(cr, 40.0/width);

  const double scale = global_scale/lens_length;
  cairo_scale(cr, scale, scale); // scale by arbitrary factor

  if (!mode_visual_debug){
    double center_shift = -((lens_length + lenses[lenses_cnt-1].thickness_short) / 2.0);
    cairo_translate(cr, center_shift, 0);
  } else {
    cairo_translate(cr, 20.0, 0.0); // move 20mm away
    draw_grid(cr);

    // find max housing radius
    double max_housing_radius = 0.0;
    for (int i=0; i < lenses_cnt; i++){
      if (lenses[i].housing_radius > max_housing_radius){
        max_housing_radius = lenses[i].housing_radius;
      }
    }

    double ruler_padding = gridsize;
    draw_rulers(cr, max_housing_radius, ruler_padding);
    draw_axis_text(cr, max_housing_radius, ruler_padding);
  }


  cairo_set_line_width(cr, 90.0/width);
  cairo_set_source_rgba(cr, lightgrey[0], lightgrey[1], lightgrey[2], 0.5);


  if (trace_forward) {
    
    fmt::print("Drawing in forward direction. \n");

    for(int k=0; k<num_rays; k++){

      const double y = 2.0f * (num_rays/2-k)/(double)num_rays * lenses[0].housing_radius;

      Eigen::Vector3d cam_pos(0,0,0);
      Eigen::Vector3d cam_dir(0,0,0);
      cam_dir[dim_up] = y;
      cam_dir[2] = cam_pos[2] + 99999;
      
      const double lambda = 0.55;
      Eigen::VectorXd in(5); in << 0,0,0,0,lambda;
      Eigen::VectorXd out(5); out <<  0,0,0,0,lambda;
      Eigen::VectorXd ap(5); ap << 0,0,0,0,lambda;
      Eigen::VectorXd inrt(5); inrt << cam_pos[0], cam_pos[1], cam_pos[2], 0.0, lambda;
      Eigen::VectorXd outrt(5); outrt << cam_dir[0], cam_dir[1], cam_dir[2], 0.0, lambda;

      int error = 0;
      if(draw_raytraced) {
        Eigen::Vector3d pos_out(0,0,0);
        Eigen::Vector3d dir_out(0,0,0);
        error = evaluate_draw(lenses, lenses_cnt, zoom, inrt, outrt, cr, scale, dim_up, draw_aspheric, pos_out, dir_out);
      }
    }
  } else {

    fmt::print("Drawing in backward direction. \n");

    for(int k=0; k<num_rays; k++){

      Eigen::Vector3d cam_pos(0.0, 0.0, 9999.0);
      const double y = 2.0 * (num_rays/2-k)/(double)num_rays * lenses[0].housing_radius;
      cam_pos[dim_up] = y;

      Eigen::Vector3d cam_dir(0.0, 0.0, -cam_pos[2]*10.0f);
      cam_dir[dim_up] = cam_pos[dim_up];
      raytrace_normalise(cam_dir);

      const float lambda = 0.55;

      //Eigen::VectorXd in(5); in << 0,0,0,0,lambda;
      //Eigen::VectorXd out(5); out << 0,0,0,0,lambda;
      float in[5] = {0.0, 0.0, 0.0, 0.0, lambda};
      float out[5] = {0.0, 0.0, 0.0, 0.0, lambda};
      float ap[5] = {0.0, 0.0, 0.0, 0.0, lambda};
      //Eigen::VectorXd ap(5); ap << 0,0,0,0,lambda;
      Eigen::VectorXd inrt(5); inrt << 0,0,0,0,lambda;
      Eigen::VectorXd outrt(5); outrt << 0,0,0,0,lambda;

      double t = 0.0;
      Eigen::Vector3d n(0,0,0);

      Eigen::Vector2d outpos(0,0);
      Eigen::Vector2d outdir(0,0);

      // intersection with first lens element
      if (stringcmp(lenses[0].geometry, "cyl-y")){
        cylindrical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, true);
        for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
        csToCylinder(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
        // cylinderToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
      }
      else if (stringcmp(lenses[0].geometry, "cyl-x")){
        cylindrical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, false);
        for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
        csToCylinder(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
        // cylinderToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
      }
      else {
        spherical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n);
        for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
        csToSphere(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
        // sphereToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
      }

      in[0] = outpos[0];
      in[1] = outpos[1];
      in[2] = outdir[0];
      in[3] = outdir[1];

      for(int i=0;i<5;i++) inrt[i] = in[i];

      int error = 0;
      if(draw_raytraced) {
        error = evaluate_reverse_draw(lenses, lenses_cnt, zoom, inrt, outrt, cr, scale, dim_up, draw_aspheric);
      } else {
        error = evaluate_reverse(lenses, lenses_cnt, zoom, inrt, outrt, draw_aspheric);
      }
    

      if(!error && draw_polynomials)
      {
        // ray color
        const std::vector<float> hsl = {k/(num_rays+1.f), .7f, .5f};
        std::vector<float> rgb(3);
        hsl_2_rgb(hsl, rgb);

        const double polynomial_length = lens_length/5.0;

        // evaluate sensor -> light
        for(int i=0;i<5;i++) in[i] = outrt[i];
        in[2] = -in[2];
        in[3] = -in[3];
        in[4] = lambda;
        poly_system_evaluate(&poly, in, out, 15);
        poly_system_evaluate(&poly_aperture, in, ap, 15);

        const int aperture_death = (ap[0]*ap[0] + ap[1]*ap[1] > aperture_rad*aperture_rad);
        
        if(!aperture_death) {
          double transmittance = out[4];
          cairo_set_source_rgba(cr, rgb[0], rgb[1], rgb[2], 6.0 * transmittance);

          // sensor
          cairo_move_to(cr, 0, in[dim_up]);
          cairo_line_to(cr, 0+polynomial_length, in[dim_up] + polynomial_length*in[dim_up+2]);
          stroke_with_pencil(cr, scale, 90.0/width);

          // aperture
          double aperture_pos = lens_get_aperture_pos_reverse(lenses, lenses_cnt-1, 0.0);
          cairo_move_to(cr, aperture_pos, ap[dim_up]);
          cairo_line_to(cr, aperture_pos + .2*polynomial_length, ap[dim_up] + .2*polynomial_length*ap[dim_up+2]);
          stroke_with_pencil(cr, scale, 90.0/width);

          // outer pupil
          Eigen::Vector2d outpos(out[0], out[1]);
          Eigen::Vector2d outdir(out[2], out[3]);
          if (stringcmp(lenses[0].geometry, "cyl-y") && !dim_up) cylinderToCs(outpos, outdir, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
          else if (stringcmp(lenses[0].geometry, "cyl-y") && dim_up) cylinderToCs(outpos, outdir, cam_pos, cam_dir, lens_length - 99999.0, 99999.0, true);
          else if (stringcmp(lenses[0].geometry, "cyl-x") && !dim_up) cylinderToCs(outpos, outdir, cam_pos, cam_dir, lens_length - 99999.0, 99999.0, false);
          else if (stringcmp(lenses[0].geometry, "cyl-x") && dim_up) cylinderToCs(outpos, outdir, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
          else sphereToCs(outpos, outdir, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
          cairo_move_to(cr, cam_pos[2], cam_pos[dim_up]);
          cairo_line_to(cr, cam_pos[2] + polynomial_length*cam_dir[2], cam_pos[dim_up] + polynomial_length*cam_dir[dim_up]);
          stroke_with_pencil(cr, scale, 90.0/width);
        }
      }

      if(0)//!error)
      {
        outrt[2] = -outrt[2];
        outrt[3] = -outrt[3];
        outrt[4] = lambda;

        // tmp need to remove
        Eigen::Vector3d tmpdraw01, tmpdraw02;
        error = evaluate_draw(lenses, lenses_cnt, zoom, outrt, inrt, cr, scale, dim_up, draw_aspheric, tmpdraw01, tmpdraw02);
      }  
    }
  }
  
  draw_lenses(cr, scale);
  draw_sensor(cr);
  draw_aperture(cr);

  if (draw_focallength) draw_focal_length(cr, scale);


  if(screenshot) {
    cairo_surface_finish(svg_surface);
    cairo_surface_destroy(svg_surface);
    fmt::print("Saved lens drawing to '{}'\n", lens_svg_path);
    screenshot = !screenshot;
  }

  return FALSE;
}


int main(int argc, char *argv[])
{
  const char *id = argv[1];
  int lens_focal_length = atol(argv[2]);

  // read lens database
  std::string lens_database_path = fmt::format("{}/database/lenses.json", std::getenv("LENTIL_PATH"));
  std::ifstream in_json(lens_database_path.c_str());
  json lens_database = json::parse(in_json);

  // read polynomial systems
  for (const auto& i : lens_database[id]["polynomial-optics"]){
    if (i == lens_focal_length){
      std::string fit_location_exitpupil = fmt::format("{}/fitted/exitpupil.fit", find_lens_id_location(id, lens_focal_length));
      std::string fit_location_aperture = fmt::format("{}/fitted/aperture.fit", find_lens_id_location(id, lens_focal_length));
      
      if(poly_system_read(&poly, fit_location_exitpupil.c_str())){
        fmt::print("[view] could not read poly system '{}'\n", fit_location_exitpupil.c_str());
      } else {
        fmt::print("[view] read poly system '{}'\n", fit_location_exitpupil.c_str());
      }

      if(poly_system_read(&poly_aperture, fit_location_aperture.c_str())){
        fmt::print("[view] could not read poly system '{}'\n", fit_location_aperture.c_str());
      } else {
        fmt::print("[view] read poly system '{}'\n", fit_location_aperture.c_str());
      }

    } else {
      fmt::print("[view] no polynomial system focal length {}\n", lens_focal_length);
    }
  }

  lens_svg_path = fmt::format("{0}/database/lenses/{1}-{2}-{3}/{1}-{2}-{3}.svg", 
                              std::getenv("LENTIL_PATH"),
                              lens_database[id]["year"].get<int>(),
                              lens_database[id]["company"].get<std::string>(),
                              lens_database[id]["product-name"].get<std::string>()
  );


  lenses_cnt = lens_configuration(lenses, id, lens_focal_length);
  lens_length = 0;
  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses[i], zoom);

  lens_pupil_dist = lens_get_thickness(lenses[lenses_cnt-1], zoom);
  lens_pupil_rad  = lenses[lenses_cnt-1].housing_radius;
  aperture_rad = lens_get_aperture_radius(lenses, lenses_cnt);


  // GTK window setup
  GtkWidget *window, *drawing_area;
  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit), NULL);

  drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), drawing_area);
  gtk_widget_set_size_request (drawing_area, width, height);
  g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), NULL);

  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_keypress), NULL);

  gtk_widget_show_all(window);
  gtk_main();


  // cleanup
  poly_system_destroy(&poly);
  poly_system_destroy(&poly_aperture);

  return 0;
}
