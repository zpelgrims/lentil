case angenieux__double_gauss__1953__49mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
Eigen::Vector3d view(
  scene_x,
  scene_y,
  scene_z + camera->lens_outer_pupil_curvature_radius
);
raytrace_normalise(view);
int error = 0;
if(1 || view(2) >= camera->lens_field_of_view)
{
  const double eps = 1e-8;
  double sqr_err = 1e30, sqr_ap_err = 1e30;
  double prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(int k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    const double begin_x = x;
    const double begin_y = y;
    const double begin_dx = dx;
    const double begin_dy = dy;
    const double begin_lambda = lambda;
    const Eigen::Vector2d pred_ap(
       + 0.197484 *begin_x + 27.5928 *begin_dx + 1.74497 *begin_dx*begin_lambda + 0.08335 *begin_x*begin_lambda + -0.106556 *begin_y*begin_dx*begin_dy + -0.000436864 *begin_x*lens_ipow(begin_y, 2) + -15.176 *lens_ipow(begin_dx, 3) + -15.544 *begin_dx*lens_ipow(begin_dy, 2) + -0.000420072 *lens_ipow(begin_x, 3) + -0.193987 *begin_x*lens_ipow(begin_dx, 2) + -0.115566 *begin_x*lens_ipow(begin_dy, 2) + 8.53267e-06 *lens_ipow(begin_x, 4)*begin_dx + -1.37132e-09 *lens_ipow(begin_x, 7) + -1.42221e-09 *begin_x*lens_ipow(begin_y, 6) + -4.46795e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -4.32995e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2),
       + 27.5931 *begin_dy + 0.19711 *begin_y + 1.74531 *begin_dy*begin_lambda + 0.0839936 *begin_y*begin_lambda + -0.115586 *begin_y*lens_ipow(begin_dx, 2) + -0.000436985 *lens_ipow(begin_x, 2)*begin_y + -15.2094 *lens_ipow(begin_dy, 3) + -0.000418615 *lens_ipow(begin_y, 3) + -0.194777 *begin_y*lens_ipow(begin_dy, 2) + -15.493 *lens_ipow(begin_dx, 2)*begin_dy + -0.107801 *begin_x*begin_dx*begin_dy + 8.51781e-06 *lens_ipow(begin_y, 4)*begin_dy + -1.40883e-09 *lens_ipow(begin_y, 7) + -4.44726e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -4.38036e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -1.37285e-09 *lens_ipow(begin_x, 6)*begin_y
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 27.5928  + 1.74497 *begin_lambda + -0.106556 *begin_y*begin_dy + -45.5281 *lens_ipow(begin_dx, 2) + -15.544 *lens_ipow(begin_dy, 2) + -0.387974 *begin_x*begin_dx + 8.53267e-06 *lens_ipow(begin_x, 4)+0.0f;
    dx1_domega0(0, 1) =  + -0.106556 *begin_y*begin_dx + -31.0879 *begin_dx*begin_dy + -0.231133 *begin_x*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + -0.231172 *begin_y*begin_dx + -30.9859 *begin_dx*begin_dy + -0.107801 *begin_x*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 27.5931  + 1.74531 *begin_lambda + -45.6282 *lens_ipow(begin_dy, 2) + -0.389554 *begin_y*begin_dy + -15.493 *lens_ipow(begin_dx, 2) + -0.107801 *begin_x*begin_dx + 8.51781e-06 *lens_ipow(begin_y, 4)+0.0f;
    Eigen::Matrix2d invApJ;
    const double invdetap = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
    invApJ(0, 0) =  dx1_domega0(1, 1)*invdetap;
    invApJ(1, 1) =  dx1_domega0(0, 0)*invdetap;
    invApJ(0, 1) = -dx1_domega0(0, 1)*invdetap;
    invApJ(1, 0) = -dx1_domega0(1, 0)*invdetap;
    for(int i=0;i<2;i++)
    {
      dx += invApJ(0, i)*delta_ap[i];
      dy += invApJ(1, i)*delta_ap[i];
    }
    out(0) =  + -0.636603 *begin_x + 49.0721 *begin_dx + 0.724233 *begin_x*begin_lambda + -0.00113165 *begin_x*lens_ipow(begin_y, 2) + -20.1743 *lens_ipow(begin_dx, 3) + -20.6523 *begin_dx*lens_ipow(begin_dy, 2) + -0.00139289 *lens_ipow(begin_x, 3) + 0.00630502 *begin_x*begin_y*begin_dy + 0.297063 *begin_x*lens_ipow(begin_dx, 2) + -0.530259 *begin_x*lens_ipow(begin_lambda, 2) + 0.250268 *begin_x*lens_ipow(begin_dy, 2) + 0.00547431 *lens_ipow(begin_y, 2)*begin_dx + 0.000592076 *lens_ipow(begin_x, 3)*begin_lambda + 0.0232881 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -3.07406e-09 *lens_ipow(begin_x, 7) + -1.62938e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4);
    out(1) =  + 49.0535 *begin_dy + -0.467832 *begin_y + 0.104946 *begin_y*begin_lambda + 0.00642504 *begin_x*begin_y*begin_dx + 0.246686 *begin_y*lens_ipow(begin_dx, 2) + -0.000814023 *lens_ipow(begin_x, 2)*begin_y + -20.2681 *lens_ipow(begin_dy, 3) + -0.00138601 *lens_ipow(begin_y, 3) + 0.00567435 *lens_ipow(begin_x, 2)*begin_dy + -20.6771 *lens_ipow(begin_dx, 2)*begin_dy + 0.525409 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.000714418 *lens_ipow(begin_y, 3)*begin_lambda + 0.0237852 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -1.47814e-06 *lens_ipow(begin_x, 4)*begin_y + -3.09117e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -3.27987e-09 *lens_ipow(begin_y, 7);
    out(2) =  + -0.0123666 *begin_x + -0.609913 *begin_dx + -0.0098959 *begin_x*begin_lambda + 1.35313e-05 *begin_x*lens_ipow(begin_y, 2) + 0.25801 *lens_ipow(begin_dx, 3) + 0.182025 *begin_dx*lens_ipow(begin_dy, 2) + 2.0662e-05 *lens_ipow(begin_x, 3) + 0.00755466 *begin_x*lens_ipow(begin_lambda, 2) + -7.0297e-06 *lens_ipow(begin_x, 3)*begin_lambda + 2.11676e-08 *begin_x*lens_ipow(begin_y, 4) + 4.81488e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -5.45117e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 0.000931727 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -9.11762e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4) + 1.63809e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -3.04567e-09 *lens_ipow(begin_x, 6)*begin_dx;
    out(3) =  + -0.611143 *begin_dy + -0.0116902 *begin_y + -0.0100684 *begin_y*begin_lambda + -0.000126838 *begin_x*begin_y*begin_dx + -0.00465873 *begin_y*lens_ipow(begin_dx, 2) + 1.00098e-05 *lens_ipow(begin_x, 2)*begin_y + 0.273941 *lens_ipow(begin_dy, 3) + 1.29961e-05 *lens_ipow(begin_y, 3) + 0.357691 *lens_ipow(begin_dx, 2)*begin_dy + 0.00685957 *begin_y*lens_ipow(begin_lambda, 2) + 0.00425551 *begin_x*begin_dx*begin_dy + -5.50655e-07 *lens_ipow(begin_y, 4)*begin_dy + 2.45207e-08 *lens_ipow(begin_x, 4)*begin_y + 4.90176e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 4.62906e-11 *lens_ipow(begin_y, 7) + -3.83828e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy;
    Eigen::Vector3d pred_out_cs_pos(0,0,0);
    Eigen::Vector3d pred_out_cs_dir(0,0,0);
    Eigen::Vector2d outpos(out(0), out(1));
    Eigen::Vector2d outdir(out(2), out(3));
    if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    Eigen::Vector3d view(
      scene_x - pred_out_cs_pos(0),
      scene_y - pred_out_cs_pos(1),
      scene_z - pred_out_cs_pos(2)
    );
    raytrace_normalise(view);
    Eigen::VectorXd out_new(5); out_new.setZero();
    Eigen::Vector2d out_new_pos(0,0);
    Eigen::Vector2d out_new_dir(0,0);
    if (camera->lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    out_new(0) = out_new_pos(0);
    out_new(1) = out_new_pos(1);
    out_new(2) = out_new_dir(0);
    out_new(3) = out_new_dir(1);
    const Eigen::Vector2d delta_out(out_new[2] - out[2], out_new[3] - out[3]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2d domega2_dx0;
    domega2_dx0(0, 0) =  + -0.0123666  + -0.0098959 *begin_lambda + 1.35313e-05 *lens_ipow(begin_y, 2) + 6.19861e-05 *lens_ipow(begin_x, 2) + 0.00755466 *lens_ipow(begin_lambda, 2) + -2.10891e-05 *lens_ipow(begin_x, 2)*begin_lambda + 2.11676e-08 *lens_ipow(begin_y, 4) + 9.62976e-05 *begin_x*begin_y*begin_dx*begin_dy + -1.63535e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.000273529 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + 8.19045e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -1.8274e-08 *lens_ipow(begin_x, 5)*begin_dx+0.0f;
    domega2_dx0(0, 1) =  + 2.70627e-05 *begin_x*begin_y + 8.46706e-08 *begin_x*lens_ipow(begin_y, 3) + 4.81488e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -5.45117e-07 *lens_ipow(begin_x, 3)*begin_dy + 0.00186345 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 3.27618e-10 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    domega2_dx0(1, 0) =  + -0.000126838 *begin_y*begin_dx + 2.00195e-05 *begin_x*begin_y + 0.00425551 *begin_dx*begin_dy + 9.80827e-08 *lens_ipow(begin_x, 3)*begin_y + 9.80352e-08 *begin_x*lens_ipow(begin_y, 3) + -1.53531e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.0116902  + -0.0100684 *begin_lambda + -0.000126838 *begin_x*begin_dx + -0.00465873 *lens_ipow(begin_dx, 2) + 1.00098e-05 *lens_ipow(begin_x, 2) + 3.89883e-05 *lens_ipow(begin_y, 2) + 0.00685957 *lens_ipow(begin_lambda, 2) + -2.20262e-06 *lens_ipow(begin_y, 3)*begin_dy + 2.45207e-08 *lens_ipow(begin_x, 4) + 1.47053e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 3.24034e-10 *lens_ipow(begin_y, 6) + -7.67656e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dy+0.0f;
    Eigen::Matrix2d invJ;
    const double invdet = 1.0f/(domega2_dx0(0, 0)*domega2_dx0(1, 1) - domega2_dx0(0, 1)*domega2_dx0(1, 0));
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
const double begin_x = x;
const double begin_y = y;
const double begin_dx = dx;
const double begin_dy = dy;
const double begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.328411  + 0.347751 *begin_lambda + -0.000952343 *begin_y*begin_dy + -0.000969273 *begin_x*begin_dx + -0.236589 *lens_ipow(begin_lambda, 2) + -0.208874 *lens_ipow(begin_dy, 4) + -0.000239654 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000244213 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.209815 *lens_ipow(begin_dx, 4) + -0.000110959 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.420373 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00027197 *begin_x*begin_y*begin_dx*begin_dy + -0.000108937 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -1.71491e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.1839e-10 *lens_ipow(begin_y, 6) + -2.16236e-10 *lens_ipow(begin_x, 6);
else
  out[4] = 0.0f;
} break;
