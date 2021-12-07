case zeiss__biotar__1927__65mm:
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
       + 39.4502 *begin_dx + 0.436185 *begin_x + 8.11669 *begin_dx*begin_lambda + 0.160606 *begin_x*begin_lambda + -5.58295 *begin_dx*lens_ipow(begin_lambda, 2) + -25.246 *begin_dx*lens_ipow(begin_dy, 2) + -24.9338 *lens_ipow(begin_dx, 3) + -0.212154 *begin_y*begin_dx*begin_dy + -0.000617063 *lens_ipow(begin_y, 2)*begin_dx + -0.111298 *begin_x*lens_ipow(begin_lambda, 2) + -0.211338 *begin_x*lens_ipow(begin_dy, 2) + -0.398444 *begin_x*lens_ipow(begin_dx, 2) + -0.0050129 *begin_x*begin_y*begin_dy + -0.000136241 *begin_x*lens_ipow(begin_y, 2) + -0.00297618 *lens_ipow(begin_x, 2)*begin_dx + -9.81026e-05 *lens_ipow(begin_x, 3) + -0.412554 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.0300327 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.28394e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -0.00044426 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.44832e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -1.49361e-05 *lens_ipow(begin_x, 4)*begin_dx + -1.69963e-07 *lens_ipow(begin_x, 5) + -1.9154e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3) + 4.8303 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -7.19451e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -6.26792e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -0.00772907 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2),
       + 39.44 *begin_dy + 0.435502 *begin_y + 8.11557 *begin_dy*begin_lambda + 0.162013 *begin_y*begin_lambda + -5.54718 *begin_dy*lens_ipow(begin_lambda, 2) + -24.7458 *lens_ipow(begin_dy, 3) + -25.7148 *lens_ipow(begin_dx, 2)*begin_dy + -0.111377 *begin_y*lens_ipow(begin_lambda, 2) + -0.394523 *begin_y*lens_ipow(begin_dy, 2) + -0.208154 *begin_y*lens_ipow(begin_dx, 2) + -0.00306299 *lens_ipow(begin_y, 2)*begin_dy + -9.98872e-05 *lens_ipow(begin_y, 3) + -0.232228 *begin_x*begin_dx*begin_dy + -0.00501307 *begin_x*begin_y*begin_dx + -0.000656839 *lens_ipow(begin_x, 2)*begin_dy + -0.000136724 *lens_ipow(begin_x, 2)*begin_y + -0.000444284 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -1.45394e-05 *lens_ipow(begin_y, 4)*begin_dy + -1.66671e-07 *lens_ipow(begin_y, 5) + 0.0338453 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00451619 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.0192562 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.20764e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -1.40737e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.000249073 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -3.09181e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -6.81701e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 0.015057 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 39.4502  + 8.11669 *begin_lambda + -5.58295 *lens_ipow(begin_lambda, 2) + -25.246 *lens_ipow(begin_dy, 2) + -74.8015 *lens_ipow(begin_dx, 2) + -0.212154 *begin_y*begin_dy + -0.000617063 *lens_ipow(begin_y, 2) + -0.796887 *begin_x*begin_dx + -0.00297618 *lens_ipow(begin_x, 2) + -0.412554 *begin_y*lens_ipow(begin_dy, 3) + 0.0600655 *begin_x*begin_y*begin_dx*begin_dy + -1.28394e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00088852 *lens_ipow(begin_x, 3)*begin_dx + -1.49361e-05 *lens_ipow(begin_x, 4) + -5.7462e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 9.6606 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.0154581 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(0, 1) =  + -50.4921 *begin_dx*begin_dy + -0.212154 *begin_y*begin_dx + -0.422675 *begin_x*begin_dy + -0.0050129 *begin_x*begin_y + -1.23766 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.0300327 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 19.3212 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -6.26792e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_lambda + -0.0154581 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 0) =  + -51.4296 *begin_dx*begin_dy + -0.416308 *begin_y*begin_dx + -0.232228 *begin_x*begin_dy + -0.00501307 *begin_x*begin_y + 0.0338453 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.0385124 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.000249073 *lens_ipow(begin_x, 3)*begin_dy + -3.09181e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 0.0602278 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 1) =  + 39.44  + 8.11557 *begin_lambda + -5.54718 *lens_ipow(begin_lambda, 2) + -74.2373 *lens_ipow(begin_dy, 2) + -25.7148 *lens_ipow(begin_dx, 2) + -0.789046 *begin_y*begin_dy + -0.00306299 *lens_ipow(begin_y, 2) + -0.232228 *begin_x*begin_dx + -0.000656839 *lens_ipow(begin_x, 2) + -0.000888568 *lens_ipow(begin_y, 3)*begin_dy + -1.45394e-05 *lens_ipow(begin_y, 4) + 0.0676905 *begin_x*begin_y*begin_dx*begin_dy + -0.0135486 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.0192562 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.20764e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.000249073 *lens_ipow(begin_x, 3)*begin_dx + 0.0301139 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4)*begin_dy+0.0f;
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
    out(0) =  + 64.3767 *begin_dx + 0.191737 *begin_x + 1.16729 *begin_dx*begin_lambda + 0.0661601 *begin_x*begin_lambda + -27.6186 *begin_dx*lens_ipow(begin_dy, 2) + -25.8465 *lens_ipow(begin_dx, 3) + 0.396334 *begin_y*begin_dx*begin_dy + 0.00657566 *lens_ipow(begin_y, 2)*begin_dx + 0.883576 *begin_x*lens_ipow(begin_dx, 2) + -0.000190697 *begin_x*lens_ipow(begin_y, 2) + 0.0196332 *lens_ipow(begin_x, 2)*begin_dx + -0.000121115 *lens_ipow(begin_x, 3) + 2.51073 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.0327412 *begin_x*begin_y*begin_dy*begin_lambda + -1.30423 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -2.13248 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.700146 *begin_x*lens_ipow(begin_dy, 4) + 2.26636 *begin_x*lens_ipow(begin_dx, 4) + 0.148678 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.00125879 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.20397 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.0037511 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -3.62018e-07 *lens_ipow(begin_x, 5) + 0.137163 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.00529671 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 0.00149768 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -8.16747e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -2.041e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4);
    out(1) =  + 64.8882 *begin_dy + 0.181475 *begin_y + 0.0650781 *begin_y*begin_lambda + -27.4286 *lens_ipow(begin_dy, 3) + -24.8592 *lens_ipow(begin_dx, 2)*begin_dy + 1.18351 *begin_y*lens_ipow(begin_dy, 2) + 0.747602 *begin_y*lens_ipow(begin_dx, 2) + 0.0262429 *lens_ipow(begin_y, 2)*begin_dy + 0.474421 *begin_x*begin_dx*begin_dy + 0.0222542 *begin_x*begin_y*begin_dx + 0.00872586 *lens_ipow(begin_x, 2)*begin_dy + -0.609336 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.174702 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.032193 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.00231342 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -2.61347e-05 *lens_ipow(begin_y, 4)*begin_dy + -5.85465e-07 *lens_ipow(begin_y, 5) + 0.0945208 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -4.18019e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -5.32706e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -1.20494e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -5.88229e-06 *lens_ipow(begin_x, 4)*begin_dy + -5.20772e-07 *lens_ipow(begin_x, 4)*begin_y + 4.64527 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.0571145 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -6.6065e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_lambda + 56.6316 *lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 2) + 0.0751999 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2);
    out(2) =  + -1.19982 *begin_dx + -0.0184927 *begin_x + -0.00328474 *begin_x*begin_lambda + 0.606473 *lens_ipow(begin_dx, 3) + -0.0109083 *begin_y*begin_dx*begin_dy + 5.27137e-05 *lens_ipow(begin_y, 2)*begin_dx + 0.00223705 *begin_x*lens_ipow(begin_lambda, 2) + -0.0148891 *begin_x*lens_ipow(begin_dy, 2) + -0.00483571 *begin_x*lens_ipow(begin_dx, 2) + -0.000271304 *begin_x*begin_y*begin_dy + 5.42725e-06 *begin_x*lens_ipow(begin_y, 2) + 5.56318e-06 *lens_ipow(begin_x, 3) + -0.441241 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.00116566 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 3.64016e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -0.000386979 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.00139607 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 2.0405e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 2.86711e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -0.0621033 *begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -0.000916617 *begin_x*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -0.00199526 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 8.35075e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dy*begin_lambda + -9.93281e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4) + 37.5502 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + 4.54998e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dx + 1.37685e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + 299.909 *lens_ipow(begin_dx, 9)*lens_ipow(begin_dy, 2);
    out(3) =  + -1.19504 *begin_dy + -0.0186865 *begin_y + -0.00286609 *begin_y*begin_lambda + 0.564321 *lens_ipow(begin_dy, 3) + 1.31388 *lens_ipow(begin_dx, 2)*begin_dy + 0.0021301 *begin_y*lens_ipow(begin_lambda, 2) + -0.00760933 *begin_y*lens_ipow(begin_dx, 2) + 5.9781e-06 *lens_ipow(begin_y, 3) + 0.0237108 *begin_x*begin_dx*begin_dy + -8.01681e-05 *begin_x*begin_y*begin_dx + 0.000149602 *lens_ipow(begin_x, 2)*begin_dy + 5.38553e-06 *lens_ipow(begin_x, 2)*begin_y + -1.42989e-06 *lens_ipow(begin_y, 3)*begin_lambda + 0.705387 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.0489788 *begin_y*lens_ipow(begin_dy, 4) + 0.0109239 *begin_y*lens_ipow(begin_dx, 4) + -0.00227191 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -2.76188e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -9.78559e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 1.79576e-09 *lens_ipow(begin_y, 5) + -0.00103026 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -6.87151e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 2.71198e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_lambda + -0.000963999 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 7.41308e-12 *lens_ipow(begin_x, 6)*begin_y + 4.30481e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy + 1.31821e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 1.36461e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5)*begin_dx;
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
    domega2_dx0(0, 0) =  + -0.0184927  + -0.00328474 *begin_lambda + 0.00223705 *lens_ipow(begin_lambda, 2) + -0.0148891 *lens_ipow(begin_dy, 2) + -0.00483571 *lens_ipow(begin_dx, 2) + -0.000271304 *begin_y*begin_dy + 5.42725e-06 *lens_ipow(begin_y, 2) + 1.66895e-05 *lens_ipow(begin_x, 2) + 3.64016e-07 *lens_ipow(begin_y, 3)*begin_dy + -0.000773958 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00279214 *begin_x*lens_ipow(begin_dx, 3) + 4.08101e-05 *begin_x*begin_y*begin_dx*begin_dy + 5.73422e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000916617 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -0.00199526 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 2.50522e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + -0.000297984 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + 1.81999e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx + 6.88425e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)+0.0f;
    domega2_dx0(0, 1) =  + -0.0109083 *begin_dx*begin_dy + 0.000105427 *begin_y*begin_dx + -0.000271304 *begin_x*begin_dy + 1.08545e-05 *begin_x*begin_y + -0.00233131 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 1.09205e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 2.0405e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 5.73422e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -0.0621033 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -0.000916617 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + -0.00199526 *begin_x*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 8.35075e-07 *lens_ipow(begin_x, 3)*begin_dy*begin_lambda + 1.81999e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx + 5.5074e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0237108 *begin_dx*begin_dy + -8.01681e-05 *begin_y*begin_dx + 0.000299204 *begin_x*begin_dy + 1.07711e-05 *begin_x*begin_y + -0.00103026 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -1.3743e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 8.13595e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + 4.44785e-11 *lens_ipow(begin_x, 5)*begin_y + 1.72192e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy + 5.27283e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + 6.82303e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_dx+0.0f;
    domega2_dx0(1, 1) =  + -0.0186865  + -0.00286609 *begin_lambda + 0.0021301 *lens_ipow(begin_lambda, 2) + -0.00760933 *lens_ipow(begin_dx, 2) + 1.79343e-05 *lens_ipow(begin_y, 2) + -8.01681e-05 *begin_x*begin_dx + 5.38553e-06 *lens_ipow(begin_x, 2) + -4.28966e-06 *lens_ipow(begin_y, 2)*begin_lambda + -0.0489788 *lens_ipow(begin_dy, 4) + 0.0109239 *lens_ipow(begin_dx, 4) + -0.00454383 *begin_y*lens_ipow(begin_dy, 3) + -8.28565e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -2.93568e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 8.9788e-09 *lens_ipow(begin_y, 4) + -0.00103026 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -6.87151e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 2.71198e-07 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -0.001928 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 7.41308e-12 *lens_ipow(begin_x, 6) + 1.72192e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + 6.59104e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 6.82303e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_dx+0.0f;
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
  out[4] =  + 0.446786  + 0.699498 *begin_lambda + -0.965043 *lens_ipow(begin_lambda, 2) + 0.000402576 *begin_y*begin_dy + -1.51713e-05 *lens_ipow(begin_x, 2) + 0.468723 *lens_ipow(begin_lambda, 3) + -0.750792 *lens_ipow(begin_dy, 4) + -1.91272 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.793913 *lens_ipow(begin_dx, 4) + -0.0530368 *begin_y*lens_ipow(begin_dy, 3) + -0.0505484 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0013785 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000428218 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -1.6159e-05 *lens_ipow(begin_y, 3)*begin_dy + -7.81263e-08 *lens_ipow(begin_y, 4) + -0.0502733 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0489009 *begin_x*lens_ipow(begin_dx, 3) + -0.00177587 *begin_x*begin_y*begin_dx*begin_dy + -1.39641e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000406246 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.00121555 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.27783e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.23823e-05 *lens_ipow(begin_x, 3)*begin_dx + -1.47238 *lens_ipow(begin_dy, 6) + -1.14855 *lens_ipow(begin_dx, 6) + -4.90664e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 1.2297e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy*begin_lambda + -37.3204 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4);
else
  out[4] = 0.0f;
} break;
