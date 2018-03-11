#include "raytrace.h"
#include "poly.h"
#include <math.h>

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
  snprintf(fname, 1024, "%s.fit", lensfilename);
  poly_system_t poly;
  if(poly_system_read(&poly, fname)) fprintf(stderr, "[fresnel] couldn't open poly `%s'\n", fname);
  lenses_cnt = lens_configuration(lenses, lensfilename, sizeof(lenses));
  const float p_dist = lens_get_thickness(lenses + lenses_cnt-1, zoom);
  const float p_rad = lenses[lenses_cnt-1].housing_radius;
  const int sample_cnt = 50000;
  FILE *f = fopen("fresnel.dat", "wb");
  // stupid way to set color-range in gnuplot using two points
  fprintf(f, "%g, %g, %g, 0, 0, 1\n", 0.f, 0.f, 1.f);
  fprintf(f, "%g, %g, %g, 0, 0, 0\n", 0.f, 0.f, 0.f);
#define profile_cnt 32
  float profile_valr[profile_cnt] = {0.0f};
  int   profile_numr[profile_cnt] = {0};
  float profile_valp[profile_cnt] = {0.0f};
  int   profile_nump[profile_cnt] = {0};
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
      float intensity = out[4];
      fprintf(f, "%g, %g, %g, %g, %g, %g\n", out[0], out[1], intensity, poly_out[0], poly_out[1], poly_out[4]);
      const float rr = sqrtf(out[0]*out[0] + out[1]*out[1]);
      // const float rp = sqrtf(poly_out[0]*poly_out[0] + poly_out[1]*poly_out[1]);
      // normalise to outer pupil radius
      int binr = profile_cnt * rr/lenses[0].housing_radius;
      // int binp = profile_cnt * rp/lenses[0].housing_radius;
      profile_valr[binr] += intensity;
      profile_numr[binr] ++;
      profile_valp[binr] += poly_out[4];
      profile_nump[binr] ++;
    }
    else
      --i;
  }
  fclose(f);
  for(int k=0;k<profile_cnt;k++) if(profile_numr[k]) profile_valr[k] /= profile_numr[k];
  for(int k=0;k<profile_cnt;k++) if(profile_nump[k]) profile_valp[k] /= profile_nump[k];
  f = fopen("fresnel-profile.dat", "wb");
  for(int k=0;k<profile_cnt;k++) fprintf(f, "%g %g\n", profile_valr[k], profile_valp[k]);
  fclose(f);
  exit(0);
}
