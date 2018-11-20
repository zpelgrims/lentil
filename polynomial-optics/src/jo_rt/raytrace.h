#pragma once
#include "spectrum.h"
#include "pathspace.h"
#include "matrix2.h"
#include "lenssystem.h"
#include <stdio.h>
#include <strings.h>

#define INTENSITY_EPS 1e-5

// map tangent space delta at end of chain (last vertex v[n] in array, in respective tangent space uv)
// to world space at given vertex (v[v], v < n, delta, 3d)
static inline void lensmf_map(const vertex_t *vtx, float u, float v, float *delta)
{
  const float Tx = vtx->diffgeo.Tp[0] * u + vtx->diffgeo.Tp[1] * v;
  const float Ty = vtx->diffgeo.Tp[2] * u + vtx->diffgeo.Tp[3] * v;
  for(int k=0;k<3;k++)
    delta[k] = Tx * vtx->diffgeo.dpdu[k] + Ty * vtx->diffgeo.dpdv[k];
}

// TODO: put into raytrace.h? and also do this for asphericals/cylindrical/prisms?
// initialize some essential variables in the diffgeo struct on each vertex.
// don't actually compute the tangent space mappings yet.
static inline void lensmf_sphere_init(path_t *p, int v, const float *n, const float radius, int anam)
{
  // compute dndu dndv for every vertex, depends on uv coordinates to be useful
  p->v[v].diffgeo.dpdu[0] = -p->v[v].hit.x[1] * 2*M_PI;
  p->v[v].diffgeo.dpdu[1] =  p->v[v].hit.x[0] * 2*M_PI;
  p->v[v].diffgeo.dpdu[2] =  0.0f;
  const float zrad = p->v[v].hit.x[0]*p->v[v].hit.x[0] +  p->v[v].hit.x[1]*p->v[v].hit.x[1];
  const float cos_theta = p->v[v].hit.x[2]/radius;
  const float sin_theta = sqrtf(MAX(0.0f, 1.0f-cos_theta*cos_theta));
  float cos_phi, sin_phi;
  if(zrad > 0.0f)
  {
    cos_phi = p->v[v].hit.x[0] / zrad;
    sin_phi = p->v[v].hit.x[1] / zrad;
  }
  else
  {
    cos_phi = 0.0f;
    sin_phi = 1.0f;
  }
  p->v[v].diffgeo.dpdv[0] = p->v[v].hit.x[2] * cos_phi * M_PI;
  p->v[v].diffgeo.dpdv[1] = p->v[v].hit.x[2] * sin_phi * M_PI;
  p->v[v].diffgeo.dpdv[2] = -sin_theta * radius * M_PI;

  for(int k=0;k<3;k++)
  {
    p->v[v].diffgeo.dndu[k] = p->v[v].diffgeo.dpdu[k] / radius;
    p->v[v].diffgeo.dndv[k] = p->v[v].diffgeo.dpdv[k] / radius;
  }
  if(anam)
  {
    p->v[v].diffgeo.dpdv[0] = 0.0f;
    p->v[v].diffgeo.dpdv[1] = 1.0f;
    p->v[v].diffgeo.dpdv[2] = 0.0f;
  }

  // ortho normalise, stick to dpdu as direction:
  const float ilu = 1.0f/sqrtf(dotproduct(p->v[v].diffgeo.dpdu, p->v[v].diffgeo.dpdu));
  for(int k=0;k<3;k++) p->v[v].diffgeo.dpdu[k] *= ilu;
  for(int k=0;k<3;k++) p->v[v].diffgeo.dndu[k] *= ilu;
  const float dot = dotproduct(p->v[v].diffgeo.dpdu, p->v[v].diffgeo.dpdv);
  for(int k=0;k<3;k++) p->v[v].diffgeo.dpdv[k] -= dot*p->v[v].diffgeo.dpdu[k];
  for(int k=0;k<3;k++) p->v[v].diffgeo.dndv[k] -= dot*p->v[v].diffgeo.dndu[k];
  const float ilv = 1.0f/sqrtf(dotproduct(p->v[v].diffgeo.dpdv, p->v[v].diffgeo.dpdv));
  for(int k=0;k<3;k++) p->v[v].diffgeo.dpdv[k] *= ilv;
  for(int k=0;k<3;k++) p->v[v].diffgeo.dndv[k] *= ilv;

  // shading frame is also rotated to match dpdu:
  memcpy(p->v[v].hit.a, p->v[v].diffgeo.dpdu, sizeof(float)*3);
  memcpy(p->v[v].hit.b, p->v[v].diffgeo.dpdv, sizeof(float)*3);
  normalise(p->v[v].hit.a);
  normalise(p->v[v].hit.b);
}

