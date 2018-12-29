case angenieux_double_gauss_1953_49mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
Eigen::Vector3f view(
  scene_x,
  scene_y,
  scene_z + camera->lens_outer_pupil_curvature_radius
);
raytrace_normalise(view);
int error = 0;
if(1 || view(2) >= camera->lens_field_of_view)
{
  const float eps = 1e-8;
  float sqr_err = 1e30, sqr_ap_err = 1e30;
  float prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(int k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    const float begin_x = x;
    const float begin_y = y;
    const float begin_dx = dx;
    const float begin_dy = dy;
    const float begin_lambda = lambda;
    const Eigen::Vector2f pred_ap(
       + 26.1763 *begin_dx + 0.14819 *begin_x + 7.14375 *begin_dx*begin_lambda + 0.312482 *begin_x*begin_lambda + -5.001 *begin_dx*lens_ipow(begin_lambda, 2) + -15.0851 *begin_dx*lens_ipow(begin_dy, 2) + -16.001 *lens_ipow(begin_dx, 3) + -0.0582372 *begin_y*begin_dx*begin_dy + -0.238972 *begin_x*lens_ipow(begin_lambda, 2) + -0.131913 *begin_x*lens_ipow(begin_dy, 2) + -0.193622 *begin_x*lens_ipow(begin_dx, 2) + -0.000578872 *begin_x*lens_ipow(begin_y, 2) + -0.000548528 *lens_ipow(begin_x, 3) + 0.000183062 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.000199632 *lens_ipow(begin_x, 3)*begin_lambda + 4.35129 *lens_ipow(begin_dx, 5) + 0.0122646 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 2.06341e-05 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 6.59632e-08 *begin_x*lens_ipow(begin_y, 5)*begin_dy + 1.17599e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + 0.000308291 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.18461e-09 *lens_ipow(begin_x, 7) + -0.216652 *begin_x*begin_y*lens_ipow(begin_dy, 7) + 0.00924303 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 6) + -2.25835e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6) + -0.00069423 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 4) + -2.9854e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2) + 8.82456e-14 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2)*begin_lambda,
       + 26.2498 *begin_dy + 7.10235 *begin_dy*begin_lambda + 1.10029 *begin_y*begin_lambda + -4.89017 *begin_dy*lens_ipow(begin_lambda, 2) + -17.1237 *lens_ipow(begin_dy, 3) + -15.9578 *lens_ipow(begin_dx, 2)*begin_dy + -1.64836 *begin_y*lens_ipow(begin_lambda, 2) + -0.144102 *begin_y*lens_ipow(begin_dy, 2) + -0.175288 *begin_y*lens_ipow(begin_dx, 2) + -0.000420648 *lens_ipow(begin_y, 3) + -0.000493915 *lens_ipow(begin_x, 2)*begin_y + 0.846195 *begin_y*lens_ipow(begin_lambda, 3) + 8.01887 *lens_ipow(begin_dy, 5) + 0.290532 *begin_y*lens_ipow(begin_dx, 4) + -0.00096102 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.303622 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.00108222 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.013782 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 4.44939e-06 *lens_ipow(begin_x, 4)*begin_dy + 98.4368 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -2.41734e-09 *lens_ipow(begin_y, 7) + 1.62559e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -6.42878e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 1.80506e-09 *lens_ipow(begin_y, 7)*begin_lambda + -0.00170251 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.000177481 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 5) + 1.05838e-06 *lens_ipow(begin_x, 5)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -2.82609e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)
    );
    const Eigen::Vector2f delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 26.1763  + 7.14375 *begin_lambda + -5.001 *lens_ipow(begin_lambda, 2) + -15.0851 *lens_ipow(begin_dy, 2) + -48.0029 *lens_ipow(begin_dx, 2) + -0.0582372 *begin_y*begin_dy + -0.387245 *begin_x*begin_dx + 21.7565 *lens_ipow(begin_dx, 4) + 0.0122646 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 2.06341e-05 *lens_ipow(begin_x, 4)*begin_lambda + 1.17599e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + 0.000616582 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy + 0.0554582 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -0.00069423 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 4)+0.0f;
    dx1_domega0(0, 1) =  + -30.1702 *begin_dx*begin_dy + -0.0582372 *begin_y*begin_dx + -0.263826 *begin_x*begin_dy + 0.0245292 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 6.59632e-08 *begin_x*lens_ipow(begin_y, 5) + 0.000308291 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2) + -1.51656 *begin_x*begin_y*lens_ipow(begin_dy, 6) + -0.00277692 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 0) =  + -31.9157 *begin_dx*begin_dy + -0.350576 *begin_y*begin_dx + 1.16213 *begin_y*lens_ipow(begin_dx, 3) + -0.303622 *begin_x*lens_ipow(begin_dy, 3) + -0.00108222 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.027564 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 393.747 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -0.00340502 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + 1.05838e-06 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 1) =  + 26.2498  + 7.10235 *begin_lambda + -4.89017 *lens_ipow(begin_lambda, 2) + -51.3712 *lens_ipow(begin_dy, 2) + -15.9578 *lens_ipow(begin_dx, 2) + -0.288205 *begin_y*begin_dy + 40.0943 *lens_ipow(begin_dy, 4) + -0.00192204 *lens_ipow(begin_y, 3)*begin_dy + -0.910867 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00108222 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.013782 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 4.44939e-06 *lens_ipow(begin_x, 4) + 295.31 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -0.00510753 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000887403 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 4) + 2.11675e-06 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_dy+0.0f;
    Eigen::Matrix2f invApJ;
    const float invdetap = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
    invApJ(0, 0) =  dx1_domega0(1, 1)*invdetap;
    invApJ(1, 1) =  dx1_domega0(0, 0)*invdetap;
    invApJ(0, 1) = -dx1_domega0(0, 1)*invdetap;
    invApJ(1, 0) = -dx1_domega0(1, 0)*invdetap;
    for(int i=0;i<2;i++)
    {
      dx += invApJ(0, i)*delta_ap[i];
      dy += invApJ(1, i)*delta_ap[i];
    }
    out(0) =  + 48.8821 *begin_dx + -0.645099 *begin_x + 0.721375 *begin_x*begin_lambda + -19.6882 *begin_dx*lens_ipow(begin_dy, 2) + -18.9497 *lens_ipow(begin_dx, 3) + 0.193832 *begin_y*begin_dx*begin_dy + 0.00510371 *lens_ipow(begin_y, 2)*begin_dx + -0.555092 *begin_x*lens_ipow(begin_lambda, 2) + 0.269599 *begin_x*lens_ipow(begin_dy, 2) + 0.549184 *begin_x*lens_ipow(begin_dx, 2) + 0.007716 *begin_x*begin_y*begin_dy + -0.00130559 *begin_x*lens_ipow(begin_y, 2) + -0.00105494 *lens_ipow(begin_x, 3) + 0.000559786 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.040214 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.000507259 *lens_ipow(begin_x, 3)*begin_lambda + 0.0360917 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0759788 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00234288 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.59685e-06 *lens_ipow(begin_x, 5) + -3.42304e-06 *lens_ipow(begin_y, 5)*begin_dx*begin_dy + -3.83629e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -2.63138e-09 *begin_x*lens_ipow(begin_y, 6) + -1.78393e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -1.07142e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -0.000304642 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 2) + -8.53655e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 8.10945e-07 *lens_ipow(begin_x, 6)*begin_dx*lens_ipow(begin_lambda, 3);
    out(1) =  + 49.027 *begin_dy + -0.621037 *begin_y + 0.696948 *begin_y*begin_lambda + -23.107 *lens_ipow(begin_dy, 3) + -18.7367 *lens_ipow(begin_dx, 2)*begin_dy + -0.553529 *begin_y*lens_ipow(begin_lambda, 2) + 0.241088 *begin_y*lens_ipow(begin_dx, 2) + 0.0124908 *lens_ipow(begin_y, 2)*begin_dy + -0.00132421 *lens_ipow(begin_y, 3) + 0.00537062 *begin_x*begin_y*begin_dx + -0.00140918 *lens_ipow(begin_x, 2)*begin_y + 0.38429 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.000582984 *lens_ipow(begin_y, 3)*begin_lambda + 0.277135 *begin_x*begin_dx*begin_dy*begin_lambda + 0.0112343 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.000706359 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 18.2152 *lens_ipow(begin_dy, 5) + 1.94318 *begin_y*lens_ipow(begin_dy, 4) + -1.65049e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.144205 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.183519 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 5.89866 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -3.33064e-09 *lens_ipow(begin_y, 7) + 2.6672 *begin_x*begin_dx*lens_ipow(begin_dy, 5) + -9.20241e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 0.000245366 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*begin_dy + -8.37379e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -2.99011e-09 *lens_ipow(begin_x, 6)*begin_y;
    out(2) =  + -0.610441 *begin_dx + -0.0125123 *begin_x + 0.0110383 *begin_dx*begin_lambda + -0.00922338 *begin_x*begin_lambda + 0.148194 *begin_dx*lens_ipow(begin_dy, 2) + 0.22954 *lens_ipow(begin_dx, 3) + 0.00748852 *begin_x*lens_ipow(begin_lambda, 2) + -0.00110408 *begin_x*lens_ipow(begin_dy, 2) + -6.12117e-05 *begin_x*begin_y*begin_dy + 1.80792e-05 *begin_x*lens_ipow(begin_y, 2) + -0.000166332 *lens_ipow(begin_x, 2)*begin_dx + 1.85718e-05 *lens_ipow(begin_x, 3) + -8.28448e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -8.08293e-06 *lens_ipow(begin_x, 3)*begin_lambda + 0.0003898 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -1.20995e-07 *lens_ipow(begin_y, 4)*begin_dx + -0.00449414 *begin_x*lens_ipow(begin_dy, 4) + -3.49031e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 0.000719834 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0010609 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 3.98186e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 2.57891e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 4.08399e-11 *begin_x*lens_ipow(begin_y, 6) + -3.87996e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3) + 4.02693e-11 *lens_ipow(begin_x, 7) + 2.00841e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2) + 2.39022e-15 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 6) + 0.460264 *begin_x*begin_y*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3)*begin_lambda;
    out(3) =  + -0.616863 *begin_dy + -0.0119682 *begin_y + 0.0104117 *begin_dy*begin_lambda + -0.0100025 *begin_y*begin_lambda + 0.291716 *lens_ipow(begin_dy, 3) + 0.422799 *lens_ipow(begin_dx, 2)*begin_dy + 0.00733861 *begin_y*lens_ipow(begin_lambda, 2) + -0.00410946 *begin_y*lens_ipow(begin_dx, 2) + 1.36949e-05 *lens_ipow(begin_y, 3) + 0.00307779 *begin_x*begin_dx*begin_dy + -0.000104203 *begin_x*begin_y*begin_dx + 1.44688e-05 *lens_ipow(begin_x, 2)*begin_y + -0.442489 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.320492 *lens_ipow(begin_dx, 4)*begin_dy + -1.11051e-06 *lens_ipow(begin_y, 4)*begin_dy + 2.30472e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -2.41972e-07 *lens_ipow(begin_x, 4)*begin_dy + -4.9917e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 3.92392e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy + 4.24265e-11 *lens_ipow(begin_y, 7) + 3.65779e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 1.29196e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 4.1403e-11 *lens_ipow(begin_x, 6)*begin_y + -1.15075 *lens_ipow(begin_dy, 7)*begin_lambda + -0.0653355 *begin_y*lens_ipow(begin_dy, 6)*begin_lambda + 3.55529e-09 *lens_ipow(begin_y, 6)*begin_dy*begin_lambda + -4.4978e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_lambda + 2.67424e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 3)*begin_lambda;
    Eigen::Vector3f pred_out_cs_pos(0,0,0);
    Eigen::Vector3f pred_out_cs_dir(0,0,0);
    Eigen::Vector2f outpos(out(0), out(1));
    Eigen::Vector2f outdir(out(2), out(3));
    if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    Eigen::Vector3f view(
      scene_x - pred_out_cs_pos(0),
      scene_y - pred_out_cs_pos(1),
      scene_z - pred_out_cs_pos(2)
    );
    raytrace_normalise(view);
    Eigen::VectorXf out_new(5); out_new.setZero();
    Eigen::Vector2f out_new_pos(0,0);
    Eigen::Vector2f out_new_dir(0,0);
    if (camera->lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    out_new(0) = out_new_pos(0);
    out_new(1) = out_new_pos(1);
    out_new(2) = out_new_dir(0);
    out_new(3) = out_new_dir(1);
    const Eigen::Vector2f delta_out(out_new[2] - out[2], out_new[3] - out[3]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2f domega2_dx0;
    domega2_dx0(0, 0) =  + -0.0125123  + -0.00922338 *begin_lambda + 0.00748852 *lens_ipow(begin_lambda, 2) + -0.00110408 *lens_ipow(begin_dy, 2) + -6.12117e-05 *begin_y*begin_dy + 1.80792e-05 *lens_ipow(begin_y, 2) + -0.000332664 *begin_x*begin_dx + 5.57153e-05 *lens_ipow(begin_x, 2) + -8.28448e-06 *lens_ipow(begin_y, 2)*begin_lambda + -2.42488e-05 *lens_ipow(begin_x, 2)*begin_lambda + -0.00449414 *lens_ipow(begin_dy, 4) + -3.49031e-07 *lens_ipow(begin_y, 3)*begin_dy + 0.00143967 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.00212179 *begin_x*lens_ipow(begin_dx, 3) + 7.96372e-05 *begin_x*begin_y*begin_dx*begin_dy + 7.73673e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 4.08399e-11 *lens_ipow(begin_y, 6) + -1.55198e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + 2.81885e-10 *lens_ipow(begin_x, 6) + 1.40589e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2) + 1.19511e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + 0.460264 *begin_y*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -6.12117e-05 *begin_x*begin_dy + 3.61584e-05 *begin_x*begin_y + -1.6569e-05 *begin_x*begin_y*begin_lambda + 0.0007796 *begin_y*lens_ipow(begin_dx, 3) + -4.83979e-07 *lens_ipow(begin_y, 3)*begin_dx + -1.04709e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 3.98186e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 5.15782e-08 *lens_ipow(begin_x, 3)*begin_y + 2.4504e-10 *begin_x*lens_ipow(begin_y, 5) + 4.01682e-13 *lens_ipow(begin_x, 7)*begin_y + 1.43413e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5) + 0.460264 *begin_x*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.00307779 *begin_dx*begin_dy + -0.000104203 *begin_y*begin_dx + 2.89375e-05 *begin_x*begin_y + 2.30472e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -9.67889e-07 *lens_ipow(begin_x, 3)*begin_dy + -9.9834e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 7.31557e-10 *begin_x*lens_ipow(begin_y, 5) + 5.16782e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 2.48418e-10 *lens_ipow(begin_x, 5)*begin_y + -8.99561e-10 *begin_x*lens_ipow(begin_y, 5)*begin_lambda + 1.06969e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.0119682  + -0.0100025 *begin_lambda + 0.00733861 *lens_ipow(begin_lambda, 2) + -0.00410946 *lens_ipow(begin_dx, 2) + 4.10847e-05 *lens_ipow(begin_y, 2) + -0.000104203 *begin_x*begin_dx + 1.44688e-05 *lens_ipow(begin_x, 2) + -4.44204e-06 *lens_ipow(begin_y, 3)*begin_dy + 4.60945e-05 *begin_x*begin_y*begin_dx*begin_dy + -9.9834e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 1.56957e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + 2.96985e-10 *lens_ipow(begin_y, 6) + 1.82889e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + 3.87587e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 4.1403e-11 *lens_ipow(begin_x, 6) + -0.0653355 *lens_ipow(begin_dy, 6)*begin_lambda + 2.13318e-08 *lens_ipow(begin_y, 5)*begin_dy*begin_lambda + -2.2489e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_lambda+0.0f;
    Eigen::Matrix2f invJ;
    const float invdet = 1.0f/(domega2_dx0(0, 0)*domega2_dx0(1, 1) - domega2_dx0(0, 1)*domega2_dx0(1, 0));
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
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.238048  + 0.856356 *begin_lambda + -1.17367 *lens_ipow(begin_lambda, 2) + 0.567787 *lens_ipow(begin_lambda, 3) + -0.000559814 *begin_y*begin_dy*begin_lambda + -0.000554268 *begin_x*begin_dx*begin_lambda + -0.169285 *lens_ipow(begin_dy, 4) + -0.496274 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.17286 *lens_ipow(begin_dx, 4) + -0.00824271 *begin_y*lens_ipow(begin_dy, 3) + -0.00655018 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000234472 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000123029 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -5.09404e-08 *lens_ipow(begin_y, 4) + -0.00661154 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00811139 *begin_x*lens_ipow(begin_dx, 3) + -0.000477706 *begin_x*begin_y*begin_dx*begin_dy + -0.000124752 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000235274 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -7.64568e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -4.86286e-08 *lens_ipow(begin_x, 4) + -0.120174 *lens_ipow(begin_dy, 4)*begin_lambda + -0.112317 *lens_ipow(begin_dx, 4)*begin_lambda + -0.000909037 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.000889541 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + 1.02523e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -5.84143e-17 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 8) + -1.75004e-17 *lens_ipow(begin_x, 10)*lens_ipow(begin_y, 2);
else
  out[4] = 0.0f;
} break;
