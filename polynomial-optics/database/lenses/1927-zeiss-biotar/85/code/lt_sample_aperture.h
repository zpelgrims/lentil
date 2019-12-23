case zeiss__biotar__1927__85mm:
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
       + 51.713 *begin_dx + 0.441284 *begin_x + 10.2785 *begin_dx*begin_lambda + 0.148614 *begin_x*begin_lambda + -7.01106 *begin_dx*lens_ipow(begin_lambda, 2) + -32.9667 *begin_dx*lens_ipow(begin_dy, 2) + -32.7629 *lens_ipow(begin_dx, 3) + -0.000840311 *lens_ipow(begin_y, 2)*begin_dx + -0.101817 *begin_x*lens_ipow(begin_lambda, 2) + -0.20401 *begin_x*lens_ipow(begin_dy, 2) + -0.416408 *begin_x*lens_ipow(begin_dx, 2) + -8.56721e-05 *begin_x*lens_ipow(begin_y, 2) + -0.00289033 *lens_ipow(begin_x, 2)*begin_dx + -7.85774e-05 *lens_ipow(begin_x, 3) + -0.0128199 *begin_x*begin_y*begin_dy*begin_lambda + -4.44835 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 0.0114289 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0300798 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.000178463 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00021845 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -5.29765e-06 *lens_ipow(begin_x, 4)*begin_dx + 10.8821 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + 0.025116 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -7.37927 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + 3.51607 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 9.08072e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.0290931 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 6) + -1.46712e-15 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2),
       + 51.7129 *begin_dy + 0.44183 *begin_y + 10.2789 *begin_dy*begin_lambda + 0.148753 *begin_y*begin_lambda + -7.01485 *begin_dy*lens_ipow(begin_lambda, 2) + -32.8227 *lens_ipow(begin_dy, 3) + -33.0125 *lens_ipow(begin_dx, 2)*begin_dy + -0.102029 *begin_y*lens_ipow(begin_lambda, 2) + -0.460732 *begin_y*lens_ipow(begin_dy, 2) + -0.232539 *begin_y*lens_ipow(begin_dx, 2) + -0.00372251 *lens_ipow(begin_y, 2)*begin_dy + -7.9245e-05 *lens_ipow(begin_y, 3) + -0.227084 *begin_x*begin_dx*begin_dy + -0.0032596 *begin_x*begin_y*begin_dx + -0.000706094 *lens_ipow(begin_x, 2)*begin_dy + -8.09562e-05 *lens_ipow(begin_x, 2)*begin_y + 0.360857 *begin_y*lens_ipow(begin_dy, 4) + 0.557035 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.181487 *begin_y*lens_ipow(begin_dx, 4) + 0.013793 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -2.76262e-06 *lens_ipow(begin_y, 4)*begin_dy + 0.0292298 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -3.11841e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.0145691 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.000153341 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.00019357 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -1.15312e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -2.68142e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 51.713  + 10.2785 *begin_lambda + -7.01106 *lens_ipow(begin_lambda, 2) + -32.9667 *lens_ipow(begin_dy, 2) + -98.2887 *lens_ipow(begin_dx, 2) + -0.000840311 *lens_ipow(begin_y, 2) + -0.832817 *begin_x*begin_dx + -0.00289033 *lens_ipow(begin_x, 2) + -4.44835 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + 0.0114289 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.0601595 *begin_x*begin_y*begin_dx*begin_dy + 0.000356926 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.0004369 *lens_ipow(begin_x, 3)*begin_dx + -5.29765e-06 *lens_ipow(begin_x, 4) + 10.8821 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -7.37927 *begin_y*begin_dy*lens_ipow(begin_lambda, 4) + 7.03213 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + 9.08072e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + -65.9335 *begin_dx*begin_dy + -0.40802 *begin_x*begin_dy + -0.0128199 *begin_x*begin_y*begin_lambda + -4.44835 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.0228579 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0300798 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 10.8821 *begin_y*begin_dx*lens_ipow(begin_lambda, 3) + 0.025116 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + -7.37927 *begin_y*begin_dx*lens_ipow(begin_lambda, 4) + 14.0643 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 9.08072e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -0.0290931 *begin_x*begin_y*lens_ipow(begin_lambda, 6)+0.0f;
    dx1_domega0(1, 0) =  + -66.025 *begin_dx*begin_dy + -0.465078 *begin_y*begin_dx + -0.227084 *begin_x*begin_dy + -0.0032596 *begin_x*begin_y + 1.11407 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.725949 *begin_y*lens_ipow(begin_dx, 3) + 0.0292298 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -3.11841e-06 *begin_x*lens_ipow(begin_y, 3) + 0.0291382 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.00019357 *lens_ipow(begin_x, 3)*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 51.7129  + 10.2789 *begin_lambda + -7.01485 *lens_ipow(begin_lambda, 2) + -98.4682 *lens_ipow(begin_dy, 2) + -33.0125 *lens_ipow(begin_dx, 2) + -0.921463 *begin_y*begin_dy + -0.00372251 *lens_ipow(begin_y, 2) + -0.227084 *begin_x*begin_dx + -0.000706094 *lens_ipow(begin_x, 2) + 1.44343 *begin_y*lens_ipow(begin_dy, 3) + 1.11407 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0413791 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -2.76262e-06 *lens_ipow(begin_y, 4) + 0.0584596 *begin_x*begin_y*begin_dx*begin_dy + 0.0145691 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.000306681 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.00019357 *lens_ipow(begin_x, 3)*begin_dx + -1.15312e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)+0.0f;
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
    out(0) =  + 84.4101 *begin_dx + 0.151067 *begin_x + 1.20989 *begin_dx*begin_lambda + 0.19879 *begin_x*begin_lambda + -32.8839 *begin_dx*lens_ipow(begin_dy, 2) + -41.6454 *lens_ipow(begin_dx, 3) + 0.487389 *begin_y*begin_dx*begin_dy + 0.00635323 *lens_ipow(begin_y, 2)*begin_dx + -0.131763 *begin_x*lens_ipow(begin_lambda, 2) + 0.737916 *begin_x*lens_ipow(begin_dy, 2) + 0.743442 *begin_x*lens_ipow(begin_dx, 2) + 0.0180242 *begin_x*begin_y*begin_dy + 0.0158024 *lens_ipow(begin_x, 2)*begin_dx + 53.0286 *lens_ipow(begin_dx, 5) + 0.0242103 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 4.61444 *begin_x*lens_ipow(begin_dx, 4) + 0.0739513 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.82448e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -1.56349e-07 *begin_x*lens_ipow(begin_y, 4) + 0.205256 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -2.67964e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.00267516 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.99492e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -4.6218e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -2.40724e-07 *lens_ipow(begin_x, 5) + 0.100587 *begin_x*begin_y*lens_ipow(begin_dy, 5) + 0.263679 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.299207 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3);
    out(1) =  + 84.4159 *begin_dy + 0.189842 *begin_y + 1.1865 *begin_dy*begin_lambda + 0.0536881 *begin_y*begin_lambda + -41.417 *lens_ipow(begin_dy, 3) + -32.9316 *lens_ipow(begin_dx, 2)*begin_dy + 0.758543 *begin_y*lens_ipow(begin_dy, 2) + 0.0160385 *lens_ipow(begin_y, 2)*begin_dy + 0.502996 *begin_x*begin_dx*begin_dy + 0.0165435 *begin_x*begin_y*begin_dx + 0.00639045 *lens_ipow(begin_x, 2)*begin_dy + 2.7547 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 51.741 *lens_ipow(begin_dy, 5) + 4.48828 *begin_y*lens_ipow(begin_dy, 4) + -2.53308 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.201681 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.0277082 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.00263178 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -2.34845e-07 *lens_ipow(begin_y, 5) + 0.0764659 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.0335998 *begin_x*begin_y*lens_ipow(begin_dx, 3) + -2.06717e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.0278371 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.000522063 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -2.73537e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -4.84962e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -1.21751e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -1.5883e-07 *lens_ipow(begin_x, 4)*begin_y;
    out(2) =  + -1.19337 *begin_dx + -0.0141689 *begin_x + -0.00219212 *begin_x*begin_lambda + -0.31858 *begin_dx*lens_ipow(begin_dy, 2) + 0.543992 *lens_ipow(begin_dx, 3) + -0.00977878 *begin_y*begin_dx*begin_dy + 1.71362e-05 *lens_ipow(begin_y, 2)*begin_dx + 0.00153435 *begin_x*lens_ipow(begin_lambda, 2) + -0.0116307 *begin_x*lens_ipow(begin_dy, 2) + -0.00334245 *begin_x*lens_ipow(begin_dx, 2) + -0.000144243 *begin_x*begin_y*begin_dy + 1.94085e-06 *begin_x*lens_ipow(begin_y, 2) + -3.2479e-05 *lens_ipow(begin_x, 2)*begin_dx + 2.02825e-06 *lens_ipow(begin_x, 3) + -0.000471321 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.000522503 *begin_x*begin_y*lens_ipow(begin_dy, 3) + -0.00104484 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -7.0357e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000436432 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 1.45248e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.042061 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + -0.00165685 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 4.71748 *begin_dx*lens_ipow(begin_dy, 6) + 13.6419 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 9.16676 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 7.0025e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 9.93932e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -4.40633e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2);
    out(3) =  + -1.19119 *begin_dy + -0.0142452 *begin_y + -0.00620803 *begin_dy*begin_lambda + -0.00207664 *begin_y*begin_lambda + 0.562043 *lens_ipow(begin_dy, 3) + 1.38318 *lens_ipow(begin_dx, 2)*begin_dy + 0.0013948 *begin_y*lens_ipow(begin_lambda, 2) + -0.00123975 *begin_y*lens_ipow(begin_dy, 2) + -0.00591907 *begin_y*lens_ipow(begin_dx, 2) + -2.17774e-05 *lens_ipow(begin_y, 2)*begin_dy + 2.27757e-06 *lens_ipow(begin_y, 3) + 0.0183511 *begin_x*begin_dx*begin_dy + -5.42478e-05 *begin_x*begin_y*begin_dx + 8.63408e-05 *lens_ipow(begin_x, 2)*begin_dy + 2.25411e-06 *lens_ipow(begin_x, 2)*begin_y + -0.43868 *lens_ipow(begin_dx, 4)*begin_dy + -0.031619 *begin_y*lens_ipow(begin_dy, 4) + 0.00664437 *begin_y*lens_ipow(begin_dx, 4) + -0.00111397 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.000206566 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -8.89283e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -4.2258e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.000446908 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00363951 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 4.05218e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 2.76339e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 9.38405e-08 *lens_ipow(begin_x, 5)*begin_dx*lens_ipow(begin_dy, 3) + 1.05149e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_dx;
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
    domega2_dx0(0, 0) =  + -0.0141689  + -0.00219212 *begin_lambda + 0.00153435 *lens_ipow(begin_lambda, 2) + -0.0116307 *lens_ipow(begin_dy, 2) + -0.00334245 *lens_ipow(begin_dx, 2) + -0.000144243 *begin_y*begin_dy + 1.94085e-06 *lens_ipow(begin_y, 2) + -6.49579e-05 *begin_x*begin_dx + 6.08475e-06 *lens_ipow(begin_x, 2) + -0.000522503 *begin_y*lens_ipow(begin_dy, 3) + -0.00104484 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -7.0357e-06 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000872865 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 4.35744e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.042061 *lens_ipow(begin_dx, 4)*begin_lambda + -0.0033137 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + 2.801e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 4.96966e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -2.20317e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(0, 1) =  + -0.00977878 *begin_dx*begin_dy + 3.42724e-05 *begin_y*begin_dx + -0.000144243 *begin_x*begin_dy + 3.88171e-06 *begin_x*begin_y + -0.000942642 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.000522503 *begin_x*lens_ipow(begin_dy, 3) + -0.00104484 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -1.40714e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 1.45248e-07 *lens_ipow(begin_x, 3)*begin_dy + 1.4005e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 1.98786e-11 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    domega2_dx0(1, 0) =  + 0.0183511 *begin_dx*begin_dy + -5.42478e-05 *begin_y*begin_dx + 0.000172682 *begin_x*begin_dy + 4.50823e-06 *begin_x*begin_y + -0.000446908 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00727902 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 8.10437e-10 *begin_x*lens_ipow(begin_y, 4)*begin_dy + 1.10536e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + 4.69203e-07 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 3) + 5.25744e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx+0.0f;
    domega2_dx0(1, 1) =  + -0.0142452  + -0.00207664 *begin_lambda + 0.0013948 *lens_ipow(begin_lambda, 2) + -0.00123975 *lens_ipow(begin_dy, 2) + -0.00591907 *lens_ipow(begin_dx, 2) + -4.35548e-05 *begin_y*begin_dy + 6.83272e-06 *lens_ipow(begin_y, 2) + -5.42478e-05 *begin_x*begin_dx + 2.25411e-06 *lens_ipow(begin_x, 2) + -0.031619 *lens_ipow(begin_dy, 4) + 0.00664437 *lens_ipow(begin_dx, 4) + -0.00222795 *begin_y*lens_ipow(begin_dy, 3) + -0.000413132 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -2.66785e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -1.26774e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.000446908 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 1.62087e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + 1.38169e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 3.15446e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx+0.0f;
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
  out[4] =  + 0.446659  + 0.695847 *begin_lambda + -0.96 *lens_ipow(begin_lambda, 2) + 0.0404663 *lens_ipow(begin_dy, 2) + 0.0344883 *lens_ipow(begin_dx, 2) + 0.000767805 *begin_y*begin_dy + 0.000889958 *begin_x*begin_dx + 0.466489 *lens_ipow(begin_lambda, 3) + -1.1846 *lens_ipow(begin_dy, 4) + -2.35205 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.13233 *lens_ipow(begin_dx, 4) + -0.0443759 *begin_y*lens_ipow(begin_dy, 3) + -0.043916 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000941243 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000299905 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -8.83212e-06 *lens_ipow(begin_y, 3)*begin_dy + -1.05976e-08 *lens_ipow(begin_y, 4) + -0.0439537 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0479772 *begin_x*lens_ipow(begin_dx, 3) + -0.00121497 *begin_x*begin_y*begin_dx*begin_dy + -8.23227e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000299351 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000930743 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -8.21141e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -8.89294e-06 *lens_ipow(begin_x, 3)*begin_dx + 0.0240582 *begin_x*lens_ipow(begin_dx, 5) + -2.03375e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -7.05119e-11 *lens_ipow(begin_x, 6);
else
  out[4] = 0.0f;
} break;
