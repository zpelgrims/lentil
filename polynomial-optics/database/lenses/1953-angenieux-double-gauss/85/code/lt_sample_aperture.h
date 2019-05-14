case angenieux_double_gauss_1953_85mm:
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
       + 45.5498 *begin_dx + 0.151196 *begin_x + 0.273694 *begin_x*begin_lambda + 11.6248 *begin_dx*begin_lambda + -8.01172 *begin_dx*lens_ipow(begin_lambda, 2) + -0.000142485 *lens_ipow(begin_x, 3) + -0.176638 *begin_x*lens_ipow(begin_dx, 2) + -0.0284183 *begin_y*begin_dx*begin_dy + -0.15572 *begin_x*lens_ipow(begin_dy, 2) + -28.2318 *lens_ipow(begin_dx, 3) + -0.188388 *begin_x*lens_ipow(begin_lambda, 2) + -26.1766 *begin_dx*lens_ipow(begin_dy, 2) + -0.000123348 *begin_x*lens_ipow(begin_y, 2) + 0.00259477 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.0104329 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 11.9638 *lens_ipow(begin_dx, 5) + 0.215298 *begin_x*lens_ipow(begin_dy, 4) + 0.0115168 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -8.00724e-08 *begin_x*lens_ipow(begin_y, 4) + -0.0225047 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.000414222 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + -3.63043e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 107.131 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 1.18347 *begin_x*lens_ipow(begin_dx, 6)*begin_lambda,
       + 0.152609 *begin_y + 45.3785 *begin_dy + 11.7108 *begin_dy*begin_lambda + 0.272013 *begin_y*begin_lambda + -0.186622 *begin_y*lens_ipow(begin_lambda, 2) + -0.161807 *begin_y*lens_ipow(begin_dx, 2) + -27.5264 *lens_ipow(begin_dy, 3) + -0.200653 *begin_y*lens_ipow(begin_dy, 2) + -8.01158 *begin_dy*lens_ipow(begin_lambda, 2) + -0.00014469 *lens_ipow(begin_y, 3) + -0.0419784 *begin_x*begin_dx*begin_dy + 0.00148334 *lens_ipow(begin_y, 2)*begin_dy + -25.607 *lens_ipow(begin_dx, 2)*begin_dy + 0.00121585 *lens_ipow(begin_x, 2)*begin_dy + -0.000143192 *lens_ipow(begin_x, 2)*begin_y + 11.3829 *lens_ipow(begin_dy, 5) + -0.00748748 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.260173 *begin_y*lens_ipow(begin_dy, 4) + -0.00563263 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.016367 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.208047 *begin_y*lens_ipow(begin_dx, 4) + 3.05906 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 130.888 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -1.25884e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 45.5498  + 11.6248 *begin_lambda + -8.01172 *lens_ipow(begin_lambda, 2) + -0.353275 *begin_x*begin_dx + -0.0284183 *begin_y*begin_dy + -84.6954 *lens_ipow(begin_dx, 2) + -26.1766 *lens_ipow(begin_dy, 2) + 0.00259477 *lens_ipow(begin_x, 2)*begin_lambda + 0.0104329 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 59.8189 *lens_ipow(begin_dx, 4) + 0.0230336 *begin_x*begin_y*begin_dx*begin_dy + -0.0225047 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.000414222 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 321.394 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 7.10084 *begin_x*lens_ipow(begin_dx, 5)*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -0.0284183 *begin_y*begin_dx + -0.31144 *begin_x*begin_dy + -52.3531 *begin_dx*begin_dy + 0.0208658 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.86119 *begin_x*lens_ipow(begin_dy, 3) + 0.0115168 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -0.0450094 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda + -0.000414222 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + 428.525 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 0) =  + -0.323614 *begin_y*begin_dx + -0.0419784 *begin_x*begin_dy + -51.2139 *begin_dx*begin_dy + -0.014975 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.016367 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.832187 *begin_y*lens_ipow(begin_dx, 3) + 12.2362 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 523.553 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 1) =  + 45.3785  + 11.7108 *begin_lambda + -82.5792 *lens_ipow(begin_dy, 2) + -0.401306 *begin_y*begin_dy + -8.01158 *lens_ipow(begin_lambda, 2) + -0.0419784 *begin_x*begin_dx + 0.00148334 *lens_ipow(begin_y, 2) + -25.607 *lens_ipow(begin_dx, 2) + 0.00121585 *lens_ipow(begin_x, 2) + 56.9146 *lens_ipow(begin_dy, 4) + -0.00748748 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.04069 *begin_y*lens_ipow(begin_dy, 3) + -0.0168979 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.0327341 *begin_x*begin_y*begin_dx*begin_dy + 6.11812 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + 392.665 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)+0.0f;
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
    out(0) =  + 84.7496 *begin_dx + -0.630653 *begin_x + 0.648774 *begin_x*begin_lambda + -0.000322825 *lens_ipow(begin_x, 3) + 0.552026 *begin_x*lens_ipow(begin_dx, 2) + -32.6321 *lens_ipow(begin_dx, 3) + -0.458111 *begin_x*lens_ipow(begin_lambda, 2) + -33.6475 *begin_dx*lens_ipow(begin_dy, 2) + -0.00045453 *begin_x*lens_ipow(begin_y, 2) + 0.000203875 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0212221 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.0104645 *begin_x*begin_y*begin_dy*begin_lambda + 0.00616556 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.399235 *begin_y*begin_dx*begin_dy*begin_lambda + 5.79425 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.0270538 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000876197 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -14.1942 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.0316393 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.000996136 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 9.6531 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -3.29683e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -7.43209e-05 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 3) + -2.80786e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4);
    out(1) =  + -0.629141 *begin_y + 84.9913 *begin_dy + 0.643184 *begin_y*begin_lambda + -0.445984 *begin_y*lens_ipow(begin_lambda, 2) + 0.277323 *begin_y*lens_ipow(begin_dx, 2) + -43.1988 *lens_ipow(begin_dy, 3) + 0.384825 *begin_y*lens_ipow(begin_dy, 2) + -0.000328228 *lens_ipow(begin_y, 3) + 0.21319 *begin_x*begin_dx*begin_dy + 0.00480778 *begin_x*begin_y*begin_dx + -32.9647 *lens_ipow(begin_dx, 2)*begin_dy + 0.00354965 *lens_ipow(begin_x, 2)*begin_dy + -0.000346602 *lens_ipow(begin_x, 2)*begin_y + 0.0170589 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 8.91253 *lens_ipow(begin_dy, 3)*begin_lambda + 22.5966 *lens_ipow(begin_dy, 5) + 0.0262924 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.000467849 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.000465245 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0281633 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 1.9332 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 6.09632e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*begin_dy + -4.80916e-05 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 3) + -2.3161e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5);
    out(2) =  + -0.610791 *begin_dx + -0.00735722 *begin_x + -0.00427697 *begin_x*begin_lambda + 0.00801533 *begin_dx*begin_lambda + 2.81839e-06 *lens_ipow(begin_x, 3) + -0.00118079 *begin_x*lens_ipow(begin_dy, 2) + 0.276686 *lens_ipow(begin_dx, 3) + 0.00295211 *begin_x*lens_ipow(begin_lambda, 2) + -5.37241e-05 *lens_ipow(begin_x, 2)*begin_dx + 2.67351e-06 *begin_x*lens_ipow(begin_y, 2) + -3.4422e-05 *begin_x*begin_y*begin_dy + 0.548419 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 8.20225e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000125285 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 9.58194e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.189083 *lens_ipow(begin_dx, 5) + 0.000257719 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 3.23467e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.49563 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.00045307 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.0193136 *begin_x*lens_ipow(begin_dx, 6) + 0.0141629 *begin_x*begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 5.49694e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2) + 2.04398e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4);
    out(3) =  + -0.0072681 *begin_y + -0.616363 *begin_dy + 0.00944648 *begin_dy*begin_lambda + -0.00454731 *begin_y*begin_lambda + 0.0032206 *begin_y*lens_ipow(begin_lambda, 2) + -0.00226146 *begin_y*lens_ipow(begin_dx, 2) + 0.318005 *lens_ipow(begin_dy, 3) + 2.73411e-06 *lens_ipow(begin_y, 3) + 0.00222699 *begin_x*begin_dx*begin_dy + -3.48559e-05 *begin_x*begin_y*begin_dx + 0.428195 *lens_ipow(begin_dx, 2)*begin_dy + 2.7105e-06 *lens_ipow(begin_x, 2)*begin_y + -1.18909e-07 *lens_ipow(begin_y, 4)*begin_dy + -1.18598e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -0.247974 *lens_ipow(begin_dy, 5) + -0.645702 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 3.50586e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.336225 *lens_ipow(begin_dx, 4)*begin_dy + 6.61506e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -0.0156555 *begin_y*lens_ipow(begin_dy, 6) + -0.0491567 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.0666803 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 1.14734e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 2.23223e-09 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.00735722  + -0.00427697 *begin_lambda + 8.45516e-06 *lens_ipow(begin_x, 2) + -0.00118079 *lens_ipow(begin_dy, 2) + 0.00295211 *lens_ipow(begin_lambda, 2) + -0.000107448 *begin_x*begin_dx + 2.67351e-06 *lens_ipow(begin_y, 2) + -3.4422e-05 *begin_y*begin_dy + 1.64045e-05 *begin_x*begin_y*begin_dx*begin_dy + 0.000125285 *begin_y*lens_ipow(begin_dy, 3) + 0.000515437 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 3.23467e-06 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.00090614 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + -0.0193136 *lens_ipow(begin_dx, 6) + 0.0141629 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 0.000164908 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2) + 1.02199e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)+0.0f;
    domega2_dx0(0, 1) =  + 5.34701e-06 *begin_x*begin_y + -3.4422e-05 *begin_x*begin_dy + 8.20225e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.000125285 *begin_x*lens_ipow(begin_dy, 3) + 0.000191639 *begin_y*lens_ipow(begin_dx, 3) + 6.46935e-06 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.0141629 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 8.17591e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.00222699 *begin_dx*begin_dy + -3.48559e-05 *begin_y*begin_dx + 5.421e-06 *begin_x*begin_y + -2.37196e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 3.50586e-06 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 2.64602e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -0.0666803 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 2.29467e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.0072681  + -0.00454731 *begin_lambda + 0.0032206 *lens_ipow(begin_lambda, 2) + -0.00226146 *lens_ipow(begin_dx, 2) + 8.20232e-06 *lens_ipow(begin_y, 2) + -3.48559e-05 *begin_x*begin_dx + 2.7105e-06 *lens_ipow(begin_x, 2) + -4.75636e-07 *lens_ipow(begin_y, 3)*begin_dy + -2.37196e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 7.01173e-06 *begin_x*begin_y*begin_dx*begin_dy + 1.98452e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -0.0156555 *lens_ipow(begin_dy, 6) + -0.0491567 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 2.29467e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 1.33934e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_dy+0.0f;
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
  out[4] =  + 0.237803  + 0.856861 *begin_lambda + -1.17402 *lens_ipow(begin_lambda, 2) + 0.567347 *lens_ipow(begin_lambda, 3) + -0.00473145 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -5.13263e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00583318 *begin_x*lens_ipow(begin_dx, 3) + -0.191747 *lens_ipow(begin_dy, 4) + -0.000176699 *begin_x*begin_y*begin_dx*begin_dy + -0.00580119 *begin_y*lens_ipow(begin_dy, 3) + -0.000107851 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.00473576 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.000107954 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.191206 *lens_ipow(begin_dx, 4) + -5.13494e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.59732 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.45331e-06 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + 1.17515 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000318083 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -1.45499e-06 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_lambda, 2) + -0.000325374 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -0.292015 *lens_ipow(begin_dx, 6)*begin_lambda + -0.287084 *lens_ipow(begin_dy, 6)*begin_lambda + -3.00754e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_lambda;
else
  out[4] = 0.0f;
} break;
