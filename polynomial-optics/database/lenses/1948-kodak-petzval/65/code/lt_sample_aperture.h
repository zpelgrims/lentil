case kodak__petzval__1948__65mm:
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
       + 49.8357 *begin_dx + 0.793548 *begin_x + 0.791318 *begin_dx*begin_lambda + -0.00151901 *begin_x*begin_lambda + -0.577759 *begin_dx*lens_ipow(begin_lambda, 2) + 0.512329 *begin_y*begin_dx*begin_dy + 0.00810194 *lens_ipow(begin_y, 2)*begin_dx + 0.100015 *begin_x*lens_ipow(begin_dy, 2) + 0.571734 *begin_x*lens_ipow(begin_dx, 2) + 0.011248 *begin_x*begin_y*begin_dy + 0.000113484 *begin_x*lens_ipow(begin_y, 2) + 0.0170971 *lens_ipow(begin_x, 2)*begin_dx + 8.34546e-05 *lens_ipow(begin_x, 3) + 27.5173 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.039681 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.000461425 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 1.62897e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 1.18569e-07 *begin_x*lens_ipow(begin_y, 4) + 0.0424619 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 1.89441e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.000323218 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.00293363 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 1.94167e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 3.65412e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 6.60368e-05 *lens_ipow(begin_x, 4)*begin_dx + 4.70589e-07 *lens_ipow(begin_x, 5) + 0.0187018 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*begin_lambda + -6.36602e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx*begin_dy,
       + 49.8145 *begin_dy + 0.793134 *begin_y + 0.782763 *begin_dy*begin_lambda + -0.00173041 *begin_y*begin_lambda + -0.569979 *begin_dy*lens_ipow(begin_lambda, 2) + 1.8223 *lens_ipow(begin_dx, 2)*begin_dy + 0.540615 *begin_y*lens_ipow(begin_dy, 2) + 0.143649 *begin_y*lens_ipow(begin_dx, 2) + 0.016552 *lens_ipow(begin_y, 2)*begin_dy + 8.64649e-05 *lens_ipow(begin_y, 3) + 0.564544 *begin_x*begin_dx*begin_dy + 0.0129486 *begin_x*begin_y*begin_dx + 0.008746 *lens_ipow(begin_x, 2)*begin_dy + 0.00013555 *lens_ipow(begin_x, 2)*begin_y + 14.8466 *lens_ipow(begin_dy, 5) + 2.28976 *begin_y*lens_ipow(begin_dy, 4) + 0.148822 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00507292 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 8.44335e-05 *lens_ipow(begin_y, 4)*begin_dy + 5.10374e-07 *lens_ipow(begin_y, 5) + 0.00018379 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 7.31837e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.327032 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 5.28801e-09 *lens_ipow(begin_x, 5)*begin_y*begin_dx + -347.529 *lens_ipow(begin_dx, 8)*begin_dy + 3.66578e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.26265e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 3.3364e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 49.8357  + 0.791318 *begin_lambda + -0.577759 *lens_ipow(begin_lambda, 2) + 0.512329 *begin_y*begin_dy + 0.00810194 *lens_ipow(begin_y, 2) + 1.14347 *begin_x*begin_dx + 0.0170971 *lens_ipow(begin_x, 2) + 82.552 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0793619 *begin_x*begin_y*begin_dx*begin_dy + 0.127386 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 1.89441e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.00586726 *lens_ipow(begin_x, 3)*begin_dx + 6.60368e-05 *lens_ipow(begin_x, 4) + 0.0561053 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -6.36602e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + 0.512329 *begin_y*begin_dx + 0.20003 *begin_x*begin_dy + 0.011248 *begin_x*begin_y + 55.0347 *lens_ipow(begin_dx, 3)*begin_dy + -0.039681 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 0.000922851 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 1.62897e-05 *begin_x*lens_ipow(begin_y, 3) + 0.000646435 *lens_ipow(begin_x, 3)*begin_dy + 1.94167e-05 *lens_ipow(begin_x, 3)*begin_y + 0.0561053 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -6.36602e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx+0.0f;
    dx1_domega0(1, 0) =  + 3.6446 *begin_dx*begin_dy + 0.287298 *begin_y*begin_dx + 0.564544 *begin_x*begin_dy + 0.0129486 *begin_x*begin_y + 0.654063 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 5.28801e-09 *lens_ipow(begin_x, 5)*begin_y + -2780.23 *lens_ipow(begin_dx, 7)*begin_dy + 7.33156e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + -2.26265e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 49.8145  + 0.782763 *begin_lambda + -0.569979 *lens_ipow(begin_lambda, 2) + 1.8223 *lens_ipow(begin_dx, 2) + 1.08123 *begin_y*begin_dy + 0.016552 *lens_ipow(begin_y, 2) + 0.564544 *begin_x*begin_dx + 0.008746 *lens_ipow(begin_x, 2) + 74.2332 *lens_ipow(begin_dy, 4) + 9.15906 *begin_y*lens_ipow(begin_dy, 3) + 0.446466 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.0101458 *lens_ipow(begin_y, 3)*begin_dy + 8.44335e-05 *lens_ipow(begin_y, 4) + 0.000367579 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 7.31837e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.654063 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -347.529 *lens_ipow(begin_dx, 8) + 7.33156e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -2.26265e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 64.9422 *begin_dx + 0.558616 *begin_x + -0.0355691 *begin_x*begin_lambda + -29.9649 *begin_dx*lens_ipow(begin_dy, 2) + -31.4593 *lens_ipow(begin_dx, 3) + 0.366561 *begin_y*begin_dx*begin_dy + 0.012091 *lens_ipow(begin_y, 2)*begin_dx + 0.0232271 *begin_x*lens_ipow(begin_lambda, 2) + 0.506025 *begin_x*lens_ipow(begin_dy, 2) + 0.68474 *begin_x*lens_ipow(begin_dx, 2) + 0.0305808 *begin_x*begin_y*begin_dy + 0.000313053 *begin_x*lens_ipow(begin_y, 2) + 0.036109 *lens_ipow(begin_x, 2)*begin_dx + 0.00023037 *lens_ipow(begin_x, 3) + 0.0513161 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -4.3411e-08 *begin_x*lens_ipow(begin_y, 4) + 0.0921031 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.00587235 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.000124423 *lens_ipow(begin_x, 4)*begin_dx + 8.50377e-07 *lens_ipow(begin_x, 5) + 1.94162e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.0812924 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 7.71408e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + 5.59088e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -1.09501e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy*begin_lambda + -0.00060165 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -1.64149 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -159.342 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4);
    out(1) =  + 64.9464 *begin_dy + 0.558716 *begin_y + -0.0360494 *begin_y*begin_lambda + -31.4511 *lens_ipow(begin_dy, 3) + -30.6062 *lens_ipow(begin_dx, 2)*begin_dy + 0.0253794 *begin_y*lens_ipow(begin_lambda, 2) + 0.693314 *begin_y*lens_ipow(begin_dy, 2) + 0.470482 *begin_y*lens_ipow(begin_dx, 2) + 0.0345958 *lens_ipow(begin_y, 2)*begin_dy + 0.000206215 *lens_ipow(begin_y, 3) + 0.335301 *begin_x*begin_dx*begin_dy + 0.0285774 *begin_x*begin_y*begin_dx + 0.0117329 *lens_ipow(begin_x, 2)*begin_dy + 0.00028576 *lens_ipow(begin_x, 2)*begin_y + 0.12641 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00774127 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.000160241 *lens_ipow(begin_y, 4)*begin_dy + 1.09578e-06 *lens_ipow(begin_y, 5) + 1.37274e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00101352 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 6.54215e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 8.90565e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.00133577 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 0.00462099 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 7.62034e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 1.18876e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_lambda + -4.74514 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.000755477 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2);
    out(2) =  + -1.41015 *begin_dx + -0.0273768 *begin_x + 0.000252428 *begin_x*begin_lambda + 0.0076591 *begin_dx*lens_ipow(begin_lambda, 2) + -0.669303 *begin_dx*lens_ipow(begin_dy, 2) + 0.786303 *lens_ipow(begin_dx, 3) + -0.0310643 *begin_y*begin_dx*begin_dy + -0.000245665 *lens_ipow(begin_y, 2)*begin_dx + -0.0227746 *begin_x*lens_ipow(begin_dy, 2) + -0.000791948 *begin_x*begin_y*begin_dy + -3.66754e-06 *begin_x*lens_ipow(begin_y, 2) + -0.00036629 *lens_ipow(begin_x, 2)*begin_dx + -6.72487e-07 *lens_ipow(begin_x, 3) + -0.168486 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.264639 *lens_ipow(begin_dx, 3)*begin_lambda + 1.38466 *begin_dx*lens_ipow(begin_dy, 4) + 2.41752 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.930077 *lens_ipow(begin_dx, 5) + -0.000304873 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0196184 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 4.48158e-05 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00175712 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -9.93893e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -9.24115e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.78337e-06 *lens_ipow(begin_x, 4)*begin_dx + -1.12037e-08 *lens_ipow(begin_x, 5) + 0.00750501 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + -0.0041541 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3);
    out(3) =  + -1.40969 *begin_dy + -0.0273691 *begin_y + 0.00024878 *begin_y*begin_lambda + 0.00765284 *begin_dy*lens_ipow(begin_lambda, 2) + 0.766623 *lens_ipow(begin_dy, 3) + 2.10359 *lens_ipow(begin_dx, 2)*begin_dy + 0.0012633 *begin_y*lens_ipow(begin_dx, 2) + -0.000365101 *lens_ipow(begin_y, 2)*begin_dy + -7.52957e-07 *lens_ipow(begin_y, 3) + 0.0478673 *begin_x*begin_dx*begin_dy + -9.14448e-05 *begin_x*begin_y*begin_dx + 0.000230142 *lens_ipow(begin_x, 2)*begin_dy + 5.2173e-07 *lens_ipow(begin_x, 2)*begin_y + -0.267337 *lens_ipow(begin_dy, 3)*begin_lambda + -0.150272 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 1.26867 *lens_ipow(begin_dy, 5) + 1.57032 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.901323 *lens_ipow(begin_dx, 4)*begin_dy + -0.00213489 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -9.57961e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -1.69425e-06 *lens_ipow(begin_y, 4)*begin_dy + -1.00849e-08 *lens_ipow(begin_y, 5) + -0.0501276 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 2.0601e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 6.01269e-06 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -5.86931e-08 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -0.00422663 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 3.46921e-05 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 3);
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
    domega2_dx0(0, 0) =  + -0.0273768  + 0.000252428 *begin_lambda + -0.0227746 *lens_ipow(begin_dy, 2) + -0.000791948 *begin_y*begin_dy + -3.66754e-06 *lens_ipow(begin_y, 2) + -0.00073258 *begin_x*begin_dx + -2.01746e-06 *lens_ipow(begin_x, 2) + 0.0196184 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 4.48158e-05 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00351424 *begin_x*lens_ipow(begin_dx, 3) + -1.98779e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000277235 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -7.13348e-06 *lens_ipow(begin_x, 3)*begin_dx + -5.60187e-08 *lens_ipow(begin_x, 4) + 0.00750501 *lens_ipow(begin_dy, 4)*begin_lambda + -0.0041541 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(0, 1) =  + -0.0310643 *begin_dx*begin_dy + -0.000491331 *begin_y*begin_dx + -0.000791948 *begin_x*begin_dy + -7.33508e-06 *begin_x*begin_y + -0.000609746 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 4.48158e-05 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -1.98779e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dx+0.0f;
    domega2_dx0(1, 0) =  + 0.0478673 *begin_dx*begin_dy + -9.14448e-05 *begin_y*begin_dx + 0.000460285 *begin_x*begin_dy + 1.04346e-06 *begin_x*begin_y + -0.0501276 *lens_ipow(begin_dx, 3)*begin_dy + 4.12019e-09 *begin_x*lens_ipow(begin_y, 3) + 1.80381e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -1.76079e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 3.46921e-05 *begin_y*begin_dx*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.0273691  + 0.00024878 *begin_lambda + 0.0012633 *lens_ipow(begin_dx, 2) + -0.000730203 *begin_y*begin_dy + -2.25887e-06 *lens_ipow(begin_y, 2) + -9.14448e-05 *begin_x*begin_dx + 5.2173e-07 *lens_ipow(begin_x, 2) + -0.00426979 *begin_y*lens_ipow(begin_dy, 3) + -0.000287388 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -6.777e-06 *lens_ipow(begin_y, 3)*begin_dy + -5.04246e-08 *lens_ipow(begin_y, 4) + 6.18029e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -5.86931e-08 *lens_ipow(begin_x, 3)*begin_dx + -0.00422663 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 3.46921e-05 *begin_x*begin_dx*lens_ipow(begin_lambda, 3)+0.0f;
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
  out[4] =  + 0.53453  + 0.649055 *begin_lambda + -0.898478 *lens_ipow(begin_lambda, 2) + 0.437368 *lens_ipow(begin_lambda, 3) + 0.00195654 *begin_x*begin_y*begin_dx*begin_dy + -7.00229e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.000494272 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + -3.36073e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -7.87749e-07 *lens_ipow(begin_y, 5)*begin_dy + -6.46245e-09 *lens_ipow(begin_y, 6) + 0.685965 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.000166626 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 3) + -0.000510273 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -3.4421e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -8.00415e-07 *lens_ipow(begin_x, 5)*begin_dx + -6.526e-09 *lens_ipow(begin_x, 6) + 0.983755 *begin_y*lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + -0.000281642 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 2.86056e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + 2.68219e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -2.56153e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx + -2.90086e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + -7.18052e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -6.71239 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4)*begin_lambda + -1.641e-09 *begin_x*lens_ipow(begin_y, 6)*begin_dx*lens_ipow(begin_dy, 2) + -6.81357e-15 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8) + 1.23033e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 2.07044e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dy;
else
  out[4] = 0.0f;
} break;
