#include "lenssystem.h"
#include "raytrace.h"
#include "raytrace_draw.h"
#include "poly.h"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>
#include <cairo-svg.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#include <sys/time.h>
#include <fenv.h>

//json parsing
#include "../ext/json.hpp"
#include <string>
#include <fstream>
using json = nlohmann::json;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static float zoom = 0.0f; // zoom, if the lens supports it.
//static const int degree = 4;  // degree of the polynomial. 1 is thin lens
//static const float coverage = .5f; // coverage of incoming rays at scene facing pupil (those you point with the mouse)
static int num_rays = 50;
static int dim_up = 0; // plot yz (side) or xz (top) of the lens in 2d?
static char lensfilename[512] = "";
static char lens_name[512];
static poly_system_t poly, poly_aperture;
static float aperture_rad;
static lens_element_t lenses[50];
static int lenses_cnt = 0;
static float lens_pupil_dist = 0.0f;
static float lens_pupil_rad = 0.0f;
static float lens_length = 0;
static float aperture_pos = 0;

//remove these mouse events
static float mouse_x = 0.0f;
static float mouse_y = 0.0f;

static int screenshot = 1;
static int draw_solve_omega = 0;
static int draw_raytraced = 1;
static int draw_polynomials = 1;
static int draw_aspheric = 1;

static int width = 900;
static int height = 550;
static int gridsize = 10; //10 mm

static float extra_space = 0.0f;
static float global_scale = 20.0f;
static float window_aspect_ratio = (float)width/(float)height;

float black[4] = {0.05, 0.05, 0.05, 1.0};
float darkgrey[4] = {0.15, 0.15, 0.15, 1.0};
float grey[4] = {0.5, 0.5, 0.5, 1.0};
float lightgrey[4] = {0.7, 0.7, 0.7, 1.0};
float yellow[4] = {0.949, 0.882, 0.749, 0.65};
float green[4] = {0.749, 0.949, 0.874, 1.0};
float white50[4] = {1.0, 1.0, 1.0, 0.5};