// same as wenzel's code in mitsuba.
// initialize tangent space derivatives and invert matrix, so we can
// map tangent space vertex relocations through the specular chain (fixed halfvectors)
// start: diffuse vertex before the spec chain
// end: diffuse vertex at end of spec chain
static inline float lensmf_compute_derivatives(path_t *p, int start, int end)
{
  assert(start >= 0);
  assert(end <= p->length-1);
  const int n = end;

  mat2_set_zero(p->v[0].diffgeo.Tp);     // does not move at all
  mat2_set_identity(p->v[n].diffgeo.Tp); // moves freely along its own tangent space

  if(end-start == 1) return 1.0f; // all good.

  // assemble matrices a, b, c (how does vertex i depend on i-1, i, and i+1)
  for(int i=start;i<end;i++)
  {
    // fprintf(stderr, "mf create %d/%d\n", i, n);
    vertex_manifold_t *mf = &p->v[i].diffgeo;
    float wo[3]; // pointing from vert i to i+1
    for(int k=0;k<3;k++) wo[k] = p->v[i+1].hit.x[k] - p->v[i].hit.x[k];
    float ilo = sqrtf(dotproduct(wo, wo));
    if(ilo == 0.0f) return 0.0f;
    ilo = 1.0/ilo;
    for(int k=0;k<3;k++) wo[k] *= ilo;

    if(mf->type == s_pinned_position)
    {
      mat2_set_zero(mf->a);
      mat2_set_identity(mf->b);
      mat2_set_zero(mf->c);
      continue;
    }
    else if(mf->type == s_pinned_direction)
    {
      float dC_dnext_u[3], dC_dnext_v[3], dC_dcurr_u[3], dC_dcurr_v[3];
      const float dot_wo_v0dpdu = dotproduct(wo, p->v[i].diffgeo.dpdu);
      const float dot_wo_v0dpdv = dotproduct(wo, p->v[i].diffgeo.dpdv);
      const float dot_wo_v1dpdu = dotproduct(wo, p->v[i+1].diffgeo.dpdu);
      const float dot_wo_v1dpdv = dotproduct(wo, p->v[i+1].diffgeo.dpdv);
      for(int k=0;k<3;k++)
      {
        dC_dnext_u[k] = (p->v[i+1].diffgeo.dpdu[k] - wo[k] * dot_wo_v1dpdu) * ilo;
        dC_dnext_v[k] = (p->v[i+1].diffgeo.dpdv[k] - wo[k] * dot_wo_v1dpdv) * ilo;
        dC_dcurr_u[k] = (wo[k] * dot_wo_v0dpdu - p->v[i].diffgeo.dpdu[k]) * ilo;
        dC_dcurr_v[k] = (wo[k] * dot_wo_v0dpdv - p->v[i].diffgeo.dpdv[k]) * ilo;
      }

      mat2_set_zero(mf->a);
      mf->b[0] = dotproduct(dC_dcurr_u, p->v[0].diffgeo.dpdu);
      mf->b[1] = dotproduct(dC_dcurr_v, p->v[0].diffgeo.dpdu);
      mf->b[2] = dotproduct(dC_dcurr_u, p->v[0].diffgeo.dpdv);
      mf->b[3] = dotproduct(dC_dcurr_v, p->v[0].diffgeo.dpdv);

      mf->c[0] = dotproduct(dC_dnext_u, p->v[0].diffgeo.dpdu);
      mf->c[1] = dotproduct(dC_dnext_v, p->v[0].diffgeo.dpdu);
      mf->c[2] = dotproduct(dC_dnext_u, p->v[0].diffgeo.dpdv);
      mf->c[3] = dotproduct(dC_dnext_v, p->v[0].diffgeo.dpdv);
      continue;
    }

    assert(i > start); // first vertex should have been pinned one or the other way above.
    float wi[3]; // pointing from vert i to i-1
    for(int k=0;k<3;k++) wi[k] = p->v[i-1].hit.x[k] - p->v[i].hit.x[k];
    float ili = sqrtf(dotproduct(wi, wi));
    if(ili == 0.0f) return 0.0f;
    ili = 1.0/ili;
    for(int k=0;k<3;k++) wi[k] *= ili;

    assert(p->v[i].mode & s_transmit); // special case here for lenses
    if(p->v[i].mode & (s_reflect | s_transmit)) /* reflection or refraction */
    {
      // ratio n1/n2 where n2 is inside the shape
      const float eta = (p->v[i].mode & s_reflect) ? 1.0f :
        (p->e[i+1].vol.ior / p->e[i].vol.ior);
      // reflected path also goes through normalise_H, but happens to have eta == 1.
      const int normalise_H = !((p->v[i].mode & s_transmit) && (eta == 1.0f));

      float ilh, H[3];
      if(normalise_H)
      {
        for(int k=0;k<3;k++) H[k] = wi[k] + eta * wo[k];
        ilh = 1.0f/sqrtf(dotproduct(H, H));
        for(int k=0;k<3;k++) H[k] *= ilh;
      }
      else
      {
        // don't normalise H for index-matched transmission
        for(int k=0;k<3;k++) H[k] = wi[k] + wo[k];
        ilh = 1.0f;
      }

      float dot_H_n    = dotproduct(p->v[i].hit.n, H);
      float dot_H_dndu = dotproduct(mf->dndu, H);
      float dot_H_dndv = dotproduct(mf->dndv, H);
      float dot_dpdu_n = dotproduct(mf->dpdu, p->v[i].hit.n);
      float dot_dpdv_n = dotproduct(mf->dpdv, p->v[i].hit.n);

      // tangent frame around shading normal:
      float *s = p->v[i].hit.a, *t = p->v[i].hit.b;

      ilo *= eta * ilh; ili *= ilh;

      // derivatives of C wrt previous vertex v[i-1]
      float dH_du[3], dH_dv[3];
      const float dot_wi_dpdu = dotproduct(wi, p->v[i-1].diffgeo.dpdu);
      const float dot_wi_dpdv = dotproduct(wi, p->v[i-1].diffgeo.dpdv);
      for(int k=0;k<3;k++) dH_du[k] = (p->v[i-1].diffgeo.dpdu[k] - wi[k] * dot_wi_dpdu) * ili;
      for(int k=0;k<3;k++) dH_dv[k] = (p->v[i-1].diffgeo.dpdv[k] - wi[k] * dot_wi_dpdv) * ili;

      if(normalise_H)
      {
        const float dotu = dotproduct(dH_du, H);
        const float dotv = dotproduct(dH_dv, H);
        for(int k=0;k<3;k++)
        {
          dH_du[k] -= H[k] * dotu;
          dH_dv[k] -= H[k] * dotv;
        }
      }

      mf->a[0] = dotproduct(dH_du, s);
      mf->a[1] = dotproduct(dH_dv, s);
      mf->a[2] = dotproduct(dH_du, t);
      mf->a[3] = dotproduct(dH_dv, t);

      // derivatives of C wrt current vertex v[i]
      for(int k=0;k<3;k++)
      {
        dH_du[k] = -p->v[i].diffgeo.dpdu[k] * (ili + ilo) + wi[k] * dotproduct(wi, p->v[i].diffgeo.dpdu) * ili
                                                          + wo[k] * dotproduct(wo, p->v[i].diffgeo.dpdu) * ilo;
        dH_dv[k] = -p->v[i].diffgeo.dpdv[k] * (ili + ilo) + wi[k] * dotproduct(wi, p->v[i].diffgeo.dpdv) * ili
                                                          + wo[k] * dotproduct(wo, p->v[i].diffgeo.dpdv) * ilo;
      }
      if(normalise_H)
      {
        const float dotu = dotproduct(dH_du, H);
        const float dotv = dotproduct(dH_dv, H);
        for(int k=0;k<3;k++)
        {
          dH_du[k] -= H[k] * dotu;
          dH_dv[k] -= H[k] * dotv;
        }
      }

      mf->b[0] = dotproduct(dH_du, s) - dotproduct(mf->dpdu, mf->dndu) * dot_H_n - dot_dpdu_n * dot_H_dndu;
      mf->b[1] = dotproduct(dH_dv, s) - dotproduct(mf->dpdu, mf->dndv) * dot_H_n - dot_dpdu_n * dot_H_dndv;
      mf->b[2] = dotproduct(dH_du, t) - dotproduct(mf->dpdv, mf->dndu) * dot_H_n - dot_dpdv_n * dot_H_dndu;
      mf->b[3] = dotproduct(dH_dv, t) - dotproduct(mf->dpdv, mf->dndv) * dot_H_n - dot_dpdv_n * dot_H_dndv;

      // derivatives of C wrt v[i+1]
      for(int k=0;k<3;k++)
      {
        dH_du[k] = (p->v[i+1].diffgeo.dpdu[k] - wo[k] * dotproduct(wo, p->v[i+1].diffgeo.dpdu)) * ilo;
        dH_dv[k] = (p->v[i+1].diffgeo.dpdv[k] - wo[k] * dotproduct(wo, p->v[i+1].diffgeo.dpdv)) * ilo;
      }

      if(normalise_H)
      {
        const float dotu = dotproduct(dH_du, H);
        const float dotv = dotproduct(dH_dv, H);
        for(int k=0;k<3;k++)
        {
          dH_du[k] -= H[k] * dotu;
          dH_dv[k] -= H[k] * dotv;
        }
      }

      mf->c[0] = dotproduct(dH_du, s);
      mf->c[1] = dotproduct(dH_dv, s);
      mf->c[2] = dotproduct(dH_du, t);
      mf->c[3] = dotproduct(dH_dv, t);

      // store microfacet normal
      mf->h[0] = dotproduct(H, s);
      mf->h[1] = dotproduct(H, t);
      mf->h[2] = dotproduct(H, p->v[i].hit.n);
      // XXX, orient into same hemisphere as geo normal:
      // if(dotproduct(H, p->v[i].hit.gn) < 0.0f)
        // for(int k=0;k<3;k++) mf->h[k] = - mf->h[k];
      // fprintf(stderr, "[%d] H = %f %f %f h = %f %f %f\n", i, H[0], H[1], H[2], mf->h[0], mf->h[1], mf->h[2]);
    }
  }

  // block tridiagonal LU factorization to create transport matrices Tp
  // mapping a change at vertex v[n] to each vertex v[n-1]..v[0]. v[n].Tp = identity.
  //
  // note: could do it backwards, to map changes at v[0] to v[1]..v[n-1], by
  // inverting the loop direction and swapping a (depend on prev) and c (depend on next).
  //
  // we use Salkuyeh's way to compute the overall determinant on the way.
  // (Comments on ``A note on a three-term recurrence for a tridiagonal matrix'')
  // det M = \Prod_{k=1}^n det\Lambda_k
  // \Lambda_k = b_k - a_k \Lambda^{-1}_{k-1} c_{k-1},   \Lambda_1 = b_1
  float det = 1.0f;
  float Li[4];
  float u[PATHSPACE_MAX_VERTS][4] = {{0}};
  det *= mat2_invert(p->v[start].diffgeo.b, Li);
  if(det == 0.0f)
  {
    fprintf(stderr, "[lens mf] inv fail\n");
    path_print_manifold_matrix(p, stderr);
    return 0.0f;
  }
  for(int i=start;i<end-1;i++)
  {
    mat2_mul(Li, p->v[i].diffgeo.c, u[i]);
    float au[4], b_au[4]; // b - a*u
    mat2_mul(p->v[i+1].diffgeo.a, u[i], au);
    mat2_sub(p->v[i+1].diffgeo.b, au, b_au);
    det *= mat2_invert(b_au, Li);
    if(det == 0.0f)
    {
      fprintf(stderr, "[lens mf] inv %d fail\n", i);
      fprintf(stderr, "b-au = [ %g %g  %g %g ]\n", b_au[0], b_au[1], b_au[2], b_au[3]);
      fprintf(stderr, "det = %g\n", mat2_det(b_au));
      path_print_manifold_matrix(p, stderr);
      return 0.0f;
    }
  }
  mat2_mul(Li, p->v[end-1].diffgeo.c, p->v[end-1].diffgeo.Tp);
  for(int k=0;k<4;k++) p->v[end-1].diffgeo.Tp[k] = -p->v[end-1].diffgeo.Tp[k];
  for(int i=end-2;i>=start;i--)
  {
    mat2_mul(u[i], p->v[i+1].diffgeo.Tp, p->v[i].diffgeo.Tp);
    for(int k=0;k<4;k++) p->v[i].diffgeo.Tp[k] = -p->v[i].diffgeo.Tp[k];
  }
  // fprintf(stderr, "[lens mf] det %g\n", det);
  return det;
}

