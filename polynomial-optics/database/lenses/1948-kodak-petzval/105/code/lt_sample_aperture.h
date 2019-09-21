case kodak__petzval__1948__105mm:
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
       + 80.4853 *begin_dx + 0.793429 *begin_x + -0.00160156 *begin_x*begin_lambda + 1.30033 *begin_dx*begin_lambda + 0.523012 *begin_y*begin_dx*begin_dy + 0.00743408 *begin_x*begin_y*begin_dy + 0.010363 *lens_ipow(begin_x, 2)*begin_dx + 1.16333 *begin_dx*lens_ipow(begin_dy, 2) + 4.75435e-05 *begin_x*lens_ipow(begin_y, 2) + 3.22758e-05 *lens_ipow(begin_x, 3) + 0.121525 *begin_x*lens_ipow(begin_dy, 2) + 0.555625 *begin_x*lens_ipow(begin_dx, 2) + 0.00507526 *lens_ipow(begin_y, 2)*begin_dx + -0.934829 *begin_dx*lens_ipow(begin_lambda, 2) + 1.72285e-05 *lens_ipow(begin_x, 4)*begin_dx + 1.24505 *begin_x*lens_ipow(begin_dx, 4) + 0.0621952 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 10.1114 *lens_ipow(begin_dx, 5) + 7.16169e-08 *lens_ipow(begin_x, 5) + 2.18549e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.00151122 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.0160109 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 1.05829e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 2.18964e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + 1.16865e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 4.83493e-08 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dy, 3) + 0.0728141 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*begin_lambda + 30102.5 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2),
       + 0.793305 *begin_y + 80.4738 *begin_dy + 1.3191 *begin_dy*begin_lambda + -0.00150834 *begin_y*begin_lambda + 0.12759 *begin_y*lens_ipow(begin_dx, 2) + 0.0103962 *lens_ipow(begin_y, 2)*begin_dy + 0.555099 *begin_y*lens_ipow(begin_dy, 2) + 0.00742601 *begin_x*begin_y*begin_dx + 1.46185 *lens_ipow(begin_dx, 2)*begin_dy + 4.7538e-05 *lens_ipow(begin_x, 2)*begin_y + -0.95094 *begin_dy*lens_ipow(begin_lambda, 2) + 3.22055e-05 *lens_ipow(begin_y, 3) + 0.0260774 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 3.00749 *begin_x*begin_dx*begin_dy*begin_lambda + -5.57249 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 1.81748e-05 *lens_ipow(begin_y, 4)*begin_dy + 12.3213 *lens_ipow(begin_dy, 5) + 5.92434e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.0724419 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 1.53117 *begin_y*lens_ipow(begin_dy, 4) + -0.036311 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 7.53284e-08 *lens_ipow(begin_y, 5) + 0.00165712 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 3.39225 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + 0.0198909 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 4) + -1.54663e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 0.123291 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*begin_lambda + 24529.4 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 80.4853  + 1.30033 *begin_lambda + 0.523012 *begin_y*begin_dy + 0.010363 *lens_ipow(begin_x, 2) + 1.16333 *lens_ipow(begin_dy, 2) + 1.11125 *begin_x*begin_dx + 0.00507526 *lens_ipow(begin_y, 2) + -0.934829 *lens_ipow(begin_lambda, 2) + 1.72285e-05 *lens_ipow(begin_x, 4) + 4.98021 *begin_x*lens_ipow(begin_dx, 3) + 0.186586 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 50.5571 *lens_ipow(begin_dx, 4) + 2.18549e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.00302244 *lens_ipow(begin_x, 3)*begin_dx + -0.0320218 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + 0.218442 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 150512 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(0, 1) =  + 0.523012 *begin_y*begin_dx + 0.00743408 *begin_x*begin_y + 2.32666 *begin_dx*begin_dy + 0.243051 *begin_x*begin_dy + -0.0160109 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 2.11657e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 2.18964e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 1.45048e-07 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dy, 2) + 0.218442 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 120410 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 0) =  + 0.255181 *begin_y*begin_dx + 0.00742601 *begin_x*begin_y + 2.9237 *begin_dx*begin_dy + 3.00749 *begin_x*begin_dy*begin_lambda + -5.57249 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 5.92434e-07 *begin_x*lens_ipow(begin_y, 3) + 3.39225 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -1.54663e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy + 0.369873 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 98117.4 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 1) =  + 80.4738  + 1.3191 *begin_lambda + 0.0103962 *lens_ipow(begin_y, 2) + 1.1102 *begin_y*begin_dy + 1.46185 *lens_ipow(begin_dx, 2) + -0.95094 *lens_ipow(begin_lambda, 2) + 0.0260774 *lens_ipow(begin_x, 2)*begin_lambda + 3.00749 *begin_x*begin_dx*begin_lambda + -5.57249 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + 1.81748e-05 *lens_ipow(begin_y, 4) + 61.6067 *lens_ipow(begin_dy, 4) + 0.217326 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 6.12469 *begin_y*lens_ipow(begin_dy, 3) + -0.036311 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 0.00331423 *lens_ipow(begin_y, 3)*begin_dy + 3.39225 *begin_x*begin_dx*lens_ipow(begin_lambda, 3) + 0.0198909 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 4) + -1.54663e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx + 0.369873 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 122647 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2)+0.0f;
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
    out(0) =  + 104.943 *begin_dx + 0.553008 *begin_x + -0.0108355 *begin_x*begin_lambda + 0.301209 *begin_y*begin_dx*begin_dy + 0.0171892 *begin_x*begin_y*begin_dy + 0.0242029 *lens_ipow(begin_x, 2)*begin_dx + -51.4186 *lens_ipow(begin_dx, 3) + -50.0853 *begin_dx*lens_ipow(begin_dy, 2) + 0.000101431 *begin_x*lens_ipow(begin_y, 2) + 8.37033e-05 *lens_ipow(begin_x, 3) + 0.465708 *begin_x*lens_ipow(begin_dy, 2) + 0.749551 *begin_x*lens_ipow(begin_dx, 2) + 0.00685583 *lens_ipow(begin_y, 2)*begin_dx + 1.52079e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.000269224 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 1.26007e-07 *lens_ipow(begin_x, 5) + 1.42923e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.00564736 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 0.00209706 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 3.34316e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 6.12808e-05 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 0.00298959 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -2.19171e-05 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 2) + 0.00161015 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -7.70204 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2) + -4.68793 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -3.03576 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 3) + -1841.8 *lens_ipow(begin_dx, 7)*lens_ipow(begin_lambda, 4);
    out(1) =  + 0.557703 *begin_y + 104.949 *begin_dy + -0.0331657 *begin_y*begin_lambda + 0.460136 *begin_y*lens_ipow(begin_dx, 2) + 0.0278201 *lens_ipow(begin_y, 2)*begin_dy + 0.871681 *begin_y*lens_ipow(begin_dy, 2) + 0.287984 *begin_x*begin_dx*begin_dy + 0.0170842 *begin_x*begin_y*begin_dx + -50.4524 *lens_ipow(begin_dx, 2)*begin_dy + 0.0255298 *begin_y*lens_ipow(begin_lambda, 2) + 0.000102132 *lens_ipow(begin_x, 2)*begin_y + 0.000127272 *lens_ipow(begin_y, 3) + 0.00685162 *lens_ipow(begin_x, 2)*begin_dy + -51.686 *lens_ipow(begin_dy, 3) + -0.354955 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.0120721 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -9.36139e-05 *lens_ipow(begin_y, 3)*begin_lambda + 6.68338e-05 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.00521654 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 0.000540779 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 2.9182e-07 *lens_ipow(begin_y, 5)*begin_lambda + 2.44136e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 2.30695e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 0.140047 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 4.46594e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.00311621 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -8.76513 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.00174555 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3);
    out(2) =  + -1.4141 *begin_dx + -0.0169565 *begin_x + 0.000168869 *begin_x*begin_lambda + 0.0103592 *begin_dx*begin_lambda + -0.000291212 *begin_x*begin_y*begin_dy + -0.000159372 *lens_ipow(begin_x, 2)*begin_dx + 0.870083 *lens_ipow(begin_dx, 3) + -8.03958e-07 *begin_x*lens_ipow(begin_y, 2) + -3.44648e-07 *lens_ipow(begin_x, 3) + -0.0134214 *begin_x*lens_ipow(begin_dy, 2) + -0.346257 *lens_ipow(begin_dx, 3)*begin_lambda + -0.00034396 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.0624919 *begin_y*begin_dx*begin_dy*begin_lambda + -4.73564e-08 *lens_ipow(begin_x, 4)*begin_dx + 0.347338 *lens_ipow(begin_dx, 5) + 0.0111237 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -12.101 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.80072 *begin_dx*lens_ipow(begin_dy, 4) + -3.1024e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 1.94393 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.00397151 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.00137929 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 27.4023 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.128968 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + 0.0011031 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 3) + -17.682 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -0.000972013 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 4) + -0.118404 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 5);
    out(3) =  + -0.0169439 *begin_y + -1.41106 *begin_dy + 0.000146825 *begin_y*begin_lambda + 0.0011714 *begin_y*lens_ipow(begin_dx, 2) + -0.000157016 *lens_ipow(begin_y, 2)*begin_dy + 0.0302881 *begin_x*begin_dx*begin_dy + -3.39099e-05 *begin_x*begin_y*begin_dx + 2.23097 *lens_ipow(begin_dx, 2)*begin_dy + 0.00786042 *begin_dy*lens_ipow(begin_lambda, 2) + -3.10985e-07 *lens_ipow(begin_y, 3) + 8.29378e-05 *lens_ipow(begin_x, 2)*begin_dy + 0.856984 *lens_ipow(begin_dy, 3) + -0.232999 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 1.616e-05 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -0.321709 *lens_ipow(begin_dy, 3)*begin_lambda + 3.3987e-07 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -0.0257833 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.457744 *lens_ipow(begin_dy, 5) + 0.000160241 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -1.31819 *lens_ipow(begin_dx, 4)*begin_dy + 3.68815e-05 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 3) + -0.00359211 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 4.73553e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -1.87593e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 3.02735e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -5.7743e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 6.48702e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy + 1.5318e-07 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.0169565  + 0.000168869 *begin_lambda + -0.000291212 *begin_y*begin_dy + -0.000318743 *begin_x*begin_dx + -8.03958e-07 *lens_ipow(begin_y, 2) + -1.03394e-06 *lens_ipow(begin_x, 2) + -0.0134214 *lens_ipow(begin_dy, 2) + -1.89426e-07 *lens_ipow(begin_x, 3)*begin_dx + 0.0111237 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -9.30721e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.00397151 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.00137929 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(0, 1) =  + -0.000291212 *begin_x*begin_dy + -1.60792e-06 *begin_x*begin_y + -0.000687921 *begin_y*begin_dx*begin_lambda + -0.0624919 *begin_dx*begin_dy*begin_lambda + 0.128968 *begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + 0.00220621 *begin_y*begin_dx*lens_ipow(begin_lambda, 3) + -0.00194403 *begin_y*begin_dx*lens_ipow(begin_lambda, 4) + -0.118404 *begin_dx*begin_dy*lens_ipow(begin_lambda, 5)+0.0f;
    domega2_dx0(1, 0) =  + 0.0302881 *begin_dx*begin_dy + -3.39099e-05 *begin_y*begin_dx + 0.000165876 *begin_x*begin_dy + 3.232e-05 *begin_x*begin_dy*begin_lambda + 6.7974e-07 *begin_x*begin_y*begin_lambda + -0.0257833 *lens_ipow(begin_dx, 3)*begin_dy + 0.000160241 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 3.68815e-05 *begin_y*begin_dx*lens_ipow(begin_lambda, 3) + 1.42066e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -3.75187e-10 *begin_x*lens_ipow(begin_y, 4)*begin_dy + 6.05469e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -5.7743e-05 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 2.59481e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy + 1.5318e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.0169439  + 0.000146825 *begin_lambda + 0.0011714 *lens_ipow(begin_dx, 2) + -0.000314032 *begin_y*begin_dy + -3.39099e-05 *begin_x*begin_dx + -9.32955e-07 *lens_ipow(begin_y, 2) + 3.3987e-07 *lens_ipow(begin_x, 2)*begin_lambda + 0.000160241 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 3.68815e-05 *begin_x*begin_dx*lens_ipow(begin_lambda, 3) + -0.00359211 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 9.47105e-08 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy + -7.50374e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + 6.05469e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000115486 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + 2.59481e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + 6.12719e-07 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
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
  out[4] =  + 0.453578  + 1.26704 *begin_lambda + 0.000388006 *begin_x*begin_dx + 7.61555e-06 *lens_ipow(begin_x, 2) + -2.63719 *lens_ipow(begin_lambda, 2) + 2.58355 *lens_ipow(begin_lambda, 3) + -0.981418 *lens_ipow(begin_lambda, 4) + -0.000398042 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0164745 *begin_x*lens_ipow(begin_dx, 3) + -0.730956 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.11741e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -2.0752e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -2.79968e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.000929289 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.0304858 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.82792e-05 *lens_ipow(begin_x, 3)*begin_dx + -0.0300732 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -1.2711e-07 *lens_ipow(begin_x, 4) + -0.00155588 *begin_x*begin_y*begin_dx*begin_dy + -0.000416554 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -4.98976e-06 *lens_ipow(begin_y, 3)*begin_dy + -6.63217e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -7.32995e-08 *lens_ipow(begin_y, 5)*begin_dy + -5.54249e-10 *lens_ipow(begin_y, 6) + -1.47489e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3) + -6.79808e-09 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 2) + 4.84976e-13 *lens_ipow(begin_y, 8) + -1.05683e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 4);
else
  out[4] = 0.0f;
} break;