static gboolean
motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
{
  if(event->state & GDK_BUTTON1_MASK)
  {
    mouse_x = event->x;
    mouse_y = event->y;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  return FALSE;
}

static gboolean
key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  if(event->keyval == GDK_KEY_Escape)
  {
    gtk_main_quit();
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_p)
  {
    fprintf(stderr, "Saving lens drawing\n");
    screenshot = 1;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_a)
  {
    draw_aspheric = !draw_aspheric;
    fprintf(stderr, "using %sspherical lenses\n", draw_aspheric?"a":"");
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  /*
  else if(event->keyval == GDK_KEY_i)
  {
    // adjust lens position to focus perfectly at infinity
    extra_space += 0.1;
    printf("extra_space: %f\n", extra_space);
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  */
  else if(event->keyval == GDK_KEY_plus)
  {
    global_scale += 1;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_minus)
  {
    global_scale -= 1;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_m)
  {
    num_rays += 10;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_l)
  {
    num_rays -= 10;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_s)
  {
    if (dim_up) dim_up = 0;
    else dim_up = 1;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  return FALSE;
}

static gboolean button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
  if (!GTK_WIDGET_HAS_FOCUS(widget))
    gtk_widget_grab_focus(widget);
  if(event->button == 1)// && event->type == GDK_2BUTTON_PRESS)
  {
    mouse_x = event->x;
    mouse_y = event->y;
    gtk_widget_queue_draw(widget);
    return TRUE;
  }
  return FALSE;
}

static inline float hue_2_rgb(float v1, float v2, float vH)
{
  if (vH < 0.0f) vH += 1.0f;
  if (vH > 1.0f) vH -= 1.0f;
  if ((6.0f * vH) < 1.0f) return (v1 + (v2 - v1) * 6.0f * vH);
  if ((2.0f * vH) < 1.0f) return (v2);
  if ((3.0f * vH) < 2.0f) return (v1 + (v2 - v1) * ((2.0f / 3.0f) - vH) * 6.0f);
  return (v1);
}

static inline void hsl_2_rgb(const float *HSL, float *RGB)
{
  float H = HSL[0];
  float S = HSL[1];
  float L = HSL[2];

  float var_1, var_2;

  if (S < 1e-6f)
  {
    RGB[0] = RGB[1] = RGB[2] = L;
  }
  else
  {
    if (L < 0.5f) var_2 = L * (1.0f + S);
    else          var_2 = (L + S) - (S * L);

    var_1 = 2.0f * L - var_2;

    RGB[0] = hue_2_rgb(var_1, var_2, H + (1.0f / 3.0f));
    RGB[1] = hue_2_rgb(var_1, var_2, H);
    RGB[2] = hue_2_rgb(var_1, var_2, H - (1.0f / 3.0f));
  }
}

static void stroke_with_pencil(cairo_t *cr, float scale, float line_width)
{
  cairo_save(cr);
  cairo_scale(cr, 1./scale, 1./scale);
  cairo_set_line_width(cr, line_width);
  cairo_stroke(cr);
  cairo_restore(cr);
}

static gboolean expose(GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
  cairo_t *cr = 0;
  cairo_surface_t *cst = 0;
  if(screenshot)
  {
    cst = cairo_svg_surface_create("lens-drawing.svg", width, height);
    cr = cairo_create(cst);
  } else {
    width = widget->allocation.width;
    height = widget->allocation.height;
    cr = gdk_cairo_create(gtk_widget_get_window(widget));
  }

  cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
  cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
  cairo_set_source_rgb(cr, darkgrey[0], darkgrey[1], darkgrey[2]);
  cairo_paint(cr);
  cairo_set_line_width(cr, 1.0f);

  // optical axis:
  cairo_set_source_rgb(cr, white50[0], white50[1], white50[2]);
  cairo_move_to(cr, 0, height/2.0);
  cairo_line_to(cr, width, height/2.0);
  cairo_stroke(cr);

  cairo_translate(cr, 0, height/2.0);
  cairo_scale(cr, ((float)width/window_aspect_ratio)/20.0, (float)height/20.0);
  cairo_set_line_width(cr, 40.0/width);


  // draw lens
  // scale by arbitrary factor
  const float scale = global_scale/lens_length;
  cairo_scale(cr, scale, scale);

  // move 20mm away
  cairo_translate(cr, 20.0, 0.0);

  // grid
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

  // rulers

  // find max housing radius
  float max_housing_radius = 0.0;
  for (int i=0; i < lenses_cnt; i++){
    if (lenses[i].housing_radius > max_housing_radius){
      max_housing_radius = lenses[i].housing_radius;
    }
  }

  float ruler_height = 2.5;
  float ruler_padding = gridsize;
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

  cairo_set_line_width(cr, 40.0/width);
  cairo_set_source_rgb(cr, lightgrey[0], lightgrey[1], lightgrey[2]);

  float pos = lens_length;
  aperture_pos = lens_length/2.0f;
  float hsl[3], rgb[3];

  for(int i=0;i<lenses_cnt;i++)
  {
    // untested
    // something wrong with glass->air interfaces, they dont change when changing axis
    float rad = lenses[i].lens_radius;
    if (lenses[i].anamorphic){
      if (!dim_up){ // sideview
        if(lenses[i].cylinder_axis_y){
          rad = 999999.0;
        }
      } else { // topview
        if(!lenses[i].cylinder_axis_y){
          rad = 999999.0;
        }
      }
    }
    //float rad = (dim_up && lenses[i].anamorphic) ? 900000.0 : lenses[i].lens_radius;
    
    
    float hrad = lenses[i].housing_radius;
    float t = lens_get_thickness(lenses+i, zoom);

    if(!strcasecmp(lenses[i].material, "iris"))
      aperture_pos = pos;

    if(lenses[i].ior != 1.0f && i < lenses_cnt-1)
    {
      cairo_save(cr);

      // untested
      float rad2 = lenses[i+1].lens_radius;
      if (lenses[i+1].anamorphic){
        if (!dim_up){ // sideview
          if(lenses[i+1].cylinder_axis_y){
            rad2 = 999999.0;
          }
        } else { // topview
          if(!lenses[i+1].cylinder_axis_y){
            rad2 = 999999.0;
          }
        }
      }
      //float rad2 = (dim_up && lenses[i+1].anamorphic) ? 900000.0 : lenses[i+1].lens_radius;


      float hrad2 = lenses[i+1].housing_radius;
      float off  = rad  > 0.0f ? 0.0f : M_PI;
      float off2 = rad2 > 0.0f ? 0.0f : M_PI;
      float alpha  = asinf(fminf(1.0f, fmaxf(-1.0f, fabsf(hrad/rad))));
      float alpha2 = asinf(fminf(1.0f, fmaxf(-1.0f, fabsf(hrad2/rad2))));

      if(draw_aspheric)
      {
        const int num_steps = 50;

        for(int j = 0; j <= num_steps; j++)
        {
          float y[] = {hrad*(2 * j / (float)num_steps - 1), 0};
          float *coeff = lenses[i].aspheric_correction_coefficients;
          float x = pos-evaluate_aspherical(y, rad, lenses[i].aspheric, coeff);
          cairo_line_to(cr, x, y[0]);
        }

        for(int j = num_steps; j >= 0; j--)
        {
          float y[] = {hrad2*(2 * j / (float)num_steps - 1), 0};
          float *coeff = lenses[i+1].aspheric_correction_coefficients;
          float x = pos-t-evaluate_aspherical(y, rad2, lenses[i+1].aspheric, coeff);
          cairo_line_to(cr, x, y[0]);
        }
      }
      else
      {
        cairo_arc(cr, pos-rad, 0.0f, fabsf(rad), off-alpha, off+alpha);
        if(rad * rad2 > 0.0f)
          cairo_arc_negative(cr, pos-t-rad2, 0.0f, fabsf(rad2), off2+alpha2, off2-alpha2);
        else
          cairo_arc(cr, pos-t-rad2, 0.0f, fabsf(rad2), off2-alpha2, off2+alpha2);
      }
      cairo_close_path(cr);
      
      if (lenses[i+1].anamorphic) cairo_set_source_rgba(cr, yellow[0], yellow[1], yellow[2], yellow[3]);
      else cairo_set_source_rgb(cr, grey[0], grey[1], grey[2]);
      cairo_fill_preserve(cr);

      cairo_set_source_rgb(cr, lightgrey[0] + 0.1f, lightgrey[1] + 0.1f, lightgrey[2] + 0.1f);
      stroke_with_pencil(cr, scale, 40.0/width);

      cairo_restore(cr);
    }
    else
    {
      // backside (air-facing), actually drawn double most of the time
      cairo_save(cr);
      cairo_rectangle(cr, pos-rad-2, -hrad, 2*rad+4, 2*hrad);
      cairo_clip(cr);
      if(draw_aspheric)
      {
        const int num_steps = 50;
        for(int j = 0; j <= num_steps; j++)
        {
          float y[] = {hrad*(2 * j / (float)num_steps - 1), 0};
          float *coeff = lenses[i].aspheric_correction_coefficients;
          float x = pos-evaluate_aspherical(y, rad, lenses[i].aspheric, coeff);
          cairo_line_to(cr, x, y[0]);
        }
      }
      else
      {
        cairo_arc(cr, pos-rad, 0.0f, fabsf(rad), .0f, 2.0f*M_PI);
      }
      stroke_with_pencil(cr, scale, 40./width);

      cairo_close_path(cr);
      if (lenses[i].anamorphic) cairo_set_source_rgba(cr, yellow[0], yellow[1], yellow[2], yellow[3]);
      else cairo_set_source_rgb(cr, grey[0], grey[1], grey[2]);
      cairo_fill(cr);

      cairo_restore(cr);
    }
    pos -= t;
  }


  // draw the sensor (35mm)
  cairo_move_to(cr, -1.0, -35.0/2.0);
  cairo_line_to(cr, -1.0,  35.0/2.0);
  cairo_line_to(cr,  0.0,  35.0/2.0);
  cairo_line_to(cr,  0.0, -35.0/2.0);
  cairo_close_path(cr);
  cairo_set_source_rgb(cr, grey[0], grey[1], grey[2]);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, lightgrey[0], lightgrey[1], lightgrey[2]);

  const float len = lens_length/10.0f;
  float variation[2] = {0.0f, 0.0f};

  for(int k=0; k<num_rays; k++){

    // y wedge
    const float y = 2.0f * (num_rays/2-k)/(float)num_rays * lenses[0].housing_radius;

    float cam_pos[3] = {0.0f};
    cam_pos[dim_up] = y;
    // zeno: what are these calculations doing? figure out
    cam_pos[2] = sqrtf(lenses[0].lens_radius*lenses[0].lens_radius - lenses[0].housing_radius*lenses[0].housing_radius);
    const float s = lenses[0].lens_radius / sqrtf(cam_pos[2]*cam_pos[2] + y*y);
    cam_pos[2] *= s;
    cam_pos[dim_up] *= s;
    cam_pos[2] += lens_length - lenses[0].lens_radius;


    float cam_dir[3] = {0.0f};
    cam_dir[2] = cam_pos[2] - 99999999;
    cam_dir[dim_up] = cam_pos[dim_up];
    raytrace_normalise(cam_dir);

    for(int i=0;i<3;i++) cam_pos[i] -= 0.1f * cam_dir[i];

    const float lambda = 0.5f;

    float in[5] = {0.0f};
    float out[5] = {0.0f};
    float ap[5] = {0.0f};
    float inrt[5] = {0.0f};
    float outrt[5] = {0.0f};
    inrt[4] = outrt[4] = in[4] = out[4] = ap[4] = lambda;

    float t, n[3] = {0.0f};
    spherical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n);

    for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)

    csToSphere(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
    sphereToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);

    for(int i=0;i<5;i++) inrt[i] = in[i];

    int error = 0;

    if(draw_raytraced)
      error = evaluate_reverse_draw(lenses, lenses_cnt, zoom, inrt, outrt, cr, scale, dim_up, draw_aspheric);
    else
      error = evaluate_reverse(lenses, lenses_cnt, zoom, inrt, outrt, draw_aspheric);


    // ray color:
    hsl[0] = k/(num_rays+1.);
    hsl[1] = .7f;
    hsl[2] = .5f;
    hsl_2_rgb(hsl, rgb);

    if(!error)
    {
      // evaluate sensor -> light
      for(int i=0;i<5;i++) in[i] = outrt[i];
      in[2] = -in[2];
      in[3] = -in[3];
      //outrt[4] equals transmittance
      in[4] = lambda;
      poly_system_evaluate(&poly, in, out, 15);

      // evaluate error poly vs ray traced:
      const float px_ratio = 2000.0/36.0f; // 5k pixels for 36mm film back (width)
      // const float px_err = sqrtf((out[0]-outrt[0])*(out[0]-outrt[0]) + (out[1]-outrt[1])*(out[1]-outrt[1]))*px_ratio;
      // fprintf(stderr, "error ray %d: %.02f pixels (%f %f)\n", k, px_err, (out[0] - outrt[0])*px_ratio, (out[1] - outrt[1])*px_ratio);
      variation[0] += (out[0] - outrt[0])*px_ratio;
      variation[1] += (out[1] - outrt[1])*px_ratio;
    }


    if(!error && draw_polynomials)
    {
      // draw everything grayed out in case it got killed on the aperture
      poly_system_evaluate(&poly_aperture, in, ap, 15);
      const int aperture_death = (ap[0]*ap[0] + ap[1]*ap[1] > aperture_rad*aperture_rad);
      if(!aperture_death)
      {
        // use transmittance from polynomial evaluation
        float transmittance = out[4];
        cairo_set_source_rgba(cr, rgb[0], rgb[1], rgb[2], 3.0 * transmittance);
        // sensor
        cairo_move_to(cr, 0, in[dim_up]);
        cairo_line_to(cr, 0+len, in[dim_up] + len*in[dim_up+2]);
        stroke_with_pencil(cr, scale, aperture_death ? 40./width : 60./width);

        // aperture
        cairo_move_to(cr, aperture_pos, ap[dim_up]);
        cairo_line_to(cr, aperture_pos+.2*len, ap[dim_up] + .2*len*ap[dim_up+2]);
        stroke_with_pencil(cr, scale, aperture_death ? 40./width : 60./width);

        // outer pupil
        sphereToCs(out, out+2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
        cairo_move_to(cr, cam_pos[2], cam_pos[dim_up]);
        cairo_line_to(cr, cam_pos[2]+len*cam_dir[2], cam_pos[dim_up] + len*cam_dir[dim_up]);
        stroke_with_pencil(cr, scale, aperture_death ? 40./width : 60./width);
      }
    }

    
    if(0)//!error)
    {
      outrt[2] = -outrt[2];
      outrt[3] = -outrt[3];
      outrt[4] = lambda;
      error = evaluate_draw(lenses, lenses_cnt, zoom, outrt, inrt, cr, scale, dim_up, draw_aspheric);
    }
  }
  // fprintf(stderr, "total variation of errors: (%f %f)\n", variation[0], variation[1]);

  cairo_destroy(cr);
  if(screenshot)
  {
    //cairo_surface_write_to_png(cst, "lens-drawing.png" );
    cairo_surface_destroy(cst);
    screenshot = 0;
  }
  return TRUE;
}

