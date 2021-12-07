case unknown__petzval__1900__75mm:
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
       + 55.2914 *begin_dx + 0.726822 *begin_x + 14.4587 *begin_dx*begin_lambda + 0.30756 *begin_x*begin_lambda + -20.0206 *begin_dx*lens_ipow(begin_lambda, 2) + 0.519052 *begin_y*begin_dx*begin_dy + 0.0077513 *lens_ipow(begin_y, 2)*begin_dx + -0.429532 *begin_x*lens_ipow(begin_lambda, 2) + 0.117692 *begin_x*lens_ipow(begin_dy, 2) + 0.609379 *begin_x*lens_ipow(begin_dx, 2) + 0.0115469 *begin_x*begin_y*begin_dy + 0.000119884 *begin_x*lens_ipow(begin_y, 2) + 0.0181972 *lens_ipow(begin_x, 2)*begin_dx + 0.000106076 *lens_ipow(begin_x, 3) + 9.748 *begin_dx*lens_ipow(begin_lambda, 3) + 0.210059 *begin_x*lens_ipow(begin_lambda, 3) + 4.25346e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 6.84974e-06 *lens_ipow(begin_x, 3)*begin_lambda + 1.34511e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.000515632 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 1.70763e-05 *lens_ipow(begin_x, 4)*begin_dx + 1.41414e-07 *lens_ipow(begin_x, 5) + -1.66696e-07 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + 56.6978 *lens_ipow(begin_dx, 7)*begin_lambda + 7.01251e-14 *begin_x*lens_ipow(begin_y, 8) + 9.09157e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -5.01211e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda + 7.15036e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_lambda,
       + 55.3114 *begin_dy + 0.728022 *begin_y + 14.3735 *begin_dy*begin_lambda + 0.301612 *begin_y*begin_lambda + -19.9065 *begin_dy*lens_ipow(begin_lambda, 2) + -0.420164 *begin_y*lens_ipow(begin_lambda, 2) + 0.615288 *begin_y*lens_ipow(begin_dy, 2) + 0.118286 *begin_y*lens_ipow(begin_dx, 2) + 0.0183132 *lens_ipow(begin_y, 2)*begin_dy + 0.000106594 *lens_ipow(begin_y, 3) + 0.519284 *begin_x*begin_dx*begin_dy + 0.0118472 *begin_x*begin_y*begin_dx + 0.00776532 *lens_ipow(begin_x, 2)*begin_dy + 0.000122374 *lens_ipow(begin_x, 2)*begin_y + 9.69447 *begin_dy*lens_ipow(begin_lambda, 3) + 0.20509 *begin_y*lens_ipow(begin_lambda, 3) + 7.9563e-06 *lens_ipow(begin_y, 3)*begin_lambda + -0.000645421 *begin_x*begin_y*begin_dx*begin_lambda + 0.000496892 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 1.66908e-05 *lens_ipow(begin_y, 4)*begin_dy + 1.38887e-07 *lens_ipow(begin_y, 5) + 1.14546e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 6.19134 *lens_ipow(begin_dy, 5)*begin_lambda + -6.6536e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 4.06256e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 4) + 0.000158665 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -8.4825e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 1.20626e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 55.2914  + 14.4587 *begin_lambda + -20.0206 *lens_ipow(begin_lambda, 2) + 0.519052 *begin_y*begin_dy + 0.0077513 *lens_ipow(begin_y, 2) + 1.21876 *begin_x*begin_dx + 0.0181972 *lens_ipow(begin_x, 2) + 9.748 *lens_ipow(begin_lambda, 3) + 1.34511e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.00103126 *lens_ipow(begin_x, 3)*begin_dx + 1.70763e-05 *lens_ipow(begin_x, 4) + 396.885 *lens_ipow(begin_dx, 6)*begin_lambda + 0.000181831 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -5.01211e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + 0.519052 *begin_y*begin_dx + 0.235384 *begin_x*begin_dy + 0.0115469 *begin_x*begin_y + -3.33393e-07 *begin_x*lens_ipow(begin_y, 4)*begin_dy + 0.000181831 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -5.01211e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + 0.236573 *begin_y*begin_dx + 0.519284 *begin_x*begin_dy + 0.0118472 *begin_x*begin_y + -0.000645421 *begin_x*begin_y*begin_lambda + -0.000133072 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + 4.06256e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 4) + 0.00031733 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -8.4825e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 1) =  + 55.3114  + 14.3735 *begin_lambda + -19.9065 *lens_ipow(begin_lambda, 2) + 1.23058 *begin_y*begin_dy + 0.0183132 *lens_ipow(begin_y, 2) + 0.519284 *begin_x*begin_dx + 0.00776532 *lens_ipow(begin_x, 2) + 9.69447 *lens_ipow(begin_lambda, 3) + 0.000993784 *lens_ipow(begin_y, 3)*begin_dy + 1.66908e-05 *lens_ipow(begin_y, 4) + 1.14546e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 30.9567 *lens_ipow(begin_dy, 4)*begin_lambda + 0.00031733 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -8.4825e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_lambda, 2)+0.0f;
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
    out(0) =  + 67.9757 *begin_dx + 0.451709 *begin_x + 27.9908 *begin_dx*begin_lambda + 0.605618 *begin_x*begin_lambda + -38.4836 *begin_dx*lens_ipow(begin_lambda, 2) + -48.9311 *begin_dx*lens_ipow(begin_dy, 2) + -49.309 *lens_ipow(begin_dx, 3) + 0.00871613 *lens_ipow(begin_y, 2)*begin_dx + -0.84471 *begin_x*lens_ipow(begin_lambda, 2) + 0.409548 *begin_x*lens_ipow(begin_dy, 2) + 0.386349 *begin_x*lens_ipow(begin_dx, 2) + 0.0243639 *begin_x*begin_y*begin_dy + 0.000226358 *begin_x*lens_ipow(begin_y, 2) + 0.0328186 *lens_ipow(begin_x, 2)*begin_dx + 0.000228771 *lens_ipow(begin_x, 3) + 18.5403 *begin_dx*lens_ipow(begin_lambda, 3) + 0.413546 *begin_x*lens_ipow(begin_lambda, 3) + 1.34484e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.00224199 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -4.1551e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + -0.0591362 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 5) + -9.68204 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 3) + -0.339111 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + 0.000115667 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 3) + 1.1072e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 3) + 3.67444e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.99484e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + 2.70428e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 6);
    out(1) =  + 68.7025 *begin_dy + 0.453095 *begin_y + 22.5603 *begin_dy*begin_lambda + 0.596397 *begin_y*begin_lambda + -23.4562 *begin_dy*lens_ipow(begin_lambda, 2) + -48.4873 *lens_ipow(begin_dy, 3) + -48.8395 *lens_ipow(begin_dx, 2)*begin_dy + -0.82708 *begin_y*lens_ipow(begin_lambda, 2) + 0.424846 *begin_y*lens_ipow(begin_dy, 2) + 0.407672 *begin_y*lens_ipow(begin_dx, 2) + 0.0330859 *lens_ipow(begin_y, 2)*begin_dy + 0.000226163 *lens_ipow(begin_y, 3) + 0.0242362 *begin_x*begin_y*begin_dx + 0.00875289 *lens_ipow(begin_x, 2)*begin_dy + 0.000229662 *lens_ipow(begin_x, 2)*begin_y + 0.402512 *begin_y*lens_ipow(begin_lambda, 3) + 1.26901e-05 *lens_ipow(begin_y, 3)*begin_lambda + 5.87805e-06 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 8.60137 *begin_dy*lens_ipow(begin_lambda, 4) + -0.0240782 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.00123344 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4) + -3.26079e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.00229176 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 1.7426e-06 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*begin_dy + 1.85402e-08 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2) + 8.81501e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.29475e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 5.86032e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5);
    out(2) =  + -1.62863 *begin_dx + -0.0262688 *begin_x + 0.0245379 *begin_dx*begin_lambda + -1.20846 *begin_dx*lens_ipow(begin_dy, 2) + -0.0413256 *begin_y*begin_dx*begin_dy + -0.000289654 *lens_ipow(begin_y, 2)*begin_dx + 4.51629e-06 *lens_ipow(begin_x, 3) + 3.62891 *lens_ipow(begin_dx, 3)*begin_lambda + -0.106821 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + -0.00320177 *begin_x*begin_y*begin_dy*begin_lambda + -1.22108e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.00141683 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -2.23714e-05 *lens_ipow(begin_x, 3)*begin_lambda + 2.09584 *begin_dx*lens_ipow(begin_dy, 4) + -3.63864 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 4.31908 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 1.32974 *lens_ipow(begin_dx, 5) + 0.0253482 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.0182703 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.0957679 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.0329714 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.00289209 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + 0.00105948 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 1.83313e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 1.27416e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + -0.000348114 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.258757 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5) + -0.0299322 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5);
    out(3) =  + -1.63929 *begin_dy + -0.0260494 *begin_y + 0.0706767 *begin_dy*begin_lambda + -0.000724025 *begin_y*begin_lambda + -0.0467094 *begin_dy*lens_ipow(begin_lambda, 2) + 0.847198 *lens_ipow(begin_dy, 3) + 2.94466 *lens_ipow(begin_dx, 2)*begin_dy + 0.000576562 *begin_y*lens_ipow(begin_lambda, 2) + -0.00238355 *begin_y*lens_ipow(begin_dy, 2) + -0.000447435 *lens_ipow(begin_y, 2)*begin_dy + -1.72092e-06 *lens_ipow(begin_y, 3) + 0.0619428 *begin_x*begin_dx*begin_dy + 1.2906e-06 *lens_ipow(begin_x, 2)*begin_y + 0.0184671 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -5.58292e-07 *lens_ipow(begin_y, 3)*begin_lambda + 0.0016336 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -1.65948e-06 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 1.85972 *lens_ipow(begin_dy, 5) + 2.45693 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 1.21336 *lens_ipow(begin_dx, 4)*begin_dy + -0.0171808 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.00570069 *begin_y*lens_ipow(begin_dx, 4) + -0.000282501 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00311602 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.0444021 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.00191712 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -0.000169835 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 5) + -0.325334 *begin_y*lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 4);
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
    domega2_dx0(0, 0) =  + -0.0262688  + 1.35489e-05 *lens_ipow(begin_x, 2) + -0.106821 *lens_ipow(begin_dy, 2)*begin_lambda + -0.00320177 *begin_y*begin_dy*begin_lambda + -1.22108e-05 *lens_ipow(begin_y, 2)*begin_lambda + -0.00283365 *begin_x*begin_dx*begin_lambda + -6.71141e-05 *lens_ipow(begin_x, 2)*begin_lambda + 0.0957679 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.0329714 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.00289209 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + 0.00211895 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + 5.4994e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 1.27416e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + -0.000696229 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + -0.0299322 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5)+0.0f;
    domega2_dx0(0, 1) =  + -0.0413256 *begin_dx*begin_dy + -0.000579307 *begin_y*begin_dx + -0.00320177 *begin_x*begin_dy*begin_lambda + -2.44216e-05 *begin_x*begin_y*begin_lambda + 0.0253482 *begin_dx*lens_ipow(begin_dy, 3) + 0.0182703 *lens_ipow(begin_dx, 3)*begin_dy + 0.00289209 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 2.54833e-05 *begin_x*begin_y*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0619428 *begin_dx*begin_dy + 2.5812e-06 *begin_x*begin_y + 0.0032672 *begin_x*begin_dy*begin_lambda + -3.31897e-06 *begin_x*begin_y*begin_lambda + -0.000282501 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00623205 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 0.00383424 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -0.000169835 *begin_y*begin_dx*lens_ipow(begin_lambda, 5)+0.0f;
    domega2_dx0(1, 1) =  + -0.0260494  + -0.000724025 *begin_lambda + 0.000576562 *lens_ipow(begin_lambda, 2) + -0.00238355 *lens_ipow(begin_dy, 2) + -0.000894871 *begin_y*begin_dy + -5.16276e-06 *lens_ipow(begin_y, 2) + 1.2906e-06 *lens_ipow(begin_x, 2) + 0.0184671 *lens_ipow(begin_dx, 2)*begin_lambda + -1.67488e-06 *lens_ipow(begin_y, 2)*begin_lambda + -1.65948e-06 *lens_ipow(begin_x, 2)*begin_lambda + -0.0171808 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.00570069 *lens_ipow(begin_dx, 4) + -0.000282501 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.0444021 *lens_ipow(begin_dy, 4)*begin_lambda + -0.000169835 *begin_x*begin_dx*lens_ipow(begin_lambda, 5) + -0.325334 *lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 4)+0.0f;
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
  out[4] =  + 0.592268  + 0.849922 *begin_lambda + -1.77848 *lens_ipow(begin_lambda, 2) + 1.74912 *lens_ipow(begin_lambda, 3) + 5.03858e-06 *lens_ipow(begin_y, 2)*begin_lambda + -0.000283222 *begin_x*begin_dx*begin_lambda + -0.666409 *lens_ipow(begin_lambda, 4) + 0.000202257 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.000365222 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000133082 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -1.61209e-05 *lens_ipow(begin_y, 3)*begin_dy + -1.98503e-07 *lens_ipow(begin_y, 4) + -0.000486054 *begin_x*begin_y*begin_dx*begin_dy + -1.6105e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000118627 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.55236e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -3.831e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -7.39072e-08 *lens_ipow(begin_x, 4) + -0.230018 *lens_ipow(begin_dx, 4)*begin_lambda + -7.55608e-08 *lens_ipow(begin_x, 5)*begin_dx + -6.28216e-10 *lens_ipow(begin_x, 6) + -1.39341e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 2) + -6.86882e-11 *lens_ipow(begin_x, 7)*begin_dx + -9.13577e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2) + -4.47414e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + -8.49266e-10 *lens_ipow(begin_x, 7)*lens_ipow(begin_dx, 3) + -9.03951e-16 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2) + 7.41209e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 5)*begin_dy*begin_lambda;
else
  out[4] = 0.0f;
} break;
