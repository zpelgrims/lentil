case angenieux_double_gauss_9999_50mm:
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
       + 26.6197 *begin_dx + 7.28377 *begin_dx*begin_lambda + 1.08139 *begin_x*begin_lambda + -5.01205 *begin_dx*lens_ipow(begin_lambda, 2) + -14.6075 *begin_dx*lens_ipow(begin_dy, 2) + -15.7402 *lens_ipow(begin_dx, 3) + -1.60964 *begin_x*lens_ipow(begin_lambda, 2) + -0.180071 *begin_x*lens_ipow(begin_dy, 2) + -0.148274 *begin_x*lens_ipow(begin_dx, 2) + -0.000400788 *begin_x*lens_ipow(begin_y, 2) + 0.00185361 *lens_ipow(begin_x, 2)*begin_dx + -0.00039852 *lens_ipow(begin_x, 3) + 0.829158 *begin_x*lens_ipow(begin_lambda, 3) + -0.302493 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 7.1982e-06 *lens_ipow(begin_y, 4)*begin_dx + 0.296662 *begin_x*lens_ipow(begin_dy, 4) + -3.36856e-07 *begin_x*lens_ipow(begin_y, 4) + -0.0245448 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.000970578 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -0.000461262 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 11.7284 *lens_ipow(begin_dx, 7) + 0.0894363 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4) + 0.000170292 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -1.0516e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -1.2545e-09 *lens_ipow(begin_x, 7) + 1.03998e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_lambda + -1.94162e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3) + -1.51297e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6),
       + 26.6948 *begin_dy + 7.01455 *begin_dy*begin_lambda + 1.13586 *begin_y*begin_lambda + -4.9092 *begin_dy*lens_ipow(begin_lambda, 2) + -15.9962 *lens_ipow(begin_dy, 3) + -14.3695 *lens_ipow(begin_dx, 2)*begin_dy + -1.76618 *begin_y*lens_ipow(begin_lambda, 2) + -0.130576 *begin_y*lens_ipow(begin_dy, 2) + -0.172393 *begin_y*lens_ipow(begin_dx, 2) + -0.000509892 *lens_ipow(begin_y, 3) + 0.00184984 *lens_ipow(begin_x, 2)*begin_dy + -0.000510953 *lens_ipow(begin_x, 2)*begin_y + 0.927801 *begin_y*lens_ipow(begin_lambda, 3) + 0.00349273 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.000214599 *lens_ipow(begin_y, 3)*begin_lambda + 0.000195456 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 5.37529 *lens_ipow(begin_dy, 5) + 0.286436 *begin_y*lens_ipow(begin_dx, 4) + -0.0212604 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.00053484 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.031169 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.000804279 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.00874076 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -1.33511e-09 *lens_ipow(begin_y, 7) + -4.04232e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -3.90863e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -1.30944e-09 *lens_ipow(begin_x, 6)*begin_y + 1.51024 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)
    };
    const std::vector<float> delta_ap = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 26.6197  + 7.28377 *begin_lambda + -5.01205 *lens_ipow(begin_lambda, 2) + -14.6075 *lens_ipow(begin_dy, 2) + -47.2207 *lens_ipow(begin_dx, 2) + -0.296547 *begin_x*begin_dx + 0.00185361 *lens_ipow(begin_x, 2) + -0.907479 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 7.1982e-06 *lens_ipow(begin_y, 4) + -0.0245448 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000970578 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.000922523 *lens_ipow(begin_x, 3)*begin_dx + 82.0987 *lens_ipow(begin_dx, 6) + 0.0894363 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + 0.000340585 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -5.82485e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)+0.0f;
    dx1_domega0(0, 1) =  + -29.2149 *begin_dx*begin_dy + -0.360141 *begin_x*begin_dy + -0.302493 *begin_y*lens_ipow(begin_dx, 3) + 1.18665 *begin_x*lens_ipow(begin_dy, 3) + -0.0490897 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.000970578 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.357745 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 0.000170292 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)+0.0f;
    dx1_domega0(1, 0) =  + -28.739 *begin_dx*begin_dy + -0.344787 *begin_y*begin_dx + 1.14574 *begin_y*lens_ipow(begin_dx, 3) + -0.0425207 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.031169 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -0.000804279 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 6.04094 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 1) =  + 26.6948  + 7.01455 *begin_lambda + -4.9092 *lens_ipow(begin_lambda, 2) + -47.9885 *lens_ipow(begin_dy, 2) + -14.3695 *lens_ipow(begin_dx, 2) + -0.261152 *begin_y*begin_dy + 0.00184984 *lens_ipow(begin_x, 2) + 0.00349273 *lens_ipow(begin_y, 2)*begin_lambda + 26.8765 *lens_ipow(begin_dy, 4) + -0.0212604 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00106968 *lens_ipow(begin_y, 3)*begin_dy + 0.062338 *begin_x*begin_y*begin_dx*begin_dy + -0.000804279 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.0262223 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 4.53071 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)+0.0f;
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
    out[0] =  + 50.0087 *begin_dx + -0.625383 *begin_x + 0.70729 *begin_x*begin_lambda + -19.0752 *begin_dx*lens_ipow(begin_dy, 2) + -23.3151 *lens_ipow(begin_dx, 3) + 0.157666 *begin_y*begin_dx*begin_dy + 0.00614257 *lens_ipow(begin_y, 2)*begin_dx + -0.558055 *begin_x*lens_ipow(begin_lambda, 2) + 0.243664 *begin_x*lens_ipow(begin_dy, 2) + 0.233536 *begin_x*lens_ipow(begin_dx, 2) + 0.00539894 *begin_x*begin_y*begin_dy + -0.00125972 *begin_x*lens_ipow(begin_y, 2) + -0.00129394 *lens_ipow(begin_x, 3) + 0.000547845 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0225247 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.000592132 *lens_ipow(begin_x, 3)*begin_lambda + 0.0981907 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -7.28386e-07 *begin_x*lens_ipow(begin_y, 4) + 0.0751768 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 31.3603 *lens_ipow(begin_dx, 5)*begin_lambda + 3.21257 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 0.000245089 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2) + 5.37895 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -4.82991e-05 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 2) + -9.42516e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -2.85556e-09 *lens_ipow(begin_x, 7) + 4.76941 *begin_y*lens_ipow(begin_dx, 5)*begin_dy*begin_lambda + -2.9311e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6);
    out[1] =  + 49.4517 *begin_dy + -0.631852 *begin_y + 0.858956 *begin_dy*begin_lambda + 0.7031 *begin_y*begin_lambda + -19.3886 *lens_ipow(begin_dy, 3) + -19.773 *lens_ipow(begin_dx, 2)*begin_dy + -0.543383 *begin_y*lens_ipow(begin_lambda, 2) + 0.534516 *begin_y*lens_ipow(begin_dy, 2) + 0.259969 *begin_y*lens_ipow(begin_dx, 2) + 0.0175841 *lens_ipow(begin_y, 2)*begin_dy + -0.00120744 *lens_ipow(begin_y, 3) + 0.180395 *begin_x*begin_dx*begin_dy + 0.00786971 *begin_x*begin_y*begin_dx + 0.00526514 *lens_ipow(begin_x, 2)*begin_dy + -0.0012916 *lens_ipow(begin_x, 2)*begin_y + 0.000500256 *lens_ipow(begin_y, 3)*begin_lambda + 0.000553391 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -0.00222561 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -4.38423e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.0612953 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.000952124 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -1.88183e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -3.33147e-09 *lens_ipow(begin_y, 7) + -8.01055e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 0.000282092 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*begin_dy + -4.22047e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + -8.45799e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -7.47753e-12 *lens_ipow(begin_x, 8)*begin_y;
    out[2] =  + -0.617487 *begin_dx + -0.0123227 *begin_x + 0.0185685 *begin_dx*begin_lambda + -0.00885177 *begin_x*begin_lambda + 0.153116 *begin_dx*lens_ipow(begin_dy, 2) + 0.279253 *lens_ipow(begin_dx, 3) + 0.00725753 *begin_x*lens_ipow(begin_lambda, 2) + -0.00107725 *begin_x*lens_ipow(begin_dy, 2) + -5.80527e-05 *begin_x*begin_y*begin_dy + 1.66458e-05 *begin_x*lens_ipow(begin_y, 2) + 1.77503e-05 *lens_ipow(begin_x, 3) + -7.90104e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.000237102 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -8.78732e-06 *lens_ipow(begin_x, 3)*begin_lambda + 0.0002694 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.00437584 *begin_x*lens_ipow(begin_dy, 4) + -2.56472e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 3.63808e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 1.43766e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 2.95948e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.309751 *lens_ipow(begin_dx, 5)*begin_lambda + -0.0128176 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 0.00111078 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.000880952 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 4.80978e-11 *begin_x*lens_ipow(begin_y, 6) + 3.98432e-11 *lens_ipow(begin_x, 7) + 1.31811e-10 *lens_ipow(begin_y, 7)*begin_dx*begin_dy + 1.85146e-15 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 4);
    out[3] =  + -0.61682 *begin_dy + -0.0119668 *begin_y + 0.0113263 *begin_dy*begin_lambda + -0.00911808 *begin_y*begin_lambda + 0.328767 *lens_ipow(begin_dy, 3) + 0.40495 *lens_ipow(begin_dx, 2)*begin_dy + 0.00703676 *begin_y*lens_ipow(begin_lambda, 2) + -0.00377317 *begin_y*lens_ipow(begin_dx, 2) + -0.000129118 *lens_ipow(begin_y, 2)*begin_dy + 1.02533e-05 *lens_ipow(begin_y, 3) + 0.00289076 *begin_x*begin_dx*begin_dy + -0.000110164 *begin_x*begin_y*begin_dx + 1.4505e-05 *lens_ipow(begin_x, 2)*begin_y + -7.82077e-06 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -0.303198 *lens_ipow(begin_dy, 5) + -0.432733 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.299426 *lens_ipow(begin_dx, 4)*begin_dy + 0.000781458 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 3.20858e-08 *lens_ipow(begin_y, 5) + 2.56728e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 4.13021e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.11827e-08 *lens_ipow(begin_x, 4)*begin_y + -2.44504e-08 *lens_ipow(begin_y, 5)*begin_lambda + -0.0473817 *begin_y*lens_ipow(begin_dy, 6) + 1.99151e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -1.00118e-09 *lens_ipow(begin_x, 6)*begin_dy + -4.9049e-14 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8)*begin_dy + 2.30758e-11 *lens_ipow(begin_x, 8)*lens_ipow(begin_dy, 3);
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
    domega2_dx0(0, 0) =  + -0.0123227  + -0.00885177 *begin_lambda + 0.00725753 *lens_ipow(begin_lambda, 2) + -0.00107725 *lens_ipow(begin_dy, 2) + -5.80527e-05 *begin_y*begin_dy + 1.66458e-05 *lens_ipow(begin_y, 2) + 5.32509e-05 *lens_ipow(begin_x, 2) + -7.90104e-06 *lens_ipow(begin_y, 2)*begin_lambda + -0.000474204 *begin_x*begin_dx*begin_lambda + -2.6362e-05 *lens_ipow(begin_x, 2)*begin_lambda + -0.00437584 *lens_ipow(begin_dy, 4) + -2.56472e-07 *lens_ipow(begin_y, 3)*begin_dy + 7.27616e-05 *begin_x*begin_y*begin_dx*begin_dy + 4.31298e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 8.87845e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.0128176 *lens_ipow(begin_dx, 4)*begin_lambda + 0.00222156 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.0017619 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + 4.80978e-11 *lens_ipow(begin_y, 6) + 2.78902e-10 *lens_ipow(begin_x, 6) + 1.29602e-14 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4)+0.0f;
    domega2_dx0(0, 1) =  + -5.80527e-05 *begin_x*begin_dy + 3.32917e-05 *begin_x*begin_y + -1.58021e-05 *begin_x*begin_y*begin_lambda + 0.000538801 *begin_y*lens_ipow(begin_dx, 3) + -7.69416e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 3.63808e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 5.91897e-08 *lens_ipow(begin_x, 3)*begin_y + 2.88587e-10 *begin_x*lens_ipow(begin_y, 5) + 9.22679e-10 *lens_ipow(begin_y, 6)*begin_dx*begin_dy + 7.40583e-15 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.00289076 *begin_dx*begin_dy + -0.000110164 *begin_y*begin_dx + 2.90099e-05 *begin_x*begin_y + -1.56415e-05 *begin_x*begin_y*begin_lambda + 2.56728e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 8.26041e-08 *begin_x*lens_ipow(begin_y, 3) + 8.4731e-08 *lens_ipow(begin_x, 3)*begin_y + 1.99151e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -6.00708e-09 *lens_ipow(begin_x, 5)*begin_dy + -9.8098e-14 *begin_x*lens_ipow(begin_y, 8)*begin_dy + 1.84606e-10 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.0119668  + -0.00911808 *begin_lambda + 0.00703676 *lens_ipow(begin_lambda, 2) + -0.00377317 *lens_ipow(begin_dx, 2) + -0.000258236 *begin_y*begin_dy + 3.076e-05 *lens_ipow(begin_y, 2) + -0.000110164 *begin_x*begin_dx + 1.4505e-05 *lens_ipow(begin_x, 2) + -7.82077e-06 *lens_ipow(begin_x, 2)*begin_lambda + 0.00156292 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.60429e-07 *lens_ipow(begin_y, 4) + 5.13455e-05 *begin_x*begin_y*begin_dx*begin_dy + 1.23906e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 2.11827e-08 *lens_ipow(begin_x, 4) + -1.22252e-07 *lens_ipow(begin_y, 4)*begin_lambda + -0.0473817 *lens_ipow(begin_dy, 6) + 5.97453e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -3.92392e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7)*begin_dy+0.0f;
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
  out[4] =  + 0.236859  + 0.860742 *begin_lambda + -1.17964 *lens_ipow(begin_lambda, 2) + 0.570311 *lens_ipow(begin_lambda, 3) + -0.237159 *lens_ipow(begin_dy, 4) + -0.235384 *lens_ipow(begin_dx, 4) + -0.010597 *begin_y*lens_ipow(begin_dy, 3) + -0.0100229 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000168744 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000122748 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0105681 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0101157 *begin_x*lens_ipow(begin_dx, 3) + -0.000127847 *begin_x*begin_y*begin_dx*begin_dy + -0.000112047 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -8.57444e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -4.66147e-08 *lens_ipow(begin_x, 4) + -1.38237 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.956783 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.00142196 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.00145854 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.62998e-10 *lens_ipow(begin_y, 6) + -0.00252304 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.00225779 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.00205028 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00151833 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -2.49674e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 2) + -0.000723719 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -1.99059e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4);
else
  out[4] = 0.0f;
} break;
