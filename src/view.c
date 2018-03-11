#include "lenssystem.h"
#include "raytrace.h"
#include "raytrace_draw.h"
#include "poly.h"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#include <sys/time.h>
#include <fenv.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static float zoom = 0.0f; // zoom, if the lens supports it.
static const int degree = 4;  // degree of the polynomial. 1 is thin lens
static const float coverage = .5f; // coverage of incoming rays at scene facing pupil (those you point with the mouse)
static const int num_rays = 30;//13;
static const int dim_up = 0; // plot yz or xz of the lens in 2d?
static char lensfilename[512] = "lenses/canon-anamorphic-converter.fx";
static char lens_name[512];
static poly_system_t poly, poly_aperture;
static float aperture_rad;
static lens_element_t lenses[50];
static int lenses_cnt = 0;
static float lens_pupil_dist = 0.0f, lens_pupil_rad = 0.0f;
static float lens_length = 0, aperture_pos = 0;
static float mouse_x = 0.0f, mouse_y = 0.0f;
static int screenshot = 0;
static int draw_solve_omega = 0;
static int draw_raytraced = 1;
static int draw_polynomials = 1;
static int width = 1600;
static int height = 800;

static int draw_aspheric = 1;

static gboolean
motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
{
  if(event->state & GDK_BUTTON1_MASK)
  {
    mouse_x = event->x;
    mouse_y = event->y;
    gtk_widget_queue_draw(widget);
    // fprintf(stderr, "mouse %g %g\n", mouse_x, mouse_y);
    return TRUE;
  }
  return FALSE;
}

static gboolean
key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  if(event->keyval == GDK_KEY_q || event->keyval == GDK_KEY_Escape)
  {
    gtk_main_quit();
    return TRUE;
  }
  else if(event->keyval == GDK_KEY_p)
  {
    fprintf(stderr, "saving screenshot.pdf\n");
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
  return FALSE;
}

static gboolean
button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
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

static inline float
hue_2_rgb(float v1, float v2, float vH)
{
  if (vH < 0.0f) vH += 1.0f;
  if (vH > 1.0f) vH -= 1.0f;
  if ((6.0f * vH) < 1.0f) return (v1 + (v2 - v1) * 6.0f * vH);
  if ((2.0f * vH) < 1.0f) return (v2);
  if ((3.0f * vH) < 2.0f) return (v1 + (v2 - v1) * ((2.0f / 3.0f) - vH) * 6.0f);
  return (v1);
}

static inline void
hsl_2_rgb(const float *HSL, float *RGB)
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

static void
stroke_with_pencil(cairo_t *cr, float scale, float line_width)
{
  cairo_save(cr);
  cairo_scale(cr, 1./scale, 1./scale);
  cairo_set_line_width(cr, line_width);
  cairo_stroke(cr);
  cairo_restore(cr);
}

