#include "raytrace.h"
#include <math.h>

#define min(a, b) ((a)<(b)?(a):(b))
# define M_PI   3.14159265358979323846  /* pi */
#define FLT_MAX 1e35

static int iteration_cnt = 0;
const float dist = 0;
const float dst_dist = 10000;
float last_err, last_ap_err;
FILE *logfile = 0;

static inline float dotproduct(float *u, float *v)
{
  return raytrace_dot(u, v);
}

static inline void crossproduct(const float *r, const float *u, float *v)
{
  return raytrace_cross(v, r, u);
}

static inline void normalise(float *v)
{
  return raytrace_normalise(v);
}

static inline float MAX(float a, float b)
{
  return a>b?a:b;
}

void log_iteration(const float *appos, const float aperr, const float *outpos, const float *outdir, const float sen_x, const float sen_dx, const float outerr)
{
  if(logfile)
    fprintf(logfile, "%d %g %g %g %g %g %g %g %g %g\n", iteration_cnt, aperr, outerr, iteration_cnt*1.0f, sen_x, 1.0f, sen_dx, outpos[0], outdir[2], outdir[0]);
  iteration_cnt++;
  last_err = outerr;
  last_ap_err = aperr;
}

void common_sincosf(float, float*, float*);

#define DEBUG_LOG log_iteration(pred_ap, sqr_ap_err, pred_out_cs, pred_out_cs+3, begin_x, begin_dx, sqr_err)

#include "render/lens.h"

int main(int argc, char *arg[])
{
  FILE *f = fopen("lt_convergence_profile.dat", "wb");
  
  //sample points in scene on a sphere
  for(float a = -M_PI; a <= M_PI; a += M_PI/3600)
  {
    float scene[] = {sinf(a)*dst_dist, 0, cosf(a)*dst_dist + lens_length - lens_outer_pupil_curvature_radius};
    //try different points on aperture and count number of iterations
    //for(...)
    float out[] = {0, 0, 0, 0, 0, 0, 0}; //output
    for(int i = 0; i < 10000; i++)
    {
      float u = drand48(), v = drand48();
      float ap[] = {
        lens_aperture_housing_radius * cosf(2.0f*M_PI*u)*sqrtf(v),
        lens_aperture_housing_radius * sinf(2.0f*M_PI*u)*sqrtf(v)
      };
      float sensor[] = {0, 0, 0, 0, 0}; //output
      float lambda = .55;
      iteration_cnt = 0;
      //fprintf(stderr, "%g\n", fabs(a-acosf(lens_field_of_view)/2));
      if(fabs(a - acosf(lens_field_of_view)/2) < M_PI/3600)
        logfile = fopen("lt_convergence.dat", "wb");
      lens_lt_sample_aperture(scene, ap, sensor, out, lambda);
      if(fabs(a - acosf(lens_field_of_view)/2) < M_PI/3600)
      {
        fclose(logfile);
        logfile = 0;
      }
      if(last_err != last_err || last_err > 100)
        last_err = 100;
      if(last_ap_err != last_ap_err || last_ap_err > 100)
        last_ap_err = 100;
      if(out[4] > 0 && out[0] == out[0] && out[1] == out[1])
        break;
    }
    if(out[4]>0)
    fprintf(f, "%g %d %g %g\n", a*180/M_PI, iteration_cnt, last_err, last_ap_err);
    //fprintf(stderr, "[%g] %d, %g %g %g, %g %g %g\n", a, iteration_cnt, out[0], out[1], out[2], out[3], out[4], out[5]);
  }
  fclose(f);
  exit(0);
}