static inline int spherical(
    float *pos, const float *dir,
    float R, float center, float housing_rad, float *normal)
{
  const float scv[3] = {pos[0], pos[1], pos[2] - center};
  const float a = dotproduct(dir, dir);
  const float b = 2 * dotproduct(dir, scv);
  const float c = dotproduct(scv, scv) - R*R;
  const float discr = b*b-4*a*c;
  if(discr < 0.0f) return 4;
  int error = 0;
  float t = 0.0f;
  const float t0 = (-b-sqrtf(discr))/(2*a);
  const float t1 = (-b+sqrtf(discr))/(2*a);
  if(t0 < -1e-4f) t = t1;
  else t = fminf(t0, t1);
  if(t < -1e-4f) return 16;

  for(int i=0;i<3;i++) pos[i] += dir[i] * t;
  error |= (int)(pos[0]*pos[0] + pos[1]*pos[1] > housing_rad*housing_rad)<<4;

  normal[0] = pos[0]/R;
  normal[1] = pos[1]/R;
  normal[2] = (pos[2] - center)/R;

  return error;
}

static inline float evaluate_aspherical(
    const float *pos, const float R, const int k, const float *correction)
{
  float h = sqrtf(pos[0]*pos[0]+pos[1]*pos[1]);
  float hr = h / R;
  float h2 = h*h;
  float h4 = h2*h2;
  float h6 = h4*h2;
  float h8 = h4*h4;
  float h10 = h8*h2;
  float z = h*hr/(1+sqrtf(MAX(0.0,1-(1+k)*hr*hr)))+correction[0]*h4+correction[1]*h6+correction[2]*h8+correction[3]*h10;
  return z;
}

