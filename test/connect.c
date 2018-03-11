#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

static inline void common_sincosf(float phi, float* sin, float* cos)
{
#ifdef __APPLE__
  *sin = sinf(phi);
  *cos = cosf(phi);
#else
  sincosf(phi, sin, cos);
#endif
}

#define crossproduct(v1, v2, res) \
  (res)[0] = (v1)[1]*(v2)[2] - (v2)[1]*(v1)[2];\
  (res)[1] = (v1)[2]*(v2)[0] - (v2)[2]*(v1)[0];\
  (res)[2] = (v1)[0]*(v2)[1] - (v2)[0]*(v1)[1]

#define dotproduct(u, v) ((u)[0]*(v)[0] + (u)[1]*(v)[1] + (u)[2]*(v)[2])

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(a, m, M) MIN(MAX(a, m), M)

static inline void normalise(float *f)
{
  const float len = 1.0f/sqrtf(dotproduct(f, f));
  for(int k=0;k<3;k++) f[k] *= len;
}

#include "lens.h"
#include "convexhull.h"

int main(int argc, char *argv[])
{
  // look at this point, distances in mm
  const float p[3] = {110., 70., 1000.};
  const float lambda = 0.550f; // wavelength in um

  const float sensor_width = 36.0f;
  const float sensor_height = 24.0f;
  const float f_stop = 1.0f;
  const int num_blades = 6;
  const float aperture_radius = fminf(lens_aperture_housing_radius, lens_focal_length/(2.0f * f_stop));

  fprintf(stderr, "processing lens %s\n", lens_name);

  FILE *points = fopen("points.dat", "wb");

  const int N = 10000;
  int hull_size;
  point_t pt[N];
  point_t *hull[N];
  int num_visible = 0;

  for(int n=0;n<N;n++)
  {
    const float ax = drand48();
    const float ay = drand48();

    // [x,y,dx,dy,lambda] on the sensor, aperture, and outgoing pupil:
    float sen[5], ape[5], out[5];
    sen[4] = ape[4] = out[4] = lambda;

    // sample point on aperture
    lens_sample_aperture(ape+0, ape+1, ax, ay, aperture_radius, num_blades);

    // initial guess: sensor = 0, direction via aperture sampling
    sen[0] = sen[1] = 0.0f;

    float transmittance = lens_lt_sample_aperture(p, ape, sen, out, sen[4]);
    // compute visibility of sample: pixel coordinate, inner pupil, outer pupil
    int visible = transmittance > 0.0f;

    // clip at inward facing pupil:
    const float px = sen[0] + sen[2] * lens_focal_length, py = sen[1] + sen[3]*lens_focal_length;
    if(px*px + py*py > lens_inner_pupil_radius*lens_inner_pupil_radius)
      visible = 0;

    // clip at outer pupil:
    if(sqrtf(out[0]*out[0] + out[1]*out[1]) > lens_outer_pupil_radius)
      visible = 0;

    // sensor clipping:
    if(sen[0] > sensor_width/2.0 || sen[0] < -sensor_width/2.0 || sen[1] > sensor_height/2.0 || sen[1] < -sensor_height/2.0)
      visible = 0;

    pt[num_visible].x = out[0]/lens_outer_pupil_radius;
    pt[num_visible].y = out[1]/lens_outer_pupil_radius;
    if(visible)
      num_visible++;
      // fprintf(points2, "%g %g\n", out[0]/lens_outer_pupil_radius, out[1]/lens_outer_pupil_radius);
  }

  hull_size = convex_hull(pt, num_visible, hull);
  for(int k=0;k<hull_size;k++)
    fprintf(points, "%g %g\n", hull[k]->x, hull[k]->y);

  fclose(points);
  FILE *points2 = fopen("points2.dat", "wb");

  num_visible = 0;
  for(int n=0;n<N;n++)
  {
    const float ax = drand48();
    const float ay = drand48();

    // [x,y,dx,dy,lambda] on the sensor, aperture, and outgoing pupil:
    float sen[5], ape[5], out[5];
    sen[4] = ape[4] = out[4] = lambda;

    // sample point on aperture
    lens_sample_aperture(ape+0, ape+1, ax, ay, aperture_radius, num_blades);

    // initial guess: sensor = 0, direction via aperture sampling
    sen[0] = sen[1] = 0.0f;

    float transmittance = lens_lt_sample_aperture(p, ape, sen, out, sen[4]);
    if(transmittance > 0.0f)
    {
      pt[num_visible].x = out[0]/lens_outer_pupil_radius;
      pt[num_visible].y = out[1]/lens_outer_pupil_radius;
      num_visible++;
    }
  }

  hull_size = convex_hull(pt, num_visible, hull);
  for(int k=0;k<hull_size;k++)
    fprintf(points2, "%g %g\n", hull[k]->x, hull[k]->y);

  fclose(points2);

  exit(0);
}
