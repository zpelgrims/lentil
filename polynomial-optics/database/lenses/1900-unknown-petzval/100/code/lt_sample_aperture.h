case unknown__petzval__1900__100mm:
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
       + 73.7384 *begin_dx + 0.728176 *begin_x + 19.2294 *begin_dx*begin_lambda + 0.301287 *begin_x*begin_lambda + -26.6564 *begin_dx*lens_ipow(begin_lambda, 2) + 0.513367 *begin_y*begin_dx*begin_dy + 0.00575368 *lens_ipow(begin_y, 2)*begin_dx + -0.419986 *begin_x*lens_ipow(begin_lambda, 2) + 0.114331 *begin_x*lens_ipow(begin_dy, 2) + 0.607287 *begin_x*lens_ipow(begin_dx, 2) + 0.00852689 *begin_x*begin_y*begin_dy + 6.55281e-05 *begin_x*lens_ipow(begin_y, 2) + 0.0135836 *lens_ipow(begin_x, 2)*begin_dx + 5.93305e-05 *lens_ipow(begin_x, 3) + 12.9936 *begin_dx*lens_ipow(begin_lambda, 3) + 0.205197 *begin_x*lens_ipow(begin_lambda, 3) + 4.81507e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 4.99191e-06 *lens_ipow(begin_x, 3)*begin_lambda + 0.161841 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 1.01751e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.000298892 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 7.02416e-06 *lens_ipow(begin_x, 4)*begin_dx + 4.08147e-08 *lens_ipow(begin_x, 5) + -0.194778 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 4.76247e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 9.52937e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.9666e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 2.40067e-15 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 4),
       + 73.7379 *begin_dy + 0.727939 *begin_y + 19.2421 *begin_dy*begin_lambda + 0.301908 *begin_y*begin_lambda + -26.661 *begin_dy*lens_ipow(begin_lambda, 2) + -0.420129 *begin_y*lens_ipow(begin_lambda, 2) + 0.600997 *begin_y*lens_ipow(begin_dy, 2) + 0.112726 *begin_y*lens_ipow(begin_dx, 2) + 0.0133571 *lens_ipow(begin_y, 2)*begin_dy + 5.97218e-05 *lens_ipow(begin_y, 3) + 0.513253 *begin_x*begin_dx*begin_dy + 0.00845785 *begin_x*begin_y*begin_dx + 0.00572558 *lens_ipow(begin_x, 2)*begin_dy + 6.63926e-05 *lens_ipow(begin_x, 2)*begin_y + 12.9868 *begin_dy*lens_ipow(begin_lambda, 3) + 0.205436 *begin_y*lens_ipow(begin_lambda, 3) + -23.8508 *lens_ipow(begin_dy, 5) + -0.925979 *begin_y*lens_ipow(begin_dy, 4) + 0.000611558 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 1.15445e-05 *lens_ipow(begin_y, 4)*begin_dy + 6.21799e-08 *lens_ipow(begin_y, 5) + -2.327e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 9.28307e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 6.14422e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 2.30575e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 258.305 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4) + -1.15835e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 3.95343e-16 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 73.7384  + 19.2294 *begin_lambda + -26.6564 *lens_ipow(begin_lambda, 2) + 0.513367 *begin_y*begin_dy + 0.00575368 *lens_ipow(begin_y, 2) + 1.21457 *begin_x*begin_dx + 0.0135836 *lens_ipow(begin_x, 2) + 12.9936 *lens_ipow(begin_lambda, 3) + 0.485524 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.01751e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.000597785 *lens_ipow(begin_x, 3)*begin_dx + 7.02416e-06 *lens_ipow(begin_x, 4) + -0.779111 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + 1.90587e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -2.9666e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + 0.513367 *begin_y*begin_dx + 0.228662 *begin_x*begin_dy + 0.00852689 *begin_x*begin_y + 0.161841 *begin_y*lens_ipow(begin_dx, 3) + 4.76247e-07 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + 1.90587e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -2.9666e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx+0.0f;
    dx1_domega0(1, 0) =  + 0.225452 *begin_y*begin_dx + 0.513253 *begin_x*begin_dy + 0.00845785 *begin_x*begin_y + 9.28307e-07 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + 1033.22 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + -2.31669e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 1) =  + 73.7379  + 19.2421 *begin_lambda + -26.661 *lens_ipow(begin_lambda, 2) + 1.20199 *begin_y*begin_dy + 0.0133571 *lens_ipow(begin_y, 2) + 0.513253 *begin_x*begin_dx + 0.00572558 *lens_ipow(begin_x, 2) + 12.9868 *lens_ipow(begin_lambda, 3) + -119.254 *lens_ipow(begin_dy, 4) + -3.70391 *begin_y*lens_ipow(begin_dy, 3) + 0.00122312 *lens_ipow(begin_y, 3)*begin_dy + 1.15445e-05 *lens_ipow(begin_y, 4) + 2.30575e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 1033.22 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -2.31669e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy+0.0f;
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
    out(0) =  + 90.6531 *begin_dx + 0.4524 *begin_x + 37.4278 *begin_dx*begin_lambda + 0.601095 *begin_x*begin_lambda + -51.7994 *begin_dx*lens_ipow(begin_lambda, 2) + -64.9442 *begin_dx*lens_ipow(begin_dy, 2) + -66.6762 *lens_ipow(begin_dx, 3) + 0.00645309 *lens_ipow(begin_y, 2)*begin_dx + -0.834825 *begin_x*lens_ipow(begin_lambda, 2) + 0.415465 *begin_x*lens_ipow(begin_dy, 2) + 0.326509 *begin_x*lens_ipow(begin_dx, 2) + 0.0184585 *begin_x*begin_y*begin_dy + 0.000132629 *begin_x*lens_ipow(begin_y, 2) + 0.0227063 *lens_ipow(begin_x, 2)*begin_dx + 0.000115526 *lens_ipow(begin_x, 3) + 25.2017 *begin_dx*lens_ipow(begin_lambda, 3) + 0.407414 *begin_x*lens_ipow(begin_lambda, 3) + -1.16563 *begin_x*lens_ipow(begin_dx, 4) + -0.0222499 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 4.93253e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.0012779 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 2.41732e-05 *lens_ipow(begin_x, 4)*begin_dx + 1.27477e-07 *lens_ipow(begin_x, 5) + 70.9026 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 3.08962e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 1.86528e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 5.05386e-11 *lens_ipow(begin_x, 7)*begin_y*begin_dy + 4.52381e-12 *lens_ipow(begin_x, 9)*lens_ipow(begin_dy, 2);
    out(1) =  + 90.6436 *begin_dy + 0.452848 *begin_y + 37.4646 *begin_dy*begin_lambda + 0.598858 *begin_y*begin_lambda + -51.8916 *begin_dy*lens_ipow(begin_lambda, 2) + -66.4367 *lens_ipow(begin_dy, 3) + -65.0089 *lens_ipow(begin_dx, 2)*begin_dy + -0.831154 *begin_y*lens_ipow(begin_lambda, 2) + 0.323803 *begin_y*lens_ipow(begin_dy, 2) + 0.409423 *begin_y*lens_ipow(begin_dx, 2) + 0.0227366 *lens_ipow(begin_y, 2)*begin_dy + 0.000115771 *lens_ipow(begin_y, 3) + 0.0182343 *begin_x*begin_y*begin_dx + 0.00652758 *lens_ipow(begin_x, 2)*begin_dy + 0.000131033 *lens_ipow(begin_x, 2)*begin_y + 25.2777 *begin_dy*lens_ipow(begin_lambda, 3) + 0.405522 *begin_y*lens_ipow(begin_lambda, 3) + 0.0501809 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00201348 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 2.76212e-05 *lens_ipow(begin_y, 4)*begin_dy + 1.3031e-07 *lens_ipow(begin_y, 5) + -0.228215 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + 1.13443e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 1106.68 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5)*begin_lambda + 1.18081e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_lambda + 1.64171e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.87932e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx*begin_dy + 3.865e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7);
    out(2) =  + -1.6662 *begin_dx + -0.0195467 *begin_x + 0.218846 *begin_dx*begin_lambda + -0.000494585 *begin_x*begin_lambda + -0.32161 *begin_dx*lens_ipow(begin_lambda, 2) + -1.22128 *begin_dx*lens_ipow(begin_dy, 2) + 0.983664 *lens_ipow(begin_dx, 3) + -0.0308055 *begin_y*begin_dx*begin_dy + -0.000159033 *lens_ipow(begin_y, 2)*begin_dx + 0.000368155 *begin_x*lens_ipow(begin_lambda, 2) + -0.0219661 *begin_x*lens_ipow(begin_dy, 2) + -0.000481324 *begin_x*begin_y*begin_dy + -1.77814e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000244163 *lens_ipow(begin_x, 2)*begin_dx + -8.31379e-07 *lens_ipow(begin_x, 3) + 0.168836 *begin_dx*lens_ipow(begin_lambda, 3) + -0.197943 *lens_ipow(begin_dx, 3)*begin_lambda + -0.00187141 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 5.6039 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 1.17423 *lens_ipow(begin_dx, 5) + 0.0213212 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.0397705 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.37372e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 34.22 *begin_dx*lens_ipow(begin_dy, 6) + -4.8474e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -0.0088673 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -0.0360702 *begin_x*begin_y*lens_ipow(begin_dy, 7) + -1.72506e-07 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 4)*begin_lambda;
    out(3) =  + -1.62721 *begin_dy + -0.0194426 *begin_y + 0.0220237 *begin_dy*begin_lambda + -0.000893952 *begin_y*begin_lambda + 0.919551 *lens_ipow(begin_dy, 3) + 0.000740008 *begin_y*lens_ipow(begin_lambda, 2) + -0.000243159 *lens_ipow(begin_y, 2)*begin_dy + -8.11383e-07 *lens_ipow(begin_y, 3) + 1.78469e-07 *lens_ipow(begin_x, 2)*begin_y + 13.5855 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.00210167 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0153558 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.204459 *begin_x*begin_dx*begin_dy*begin_lambda + 0.000448851 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -0.193811 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 1.38163 *lens_ipow(begin_dy, 5) + -16.1488 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 2.53206 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.0146515 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.000123213 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.22777 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.0175996 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.000183951 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -1.69181e-08 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -0.00145596 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 4) + 8.06191 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 5) + 0.134538 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 6) + 0.00166866 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 6);
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
    domega2_dx0(0, 0) =  + -0.0195467  + -0.000494585 *begin_lambda + 0.000368155 *lens_ipow(begin_lambda, 2) + -0.0219661 *lens_ipow(begin_dy, 2) + -0.000481324 *begin_y*begin_dy + -1.77814e-06 *lens_ipow(begin_y, 2) + -0.000488325 *begin_x*begin_dx + -2.49414e-06 *lens_ipow(begin_x, 2) + -0.00187141 *lens_ipow(begin_dx, 2)*begin_lambda + 0.0397705 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 4.12115e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.45422e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -0.0360702 *begin_y*lens_ipow(begin_dy, 7) + -1.72506e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 4)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -0.0308055 *begin_dx*begin_dy + -0.000318066 *begin_y*begin_dx + -0.000481324 *begin_x*begin_dy + -3.55628e-06 *begin_x*begin_y + 0.0213212 *lens_ipow(begin_dx, 3)*begin_dy + -9.6948e-10 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_lambda, 2) + -0.0177346 *begin_y*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -0.0360702 *begin_x*lens_ipow(begin_dy, 7) + -6.90025e-07 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4)*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 3.56938e-07 *begin_x*begin_y + 0.204459 *begin_dx*begin_dy*begin_lambda + 0.000897703 *begin_x*begin_dy*begin_lambda + -0.22777 *begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.0175996 *lens_ipow(begin_dx, 3)*begin_dy + -0.000183951 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -5.07542e-08 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -0.00291191 *begin_x*begin_dy*lens_ipow(begin_lambda, 4) + 0.134538 *begin_dx*begin_dy*lens_ipow(begin_lambda, 6) + 0.00333732 *begin_x*begin_dy*lens_ipow(begin_lambda, 6)+0.0f;
    domega2_dx0(1, 1) =  + -0.0194426  + -0.000893952 *begin_lambda + 0.000740008 *lens_ipow(begin_lambda, 2) + -0.000486318 *begin_y*begin_dy + -2.43415e-06 *lens_ipow(begin_y, 2) + 1.78469e-07 *lens_ipow(begin_x, 2) + -0.00210167 *lens_ipow(begin_dy, 2)*begin_lambda + 0.0153558 *lens_ipow(begin_dx, 2)*begin_lambda + -0.0146515 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.000246426 *begin_y*lens_ipow(begin_dy, 3) + -0.000183951 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -1.69181e-08 *lens_ipow(begin_x, 3)*begin_dx+0.0f;
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
  out[4] =  + 0.592683  + 0.846588 *begin_lambda + -1.76853 *lens_ipow(begin_lambda, 2) + 6.54142e-07 *lens_ipow(begin_y, 2) + 1.73653 *lens_ipow(begin_lambda, 3) + -0.660535 *lens_ipow(begin_lambda, 4) + -0.162475 *lens_ipow(begin_dx, 4) + -0.000200918 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -5.90471e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -6.33657e-06 *lens_ipow(begin_y, 3)*begin_dy + -5.72927e-08 *lens_ipow(begin_y, 4) + -0.00934463 *begin_x*lens_ipow(begin_dx, 3) + -0.000246545 *begin_x*begin_y*begin_dx*begin_dy + -5.82705e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -7.05523e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000375638 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -6.0599e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.13533e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -7.46046e-06 *lens_ipow(begin_x, 3)*begin_dx + -5.12277e-08 *lens_ipow(begin_x, 4) + 1.2056e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -2.76727e-11 *lens_ipow(begin_x, 6) + 9.75932e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + 1.70059e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -2.64881e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -3.10548e-12 *lens_ipow(begin_x, 7)*begin_dx + -6.81819e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.07585e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2);
else
  out[4] = 0.0f;
} break;