static inline float evaluate_aspherical_derivative(const float *pos, const float R, const int k, const float *correction)
{
  float h = sqrtf(pos[0]*pos[0]+pos[1]*pos[1]);
  float hr = h / R;
  float h2 = h*h;
  float h3 = h2*h;
  float h5 = h3*h2;
  float h7 = h5*h2;
  float h9 = h7*h2;
  float z = 2*hr/(1+sqrtf(MAX(0.0,1-(1+k)*hr*hr)))+
    hr*hr*hr*(k+1)/(sqrtf(MAX(0.0,1-(1+k)*hr*hr))*powf(sqrtf(MAX(0.0,1-(1+k)*hr*hr))+1, 2))+
    4*correction[0]*h3+6*correction[1]*h5+8*correction[2]*h7+10*correction[3]*h9;
  return z;
}

static inline int aspherical(
    float *pos, const float *dir,
    const float R, const float center, const int k,
    const float *correction, const float housing_rad, float *normal)
{
  //first intersect sphere, then do correction iteratively
  int error = spherical(pos, dir, R, center, housing_rad, normal);

  float rad = R;
  float corr[4] = {correction[0], correction[1], correction[2], correction[3]};
  if(fabs(center+R-pos[2]) > fabs(center-R-pos[2]))
  {
    rad = -R;
    for(int i = 0; i < 4; i++) corr[i] = -corr[i];
  }

  float position_error = 1e7f;

  for(int i = 0; i < 100; i++)
  {
    position_error = rad+center-pos[2]-evaluate_aspherical(pos, rad, k, correction);
    float tErr = position_error/dir[2];
    for(int i=0;i<3;i++) pos[i] += dir[i] * tErr;
    if(fabsf(position_error) < 1e-4f) break;
  }

  float dz = evaluate_aspherical_derivative(pos, rad, k, correction);
  const float r = sqrt(pos[0]*pos[0]+pos[1]*pos[1]);

  if(normal[2] < 0) dz = -dz;
  normal[0] = pos[0]/r*dz;
  normal[1] = pos[1]/r*dz;
  normal[2] /= fabs(normal[2]);

  normalise(normal);

  return error;
}

