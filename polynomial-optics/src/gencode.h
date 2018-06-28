#pragma once
#include "poly.h"

void print_poly_system_code(FILE *f, const poly_system_t *system,
    const char *vnamei[poly_num_vars],
    const char *vnameo[poly_num_vars])
{
  for(int i = 0; i < poly_num_vars; i++)
  {
    fprintf(f, "const float out_%s = ", vnameo[i]);
    poly_print(&system->poly[i], vnamei, f);
    fprintf(f, ";\n");
  }
}

// dump out jacobian source code to a stream
void print_jacobian(FILE *f, const poly_system_t *system, const char *vnamei[poly_num_vars])
{
  poly_jacobian_t jacobian;
  poly_system_get_jacobian(system, &jacobian);
  for(int i = 0; i < poly_num_vars; i++)
    for(int j = 0; j < poly_num_vars; j++)
    {
      fprintf(f, "const float dx%d%d = ", i, j);
      poly_print(&jacobian.poly[i*poly_num_vars+j], vnamei, f);
      fprintf(f, "+0.0f;\n");
    }
}

void print_pt_sample_aperture(FILE *f, const poly_system_t *system,
    const char *vnamei[poly_num_vars],
    const char *vnameo[poly_num_vars])
{
  // input to this is [x,y,dx,dy] and `dist', which is the distance to the start of the polynomial.

  char *begin_var[poly_num_vars];
  for(int k=0;k<poly_num_vars;k++) begin_var[k] = malloc(50);
  for(int k=0;k<poly_num_vars;k++) snprintf(begin_var[k], 50, "begin_%s", vnamei[k]);

  // solve the first two rows of the system x1 = P(x0, omega0, ..) for given x1 and x0.
  // 1) first guess, take omega0 = normalise(x1 - x0), leave rest of x0 input unchanged
  //    this has to be done outside, we don't know about the 3d geometry any more.
  // float sqr_err = 0.0f;
  for(int k=0;k<4;k++)
    fprintf(f, "float pred_%s;\n", vnameo[k]);
  fprintf(f, "float sqr_err = FLT_MAX;\n");
  fprintf(f, "for(int k=0;k<5&&sqr_err > 1e-4f;k++)\n{\n");

  // 1.5) compute input to the polynomial, begin_[x,y,dx,dy] from our initial guess and the distance:
  fprintf(f, "  const float %s = %s + dist * %s;\n", begin_var[0], vnamei[0], vnamei[2]);
  fprintf(f, "  const float %s = %s + dist * %s;\n", begin_var[1], vnamei[1], vnamei[3]);
  fprintf(f, "  const float %s = %s;\n", begin_var[2], vnamei[2]);
  fprintf(f, "  const float %s = %s;\n", begin_var[3], vnamei[3]);
  // wavelength may be unused for lenses such as lensbaby, where the aperture comes right after
  // the sensor, without glass elements in between:
  fprintf(f, "  __attribute__((unused)) const float %s = %s;\n", begin_var[4], vnamei[4]);

  // 2) evaluate what we get x1' = P(x0, omega0, ..)
  for(int k=0;k<4;k++)
  {
    fprintf(f, "  pred_%s = ", vnameo[k]);
    poly_print(&system->poly[k], (const char**)begin_var, f);
    fprintf(f, ";\n");
  }

  // 3) evaluate 2x2 submatrix of jacobian dx1/domega0 and step omega0 back to our target x1.
  poly_jacobian_t sysjac;
  poly_system_get_jacobian(system, &sysjac);
  fprintf(f, "  float dx1_domega0[2][2];\n");
  for(int i=0;i<2;i++) for(int j=0;j<2;j++)
  {
    fprintf(f, "  dx1_domega0[%d][%d] = ", i, j);
    poly_print(&sysjac.poly[i*poly_num_vars+j+2], (const char**)begin_var, f);
    fprintf(f, "+0.0f;\n");
  }
  for(int k=0;k<poly_num_vars*poly_num_vars;k++)
    poly_destroy(sysjac.poly+k);

  // 4) invert jacobian (could use adjoint, but who's gonna fight over a 2x2 inversion)
  fprintf(f, "  float invJ[2][2];\n");
  fprintf(f, "  const float invdet = 1.0f/(dx1_domega0[0][0]*dx1_domega0[1][1] - dx1_domega0[0][1]*dx1_domega0[1][0]);\n");
  fprintf(f, "  invJ[0][0] =  dx1_domega0[1][1]*invdet;\n");
  fprintf(f, "  invJ[1][1] =  dx1_domega0[0][0]*invdet;\n");
  fprintf(f, "  invJ[0][1] = -dx1_domega0[0][1]*invdet;\n");
  fprintf(f, "  invJ[1][0] = -dx1_domega0[1][0]*invdet;\n");

  // 5) determine step and update omega0
  fprintf(f, "  const float dx1[2] = {out_x - pred_x, out_y - pred_y};\n");
    // sqr_err = 0.0f;
    // for(int k=0;k<2;k++) sqr_err += dx1[k]*dx1[k];
  fprintf(f, "  for(int i=0;i<2;i++)\n  {\n");
  for(int k=0;k<2;k++)
  fprintf(f, "    %s += invJ[%d][i]*dx1[i];\n", vnamei[k+2], k);
  fprintf(f, "  }\n");
  fprintf(f, "  sqr_err = dx1[0]*dx1[0] + dx1[1]*dx1[1];\n");

  fprintf(f, "}\n"); // end newton iteration loop
  // now evaluate omega out
  for(int k=0;k<2;k++)
    fprintf(f, "out_%s = pred_%s;\n", vnameo[k+2], vnameo[k+2]);
  for(int k=0;k<poly_num_vars;k++) free(begin_var[k]);
}

