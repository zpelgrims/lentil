case asahi__takumar__1969__85mm:
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
       + 51.7353 *begin_dx + 0.338736 *begin_x + 10.3533 *begin_dx*begin_lambda + 0.176749 *begin_x*begin_lambda + -7.07507 *begin_dx*lens_ipow(begin_lambda, 2) + -29.793 *begin_dx*lens_ipow(begin_dy, 2) + -29.5833 *lens_ipow(begin_dx, 3) + -0.106863 *begin_y*begin_dx*begin_dy + 0.0012989 *lens_ipow(begin_y, 2)*begin_dx + -0.120922 *begin_x*lens_ipow(begin_lambda, 2) + -0.163605 *begin_x*lens_ipow(begin_dy, 2) + -0.280733 *begin_x*lens_ipow(begin_dx, 2) + 0.000813969 *begin_x*begin_y*begin_dy + -5.46827e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00216317 *lens_ipow(begin_x, 2)*begin_dx + -5.29176e-05 *lens_ipow(begin_x, 3) + -0.363388 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.343916 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.00598417 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.222924 *begin_x*lens_ipow(begin_dy, 4) + -0.00779999 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.016676 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda,
       + 51.7458 *begin_dy + 0.33896 *begin_y + 10.3081 *begin_dy*begin_lambda + 0.174589 *begin_y*begin_lambda + -7.04044 *begin_dy*lens_ipow(begin_lambda, 2) + -29.5302 *lens_ipow(begin_dy, 3) + -29.7097 *lens_ipow(begin_dx, 2)*begin_dy + -0.119324 *begin_y*lens_ipow(begin_lambda, 2) + -0.278849 *begin_y*lens_ipow(begin_dy, 2) + -0.164669 *begin_y*lens_ipow(begin_dx, 2) + 0.00214903 *lens_ipow(begin_y, 2)*begin_dy + -5.14451e-05 *lens_ipow(begin_y, 3) + -0.133046 *begin_x*begin_dx*begin_dy + 0.000880539 *begin_x*begin_y*begin_dx + 0.00123277 *lens_ipow(begin_x, 2)*begin_dy + -4.93721e-05 *lens_ipow(begin_x, 2)*begin_y + 0.228092 *begin_y*lens_ipow(begin_dx, 4) + -0.00817597 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.281369 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.00497022 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.107823 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + -1.1996e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 51.7353  + 10.3533 *begin_lambda + -7.07507 *lens_ipow(begin_lambda, 2) + -29.793 *lens_ipow(begin_dy, 2) + -88.7499 *lens_ipow(begin_dx, 2) + -0.106863 *begin_y*begin_dy + 0.0012989 *lens_ipow(begin_y, 2) + -0.561467 *begin_x*begin_dx + 0.00216317 *lens_ipow(begin_x, 2) + -0.363388 *begin_y*lens_ipow(begin_dy, 3) + -1.03175 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0179525 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00779999 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.0333519 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -59.5859 *begin_dx*begin_dy + -0.106863 *begin_y*begin_dx + -0.327209 *begin_x*begin_dy + 0.000813969 *begin_x*begin_y + -1.09016 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.343916 *begin_y*lens_ipow(begin_dx, 3) + 0.891695 *begin_x*lens_ipow(begin_dy, 3) + -0.0156 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.016676 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + -59.4194 *begin_dx*begin_dy + -0.329338 *begin_y*begin_dx + -0.133046 *begin_x*begin_dy + 0.000880539 *begin_x*begin_y + 0.912368 *begin_y*lens_ipow(begin_dx, 3) + -0.0163519 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.844106 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.107823 *begin_x*begin_y*lens_ipow(begin_dy, 4)+0.0f;
    dx1_domega0(1, 1) =  + 51.7458  + 10.3081 *begin_lambda + -7.04044 *lens_ipow(begin_lambda, 2) + -88.5907 *lens_ipow(begin_dy, 2) + -29.7097 *lens_ipow(begin_dx, 2) + -0.557698 *begin_y*begin_dy + 0.00214903 *lens_ipow(begin_y, 2) + -0.133046 *begin_x*begin_dx + 0.00123277 *lens_ipow(begin_x, 2) + -0.00817597 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.281369 *begin_x*lens_ipow(begin_dx, 3) + -0.0149107 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.431294 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3)+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 84.2638 *begin_dx + -0.0499727 *begin_x + 1.09612 *begin_dx*begin_lambda + 0.0840945 *begin_x*begin_lambda + -33.6235 *begin_dx*lens_ipow(begin_dy, 2) + -34.77 *lens_ipow(begin_dx, 3) + 0.0881999 *begin_y*begin_dx*begin_dy + 0.00924675 *begin_x*begin_y*begin_dy + -0.000108135 *begin_x*lens_ipow(begin_y, 2) + 0.0139178 *lens_ipow(begin_x, 2)*begin_dx + -0.000115728 *lens_ipow(begin_x, 3) + 0.0187681 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 2.19809 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -0.0180875 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 8.75365 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -2.04032 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.0193498 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0215883 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.000299381 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -19.6427 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 11.9329 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 0.000534663 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2);
    out(1) =  + 84.2309 *begin_dy + -0.111462 *begin_y + 1.14475 *begin_dy*begin_lambda + 0.31634 *begin_y*begin_lambda + -34.7408 *lens_ipow(begin_dy, 3) + -33.5667 *lens_ipow(begin_dx, 2)*begin_dy + -0.213372 *begin_y*lens_ipow(begin_lambda, 2) + 0.578243 *begin_y*lens_ipow(begin_dy, 2) + 0.0139516 *lens_ipow(begin_y, 2)*begin_dy + -0.000116248 *lens_ipow(begin_y, 3) + 0.0880602 *begin_x*begin_dx*begin_dy + 0.00923918 *begin_x*begin_y*begin_dx + -0.00010834 *lens_ipow(begin_x, 2)*begin_y + 2.49343 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.018945 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -3.65139 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.0221381 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.000309896 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.0190619 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0183779 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.0003226 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 2.04758 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4);
    out(2) =  + -0.908266 *begin_dx + -0.0106622 *begin_x + -0.00312394 *begin_x*begin_lambda + 0.447565 *lens_ipow(begin_dx, 3) + 1.07158e-05 *lens_ipow(begin_y, 2)*begin_dx + 0.00218115 *begin_x*lens_ipow(begin_lambda, 2) + -9.20379e-05 *begin_x*begin_y*begin_dy + 1.84421e-06 *begin_x*lens_ipow(begin_y, 2) + -7.01229e-05 *lens_ipow(begin_x, 2)*begin_dx + 1.76432e-06 *lens_ipow(begin_x, 3) + 0.202013 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.00098138 *begin_y*begin_dx*begin_dy*begin_lambda + -0.0233597 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + -0.26762 *lens_ipow(begin_dx, 5) + 0.0294073 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 5.27416e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -0.170657 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.000171122 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.0117028 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 4.25681e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -6.05378e-07 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -0.0179475 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5);
    out(3) =  + -0.904588 *begin_dy + -0.0106583 *begin_y + -0.00312097 *begin_y*begin_lambda + 0.385287 *lens_ipow(begin_dy, 3) + 0.761124 *lens_ipow(begin_dx, 2)*begin_dy + 0.00216928 *begin_y*lens_ipow(begin_lambda, 2) + -7.71459e-05 *lens_ipow(begin_y, 2)*begin_dy + 1.76052e-06 *lens_ipow(begin_y, 3) + 0.00926996 *begin_x*begin_dx*begin_dy + -8.64274e-05 *begin_x*begin_y*begin_dx + 1.80402e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0185379 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.478092 *lens_ipow(begin_dx, 4)*begin_dy + -0.00446808 *begin_y*lens_ipow(begin_dy, 4) + 0.00033264 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.0674016 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 0.000376803 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.000361299 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -2.30413 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5) + -0.0615954 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + 9.55541e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 2.09215e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.0106622  + -0.00312394 *begin_lambda + 0.00218115 *lens_ipow(begin_lambda, 2) + -9.20379e-05 *begin_y*begin_dy + 1.84421e-06 *lens_ipow(begin_y, 2) + -0.000140246 *begin_x*begin_dx + 5.29297e-06 *lens_ipow(begin_x, 2) + -0.0233597 *lens_ipow(begin_dy, 2)*begin_lambda + 0.0294073 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 1.05483e-05 *begin_x*begin_y*begin_dx*begin_dy + -0.0117028 *lens_ipow(begin_dx, 4)*begin_lambda + 1.27704e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -6.05378e-07 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -0.0179475 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5)+0.0f;
    domega2_dx0(0, 1) =  + 2.14316e-05 *begin_y*begin_dx + -9.20379e-05 *begin_x*begin_dy + 3.68842e-06 *begin_x*begin_y + -0.00098138 *begin_dx*begin_dy*begin_lambda + 5.27416e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.000342244 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + -1.81614e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy+0.0f;
    domega2_dx0(1, 0) =  + 0.00926996 *begin_dx*begin_dy + -8.64274e-05 *begin_y*begin_dx + 3.60804e-06 *begin_x*begin_y + 0.00066528 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.000722599 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + 1.91108e-08 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 6.27645e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.0106583  + -0.00312097 *begin_lambda + 0.00216928 *lens_ipow(begin_lambda, 2) + -0.000154292 *begin_y*begin_dy + 5.28155e-06 *lens_ipow(begin_y, 2) + -8.64274e-05 *begin_x*begin_dx + 1.80402e-06 *lens_ipow(begin_x, 2) + -0.0185379 *lens_ipow(begin_dx, 2)*begin_lambda + -0.00446808 *lens_ipow(begin_dy, 4) + 0.0674016 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 0.000753605 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.0615954 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + 2.86662e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 4.1843e-08 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy+0.0f;
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
if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;
const double begin_x = x;
const double begin_y = y;
const double begin_dx = dx;
const double begin_dy = dy;
const double begin_lambda = lambda;
if(error==0)
  out[4] =  + 2.14237 *begin_lambda + -4.76276 *lens_ipow(begin_lambda, 2) + 0.0163816 *lens_ipow(begin_dy, 2) + 4.96598 *lens_ipow(begin_lambda, 3) + -1.99875 *lens_ipow(begin_lambda, 4) + -0.532897 *lens_ipow(begin_dy, 4) + -1.07862 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.163082 *lens_ipow(begin_dx, 4) + -0.0151502 *begin_y*lens_ipow(begin_dy, 3) + -0.0156894 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000250687 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -9.73165e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.016156 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00033774 *begin_x*begin_y*begin_dx*begin_dy + -9.91083e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.92699e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.68764 *lens_ipow(begin_dx, 6) + -0.111266 *begin_x*lens_ipow(begin_dx, 5) + -0.00363696 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -6.74243e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -6.20177e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -9.66602e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda;
else
  out[4] = 0.0f;
} break;