static inline int cylindrical(
    float *pos, const float *dir,
    float R, float center, float housing_rad, float *normal)
{
  const float scv[3] = {pos[0], 0, pos[2] - center};
  const float a = dotproduct(dir, dir);
  const float b = 2 * dotproduct(dir, scv);
  const float c = dotproduct(scv, scv) - R*R;
  const float discr = b*b-4*a*c;
  if(discr < 0.0f) return 4;
  int error = 0;
  float t = 0.0f;
  if(R > 0.0f)
    t = (-b-sqrtf(discr))/(2*a);
  else if(R < 0.0f)
    t = (-b+sqrtf(discr))/(2*a);

  for(int i=0;i<3;i++) pos[i] += dir[i] * t;
  error |= (int)(pos[0]*pos[0] + pos[1]*pos[1] > housing_rad*housing_rad)<<4;

  normal[0] = pos[0]/R;
  normal[1] = 0.0f;
  normal[2] = (pos[2] - center)/R;

  return error;
}

static inline float fresnel(const float n1, const float n2, const float cosr, const float cost)
{
  if(cost <= 0.0f) return 1.0f; // total inner reflection
  // fresnel for unpolarized light:
  const float Rs = (n1*cosr - n2*cost)/(n1*cosr + n2*cost);
  const float Rp = (n1*cost - n2*cosr)/(n1*cost + n2*cosr);
  return fminf(1.0f, (Rs*Rs + Rp*Rp)*.5f);
}

