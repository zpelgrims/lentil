case nikon__unknown__2014__50mm:
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
       + 32.2033 *begin_dx + 0.293892 *begin_x + 8.12711 *begin_dx*begin_lambda + 0.229711 *begin_x*begin_lambda + -5.57645 *begin_dx*lens_ipow(begin_lambda, 2) + -16.0656 *begin_dx*lens_ipow(begin_dy, 2) + -16.2005 *lens_ipow(begin_dx, 3) + -0.0330797 *begin_y*begin_dx*begin_dy + 0.00154237 *lens_ipow(begin_y, 2)*begin_dx + -0.161167 *begin_x*lens_ipow(begin_lambda, 2) + -0.086926 *begin_x*lens_ipow(begin_dy, 2) + -0.136109 *begin_x*lens_ipow(begin_dx, 2) + 0.00134402 *begin_x*begin_y*begin_dy + -0.000128356 *begin_x*lens_ipow(begin_y, 2) + 0.0029124 *lens_ipow(begin_x, 2)*begin_dx + -0.000130615 *lens_ipow(begin_x, 3) + -0.00890124 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -1.57528e-07 *begin_x*lens_ipow(begin_y, 4) + -0.0153847 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.00964676 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -5.44193e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -1.47617e-07 *lens_ipow(begin_x, 5) + 4.40819e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -2.0766 *begin_y*lens_ipow(begin_dx, 5)*begin_dy + -0.890754 *begin_x*lens_ipow(begin_dx, 6) + -0.0503654 *begin_x*begin_y*lens_ipow(begin_dy, 5) + -32.3674 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5) + -1.45718e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda,
       + 32.2903 *begin_dy + 0.294709 *begin_y + 7.97882 *begin_dy*begin_lambda + 0.22979 *begin_y*begin_lambda + -5.53527 *begin_dy*lens_ipow(begin_lambda, 2) + -16.2714 *lens_ipow(begin_dy, 3) + -16.138 *lens_ipow(begin_dx, 2)*begin_dy + -0.161941 *begin_y*lens_ipow(begin_lambda, 2) + -0.159077 *begin_y*lens_ipow(begin_dy, 2) + -0.0877576 *begin_y*lens_ipow(begin_dx, 2) + 0.00172884 *lens_ipow(begin_y, 2)*begin_dy + -0.000142552 *lens_ipow(begin_y, 3) + -0.0369266 *begin_x*begin_dx*begin_dy + 0.00131549 *begin_x*begin_y*begin_dx + -0.000128886 *lens_ipow(begin_x, 2)*begin_y + 0.00270247 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -0.014938 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.000301109 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 6.01003e-06 *lens_ipow(begin_y, 4)*begin_dy + -1.06517e-07 *lens_ipow(begin_y, 5) + -5.77526e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -1.55789e-07 *lens_ipow(begin_x, 4)*begin_y + -0.0158074 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 4.97905e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -1.86604 *begin_x*begin_dx*lens_ipow(begin_dy, 5) + -0.0512776 *begin_x*begin_y*lens_ipow(begin_dx, 5) + -29.8029 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + -7.88417e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 32.2033  + 8.12711 *begin_lambda + -5.57645 *lens_ipow(begin_lambda, 2) + -16.0656 *lens_ipow(begin_dy, 2) + -48.6016 *lens_ipow(begin_dx, 2) + -0.0330797 *begin_y*begin_dy + 0.00154237 *lens_ipow(begin_y, 2) + -0.272218 *begin_x*begin_dx + 0.0029124 *lens_ipow(begin_x, 2) + -0.0267037 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0153847 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.0289403 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -10.383 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + -5.34452 *begin_x*lens_ipow(begin_dx, 5) + -97.1022 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5) + -1.45718e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -32.1313 *begin_dx*begin_dy + -0.0330797 *begin_y*begin_dx + -0.173852 *begin_x*begin_dy + 0.00134402 *begin_x*begin_y + -0.0307695 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -2.0766 *begin_y*lens_ipow(begin_dx, 5) + -0.251827 *begin_x*begin_y*lens_ipow(begin_dy, 4) + -161.837 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + -1.45718e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + -32.2759 *begin_dx*begin_dy + -0.175515 *begin_y*begin_dx + -0.0369266 *begin_x*begin_dy + 0.00131549 *begin_x*begin_y + -0.0298761 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -1.86604 *begin_x*lens_ipow(begin_dy, 5) + -0.256388 *begin_x*begin_y*lens_ipow(begin_dx, 4) + -149.014 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -7.88417e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 32.2903  + 7.97882 *begin_lambda + -5.53527 *lens_ipow(begin_lambda, 2) + -48.8143 *lens_ipow(begin_dy, 2) + -16.138 *lens_ipow(begin_dx, 2) + -0.318155 *begin_y*begin_dy + 0.00172884 *lens_ipow(begin_y, 2) + -0.0369266 *begin_x*begin_dx + 0.00270247 *lens_ipow(begin_x, 2)*begin_lambda + -0.014938 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.000602218 *lens_ipow(begin_y, 3)*begin_dy + 6.01003e-06 *lens_ipow(begin_y, 4) + -0.0474223 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -9.33022 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -89.4087 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + -7.88417e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx+0.0f;
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
    out(0) =  + 49.7012 *begin_dx + -0.212613 *begin_x + 1.27307 *begin_dx*begin_lambda + 0.404138 *begin_x*begin_lambda + -23.1829 *begin_dx*lens_ipow(begin_dy, 2) + -22.6096 *lens_ipow(begin_dx, 3) + 0.00455905 *lens_ipow(begin_y, 2)*begin_dx + -0.305967 *begin_x*lens_ipow(begin_lambda, 2) + 0.301279 *begin_x*lens_ipow(begin_dy, 2) + 0.308243 *begin_x*lens_ipow(begin_dx, 2) + 0.00854471 *begin_x*begin_y*begin_dy + -0.000385561 *begin_x*lens_ipow(begin_y, 2) + 0.0138204 *lens_ipow(begin_x, 2)*begin_dx + -0.000387283 *lens_ipow(begin_x, 3) + 0.00018661 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.000169064 *lens_ipow(begin_x, 3)*begin_lambda + 17.7985 *begin_dx*lens_ipow(begin_dy, 4) + 37.2819 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -3.82252e-07 *begin_x*lens_ipow(begin_y, 4) + -0.0127892 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -7.51068e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -3.33622e-07 *lens_ipow(begin_x, 5) + 33.5268 *lens_ipow(begin_dx, 5)*begin_lambda + 8.61077e-09 *lens_ipow(begin_y, 6)*begin_dx + -3.67016e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -16.0073 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 5) + 1.6653e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + 4.65906e-13 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2)*begin_dx;
    out(1) =  + 49.7454 *begin_dy + -0.22674 *begin_y + 1.24723 *begin_dy*begin_lambda + 0.432303 *begin_y*begin_lambda + -22.886 *lens_ipow(begin_dy, 3) + -24.0534 *lens_ipow(begin_dx, 2)*begin_dy + -0.307127 *begin_y*lens_ipow(begin_lambda, 2) + 0.310584 *begin_y*lens_ipow(begin_dy, 2) + 0.354842 *begin_y*lens_ipow(begin_dx, 2) + 0.0136129 *lens_ipow(begin_y, 2)*begin_dy + -0.000292058 *lens_ipow(begin_y, 3) + 0.00879727 *begin_x*begin_y*begin_dx + 0.00461721 *lens_ipow(begin_x, 2)*begin_dy + -0.000310742 *lens_ipow(begin_x, 2)*begin_y + -0.12958 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 37.4118 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 19.4673 *lens_ipow(begin_dx, 4)*begin_dy + -3.89967e-07 *lens_ipow(begin_y, 5) + -1.37179e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -3.17215e-07 *lens_ipow(begin_x, 4)*begin_y + 35.2127 *lens_ipow(begin_dy, 5)*begin_lambda + 1.43815e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 0.00283339 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 4) + -9.59077e-07 *lens_ipow(begin_x, 5)*begin_dx*begin_dy + -15.3132 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 5) + 3.43868e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 2.96504e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy + 4.57468e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*lens_ipow(begin_lambda, 2);
    out(2) =  + -0.656388 *begin_dx + -0.0184691 *begin_x + 0.00461947 *begin_dx*begin_lambda + -0.000470267 *begin_x*begin_lambda + 0.231104 *begin_dx*lens_ipow(begin_dy, 2) + 0.344279 *lens_ipow(begin_dx, 3) + 0.001826 *begin_y*begin_dx*begin_dy + 3.68965e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.00307331 *begin_x*lens_ipow(begin_dy, 2) + 0.00188426 *begin_x*lens_ipow(begin_dx, 2) + -0.000110734 *begin_x*begin_y*begin_dy + 7.42494e-06 *begin_x*lens_ipow(begin_y, 2) + -7.734e-05 *lens_ipow(begin_x, 2)*begin_dx + 1.72866e-05 *lens_ipow(begin_x, 3) + -3.03205e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -4.20198e-05 *lens_ipow(begin_x, 3)*begin_lambda + 0.000270495 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.0004597 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 3.62885e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 8.38843e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 1.57957e-08 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + 9.60291e-12 *begin_x*lens_ipow(begin_y, 6) + 1.0731e-06 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 2) + 2.59887e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 2) + -3.63002e-10 *lens_ipow(begin_x, 6)*begin_dx + 4.9865e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 4.67665e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -6.21182e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 5);
    out(3) =  + -0.653251 *begin_dy + -0.0175214 *begin_y + -0.00406715 *begin_y*begin_lambda + 0.341807 *lens_ipow(begin_dy, 3) + 0.45725 *lens_ipow(begin_dx, 2)*begin_dy + 0.00328034 *begin_y*lens_ipow(begin_lambda, 2) + 0.00213872 *begin_y*lens_ipow(begin_dy, 2) + -0.00313275 *begin_y*lens_ipow(begin_dx, 2) + -7.48374e-05 *lens_ipow(begin_y, 2)*begin_dy + 7.03734e-06 *lens_ipow(begin_y, 3) + 0.00869214 *begin_x*begin_dx*begin_dy + -0.000119345 *begin_x*begin_y*begin_dx + 6.94791e-06 *lens_ipow(begin_x, 2)*begin_y + -2.85094e-06 *lens_ipow(begin_y, 3)*begin_lambda + 2.68957e-05 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -3.03631e-06 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 0.000298998 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 4.51713e-09 *lens_ipow(begin_y, 5) + 1.22595e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.000298759 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.000212181 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 9.26815e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 5.73254e-09 *lens_ipow(begin_x, 4)*begin_y + -1.69555e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + -2.60542e-10 *lens_ipow(begin_y, 6)*begin_dy + -1.49943e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -3.03442e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx + -1.61975e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6)*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.0184691  + -0.000470267 *begin_lambda + -0.00307331 *lens_ipow(begin_dy, 2) + 0.00188426 *lens_ipow(begin_dx, 2) + -0.000110734 *begin_y*begin_dy + 7.42494e-06 *lens_ipow(begin_y, 2) + -0.00015468 *begin_x*begin_dx + 5.18597e-05 *lens_ipow(begin_x, 2) + -3.03205e-06 *lens_ipow(begin_y, 2)*begin_lambda + -0.000126059 *lens_ipow(begin_x, 2)*begin_lambda + -0.0004597 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.000108866 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 2.51653e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 1.57957e-08 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + 9.60291e-12 *lens_ipow(begin_y, 6) + 4.29238e-06 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + 1.29943e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 2) + -2.17801e-09 *lens_ipow(begin_x, 5)*begin_dx + 1.9946e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 2.33833e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -3.10591e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 5)+0.0f;
    domega2_dx0(0, 1) =  + 0.001826 *begin_dx*begin_dy + 7.37931e-05 *begin_y*begin_dx + -0.000110734 *begin_x*begin_dy + 1.48499e-05 *begin_x*begin_y + -6.06411e-06 *begin_x*begin_y*begin_lambda + 0.00054099 *begin_y*lens_ipow(begin_dx, 3) + -0.0004597 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.67769e-08 *lens_ipow(begin_x, 3)*begin_y + 6.31827e-08 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 5.76175e-11 *begin_x*lens_ipow(begin_y, 5) + 1.49595e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.87066e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.00869214 *begin_dx*begin_dy + -0.000119345 *begin_y*begin_dx + 1.38958e-05 *begin_x*begin_y + 5.37913e-05 *begin_x*begin_dy*begin_lambda + -6.07262e-06 *begin_x*begin_y*begin_lambda + 1.22595e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.000597518 *begin_x*lens_ipow(begin_dy, 3) + 0.000424361 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.85363e-08 *begin_x*lens_ipow(begin_y, 3) + 2.29302e-08 *lens_ipow(begin_x, 3)*begin_y + -4.49828e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -9.10327e-12 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx + -6.47899e-14 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.0175214  + -0.00406715 *begin_lambda + 0.00328034 *lens_ipow(begin_lambda, 2) + 0.00213872 *lens_ipow(begin_dy, 2) + -0.00313275 *lens_ipow(begin_dx, 2) + -0.000149675 *begin_y*begin_dy + 2.1112e-05 *lens_ipow(begin_y, 2) + -0.000119345 *begin_x*begin_dx + 6.94791e-06 *lens_ipow(begin_x, 2) + -8.55283e-06 *lens_ipow(begin_y, 2)*begin_lambda + -3.03631e-06 *lens_ipow(begin_x, 2)*begin_lambda + 0.000597995 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 2.25856e-08 *lens_ipow(begin_y, 4) + 2.45189e-05 *begin_x*begin_y*begin_dx*begin_dy + 2.78044e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 5.73254e-09 *lens_ipow(begin_x, 4) + -8.47775e-08 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -1.56325e-09 *lens_ipow(begin_y, 5)*begin_dy + -1.49943e-06 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + -1.51721e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx + -9.71848e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_dy+0.0f;
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
  out[4] =  + 1.14868 *begin_lambda + -1.45402 *lens_ipow(begin_lambda, 2) + 1.04417 *lens_ipow(begin_lambda, 4) + -0.489479 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.130712 *lens_ipow(begin_dx, 4) + -0.00547656 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000212948 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -7.33864e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00485668 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00420614 *begin_x*lens_ipow(begin_dx, 3) + -0.00023441 *begin_x*begin_y*begin_dx*begin_dy + -7.22729e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000155679 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -2.73397e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.59221e-08 *lens_ipow(begin_x, 4) + -0.308009 *lens_ipow(begin_dy, 4)*begin_lambda + -0.173446 *lens_ipow(begin_dx, 4)*begin_lambda + -0.0110142 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -0.000686115 *begin_x*begin_dx*lens_ipow(begin_lambda, 3) + -0.498134 *lens_ipow(begin_lambda, 6) + -0.364882 *lens_ipow(begin_dy, 6) + -6.7882e-11 *lens_ipow(begin_y, 6) + -3.12185e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.33486e-11 *lens_ipow(begin_x, 7)*begin_dx + 5.2333e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3) + -2.17971e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + -2.7285e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + 6.30973e-14 *lens_ipow(begin_x, 8)*begin_y*begin_dy;
else
  out[4] = 0.0f;
} break;
