case minolta__fisheye__1978__22mm:
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
       + 51.0305 *begin_dx + 0.733929 *begin_x + -1.48794 *begin_dx*begin_lambda + -0.0326085 *begin_x*begin_lambda + 87.127 *lens_ipow(begin_dx, 3) + 4.36432 *begin_x*lens_ipow(begin_dx, 2) + 0.000116309 *begin_x*lens_ipow(begin_y, 2) + 0.0649506 *lens_ipow(begin_x, 2)*begin_dx + 0.000279019 *lens_ipow(begin_x, 3) + 243.947 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 9.57984 *begin_y*begin_dx*begin_dy*begin_lambda + 0.100881 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 3.00329 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.106223 *begin_x*begin_y*begin_dy*begin_lambda + 0.000408303 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.0912152 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -262.888 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -13.3903 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -3.23379 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.11432 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 4.03962 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + -0.000573832 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 4),
       + 51.028 *begin_dy + 0.733959 *begin_y + -1.48445 *begin_dy*begin_lambda + -0.0327609 *begin_y*begin_lambda + 87.2516 *lens_ipow(begin_dy, 3) + 4.37067 *begin_y*lens_ipow(begin_dy, 2) + 0.0650749 *lens_ipow(begin_y, 2)*begin_dy + 0.000279958 *lens_ipow(begin_y, 3) + 0.0136364 *lens_ipow(begin_x, 2)*begin_dy + 0.000250551 *lens_ipow(begin_x, 2)*begin_y + 326.528 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 4.01016 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 12.349 *begin_x*begin_dx*begin_dy*begin_lambda + 0.142015 *begin_x*begin_y*begin_dx*begin_lambda + 0.0382774 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -298.312 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -3.65448 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -11.2652 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.129422 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.000179597 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 2) + -0.0419115 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -0.000404068 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 5)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 51.0305  + -1.48794 *begin_lambda + 261.381 *lens_ipow(begin_dx, 2) + 8.72865 *begin_x*begin_dx + 0.0649506 *lens_ipow(begin_x, 2) + 243.947 *lens_ipow(begin_dy, 2)*begin_lambda + 9.57984 *begin_y*begin_dy*begin_lambda + 0.100881 *lens_ipow(begin_y, 2)*begin_lambda + -0.0912152 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -262.888 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -13.3903 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 4.03962 *begin_y*begin_dy*lens_ipow(begin_lambda, 4)+0.0f;
    dx1_domega0(0, 1) =  + 487.894 *begin_dx*begin_dy*begin_lambda + 9.57984 *begin_y*begin_dx*begin_lambda + 6.00657 *begin_x*begin_dy*begin_lambda + 0.106223 *begin_x*begin_y*begin_lambda + -525.775 *begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -13.3903 *begin_y*begin_dx*lens_ipow(begin_lambda, 3) + -6.46758 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -0.11432 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 4.03962 *begin_y*begin_dx*lens_ipow(begin_lambda, 4)+0.0f;
    dx1_domega0(1, 0) =  + 653.056 *begin_dx*begin_dy*begin_lambda + 8.02031 *begin_y*begin_dx*begin_lambda + 12.349 *begin_x*begin_dy*begin_lambda + 0.142015 *begin_x*begin_y*begin_lambda + -596.625 *begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -7.30895 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -11.2652 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.129422 *begin_x*begin_y*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 1) =  + 51.028  + -1.48445 *begin_lambda + 261.755 *lens_ipow(begin_dy, 2) + 8.74133 *begin_y*begin_dy + 0.0650749 *lens_ipow(begin_y, 2) + 0.0136364 *lens_ipow(begin_x, 2) + 326.528 *lens_ipow(begin_dx, 2)*begin_lambda + 12.349 *begin_x*begin_dx*begin_lambda + 0.0382774 *lens_ipow(begin_x, 2)*begin_lambda + -298.312 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -11.2652 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.0419115 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3)+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 22.2439 *begin_dx + -0.428004 *begin_x + -0.0608449 *begin_x*begin_lambda + 0.322731 *begin_y*begin_dx*begin_dy + 0.00956178 *lens_ipow(begin_y, 2)*begin_dx + 0.000111309 *begin_x*lens_ipow(begin_y, 2) + 9.96057e-05 *lens_ipow(begin_x, 3) + 0.725951 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 1.77434 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.0456289 *begin_x*begin_y*begin_dy*begin_lambda + 0.0659662 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -0.0340894 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00128692 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000113692 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 0.000401697 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 31.3123 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + 7.83337 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.142573 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 0.00213764 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.0383609 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 3) + 244.369 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.565547 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4);
    out(1) =  + 21.8406 *begin_dy + -0.434039 *begin_y + 0.570717 *begin_dy*begin_lambda + -0.0520975 *begin_y*begin_lambda + 8.26172 *lens_ipow(begin_dy, 3) + 10.0879 *lens_ipow(begin_dx, 2)*begin_dy + 0.00013764 *lens_ipow(begin_y, 3) + 0.646032 *begin_x*begin_dx*begin_dy + 0.0126321 *lens_ipow(begin_x, 2)*begin_dy + 0.000150695 *lens_ipow(begin_x, 2)*begin_y + 2.83193 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 1.31573 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.0817122 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.0679595 *begin_x*begin_y*begin_dx*begin_lambda + -0.0581486 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -2.81476 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -1.2458 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.0828962 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 0.013491 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.00038029 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy + 2.42076e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + 0.0785985 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5);
    out(2) =  + -0.22432 *begin_dx + -0.0400776 *begin_x + 0.000801607 *begin_x*begin_lambda + 0.000156956 *lens_ipow(begin_y, 2)*begin_dx + 7.75964e-06 *begin_x*lens_ipow(begin_y, 2) + 9.30339e-05 *lens_ipow(begin_x, 2)*begin_dx + 8.02265e-06 *lens_ipow(begin_x, 3) + 0.0175383 *begin_dx*lens_ipow(begin_lambda, 3) + 0.510957 *begin_dx*lens_ipow(begin_dy, 4) + 0.0567796 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + 1.06816 *begin_y*lens_ipow(begin_dx, 5)*begin_dy + 0.155518 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -0.653231 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 0.0108262 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + 0.000332222 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 5.17296e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 3.99311e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 1.16052e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 0.0118806 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.000334481 *lens_ipow(begin_y, 3)*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + 2.01093e-06 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_lambda, 3) + 1.04122e-09 *begin_x*lens_ipow(begin_y, 5)*begin_dy*begin_lambda;
    out(3) =  + -0.255428 *begin_dy + -0.0409685 *begin_y + 0.0317715 *begin_dy*begin_lambda + 0.00324897 *begin_y*begin_lambda + 0.722666 *lens_ipow(begin_dy, 3) + -0.00214014 *begin_y*lens_ipow(begin_lambda, 2) + 0.0315341 *begin_y*lens_ipow(begin_dy, 2) + 0.0032017 *begin_y*lens_ipow(begin_dx, 2) + 0.0005702 *lens_ipow(begin_y, 2)*begin_dy + 1.01785e-05 *lens_ipow(begin_y, 3) + 0.000244052 *lens_ipow(begin_x, 2)*begin_dy + 9.51457e-06 *lens_ipow(begin_x, 2)*begin_y + 0.907098 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.0255194 *begin_x*begin_dx*begin_dy*begin_lambda + 0.00430758 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 8.03303e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 0.206414 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 1.18787e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 0.00550053 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 8.0587e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -4.20111e-09 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_lambda, 2) + 0.00776074 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5);
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
    domega2_dx0(0, 0) =  + -0.0400776  + 0.000801607 *begin_lambda + 7.75964e-06 *lens_ipow(begin_y, 2) + 0.000186068 *begin_x*begin_dx + 2.4068e-05 *lens_ipow(begin_x, 2) + 0.0567796 *lens_ipow(begin_dy, 4)*begin_lambda + -0.653231 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 0.0108262 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + 0.000664444 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 1.55189e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.59725e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 5.80259e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 1.04122e-09 *lens_ipow(begin_y, 5)*begin_dy*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + 0.000313911 *begin_y*begin_dx + 1.55193e-05 *begin_x*begin_y + 1.06816 *lens_ipow(begin_dx, 5)*begin_dy + 0.311036 *begin_y*lens_ipow(begin_dx, 5) + 0.0216524 *begin_x*begin_y*lens_ipow(begin_dx, 4) + 0.000664444 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3) + 1.03459e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2) + 7.98623e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 2.32104e-10 *lens_ipow(begin_x, 5)*begin_y + 0.0237611 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.00100344 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + 8.04373e-06 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 3) + 5.20608e-09 *begin_x*lens_ipow(begin_y, 4)*begin_dy*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.000488105 *begin_x*begin_dy + 1.90291e-05 *begin_x*begin_y + 0.0255194 *begin_dx*begin_dy*begin_lambda + 0.206414 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 1.18787e-06 *lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 0.0110011 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + 0.000161174 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -1.68044e-08 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(1, 1) =  + -0.0409685  + 0.00324897 *begin_lambda + -0.00214014 *lens_ipow(begin_lambda, 2) + 0.0315341 *lens_ipow(begin_dy, 2) + 0.0032017 *lens_ipow(begin_dx, 2) + 0.0011404 *begin_y*begin_dy + 3.05356e-05 *lens_ipow(begin_y, 2) + 9.51457e-06 *lens_ipow(begin_x, 2) + 0.00861515 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.000240991 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 3.56362e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 8.0587e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -4.20111e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 2) + 0.00776074 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5)+0.0f;
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
  out[4] =  + 0.299393  + 0.369348 *begin_lambda + -0.251429 *lens_ipow(begin_lambda, 2) + -0.180494 *lens_ipow(begin_dy, 2) + -0.00600929 *begin_y*begin_dy + -5.06395e-05 *lens_ipow(begin_y, 2) + -9.48285 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.165823 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000596501 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.184105 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00220308 *begin_x*begin_y*begin_dx*begin_dy + -0.000736814 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -47.2435 *lens_ipow(begin_dy, 6) + -259.822 *lens_ipow(begin_dx, 6) + -1.9653 *begin_y*lens_ipow(begin_dy, 5) + -0.0209532 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -21.5887 *begin_x*lens_ipow(begin_dx, 5) + -0.741736 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -0.0133607 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -0.000133262 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -7.22386e-07 *lens_ipow(begin_x, 5)*begin_dx + -1.90217e-09 *lens_ipow(begin_x, 6);
else
  out[4] = 0.0f;
} break;
