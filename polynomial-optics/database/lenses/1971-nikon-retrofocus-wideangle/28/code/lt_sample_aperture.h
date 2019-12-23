case nikon__retrofocus_wideangle__1971__28mm:
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
       + 36.8509 *begin_dx + 0.761108 *begin_x + -0.00662178 *begin_x*begin_lambda + 1.25266 *begin_y*begin_dx*begin_dy + 8.91949 *begin_dx*lens_ipow(begin_dy, 2) + 0.0239075 *lens_ipow(begin_y, 2)*begin_dx + 4.63029 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.0023141 *lens_ipow(begin_x, 3)*begin_lambda + 0.196747 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.00265689 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 41.365 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 0.0173568 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 17.0056 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 1.16157 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -41.7386 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.0422162 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + -2.82755 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -0.00250568 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + 1.90426 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 4) + -0.279842 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 4) + 0.0284157 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 4) + 28.3181 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -1.7097e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -13.0236 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 6) + 4.9701e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -277.123 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 8) + 1.6843e-08 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 4) + 1.67843e-08 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 4),
       + 0.768353 *begin_y + 36.8421 *begin_dy + -0.034862 *begin_y*begin_lambda + 0.0798566 *lens_ipow(begin_y, 2)*begin_dy + 2.09584 *begin_y*lens_ipow(begin_dy, 2) + 0.0257873 *begin_y*lens_ipow(begin_lambda, 2) + 0.000832891 *lens_ipow(begin_y, 3) + 9.38293 *lens_ipow(begin_dy, 3) + 3.15117 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 41.2127 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.0925706 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.213198 *begin_x*begin_y*begin_dx*begin_lambda + 4.99446 *begin_x*begin_dx*begin_dy*begin_lambda + 0.00317324 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -4.72596 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.00294993 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 2) + -0.000158278 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.00291481 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -3.00936 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.199349 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -0.0860934 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -43.0671 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 1.8383e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -0.0592202 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + 1.9848e-08 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 4) + -5.44052e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx*begin_dy + -4.67959e-10 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 1.4365e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 36.8509  + 1.25266 *begin_y*begin_dy + 8.91949 *lens_ipow(begin_dy, 2) + 0.0239075 *lens_ipow(begin_y, 2) + 9.26058 *begin_x*begin_dx*begin_lambda + 0.196747 *lens_ipow(begin_x, 2)*begin_lambda + 0.00797067 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 124.095 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.279842 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 4) + -1.7097e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + -26.0471 *begin_x*begin_dx*lens_ipow(begin_lambda, 6) + -831.369 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 8) + 6.73719e-08 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3)+0.0f;
    dx1_domega0(0, 1) =  + 1.25266 *begin_y*begin_dx + 17.839 *begin_dx*begin_dy + 34.0113 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 1.16157 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + -83.4772 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -2.82755 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 1.90426 *begin_x*begin_y*lens_ipow(begin_lambda, 4) + 56.6363 *begin_x*begin_dy*lens_ipow(begin_lambda, 4) + -1.7097e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx + 6.71371e-08 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 0) =  + 6.30234 *begin_y*begin_dx*begin_lambda + 82.4255 *begin_dx*begin_dy*begin_lambda + 0.213198 *begin_x*begin_y*begin_lambda + 4.99446 *begin_x*begin_dy*begin_lambda + -4.72596 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.000158278 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -6.01873 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -0.199349 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + -86.1341 *begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.296101 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 7.9392e-08 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 3) + -5.44052e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 36.8421  + 0.0798566 *lens_ipow(begin_y, 2) + 4.19167 *begin_y*begin_dy + 28.1488 *lens_ipow(begin_dy, 2) + 41.2127 *lens_ipow(begin_dx, 2)*begin_lambda + 0.0925706 *lens_ipow(begin_x, 2)*begin_lambda + 4.99446 *begin_x*begin_dx*begin_lambda + -4.72596 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.000158278 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.00874442 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0860934 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + -43.0671 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.17766 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + -5.44052e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx + -1.40388e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)+0.0f;
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
    out(0) =  + 23.7828 *begin_dx + -0.161152 *begin_x + 16.8335 *begin_dx*begin_lambda + 0.403724 *begin_y*begin_dx*begin_dy + 0.0323375 *begin_x*begin_y*begin_dy + -5.93453 *begin_dx*lens_ipow(begin_dy, 2) + 0.000792711 *begin_x*lens_ipow(begin_y, 2) + 0.000244389 *lens_ipow(begin_x, 3) + 0.660224 *begin_x*lens_ipow(begin_dy, 2) + 0.0191113 *lens_ipow(begin_y, 2)*begin_dx + -22.8558 *begin_dx*lens_ipow(begin_lambda, 2) + 5.80048 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 10.7284 *begin_dx*lens_ipow(begin_lambda, 3) + 0.00243259 *lens_ipow(begin_x, 3)*begin_lambda + 0.239503 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -0.264621 *begin_x*lens_ipow(begin_dx, 4) + -20.7619 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.00251225 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + -6.81187 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000419481 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.000773233 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.180046 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.012887 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.00116383 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -0.255086 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -6.38341e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 2.08661e-06 *lens_ipow(begin_x, 6)*begin_dx*lens_ipow(begin_dy, 4) + 3.30025e-08 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 4);
    out(1) =  + -0.155048 *begin_y + 24.1702 *begin_dy + 16.146 *begin_dy*begin_lambda + -0.00940921 *begin_y*begin_lambda + 0.614081 *begin_y*lens_ipow(begin_dx, 2) + 0.048021 *lens_ipow(begin_y, 2)*begin_dy + 0.8849 *begin_y*lens_ipow(begin_dy, 2) + 0.279602 *begin_x*begin_dx*begin_dy + 0.0307115 *begin_x*begin_y*begin_dx + -9.20285 *lens_ipow(begin_dx, 2)*begin_dy + 0.000770668 *lens_ipow(begin_x, 2)*begin_y + -22.9382 *begin_dy*lens_ipow(begin_lambda, 2) + 0.000769356 *lens_ipow(begin_y, 3) + 0.0174747 *lens_ipow(begin_x, 2)*begin_dy + -9.41278 *lens_ipow(begin_dy, 3) + 11.1695 *begin_dy*lens_ipow(begin_lambda, 3) + -0.193871 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.00309834 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -9.84889e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -0.080952 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00729952 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -6.66341e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + 0.000704529 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -1.00863 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.0359866 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.00113247 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 31.9193 *lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 3) + 0.752275 *begin_y*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3);
    out(2) =  + -1.03413 *begin_dx + -0.0320616 *begin_x + 0.0066317 *begin_x*begin_lambda + -0.000973395 *begin_x*begin_y*begin_dy + -0.004598 *begin_x*lens_ipow(begin_lambda, 2) + -0.180573 *begin_dx*lens_ipow(begin_dy, 2) + -1.10475e-05 *begin_x*lens_ipow(begin_y, 2) + -0.0173884 *begin_x*lens_ipow(begin_dy, 2) + 1.44411e-05 *lens_ipow(begin_y, 2)*begin_dx + 1.13877 *lens_ipow(begin_dx, 3)*begin_lambda + -3.73767e-05 *lens_ipow(begin_x, 3)*begin_lambda + -0.0035957 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -8.79634e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.00182855 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 5.30265e-07 *lens_ipow(begin_y, 4)*begin_dx + 3.5998e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 2.80878e-05 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 0.000402729 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.00335341 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 1.89966 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -8.25539e-07 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + -0.00558445 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + -1.5857 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4) + -8.37827e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -7.67058e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 2) + 7.47061e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 3) + -0.000808357 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 1.97048 *lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 6);
    out(3) =  + -0.0307774 *begin_y + -1.03556 *begin_dy + 0.00174162 *begin_y*begin_lambda + 0.0700065 *begin_x*begin_dx*begin_dy + 1.58614 *lens_ipow(begin_dx, 2)*begin_dy + -1.02083e-05 *lens_ipow(begin_y, 3) + 0.000766049 *lens_ipow(begin_x, 2)*begin_dy + -0.00144102 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 1.10587 *lens_ipow(begin_dy, 3)*begin_lambda + -0.00349262 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.00034959 *begin_x*begin_y*begin_dx*begin_lambda + -0.110901 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -3.32719e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 2) + -3.70051e-07 *lens_ipow(begin_y, 4)*begin_dy + 0.00306464 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -0.00293124 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0614765 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.00251561 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -0.0640027 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -6.8708e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -2.63912 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -1.1861 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 4) + -5.53159e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 2) + 1.50784e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy + 0.000116264 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 8.30034e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 4) + -1.19581e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*lens_ipow(begin_dy, 2) + -3.74473e-13 *begin_x*lens_ipow(begin_y, 8)*begin_dx*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.0320616  + 0.0066317 *begin_lambda + -0.000973395 *begin_y*begin_dy + -0.004598 *lens_ipow(begin_lambda, 2) + -1.10475e-05 *lens_ipow(begin_y, 2) + -0.0173884 *lens_ipow(begin_dy, 2) + -0.00011213 *lens_ipow(begin_x, 2)*begin_lambda + -0.00719139 *begin_x*begin_dx*begin_lambda + -2.6389e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00182855 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.000107994 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 0.00670682 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -3.30216e-06 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -0.00558445 *lens_ipow(begin_dy, 4)*begin_lambda + -4.18913e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 2) + -3.83529e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 2) + 3.73531e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 3) + -0.000808357 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(0, 1) =  + -0.000973395 *begin_x*begin_dy + -2.20949e-05 *begin_x*begin_y + 2.88823e-05 *begin_y*begin_dx + -1.75927e-08 *lens_ipow(begin_x, 3)*begin_y + -0.00182855 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 2.12106e-06 *lens_ipow(begin_y, 3)*begin_dx + 8.42633e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.000805459 *begin_y*lens_ipow(begin_dx, 3) + -0.000808357 *begin_x*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0700065 *begin_dx*begin_dy + 0.0015321 *begin_x*begin_dy + -0.00288203 *begin_x*begin_dy*begin_lambda + -0.00034959 *begin_y*begin_dx*begin_lambda + -0.110901 *begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -6.65439e-05 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + -0.00293124 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00251561 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -0.000137416 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 6.03136e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy + 0.000232527 *begin_x*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -3.58744e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx*lens_ipow(begin_dy, 2) + -3.74473e-13 *lens_ipow(begin_y, 8)*begin_dx*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.0307774  + 0.00174162 *begin_lambda + -3.06248e-05 *lens_ipow(begin_y, 2) + -0.00698524 *begin_y*begin_dy*begin_lambda + -0.00034959 *begin_x*begin_dx*begin_lambda + -3.32719e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + -1.48021e-06 *lens_ipow(begin_y, 3)*begin_dy + 0.00612929 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00293124 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0614765 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.00251561 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.0640027 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -6.8708e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -2.7658e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 2) + 6.03136e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + 0.000116264 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 4.15017e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 4) + -5.97907e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2) + -2.99578e-12 *begin_x*lens_ipow(begin_y, 7)*begin_dx*begin_dy+0.0f;
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
  out[4] =  + 2.05311 *begin_lambda + -0.00201505 *begin_y*begin_dy + -0.000163813 *begin_x*begin_dx + -2.21987e-05 *lens_ipow(begin_y, 2) + -0.0421173 *lens_ipow(begin_dy, 2) + -4.44343 *lens_ipow(begin_lambda, 2) + 4.53022 *lens_ipow(begin_lambda, 3) + -1.78921 *lens_ipow(begin_lambda, 4) + -2.89002 *lens_ipow(begin_dx, 4) + -0.0299405 *begin_y*lens_ipow(begin_dy, 3) + -0.180237 *begin_x*lens_ipow(begin_dx, 3) + -2.4053 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.21071 *lens_ipow(begin_dy, 4) + -2.16336e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.02436e-07 *lens_ipow(begin_y, 4) + -0.00523778 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.0296407 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -8.25795e-05 *lens_ipow(begin_x, 3)*begin_dx + -0.029477 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -6.00345e-07 *lens_ipow(begin_x, 4) + -9.04551e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -0.000131603 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 5) + -0.925517 *lens_ipow(begin_dy, 8) + 0.00311719 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 3.40141e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + -1.14283e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + 1.99512 *begin_x*begin_dx*lens_ipow(begin_dy, 8)*begin_lambda + 2.02085 *begin_y*lens_ipow(begin_dx, 8)*begin_dy*begin_lambda;
else
  out[4] = 0.0f;
} break;
