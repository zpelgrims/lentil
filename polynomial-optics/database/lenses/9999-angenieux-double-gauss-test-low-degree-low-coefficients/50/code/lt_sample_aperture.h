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
       + 28.2028 *begin_dx + 0.195015 *begin_x + 1.80203 *begin_dx*begin_lambda + 0.0827779 *begin_x*begin_lambda + -15.9536 *begin_dx*lens_ipow(begin_dy, 2) + -15.9163 *lens_ipow(begin_dx, 3) + -0.107283 *begin_y*begin_dx*begin_dy + -0.115813 *begin_x*lens_ipow(begin_dy, 2) + -0.223652 *begin_x*lens_ipow(begin_dx, 2) + -0.000287134 *begin_x*lens_ipow(begin_y, 2) + -0.000307077 *lens_ipow(begin_x, 3) + -7.82062e-07 *begin_x*lens_ipow(begin_y, 4) + -1.5295e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -6.97961e-07 *lens_ipow(begin_x, 5),
       + 28.218 *begin_dy + 0.194886 *begin_y + 1.77846 *begin_dy*begin_lambda + 0.0825992 *begin_y*begin_lambda + -15.9435 *lens_ipow(begin_dy, 3) + -15.9016 *lens_ipow(begin_dx, 2)*begin_dy + -0.223052 *begin_y*lens_ipow(begin_dy, 2) + -0.11646 *begin_y*lens_ipow(begin_dx, 2) + -0.000301214 *lens_ipow(begin_y, 3) + -0.106337 *begin_x*begin_dx*begin_dy + -0.000288825 *lens_ipow(begin_x, 2)*begin_y + -7.18236e-07 *lens_ipow(begin_y, 5) + -1.55876e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -7.59872e-07 *lens_ipow(begin_x, 4)*begin_y
    };
    const std::vector<float> delta_ap = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 28.2028  + 1.80203 *begin_lambda + -15.9536 *lens_ipow(begin_dy, 2) + -47.749 *lens_ipow(begin_dx, 2) + -0.107283 *begin_y*begin_dy + -0.447305 *begin_x*begin_dx+0.0f;
    dx1_domega0(0, 1) =  + -31.9073 *begin_dx*begin_dy + -0.107283 *begin_y*begin_dx + -0.231626 *begin_x*begin_dy+0.0f;
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
    out[0] =  + 50.1459 *begin_dx + -0.511723 *begin_x + 0.189872 *begin_x*begin_lambda + -20.779 *begin_dx*lens_ipow(begin_dy, 2) + -20.3287 *lens_ipow(begin_dx, 3) + 0.252909 *begin_x*lens_ipow(begin_dy, 2) + 0.318411 *begin_x*lens_ipow(begin_dx, 2) + 0.00592114 *begin_x*begin_y*begin_dy + -0.0011197 *begin_x*lens_ipow(begin_y, 2) + 0.013221 *lens_ipow(begin_x, 2)*begin_dx + -0.000831514 *lens_ipow(begin_x, 3) + 2.55569e-05 *lens_ipow(begin_y, 4)*begin_dx + -2.16711e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -1.22874e-06 *lens_ipow(begin_x, 5);
    out[1] =  + 50.136 *begin_dy + -0.512954 *begin_y + 0.190038 *begin_y*begin_lambda + -20.2295 *lens_ipow(begin_dy, 3) + -20.7874 *lens_ipow(begin_dx, 2)*begin_dy + 0.329953 *begin_y*lens_ipow(begin_dy, 2) + 0.252932 *begin_y*lens_ipow(begin_dx, 2) + 0.013515 *lens_ipow(begin_y, 2)*begin_dy + -0.000819861 *lens_ipow(begin_y, 3) + 0.00582583 *begin_x*begin_y*begin_dx + -0.00111165 *lens_ipow(begin_x, 2)*begin_y + -1.25426e-06 *lens_ipow(begin_y, 5) + -2.26339e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.52991e-05 *lens_ipow(begin_x, 4)*begin_dy;
    out[2] =  + -0.609054 *begin_dx + -0.0134161 *begin_x + -0.00247318 *begin_x*begin_lambda + 0.167404 *begin_dx*lens_ipow(begin_dy, 2) + 0.271939 *lens_ipow(begin_dx, 3) + -0.00243114 *begin_x*lens_ipow(begin_dy, 2) + -0.000100289 *begin_x*begin_y*begin_dy + 8.72631e-06 *begin_x*lens_ipow(begin_y, 2) + 1.06648e-05 *lens_ipow(begin_x, 3) + 2.22203e-08 *begin_x*lens_ipow(begin_y, 4) + 3.27548e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 4.59792e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -5.3944e-07 *lens_ipow(begin_x, 4)*begin_dx + 1.65734e-08 *lens_ipow(begin_x, 5);
    out[3] =  + -0.612368 *begin_dy + -0.0133897 *begin_y + -0.00244101 *begin_y*begin_lambda + 0.27869 *lens_ipow(begin_dy, 3) + 0.368978 *lens_ipow(begin_dx, 2)*begin_dy + -0.00440674 *begin_y*lens_ipow(begin_dx, 2) + 9.82949e-06 *lens_ipow(begin_y, 3) + 0.00456728 *begin_x*begin_dx*begin_dy + -9.96711e-05 *begin_x*begin_y*begin_dx + 9.43078e-06 *lens_ipow(begin_x, 2)*begin_y + -5.31726e-07 *lens_ipow(begin_y, 4)*begin_dy + 1.82196e-08 *lens_ipow(begin_y, 5) + 4.80663e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.37038e-08 *lens_ipow(begin_x, 4)*begin_y;
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
    domega2_dx0(0, 0) =  + -0.0134161  + -0.00247318 *begin_lambda + -0.00243114 *lens_ipow(begin_dy, 2) + -0.000100289 *begin_y*begin_dy + 8.72631e-06 *lens_ipow(begin_y, 2) + 3.19944e-05 *lens_ipow(begin_x, 2) + 2.22203e-08 *lens_ipow(begin_y, 4) + 6.55096e-05 *begin_x*begin_y*begin_dx*begin_dy + 1.37938e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.15776e-06 *lens_ipow(begin_x, 3)*begin_dx + 8.2867e-08 *lens_ipow(begin_x, 4)+0.0f;
    domega2_dx0(0, 1) =  + -0.000100289 *begin_x*begin_dy + 1.74526e-05 *begin_x*begin_y + 8.88811e-08 *begin_x*lens_ipow(begin_y, 3) + 3.27548e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 9.19584e-08 *lens_ipow(begin_x, 3)*begin_y+0.0f;
    domega2_dx0(1, 0) =  + 0.00456728 *begin_dx*begin_dy + -9.96711e-05 *begin_y*begin_dx + 1.88616e-05 *begin_x*begin_y + 9.61326e-08 *begin_x*lens_ipow(begin_y, 3) + 9.48153e-08 *lens_ipow(begin_x, 3)*begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.0133897  + -0.00244101 *begin_lambda + -0.00440674 *lens_ipow(begin_dx, 2) + 2.94885e-05 *lens_ipow(begin_y, 2) + -9.96711e-05 *begin_x*begin_dx + 9.43078e-06 *lens_ipow(begin_x, 2) + -2.1269e-06 *lens_ipow(begin_y, 3)*begin_dy + 9.10982e-08 *lens_ipow(begin_y, 4) + 1.44199e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 2.37038e-08 *lens_ipow(begin_x, 4)+0.0f;
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