static inline float refract(const float n1, const float n2, const float *n, float *dir)
{
  if(n1 == n2)
    return 1;
  const float eta = n1/n2;

  const float norm = sqrtf(dotproduct(dir,dir));
  const float cos1 = - dotproduct(n, dir)/norm;
  const float cos2_2 = 1.0f-eta*eta*(1.0f-cos1*cos1);
  // total (inner) reflection?
  if(cos2_2 < 0.0f)
    return 0;
  const float cos2 = sqrtf(cos2_2);

  for(int i=0;i<3;i++) dir[i] = dir[i]*eta/norm + (eta*cos1-cos2)*n[i];

  return 1.0f-fresnel(n1, n2, cos1, cos2);
}

static inline int intersect_element(
    const lens_element_t *el,  // the lens element in question
    const float R,             // radius to intersect (negative curvature radius for sensor->scene)
    float *pos,                // camera space ray position (will be moved)
    const float *dir,          // direction
    const float dist,          // distance along optical axis from origin to this element
    float *n)                  // output normal[3]
{
  if(el->anamorphic)
    return cylindrical(pos, dir, R, dist + R, el->housing_radius, n);
  else if(el->aspheric)
    return aspherical(pos, dir, R, dist + R, el->aspheric, el->aspheric_correction_coefficients, el->housing_radius, n);
  else
    return spherical(pos, dir, R, dist + R, el->housing_radius, n);
}

// evalute sensor to scene, return fresnel transmittance:
static inline float evaluate(
    const lens_t* lens,
    const float lambda,   // in nm
    const float *in_pos,  // set in_pos[2] = -focus to focus
    const float *in_dir,
    float *pos,
    float *dir,
    const int aperture,
    path_t *path,         // if !=0, will be filled (v[0] on sensor -> v[len-1])
    float *normal)        // pass normal of last element, if != 0
{
  float n1 = spectrum_eta_from_abbe(lens->element[lens->num-1].ior, lens->element[lens->num-1].vno, lambda);
  float transmittance = 1.0f;
  for(int k=0;k<3;k++) pos[k] = in_pos[k];
  for(int k=0;k<3;k++) dir[k] = in_dir[k];
  float distsum = 0;
  if(path)
  {
    path_init(path, 0, 0);
    memset(path->v, 0, sizeof(vertex_t)*lens->num);
    memset(path->e, 0, sizeof(edge_t)*lens->num);
    path->v[0].mode = s_transmit | s_specular;
    path->v[0].hit.x[0] = pos[0];
    path->v[0].hit.x[1] = pos[1];
    path->v[0].hit.x[2] = pos[2];
    path->e[1].omega[0] = dir[0];
    path->e[1].omega[1] = dir[1];
    path->e[1].omega[2] = dir[2];
    path->e[0].vol.ior = n1;
    path->e[1].vol.ior = n1;

    // tangent space init (path_init zeros out the rest):
    path->lambda = lambda;
    path->v[0].hit.a[0] = 1.0f;
    path->v[0].hit.b[1] = 1.0f;
    path->v[0].hit.n[2] = -1.0f;
    path->v[0].diffgeo.dpdu[0] = 1.0f;
    path->v[0].diffgeo.dpdv[1] = 1.0f;
    path->length = 1;
  }

  for(int k=lens->num-1;k>=0;k--)
  {
    // propagate the ray reverse to the plane of intersection optical axis/lens element:
    const float R = -lens->element[k].lens_radius; // negative, evaluate() is the adjoint case
    distsum += lens_get_thickness(lens->element+k, lens->zoom);

    // stop after moving to aperture.
    if(aperture && (k == lens->aperture_element)) break;

    // normal at intersection
    float n[3] = {0.0f};
    if(intersect_element(lens->element+k, R, pos, dir, distsum, n))
    {
      // fprintf(stderr, "did not intersect element %d : %g %g %g -> %g %g %g R %g\n", k,
      //     pos[0], pos[1], pos[2],
      //     dir[0], dir[1], dir[2],
      //     R);
      return 0.0f;
    }

    if(normal && (k == 0))
      for(int i=0;i<3;i++) normal[i] = n[i];

    // index of refraction and ratio current/next:
    const float n2 = k ? spectrum_eta_from_abbe(lens->element[k-1].ior, lens->element[k-1].vno, lambda) : 1.0f; // outside the lens there is vacuum

    transmittance *= refract(n1, n2, n, dir);
    // if(transmittance < INTENSITY_EPS) return 0.0f;
    normalise(dir);
    n1 = n2;
    if(path)
    { // init tangent space
      for(int i=0;i<3;i++) path->v[path->length].hit.x[i] = pos[i];
      // XXX do we need omega? me thinks no:
      for(int i=0;i<3;i++) path->e[path->length+1].omega[i] = dir[i];
      path->e[path->length+1].vol.ior = n2;
      path->v[path->length].mode = s_transmit | s_specular;
      lensmf_sphere_init(path, path->length, n, R, lens->element[k].anamorphic);
      path->length++;
    }
  }

  if(path)
  { // TODO: what's this supposed to do if !aperture?
    // TODO: we'd want to intersect a plane in the scene?
    const int v = path->length;
    // last propagation, intersect with aperture plane at z=distsum
    const float t = (distsum - path->v[v-1].hit.x[2])/path->e[v].omega[2];
    for(int k=0;k<3;k++)
      path->v[v].hit.x[k] = path->v[v-1].hit.x[k] + t * path->e[v].omega[k];

    // tangent space of last vertex
    path->v[v].hit.a[0] = 1.0f;
    path->v[v].hit.b[1] = 1.0f;
    path->v[v].hit.n[2] = -1.0f;
    path->v[v].diffgeo.dpdu[0] = 1.0f;
    path->v[v].diffgeo.dpdv[1] = 1.0f;
    path->length++;
  }
  return transmittance;
}

