case kodak__petzval__1948__58mm:
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
       + 44.4314 *begin_dx + 0.792291 *begin_x + 0.761035 *begin_dx*begin_lambda + -0.520161 *begin_dx*lens_ipow(begin_lambda, 2) + 1.38736 *begin_dx*lens_ipow(begin_dy, 2) + 0.556785 *begin_y*begin_dx*begin_dy + 0.00964987 *lens_ipow(begin_y, 2)*begin_dx + 0.14045 *begin_x*lens_ipow(begin_dy, 2) + 0.585192 *begin_x*lens_ipow(begin_dx, 2) + 0.0142849 *begin_x*begin_y*begin_dy + 0.000163413 *begin_x*lens_ipow(begin_y, 2) + 0.0200543 *lens_ipow(begin_x, 2)*begin_dx + 0.00012003 *lens_ipow(begin_x, 3) + 0.0477165 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.00351845 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 8.59177e-05 *lens_ipow(begin_x, 4)*begin_dx + 6.61567e-07 *lens_ipow(begin_x, 5) + 3.89879 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 4.29328e-09 *begin_x*lens_ipow(begin_y, 5)*begin_dy + -0.0719371 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -1.25176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.19167e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy,
       + 44.4236 *begin_dy + 0.792148 *begin_y + 0.776576 *begin_dy*begin_lambda + -0.526972 *begin_dy*lens_ipow(begin_lambda, 2) + 1.22909 *lens_ipow(begin_dx, 2)*begin_dy + 0.590742 *begin_y*lens_ipow(begin_dy, 2) + 0.143798 *begin_y*lens_ipow(begin_dx, 2) + 0.0203328 *lens_ipow(begin_y, 2)*begin_dy + 0.000125098 *lens_ipow(begin_y, 3) + 0.558886 *begin_x*begin_dx*begin_dy + 0.0146088 *begin_x*begin_y*begin_dx + 0.00977933 *lens_ipow(begin_x, 2)*begin_dy + 0.000168739 *lens_ipow(begin_x, 2)*begin_y + 0.0501801 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00357861 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 8.42457e-05 *lens_ipow(begin_y, 4)*begin_dy + 6.22491e-07 *lens_ipow(begin_y, 5) + 4.01293 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 1.39225e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -1.85259e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.07148e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -1.53597e-10 *lens_ipow(begin_x, 6)*begin_y*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 44.4314  + 0.761035 *begin_lambda + -0.520161 *lens_ipow(begin_lambda, 2) + 1.38736 *lens_ipow(begin_dy, 2) + 0.556785 *begin_y*begin_dy + 0.00964987 *lens_ipow(begin_y, 2) + 1.17038 *begin_x*begin_dx + 0.0200543 *lens_ipow(begin_x, 2) + 0.14315 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.00703689 *lens_ipow(begin_x, 3)*begin_dx + 8.59177e-05 *lens_ipow(begin_x, 4) + 7.79758 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.215811 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.25176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -1.19167e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + 2.77472 *begin_dx*begin_dy + 0.556785 *begin_y*begin_dx + 0.2809 *begin_x*begin_dy + 0.0142849 *begin_x*begin_y + 15.5952 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 4.29328e-09 *begin_x*lens_ipow(begin_y, 5) + -0.143874 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_dy + -1.25176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -1.19167e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx+0.0f;
    dx1_domega0(1, 0) =  + 2.45819 *begin_dx*begin_dy + 0.287596 *begin_y*begin_dx + 0.558886 *begin_x*begin_dy + 0.0146088 *begin_x*begin_y + 16.0517 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -1.85259e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 44.4236  + 0.776576 *begin_lambda + -0.526972 *lens_ipow(begin_lambda, 2) + 1.22909 *lens_ipow(begin_dx, 2) + 1.18148 *begin_y*begin_dy + 0.0203328 *lens_ipow(begin_y, 2) + 0.558886 *begin_x*begin_dx + 0.00977933 *lens_ipow(begin_x, 2) + 0.15054 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.00715722 *lens_ipow(begin_y, 3)*begin_dy + 8.42457e-05 *lens_ipow(begin_y, 4) + 8.02585 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + 1.39225e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -1.85259e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 2.14296e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy*begin_lambda+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 57.929 *begin_dx + 0.556916 *begin_x + -0.0329632 *begin_x*begin_lambda + -25.9559 *begin_dx*lens_ipow(begin_dy, 2) + -27.7084 *lens_ipow(begin_dx, 3) + 0.407077 *begin_y*begin_dx*begin_dy + 0.0140892 *lens_ipow(begin_y, 2)*begin_dx + 0.0222124 *begin_x*lens_ipow(begin_lambda, 2) + 0.535032 *begin_x*lens_ipow(begin_dy, 2) + 0.758416 *begin_x*lens_ipow(begin_dx, 2) + 0.0352314 *begin_x*begin_y*begin_dy + 0.00039312 *begin_x*lens_ipow(begin_y, 2) + 0.0421927 *lens_ipow(begin_x, 2)*begin_dx + 0.000308262 *lens_ipow(begin_x, 3) + 0.106561 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.0073804 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.000170508 *lens_ipow(begin_x, 4)*begin_dx + 1.28331e-06 *lens_ipow(begin_x, 5) + -1.86118e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -3.12295e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -0.276811 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 9.14768e-09 *begin_x*lens_ipow(begin_y, 5)*begin_dy*begin_lambda;
    out(1) =  + 57.9212 *begin_dy + 0.556841 *begin_y + -0.0323802 *begin_y*begin_lambda + -27.4589 *lens_ipow(begin_dy, 3) + -26.1764 *lens_ipow(begin_dx, 2)*begin_dy + 0.0216661 *begin_y*lens_ipow(begin_lambda, 2) + 0.759258 *begin_y*lens_ipow(begin_dy, 2) + 0.488764 *begin_y*lens_ipow(begin_dx, 2) + 0.0421223 *lens_ipow(begin_y, 2)*begin_dy + 0.000307966 *lens_ipow(begin_y, 3) + 0.398698 *begin_x*begin_dx*begin_dy + 0.033311 *begin_x*begin_y*begin_dx + 0.0141201 *lens_ipow(begin_x, 2)*begin_dy + 0.000388187 *lens_ipow(begin_x, 2)*begin_y + 0.10207 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00721062 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.000376859 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 0.000168652 *lens_ipow(begin_y, 4)*begin_dy + 1.27145e-06 *lens_ipow(begin_y, 5) + 1.46993e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -7.28989e-08 *lens_ipow(begin_x, 4)*begin_y + 0.447231 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2);
    out(2) =  + -1.40845 *begin_dx + -0.0306545 *begin_x + 0.00023907 *begin_x*begin_lambda + -0.737734 *begin_dx*lens_ipow(begin_dy, 2) + 0.806049 *lens_ipow(begin_dx, 3) + -0.0348391 *begin_y*begin_dx*begin_dy + -0.000314392 *lens_ipow(begin_y, 2)*begin_dx + -0.0248234 *begin_x*lens_ipow(begin_dy, 2) + -0.000964257 *begin_x*begin_y*begin_dy + -4.99464e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000539385 *lens_ipow(begin_x, 2)*begin_dx + -2.16149e-06 *lens_ipow(begin_x, 3) + -0.239651 *lens_ipow(begin_dx, 3)*begin_lambda + 0.976033 *begin_dx*lens_ipow(begin_dy, 4) + 1.82526 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.00357274 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.0312388 *begin_x*lens_ipow(begin_dx, 4) + 8.53971e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 1.05372e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.0101301 *begin_dx*lens_ipow(begin_lambda, 5) + -0.00040734 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 7.89562e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4);
    out(3) =  + -1.40815 *begin_dy + -0.0306362 *begin_y + 0.000236412 *begin_y*begin_lambda + 0.811343 *lens_ipow(begin_dy, 3) + 2.0346 *lens_ipow(begin_dx, 2)*begin_dy + 0.00145314 *begin_y*lens_ipow(begin_dx, 2) + -0.000535662 *lens_ipow(begin_y, 2)*begin_dy + -2.16233e-06 *lens_ipow(begin_y, 3) + 0.0525283 *begin_x*begin_dx*begin_dy + -0.000129955 *begin_x*begin_y*begin_dx + 0.000266248 *lens_ipow(begin_x, 2)*begin_dy + -0.268095 *lens_ipow(begin_dy, 3)*begin_lambda + -0.0798762 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.00977396 *begin_dy*lens_ipow(begin_lambda, 4) + 1.54939 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.00393053 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.031067 *begin_y*lens_ipow(begin_dy, 4) + 1.04254e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -2.59103e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.0239333 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 4.69398e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 3.06118e-09 *lens_ipow(begin_x, 4)*begin_y;
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
    domega2_dx0(0, 0) =  + -0.0306545  + 0.00023907 *begin_lambda + -0.0248234 *lens_ipow(begin_dy, 2) + -0.000964257 *begin_y*begin_dy + -4.99464e-06 *lens_ipow(begin_y, 2) + -0.00107877 *begin_x*begin_dx + -6.48447e-06 *lens_ipow(begin_x, 2) + -0.00357274 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.0312388 *lens_ipow(begin_dx, 4) + 1.70794e-05 *begin_x*begin_y*begin_dx*begin_dy + 3.16116e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 2.36869e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)+0.0f;
    domega2_dx0(0, 1) =  + -0.0348391 *begin_dx*begin_dy + -0.000628785 *begin_y*begin_dx + -0.000964257 *begin_x*begin_dy + -9.98927e-06 *begin_x*begin_y + 8.53971e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.00081468 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 3.15825e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0525283 *begin_dx*begin_dy + -0.000129955 *begin_y*begin_dx + 0.000532497 *begin_x*begin_dy + -0.0239333 *lens_ipow(begin_dx, 3)*begin_dy + 9.38796e-09 *begin_x*lens_ipow(begin_y, 3) + 1.22447e-08 *lens_ipow(begin_x, 3)*begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.0306362  + 0.000236412 *begin_lambda + 0.00145314 *lens_ipow(begin_dx, 2) + -0.00107132 *begin_y*begin_dy + -6.48699e-06 *lens_ipow(begin_y, 2) + -0.000129955 *begin_x*begin_dx + -0.00393053 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.031067 *lens_ipow(begin_dy, 4) + 3.12762e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -7.77308e-06 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.40819e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 3.06118e-09 *lens_ipow(begin_x, 4)+0.0f;
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
  out[4] =  + 0.53546  + 0.644943 *begin_lambda + -0.888791 *lens_ipow(begin_lambda, 2) + 0.430822 *lens_ipow(begin_lambda, 3) + -0.000664659 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00338703 *begin_x*begin_y*begin_dx*begin_dy + -0.000114326 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000566222 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.00177956 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.000112054 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -2.97932e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -8.75096e-05 *lens_ipow(begin_x, 3)*begin_dx + -1.12123e-06 *lens_ipow(begin_x, 4) + -0.0449872 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.0039516 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + -0.000139045 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -2.386e-06 *lens_ipow(begin_y, 5)*begin_dy + -1.70635e-08 *lens_ipow(begin_y, 6) + 7.39176e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -3.6793e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -2.90206e-10 *lens_ipow(begin_x, 7)*begin_dx + -6.78241e-12 *lens_ipow(begin_x, 8);
else
  out[4] = 0.0f;
} break;
