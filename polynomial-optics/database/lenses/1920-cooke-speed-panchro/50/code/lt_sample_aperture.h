case cooke__speed_panchro__1920__50mm:
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
       + 35.0924 *begin_dx + 0.641858 *begin_x + 0.0891351 *begin_x*begin_lambda + 4.15582 *begin_dx*begin_lambda + -0.35824 *begin_y*begin_dx*begin_dy + -26.3231 *lens_ipow(begin_dx, 3) + -0.0614295 *begin_x*lens_ipow(begin_lambda, 2) + -26.6746 *begin_dx*lens_ipow(begin_dy, 2) + 4.76207e-05 *begin_x*lens_ipow(begin_y, 2) + 3.63493e-05 *lens_ipow(begin_x, 3) + -0.28474 *begin_x*lens_ipow(begin_dy, 2) + -0.695782 *begin_x*lens_ipow(begin_dx, 2) + 0.00176537 *lens_ipow(begin_y, 2)*begin_dx + -2.83826 *begin_dx*lens_ipow(begin_lambda, 2) + -8.30289e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 7.15132e-06 *lens_ipow(begin_x, 4)*begin_dx + -1.09246 *begin_x*lens_ipow(begin_dx, 4) + -1.45601 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -21.2452 *lens_ipow(begin_dx, 5) + -2.34404e-08 *begin_x*lens_ipow(begin_y, 4) + 0.330499 *begin_x*lens_ipow(begin_dy, 4) + -0.014155 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.828448 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0184576 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.000573584 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -19.1225 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.00669948 *begin_x*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -6.24636e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy*begin_lambda,
       + 0.641428 *begin_y + 35.117 *begin_dy + 4.20006 *begin_dy*begin_lambda + 0.0917387 *begin_y*begin_lambda + -0.270424 *begin_y*lens_ipow(begin_dx, 2) + -0.718968 *begin_y*lens_ipow(begin_dy, 2) + -0.400704 *begin_x*begin_dx*begin_dy + -26.8992 *lens_ipow(begin_dx, 2)*begin_dy + -0.0635284 *begin_y*lens_ipow(begin_lambda, 2) + 4.13994e-05 *lens_ipow(begin_x, 2)*begin_y + -2.89084 *begin_dy*lens_ipow(begin_lambda, 2) + 3.21081e-05 *lens_ipow(begin_y, 3) + 0.00101614 *lens_ipow(begin_x, 2)*begin_dy + -28.0817 *lens_ipow(begin_dy, 3) + -0.253707 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.12982 *begin_y*lens_ipow(begin_dx, 4) + 6.71005 *lens_ipow(begin_dy, 5) + -4.877e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.0149934 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.000432234 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 4.85851e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0343761 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_dy + -0.0805902 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + -0.275488 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -10.3718 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -6.11016 *begin_x*begin_dx*lens_ipow(begin_dy, 5) + -0.0623095 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -8.38267e-10 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2)*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 35.0924  + 4.15582 *begin_lambda + -0.35824 *begin_y*begin_dy + -78.9693 *lens_ipow(begin_dx, 2) + -26.6746 *lens_ipow(begin_dy, 2) + -1.39156 *begin_x*begin_dx + 0.00176537 *lens_ipow(begin_y, 2) + -2.83826 *lens_ipow(begin_lambda, 2) + 7.15132e-06 *lens_ipow(begin_x, 4) + -4.36983 *begin_x*lens_ipow(begin_dx, 3) + -4.36804 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -106.226 *lens_ipow(begin_dx, 4) + -0.014155 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.828448 *begin_y*lens_ipow(begin_dy, 3) + -0.0553727 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.00114717 *lens_ipow(begin_x, 3)*begin_dx + -57.3675 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(0, 1) =  + -0.35824 *begin_y*begin_dx + -53.3493 *begin_dx*begin_dy + -0.569479 *begin_x*begin_dy + -1.45601 *begin_y*lens_ipow(begin_dx, 3) + 1.322 *begin_x*lens_ipow(begin_dy, 3) + -0.02831 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -2.48534 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -38.245 *lens_ipow(begin_dx, 3)*begin_dy + 0.0200984 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -6.24636e-06 *lens_ipow(begin_x, 3)*begin_y*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + -0.540848 *begin_y*begin_dx + -0.400704 *begin_x*begin_dy + -53.7985 *begin_dx*begin_dy + -0.76112 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.519282 *begin_y*lens_ipow(begin_dx, 3) + 0.0149934 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.000432234 *begin_x*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 4.85851e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2) + -0.137504 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + -0.550975 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 3) + -31.1154 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -6.11016 *begin_x*lens_ipow(begin_dy, 5) + -0.124619 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -1.67653e-09 *lens_ipow(begin_y, 7)*begin_dx*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 35.117  + 4.20006 *begin_lambda + -1.43794 *begin_y*begin_dy + -0.400704 *begin_x*begin_dx + -26.8992 *lens_ipow(begin_dx, 2) + -2.89084 *lens_ipow(begin_lambda, 2) + 0.00101614 *lens_ipow(begin_x, 2) + -84.2452 *lens_ipow(begin_dy, 2) + -0.253707 *begin_x*lens_ipow(begin_dx, 3) + 33.5503 *lens_ipow(begin_dy, 4) + 0.0299867 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + 0.000432234 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 9.71703e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy + -0.0343761 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + -0.402951 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + -0.826463 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -31.1154 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -30.5508 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.186928 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;
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
    out(0) =  + 49.3667 *begin_dx + 0.584894 *begin_x + 0.0251879 *begin_x*begin_lambda + 0.638997 *begin_y*begin_dx*begin_dy + 0.0600612 *begin_x*begin_y*begin_dy + 0.0832236 *lens_ipow(begin_x, 2)*begin_dx + -7.39669 *lens_ipow(begin_dx, 3) + -17.9301 *begin_dx*lens_ipow(begin_dy, 2) + 0.000715225 *begin_x*lens_ipow(begin_y, 2) + 0.000721905 *lens_ipow(begin_x, 3) + 1.06016 *begin_x*lens_ipow(begin_dy, 2) + 2.10209 *begin_x*lens_ipow(begin_dx, 2) + 0.0189149 *lens_ipow(begin_y, 2)*begin_dx + 0.605873 *begin_dx*lens_ipow(begin_lambda, 2) + -4.73416e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.000444111 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.00064404 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 82.9544 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.00101892 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 0.00293701 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -376.485 *lens_ipow(begin_dx, 5)*begin_lambda + -0.877654 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -32.7738 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + -0.00755687 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 4.52876e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -1.8332 *begin_x*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + 520.899 *begin_dx*lens_ipow(begin_dy, 6)*begin_lambda + -2457.74 *begin_dx*lens_ipow(begin_dy, 8)*lens_ipow(begin_lambda, 2);
    out(1) =  + 0.583209 *begin_y + 49.3034 *begin_dy + 0.0277126 *begin_y*begin_lambda + 1.03381 *begin_y*lens_ipow(begin_dx, 2) + 0.0843913 *lens_ipow(begin_y, 2)*begin_dy + 2.15725 *begin_y*lens_ipow(begin_dy, 2) + 0.615946 *begin_x*begin_dx*begin_dy + 0.058987 *begin_x*begin_y*begin_dx + -20.1756 *lens_ipow(begin_dx, 2)*begin_dy + 0.000709236 *lens_ipow(begin_x, 2)*begin_y + 0.759262 *begin_dy*lens_ipow(begin_lambda, 2) + 0.000727772 *lens_ipow(begin_y, 3) + 0.0190906 *lens_ipow(begin_x, 2)*begin_dy + -6.69976 *lens_ipow(begin_dy, 3) + 98.9061 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.622113 *begin_y*lens_ipow(begin_dx, 4) + 0.00176627 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -3.06815e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.7419e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + 0.000630243 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.017687 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 35.3253 *lens_ipow(begin_dx, 4)*begin_dy + -0.00751692 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 2.79646e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -32.2363 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.00209685 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -0.87042 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -363.309 *lens_ipow(begin_dy, 5)*begin_lambda;
    out(2) =  + -1.55849 *begin_dx + -0.0390003 *begin_x + -0.0652355 *begin_y*begin_dx*begin_dy + -0.00221196 *begin_x*begin_y*begin_dy + -0.00099431 *lens_ipow(begin_x, 2)*begin_dx + 0.528302 *lens_ipow(begin_dx, 3) + -1.48443 *begin_dx*lens_ipow(begin_dy, 2) + -1.4765e-05 *begin_x*lens_ipow(begin_y, 2) + -3.59769e-06 *lens_ipow(begin_x, 3) + -0.0566225 *begin_x*lens_ipow(begin_dy, 2) + -0.0167901 *begin_x*lens_ipow(begin_dx, 2) + -0.000560235 *lens_ipow(begin_y, 2)*begin_dx + -8.88015e-07 *lens_ipow(begin_x, 3)*begin_lambda + 1.4175e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.00656052 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.190499 *begin_x*lens_ipow(begin_dx, 4) + 0.0023382 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 3.07109e-07 *lens_ipow(begin_y, 4)*begin_dx + 3.8375 *lens_ipow(begin_dx, 5) + 0.106264 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.34232e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 9.48294e-09 *begin_x*lens_ipow(begin_y, 4) + 5.3455 *begin_dx*lens_ipow(begin_dy, 4) + 0.0554922 *begin_x*lens_ipow(begin_dy, 4) + 0.153021 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.000117605 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -4.70249e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 5.50332 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2);
    out(3) =  + -0.039023 *begin_y + -1.56279 *begin_dy + -0.000129443 *begin_y*begin_lambda + 0.00167438 *begin_y*lens_ipow(begin_dx, 2) + -0.000872531 *lens_ipow(begin_y, 2)*begin_dy + -0.0119092 *begin_y*lens_ipow(begin_dy, 2) + 0.0968314 *begin_x*begin_dx*begin_dy + 2.76457 *lens_ipow(begin_dx, 2)*begin_dy + 5.58896e-06 *lens_ipow(begin_x, 2)*begin_y + -3.61198e-06 *lens_ipow(begin_y, 3) + 0.000879955 *lens_ipow(begin_x, 2)*begin_dy + 0.564613 *lens_ipow(begin_dy, 3) + -2.97583e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.978611 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 4.91588 *lens_ipow(begin_dy, 5) + -0.0021495 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00317877 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 3.99074e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.245484 *begin_y*lens_ipow(begin_dy, 4) + 2.34398e-09 *lens_ipow(begin_y, 5) + 0.00044327 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -1.06172e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 7.0207e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 3) + 0.000870917 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 3) + 0.0249418 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.000419582 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.729649 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*begin_lambda + 4.37975e-08 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0390003  + -0.00221196 *begin_y*begin_dy + -0.00198862 *begin_x*begin_dx + -1.4765e-05 *lens_ipow(begin_y, 2) + -1.07931e-05 *lens_ipow(begin_x, 2) + -0.0566225 *lens_ipow(begin_dy, 2) + -0.0167901 *lens_ipow(begin_dx, 2) + -2.66404e-06 *lens_ipow(begin_x, 2)*begin_lambda + 4.2525e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00656052 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.190499 *lens_ipow(begin_dx, 4) + 0.00467641 *begin_x*lens_ipow(begin_dx, 3) + 0.106264 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.34232e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 9.48294e-09 *lens_ipow(begin_y, 4) + 0.0554922 *lens_ipow(begin_dy, 4) + -0.000235211 *begin_x*begin_y*begin_dx*begin_dy + -4.70249e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(0, 1) =  + -0.0652355 *begin_dx*begin_dy + -0.00221196 *begin_x*begin_dy + -2.95301e-05 *begin_x*begin_y + -0.00112047 *begin_y*begin_dx + 2.835e-08 *lens_ipow(begin_x, 3)*begin_y + -0.00656052 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.22844e-06 *lens_ipow(begin_y, 3)*begin_dx + -8.68464e-05 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 3.79318e-08 *begin_x*lens_ipow(begin_y, 3) + 0.153021 *begin_dx*lens_ipow(begin_dy, 3) + -0.000117605 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -9.40498e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(1, 0) =  + 0.0968314 *begin_dx*begin_dy + 1.11779e-05 *begin_x*begin_y + 0.00175991 *begin_x*begin_dy + -2.97583e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.0021495 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 7.98149e-09 *begin_x*lens_ipow(begin_y, 3) + 0.000886541 *begin_x*lens_ipow(begin_dy, 3) + 2.80828e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3) + 0.00261275 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 3) + 0.0498836 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.000839165 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.7519e-07 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.039023  + -0.000129443 *begin_lambda + 0.00167438 *lens_ipow(begin_dx, 2) + -0.00174506 *begin_y*begin_dy + -0.0119092 *lens_ipow(begin_dy, 2) + 5.58896e-06 *lens_ipow(begin_x, 2) + -1.0836e-05 *lens_ipow(begin_y, 2) + -5.95166e-05 *begin_x*begin_y*begin_dx*begin_dy + -0.0021495 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.00635754 *begin_y*lens_ipow(begin_dy, 3) + 1.19722e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.245484 *lens_ipow(begin_dy, 4) + 1.17199e-08 *lens_ipow(begin_y, 4) + -3.18516e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.000419582 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.729649 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*begin_lambda + 4.37975e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
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
  out[4] =  + 0.499384  + 0.58713 *begin_lambda + -0.814674 *lens_ipow(begin_lambda, 2) + 0.397516 *lens_ipow(begin_lambda, 3) + -3.80388 *lens_ipow(begin_dx, 4) + -0.228118 *begin_y*lens_ipow(begin_dy, 3) + -0.250915 *begin_x*lens_ipow(begin_dx, 3) + -9.52048e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -3.40794 *lens_ipow(begin_dy, 4) + -4.58732e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -1.1211e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -6.03187e-07 *lens_ipow(begin_y, 4) + -0.00725467 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.000104799 *lens_ipow(begin_x, 3)*begin_dx + -0.00675165 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0869756 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -6.06514e-07 *lens_ipow(begin_x, 4) + -0.00392193 *begin_x*begin_y*begin_dx*begin_dy + -0.00219128 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000100268 *lens_ipow(begin_y, 3)*begin_dy + -0.253352 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -9.19001e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.00882851 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + -0.00409879 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.416998 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -12.5423 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.190802 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + 0.00422637 *begin_x*begin_dx*lens_ipow(begin_lambda, 4);
else
  out[4] = 0.0f;
} break;