// evaluate scene to sensor:
static inline float evaluate_reverse(
    const lens_t* lens,
    const float lambda,  // in nm
    float *pos,          // will be overwritten to be pos/dir on sensor or aperture
    float *dir,
    float *opos,         // if != 0 will be pos dir on scene-facing element
    float *odir,
    const int aperture,
    path_t *path,        // if != 0 will be inited starting from v[1] on scene-facing glass
    float *normal)       // if != 0 will be normal of scene-facing element
{
  float n1 = 1.0f;
  float transmittance = 1.0f;
  // ??? do we want this:
  // for(int i = 0; i < 2; i++) dir[i] = -dir[i];
  float dist = 0;
  float distsum = 0;

  for(int k=0;k<lens->num;k++)
  {
    const float R = lens->element[k].lens_radius;
    dist = lens_get_thickness(lens->element+k, lens->zoom);

    // normal at intersection
    float n[3] = {0.0};
    if(intersect_element(lens->element+k, R, pos, dir, distsum, n))
      return 0.0f;
    if(k==0 && opos)   for(int i=0;i<3;i++) opos[i] = pos[i];
    if(k==0 && opos)   for(int i=0;i<3;i++) odir[i] = dir[i];
    if(k==0 && normal) for(int i=0;i<3;i++) normal[i] = n[i];

    // index of refraction and ratio current/next:
    const float n2 = spectrum_eta_from_abbe(lens->element[k].ior, lens->element[k].vno, lambda);
    transmittance *= refract(n1, n2, n, dir);
    if(transmittance < INTENSITY_EPS) return 0.0f;

    // and renormalise:
    normalise(dir);

    if(path)
    {
      const int v = path->length;
      for(int i=0;i<3;i++) path->v[v].hit.x[i] = pos[i];
      // XXX do we need omega? me thinks no:
      for(int i=0;i<3;i++) path->e[v+1].omega[i] = dir[i];
      path->e[v+1].vol.ior = n2;
      path->v[v].mode = s_transmit | s_specular;
      lensmf_sphere_init(path, path->length, n, R, lens->element[k].anamorphic);
      path->length++;
    }

    distsum += dist;

    // stop after processing aperture but before moving to next element
    if(aperture && (k == lens->aperture_element))
      return transmittance;

    n1 = n2;
  }
  // need to move thickness of last element up to sensor
  for(int i=0;i<3;i++) pos[i] += dist * dir[i];
  return transmittance;
}