int main(int argc, char *argv[])
{
  const char *id = argv[1];
  int lens_focal_length = atol(argv[2]);

  // read lens database
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";

  std::ifstream in_json(lens_database_path.c_str());
  json lens_database = json::parse(in_json);

  for (const auto& i : lens_database[id]["polynomial-optics"]){
    if (i == lens_focal_length){
      std::string fit_location_exitpupil = find_lens_id_location(id, lens_focal_length);
      fit_location_exitpupil += "fitted/exitpupil.fit";
      if(poly_system_read(&poly, fit_location_exitpupil.c_str())){
        printf("[view] could not read poly system `%s'\n", fit_location_exitpupil.c_str());
      }
    } else {
      printf("[view] no exitpupil poly system focal length %d\n", lens_focal_length);
    }
  }
  for (const auto& i : lens_database[id]["polynomial-optics-aperture"]){
    if (i == lens_focal_length){
      std::string fit_location_aperture = find_lens_id_location(id, lens_focal_length);
      fit_location_aperture += "fitted/aperture.fit";
      if(poly_system_read(&poly_aperture, fit_location_aperture.c_str())){
        printf("[view] could not read poly system `%s'\n", fit_location_aperture.c_str());
      }
    } else {
      printf("[view] no aperture poly system focal length %d\n", lens_focal_length);
    }
  }

  
  // calculate lens length
  lenses_cnt = lens_configuration(lenses, id, lens_focal_length);
  lens_length = 0;
  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses+i, zoom);

  lens_pupil_dist = lens_get_thickness(lenses + lenses_cnt-1, zoom);
  lens_pupil_rad  = lenses[lenses_cnt-1].housing_radius;
  aperture_rad = lens_get_aperture_radius(lenses, lenses_cnt);

