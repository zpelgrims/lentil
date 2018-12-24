case angenieux_double_gauss_test_low_degree_low_coefficients_9999_49mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
Eigen::Vector3f view(
  scene_x,
  scene_y,
  scene_z + camera->lens_outer_pupil_curvature_radius
);
raytrace_normalise(view);
int error = 0;
if(1 || view(2) >= camera->lens_field_of_view)
{
  const float eps = 1e-8;
  float sqr_err = 1e30, sqr_ap_err = 1e30;
  float prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(int k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    const float begin_x = x;
    const float begin_y = y;
    const float begin_dx = dx;
    const float begin_dy = dy;
    const float begin_lambda = lambda;
    const Eigen::Vector2f pred_ap(
       + 27.6412 *begin_dx + 0.194212 *begin_x + 1.76473 *begin_dx*begin_lambda + 0.0836355 *begin_x*begin_lambda + -15.6427 *begin_dx*lens_ipow(begin_dy, 2) + -15.6168 *lens_ipow(begin_dx, 3) + -0.108718 *begin_y*begin_dx*begin_dy + -0.115429 *begin_x*lens_ipow(begin_dy, 2) + -0.224427 *begin_x*lens_ipow(begin_dx, 2) + -0.000294934 *begin_x*lens_ipow(begin_y, 2) + -0.000313961 *lens_ipow(begin_x, 3) + -8.60107e-07 *begin_x*lens_ipow(begin_y, 4) + -1.67653e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -7.78073e-07 *lens_ipow(begin_x, 5),
       + 27.8704 *begin_dy + 0.182264 *begin_y + 1.35479 *begin_dy*begin_lambda + 0.10441 *begin_y*begin_lambda + -15.6127 *lens_ipow(begin_dy, 3) + -15.596 *lens_ipow(begin_dx, 2)*begin_dy + -0.000308064 *lens_ipow(begin_y, 3) + -0.000297301 *lens_ipow(begin_x, 2)*begin_y + -0.397297 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.208492 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.190213 *begin_x*begin_dx*begin_dy*begin_lambda + -7.94038e-07 *lens_ipow(begin_y, 5) + -1.70633e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -8.30246e-07 *lens_ipow(begin_x, 4)*begin_y
    );
    const Eigen::Vector2f delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 27.6412  + 1.76473 *begin_lambda + -15.6427 *lens_ipow(begin_dy, 2) + -46.8504 *lens_ipow(begin_dx, 2) + -0.108718 *begin_y*begin_dy + -0.448854 *begin_x*begin_dx+0.0f;
    dx1_domega0(0, 1) =  + -31.2853 *begin_dx*begin_dy + -0.108718 *begin_y*begin_dx + -0.230859 *begin_x*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + -31.192 *begin_dx*begin_dy + -0.416984 *begin_y*begin_dx*begin_lambda + -0.190213 *begin_x*begin_dy*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 27.8704  + 1.35479 *begin_lambda + -46.838 *lens_ipow(begin_dy, 2) + -15.596 *lens_ipow(begin_dx, 2) + -0.794593 *begin_y*begin_dy*begin_lambda + -0.190213 *begin_x*begin_dx*begin_lambda+0.0f;
    Eigen::Matrix2f invApJ;
    const float invdetap = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
    invApJ(0, 0) =  dx1_domega0(1, 1)*invdetap;
    invApJ(1, 1) =  dx1_domega0(0, 0)*invdetap;
    invApJ(0, 1) = -dx1_domega0(0, 1)*invdetap;
    invApJ(1, 0) = -dx1_domega0(1, 0)*invdetap;
    for(int i=0;i<2;i++)
    {
      dx += invApJ(0, i)*delta_ap[i];
      dy += invApJ(1, i)*delta_ap[i];
    }
    out(0) =  + 49.1433 *begin_dx + -0.513328 *begin_x + 0.192173 *begin_x*begin_lambda + -20.335 *begin_dx*lens_ipow(begin_dy, 2) + -19.9106 *lens_ipow(begin_dx, 3) + 0.253296 *begin_x*lens_ipow(begin_dy, 2) + 0.319553 *begin_x*lens_ipow(begin_dx, 2) + 0.0060597 *begin_x*begin_y*begin_dy + -0.00117189 *begin_x*lens_ipow(begin_y, 2) + 0.0135173 *lens_ipow(begin_x, 2)*begin_dx + -0.000854669 *lens_ipow(begin_x, 3) + 2.67923e-05 *lens_ipow(begin_y, 4)*begin_dx + -2.31028e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -1.38382e-06 *lens_ipow(begin_x, 5);
    out(1) =  + 49.1383 *begin_dy + -0.513863 *begin_y + 0.19164 *begin_y*begin_lambda + -19.8535 *lens_ipow(begin_dy, 3) + -20.3529 *lens_ipow(begin_dx, 2)*begin_dy + 0.32836 *begin_y*lens_ipow(begin_dy, 2) + 0.253447 *begin_y*lens_ipow(begin_dx, 2) + 0.013764 *lens_ipow(begin_y, 2)*begin_dy + -0.000846311 *lens_ipow(begin_y, 3) + 0.0059326 *begin_x*begin_y*begin_dx + -0.001166 *lens_ipow(begin_x, 2)*begin_y + -1.39688e-06 *lens_ipow(begin_y, 5) + -2.4141e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.6327e-05 *lens_ipow(begin_x, 4)*begin_dy;
    out(2) =  + -0.609131 *begin_dx + -0.0136628 *begin_x + -0.00255248 *begin_x*begin_lambda + 0.167611 *begin_dx*lens_ipow(begin_dy, 2) + 0.272776 *lens_ipow(begin_dx, 3) + -0.0024947 *begin_x*lens_ipow(begin_dy, 2) + -0.00010505 *begin_x*begin_y*begin_dy + 9.13473e-06 *begin_x*lens_ipow(begin_y, 2) + 1.11558e-05 *lens_ipow(begin_x, 3) + 2.50396e-08 *begin_x*lens_ipow(begin_y, 4) + 3.52662e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 5.14112e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -5.82766e-07 *lens_ipow(begin_x, 4)*begin_dx + 1.89983e-08 *lens_ipow(begin_x, 5);
    out(3) =  + -0.612494 *begin_dy + -0.0136392 *begin_y + -0.00251221 *begin_y*begin_lambda + 0.279447 *lens_ipow(begin_dy, 3) + 0.369593 *lens_ipow(begin_dx, 2)*begin_dy + -0.00451731 *begin_y*lens_ipow(begin_dx, 2) + 1.02324e-05 *lens_ipow(begin_y, 3) + 0.00468285 *begin_x*begin_dx*begin_dy + -0.000103711 *begin_x*begin_y*begin_dx + 9.95221e-06 *lens_ipow(begin_x, 2)*begin_y + -5.66354e-07 *lens_ipow(begin_y, 4)*begin_dy + 2.09699e-08 *lens_ipow(begin_y, 5) + 5.37936e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.62875e-08 *lens_ipow(begin_x, 4)*begin_y;
    Eigen::Vector3f pred_out_cs_pos(0,0,0);
    Eigen::Vector3f pred_out_cs_dir(0,0,0);
    Eigen::Vector2f outpos(out(0), out(1));
    Eigen::Vector2f outdir(out(2), out(3));
    if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    Eigen::Vector3f view(
      scene_x - pred_out_cs_pos(0),
      scene_y - pred_out_cs_pos(1),
      scene_z - pred_out_cs_pos(2)
    );
    raytrace_normalise(view);
    Eigen::VectorXf out_new(5); out_new.setZero();
    Eigen::Vector2f out_new_pos(0,0);
    Eigen::Vector2f out_new_dir(0,0);
    if (camera->lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    out_new(0) = out_new_pos(0);
    out_new(1) = out_new_pos(1);
    out_new(2) = out_new_dir(0);
    out_new(3) = out_new_dir(1);
    const Eigen::Vector2f delta_out(out_new[2] - out[2], out_new[3] - out[3]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2f domega2_dx0;
    domega2_dx0(0, 0) =  + -0.0136628  + -0.00255248 *begin_lambda + -0.0024947 *lens_ipow(begin_dy, 2) + -0.00010505 *begin_y*begin_dy + 9.13473e-06 *lens_ipow(begin_y, 2) + 3.34674e-05 *lens_ipow(begin_x, 2) + 2.50396e-08 *lens_ipow(begin_y, 4) + 7.05324e-05 *begin_x*begin_y*begin_dx*begin_dy + 1.54234e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.33106e-06 *lens_ipow(begin_x, 3)*begin_dx + 9.49917e-08 *lens_ipow(begin_x, 4)+0.0f;
    domega2_dx0(0, 1) =  + -0.00010505 *begin_x*begin_dy + 1.82695e-05 *begin_x*begin_y + 1.00158e-07 *begin_x*lens_ipow(begin_y, 3) + 3.52662e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 1.02822e-07 *lens_ipow(begin_x, 3)*begin_y+0.0f;
    domega2_dx0(1, 0) =  + 0.00468285 *begin_dx*begin_dy + -0.000103711 *begin_y*begin_dx + 1.99044e-05 *begin_x*begin_y + 1.07587e-07 *begin_x*lens_ipow(begin_y, 3) + 1.0515e-07 *lens_ipow(begin_x, 3)*begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.0136392  + -0.00251221 *begin_lambda + -0.00451731 *lens_ipow(begin_dx, 2) + 3.06973e-05 *lens_ipow(begin_y, 2) + -0.000103711 *begin_x*begin_dx + 9.95221e-06 *lens_ipow(begin_x, 2) + -2.26542e-06 *lens_ipow(begin_y, 3)*begin_dy + 1.04849e-07 *lens_ipow(begin_y, 4) + 1.61381e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 2.62875e-08 *lens_ipow(begin_x, 4)+0.0f;
    Eigen::Matrix2f invJ;
    const float invdet = 1.0f/(domega2_dx0(0, 0)*domega2_dx0(1, 1) - domega2_dx0(0, 1)*domega2_dx0(1, 0));
    invJ(0, 0) =  domega2_dx0(1, 1)*invdet;
    invJ(1, 1) =  domega2_dx0(0, 0)*invdet;
    invJ(0, 1) = -domega2_dx0(0, 1)*invdet;
    invJ(1, 0) = -domega2_dx0(1, 0)*invdet;
    for(int i=0;i<2;i++)
    {
      x += 0.72 * invJ(0, i) * delta_out[i];
      y += 0.72 * invJ(1, i) * delta_out[i];
    }
    if(sqr_err>prev_sqr_err) error |= 1;
    if(sqr_ap_err>prev_sqr_ap_err) error |= 2;
    if(out[0]!=out[0]) error |= 4;
    if(out[1]!=out[1]) error |= 8;
    // reset error code for first few iterations.
    if(k<10) error = 0;
  }
}
else
  error = 128;
if(out[0]*out[0]+out[1]*out[1] > camera->lens_outer_pupil_radius*camera->lens_outer_pupil_radius) error |= 16;
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.327805  + 0.348986 *begin_lambda + -0.236323 *lens_ipow(begin_lambda, 2) + -0.00106248 *begin_x*begin_dx + -0.263343 *lens_ipow(begin_dy, 4) + -0.225619 *lens_ipow(begin_dx, 4) + -0.0106736 *begin_y*lens_ipow(begin_dy, 3) + -0.000301168 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -6.03226e-08 *lens_ipow(begin_y, 4) + 7.34702e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000227849 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -8.28495e-08 *lens_ipow(begin_x, 4) + -0.749681 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 4.68196e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 3);
else
  out[4] = 0.0f;
} break;
