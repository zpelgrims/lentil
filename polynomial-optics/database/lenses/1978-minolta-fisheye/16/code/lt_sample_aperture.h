case minolta__fisheye__1978__16mm:
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
       + 37.6685 *begin_dx + 0.759009 *begin_x + -0.126328 *begin_x*begin_lambda + -2.62285 *begin_dx*begin_lambda + 3.3061 *begin_y*begin_dx*begin_dy + 0.0534087 *begin_x*begin_y*begin_dy + 0.0890442 *lens_ipow(begin_x, 2)*begin_dx + 63.1316 *lens_ipow(begin_dx, 3) + 0.0854813 *begin_x*lens_ipow(begin_lambda, 2) + 63.1171 *begin_dx*lens_ipow(begin_dy, 2) + 0.0005434 *begin_x*lens_ipow(begin_y, 2) + 0.000524518 *lens_ipow(begin_x, 3) + 1.09803 *begin_x*lens_ipow(begin_dy, 2) + 4.35379 *begin_x*lens_ipow(begin_dx, 2) + 0.0376109 *lens_ipow(begin_y, 2)*begin_dx + 1.66962 *begin_dx*lens_ipow(begin_lambda, 3) + -6.87775e-06 *lens_ipow(begin_y, 4)*begin_dx + -7.71222e-08 *begin_x*lens_ipow(begin_y, 4) + 41.8824 *begin_dx*lens_ipow(begin_dy, 4) + 0.0610037 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 2.98404 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.00843765 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 0.00036693 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.639147 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.0093082 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 12.6985 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -2.02516e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dx + -5.12895e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4),
       + 0.758933 *begin_y + 37.6595 *begin_dy + -2.58853 *begin_dy*begin_lambda + -0.126325 *begin_y*begin_lambda + 1.07499 *begin_y*lens_ipow(begin_dx, 2) + 0.0891274 *lens_ipow(begin_y, 2)*begin_dy + 4.35648 *begin_y*lens_ipow(begin_dy, 2) + 3.20535 *begin_x*begin_dx*begin_dy + 0.0518898 *begin_x*begin_y*begin_dx + 61.4121 *lens_ipow(begin_dx, 2)*begin_dy + 0.0859262 *begin_y*lens_ipow(begin_lambda, 2) + 0.000522451 *lens_ipow(begin_x, 2)*begin_y + 0.00052592 *lens_ipow(begin_y, 3) + 0.0361946 *lens_ipow(begin_x, 2)*begin_dy + 63.1414 *lens_ipow(begin_dy, 3) + 1.67249 *begin_dy*lens_ipow(begin_lambda, 3) + 0.0870487 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 3.96772 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 9.44877 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.575586 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + 0.00835634 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.000597607 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + 58.9404 *lens_ipow(begin_dx, 4)*begin_dy + 7.34058e-09 *begin_x*lens_ipow(begin_y, 5)*begin_dx*begin_lambda + 2.33481e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 4)*begin_lambda + 0.000132682 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -8.12154e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -1.33636e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 37.6685  + -2.62285 *begin_lambda + 3.3061 *begin_y*begin_dy + 0.0890442 *lens_ipow(begin_x, 2) + 189.395 *lens_ipow(begin_dx, 2) + 63.1171 *lens_ipow(begin_dy, 2) + 8.70759 *begin_x*begin_dx + 0.0376109 *lens_ipow(begin_y, 2) + 1.66962 *lens_ipow(begin_lambda, 3) + -6.87775e-06 *lens_ipow(begin_y, 4) + 41.8824 *lens_ipow(begin_dy, 4) + 0.0610037 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 2.98404 *begin_y*lens_ipow(begin_dy, 3) + 1.91744 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.0279246 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 38.0956 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -2.02516e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)+0.0f;
    dx1_domega0(0, 1) =  + 3.3061 *begin_y*begin_dx + 0.0534087 *begin_x*begin_y + 126.234 *begin_dx*begin_dy + 2.19606 *begin_x*begin_dy + 167.529 *begin_dx*lens_ipow(begin_dy, 3) + 0.122007 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 8.95211 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.025313 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.000733861 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.639147 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 25.3971 *lens_ipow(begin_dx, 3)*begin_dy*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + 2.14999 *begin_y*begin_dx + 3.20535 *begin_x*begin_dy + 0.0518898 *begin_x*begin_y + 122.824 *begin_dx*begin_dy + 0.174097 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 11.9032 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 18.8975 *begin_dx*lens_ipow(begin_dy, 3) + 0.575586 *begin_x*lens_ipow(begin_dy, 3) + 0.000597607 *lens_ipow(begin_x, 3)*begin_dy + 235.762 *lens_ipow(begin_dx, 3)*begin_dy + 7.34058e-09 *begin_x*lens_ipow(begin_y, 5)*begin_lambda + 9.33924e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3)*begin_lambda + 0.000398047 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 37.6595  + -2.58853 *begin_lambda + 0.0891274 *lens_ipow(begin_y, 2) + 8.71295 *begin_y*begin_dy + 3.20535 *begin_x*begin_dx + 61.4121 *lens_ipow(begin_dx, 2) + 0.0361946 *lens_ipow(begin_x, 2) + 189.424 *lens_ipow(begin_dy, 2) + 1.67249 *lens_ipow(begin_lambda, 3) + 0.0870487 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 3.96772 *begin_x*lens_ipow(begin_dx, 3) + 28.3463 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.72676 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.025069 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.000597607 *lens_ipow(begin_x, 3)*begin_dx + 58.9404 *lens_ipow(begin_dx, 4) + 0.000265365 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -8.12154e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_lambda+0.0f;
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
    out(0) =  + 16.2952 *begin_dx + -0.379064 *begin_x + -0.238489 *begin_x*begin_lambda + 0.291671 *begin_y*begin_dx*begin_dy + 0.0341973 *lens_ipow(begin_x, 2)*begin_dx + 0.15748 *begin_x*lens_ipow(begin_lambda, 2) + 0.000233669 *lens_ipow(begin_x, 3) + 0.724948 *begin_x*lens_ipow(begin_dx, 2) + 0.0105974 *lens_ipow(begin_y, 2)*begin_dx + 0.743366 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.0003848 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0400315 *begin_x*begin_y*begin_dy*begin_lambda + 6.57908e-06 *lens_ipow(begin_x, 4)*begin_dx + -3.59621 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.0045124 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.000353389 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 0.127003 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -93.5788 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.000171206 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.97369e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + -0.00055306 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.33021e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -0.393168 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 1.85745e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 4.76628e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -7.84 *begin_y*lens_ipow(begin_dx, 5)*begin_dy*begin_lambda + 1.53606 *begin_x*lens_ipow(begin_dy, 6)*begin_lambda + -8.47081 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3);
    out(1) =  + -0.377566 *begin_y + 16.1692 *begin_dy + -0.254022 *begin_y*begin_lambda + 0.0425349 *lens_ipow(begin_y, 2)*begin_dy + 1.08476 *begin_y*lens_ipow(begin_dy, 2) + 0.291355 *begin_x*begin_dx*begin_dy + 0.173301 *begin_y*lens_ipow(begin_lambda, 2) + 0.000330676 *lens_ipow(begin_y, 3) + 0.0118822 *lens_ipow(begin_x, 2)*begin_dy + 6.15404 *lens_ipow(begin_dy, 3) + 0.578615 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -7.69099e-05 *lens_ipow(begin_y, 3)*begin_lambda + 0.0366091 *begin_x*begin_y*begin_dx*begin_lambda + 0.000383541 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 0.177445 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -72.5367 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 5.16712e-06 *lens_ipow(begin_y, 4)*begin_dy + 0.0594512 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00036082 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -4.06687e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -2.86901 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.124862 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.00472139 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.0183229 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -1.13922 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -14.5614 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.224404 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 1.56218 *begin_y*lens_ipow(begin_dx, 6)*begin_lambda;
    out(2) =  + -0.220124 *begin_dx + -0.0554835 *begin_x + 0.00272005 *begin_x*begin_lambda + 0.000127978 *lens_ipow(begin_x, 2)*begin_dx + -0.00170713 *begin_x*lens_ipow(begin_lambda, 2) + 2.03853e-05 *begin_x*lens_ipow(begin_y, 2) + 2.08709e-05 *lens_ipow(begin_x, 3) + 0.000214237 *lens_ipow(begin_y, 2)*begin_dx + 3.10537e-07 *lens_ipow(begin_x, 4)*begin_dx + 0.268884 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.04149 *begin_x*lens_ipow(begin_dy, 4) + 0.00814963 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.0014028 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 3.17569 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.00757486 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.000896044 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.000443593 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 3.04567e-06 *lens_ipow(begin_y, 4)*begin_dx*begin_lambda + 9.62599e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.000267681 *lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda + -5.30812e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy*begin_lambda + 0.04497 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + 0.0177842 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 0.302398 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 3) + 0.000125373 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.00488721 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + -4.84004e-06 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_lambda, 6) + 3.48966e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 6);
    out(3) =  + -0.0556336 *begin_y + -0.222065 *begin_dy + 0.00353503 *begin_y*begin_lambda + 0.00257455 *begin_y*lens_ipow(begin_dx, 2) + -0.00327772 *begin_y*lens_ipow(begin_dy, 2) + 0.0185986 *begin_x*begin_dx*begin_dy + 0.411785 *lens_ipow(begin_dx, 2)*begin_dy + -0.00244663 *begin_y*lens_ipow(begin_lambda, 2) + 2.09185e-05 *lens_ipow(begin_x, 2)*begin_y + 1.91023e-05 *lens_ipow(begin_y, 3) + 0.00032752 *lens_ipow(begin_x, 2)*begin_dy + 2.79188e-07 *lens_ipow(begin_y, 4)*begin_dy + 1.34053e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.145204 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + 0.00422189 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 7.64554e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 8.80826e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 0.0127026 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 1.13456e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.00061717 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + -3.07033e-07 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + -0.102348 *begin_x*lens_ipow(begin_dx, 5)*begin_dy + 0.228126 *begin_y*lens_ipow(begin_dx, 6) + -6.21447e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 0.00468692 *begin_x*begin_y*lens_ipow(begin_dx, 5) + -7.83111e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + 3.30393e-07 *lens_ipow(begin_x, 5)*begin_dx*lens_ipow(begin_dy, 3) + 0.000411412 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 5)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0554835  + 0.00272005 *begin_lambda + 0.000255957 *begin_x*begin_dx + -0.00170713 *lens_ipow(begin_lambda, 2) + 2.03853e-05 *lens_ipow(begin_y, 2) + 6.26126e-05 *lens_ipow(begin_x, 2) + 1.24215e-06 *lens_ipow(begin_x, 3)*begin_dx + 0.04149 *lens_ipow(begin_dy, 4) + 0.0014028 *begin_y*lens_ipow(begin_dy, 3) + 0.000896044 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.000887185 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + 1.9252e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.59244e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 0.04497 *lens_ipow(begin_dy, 4)*begin_lambda + 0.000376118 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.00977441 *begin_x*begin_dx*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + 3.48966e-06 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 6)+0.0f;
    domega2_dx0(0, 1) =  + 4.07707e-05 *begin_x*begin_y + 0.000428473 *begin_y*begin_dx + 0.268884 *lens_ipow(begin_dx, 3)*begin_dy + 0.0162993 *begin_y*lens_ipow(begin_dx, 3) + 0.0014028 *begin_x*lens_ipow(begin_dy, 3) + 0.0151497 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.00179209 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.000443593 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda + 1.21827e-05 *lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 1.9252e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + 0.000803043 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -5.30812e-06 *lens_ipow(begin_x, 3)*begin_dy*begin_lambda + 0.0355684 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 0.302398 *lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 3) + -1.93601e-05 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 6) + 1.0469e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 6)+0.0f;
    domega2_dx0(1, 0) =  + 0.0185986 *begin_dx*begin_dy + 4.1837e-05 *begin_x*begin_y + 0.000655039 *begin_x*begin_dy + 1.34053e-06 *lens_ipow(begin_y, 3)*begin_dx + 0.145204 *begin_dx*lens_ipow(begin_dy, 3) + 1.52911e-07 *begin_x*lens_ipow(begin_y, 3) + 0.0254052 *begin_x*lens_ipow(begin_dy, 3) + 2.26913e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.00123434 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -1.22813e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2) + -0.102348 *lens_ipow(begin_dx, 5)*begin_dy + -2.48579e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 0.00468692 *begin_y*lens_ipow(begin_dx, 5) + -3.13245e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 1.65197e-06 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 3) + 0.00123424 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 5)*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.0556336  + 0.00353503 *begin_lambda + 0.00257455 *lens_ipow(begin_dx, 2) + -0.00327772 *lens_ipow(begin_dy, 2) + -0.00244663 *lens_ipow(begin_lambda, 2) + 2.09185e-05 *lens_ipow(begin_x, 2) + 5.7307e-05 *lens_ipow(begin_y, 2) + 1.11675e-06 *lens_ipow(begin_y, 3)*begin_dy + 4.02159e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.00844378 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 2.29366e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.000264248 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 2.26913e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.00061717 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -3.07033e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 2) + 0.228126 *lens_ipow(begin_dx, 6) + -1.86434e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 0.00468692 *begin_x*lens_ipow(begin_dx, 5) + -1.56622e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dy+0.0f;
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
  out[4] =  + 0.30175  + 0.358447 *begin_lambda + -0.00976144 *begin_y*begin_dy + -0.00878109 *begin_x*begin_dx + -0.26155 *lens_ipow(begin_dy, 2) + -0.227852 *lens_ipow(begin_dx, 2) + -0.242047 *lens_ipow(begin_lambda, 2) + -1.04282 *lens_ipow(begin_dx, 4) + -0.0325456 *begin_x*lens_ipow(begin_dx, 3) + -1.40154e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -8.8973e-07 *lens_ipow(begin_y, 4) + -8.78176e-07 *lens_ipow(begin_x, 4) + 0.000848054 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + -5.72791 *lens_ipow(begin_dy, 6) + -0.172762 *begin_y*lens_ipow(begin_dy, 5) + -2.40089e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 0.388079 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.02956 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 1.00201e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 1.62711e-11 *lens_ipow(begin_y, 8) + 1.51922e-11 *lens_ipow(begin_x, 8) + -3.89052e-14 *lens_ipow(begin_y, 10) + -2.07782e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + 8.73139e-08 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -2.08713e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4) + -3.60784e-14 *lens_ipow(begin_x, 10) + 7.35753e-15 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 7)*begin_dx + 2.25344e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda;
else
  out[4] = 0.0f;
} break;