// light tracer connecting to a given point on the aperture and in the scene.
// idea as follows:
//
// evaluate:
//
// input : z[x,y,z] point on the scene geometry
// input : a[x,y,u,v] point on aperture, [u,v] initial guess
// output: x[x,y,u,v] point on the sensor
//
// // do newton iterations
// while(error > EPSILON || apertureError > EPSILON)
// {
//   // calculate error in aperture position
//   delta_ap = (a - Pa(x))[x,y]
//   // propagate back error to sensor direction through 2x2 subblock of jacobian
//   // mapping sensor directions to aperture positions
//   x[u,v] += Ja^{-1}(x)*delta_ap
//   // calculate error in direction on the outer pupil
//   out = fromSpherical(P(x))[x,y,z,u,v,w]
//   reqDir = normalise(z - out[x,y,z])
//   delta_out = toSpherical(out[u,v,w]-reqDir)
//   // propagate back error to sensor position through 2x2 subblock of jacobian
//   // mapping sensor positions to outer pupil directions
//   x[x,y] += J^{-1}(x) * delta_out
// }
void print_lt_sample_aperture(FILE *f, const poly_system_t *system, const poly_system_t *ap_system,
    const char *vnamei[poly_num_vars],
    const char *vnameo[poly_num_vars])
{
  // input to this is scene_[x,y,z] point in scene and ap_[x,y] point on the aperture
  fprintf(f, "//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture\n");
  fprintf(f, "//output: [x,y,dx,dy] point and direction on sensor\n");
  //for debug output
  fprintf(f, "#ifndef DEBUG_LOG\n#define DEBUG_LOG\n#endif\n");

  char *begin_var[poly_num_vars];
  for(int k=0;k<poly_num_vars;k++) begin_var[k] = malloc(50);
  for(int k=0;k<poly_num_vars;k++) snprintf(begin_var[k], 50, "begin_%s", vnamei[k]);
  //early out if worldspace point is definitely outside field of view:
  fprintf(f, "float view[3] =\n{\n");
  fprintf(f, "  scene_x,\n");
  fprintf(f, "  scene_y,\n");
  fprintf(f, "  scene_z + lens_outer_pupil_curvature_radius\n};\n");
  fprintf(f, "normalise(view);\n");
  fprintf(f, "int error = 0;\n");
  fprintf(f, "if(1 || view[2] >= lens_field_of_view)\n{\n");
  fprintf(f, "  const float eps = 1e-8;\n");
  fprintf(f, "  float sqr_err = 1e30, sqr_ap_err = 1e30;\n");
  fprintf(f, "  float prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;\n");
  //also stop if error is getting larger
  fprintf(f, "  for(int k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)\n  {\n");
  fprintf(f, "    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;\n");

  // 1) input to the polynomial, begin_[x,y,dx,dy], is always the same as the current sensor guess vname:
  fprintf(f, "    const float %s = %s;\n", begin_var[0], vnamei[0]);
  fprintf(f, "    const float %s = %s;\n", begin_var[1], vnamei[1]);
  fprintf(f, "    const float %s = %s;\n", begin_var[2], vnamei[2]);
  fprintf(f, "    const float %s = %s;\n", begin_var[3], vnamei[3]);
  fprintf(f, "    const float %s = %s;\n", begin_var[4], vnamei[4]);

  // 2) evaluate aperture position and calculate error vector
  fprintf(f, "    const float pred_ap[2] = {\n");
  for(int k=0;k<2;k++)
  {
    fprintf(f, "      ");
    poly_print(&ap_system->poly[k], (const char**)begin_var, f);
    fprintf(f, "%s", k<1?",\n":"\n    };\n");
  }

  fprintf(f, "    const float delta_ap[] = {ap_%s - pred_ap[0], ap_%s - pred_ap[1]};\n", vnameo[0], vnameo[1]);
  fprintf(f, "    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];\n");

  // 3) calculate inverse 2x2 submatrix of jacobian and propagate error back to sensor direction
  // 3.1) evaluate aperture jacobian
  poly_jacobian_t apjac;
  poly_system_get_jacobian(ap_system, &apjac);
  fprintf(f, "    float dx1_domega0[2][2];\n");
  for(int i=0;i<2;i++) for(int j=0;j<2;j++)
  {
    fprintf(f, "    dx1_domega0[%d][%d] = ", i, j);
    poly_print(&apjac.poly[i*poly_num_vars+j+2], (const char**)begin_var, f);
    fprintf(f, "+0.0f;\n");
  }

  // 3.2) invert jacobian
  fprintf(f, "    float invApJ[2][2];\n");
  fprintf(f, "    const float invdetap = 1.0f/(dx1_domega0[0][0]*dx1_domega0[1][1] - dx1_domega0[0][1]*dx1_domega0[1][0]);\n");
  fprintf(f, "    invApJ[0][0] =  dx1_domega0[1][1]*invdetap;\n");
  fprintf(f, "    invApJ[1][1] =  dx1_domega0[0][0]*invdetap;\n");
  fprintf(f, "    invApJ[0][1] = -dx1_domega0[0][1]*invdetap;\n");
  fprintf(f, "    invApJ[1][0] = -dx1_domega0[1][0]*invdetap;\n");

  // 3.3) propagate back error
  // We do not need to check if the error is small here, as we would have exited
  // the loop if the error had been small
  fprintf(f, "    for(int i=0;i<2;i++)\n    {\n");
  for(int k=0;k<2;k++)
  {
    fprintf(f, "      %s += invApJ[%d][i]*delta_ap[i];\n", vnamei[k+2], k);
  }
  fprintf(f, "    }\n");

  // 4) evaluate scene direction and calculate error vector
  // - get out position and out direction in worldspace
  // - calculate vector from out position to scene point
  // - transform this vector back to spherical coordinates
  
  //do not calculate transmittance all the time, just once at the end
  for(int k=0;k<4;k++)
  {
    fprintf(f, "    out[%d] = ", k);
    poly_print(&system->poly[k], (const char**)begin_var, f);
    fprintf(f, ";\n");
  }
  fprintf(f, "    float pred_out_cs[7] = {0.0f};\n");
  fprintf(f, "    lens_sphereToCs(out, out+2, pred_out_cs, pred_out_cs+3, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);\n");
  fprintf(f, "    float view[3] =\n    {\n");
  fprintf(f, "      scene_x - pred_out_cs[0],\n");
  fprintf(f, "      scene_y - pred_out_cs[1],\n");
  fprintf(f, "      scene_z - pred_out_cs[2]\n    };\n");
  fprintf(f, "    normalise(view);\n");

  fprintf(f, "    float out_new[5];\n");
  //Position is just converted back, direction gets replaced with new one
  fprintf(f, "    lens_csToSphere(pred_out_cs, view, out_new, out_new+2, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);\n");

  //Calculate error vector (out_new - pred_out)[dx,dy]
  fprintf(f, "    const float delta_out[] = {out_new[2] - out[2], out_new[3] - out[3]};\n");
  fprintf(f, "    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];\n");

  // 5) Propagate error back to sensor position
  // 5.1) calculate inverse 2x2 submatrix of jacobian mapping sensor positions to outgoing directions
  poly_jacobian_t jac;
  poly_system_get_jacobian(system, &jac);
  fprintf(f, "    float domega2_dx0[2][2];\n");
  for(int i=0;i<2;i++) for(int j=0;j<2;j++)
  {
    fprintf(f, "    domega2_dx0[%d][%d] = ", i, j);
    poly_print(&jac.poly[(i+2)*poly_num_vars+j], (const char**)begin_var, f);
    fprintf(f, "+0.0f;\n");
  }

  // 5.2) invert jacobian
  fprintf(f, "    float invJ[2][2];\n");
  fprintf(f, "    const float invdet = 1.0f/(domega2_dx0[0][0]*domega2_dx0[1][1] - domega2_dx0[0][1]*domega2_dx0[1][0]);\n");
  fprintf(f, "    invJ[0][0] =  domega2_dx0[1][1]*invdet;\n");
  fprintf(f, "    invJ[1][1] =  domega2_dx0[0][0]*invdet;\n");
  fprintf(f, "    invJ[0][1] = -domega2_dx0[0][1]*invdet;\n");
  fprintf(f, "    invJ[1][0] = -domega2_dx0[1][0]*invdet;\n");

  // 5.3) propagate error back to sensor
  fprintf(f, "    for(int i=0;i<2;i++)\n    {\n");
  for(int k=0;k<2;k++)
    fprintf(f, "      %s += invJ[%d][i]*delta_out[i];\n", vnamei[k], k);
  fprintf(f, "    }\n");
  fprintf(f, "    if(sqr_err>prev_sqr_err) error |= 1;\n");
  fprintf(f, "    if(sqr_ap_err>prev_sqr_ap_err) error |= 2;\n");
  fprintf(f, "    if(out[0]!=out[0]) error |= 4;\n");
  fprintf(f, "    if(out[1]!=out[1]) error |= 8;\n");
  //fprintf(f, "    if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;\n");
  fprintf(f, "    DEBUG_LOG;\n");
  fprintf(f, "    // reset error code for first few iterations.\n");
  fprintf(f, "    if(k<10) error = 0;\n");
  fprintf(f, "  }\n");
  fprintf(f, "}\nelse\n  error = 128;\n");
  fprintf(f, "if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;\n");
  
  //now calculate transmittance or set it to zero if we stoped due to divergence
  fprintf(f, "const float %s = %s;\n", begin_var[0], vnamei[0]);
  fprintf(f, "const float %s = %s;\n", begin_var[1], vnamei[1]);
  fprintf(f, "const float %s = %s;\n", begin_var[2], vnamei[2]);
  fprintf(f, "const float %s = %s;\n", begin_var[3], vnamei[3]);
  fprintf(f, "const float %s = %s;\n", begin_var[4], vnamei[4]);
  
  fprintf(f, "if(error==0)\n");
  fprintf(f, "  out[4] = ");
  poly_print(&system->poly[4], (const char**)begin_var, f);
  fprintf(f, ";\n");
  fprintf(f, "else\n  out[4] = 0.0f;\n");
  for(int k=0;k<poly_num_vars;k++) free(begin_var[k]);
}