static gboolean
expose(GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
  cairo_t *cr = 0;
  cairo_surface_t *cst = 0;
  if(screenshot)
  {
    cst = cairo_pdf_surface_create("screenshot.pdf", width, height);//cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(cst);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_set_line_width(cr, 1.);
    cairo_set_source_rgba(cr, 0, 0, 0, .5);
  }
  else
  {
    width = widget->allocation.width;
    height = widget->allocation.height;
    cr = gdk_cairo_create(gtk_widget_get_window(widget));
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_set_line_width(cr, 1.);
    cairo_set_source_rgba(cr, 1, 1, 1, .5);
  }

  // optical axis:
  cairo_move_to(cr, 0, height/2.0);
  cairo_line_to(cr, width, height/2.0);
  cairo_stroke(cr);

  cairo_scale(cr, width/40.0, height/20.0);
  cairo_translate(cr, 0, 10);
  cairo_set_line_width(cr, 40.0/width);

  // black box lens system:
  cairo_rectangle(cr, 10, -5, 20, 10);
  cairo_stroke(cr);

  cairo_move_to(cr, 10, -6);
  cairo_set_font_size(cr, 1);
  cairo_show_text(cr, lens_name);
  cairo_new_path(cr);

  // draw lens
  // cairo_save(cr);
  // cairo_rectangle(cr, 10, -5, 20, 10);
  // cairo_clip(cr);
  const float scale = 20.0/lens_length;
  cairo_translate(cr, 10.0, 0.0);
  cairo_scale(cr, scale, scale);
  // cairo_set_line_width(cr, 1.0f);
  float pos = lens_length;
  aperture_pos = lens_length/2.0f;
  float hsl[3], rgb[3];
  for(int i=0;i<lenses_cnt;i++)
  {
    float rad = (dim_up && lenses[i].anamorphic) ? 900000.0 : lenses[i].lens_radius;
    float hrad = lenses[i].housing_radius;
    float t = lens_get_thickness(lenses+i, zoom);
    if(!strcasecmp(lenses[i].material, "iris"))
      aperture_pos = pos;
    if(lenses[i].ior != 1.0f && i < lenses_cnt-1)
    {
      cairo_save(cr);

      float rad2 = (dim_up && lenses[i+1].anamorphic) ? 900000.0 : lenses[i+1].lens_radius;
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
      if(screenshot)
        cairo_set_source_rgba(cr, 0.2f, 0.2f, 0.3f, .5f);
      else
        cairo_set_source_rgba(cr, 0.8f, 0.8f, 1.0f, .5f);
      cairo_fill_preserve(cr);
      if(screenshot)
        cairo_set_source_rgba(cr, 0.0f, 0.0f, 0.0f, 1.0f);
      else
        cairo_set_source_rgba(cr, 1.0f, 1.0f, 1.0f, 1.0f);
      stroke_with_pencil(cr, scale, 40./width);
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
  cairo_set_source_rgb(cr, .5, .5, .5);
  cairo_fill(cr);
  // pos is now about 0 and points to the left end of the blackbox
  // cairo_restore(cr);

  const float len = lens_length/10.0f;
  const float m_x = (mouse_x - width/4.0f)/(width/2.0f) * lens_length;
  const float m_y = (mouse_y - height/2.0f)/(height) * lens_length;
  float variation[2] = {0.0f, 0.0f};
  for(int k=0;k<num_rays;k++)
  {
#if 0 // lambda wedge
    const float y = m_y/m_x * len;//0.0f;//coverage * 2.0f*(num_rays/2-k)/(float)num_rays * lenses[0].housing_radius;
    const float dy = (y - m_y)/(m_x - lens_length);
    const float lambda = 0.4f + coverage*(num_rays/2-k)/(float)num_rays * 0.3f;
#endif
#if 1 // y wedge
    const float y = 2.0f*(num_rays/2-k)/(float)num_rays * lenses[0].housing_radius;

    float cam_pos[3] = {0.0f};
    cam_pos[dim_up] = y;
    const float r = lenses[0].lens_radius;
    const float R = lenses[0].housing_radius;
    cam_pos[2] = sqrtf(r*r - R*R);
    const float s = r/sqrtf(cam_pos[2]*cam_pos[2] + y*y);
    cam_pos[2] *= s;
    cam_pos[dim_up] *= s;
    cam_pos[2] += lens_length - r;

    float cam_dir[3] = {0.0f};   // cam direction pointing from mouse pointer towards lens
    cam_dir[2] = cam_pos[2] - m_x;
    cam_dir[dim_up] = cam_pos[dim_up] - m_y;
    raytrace_normalise(cam_dir);

    for(int i=0;i<3;i++) cam_pos[i] -= 0.1f * cam_dir[i];

    const float lambda = 0.5f;
#endif
    float in[5] = {0.0f};
    float out[5] = {0.0f}, ap[5] = {0.0f};
    float inrt[5] = {0.0f}, outrt[5] = {0.0f};
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
    cairo_surface_destroy(cst);
    screenshot = 0;
  }
  return TRUE;
}

int
main(int argc, char *argv[])
{
  // feenableexcept(FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
  if(argc > 1) strncpy(lensfilename, argv[1], 512);
  lens_canonicalize_name(lensfilename, lens_name);
  char fname[1024];
  snprintf(fname, 1024, "%s.fit", lensfilename);
  if(poly_system_read(&poly, fname))
  {
    fprintf(stderr, "[view] could not read poly system `%s'\n", fname);
    // exit(0);
  }
  snprintf(fname, 1024, "%s_ap.fit", lensfilename);
  if(poly_system_read(&poly_aperture, fname))
  {
    fprintf(stderr, "[view] could not read poly system `%s'\n", fname);
    // exit(0);
  }

  lenses_cnt = lens_configuration(lenses, lensfilename, sizeof(lenses));
  lens_length = 0;
  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses+i, zoom);

  lens_pupil_dist = lens_get_thickness(lenses + lenses_cnt-1, zoom);
  lens_pupil_rad  = lenses[lenses_cnt-1].housing_radius;
  aperture_rad = lens_get_aperture_radius(lenses, lenses_cnt);

  int dump = 0;
  if(argc > 2 && !strcmp(argv[2], "-o")) dump = 1;

  GtkWidget *window;

  if(!dump)
  {
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "lens simulation");
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
  }
  else
  {
    screenshot = 1;
    if(!strncmp(lens_name, "fisheye", 7))
    {
      mouse_x = 556;
      mouse_y = -3;
    }
    else
    {
      mouse_x = 100000;
      mouse_y = -5000;
    }
    draw_solve_omega = 0;
    draw_raytraced = 1;
    draw_polynomials = 1;
    expose(0, 0, 0);
  }

  poly_system_destroy(&poly);
  poly_system_destroy(&poly_aperture);

  return 0;
}
