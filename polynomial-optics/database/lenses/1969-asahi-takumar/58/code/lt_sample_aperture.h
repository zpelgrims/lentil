case asahi__takumar__1969__58mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
Eigen::Vector3d view(
  scene_x,
  scene_y,
  scene_z + lens_outer_pupil_curvature_radius
);
raytrace_normalise(view);
int error = 0;
if(1 || view(2) >= lens_field_of_view)
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
       + 35.3504 *begin_dx + 0.332363 *begin_x + 6.97928 *begin_dx*begin_lambda + 0.191351 *begin_x*begin_lambda + -4.80586 *begin_dx*lens_ipow(begin_lambda, 2) + -20.3723 *begin_dx*lens_ipow(begin_dy, 2) + -20.1465 *lens_ipow(begin_dx, 3) + -0.131496 *begin_y*begin_dx*begin_dy + -0.133966 *begin_x*lens_ipow(begin_lambda, 2) + -0.128929 *begin_x*lens_ipow(begin_dy, 2) + -0.272339 *begin_x*lens_ipow(begin_dx, 2) + 0.00123259 *begin_x*begin_y*begin_dy + -8.13897e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00301142 *lens_ipow(begin_x, 2)*begin_dx + -8.77939e-05 *lens_ipow(begin_x, 3) + 0.00293381 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.2949 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.0184865 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.18574e-07 *begin_x*lens_ipow(begin_y, 4) + -4.20053e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -9.8336e-08 *lens_ipow(begin_x, 5) + 3.56329e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -0.0195012 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.074804 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4),
       + 35.372 *begin_dy + 0.33302 *begin_y + 6.83847 *begin_dy*begin_lambda + 0.19069 *begin_y*begin_lambda + -4.6714 *begin_dy*lens_ipow(begin_lambda, 2) + -20.1086 *lens_ipow(begin_dy, 3) + -20.0429 *lens_ipow(begin_dx, 2)*begin_dy + -0.133313 *begin_y*lens_ipow(begin_lambda, 2) + -0.273146 *begin_y*lens_ipow(begin_dy, 2) + -0.160689 *begin_y*lens_ipow(begin_dx, 2) + 0.003187 *lens_ipow(begin_y, 2)*begin_dy + -8.68112e-05 *lens_ipow(begin_y, 3) + -0.152337 *begin_x*begin_dx*begin_dy + 0.00124609 *begin_x*begin_y*begin_dx + -8.49409e-05 *lens_ipow(begin_x, 2)*begin_y + 0.00302293 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.222472 *begin_y*lens_ipow(begin_dx, 4) + -0.0108468 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.0183e-07 *lens_ipow(begin_y, 5) + 0.0156842 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -4.09e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -1.07898e-07 *lens_ipow(begin_x, 4)*begin_y + 3.49524e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -0.0214537 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 35.3504  + 6.97928 *begin_lambda + -4.80586 *lens_ipow(begin_lambda, 2) + -20.3723 *lens_ipow(begin_dy, 2) + -60.4394 *lens_ipow(begin_dx, 2) + -0.131496 *begin_y*begin_dy + -0.544679 *begin_x*begin_dx + 0.00301142 *lens_ipow(begin_x, 2) + 0.00293381 *lens_ipow(begin_y, 2)*begin_lambda + -0.2949 *begin_y*lens_ipow(begin_dy, 3) + 0.0369729 *begin_x*begin_y*begin_dx*begin_dy + -0.0585036 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.074804 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)+0.0f;
    dx1_domega0(0, 1) =  + -40.7446 *begin_dx*begin_dy + -0.131496 *begin_y*begin_dx + -0.257857 *begin_x*begin_dy + 0.00123259 *begin_x*begin_y + -0.8847 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.0184865 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -0.299216 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 0) =  + -40.0858 *begin_dx*begin_dy + -0.321378 *begin_y*begin_dx + -0.152337 *begin_x*begin_dy + 0.00124609 *begin_x*begin_y + 0.889887 *begin_y*lens_ipow(begin_dx, 3) + -0.0216937 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0156842 *begin_x*begin_y*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 1) =  + 35.372  + 6.83847 *begin_lambda + -4.6714 *lens_ipow(begin_lambda, 2) + -60.3259 *lens_ipow(begin_dy, 2) + -20.0429 *lens_ipow(begin_dx, 2) + -0.546291 *begin_y*begin_dy + 0.003187 *lens_ipow(begin_y, 2) + -0.152337 *begin_x*begin_dx + 0.00302293 *lens_ipow(begin_x, 2)*begin_lambda + -0.0108468 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.0313684 *begin_x*begin_y*begin_dx*begin_dy + -0.064361 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
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
    out(0) =  + 57.7741 *begin_dx + -0.0308817 *begin_x + 0.050174 *begin_x*begin_lambda + 0.613972 *begin_dx*lens_ipow(begin_lambda, 2) + -24.4595 *begin_dx*lens_ipow(begin_dy, 2) + -23.736 *lens_ipow(begin_dx, 3) + 0.00617687 *lens_ipow(begin_y, 2)*begin_dx + 0.577339 *begin_x*lens_ipow(begin_dx, 2) + 0.0130109 *begin_x*begin_y*begin_dy + -0.000330382 *begin_x*lens_ipow(begin_y, 2) + 0.0212544 *lens_ipow(begin_x, 2)*begin_dx + -0.000449769 *lens_ipow(begin_x, 3) + 1.69639 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.000128385 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.000438111 *lens_ipow(begin_x, 3)*begin_lambda + -1.58964 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.000337425 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.000347184 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -1.3385 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.79597e-05 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + -1.21395e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 0.140782 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5)*begin_lambda + -1.27111e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 3) + -1.52819e-12 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2);
    out(1) =  + 57.7731 *begin_dy + -0.0294735 *begin_y + 0.049727 *begin_y*begin_lambda + 0.602644 *begin_dy*lens_ipow(begin_lambda, 2) + -23.6547 *lens_ipow(begin_dy, 3) + -24.4826 *lens_ipow(begin_dx, 2)*begin_dy + 0.58088 *begin_y*lens_ipow(begin_dy, 2) + 0.0213003 *lens_ipow(begin_y, 2)*begin_dy + -0.000463359 *lens_ipow(begin_y, 3) + 0.0129471 *begin_x*begin_y*begin_dx + 0.00618951 *lens_ipow(begin_x, 2)*begin_dy + -0.000335623 *lens_ipow(begin_x, 2)*begin_y + 1.66746 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.000430412 *lens_ipow(begin_y, 3)*begin_lambda + 0.000122598 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -1.54388 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000359176 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 0.000328128 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -1.36066 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.79525e-05 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.138515 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5)*begin_lambda + -1.63056e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 4) + -2.63698e-12 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7) + -3.26244e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3);
    out(2) =  + -0.908304 *begin_dx + -0.0153871 *begin_x + -0.00554684 *begin_x*begin_lambda + 0.0841608 *begin_dx*lens_ipow(begin_dy, 2) + 0.414482 *lens_ipow(begin_dx, 3) + 3.04851e-05 *lens_ipow(begin_y, 2)*begin_dx + 0.00401261 *begin_x*lens_ipow(begin_lambda, 2) + -0.000185438 *begin_x*begin_y*begin_dy + 6.04255e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000119408 *lens_ipow(begin_x, 2)*begin_dx + 5.92748e-06 *lens_ipow(begin_x, 3) + -0.0020329 *begin_y*begin_dx*begin_dy*begin_lambda + -0.0245715 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 7.39235e-06 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 1.99197e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -3.5625e-07 *lens_ipow(begin_x, 4)*begin_dx + 0.000358812 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 0.0561268 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 3.09625e-07 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + -0.0548824 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5) + -2.70906e-05 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 7.84563e-06 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 4) + 1.90133e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -2.02743e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_lambda;
    out(3) =  + -0.904689 *begin_dy + -0.0154621 *begin_y + -0.00532167 *begin_y*begin_lambda + 0.390625 *lens_ipow(begin_dy, 3) + 0.70435 *lens_ipow(begin_dx, 2)*begin_dy + 0.00385934 *begin_y*lens_ipow(begin_lambda, 2) + -0.00634462 *begin_y*lens_ipow(begin_dx, 2) + -0.000175813 *lens_ipow(begin_y, 2)*begin_dy + 5.9302e-06 *lens_ipow(begin_y, 3) + 0.0134282 *begin_x*begin_dx*begin_dy + -0.0001819 *begin_x*begin_y*begin_dx + 5.75584e-06 *lens_ipow(begin_x, 2)*begin_y + 8.60007e-05 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -5.33282e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -1.55203e-07 *lens_ipow(begin_y, 4)*begin_dy + 0.00043908 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.000698016 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 6.68186e-06 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -9.13175e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.46812e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 2.38092e-08 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + 4.96277e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -5.85103e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_lambda + 3.79338e-14 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7);
    Eigen::Vector3d pred_out_cs_pos(0,0,0);
    Eigen::Vector3d pred_out_cs_dir(0,0,0);
    Eigen::Vector2d outpos(out(0), out(1));
    Eigen::Vector2d outdir(out(2), out(3));
    if (lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, true);
    else if (lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    Eigen::Vector3d view(
      scene_x - pred_out_cs_pos(0),
      scene_y - pred_out_cs_pos(1),
      scene_z - pred_out_cs_pos(2)
    );
    raytrace_normalise(view);
    Eigen::VectorXd out_new(5); out_new.setZero();
    Eigen::Vector2d out_new_pos(0,0);
    Eigen::Vector2d out_new_dir(0,0);
    if (lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, true);
    else if (lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    out_new(0) = out_new_pos(0);
    out_new(1) = out_new_pos(1);
    out_new(2) = out_new_dir(0);
    out_new(3) = out_new_dir(1);
    const Eigen::Vector2d delta_out(out_new[2] - out[2], out_new[3] - out[3]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2d domega2_dx0;
    domega2_dx0(0, 0) =  + -0.0153871  + -0.00554684 *begin_lambda + 0.00401261 *lens_ipow(begin_lambda, 2) + -0.000185438 *begin_y*begin_dy + 6.04255e-06 *lens_ipow(begin_y, 2) + -0.000238817 *begin_x*begin_dx + 1.77825e-05 *lens_ipow(begin_x, 2) + -0.0245715 *lens_ipow(begin_dy, 2)*begin_lambda + 3.98393e-05 *begin_x*begin_y*begin_dx*begin_dy + -1.425e-06 *lens_ipow(begin_x, 3)*begin_dx + 0.0561268 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 1.2385e-06 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -0.0548824 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5) + -2.70906e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 3.13825e-05 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 4) + 9.50663e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -1.01372e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + 6.09703e-05 *begin_y*begin_dx + -0.000185438 *begin_x*begin_dy + 1.20851e-05 *begin_x*begin_y + -0.0020329 *begin_dx*begin_dy*begin_lambda + 2.21771e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.99197e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.000717623 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + -8.12717e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 7.6053e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3) + -8.10972e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.0134282 *begin_dx*begin_dy + -0.0001819 *begin_y*begin_dx + 1.15117e-05 *begin_x*begin_y + 0.00087816 *begin_x*lens_ipow(begin_dy, 3) + 0.00139603 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 2.00456e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -2.46812e-06 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 9.52368e-08 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2) + 1.98511e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -2.34041e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_lambda + 7.58675e-14 *begin_x*lens_ipow(begin_y, 7)+0.0f;
    domega2_dx0(1, 1) =  + -0.0154621  + -0.00532167 *begin_lambda + 0.00385934 *lens_ipow(begin_lambda, 2) + -0.00634462 *lens_ipow(begin_dx, 2) + -0.000351627 *begin_y*begin_dy + 1.77906e-05 *lens_ipow(begin_y, 2) + -0.0001819 *begin_x*begin_dx + 5.75584e-06 *lens_ipow(begin_x, 2) + 0.000172001 *begin_y*begin_dy*begin_lambda + -1.59985e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -6.20812e-07 *lens_ipow(begin_y, 3)*begin_dy + -0.000273953 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -7.40436e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 2.38092e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 2) + 1.48883e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -1.75531e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_lambda + 2.65536e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6)+0.0f;
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
if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;
const double begin_x = x;
const double begin_y = y;
const double begin_dx = dx;
const double begin_dy = dy;
const double begin_lambda = lambda;
if(error==0)
  out[4] =  + 2.1378 *begin_lambda + -4.74165 *lens_ipow(begin_lambda, 2) + -0.00023108 *begin_y*begin_dy + -5.48265e-06 *lens_ipow(begin_x, 2) + 4.93941 *lens_ipow(begin_lambda, 3) + -0.000818915 *begin_x*begin_dx*begin_lambda + -1.98797 *lens_ipow(begin_lambda, 4) + -0.409383 *lens_ipow(begin_dy, 4) + -0.919756 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.236811 *lens_ipow(begin_dx, 4) + -0.0187692 *begin_y*lens_ipow(begin_dy, 3) + -0.0165798 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000454854 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00013168 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0167656 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.000473471 *begin_x*begin_y*begin_dx*begin_dy + -0.000128105 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.388407 *lens_ipow(begin_dx, 4)*begin_lambda + -3.99206e-08 *lens_ipow(begin_y, 4)*begin_lambda + -0.0289851 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + -0.000635817 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -5.66045e-06 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -0.898675 *lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2) + -2.36172e-15 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4);
else
  out[4] = 0.0f;
} break;
