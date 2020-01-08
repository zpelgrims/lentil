case asahi__takumar__1969__75mm:
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
       + 45.6738 *begin_dx + 0.337152 *begin_x + 9.17616 *begin_dx*begin_lambda + 0.181237 *begin_x*begin_lambda + -6.27137 *begin_dx*lens_ipow(begin_lambda, 2) + -26.3671 *begin_dx*lens_ipow(begin_dy, 2) + -27.0473 *lens_ipow(begin_dx, 3) + -0.133001 *begin_y*begin_dx*begin_dy + 0.00143104 *lens_ipow(begin_y, 2)*begin_dx + -0.124195 *begin_x*lens_ipow(begin_lambda, 2) + -0.16488 *begin_x*lens_ipow(begin_dy, 2) + -0.280192 *begin_x*lens_ipow(begin_dx, 2) + 0.00106194 *begin_x*begin_y*begin_dy + -6.76196e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00238312 *lens_ipow(begin_x, 2)*begin_dx + -6.79531e-05 *lens_ipow(begin_x, 3) + 4.75484 *lens_ipow(begin_dx, 5) + -0.00621918 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.241217 *begin_x*lens_ipow(begin_dy, 4) + -0.00758644 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -4.30883 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 0.101893 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -5.38275 *begin_y*begin_dx*lens_ipow(begin_dy, 7) + -7.21287e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4),
       + 45.6991 *begin_dy + 0.337942 *begin_y + 9.07613 *begin_dy*begin_lambda + 0.179175 *begin_y*begin_lambda + -6.18285 *begin_dy*lens_ipow(begin_lambda, 2) + -27.058 *lens_ipow(begin_dy, 3) + -26.2691 *lens_ipow(begin_dx, 2)*begin_dy + -0.123169 *begin_y*lens_ipow(begin_lambda, 2) + -0.279266 *begin_y*lens_ipow(begin_dy, 2) + -0.163908 *begin_y*lens_ipow(begin_dx, 2) + 0.00237704 *lens_ipow(begin_y, 2)*begin_dy + -6.81247e-05 *lens_ipow(begin_y, 3) + -0.140408 *begin_x*begin_dx*begin_dy + 0.00105714 *begin_x*begin_y*begin_dx + 0.0014235 *lens_ipow(begin_x, 2)*begin_dy + -6.77846e-05 *lens_ipow(begin_x, 2)*begin_y + 4.91716 *lens_ipow(begin_dy, 5) + 0.237216 *begin_y*lens_ipow(begin_dx, 4) + -0.0076363 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.00603336 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.107653 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + -38.76 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + -1.65896e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 1.73343e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 45.6738  + 9.17616 *begin_lambda + -6.27137 *lens_ipow(begin_lambda, 2) + -26.3671 *lens_ipow(begin_dy, 2) + -81.1419 *lens_ipow(begin_dx, 2) + -0.133001 *begin_y*begin_dy + 0.00143104 *lens_ipow(begin_y, 2) + -0.560383 *begin_x*begin_dx + 0.00238312 *lens_ipow(begin_x, 2) + 23.7742 *lens_ipow(begin_dx, 4) + -0.0186575 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00758644 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -12.9265 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.407571 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -5.38275 *begin_y*lens_ipow(begin_dy, 7)+0.0f;
    dx1_domega0(0, 1) =  + -52.7341 *begin_dx*begin_dy + -0.133001 *begin_y*begin_dx + -0.32976 *begin_x*begin_dy + 0.00106194 *begin_x*begin_y + 0.964868 *begin_x*lens_ipow(begin_dy, 3) + -0.0151729 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -12.9265 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.101893 *begin_x*begin_y*lens_ipow(begin_dx, 4) + -37.6793 *begin_y*begin_dx*lens_ipow(begin_dy, 6)+0.0f;
    dx1_domega0(1, 0) =  + -52.5382 *begin_dx*begin_dy + -0.327817 *begin_y*begin_dx + -0.140408 *begin_x*begin_dy + 0.00105714 *begin_x*begin_y + 0.948863 *begin_y*lens_ipow(begin_dx, 3) + -0.0152726 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.107653 *begin_x*begin_y*lens_ipow(begin_dy, 4) + -193.8 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 1) =  + 45.6991  + 9.07613 *begin_lambda + -6.18285 *lens_ipow(begin_lambda, 2) + -81.1739 *lens_ipow(begin_dy, 2) + -26.2691 *lens_ipow(begin_dx, 2) + -0.558532 *begin_y*begin_dy + 0.00237704 *lens_ipow(begin_y, 2) + -0.140408 *begin_x*begin_dx + 0.0014235 *lens_ipow(begin_x, 2) + 24.5858 *lens_ipow(begin_dy, 4) + -0.0076363 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0181001 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.430611 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -116.28 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2)+0.0f;
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
    out(0) =  + 74.0721 *begin_dx + -0.053022 *begin_x + 1.37223 *begin_dx*begin_lambda + 0.0873155 *begin_x*begin_lambda + -29.6292 *begin_dx*lens_ipow(begin_dy, 2) + -29.8402 *lens_ipow(begin_dx, 3) + 0.0906216 *begin_y*begin_dx*begin_dy + 0.00572915 *lens_ipow(begin_y, 2)*begin_dx + 0.0110562 *begin_x*begin_y*begin_dy + -0.000138179 *begin_x*lens_ipow(begin_y, 2) + 0.0178881 *lens_ipow(begin_x, 2)*begin_dx + -0.000136858 *lens_ipow(begin_x, 3) + 1.90989 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 2.42458 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -1.80309 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -2.38439 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.0315443 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -1.56815e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.07698e-05 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 0.0701903 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5) + -7.4114e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -2.97268e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -34.8112 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 8) + -0.00035289 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3);
    out(1) =  + 74.4068 *begin_dy + 0.846415 *begin_dy*begin_lambda + -30.7418 *lens_ipow(begin_dy, 3) + -29.6318 *lens_ipow(begin_dx, 2)*begin_dy + 0.0155113 *lens_ipow(begin_y, 2)*begin_dy + -0.000353157 *lens_ipow(begin_y, 3) + 0.00983401 *begin_x*begin_y*begin_dx + -0.00029322 *lens_ipow(begin_x, 2)*begin_y + 1.49459 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 1.26317 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.000349163 *lens_ipow(begin_y, 3)*begin_lambda + 0.145917 *begin_x*begin_dx*begin_dy*begin_lambda + 0.0197649 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.000268574 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -0.93776 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.925819 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000460279 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00065397 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.0172508 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.00024911 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.0756721 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 0.0733771 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -5.82373e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -2.40087e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 6);
    out(2) =  + -0.907098 *begin_dx + -0.0120297 *begin_x + -0.00369512 *begin_x*begin_lambda + 0.440167 *lens_ipow(begin_dx, 3) + 1.37495e-05 *lens_ipow(begin_y, 2)*begin_dx + 0.00260987 *begin_x*lens_ipow(begin_lambda, 2) + -0.00549352 *begin_x*lens_ipow(begin_dy, 2) + -0.000111884 *begin_x*begin_y*begin_dy + 2.58398e-06 *begin_x*lens_ipow(begin_y, 2) + -9.4865e-05 *lens_ipow(begin_x, 2)*begin_dx + 2.5173e-06 *lens_ipow(begin_x, 3) + 0.0779399 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.242382 *begin_dx*lens_ipow(begin_dy, 4) + -0.263357 *lens_ipow(begin_dx, 5) + -0.00808708 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00820444 *begin_x*lens_ipow(begin_dx, 4) + -0.000454356 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.57212e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 3.28953e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.015122 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.000193792 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 2.13312e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 4.70528e-14 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2) + -6.30694e-14 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2)*begin_lambda;
    out(3) =  + -0.906862 *begin_dy + -0.011995 *begin_y + -0.00388882 *begin_y*begin_lambda + 0.406557 *lens_ipow(begin_dy, 3) + 0.793966 *lens_ipow(begin_dx, 2)*begin_dy + 0.00274317 *begin_y*lens_ipow(begin_lambda, 2) + -8.73516e-05 *lens_ipow(begin_y, 2)*begin_dy + 2.71121e-06 *lens_ipow(begin_y, 3) + 0.0106195 *begin_x*begin_dx*begin_dy + -0.000113155 *begin_x*begin_y*begin_dx + 2.57684e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0286641 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.505379 *lens_ipow(begin_dx, 4)*begin_dy + 0.0437674 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 3.50549e-05 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.000174664 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.000302972 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -5.32578e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -4.61766 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5) + -0.0259181 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -2.27856e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 4.27416e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 2.73859e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -1.57386 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0120297  + -0.00369512 *begin_lambda + 0.00260987 *lens_ipow(begin_lambda, 2) + -0.00549352 *lens_ipow(begin_dy, 2) + -0.000111884 *begin_y*begin_dy + 2.58398e-06 *lens_ipow(begin_y, 2) + -0.00018973 *begin_x*begin_dx + 7.55191e-06 *lens_ipow(begin_x, 2) + -0.00808708 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00820444 *lens_ipow(begin_dx, 4) + -0.000454356 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.57212e-06 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 9.86858e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 4.26623e-08 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 3.2937e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2) + -4.41486e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + 2.7499e-05 *begin_y*begin_dx + -0.000111884 *begin_x*begin_dy + 5.16796e-06 *begin_x*begin_y + -0.000454356 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 3.14423e-06 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -0.015122 *lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.000387585 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 6.39935e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 9.41057e-14 *lens_ipow(begin_x, 7)*begin_y + -1.26139e-13 *lens_ipow(begin_x, 7)*begin_y*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.0106195 *begin_dx*begin_dy + -0.000113155 *begin_y*begin_dx + 5.15369e-06 *begin_x*begin_y + 7.01099e-05 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 0.000349328 *begin_x*lens_ipow(begin_dy, 3) + 0.000605943 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -4.55711e-10 *begin_x*lens_ipow(begin_y, 4)*begin_dy + 1.70966e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 8.21576e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.011995  + -0.00388882 *begin_lambda + 0.00274317 *lens_ipow(begin_lambda, 2) + -0.000174703 *begin_y*begin_dy + 8.13364e-06 *lens_ipow(begin_y, 2) + -0.000113155 *begin_x*begin_dx + 2.57684e-06 *lens_ipow(begin_x, 2) + -0.0286641 *lens_ipow(begin_dx, 2)*begin_lambda + 0.0437674 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -1.59773e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.0259181 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -9.11423e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + 1.28225e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 5.47717e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -1.57386 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6)*begin_lambda+0.0f;
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
  out[4] =  + 2.1416 *begin_lambda + -4.75721 *lens_ipow(begin_lambda, 2) + 0.0137456 *lens_ipow(begin_dy, 2) + -0.000224788 *begin_x*begin_dx + -2.67388e-06 *lens_ipow(begin_x, 2) + 4.95592 *lens_ipow(begin_lambda, 3) + -1.99307 *lens_ipow(begin_lambda, 4) + -0.528201 *lens_ipow(begin_dy, 4) + -1.02349 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.214462 *lens_ipow(begin_dx, 4) + -0.0167265 *begin_y*lens_ipow(begin_dy, 3) + -0.0156593 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000328453 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000118146 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.015059 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.000349488 *begin_x*begin_y*begin_dx*begin_dy + -8.21262e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -2.19311e-06 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -1.52975e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.42186 *lens_ipow(begin_dx, 6) + -0.114984 *begin_x*lens_ipow(begin_dx, 5) + -0.00390613 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -7.27393e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -7.27236e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2);
else
  out[4] = 0.0f;
} break;
