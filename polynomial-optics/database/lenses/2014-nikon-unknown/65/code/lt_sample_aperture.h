case nikon__unknown__2014__65mm:
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
       + 42.0563 *begin_dx + 0.300576 *begin_x + 10.1414 *begin_dx*begin_lambda + 0.214202 *begin_x*begin_lambda + -6.97731 *begin_dx*lens_ipow(begin_lambda, 2) + -21.0205 *begin_dx*lens_ipow(begin_dy, 2) + -22.0311 *lens_ipow(begin_dx, 3) + -0.0407341 *begin_y*begin_dx*begin_dy + 0.00120982 *lens_ipow(begin_y, 2)*begin_dx + -0.149684 *begin_x*lens_ipow(begin_lambda, 2) + -0.106212 *begin_x*lens_ipow(begin_dy, 2) + -0.151312 *begin_x*lens_ipow(begin_dx, 2) + -8.02976e-05 *begin_x*lens_ipow(begin_y, 2) + -9.74553e-05 *lens_ipow(begin_x, 3) + 0.00162615 *begin_x*begin_y*begin_dy*begin_lambda + 0.00276732 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 5.28753 *lens_ipow(begin_dx, 5) + -0.00657433 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.149579 *begin_x*lens_ipow(begin_dy, 4) + -4.9183e-08 *begin_x*lens_ipow(begin_y, 4) + -2.12565e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.00761878 *begin_x*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -0.0177432 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 2.13574e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -4.30229 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 0.0659996 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + 0.000472109 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 1.24775e-08 *lens_ipow(begin_x, 6)*begin_dx*begin_lambda,
       + 42.0453 *begin_dy + 0.300596 *begin_y + 10.1934 *begin_dy*begin_lambda + 0.214154 *begin_y*begin_lambda + -7.0263 *begin_dy*lens_ipow(begin_lambda, 2) + -22.0459 *lens_ipow(begin_dy, 3) + -21.0386 *lens_ipow(begin_dx, 2)*begin_dy + -0.149526 *begin_y*lens_ipow(begin_lambda, 2) + -0.151727 *begin_y*lens_ipow(begin_dy, 2) + -0.106266 *begin_y*lens_ipow(begin_dx, 2) + -9.76492e-05 *lens_ipow(begin_y, 3) + -0.0405621 *begin_x*begin_dx*begin_dy + 0.00120503 *lens_ipow(begin_x, 2)*begin_dy + -8.04831e-05 *lens_ipow(begin_x, 2)*begin_y + 0.00275099 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.00165483 *begin_x*begin_y*begin_dx*begin_lambda + 5.27233 *lens_ipow(begin_dy, 5) + 0.148119 *begin_y*lens_ipow(begin_dx, 4) + -0.00654718 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -2.05928e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -4.88595e-08 *lens_ipow(begin_x, 4)*begin_y + -0.0175725 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.00793088 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 2.02634e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 0.00047923 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -4.38213 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 0.0651743 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + 1.25541e-08 *lens_ipow(begin_y, 6)*begin_dy*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 42.0563  + 10.1414 *begin_lambda + -6.97731 *lens_ipow(begin_lambda, 2) + -21.0205 *lens_ipow(begin_dy, 2) + -66.0932 *lens_ipow(begin_dx, 2) + -0.0407341 *begin_y*begin_dy + 0.00120982 *lens_ipow(begin_y, 2) + -0.302624 *begin_x*begin_dx + 0.00276732 *lens_ipow(begin_x, 2)*begin_lambda + 26.4377 *lens_ipow(begin_dx, 4) + -0.019723 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0177432 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -12.9069 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.263999 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.000944219 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_lambda, 2) + 1.24775e-08 *lens_ipow(begin_x, 6)*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -42.041 *begin_dx*begin_dy + -0.0407341 *begin_y*begin_dx + -0.212424 *begin_x*begin_dy + 0.00162615 *begin_x*begin_y*begin_lambda + 0.598316 *begin_x*lens_ipow(begin_dy, 3) + -0.0228563 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.0354864 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda + -12.9069 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.0659996 *begin_x*begin_y*lens_ipow(begin_dx, 4)+0.0f;
    dx1_domega0(1, 0) =  + -42.0772 *begin_dx*begin_dy + -0.212533 *begin_y*begin_dx + -0.0405621 *begin_x*begin_dy + 0.00165483 *begin_x*begin_y*begin_lambda + 0.592477 *begin_y*lens_ipow(begin_dx, 3) + -0.035145 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -0.0237926 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -13.1464 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.0651743 *begin_x*begin_y*lens_ipow(begin_dy, 4)+0.0f;
    dx1_domega0(1, 1) =  + 42.0453  + 10.1934 *begin_lambda + -7.0263 *lens_ipow(begin_lambda, 2) + -66.1378 *lens_ipow(begin_dy, 2) + -21.0386 *lens_ipow(begin_dx, 2) + -0.303454 *begin_y*begin_dy + -0.0405621 *begin_x*begin_dx + 0.00120503 *lens_ipow(begin_x, 2) + 0.00275099 *lens_ipow(begin_y, 2)*begin_lambda + 26.3617 *lens_ipow(begin_dy, 4) + -0.0196416 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.0175725 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 0.00095846 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -13.1464 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.260697 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + 1.25541e-08 *lens_ipow(begin_y, 6)*begin_lambda+0.0f;
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
    out(0) =  + 65.5137 *begin_dx + -0.197289 *begin_x + 0.365403 *begin_x*begin_lambda + -27.5694 *begin_dx*lens_ipow(begin_dy, 2) + -31.4173 *lens_ipow(begin_dx, 3) + -0.283928 *begin_x*lens_ipow(begin_lambda, 2) + 0.00665785 *begin_x*begin_y*begin_dy + -0.000221436 *begin_x*lens_ipow(begin_y, 2) + -0.000259673 *lens_ipow(begin_x, 3) + 0.0128508 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.554975 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 8.37962e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0269105 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.000150869 *lens_ipow(begin_x, 3)*begin_lambda + -0.0109403 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 6.51627 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -1.16156e-07 *begin_x*lens_ipow(begin_y, 4) + -0.0144733 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -2.64749e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -1.13329e-07 *lens_ipow(begin_x, 5) + -16.1365 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 351.299 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 139.266 *lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 2) + 11.0472 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -3.9742e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + 8.24634e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -782.246 *lens_ipow(begin_dx, 7)*lens_ipow(begin_lambda, 4) + 4431.07 *lens_ipow(begin_dx, 9)*lens_ipow(begin_dy, 2);
    out(1) =  + 64.8957 *begin_dy + -0.197385 *begin_y + 1.03238 *begin_dy*begin_lambda + 0.366722 *begin_y*begin_lambda + -29.8649 *lens_ipow(begin_dy, 3) + -26.256 *lens_ipow(begin_dx, 2)*begin_dy + -0.272661 *begin_y*lens_ipow(begin_lambda, 2) + -0.000284036 *lens_ipow(begin_y, 3) + 0.00653697 *begin_x*begin_y*begin_dx + -0.000267218 *lens_ipow(begin_x, 2)*begin_y + 0.740744 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0338913 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.000110462 *lens_ipow(begin_y, 3)*begin_lambda + 0.0139043 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 7.79939e-05 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 6.5456 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.0261589 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -0.0128668 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 49.5772 *lens_ipow(begin_dy, 5)*begin_lambda + -0.565712 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -16.3497 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.0143868 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 11.2612 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -1.09096e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 3378.76 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 5) + 8.55196e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4) + -2.9188e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + -82.0924 *lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 5);
    out(2) =  + -0.656494 *begin_dx + -0.013607 *begin_x + 0.00363416 *begin_dx*begin_lambda + -0.00258285 *begin_x*begin_lambda + 0.23305 *begin_dx*lens_ipow(begin_dy, 2) + 0.349521 *lens_ipow(begin_dx, 3) + 0.0013903 *begin_y*begin_dx*begin_dy + 0.0019656 *begin_x*lens_ipow(begin_lambda, 2) + -0.00225875 *begin_x*lens_ipow(begin_dy, 2) + 0.00121209 *begin_x*lens_ipow(begin_dx, 2) + -6.5419e-05 *begin_x*begin_y*begin_dy + 3.00764e-06 *begin_x*lens_ipow(begin_y, 2) + -3.9418e-05 *lens_ipow(begin_x, 2)*begin_dx + 3.22067e-06 *lens_ipow(begin_x, 3) + 4.07368e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -9.66526e-07 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -9.97369e-07 *lens_ipow(begin_x, 3)*begin_lambda + 0.000212494 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.00448816 *begin_x*lens_ipow(begin_dx, 4) + -0.000271737 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.12657e-09 *begin_x*lens_ipow(begin_y, 4) + 6.84676e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 2.46823e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -4.38786e-08 *lens_ipow(begin_x, 4)*begin_dx + 2.01002e-12 *lens_ipow(begin_x, 7) + -0.000531777 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4) + 3.48175e-06 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 4) + 8.34721e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy;
    out(3) =  + -0.655693 *begin_dy + -0.0134847 *begin_y + 0.00455994 *begin_dy*begin_lambda + -0.00284866 *begin_y*begin_lambda + 0.342059 *lens_ipow(begin_dy, 3) + 0.456353 *lens_ipow(begin_dx, 2)*begin_dy + 0.00204905 *begin_y*lens_ipow(begin_lambda, 2) + 0.00164244 *begin_y*lens_ipow(begin_dy, 2) + -4.78297e-05 *lens_ipow(begin_y, 2)*begin_dy + 2.41787e-06 *lens_ipow(begin_y, 3) + 0.00682038 *begin_x*begin_dx*begin_dy + -7.0817e-05 *begin_x*begin_y*begin_dx + 2.39308e-06 *lens_ipow(begin_x, 2)*begin_y + -0.00953099 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 1.81898e-05 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.000155176 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 1.48403e-09 *lens_ipow(begin_y, 5) + -0.000189681 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.000135569 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 6.25728e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 1.53483e-09 *lens_ipow(begin_x, 4)*begin_y + 0.0245243 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 0.000833866 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -6.23626e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -0.000927694 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.0248135 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5) + -9.09183e-09 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_lambda + 8.62479e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.013607  + -0.00258285 *begin_lambda + 0.0019656 *lens_ipow(begin_lambda, 2) + -0.00225875 *lens_ipow(begin_dy, 2) + 0.00121209 *lens_ipow(begin_dx, 2) + -6.5419e-05 *begin_y*begin_dy + 3.00764e-06 *lens_ipow(begin_y, 2) + -7.8836e-05 *begin_x*begin_dx + 9.66201e-06 *lens_ipow(begin_x, 2) + -9.66526e-07 *lens_ipow(begin_y, 2)*begin_lambda + -2.99211e-06 *lens_ipow(begin_x, 2)*begin_lambda + 0.00448816 *lens_ipow(begin_dx, 4) + -0.000271737 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.12657e-09 *lens_ipow(begin_y, 4) + 0.000136935 *begin_x*lens_ipow(begin_dx, 3) + 7.4047e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.75514e-07 *lens_ipow(begin_x, 3)*begin_dx + 1.40701e-11 *lens_ipow(begin_x, 6) + 1.3927e-05 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 4) + 3.33889e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy+0.0f;
    domega2_dx0(0, 1) =  + 0.0013903 *begin_dx*begin_dy + -6.5419e-05 *begin_x*begin_dy + 6.01529e-06 *begin_x*begin_y + 8.14736e-05 *begin_y*begin_dx*begin_lambda + -1.93305e-06 *begin_x*begin_y*begin_lambda + 0.000424988 *begin_y*lens_ipow(begin_dx, 3) + -0.000271737 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 4.50627e-09 *begin_x*lens_ipow(begin_y, 3) + 4.93647e-09 *lens_ipow(begin_x, 3)*begin_y + -0.00106355 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4) + 2.50416e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_dy+0.0f;
    domega2_dx0(1, 0) =  + 0.00682038 *begin_dx*begin_dy + -7.0817e-05 *begin_y*begin_dx + 4.78616e-06 *begin_x*begin_y + 3.63796e-05 *begin_x*begin_dy*begin_lambda + -0.000189681 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.000271137 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.25146e-08 *begin_x*lens_ipow(begin_y, 3) + 6.13933e-09 *lens_ipow(begin_x, 3)*begin_y + 0.00166773 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + -1.24725e-08 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + -0.00185539 *begin_x*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 2.58744e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.0134847  + -0.00284866 *begin_lambda + 0.00204905 *lens_ipow(begin_lambda, 2) + 0.00164244 *lens_ipow(begin_dy, 2) + -9.56595e-05 *begin_y*begin_dy + 7.25361e-06 *lens_ipow(begin_y, 2) + -7.0817e-05 *begin_x*begin_dx + 2.39308e-06 *lens_ipow(begin_x, 2) + -0.00953099 *lens_ipow(begin_dx, 2)*begin_lambda + 0.000310351 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 7.42016e-09 *lens_ipow(begin_y, 4) + -0.000189681 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 1.87718e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 1.53483e-09 *lens_ipow(begin_x, 4) + 0.0245243 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -1.87088e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -0.0248135 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5) + -4.54591e-08 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_lambda + 3.44992e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy+0.0f;
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
  out[4] =  + 1.14869 *begin_lambda + -1.45304 *lens_ipow(begin_lambda, 2) + -1.74533e-06 *lens_ipow(begin_y, 2) + 1.04103 *lens_ipow(begin_lambda, 4) + -0.443343 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00386883 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00408317 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.000132568 *begin_x*begin_y*begin_dx*begin_dy + -3.8781e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000106576 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -9.63593e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -6.09343e-09 *lens_ipow(begin_x, 4) + -0.687862 *lens_ipow(begin_dy, 4)*begin_lambda + -0.705634 *lens_ipow(begin_dx, 4)*begin_lambda + -0.00732367 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -0.000147902 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0088917 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + -0.495279 *lens_ipow(begin_lambda, 6) + 0.461142 *lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + 0.480746 *lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2) + -1.35498e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -1.42459e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -1.63901e-06 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 3) + -6.5382e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.040532 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 4) + -3.32792e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + -2.49246e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -25.8418 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3);
else
  out[4] = 0.0f;
} break;
