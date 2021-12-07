// this file has been manually fixed up
// removing k<100 condition
// removing prev_sqr_err checking
// swapped the jacobian of another lens (domega2_dx0) to fix convergence

case angenieux__double_gauss__1953__49mm:
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
  for(int k=0;k<300&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    const double begin_x = x;
    const double begin_y = y;
    const double begin_dx = dx;
    const double begin_dy = dy;
    const double begin_lambda = lambda;
    const Eigen::Vector2d pred_ap(
       + 27.5808 *begin_dx + 0.192185 *begin_x + 1.76587 *begin_dx*begin_lambda + 0.084184 *begin_x*begin_lambda + -15.2207 *begin_dx*lens_ipow(begin_dy, 2) + -15.1519 *lens_ipow(begin_dx, 3) + -0.0879496 *begin_y*begin_dx*begin_dy + -0.111422 *begin_x*lens_ipow(begin_dy, 2) + -0.192698 *begin_x*lens_ipow(begin_dx, 2) + -0.000294599 *begin_x*lens_ipow(begin_y, 2) + -0.000304391 *lens_ipow(begin_x, 3) + -8.35927e-07 *begin_x*lens_ipow(begin_y, 4) + -1.72004e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 9.98088e-06 *lens_ipow(begin_x, 4)*begin_dx + -7.28996e-07 *lens_ipow(begin_x, 5) + 0.00027559 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy,
       + 27.7726 *begin_dy + 0.18399 *begin_y + 1.41182 *begin_dy*begin_lambda + 0.102705 *begin_y*begin_lambda + -15.1198 *lens_ipow(begin_dy, 3) + -15.2185 *lens_ipow(begin_dx, 2)*begin_dy + -0.000388737 *lens_ipow(begin_y, 3) + -0.000298172 *lens_ipow(begin_x, 2)*begin_y + -0.337615 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.2008 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.160158 *begin_x*begin_dx*begin_dy*begin_lambda + 1.10863e-05 *lens_ipow(begin_y, 4)*begin_dy + -1.73492e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -8.06362e-07 *lens_ipow(begin_x, 4)*begin_y + -1.64839e-09 *lens_ipow(begin_y, 7) + 0.000257524 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 27.5808  + 1.76587 *begin_lambda + -15.2207 *lens_ipow(begin_dy, 2) + -45.4557 *lens_ipow(begin_dx, 2) + -0.0879496 *begin_y*begin_dy + -0.385395 *begin_x*begin_dx + 9.98088e-06 *lens_ipow(begin_x, 4) + 0.000551179 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + -30.4413 *begin_dx*begin_dy + -0.0879496 *begin_y*begin_dx + -0.222844 *begin_x*begin_dy + 0.00027559 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)+0.0f;
    dx1_domega0(1, 0) =  + -30.437 *begin_dx*begin_dy + -0.401601 *begin_y*begin_dx*begin_lambda + -0.160158 *begin_x*begin_dy*begin_lambda + 0.000257524 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 1) =  + 27.7726  + 1.41182 *begin_lambda + -45.3593 *lens_ipow(begin_dy, 2) + -15.2185 *lens_ipow(begin_dx, 2) + -0.67523 *begin_y*begin_dy*begin_lambda + -0.160158 *begin_x*begin_dx*begin_lambda + 1.10863e-05 *lens_ipow(begin_y, 4) + 0.000515048 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 49.0822 *begin_dx + -0.645581 *begin_x + 0.737721 *begin_x*begin_lambda + -20.5624 *begin_dx*lens_ipow(begin_dy, 2) + -20.2574 *lens_ipow(begin_dx, 3) + 0.00542395 *lens_ipow(begin_y, 2)*begin_dx + -0.541384 *begin_x*lens_ipow(begin_lambda, 2) + 0.251372 *begin_x*lens_ipow(begin_dy, 2) + 0.292751 *begin_x*lens_ipow(begin_dx, 2) + 0.00634489 *begin_x*begin_y*begin_dy + -0.00112497 *begin_x*lens_ipow(begin_y, 2) + -0.00121408 *lens_ipow(begin_x, 3) + 0.0231625 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.000583182 *lens_ipow(begin_x, 3)*begin_lambda + -1.39787e-06 *lens_ipow(begin_x, 5) + -1.69511e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4);
    out(1) =  + 49.6001 *begin_dy + -0.665901 *begin_y + 0.815492 *begin_y*begin_lambda + -22.0883 *lens_ipow(begin_dy, 3) + -21.9766 *lens_ipow(begin_dx, 2)*begin_dy + -0.561464 *begin_y*lens_ipow(begin_lambda, 2) + 0.270037 *begin_y*lens_ipow(begin_dy, 2) + 0.179023 *begin_y*lens_ipow(begin_dx, 2) + -0.00121784 *lens_ipow(begin_y, 3) + -0.00111694 *lens_ipow(begin_x, 2)*begin_y + 2.02553e-05 *lens_ipow(begin_x, 4)*begin_dy + -1.08659e-06 *lens_ipow(begin_x, 4)*begin_y + 0.102879 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -0.00498764 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 1.82401e-07 *lens_ipow(begin_y, 6)*begin_dy + -1.20198e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5);
    out(2) =  + -0.609749 *begin_dx + -0.0115036 *begin_x + -0.0107814 *begin_x*begin_lambda + 0.172424 *begin_dx*lens_ipow(begin_dy, 2) + 0.264692 *lens_ipow(begin_dx, 3) + 0.00751845 *begin_x*lens_ipow(begin_lambda, 2) + -0.00236438 *begin_x*lens_ipow(begin_dy, 2) + -9.29027e-05 *begin_x*begin_y*begin_dy + 9.96414e-06 *begin_x*lens_ipow(begin_y, 2) + 1.12835e-05 *lens_ipow(begin_x, 3) + 2.33684e-08 *begin_x*lens_ipow(begin_y, 4) + 3.88426e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 4.94151e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -5.57988e-07 *lens_ipow(begin_x, 4)*begin_dx + 1.90764e-08 *lens_ipow(begin_x, 5) + 0.000777196 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2);
    out(3) =  + -0.611352 *begin_dy + -0.0115421 *begin_y + -0.010617 *begin_y*begin_lambda + 0.275255 *lens_ipow(begin_dy, 3) + 0.358756 *lens_ipow(begin_dx, 2)*begin_dy + 0.00737512 *begin_y*lens_ipow(begin_lambda, 2) + -0.00466356 *begin_y*lens_ipow(begin_dx, 2) + 1.29089e-05 *lens_ipow(begin_y, 3) + 0.00418177 *begin_x*begin_dx*begin_dy + -0.000124538 *begin_x*begin_y*begin_dx + 9.90669e-06 *lens_ipow(begin_x, 2)*begin_y + -5.43968e-07 *lens_ipow(begin_y, 4)*begin_dy + 5.00651e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.50954e-08 *lens_ipow(begin_x, 4)*begin_y + 4.73572e-11 *lens_ipow(begin_y, 7) + -3.90425e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy;
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
    // domega2_dx0(0, 0) =  + -0.0115036  + -0.0107814 *begin_lambda + 0.00751845 *lens_ipow(begin_lambda, 2) + -0.00236438 *lens_ipow(begin_dy, 2) + -9.29027e-05 *begin_y*begin_dy + 9.96414e-06 *lens_ipow(begin_y, 2) + 3.38504e-05 *lens_ipow(begin_x, 2) + 2.33684e-08 *lens_ipow(begin_y, 4) + 7.76852e-05 *begin_x*begin_y*begin_dx*begin_dy + 1.48245e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.23195e-06 *lens_ipow(begin_x, 3)*begin_dx + 9.53818e-08 *lens_ipow(begin_x, 4)+0.0f;
    // domega2_dx0(0, 1) =  + -9.29027e-05 *begin_x*begin_dy + 1.99283e-05 *begin_x*begin_y + 9.34736e-08 *begin_x*lens_ipow(begin_y, 3) + 3.88426e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 9.88302e-08 *lens_ipow(begin_x, 3)*begin_y + 0.00155439 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2)+0.0f;
    // domega2_dx0(1, 0) =  + 0.00418177 *begin_dx*begin_dy + -0.000124538 *begin_y*begin_dx + 1.98134e-05 *begin_x*begin_y + 1.0013e-07 *begin_x*lens_ipow(begin_y, 3) + 1.00381e-07 *lens_ipow(begin_x, 3)*begin_y + -1.5617e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy+0.0f;
    // domega2_dx0(1, 1) =  + -0.0115421  + -0.010617 *begin_lambda + 0.00737512 *lens_ipow(begin_lambda, 2) + -0.00466356 *lens_ipow(begin_dx, 2) + 3.87266e-05 *lens_ipow(begin_y, 2) + -0.000124538 *begin_x*begin_dx + 9.90669e-06 *lens_ipow(begin_x, 2) + -2.17587e-06 *lens_ipow(begin_y, 3)*begin_dy + 1.50195e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 2.50954e-08 *lens_ipow(begin_x, 4) + 3.315e-10 *lens_ipow(begin_y, 6) + -7.80849e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dy+0.0f;
    // BUGFIX: jacobian from lenses.js implementation, this fixes the issue where the newton iterations do not convergence.
    domega2_dx0(0, 0) =  + -0.0841526  + 0.0180182 *lens_ipow(begin_dy, 2) + 0.0627794 *lens_ipow(begin_dx, 2) + 0.0014138 *begin_y*begin_dy + 6.7031e-05 *lens_ipow(begin_y, 2) + 0.00539724 *begin_x*begin_dx + 0.000241426 *lens_ipow(begin_x, 2) + -1.91925e-05 *begin_x*begin_y*begin_dx*begin_dy + -6.95202e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 0.128222 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -6.09124e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 1.94672e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00176443 *lens_ipow(begin_lambda, 8) + -0.0310725 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 5) + 0.000176266 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -0.0150674 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 6) + -1.52378e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6) + -1.64675e-07 *lens_ipow(begin_x, 5)*begin_dx*lens_ipow(begin_lambda, 2) + -1.11794 *lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 6) + -3.65549e-15 *lens_ipow(begin_y, 10) + 7.65407e-08 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -3.05221e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_lambda, 4) + -2.93555e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4) + -1.60463e-13 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2) + -3.61904e-14 *lens_ipow(begin_x, 10);
    domega2_dx0(0, 1) =  + 0.0445784 *begin_dx*begin_dy + 0.00270553 *begin_y*begin_dx + 0.0014138 *begin_x*begin_dy + 0.000134062 *begin_x*begin_y + 0.00458532 *begin_y*lens_ipow(begin_dx, 3) + -9.59623e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.0028004 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -2.08561e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -6.09124e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 1.29781e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2) + -2.57134e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy + -0.0155363 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 5) + 0.000176266 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 5) + -3.04756e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + -0.121145 *begin_dx*begin_dy*lens_ipow(begin_lambda, 8) + -3.65549e-14 *begin_x*lens_ipow(begin_y, 9) + 1.27568e-08 *lens_ipow(begin_x, 6)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -1.67746e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3) + -3.56585e-14 *lens_ipow(begin_x, 9)*begin_y;
    domega2_dx0(1, 0) =  + 1.58352e-06  + 0.037641 *begin_dx*begin_dy + 0.00114241 *begin_y*begin_dx + 0.00232168 *begin_x*begin_dy + 0.000185005 *begin_x*begin_y + -0.0122638 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000485762 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -8.08543e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000863194 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + 0.061474 *begin_x*lens_ipow(begin_dy, 5) + 0.0636202 *begin_x*lens_ipow(begin_dx, 4)*begin_dy + -1.23491e-09 *begin_x*lens_ipow(begin_y, 5) + -4.62094e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3) + 2.4501e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 3) + 8.40323e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx*begin_dy*begin_lambda + 1.86325e-11 *lens_ipow(begin_y, 8)*begin_dx*begin_dy + 5.56914e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 8.51035e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -2.29075e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3);
    domega2_dx0(1, 1) =  + -0.0841902  + 0.0628713 *lens_ipow(begin_dy, 2) + 0.000197341 *begin_dx*begin_dy + 0.0140972 *lens_ipow(begin_dx, 2) + 0.00543763 *begin_y*begin_dy + 0.000245926 *lens_ipow(begin_y, 2) + 0.00114241 *begin_x*begin_dx + 9.25026e-05 *lens_ipow(begin_x, 2) + 5.93229e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.000485762 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -8.08543e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 0.134065 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.00172639 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -3.08727e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -1.54031e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -0.000968929 *lens_ipow(begin_lambda, 7) + 0.00053879 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 5) + -2.07699e-07 *lens_ipow(begin_y, 5)*begin_dy*lens_ipow(begin_lambda, 2) + -7.57489e-12 *lens_ipow(begin_y, 8) + 1.12043e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda + -1.13772 *lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 6) + -3.63686e-09 *lens_ipow(begin_y, 6)*lens_ipow(begin_lambda, 4) + 1.4906e-10 *begin_x*lens_ipow(begin_y, 7)*begin_dx*begin_dy + 2.78457e-05 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 6.38276e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -8.59032e-14 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2);
    Eigen::Matrix2d invJ = domega2_dx0.inverse().eval();
    Eigen::Vector2d solution_pos = 0.72 * invJ * delta_out; // default newton-raphson
    x += solution_pos(0);
    y += solution_pos(1);
    // if(sqr_err>prev_sqr_err) error |= 1;
    // if(sqr_ap_err>prev_sqr_ap_err) error |= 2;
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
  out[4] =  + 0.328577  + 0.347462 *begin_lambda + -0.236432 *lens_ipow(begin_lambda, 2) + -0.000978559 *begin_y*begin_dy + -0.00096636 *begin_x*begin_dx + -0.210461 *lens_ipow(begin_dy, 4) + -0.423925 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.20998 *lens_ipow(begin_dx, 4) + -0.000245422 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000105437 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -6.2113e-08 *lens_ipow(begin_y, 4) + -0.00026575 *begin_x*begin_y*begin_dx*begin_dy + -0.000103071 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000240594 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -6.26293e-08 *lens_ipow(begin_x, 4) + -6.24307e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4);
else
  out[4] = 0.0f;
} break;
