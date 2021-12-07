case cooke__speed_panchro__1920__100mm:
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
       + 70.0927 *begin_dx + 0.642366 *begin_x + 0.0856359 *begin_x*begin_lambda + 8.207 *begin_dx*begin_lambda + -0.306917 *begin_y*begin_dx*begin_dy + 0.0010317 *lens_ipow(begin_x, 2)*begin_dx + -45.8417 *lens_ipow(begin_dx, 3) + -0.0586154 *begin_x*lens_ipow(begin_lambda, 2) + -46.0844 *begin_dx*lens_ipow(begin_dy, 2) + 1.06655e-05 *begin_x*lens_ipow(begin_y, 2) + 9.49318e-06 *lens_ipow(begin_x, 3) + -0.256023 *begin_x*lens_ipow(begin_dy, 2) + -0.558043 *begin_x*lens_ipow(begin_dx, 2) + 0.000992735 *lens_ipow(begin_y, 2)*begin_dx + -5.60491 *begin_dx*lens_ipow(begin_lambda, 2) + -0.0266219 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -3.76283 *begin_x*lens_ipow(begin_dx, 4) + -0.031807 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -3.50353 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -121.218 *lens_ipow(begin_dx, 5) + -3.76677 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -104.008 *begin_dx*lens_ipow(begin_dy, 4) + -0.0210866 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -2.95128 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0143364 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.020339 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -234.842 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 3.98383e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx,
       + 0.642885 *begin_y + 70.1796 *begin_dy + 8.1424 *begin_dy*begin_lambda + 0.0847499 *begin_y*begin_lambda + -0.274506 *begin_y*lens_ipow(begin_dx, 2) + 0.000578186 *lens_ipow(begin_y, 2)*begin_dy + -0.64955 *begin_y*lens_ipow(begin_dy, 2) + -52.0577 *lens_ipow(begin_dx, 2)*begin_dy + -0.0578827 *begin_y*lens_ipow(begin_lambda, 2) + 1.05888e-05 *lens_ipow(begin_x, 2)*begin_y + -5.55115 *begin_dy*lens_ipow(begin_lambda, 2) + 9.95709e-06 *lens_ipow(begin_y, 3) + 0.000744536 *lens_ipow(begin_x, 2)*begin_dy + -51.3611 *lens_ipow(begin_dy, 3) + -1.88091 *begin_x*begin_dx*begin_dy*begin_lambda + 2.59627 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.0120035 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.92652 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.00337103 *begin_x*begin_y*lens_ipow(begin_dx, 3) + -57.7709 *lens_ipow(begin_dx, 4)*begin_dy + 0.787701 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + -684.315 *lens_ipow(begin_dy, 7) + -0.102244 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + -1.40302 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + -0.207061 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5) + -24.7483 *begin_y*lens_ipow(begin_dy, 6) + 0.00887828 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -6442.83 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 7)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 70.0927  + 8.207 *begin_lambda + -0.306917 *begin_y*begin_dy + 0.0010317 *lens_ipow(begin_x, 2) + -137.525 *lens_ipow(begin_dx, 2) + -46.0844 *lens_ipow(begin_dy, 2) + -1.11609 *begin_x*begin_dx + 0.000992735 *lens_ipow(begin_y, 2) + -5.60491 *lens_ipow(begin_lambda, 2) + -0.0532438 *begin_x*begin_y*begin_dx*begin_dy + -15.0513 *begin_x*lens_ipow(begin_dx, 3) + -0.095421 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -10.5106 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -606.09 *lens_ipow(begin_dx, 4) + -7.53354 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -104.008 *lens_ipow(begin_dy, 4) + -0.0210866 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -2.95128 *begin_y*lens_ipow(begin_dy, 3) + -0.0430091 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.020339 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -704.526 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 3.98383e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)+0.0f;
    dx1_domega0(0, 1) =  + -0.306917 *begin_y*begin_dx + -92.1688 *begin_dx*begin_dy + -0.512046 *begin_x*begin_dy + -0.0266219 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -3.50353 *begin_y*lens_ipow(begin_dx, 3) + -7.53354 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -416.033 *begin_dx*lens_ipow(begin_dy, 3) + -0.0421732 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -8.85384 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.040678 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -469.684 *lens_ipow(begin_dx, 3)*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + -0.549013 *begin_y*begin_dx + -104.115 *begin_dx*begin_dy + -1.88091 *begin_x*begin_dy*begin_lambda + 2.59627 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.0240069 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -5.77957 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -0.0101131 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -231.084 *lens_ipow(begin_dx, 3)*begin_dy + 0.787701 *begin_x*begin_y*lens_ipow(begin_dy, 4) + -1.40302 *begin_x*begin_dy*lens_ipow(begin_lambda, 4) + 0.00887828 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -12885.7 *begin_dx*lens_ipow(begin_dy, 7)+0.0f;
    dx1_domega0(1, 1) =  + 70.1796  + 8.1424 *begin_lambda + 0.000578186 *lens_ipow(begin_y, 2) + -1.2991 *begin_y*begin_dy + -52.0577 *lens_ipow(begin_dx, 2) + -5.55115 *lens_ipow(begin_lambda, 2) + 0.000744536 *lens_ipow(begin_x, 2) + -154.083 *lens_ipow(begin_dy, 2) + -1.88091 *begin_x*begin_dx*begin_lambda + 2.59627 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.0120035 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.92652 *begin_x*lens_ipow(begin_dx, 3) + -57.7709 *lens_ipow(begin_dx, 4) + 3.1508 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -4790.2 *lens_ipow(begin_dy, 6) + -0.51122 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + -1.40302 *begin_x*begin_dx*lens_ipow(begin_lambda, 4) + -1.0353 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -148.49 *begin_y*lens_ipow(begin_dy, 5) + 0.0266348 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -45099.8 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6)+0.0f;
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
    out(0) =  + 98.9821 *begin_dx + 0.595713 *begin_x + 0.0155575 *begin_x*begin_lambda + 1.09609 *begin_dx*begin_lambda + 0.454774 *begin_y*begin_dx*begin_dy + 0.0275612 *begin_x*begin_y*begin_dy + 0.0278411 *lens_ipow(begin_x, 2)*begin_dx + -46.1965 *lens_ipow(begin_dx, 3) + -37.9112 *begin_dx*lens_ipow(begin_dy, 2) + 0.000172251 *begin_x*lens_ipow(begin_y, 2) + 0.00013455 *lens_ipow(begin_x, 3) + 0.968201 *begin_x*lens_ipow(begin_dy, 2) + 0.966248 *begin_x*lens_ipow(begin_dx, 2) + 0.00908415 *lens_ipow(begin_y, 2)*begin_dx + 3.93335e-05 *lens_ipow(begin_x, 4)*begin_dx + 4.29761 *begin_x*lens_ipow(begin_dx, 4) + 0.273077 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 8.14998e-08 *lens_ipow(begin_x, 5) + 0.0340154 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 0.00521466 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.000936333 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.259283 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.00508906 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 5.86382e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + 0.00335443 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 5.33562e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 0.817831 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + 2.34661e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2);
    out(1) =  + 0.594941 *begin_y + 99.0029 *begin_dy + 1.09371 *begin_dy*begin_lambda + 0.0180041 *begin_y*begin_lambda + 0.994974 *begin_y*lens_ipow(begin_dx, 2) + 0.0269692 *lens_ipow(begin_y, 2)*begin_dy + 0.919729 *begin_y*lens_ipow(begin_dy, 2) + 0.42872 *begin_x*begin_dx*begin_dy + 0.0267113 *begin_x*begin_y*begin_dx + -38.9922 *lens_ipow(begin_dx, 2)*begin_dy + 0.00017391 *lens_ipow(begin_x, 2)*begin_y + 0.000124928 *lens_ipow(begin_y, 3) + 0.00897131 *lens_ipow(begin_x, 2)*begin_dy + -46.4577 *lens_ipow(begin_dy, 3) + -0.687585 *begin_y*lens_ipow(begin_dx, 4) + 4.24728e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.29062 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 4.6995 *begin_y*lens_ipow(begin_dy, 4) + 1.10801e-07 *lens_ipow(begin_y, 5) + 1.93022e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.00115994 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.00555414 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 2.05724e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 0.258023 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.00552391 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 1.06864 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + 6.27509e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 6.73421e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda;
    out(2) =  + -1.5611 *begin_dx + -0.0195302 *begin_x + -0.0329162 *begin_y*begin_dx*begin_dy + -0.000553464 *begin_x*begin_y*begin_dy + -0.000239373 *lens_ipow(begin_x, 2)*begin_dx + 0.585513 *lens_ipow(begin_dx, 3) + -1.24965 *begin_dx*lens_ipow(begin_dy, 2) + -1.61235e-06 *begin_x*lens_ipow(begin_y, 2) + -4.90604e-07 *lens_ipow(begin_x, 3) + -0.0260655 *begin_x*lens_ipow(begin_dy, 2) + -0.00653252 *begin_x*lens_ipow(begin_dx, 2) + -0.000130977 *lens_ipow(begin_y, 2)*begin_dx + 0.0795359 *begin_x*lens_ipow(begin_dx, 4) + 0.0993467 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 3.78442 *lens_ipow(begin_dx, 5) + -0.000908762 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.000319173 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -1.55252e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -7.39077e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.20913e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.0169987 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 181.614 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + -0.00466995 *begin_x*begin_y*lens_ipow(begin_dy, 5) + 1.40425 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 2.22464 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 159.509 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2)*begin_lambda + 2.71843 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*begin_lambda + 137.644 *begin_dx*lens_ipow(begin_dy, 8);
    out(3) =  + -0.0195665 *begin_y + -1.56379 *begin_dy + -0.0001667 *lens_ipow(begin_y, 2)*begin_dy + -0.00174079 *begin_y*lens_ipow(begin_dy, 2) + 0.0454552 *begin_x*begin_dx*begin_dy + 2.57162 *lens_ipow(begin_dx, 2)*begin_dy + 7.83737e-07 *lens_ipow(begin_x, 2)*begin_y + -3.20787e-07 *lens_ipow(begin_y, 3) + 0.000218088 *lens_ipow(begin_x, 2)*begin_dy + 0.673077 *lens_ipow(begin_dy, 3) + 7.64197 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.00716687 *begin_y*lens_ipow(begin_dx, 4) + -1.49228e-07 *lens_ipow(begin_y, 4)*begin_dy + 2.81465 *lens_ipow(begin_dy, 5) + 0.0789539 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + 0.000649223 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0020327 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00042308 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.113038 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.15948e-05 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -3.06963e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00209341 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 3.473 *lens_ipow(begin_dx, 4)*begin_dy*lens_ipow(begin_lambda, 2) + 1.16981e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 3) + 0.148523 *begin_x*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2) + 1.22777e-07 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 4) + 0.0209036 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 7)*begin_lambda + 0.00102791 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 2);
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
    domega2_dx0(0, 0) =  + -0.0195302  + -0.000553464 *begin_y*begin_dy + -0.000478745 *begin_x*begin_dx + -1.61235e-06 *lens_ipow(begin_y, 2) + -1.47181e-06 *lens_ipow(begin_x, 2) + -0.0260655 *lens_ipow(begin_dy, 2) + -0.00653252 *lens_ipow(begin_dx, 2) + 0.0795359 *lens_ipow(begin_dx, 4) + -3.10503e-05 *begin_x*begin_y*begin_dx*begin_dy + -2.21723e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.20913e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00466995 *begin_y*lens_ipow(begin_dy, 5) + 1.40425 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 2.71843 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -0.0329162 *begin_dx*begin_dy + -0.000553464 *begin_x*begin_dy + -3.22471e-06 *begin_x*begin_y + -0.000261954 *begin_y*begin_dx + 0.0993467 *lens_ipow(begin_dx, 3)*begin_dy + -0.00181752 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.000638345 *begin_y*lens_ipow(begin_dx, 3) + -1.55252e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -2.41826e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.0339973 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.00466995 *begin_x*lens_ipow(begin_dy, 5) + 2.22464 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0454552 *begin_dx*begin_dy + 1.56747e-06 *begin_x*begin_y + 0.000436176 *begin_x*begin_dy + 0.0789539 *begin_dx*lens_ipow(begin_dy, 3) + 0.000649223 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 3.47844e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.00418682 *begin_x*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 4.67924e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3) + 0.148523 *lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2) + 4.91108e-07 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 4) + 0.0418072 *begin_x*lens_ipow(begin_dy, 7)*begin_lambda + 0.00308372 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(1, 1) =  + -0.0195665  + -0.000333401 *begin_y*begin_dy + -0.00174079 *lens_ipow(begin_dy, 2) + 7.83737e-07 *lens_ipow(begin_x, 2) + -9.6236e-07 *lens_ipow(begin_y, 2) + 0.00716687 *lens_ipow(begin_dx, 4) + -5.96913e-07 *lens_ipow(begin_y, 3)*begin_dy + 0.000649223 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00406541 *begin_y*lens_ipow(begin_dy, 3) + 0.00084616 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.113038 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -9.20888e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 1.22777e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 4)+0.0f;
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
  out[4] =  + 0.501267  + 0.572903 *begin_lambda + 0.00148701 *begin_y*begin_dy + 0.00122478 *begin_x*begin_dx + 8.40492e-06 *lens_ipow(begin_y, 2) + 0.0800527 *lens_ipow(begin_dy, 2) + 0.0722636 *lens_ipow(begin_dx, 2) + -0.791089 *lens_ipow(begin_lambda, 2) + 0.384565 *lens_ipow(begin_lambda, 3) + -4.28262 *lens_ipow(begin_dx, 4) + -0.143301 *begin_y*lens_ipow(begin_dy, 3) + -0.00069426 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.136936 *begin_x*lens_ipow(begin_dx, 3) + -8.71317 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.52161e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -4.4212 *lens_ipow(begin_dy, 4) + -1.5545e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -9.54433e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -5.15794e-08 *lens_ipow(begin_y, 4) + -0.00194097 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.142554 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.43599e-05 *lens_ipow(begin_x, 3)*begin_dx + -0.00207201 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.14085 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0027272 *begin_x*begin_y*begin_dx*begin_dy + -0.000663378 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.57935e-05 *lens_ipow(begin_y, 3)*begin_dy + -9.1091e-11 *lens_ipow(begin_x, 6);
else
  out[4] = 0.0f;
} break;
