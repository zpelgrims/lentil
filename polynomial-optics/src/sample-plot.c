#include "raytrace.h"
#include "poly.h"
#include <math.h>

//#define AP

static lens_element_t lenses[50];
static int lenses_cnt = 0;
static const float zoom = 0.0f;
static int aspheric_elements = 1;

int main(int argc, char *arg[])
{
  if(argc < 2)
  {
    fprintf(stderr, "usage: %s lensfile\n", arg[0]);
    exit(1);
  }
  char *lensfilename = arg[1];
  char fname[1024];
  #ifndef AP
  snprintf(fname, 1024, "%s.fit", lensfilename);
  #else
  snprintf(fname, 1024, "%s_ap.fit", lensfilename);
  #endif
  poly_system_t poly;
  if(poly_system_read(&poly, fname)) fprintf(stderr, "[sample-plot] couldn't open poly `%s'\n", fname);
  lenses_cnt = lens_configuration(lenses, lensfilename, sizeof(lenses));
  const float p_dist = lens_get_thickness(lenses + lenses_cnt-1, zoom);
  const float p_rad = lenses[lenses_cnt-1].housing_radius;
  const int sample_cnt = 5000;
  FILE *f = fopen("sample-plot.dat", "wb");
  for(int i=0;i<sample_cnt;i++)
  {
    const float u = drand48(), v = drand48(), w = drand48(), x = drand48(), y = drand48();
    float ray_in[] = {
      (x-0.5)*36.0f,
      (y-0.5)*24.0f,
      p_rad/p_dist * cosf(2.0f*M_PI*u)*sqrtf(v),
      p_rad/p_dist * sinf(2.0f*M_PI*u)*sqrtf(v),
      0.4 + 0.3*w};
    ray_in[2] -= ray_in[0] / p_dist;
    ray_in[3] -= ray_in[1] / p_dist;
    float out[5] = {0.0f, 0.0f, 0.0f, 0.0f, ray_in[4]};
    float poly_out[5] = {0.0f};
    int error = evaluate(lenses, lenses_cnt, zoom, ray_in, out, aspheric_elements);
    if(!error)
    {
      poly_system_evaluate(&poly, ray_in, poly_out, 100);
      float r[6], p[6];
      #ifndef AP
      sphereToCs(out, out+2, r, r+3, 0, lenses[0].lens_radius);
      sphereToCs(poly_out, poly_out+2, p, p+3, 0, lenses[0].lens_radius);
      #else
      evaluate_aperture(lenses, lenses_cnt, zoom, ray_in, out, aspheric_elements);
      r[0] = out[0]; r[1] = out[1]; r[3] = out[2]; r[4] = out[3];
      p[0] = poly_out[0]; p[1] = poly_out[1]; p[3] = poly_out[2]; p[4] = poly_out[3];
      #endif

      fprintf(f, "%g, %g, %g, %g, %g, %g, %g, %g\n", r[0], r[1], r[3], r[4], p[0], p[1], p[3], p[4]);
    }
    else
      --i;
  }
  fclose(f);
  exit(0);
}
