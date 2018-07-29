#pragma once
#include "spectrum.h"
#include <stdio.h>
#include <strings.h>
#include <cairo.h>


/* might be useful at some point?
// line plane intersection with fixed intersection at y = 0, for finding the focal length and sensor shift
inline float line_plane_y0_intersection(float ray_origin_x, float ray_origin_y, float ray_origin_z, float ray_direction_x, float ray_direction_y, float ray_direction_z){
    float ray_origin[3] = {ray_origin_x, ray_origin_y, ray_origin_z};
    float ray_direction[3] = {ray_direction_x, ray_direction_y, ray_direction_z};

    float coord[3] = {100.0, 0.0, 100.0};
    float plane_normal[3] = {0.0, 1.0, 0.0};
    raytrace_normalise(ray_direction);
    raytrace_normalise(coord);

    float dot_coord_plane_normal = raytrace_dot(coord, plane_normal);
    float dot_plane_normal_ray_origin = raytrace_dot(plane_normal, ray_origin);
    float dot_plane_normal_ray_direction = raytrace_dot(plane_normal, ray_direction);
    return ray_origin[2] + (ray_direction[2] * (dot_coord_plane_normal - dot_plane_normal_ray_origin) / dot_plane_normal_ray_direction);
}
*/

/*
// line line intersection for finding the principle plane
// in 2d yz space, because ray is shot from x=0 into x=0 direction
Eigen::Vector2d lineLineIntersection(Eigen::Vector3d line1_origin, Eigen::Vector3d line1_direction, Eigen::Vector3d line2_origin, Eigen::Vector3d line2_direction){
    float A1 = line1_direction(1) - line1_origin(1);
    float B1 = line1_origin(2) - line1_direction(2);
    float C1 = A1 * line1_origin(2) + B1 * line1_origin(1);
    float A2 = line2_direction(1) - line2_origin(1);
    float B2 = line2_origin(2) - line2_direction(2);
    float C2 = A2 * line2_origin(2) + B2 * line2_origin(1);
    float delta = A1 * B2 - A2 * B1;
    Eigen::Vector2d rv((B2 * C1 - B1 * C2) / delta, (A1 * C2 - A2 * C1) / delta);
    return rv;
}

// line plane intersection with fixed intersection at y = 0
Eigen::Vector3d linePlaneIntersection(Eigen::Vector3d rayOrigin, Eigen::Vector3d rayDirection) {
    Eigen::Vector3d coord(100.0, 0.0, 100.0);
    Eigen::Vector3d planeNormal(0.0, 1.0, 0.0);
    rayDirection.normalize();
    coord.normalize();
    return rayOrigin + (rayDirection * (coord.dot(planeNormal) - planeNormal.dot(rayOrigin)) / planeNormal.dot(rayDirection));
}

// after last lens element:
Eigen::Vector3d pp_line1start(0.0, rayOriginHeight, 0.0);
Eigen::Vector3d pp_line1end(0.0, rayOriginHeight, 999999.0);
Eigen::Vector3d pp_line2end(0.0, ray_origin.y + (ray_direction.y * 10000.0), ray_origin.z + (ray_direction.z * 10000.0));

float principlePlaneDistance = lineLineIntersection(pp_line1start, pp_line1end, ray_origin, pp_line2end).x;
float focalPointDistance = linePlaneIntersection(ray_origin, ray_direction).z;
float tracedFocalLength = focalPointDistance - principlePlaneDistance;

*/

// need to put the focal length testing code into evaluate_draw? need to do it outside of the loop where all rays are calculated