/*
  int dump = 0;
  if(argc > 2 && !strcmp(argv[2], "-o")) dump = 1;
*/
  GtkWidget *window;
/*
  if(!dump)
  {
*/
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Lens Validation");
    gtk_window_resize(GTK_WINDOW(window), width, height);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), area);
    gtk_drawing_area_size(GTK_DRAWING_AREA(area), width, height);
    gtk_widget_add_events(GTK_WIDGET(area), GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_LEAVE_NOTIFY_MASK);

    g_signal_connect(area, "expose-event", G_CALLBACK(expose), NULL);
    g_signal_connect(area, "button-press-event", G_CALLBACK (button_press), NULL);
    g_signal_connect(area, "key-press-event", G_CALLBACK (key_press), NULL);
    g_signal_connect(area, "motion-notify-event", G_CALLBACK (motion_notify), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    GTK_WIDGET_SET_FLAGS(area, GTK_CAN_FOCUS);

    gtk_widget_show (window);
    gtk_widget_show_all (window);

    gtk_main ();
  /*
  }
  else
  {
    screenshot = 1;
    draw_solve_omega = 0;
    draw_raytraced = 1;
    draw_polynomials = 1;
    expose(0, 0, 0);
  }*/

  poly_system_destroy(&poly);
  poly_system_destroy(&poly_aperture);

  return 0;
}
