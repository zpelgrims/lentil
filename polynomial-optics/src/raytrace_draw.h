#pragma once
#include "spectrum.h"
#include <stdio.h>
#include <strings.h>
#include <cairo.h>
#include <vector>

// evalute sensor to outer pupil:
static inline int evaluate_draw(const std::vector<lens_element_t> lenses, 
                                const int lenses_cnt, 
                                const float zoom, 
                                const Eigen::VectorXf in, 
                                Eigen::VectorXf &out, 
                                cairo_t *cr, 
                                float scale, 
                                const int dim_up, 
                                const int draw_aspherical,
                                Eigen::Vector3f &pos_out,
                                Eigen::Vector3f &dir_out)
{
  int error = 0;
  float n1 = spectrum_eta_from_abbe_um(lenses[lenses_cnt-1].ior, lenses[lenses_cnt-1].vno, in(4));
  Eigen::Vector3f pos(0,0,0);
  Eigen::Vector3f dir(0,0,0);
  float intensity = 1.0f;

  planeToCs(Eigen::Vector2f(in(0), in(1)), Eigen::Vector2f(in(2), in(3)), pos, dir, 0);

  cairo_set_source_rgba(cr, 1.0, 1.0, 0.2, 0.7);
  cairo_move_to(cr, pos(2), pos(dim_up));

  float distsum = 0;

  for(int k=lenses_cnt-1;k>=0;k--)
  {
    // propagate the ray reverse to the plane of intersection optical axis/lens element:
    const float R = -lenses[k].lens_radius; // negative, evaluate() is the adjoint case
    float t = 0.0f;
    distsum += lens_get_thickness(lenses[k], zoom);
    
    Eigen::Vector3f normal(0,0,0);
    error |= intersect(lenses, k, pos, dir, t, normal, R, distsum, true);

    // index of refraction and ratio current/next:
    const float n2 = k ? spectrum_eta_from_abbe_um(lenses[k-1].ior, lenses[k-1].vno, in(4)) : 1.0f; // outside the lens there is vacuum

    cairo_line_to(cr, pos(2), pos(dim_up));

    intensity *= refract(n1, n2, normal, dir);
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

  Eigen::Vector2f outpos(0,0);
  Eigen::Vector2f outdir(0,0);
  
  // return [x,y,dx,dy,lambda]
  if (stringcmp(lenses[0].geometry, "cyl-y")) csToCylinder(pos, dir, outpos, outdir, distsum-std::abs(lenses[0].lens_radius), lenses[0].lens_radius, true);
  else if (stringcmp(lenses[0].geometry, "cyl-x")) csToCylinder(pos, dir, outpos, outdir, distsum-std::abs(lenses[0].lens_radius), lenses[0].lens_radius, false);
  else csToSphere(pos, dir, outpos, outdir, distsum-std::abs(lenses[0].lens_radius), lenses[0].lens_radius);

  out(0) = outpos(0);
  out(1) = outpos(1);
  out(2) = outdir(0);
  out(3) = outdir(1);
  out(4) = intensity;


  cairo_line_to(cr, pos(2) + dir(2)*1000.0, pos(dim_up) + dir(dim_up)*1000.0);
  cairo_save(cr);
  cairo_scale(cr, 1/scale, 1/scale);
  cairo_set_line_width(cr, 1.0f/20.0f);
  cairo_stroke(cr);
  cairo_restore(cr);

  pos_out(0) = pos(0);
  pos_out(1) = pos(1);
  pos_out(2) = pos(2);
  dir_out(0) = dir(0);
  dir_out(1) = dir(1);
  dir_out(2) = dir(2);
  return error;
}

// evaluate scene to sensor:
static inline int evaluate_reverse_draw(const std::vector<lens_element_t> lenses, const int lenses_cnt, const float zoom, const Eigen::VectorXf in, Eigen::VectorXf &out, cairo_t *cr, const float scale, const int dim_up, const int draw_aspherical)
{
  int error = 0;
  float n1 = 1.0f;
  Eigen::Vector3f pos(0,0,0);
  Eigen::Vector3f dir(0,0,0);
  float intensity = 1.0f;

  float lens_length = 0;
  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses[i], zoom);

  const Eigen::Vector2f inpos(in(0), in(1));
  const Eigen::Vector2f indir(in(2), in(3));
  if (stringcmp(lenses[0].geometry, "cyl-y")) cylinderToCs(inpos, indir, pos, dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
  else if (stringcmp(lenses[0].geometry, "cyl-x")) cylinderToCs(inpos, indir, pos, dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
  else sphereToCs(inpos, indir, pos, dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);

  // sphere param only knows about directions facing /away/ from outer pupil, so
  // need to flip this if we're tracing into the lens towards the sensor:
  for(int i = 0; i < 3; i++) dir(i) = -dir(i);

  cairo_move_to(cr, pos(2)-9999.0*dir(2), pos(dim_up) - 9999.0*dir(dim_up)); 
  cairo_line_to(cr, pos(2), pos(dim_up));

  float distsum = lens_length;

  for(int k=0;k<lenses_cnt;k++)
  {
    const float R = lenses[k].lens_radius;
    float t = 0.0f;
    const float dist = lens_get_thickness(lenses[k], zoom);

    //normal at intersection
    Eigen::Vector3f n(0,0,0);
    error |= intersect(lenses, k, pos, dir, t, n, R, distsum, false);

    if(n[2] < 0.0) error |= 16;

    cairo_line_to(cr, pos(2), pos(dim_up));
    
    // index of refraction and ratio current/next:
    const float n2 = spectrum_eta_from_abbe_um(lenses[k].ior, lenses[k].vno, in(4));
    intensity *= refract(n1, n2, n, dir);
    if(intensity < INTENSITY_EPS) error |= 8;

    if(error) { // uncomment to draw vignetted rays
      // cairo_save(cr);
      // cairo_scale(cr, 1/scale, 1/scale);
      // cairo_set_line_width(cr, 1.0f/20.0f);
      // cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 0.15);
      // cairo_stroke(cr);
      cairo_new_path(cr);
      // cairo_restore(cr);
      return error;
    }

    // and renormalise:
    raytrace_normalise(dir);

    distsum -= dist;
    n1 = n2;
  }
  

  cairo_line_to(cr, pos(2), pos(dim_up));
  cairo_line_to(cr, 0.0f, pos(dim_up) - pos(2)*dir(dim_up)/dir(2));
  
  cairo_save(cr);
  cairo_scale(cr, 1/scale, 1/scale);

  if(error) cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 0.05);
  else      cairo_set_source_rgba(cr, 0.6, 0.6, 0.6, 3.0f * intensity);
  cairo_stroke(cr);
  cairo_restore(cr);

  // return [x,y,dx,dy,lambda]
  Eigen::Vector2f outpos(0,0);
  Eigen::Vector2f outdir(0,0);
  csToPlane(pos, dir, outpos, outdir, 0.0f);//0.0==distsum);
  out(0) = outpos(0);
  out(1) = outpos(1);
  out(2) = outdir(0);
  out(3) = outdir(1);
  out(4) = intensity;
  
  return error;
}
