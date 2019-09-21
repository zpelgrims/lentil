case unknown__petzval__1900__85mm:
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
       + 62.6941 *begin_dx + 0.729786 *begin_x + 0.291467 *begin_x*begin_lambda + 16.2221 *begin_dx*begin_lambda + 0.517575 *begin_y*begin_dx*begin_dy + 0.0099905 *begin_x*begin_y*begin_dy + 0.0160318 *lens_ipow(begin_x, 2)*begin_dx + -0.401112 *begin_x*lens_ipow(begin_lambda, 2) + 9.19733e-05 *begin_x*lens_ipow(begin_y, 2) + 8.56897e-05 *lens_ipow(begin_x, 3) + 0.115145 *begin_x*lens_ipow(begin_dy, 2) + 0.606557 *begin_x*lens_ipow(begin_dx, 2) + 0.00673083 *lens_ipow(begin_y, 2)*begin_dx + -22.3745 *begin_dx*lens_ipow(begin_lambda, 2) + 10.8466 *begin_dx*lens_ipow(begin_lambda, 3) + 0.193867 *begin_x*lens_ipow(begin_lambda, 3) + 1.10113e-05 *lens_ipow(begin_x, 4)*begin_dx + 0.272949 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.9176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 2.37024e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 0.00187757 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.00036301 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 7.47695e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + 4.04912e-07 *lens_ipow(begin_x, 5)*begin_lambda + 7.11313e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -6.79192e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 2) + 3.87066e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 3) + 1.46099e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2),
       + 0.72786 *begin_y + 62.6813 *begin_dy + 16.2795 *begin_dy*begin_lambda + 0.300939 *begin_y*begin_lambda + 0.118253 *begin_y*lens_ipow(begin_dx, 2) + 0.0160989 *lens_ipow(begin_y, 2)*begin_dy + 0.612785 *begin_y*lens_ipow(begin_dy, 2) + 0.518242 *begin_x*begin_dx*begin_dy + 0.0101635 *begin_x*begin_y*begin_dx + -0.416936 *begin_y*lens_ipow(begin_lambda, 2) + 9.47264e-05 *lens_ipow(begin_x, 2)*begin_y + -22.4924 *begin_dy*lens_ipow(begin_lambda, 2) + 8.54947e-05 *lens_ipow(begin_y, 3) + 0.00684215 *lens_ipow(begin_x, 2)*begin_dy + 0.202682 *begin_y*lens_ipow(begin_lambda, 3) + 10.9306 *begin_dy*lens_ipow(begin_lambda, 3) + 1.568e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.0124216 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -1.71981e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -2.16242e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 9.42582e-08 *lens_ipow(begin_y, 5) + 0.000776229 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 1.16933e-08 *lens_ipow(begin_y, 5)*begin_lambda + 3.94969e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 0.000790013 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 1.09145e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -176826 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 7) + 1.07179e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 62.6941  + 16.2221 *begin_lambda + 0.517575 *begin_y*begin_dy + 0.0160318 *lens_ipow(begin_x, 2) + 1.21311 *begin_x*begin_dx + 0.00673083 *lens_ipow(begin_y, 2) + -22.3745 *lens_ipow(begin_lambda, 2) + 10.8466 *lens_ipow(begin_lambda, 3) + 1.10113e-05 *lens_ipow(begin_x, 4) + 0.545899 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 1.9176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.00187757 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.00072602 *lens_ipow(begin_x, 3)*begin_dx + 1.46099e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(0, 1) =  + 0.517575 *begin_y*begin_dx + 0.0099905 *begin_x*begin_y + 0.230291 *begin_x*begin_dy + 0.545899 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 2.37024e-06 *lens_ipow(begin_x, 3)*begin_y + 0.00375515 *lens_ipow(begin_y, 2)*begin_dx*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + 0.236505 *begin_y*begin_dx + 0.518242 *begin_x*begin_dy + 0.0101635 *begin_x*begin_y + -3.43961e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.00158003 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 1.09145e-07 *begin_x*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)*begin_lambda + -707304 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 7)+0.0f;
    dx1_domega0(1, 1) =  + 62.6813  + 16.2795 *begin_lambda + 0.0160989 *lens_ipow(begin_y, 2) + 1.22557 *begin_y*begin_dy + 0.518242 *begin_x*begin_dx + -22.4924 *lens_ipow(begin_lambda, 2) + 0.00684215 *lens_ipow(begin_x, 2) + 10.9306 *lens_ipow(begin_lambda, 3) + 1.568e-05 *lens_ipow(begin_y, 4) + 0.0372647 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.00155246 *lens_ipow(begin_y, 3)*begin_dy + 0.00237004 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 2.1829e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dx*begin_dy*begin_lambda + -1.23778e+06 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 6)+0.0f;
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
    out(0) =  + 77.1309 *begin_dx + 0.454088 *begin_x + 0.59228 *begin_x*begin_lambda + 31.296 *begin_dx*begin_lambda + 0.0214508 *begin_x*begin_y*begin_dy + 0.0269243 *lens_ipow(begin_x, 2)*begin_dx + -56.2187 *lens_ipow(begin_dx, 3) + -0.818791 *begin_x*lens_ipow(begin_lambda, 2) + -55.2151 *begin_dx*lens_ipow(begin_dy, 2) + 0.000177113 *begin_x*lens_ipow(begin_y, 2) + 0.000157602 *lens_ipow(begin_x, 3) + 0.409904 *begin_x*lens_ipow(begin_dy, 2) + 0.334909 *begin_x*lens_ipow(begin_dx, 2) + 0.00768378 *lens_ipow(begin_y, 2)*begin_dx + -42.9963 *begin_dx*lens_ipow(begin_lambda, 2) + 20.7679 *begin_dx*lens_ipow(begin_lambda, 3) + 0.397003 *begin_x*lens_ipow(begin_lambda, 3) + 8.74322e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 6.98523e-06 *lens_ipow(begin_x, 3)*begin_lambda + 4.3619e-05 *lens_ipow(begin_x, 4)*begin_dx + 0.0525086 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 2.49875e-07 *lens_ipow(begin_x, 5) + 0.00258281 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 1.82642e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 1.03989e-14 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 4) + -8.9507e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -5.54443e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 2.91034e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4)*begin_dx;
    out(1) =  + 0.453986 *begin_y + 77.1077 *begin_dy + 31.4081 *begin_dy*begin_lambda + 0.590498 *begin_y*begin_lambda + 0.408793 *begin_y*lens_ipow(begin_dx, 2) + 0.0293245 *lens_ipow(begin_y, 2)*begin_dy + 0.436343 *begin_y*lens_ipow(begin_dy, 2) + 0.0214208 *begin_x*begin_y*begin_dx + -55.3199 *lens_ipow(begin_dx, 2)*begin_dy + -0.815614 *begin_y*lens_ipow(begin_lambda, 2) + 0.000179169 *lens_ipow(begin_x, 2)*begin_y + -43.2699 *begin_dy*lens_ipow(begin_lambda, 2) + 0.000178562 *lens_ipow(begin_y, 3) + 0.00770216 *lens_ipow(begin_x, 2)*begin_dy + -55.0125 *lens_ipow(begin_dy, 3) + -0.0235675 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.395174 *begin_y*lens_ipow(begin_lambda, 3) + 20.9473 *begin_dy*lens_ipow(begin_lambda, 3) + 9.35429e-06 *lens_ipow(begin_y, 3)*begin_lambda + 5.03411e-06 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 2.83665e-07 *lens_ipow(begin_y, 4)*begin_dy + 4.67524e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -2.69784e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4) + 1.44244e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2) + 308682 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 7) + -7.54745e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx*begin_dy + 9.46377e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7) + 3.17946 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5);
    out(2) =  + -1.66455 *begin_dx + -0.0229909 *begin_x + -0.000609063 *begin_x*begin_lambda + 0.212594 *begin_dx*begin_lambda + -0.0360606 *begin_y*begin_dx*begin_dy + -0.000664524 *begin_x*begin_y*begin_dy + -0.000341473 *lens_ipow(begin_x, 2)*begin_dx + 0.973882 *lens_ipow(begin_dx, 3) + 0.000455632 *begin_x*lens_ipow(begin_lambda, 2) + -1.16931 *begin_dx*lens_ipow(begin_dy, 2) + -2.93278e-06 *begin_x*lens_ipow(begin_y, 2) + -1.28054e-06 *lens_ipow(begin_x, 3) + -0.0254622 *begin_x*lens_ipow(begin_dy, 2) + -0.000224042 *lens_ipow(begin_y, 2)*begin_dx + -0.313753 *begin_dx*lens_ipow(begin_lambda, 2) + -0.00281935 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.165033 *begin_dx*lens_ipow(begin_lambda, 3) + -0.172153 *lens_ipow(begin_dx, 3)*begin_lambda + 1.04913 *lens_ipow(begin_dx, 5) + -1.34098e-07 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + -1.52874e-09 *lens_ipow(begin_x, 5)*begin_lambda + -0.0146742 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 66.5723 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 22.5431 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 10.3113 *begin_dx*lens_ipow(begin_dy, 6) + 0.000101564 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 5.91217e-05 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -5.46709e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_lambda;
    out(3) =  + -0.0229683 *begin_y + -1.639 *begin_dy + 0.0662049 *begin_dy*begin_lambda + -0.000715456 *begin_y*begin_lambda + 0.00445966 *begin_y*lens_ipow(begin_dx, 2) + -0.000318875 *lens_ipow(begin_y, 2)*begin_dy + 0.0555798 *begin_x*begin_dx*begin_dy + 3.06218 *lens_ipow(begin_dx, 2)*begin_dy + 0.000562722 *begin_y*lens_ipow(begin_lambda, 2) + 3.55327e-07 *lens_ipow(begin_x, 2)*begin_y + -0.0411715 *begin_dy*lens_ipow(begin_lambda, 2) + -1.15925e-06 *lens_ipow(begin_y, 3) + 0.91784 *lens_ipow(begin_dy, 3) + -0.149761 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.00120167 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -0.0284935 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 2.33253 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.0060437 *begin_y*lens_ipow(begin_dx, 4) + 1.1839 *lens_ipow(begin_dy, 5) + -0.00216157 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 2.49518e-06 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -0.22379 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -1.47763e-07 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -1.58375e-09 *lens_ipow(begin_y, 5)*begin_lambda + 0.00129974 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 1.05286e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 1.37693e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 2) + -0.00487297 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4);
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
    domega2_dx0(0, 0) =  + -0.0229909  + -0.000609063 *begin_lambda + -0.000664524 *begin_y*begin_dy + -0.000682946 *begin_x*begin_dx + 0.000455632 *lens_ipow(begin_lambda, 2) + -2.93278e-06 *lens_ipow(begin_y, 2) + -3.84163e-06 *lens_ipow(begin_x, 2) + -0.0254622 *lens_ipow(begin_dy, 2) + -0.00281935 *lens_ipow(begin_dx, 2)*begin_lambda + -5.36391e-07 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -7.64371e-09 *lens_ipow(begin_x, 4)*begin_lambda + -0.0146742 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.000203128 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -1.64013e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -0.0360606 *begin_dx*begin_dy + -0.000664524 *begin_x*begin_dy + -5.86556e-06 *begin_x*begin_y + -0.000448084 *begin_y*begin_dx + -0.0146742 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.000101564 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.000177365 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -2.18684e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.0555798 *begin_dx*begin_dy + 7.10653e-07 *begin_x*begin_y + 0.00240334 *begin_x*begin_dy*begin_lambda + -0.0284935 *lens_ipow(begin_dx, 3)*begin_dy + -0.00432315 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 7.48553e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.00259949 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + 1.05286e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 1.37693e-07 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(1, 1) =  + -0.0229683  + -0.000715456 *begin_lambda + 0.00445966 *lens_ipow(begin_dx, 2) + -0.000637749 *begin_y*begin_dy + 0.000562722 *lens_ipow(begin_lambda, 2) + 3.55327e-07 *lens_ipow(begin_x, 2) + -3.47775e-06 *lens_ipow(begin_y, 2) + 0.0060437 *lens_ipow(begin_dx, 4) + -5.91053e-07 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -7.91873e-09 *lens_ipow(begin_y, 4)*begin_lambda + 2.10571e-05 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + 4.13079e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -0.00487297 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4)+0.0f;
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
  out[4] =  + 0.593176  + 0.842987 *begin_lambda + -1.75872 *lens_ipow(begin_lambda, 2) + 1.07251e-06 *lens_ipow(begin_y, 2)*begin_lambda + 1.72466 *lens_ipow(begin_lambda, 3) + -0.655162 *lens_ipow(begin_lambda, 4) + 0.388269 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -7.48269e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -7.43305e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -1.9575e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.04882e-07 *lens_ipow(begin_y, 4) + -0.000268865 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.0116643 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.00605e-05 *lens_ipow(begin_x, 3)*begin_dx + -0.000305766 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.0123624 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -1.01951e-07 *lens_ipow(begin_x, 4) + -0.000192304 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -1.09073e-05 *lens_ipow(begin_y, 3)*begin_dy + -0.0124214 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -3.84348e-11 *lens_ipow(begin_y, 6) + -5.9017e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 5) + -6.1907e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 2.14622e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 2.65517e-10 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 2) + -1.32932e-13 *lens_ipow(begin_x, 8) + -2.05383e-14 *lens_ipow(begin_x, 9)*begin_dx + -1.44793e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_lambda;
else
  out[4] = 0.0f;
} break;
