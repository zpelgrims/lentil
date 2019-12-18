case nikon__retrofocus_wideangle__1971__18mm:
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
       + 23.6777 *begin_dx + 0.767079 *begin_x + -0.0268957 *begin_x*begin_lambda + 6.17727 *begin_dx*lens_ipow(begin_dy, 2) + 6.21552 *lens_ipow(begin_dx, 3) + 1.28056 *begin_y*begin_dx*begin_dy + 0.0376437 *lens_ipow(begin_y, 2)*begin_dx + 0.0178444 *begin_x*lens_ipow(begin_lambda, 2) + 0.793056 *begin_x*lens_ipow(begin_dy, 2) + 2.07123 *begin_x*lens_ipow(begin_dx, 2) + 0.0857218 *begin_x*begin_y*begin_dy + 0.00199391 *begin_x*lens_ipow(begin_y, 2) + 0.122466 *lens_ipow(begin_x, 2)*begin_dx + 0.00196572 *lens_ipow(begin_x, 3) + -0.932744 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -0.0203429 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + -0.0429042 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.000893076 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 6.79567e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 4.96732e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + 3.62668e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2) + 3.40153e-07 *lens_ipow(begin_x, 6)*begin_dx + 6.99584e-09 *lens_ipow(begin_x, 7) + 0.00105374 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.0388024 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.000146955 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -4.66581e-06 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.0144348 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 4),
       + 23.6918 *begin_dy + 0.764022 *begin_y + -0.0100602 *begin_y*begin_lambda + 5.95729 *lens_ipow(begin_dy, 3) + 6.52437 *lens_ipow(begin_dx, 2)*begin_dy + 2.02401 *begin_y*lens_ipow(begin_dy, 2) + 0.740725 *begin_y*lens_ipow(begin_dx, 2) + 0.119836 *lens_ipow(begin_y, 2)*begin_dy + 0.00191576 *lens_ipow(begin_y, 3) + 1.30319 *begin_x*begin_dx*begin_dy + 0.0817787 *begin_x*begin_y*begin_dx + 0.0378362 *lens_ipow(begin_x, 2)*begin_dy + 0.00190972 *lens_ipow(begin_x, 2)*begin_y + -0.0415398 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.0448266 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0045402 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.81186e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 55.1 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 2.97975e-07 *lens_ipow(begin_y, 6)*begin_dy + 9.04063e-09 *lens_ipow(begin_y, 7) + -0.000233597 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + 6.69182e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + 1.52186e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -0.37456 *begin_dy*lens_ipow(begin_lambda, 7) + -0.000204576 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 5) + -4.70675e-12 *lens_ipow(begin_y, 9) + 6.74734e-10 *lens_ipow(begin_x, 7)*begin_y*begin_dx + 2.06939e-11 *lens_ipow(begin_x, 8)*begin_y
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 23.6777  + 6.17727 *lens_ipow(begin_dy, 2) + 18.6466 *lens_ipow(begin_dx, 2) + 1.28056 *begin_y*begin_dy + 0.0376437 *lens_ipow(begin_y, 2) + 4.14246 *begin_x*begin_dx + 0.122466 *lens_ipow(begin_x, 2) + -3.73097 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.0813717 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.128713 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00267923 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 7.25336e-06 *lens_ipow(begin_x, 5)*begin_dx + 3.40153e-07 *lens_ipow(begin_x, 6) + 0.00105374 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.0388024 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.000440865 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -1.39974e-05 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(0, 1) =  + 12.3545 *begin_dx*begin_dy + 1.28056 *begin_y*begin_dx + 1.58611 *begin_x*begin_dy + 0.0857218 *begin_x*begin_y + -0.932744 *begin_x*begin_y*lens_ipow(begin_dx, 4) + -0.0429042 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3) + 9.93464e-06 *lens_ipow(begin_x, 5)*begin_dy + 0.00210748 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 0.116407 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000146955 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.0577393 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 4)+0.0f;
    dx1_domega0(1, 0) =  + 13.0487 *begin_dx*begin_dy + 1.48145 *begin_y*begin_dx + 1.30319 *begin_x*begin_dy + 0.0817787 *begin_x*begin_y + -0.0830795 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.0448266 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -0.0045402 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 220.4 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -0.00070079 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 6.69182e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 6.74734e-10 *lens_ipow(begin_x, 7)*begin_y+0.0f;
    dx1_domega0(1, 1) =  + 23.6918  + 17.8719 *lens_ipow(begin_dy, 2) + 6.52437 *lens_ipow(begin_dx, 2) + 4.04802 *begin_y*begin_dy + 0.119836 *lens_ipow(begin_y, 2) + 1.30319 *begin_x*begin_dx + 0.0378362 *lens_ipow(begin_x, 2) + -0.0415398 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0896533 *begin_x*begin_y*begin_dx*begin_dy + -0.0045402 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 165.3 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 2.97975e-07 *lens_ipow(begin_y, 6) + -0.37456 *lens_ipow(begin_lambda, 7) + -0.00102288 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 4)+0.0f;
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
    out(0) =  + 15.4646 *begin_dx + -0.160044 *begin_x + 10.3325 *begin_dx*begin_lambda + -14.2917 *begin_dx*lens_ipow(begin_lambda, 2) + -5.76141 *begin_dx*lens_ipow(begin_dy, 2) + 0.29956 *begin_y*begin_dx*begin_dy + 0.0276697 *lens_ipow(begin_y, 2)*begin_dx + 0.612015 *begin_x*lens_ipow(begin_dy, 2) + 1.63107 *begin_x*lens_ipow(begin_dx, 2) + 0.0478055 *begin_x*begin_y*begin_dy + 0.00186743 *begin_x*lens_ipow(begin_y, 2) + 0.104644 *lens_ipow(begin_x, 2)*begin_dx + 0.0022526 *lens_ipow(begin_x, 3) + 6.9205 *begin_dx*lens_ipow(begin_lambda, 3) + -10.4223 *lens_ipow(begin_dx, 3)*begin_lambda + -1.39524 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -0.0581866 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -0.000786052 *lens_ipow(begin_x, 3)*begin_lambda + -0.205298 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.0559907 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.00420018 *begin_x*begin_y*lens_ipow(begin_dy, 3) + -0.0848119 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.00296676 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.059667 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.00543352 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.00277114 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -0.000579311 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 2.60204e-07 *lens_ipow(begin_x, 5);
    out(1) =  + 15.537 *begin_dy + -0.15536 *begin_y + 10.2929 *begin_dy*begin_lambda + -0.00799896 *begin_y*begin_lambda + -14.543 *begin_dy*lens_ipow(begin_lambda, 2) + -5.64152 *lens_ipow(begin_dy, 3) + -6.00065 *lens_ipow(begin_dx, 2)*begin_dy + 0.869034 *begin_y*lens_ipow(begin_dy, 2) + 0.57695 *begin_y*lens_ipow(begin_dx, 2) + 0.0725489 *lens_ipow(begin_y, 2)*begin_dy + 0.00181249 *lens_ipow(begin_y, 3) + 0.237957 *begin_x*begin_dx*begin_dy + 0.0441562 *begin_x*begin_y*begin_dx + 0.0260706 *lens_ipow(begin_x, 2)*begin_dy + 0.00178 *lens_ipow(begin_x, 2)*begin_y + 7.07517 *begin_dy*lens_ipow(begin_lambda, 3) + -1.12335 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000587695 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00221895 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 2.71797e-07 *lens_ipow(begin_y, 5) + -0.155835 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00812805 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0532854 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.00208755 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 1.07876e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.000179742 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + 2.4936e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + 6.58275e-07 *lens_ipow(begin_x, 4)*begin_y;
    out(2) =  + -1.03521 *begin_dx + -0.0499329 *begin_x + 0.0101433 *begin_x*begin_lambda + -0.235099 *begin_dx*lens_ipow(begin_dy, 2) + 9.82253e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.006542 *begin_x*lens_ipow(begin_lambda, 2) + -0.0295855 *begin_x*lens_ipow(begin_dy, 2) + 0.0199315 *begin_x*lens_ipow(begin_dx, 2) + -0.00249575 *begin_x*begin_y*begin_dy + -4.36396e-05 *begin_x*lens_ipow(begin_y, 2) + 1.6229 *lens_ipow(begin_dx, 3)*begin_lambda + -0.00430175 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -7.73255e-05 *lens_ipow(begin_x, 3)*begin_lambda + 0.00167091 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.000164012 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -1.11938e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.0387146 *begin_dx*lens_ipow(begin_lambda, 6) + -3.52392 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4) + -8.26559e-06 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2) + 7.08904e-09 *lens_ipow(begin_y, 6)*begin_dx + -0.15954 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -2.54098e-10 *lens_ipow(begin_x, 7) + 6.96166e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 6) + -5.30174e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 3) + 7.62135e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 5) + -1.27245e-06 *begin_x*lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 4)*begin_dy + -1.17123e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 6) + 1.12766e-07 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 5);
    out(3) =  + -1.03646 *begin_dy + -0.0497363 *begin_y + 0.00914487 *begin_y*begin_lambda + 0.428438 *lens_ipow(begin_dy, 3) + 1.17043 *lens_ipow(begin_dx, 2)*begin_dy + -0.00558881 *begin_y*lens_ipow(begin_lambda, 2) + -0.0022701 *lens_ipow(begin_y, 2)*begin_dy + -3.5618e-05 *lens_ipow(begin_y, 3) + 0.0590055 *begin_x*begin_dx*begin_dy + -0.000400082 *begin_x*begin_y*begin_dx + 0.103336 *lens_ipow(begin_dy, 3)*begin_lambda + -0.0588882 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.00368144 *begin_x*begin_y*begin_dx*begin_lambda + -6.14547e-05 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -2.74825e-06 *lens_ipow(begin_y, 4)*begin_dy + -9.62115e-08 *lens_ipow(begin_y, 5) + -0.00721798 *begin_x*begin_y*lens_ipow(begin_dx, 3) + -0.000806033 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -3.1096e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -4.43445e-07 *lens_ipow(begin_x, 4)*begin_y + 0.000171435 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -1.01587e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -1.18928e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.123112 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -0.000255656 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 4) + 9.09791e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 5)*begin_lambda + -0.0179289 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6) + -0.000258442 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2);
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
    domega2_dx0(0, 0) =  + -0.0499329  + 0.0101433 *begin_lambda + -0.006542 *lens_ipow(begin_lambda, 2) + -0.0295855 *lens_ipow(begin_dy, 2) + 0.0199315 *lens_ipow(begin_dx, 2) + -0.00249575 *begin_y*begin_dy + -4.36396e-05 *lens_ipow(begin_y, 2) + -0.00860351 *begin_x*begin_dx*begin_lambda + -0.000231976 *lens_ipow(begin_x, 2)*begin_lambda + 0.00334182 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.000328025 *begin_x*begin_y*begin_dx*begin_dy + -3.35813e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.15954 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -1.77869e-09 *lens_ipow(begin_x, 6) + 0.00020885 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 6) + -3.18104e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 3) + -1.27245e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 4)*begin_dy + -5.85617e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + 6.76593e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 5)+0.0f;
    domega2_dx0(0, 1) =  + 0.000196451 *begin_y*begin_dx + -0.00249575 *begin_x*begin_dy + -8.72792e-05 *begin_x*begin_y + 0.000164012 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -2.23875e-07 *lens_ipow(begin_x, 3)*begin_y + -3.30624e-05 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 4.25342e-08 *lens_ipow(begin_y, 5)*begin_dx + 4.57281e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 5) + -6.36226e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 4)*begin_dy + -7.0274e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5)+0.0f;
    domega2_dx0(1, 0) =  + 0.0590055 *begin_dx*begin_dy + -0.000400082 *begin_y*begin_dx + -0.00368144 *begin_y*begin_dx*begin_lambda + -0.000122909 *begin_x*begin_y*begin_lambda + -0.00721798 *begin_y*lens_ipow(begin_dx, 3) + -0.00161207 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -9.32879e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -1.77378e-06 *lens_ipow(begin_x, 3)*begin_y + 0.000342869 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -2.03174e-07 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + -2.37856e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.123112 *begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -0.000255656 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 4) + 0.000363916 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 5)*begin_lambda + -0.000516884 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(1, 1) =  + -0.0497363  + 0.00914487 *begin_lambda + -0.00558881 *lens_ipow(begin_lambda, 2) + -0.0045402 *begin_y*begin_dy + -0.000106854 *lens_ipow(begin_y, 2) + -0.000400082 *begin_x*begin_dx + -0.0588882 *lens_ipow(begin_dx, 2)*begin_lambda + -0.00368144 *begin_x*begin_dx*begin_lambda + -6.14547e-05 *lens_ipow(begin_x, 2)*begin_lambda + -1.0993e-05 *lens_ipow(begin_y, 3)*begin_dy + -4.81057e-07 *lens_ipow(begin_y, 4) + -0.00721798 *begin_x*lens_ipow(begin_dx, 3) + -0.000806033 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -3.1096e-05 *lens_ipow(begin_x, 3)*begin_dx + -4.43445e-07 *lens_ipow(begin_x, 4) + 0.000171435 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -3.04761e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -3.56785e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000766967 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4) + -0.0537867 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6) + -0.000516884 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2)+0.0f;
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
  out[4] =  + 2.05257 *begin_lambda + -4.44414 *lens_ipow(begin_lambda, 2) + -0.00850174 *lens_ipow(begin_dy, 2) + 4.53259 *lens_ipow(begin_lambda, 3) + -1.79071 *lens_ipow(begin_lambda, 4) + -1.38897 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.66566 *lens_ipow(begin_dx, 4) + 0.000316298 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.250079 *begin_x*lens_ipow(begin_dx, 3) + 0.0017805 *begin_x*begin_y*begin_dx*begin_dy + -0.0105767 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -2.42293e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -2.1704e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.000253815 *lens_ipow(begin_x, 3)*begin_dx + -2.84469e-06 *lens_ipow(begin_x, 4) + -48.3734 *lens_ipow(begin_dy, 6) + -4.70422 *begin_y*lens_ipow(begin_dy, 5) + -0.133201 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -2.28588e-06 *lens_ipow(begin_y, 5)*begin_dy + -4.17858e-08 *lens_ipow(begin_y, 6) + -0.00132255 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -0.133427 *begin_y*lens_ipow(begin_dy, 7) + 0.976081 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 4.48671e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 2.49226e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 4) + -5.68651e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -7.18522e-10 *lens_ipow(begin_x, 7)*begin_dx + -2.04957e-11 *lens_ipow(begin_x, 8);
else
  out[4] = 0.0f;
} break;