// evalute sensor to outer pupil:
static inline int evaluate_draw(const lens_element_t *lenses, const int lenses_cnt, const float zoom, const float *in, float *out, cairo_t *cr, float scale, int dim_up, int draw_aspherical)
{
  int error = 0;
  float n1 = spectrum_eta_from_abbe_um(lenses[lenses_cnt-1].ior, lenses[lenses_cnt-1].vno, in[4]);
  float pos[3], dir[3];
  float intensity = 1.0f;

  planeToCs(in, in + 2, pos, dir, 0);

  cairo_set_source_rgba(cr, 0.5, 0.2, 0.2, 0.1);
  cairo_move_to(cr, pos[2], pos[dim_up]);

  float distsum = 0;

  for(int k=lenses_cnt-1;k>=0;k--)
  {
    // propagate the ray reverse to the plane of intersection optical axis/lens element:
    const float R = -lenses[k].lens_radius; // negative, evaluate() is the adjoint case
    float t = 0.0f;
    const float dist = lens_get_thickness(lenses+k, zoom);
    distsum += dist;

    //normal at intersection
    float n[3];
    
    if(lenses[k].anamorphic)
      error |= cylindrical(pos, dir, &t, R, distsum + R, lenses[k].housing_radius, n, lenses[k].cylinder_axis_y);
    
    else if(draw_aspherical)
      error |= aspherical(pos, dir, &t, R, distsum + R, lenses[k].aspheric, lenses[k].aspheric_correction_coefficients, lenses[k].housing_radius, n);
    else
      error |= spherical(pos, dir, &t, R, distsum + R, lenses[k].housing_radius, n);

    // index of refraction and ratio current/next:
    const float n2 = k ? spectrum_eta_from_abbe_um(lenses[k-1].ior, lenses[k-1].vno, in[4]) : 1.0f; // outside the lens there is vacuum

    cairo_line_to(cr, pos[2], pos[dim_up]);

    intensity *= refract(n1, n2, n, dir);
    if(intensity < INTENSITY_EPS) error |= 8;

    if(error)
    {
      cairo_save(cr);
      cairo_scale(cr, 1/scale, 1/scale);
      cairo_set_line_width(cr, 1.0f/20.0f);

      cairo_new_path(cr);
      cairo_restore(cr);
      return error;
    }

    raytrace_normalise(dir);

    n1 = n2;
  }
  // return [x,y,dx,dy,lambda]
  csToSphere(pos, dir, out, out + 2, distsum-fabs(lenses[0].lens_radius), lenses[0].lens_radius);
  out[4] = intensity;

  cairo_line_to(cr, pos[2] + dir[2]*100.0, pos[dim_up] + dir[dim_up]*100.0);
  cairo_save(cr);
  cairo_scale(cr, 1/scale, 1/scale);
  cairo_set_line_width(cr, 1.0f/20.0f);
  cairo_stroke(cr);
  cairo_restore(cr);

  return error;
}

// evaluate scene to sensor:
static inline int evaluate_reverse_draw(const lens_element_t *lenses, const int lenses_cnt, const float zoom, const float *in, float *out, cairo_t *cr, float scale, int dim_up, int draw_aspherical)
{
  int error = 0;
  float n1 = 1.0f;
  float pos[3] = {0.0f}, dir[3] = {0.0f};
  float intensity = 1.0f;

  float lens_length = 0;
  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses+i, zoom);

  sphereToCs(in, in + 2, pos, dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);

  // sphere param only knows about directions facing /away/ from outer pupil, so
  // need to flip this if we're tracing into the lens towards the sensor:
  for(int i = 0; i < 3; i++) dir[i] = -dir[i];

  cairo_move_to(cr, pos[2]-100.0*dir[2], pos[dim_up] - 100.0*dir[dim_up]); 
  cairo_line_to(cr, pos[2], pos[dim_up]);

  float distsum = lens_length;

  for(int k=0;k<lenses_cnt;k++)
  {
    const float R = lenses[k].lens_radius;
    float t = 0.0f;
    const float dist = lens_get_thickness(lenses+k, zoom);

    //normal at intersection
    float n[3] = {0.0f};
    
    if(lenses[k].anamorphic)
      error |= cylindrical(pos, dir, &t, R, distsum - R, lenses[k].housing_radius, n, lenses[k].cylinder_axis_y);
    
    else if(draw_aspherical)
      error |= aspherical(pos, dir, &t, R, distsum - R, lenses[k].aspheric, lenses[k].aspheric_correction_coefficients, lenses[k].housing_radius, n);
    else
      error |= spherical(pos, dir, &t, R, distsum - R, lenses[k].housing_radius, n);

    if(n[2] < 0.0) error |= 16;

    cairo_line_to(cr, pos[2], pos[dim_up]);

    // index of refraction and ratio current/next:
    const float n2 = spectrum_eta_from_abbe_um(lenses[k].ior, lenses[k].vno, in[4]);
    intensity *= refract(n1, n2, n, dir);
    if(intensity < INTENSITY_EPS) error |= 8;

    if(error)
    {
      cairo_save(cr);
      cairo_scale(cr, 1/scale, 1/scale);
      cairo_set_line_width(cr, 1.0f/20.0f);
      cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 0.05);
      // cairo_stroke(cr);
      cairo_new_path(cr);
      cairo_restore(cr);
      return error;
    }

    // and renormalise:
    raytrace_normalise(dir);

    distsum -= dist;
    n1 = n2;
  }
  

  cairo_line_to(cr, pos[2], pos[dim_up]);
  cairo_line_to(cr, 0.0f, pos[dim_up] - pos[2]*dir[dim_up]/dir[2]);
  
  // print y=0 intersection
  // printf("pos[dim_up] - pos[2]*dir[dim_up]/dir[2]: %f\n", pos[dim_up] - pos[2]*dir[dim_up]/dir[2]);
  
  cairo_save(cr);
  cairo_scale(cr, 1/scale, 1/scale);

  if(error) cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 0.05);
  else      cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 3.0f * intensity);
  cairo_stroke(cr);
  cairo_restore(cr);

  // return [x,y,dx,dy,lambda]
  csToPlane(pos, dir, out, out + 2, 0.0f);//0.0==distsum);

  out[4] = intensity;
  
  return error;
}
