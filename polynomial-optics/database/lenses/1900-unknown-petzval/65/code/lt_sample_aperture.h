case unknown__petzval__1900__65mm:
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
       + 49.5899 *begin_dx + 0.759924 *begin_x + 3.1298 *begin_dx*begin_lambda + 0.120695 *begin_x*begin_lambda + 0.515988 *begin_y*begin_dx*begin_dy + 0.00889992 *lens_ipow(begin_y, 2)*begin_dx + -0.0835724 *begin_x*lens_ipow(begin_lambda, 2) + 0.11357 *begin_x*lens_ipow(begin_dy, 2) + 0.604841 *begin_x*lens_ipow(begin_dx, 2) + 0.0129187 *begin_x*begin_y*begin_dy + 0.000157296 *begin_x*lens_ipow(begin_y, 2) + 0.0208795 *lens_ipow(begin_x, 2)*begin_dx + 0.000141571 *lens_ipow(begin_x, 3) + -2.06405 *begin_dx*lens_ipow(begin_lambda, 3) + 7.92678e-06 *lens_ipow(begin_x, 3)*begin_lambda + -7.7508e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.000564161 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 2.35158e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 2.33614e-05 *lens_ipow(begin_x, 4)*begin_dx + 2.31805e-07 *lens_ipow(begin_x, 5) + 1.72681e-08 *begin_x*lens_ipow(begin_y, 4)*begin_lambda + 5.20658 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -6.40788e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda + 1.59467e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_lambda + -2803.02 *lens_ipow(begin_dx, 7)*lens_ipow(begin_dy, 2) + 0.00639312 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.000657857 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 4)*begin_dy + 9.15569e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2),
       + 49.5894 *begin_dy + 0.760162 *begin_y + 3.13797 *begin_dy*begin_lambda + 0.119797 *begin_y*begin_lambda + -0.0827452 *begin_y*lens_ipow(begin_lambda, 2) + 0.610543 *begin_y*lens_ipow(begin_dy, 2) + 0.113264 *begin_y*lens_ipow(begin_dx, 2) + 0.0210479 *lens_ipow(begin_y, 2)*begin_dy + 0.000146743 *lens_ipow(begin_y, 3) + 0.516508 *begin_x*begin_dx*begin_dy + 0.0130752 *begin_x*begin_y*begin_dx + 0.00891991 *lens_ipow(begin_x, 2)*begin_dy + 0.000158792 *lens_ipow(begin_x, 2)*begin_y + -2.09263 *begin_dy*lens_ipow(begin_lambda, 3) + -8.32987e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -3.61459e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + 0.00129551 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 4.43484e-05 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 4.2646e-07 *lens_ipow(begin_y, 5)*begin_lambda + 5.18524 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 8.30028e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 13.0196 *lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 3) + -3.17047e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -0.707244 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 1.60095e-12 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7) + 2.18183e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + 0.000456485 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 1.34678e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8)*begin_dy
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 49.5899  + 3.1298 *begin_lambda + 0.515988 *begin_y*begin_dy + 0.00889992 *lens_ipow(begin_y, 2) + 1.20968 *begin_x*begin_dx + 0.0208795 *lens_ipow(begin_x, 2) + -2.06405 *lens_ipow(begin_lambda, 3) + 0.00112832 *lens_ipow(begin_x, 3)*begin_dx + 2.33614e-05 *lens_ipow(begin_x, 4) + 10.4132 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -6.40788e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -19621.2 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + 0.0127862 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.00263143 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + 0.515988 *begin_y*begin_dx + 0.22714 *begin_x*begin_dy + 0.0129187 *begin_x*begin_y + -0.000155016 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 2.35158e-06 *lens_ipow(begin_x, 3)*begin_y + 20.8263 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -6.40788e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -5606.04 *lens_ipow(begin_dx, 7)*begin_dy + 0.0127862 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.000657857 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 4)+0.0f;
    dx1_domega0(1, 0) =  + 0.226527 *begin_y*begin_dx + 0.516508 *begin_x*begin_dy + 0.0130752 *begin_x*begin_y + -7.22917e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 10.3705 *begin_y*begin_dx*lens_ipow(begin_dy, 4) + 8.30028e-05 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -3.17047e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -2.12173 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.00091297 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0(1, 1) =  + 49.5894  + 3.13797 *begin_lambda + 1.22109 *begin_y*begin_dy + 0.0210479 *lens_ipow(begin_y, 2) + 0.516508 *begin_x*begin_dx + 0.00891991 *lens_ipow(begin_x, 2) + -2.09263 *lens_ipow(begin_lambda, 3) + -0.000166597 *lens_ipow(begin_y, 3)*begin_dy + 0.00259103 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 4.43484e-05 *lens_ipow(begin_y, 4)*begin_lambda + 20.7409 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.000166006 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 65.0978 *lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3) + -3.17047e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.41449 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2) + 0.000456485 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 1.34678e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8)+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 58.9159 *begin_dx + 0.451516 *begin_x + 24.2712 *begin_dx*begin_lambda + 0.606186 *begin_x*begin_lambda + -33.5079 *begin_dx*lens_ipow(begin_lambda, 2) + -42.3734 *begin_dx*lens_ipow(begin_dy, 2) + -42.3598 *lens_ipow(begin_dx, 3) + 0.0101398 *lens_ipow(begin_y, 2)*begin_dx + -0.846398 *begin_x*lens_ipow(begin_lambda, 2) + 0.410811 *begin_x*lens_ipow(begin_dy, 2) + 0.40855 *begin_x*lens_ipow(begin_dx, 2) + 0.028177 *begin_x*begin_y*begin_dy + 0.00030757 *begin_x*lens_ipow(begin_y, 2) + 0.0379138 *lens_ipow(begin_x, 2)*begin_dx + 0.000298891 *lens_ipow(begin_x, 3) + 16.2511 *begin_dx*lens_ipow(begin_lambda, 3) + 0.41458 *begin_x*lens_ipow(begin_lambda, 3) + 1.14933e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 1.72424e-05 *lens_ipow(begin_x, 3)*begin_lambda + -9.88251e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 305.635 *lens_ipow(begin_dx, 7)*lens_ipow(begin_lambda, 2) + -1.64195e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 4) + 3.6474e-05 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 1.24525e-06 *lens_ipow(begin_x, 6)*begin_dx*lens_ipow(begin_lambda, 3) + 1.11461e-08 *lens_ipow(begin_x, 7)*lens_ipow(begin_lambda, 3) + 0.00122575 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 1.56015e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + 5.22895e-14 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 4);
    out(1) =  + 59.5458 *begin_dy + 0.45251 *begin_y + 19.4711 *begin_dy*begin_lambda + 0.598958 *begin_y*begin_lambda + -20.1758 *begin_dy*lens_ipow(begin_lambda, 2) + -41.8387 *lens_ipow(begin_dy, 3) + -42.3647 *lens_ipow(begin_dx, 2)*begin_dy + -0.831557 *begin_y*lens_ipow(begin_lambda, 2) + 0.434385 *begin_y*lens_ipow(begin_dy, 2) + 0.406588 *begin_y*lens_ipow(begin_dx, 2) + 0.0386758 *lens_ipow(begin_y, 2)*begin_dy + 0.000306911 *lens_ipow(begin_y, 3) + 0.0280036 *begin_x*begin_y*begin_dx + 0.0101443 *lens_ipow(begin_x, 2)*begin_dy + 0.000306663 *lens_ipow(begin_x, 2)*begin_y + 0.404997 *begin_y*lens_ipow(begin_lambda, 3) + 1.63414e-05 *lens_ipow(begin_y, 3)*begin_lambda + 7.72501e-06 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 7.35573 *begin_dy*lens_ipow(begin_lambda, 4) + 0.0070879 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 4) + -9.80444 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5) + -0.20884 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 6.72541e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -5.30135e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 1.05635e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 2.07365e-11 *lens_ipow(begin_y, 9)*lens_ipow(begin_dx, 2) + -5.48156e-08 *begin_x*lens_ipow(begin_y, 6)*begin_dx*lens_ipow(begin_dy, 3) + 2.77132e-15 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 9);
    out(2) =  + -1.64603 *begin_dx + -0.0302104 *begin_x + 0.0964454 *begin_dx*begin_lambda + -0.00018288 *begin_x*begin_lambda + -0.0719471 *begin_dx*lens_ipow(begin_lambda, 2) + -1.13404 *begin_dx*lens_ipow(begin_dy, 2) + -0.04681 *begin_y*begin_dx*begin_dy + -0.000388871 *lens_ipow(begin_y, 2)*begin_dx + -0.0333787 *begin_x*lens_ipow(begin_dy, 2) + -0.00114565 *begin_x*begin_y*begin_dy + -6.72865e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000433214 *lens_ipow(begin_x, 2)*begin_dx + 5.96666 *lens_ipow(begin_dx, 3)*begin_lambda + -0.000484462 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -9.65263e-06 *lens_ipow(begin_x, 3)*begin_lambda + -12.9845 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 1.09993 *lens_ipow(begin_dx, 5) + -0.0102283 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.0191766 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.000177631 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 9.09743 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + 1.12376e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + 3.47189 *begin_dx*lens_ipow(begin_dy, 6) + 0.00132838 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 5) + 1875.21 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 4) + 0.0864011 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 6) + -1.0447 *begin_x*begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 0.000153859 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2);
    out(3) =  + -1.65429 *begin_dy + -0.0303047 *begin_y + 0.122283 *begin_dy*begin_lambda + -0.0903359 *begin_dy*lens_ipow(begin_lambda, 2) + 3.06533 *lens_ipow(begin_dx, 2)*begin_dy + 0.00632751 *begin_y*lens_ipow(begin_dx, 2) + 6.16859e-06 *lens_ipow(begin_y, 3) + 0.0722633 *begin_x*begin_dx*begin_dy + 0.000374548 *lens_ipow(begin_x, 2)*begin_dy + 1.15173e-06 *lens_ipow(begin_x, 2)*begin_y + 6.90107 *lens_ipow(begin_dy, 3)*begin_lambda + -0.14441 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.0591995 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.00147857 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -3.37884e-05 *lens_ipow(begin_y, 3)*begin_lambda + -7.21802e-07 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -16.3305 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 1.90232 *lens_ipow(begin_dy, 5) + 2.38064 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.866637 *lens_ipow(begin_dx, 4)*begin_dy + -0.179209 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.023436 *begin_y*lens_ipow(begin_dy, 4) + 2.99721e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -0.000322478 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 11.8174 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -0.000277807 *begin_y*lens_ipow(begin_lambda, 6) + 0.194514 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 0.00206992 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 4);
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
    domega2_dx0(0, 0) =  + -0.0302104  + -0.00018288 *begin_lambda + -0.0333787 *lens_ipow(begin_dy, 2) + -0.00114565 *begin_y*begin_dy + -6.72865e-06 *lens_ipow(begin_y, 2) + -0.000866427 *begin_x*begin_dx + -0.000968924 *begin_x*begin_dx*begin_lambda + -2.89579e-05 *lens_ipow(begin_x, 2)*begin_lambda + -0.0191766 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.000355262 *begin_x*lens_ipow(begin_dx, 3) + 3.37128e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + 0.00265676 *begin_x*begin_dx*lens_ipow(begin_lambda, 5) + 0.0864011 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 6) + -1.0447 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 0.000307717 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(0, 1) =  + -0.04681 *begin_dx*begin_dy + -0.000777743 *begin_y*begin_dx + -0.00114565 *begin_x*begin_dy + -1.34573e-05 *begin_x*begin_y + -0.0102283 *lens_ipow(begin_dx, 3)*begin_dy + -1.0447 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 0.000307717 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(1, 0) =  + 0.0722633 *begin_dx*begin_dy + 0.000749095 *begin_x*begin_dy + 2.30345e-06 *begin_x*begin_y + -1.4436e-06 *begin_x*begin_y*begin_lambda + -0.000322478 *begin_y*begin_dx*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(1, 1) =  + -0.0303047  + 0.00632751 *lens_ipow(begin_dx, 2) + 1.85058e-05 *lens_ipow(begin_y, 2) + 1.15173e-06 *lens_ipow(begin_x, 2) + 0.0591995 *lens_ipow(begin_dy, 2)*begin_lambda + -0.00295714 *begin_y*begin_dy*begin_lambda + -0.000101365 *lens_ipow(begin_y, 2)*begin_lambda + -7.21802e-07 *lens_ipow(begin_x, 2)*begin_lambda + -0.179209 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.023436 *lens_ipow(begin_dy, 4) + 8.99164e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -0.000322478 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.000277807 *lens_ipow(begin_lambda, 6) + 0.194514 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 0.00413984 *begin_y*begin_dy*lens_ipow(begin_lambda, 4)+0.0f;
    Eigen::Matrix2d invJ = domega2_dx0.inverse().eval();
    Eigen::Vector2d solution_pos = 0.72 * invJ * delta_out; // default newton-raphson
    x += solution_pos(0);
    y += solution_pos(1);
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
  out[4] =  + 0.59215  + 0.849799 *begin_lambda + -1.77608 *lens_ipow(begin_lambda, 2) + 1.74456 *lens_ipow(begin_lambda, 3) + -0.000326418 *begin_x*begin_dx*begin_lambda + -0.663814 *lens_ipow(begin_lambda, 4) + -0.000475852 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000195447 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.29926e-05 *lens_ipow(begin_y, 3)*begin_dy + -2.78417e-07 *lens_ipow(begin_y, 4) + -0.0006459 *begin_x*begin_y*begin_dx*begin_dy + -2.56937e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000157984 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -2.39918e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -6.94809e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.13419e-07 *lens_ipow(begin_x, 4) + -0.212813 *lens_ipow(begin_dx, 4)*begin_lambda + -2.46424e-10 *lens_ipow(begin_y, 6) + -1.25235e-07 *lens_ipow(begin_x, 5)*begin_dx + -1.40241e-09 *lens_ipow(begin_x, 6) + 1.15543e-09 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 2) + 6.77404e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 3) + 0.0913731 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 8) + -3.50512e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_dy + 1.38336e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx + -8.21108e-10 *lens_ipow(begin_x, 7)*lens_ipow(begin_dx, 3) + -3.31852e-15 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2) + 4.14385e-08 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda;
else
  out[4] = 0.0f;
} break;