static inline float lensmf_iterate_sensor(
    const lens_t *lens,
    const float lambda,
    const float *spos,
    float *sdir,
    float *apos,
    float *jacobian)
{
  float pos[3], dir[3], delta[3];
  // XXX ouch this only works if global path length
  // XXX is greater than number of lens elements!
  path_t path;
  const float transmittance = evaluate(
      lens, lambda, spos, sdir, pos, dir, 1, &path, 0);

  if(path.length < 2) return 0.0f;

  // path_print(&path, stdout);
  path.v[0].diffgeo.type = s_pinned_position;
  if(lensmf_compute_derivatives(&path, 0, path.length-1) == 0.0f) return 0.0f;
  // map change of aperture position to change in v[1] (optical element closest to sensor)
  lensmf_map(path.v + 1,
      apos[0] - path.v[path.length-1].hit.x[0],
      apos[1] - path.v[path.length-1].hit.x[1],
      delta);

  *jacobian = fabsf(mat2_det(path.v[1].diffgeo.Tp));

  for(int k=0;k<3;k++)
    sdir[k] = path.v[1].hit.x[k] + delta[k] - path.v[0].hit.x[k];
  normalise(sdir);

  // also return aperture position for error estimation:
  for(int k=0;k<3;k++)
    apos[k] = path.v[path.length-1].hit.x[k];
  return transmittance;
}

static inline float lensmf_iterate_scene(
    const lens_t *lens,
    const float lambda,  // wavelength nm
    const float *scene,  // 3d point in scene
    float *opos,         // storage for opos (can be uninited)
    float *odir,         // inited direction from scene -> lens
    float *apos)         // 3d aperture position, will only read 2d
{
  float pos[3], dir[3], delta[3];
  // XXX ouch this only works if global path length
  // XXX is greater than number of lens elements!
  path_t path;
  assert(PATHSPACE_MAX_VERTS > lens->num);

  // init v[0] as scene point, trace fake ray to opos
  path_init(&path, 0, 0);
  memset(path.v, 0, sizeof(vertex_t)*lens->num);
  memset(path.e, 0, sizeof(edge_t)*lens->num);
  path.v[0].mode = s_transmit | s_specular;
  path.v[0].hit.x[0] = scene[0];
  path.v[0].hit.x[1] = scene[1];
  path.v[0].hit.x[2] = -scene[2];
  path.e[1].omega[0] = odir[0];
  path.e[1].omega[1] = odir[1];
  path.e[1].omega[2] = odir[2];
  path.e[0].vol.ior = 1.0f; // start in vacuum (TODO should be global exterior medium here!)
  path.e[1].vol.ior = 1.0f;

  // tangent space init (path_init zeros out the rest):
  path.lambda = lambda;
  path.v[0].hit.a[0] = 1.0f;
  path.v[0].hit.b[1] = 1.0f;
  path.v[0].hit.n[2] = 1.0f;
  path.v[0].diffgeo.dpdu[0] = 1.0f;
  path.v[0].diffgeo.dpdv[1] = 1.0f;
  path.length = 1;

  for(int k=0;k<3;k++) pos[k] = path.v[0].hit.x[k];
  for(int k=0;k<3;k++) dir[k] = path.e[1].omega[k];

  const float transmittance = evaluate_reverse(
      lens, lambda, pos, dir, opos, odir, 1, &path, 0);

  if(path.length < 2) return 0.0f;

  // path_print(&path, stdout);
  path.v[0].diffgeo.type = s_pinned_position;
  if(lensmf_compute_derivatives(&path, 0, path.length-1) == 0.0f) return 0.0f;
  // map change of aperture position to change in v[1] (scene-facing optical element)
  lensmf_map(path.v + 1,
      apos[0] - path.v[path.length-1].hit.x[0],
      apos[1] - path.v[path.length-1].hit.x[1],
      delta);

  for(int k=0;k<3;k++)
    odir[k] = path.v[1].hit.x[k] + delta[k] - path.v[0].hit.x[k];
  normalise(odir);

  // also return aperture position for error estimation:
  for(int k=0;k<3;k++)
    apos[k] = path.v[path.length-1].hit.x[k];
  return transmittance;
}

#undef INTENSITY_EPS
