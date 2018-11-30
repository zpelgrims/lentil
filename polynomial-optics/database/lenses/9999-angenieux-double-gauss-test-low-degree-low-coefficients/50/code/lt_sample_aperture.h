case angenieux_double_gauss_test_low_degree_low_coefficients_9999_50mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
std::vector<float> view =
{
  scene_x,
  scene_y,
  scene_z + camera->lens_outer_pupil_curvature_radius
};
raytrace_normalise(view);
int error = 0;
if(1 || view[2] >= camera->lens_field_of_view)
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
    const std::vector<float> pred_ap = {
       + 28.196 *begin_dx + 0.198375 *begin_x + 1.80766 *begin_dx*begin_lambda + 0.0827756 *begin_x*begin_lambda + -15.8914 *begin_dx*lens_ipow(begin_dy, 2) + -15.9078 *lens_ipow(begin_dx, 3) + -0.108256 *begin_y*begin_dx*begin_dy + -0.115596 *begin_x*lens_ipow(begin_dy, 2) + -0.22334 *begin_x*lens_ipow(begin_dx, 2) + -0.000452834 *begin_x*lens_ipow(begin_y, 2) + -0.000338389 *lens_ipow(begin_x, 3) + -6.4402e-07 *lens_ipow(begin_x, 5) + -6.25986e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -2.06068e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2),
       + 28.218 *begin_dy + 0.194886 *begin_y + 1.77846 *begin_dy*begin_lambda + 0.0825992 *begin_y*begin_lambda + -15.9435 *lens_ipow(begin_dy, 3) + -15.9016 *lens_ipow(begin_dx, 2)*begin_dy + -0.223052 *begin_y*lens_ipow(begin_dy, 2) + -0.11646 *begin_y*lens_ipow(begin_dx, 2) + -0.000301214 *lens_ipow(begin_y, 3) + -0.106337 *begin_x*begin_dx*begin_dy + -0.000288825 *lens_ipow(begin_x, 2)*begin_y + -7.18236e-07 *lens_ipow(begin_y, 5) + -1.55876e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -7.59872e-07 *lens_ipow(begin_x, 4)*begin_y
    };
    const std::vector<float> delta_ap = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 28.196  + 1.80766 *begin_lambda + -15.8914 *lens_ipow(begin_dy, 2) + -47.7235 *lens_ipow(begin_dx, 2) + -0.108256 *begin_y*begin_dy + -0.44668 *begin_x*begin_dx+0.0f;
    dx1_domega0(0, 1) =  + -31.7828 *begin_dx*begin_dy + -0.108256 *begin_y*begin_dx + -0.231192 *begin_x*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + -31.8032 *begin_dx*begin_dy + -0.23292 *begin_y*begin_dx + -0.106337 *begin_x*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 28.218  + 1.77846 *begin_lambda + -47.8306 *lens_ipow(begin_dy, 2) + -15.9016 *lens_ipow(begin_dx, 2) + -0.446103 *begin_y*begin_dy + -0.106337 *begin_x*begin_dx+0.0f;
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
    out[0] =  + 50.062 *begin_dx + -0.514073 *begin_x + 0.193023 *begin_x*begin_lambda + -20.9598 *begin_dx*lens_ipow(begin_dy, 2) + -20.4934 *lens_ipow(begin_dx, 3) + 0.254673 *begin_x*lens_ipow(begin_dy, 2) + 0.306425 *begin_x*lens_ipow(begin_dx, 2) + 0.00639941 *begin_x*begin_y*begin_dy + -0.00107932 *begin_x*lens_ipow(begin_y, 2) + 0.0129362 *lens_ipow(begin_x, 2)*begin_dx + -0.000869314 *lens_ipow(begin_x, 3) + 0.00944102 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.22695e-06 *lens_ipow(begin_x, 5) + -1.46681e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4);
    out[1] =  + 50.0743 *begin_dy + -0.50326 *begin_y + 0.194546 *begin_y*begin_lambda + -20.5116 *lens_ipow(begin_dy, 3) + -21.1279 *lens_ipow(begin_dx, 2)*begin_dy + 0.298569 *begin_y*lens_ipow(begin_dy, 2) + 0.255843 *begin_y*lens_ipow(begin_dx, 2) + 0.0127191 *lens_ipow(begin_y, 2)*begin_dy + -0.00116563 *lens_ipow(begin_y, 3) + 0.00645673 *begin_x*begin_y*begin_dx + -0.000904587 *lens_ipow(begin_x, 2)*begin_y + 0.00951468 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -1.41119e-06 *lens_ipow(begin_x, 4)*begin_y + -1.11096e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5);
    out[2] =  + -0.61015 *begin_dx + -0.0136882 *begin_x + -0.00244039 *begin_x*begin_lambda + 0.173841 *begin_dx*lens_ipow(begin_dy, 2) + 0.261672 *lens_ipow(begin_dx, 3) + -0.00228497 *begin_x*lens_ipow(begin_dy, 2) + -8.13024e-05 *begin_x*begin_y*begin_dy + 1.17087e-05 *begin_x*lens_ipow(begin_y, 2) + 1.53775e-05 *lens_ipow(begin_x, 3) + 2.05227e-08 *begin_x*lens_ipow(begin_y, 4) + 4.01072e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000477789 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 1.64539e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -2.46716e-09 *lens_ipow(begin_x, 6)*begin_dx;
    out[3] =  + -0.612338 *begin_dy + -0.0134572 *begin_y + -0.0024402 *begin_y*begin_lambda + 0.278506 *lens_ipow(begin_dy, 3) + 0.369033 *lens_ipow(begin_dx, 2)*begin_dy + -0.0044064 *begin_y*lens_ipow(begin_dx, 2) + 1.20853e-05 *lens_ipow(begin_y, 3) + 0.00456833 *begin_x*begin_dx*begin_dy + -9.96915e-05 *begin_x*begin_y*begin_dx + 9.48415e-06 *lens_ipow(begin_x, 2)*begin_y + -5.33959e-07 *lens_ipow(begin_y, 4)*begin_dy + 4.77347e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.35804e-08 *lens_ipow(begin_x, 4)*begin_y + 4.0488e-11 *lens_ipow(begin_y, 7);
    std::vector<float> pred_out_cs_pos(3);
    std::vector<float> pred_out_cs_dir(3);
    std::vector<float> outpos = {out[0], out[1]};
    std::vector<float> outdir = {out[2], out[3]};
    if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    std::vector<float> view =
    {
      scene_x - pred_out_cs_pos[0],
      scene_y - pred_out_cs_pos[1],
      scene_z - pred_out_cs_pos[2]
    };
    raytrace_normalise(view);
    std::vector<float> out_new(5);
    std::vector<float> out_new_pos(2);
    std::vector<float> out_new_dir(2);
    if (camera->lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    out_new[0] = out_new_pos[0];
    out_new[1] = out_new_pos[1];
    out_new[2] = out_new_dir[0];
    out_new[3] = out_new_dir[1];
    const std::vector<float> delta_out = {out_new[2] - out[2], out_new[3] - out[3]};
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2f domega2_dx0;
    domega2_dx0(0, 0) =  + -0.0136882  + -0.00244039 *begin_lambda + -0.00228497 *lens_ipow(begin_dy, 2) + -8.13024e-05 *begin_y*begin_dy + 1.17087e-05 *lens_ipow(begin_y, 2) + 4.61325e-05 *lens_ipow(begin_x, 2) + 2.05227e-08 *lens_ipow(begin_y, 4) + 8.02143e-05 *begin_x*begin_y*begin_dx*begin_dy + 8.22696e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -1.48029e-08 *lens_ipow(begin_x, 5)*begin_dx+0.0f;
    domega2_dx0(0, 1) =  + -8.13024e-05 *begin_x*begin_dy + 2.34174e-05 *begin_x*begin_y + 8.2091e-08 *begin_x*lens_ipow(begin_y, 3) + 4.01072e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.000955578 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 3.29079e-10 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    domega2_dx0(1, 0) =  + 0.00456833 *begin_dx*begin_dy + -9.96915e-05 *begin_y*begin_dx + 1.89683e-05 *begin_x*begin_y + 9.54694e-08 *begin_x*lens_ipow(begin_y, 3) + 9.43216e-08 *lens_ipow(begin_x, 3)*begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.0134572  + -0.0024402 *begin_lambda + -0.0044064 *lens_ipow(begin_dx, 2) + 3.62559e-05 *lens_ipow(begin_y, 2) + -9.96915e-05 *begin_x*begin_dx + 9.48415e-06 *lens_ipow(begin_x, 2) + -2.13584e-06 *lens_ipow(begin_y, 3)*begin_dy + 1.43204e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 2.35804e-08 *lens_ipow(begin_x, 4) + 2.83416e-10 *lens_ipow(begin_y, 6)+0.0f;
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
  out[4] =  + 0.328351  + 0.348894 *begin_lambda + -0.236639 *lens_ipow(begin_lambda, 2) + -0.0244445 *lens_ipow(begin_dy, 2) + -0.000554902 *begin_y*begin_dy + -0.000752644 *begin_x*begin_dx + -0.142628 *lens_ipow(begin_dy, 4) + -0.218741 *lens_ipow(begin_dx, 4) + -9.34117e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -6.47292e-08 *lens_ipow(begin_y, 4) + -0.000178247 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.31628e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -6.40034e-08 *lens_ipow(begin_x, 4) + -0.641895 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda;
else
  out[4] = 0.0f;
} break;
