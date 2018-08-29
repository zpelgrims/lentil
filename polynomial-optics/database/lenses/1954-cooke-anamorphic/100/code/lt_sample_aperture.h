case cooke_anamorphic_1954_100mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
float view[3] =
{
  scene_x,
  scene_y,
  scene_z + camera_data->lens_outer_pupil_curvature_radius
};
normalise(view);
int error = 0;
if(1 || view[2] >= camera_data->lens_field_of_view)
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
    const float pred_ap[2] = {
       + 47.6584 *begin_dx + 0.937613 *begin_x + 0.0893812 *begin_x*begin_lambda + 4.20096 *begin_dx*begin_lambda + -2.83632 *begin_y*begin_dx*begin_dy + -0.0547221 *begin_x*begin_y*begin_dy + -104.57 *lens_ipow(begin_dx, 3) + -109.637 *begin_dx*lens_ipow(begin_dy, 2) + -0.000408792 *begin_x*lens_ipow(begin_y, 2) + -1.77898 *begin_x*lens_ipow(begin_dy, 2) + -0.0183395 *lens_ipow(begin_y, 2)*begin_dx + -37.6423 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -192.197 *lens_ipow(begin_dx, 3)*begin_lambda + -0.00442832 *lens_ipow(begin_x, 3)*begin_lambda + -0.613822 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -0.000143489 *lens_ipow(begin_x, 4)*begin_dx + 0.00389404 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 32.9374 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -1.38259e-06 *lens_ipow(begin_x, 5) + -0.00371455 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 1.18972 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 3) + -1.26086e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dy + -5.63497e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -0.729554 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 4) + -2.79463e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -8.00047 *begin_dx*lens_ipow(begin_lambda, 7) + 334.055 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 5) + -0.165046 *begin_x*lens_ipow(begin_lambda, 7),
       + 0.530478 *begin_y + 35.9657 *begin_dy + 5.4834 *begin_dy*begin_lambda + 0.0864972 *begin_y*begin_lambda + -1.83727 *begin_y*lens_ipow(begin_dx, 2) + -0.029353 *lens_ipow(begin_y, 2)*begin_dy + -2.70308 *begin_y*lens_ipow(begin_dy, 2) + -5.3588 *begin_x*begin_dx*begin_dy + -0.0680939 *begin_x*begin_y*begin_dx + -147.386 *lens_ipow(begin_dx, 2)*begin_dy + -0.0589897 *begin_y*lens_ipow(begin_lambda, 2) + -0.000661932 *lens_ipow(begin_x, 2)*begin_y + -3.69976 *begin_dy*lens_ipow(begin_lambda, 2) + -0.000138807 *lens_ipow(begin_y, 3) + -0.0530305 *lens_ipow(begin_x, 2)*begin_dy + -81.7688 *lens_ipow(begin_dy, 3) + -0.000301658 *lens_ipow(begin_y, 4)*begin_dy + -0.676003 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -1.5937e-06 *lens_ipow(begin_y, 5) + -0.0217948 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -9.99048e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -8.35568e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -0.000434344 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.114583 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4) + -0.011158 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -6.49134e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -2.08893e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + -2.23623e-05 *lens_ipow(begin_x, 6)*begin_y*lens_ipow(begin_dy, 4)
    };
    const float delta_ap[] = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =  + 47.6584  + 4.20096 *begin_lambda + -2.83632 *begin_y*begin_dy + -313.71 *lens_ipow(begin_dx, 2) + -109.637 *lens_ipow(begin_dy, 2) + -0.0183395 *lens_ipow(begin_y, 2) + -75.2846 *begin_x*begin_dx*begin_lambda + -576.591 *lens_ipow(begin_dx, 2)*begin_lambda + -0.613822 *lens_ipow(begin_x, 2)*begin_lambda + -0.000143489 *lens_ipow(begin_x, 4) + 65.8747 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.00742911 *lens_ipow(begin_x, 3)*begin_dx + 1.18972 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + -0.729554 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 4) + -2.79463e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -8.00047 *lens_ipow(begin_lambda, 7) + 1002.16 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5)+0.0f;
    dx1_domega0[0][1] =  + -2.83632 *begin_y*begin_dx + -0.0547221 *begin_x*begin_y + -219.274 *begin_dx*begin_dy + -3.55795 *begin_x*begin_dy + -1.26086e-07 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    dx1_domega0[1][0] =  + -3.67454 *begin_y*begin_dx + -5.3588 *begin_x*begin_dy + -0.0680939 *begin_x*begin_y + -294.771 *begin_dx*begin_dy + -9.99048e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + -8.35568e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -0.000868689 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -0.458333 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -0.0334741 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)+0.0f;
    dx1_domega0[1][1] =  + 35.9657  + 5.4834 *begin_lambda + -0.029353 *lens_ipow(begin_y, 2) + -5.40617 *begin_y*begin_dy + -5.3588 *begin_x*begin_dx + -147.386 *lens_ipow(begin_dx, 2) + -3.69976 *lens_ipow(begin_lambda, 2) + -0.0530305 *lens_ipow(begin_x, 2) + -245.307 *lens_ipow(begin_dy, 2) + -0.000301658 *lens_ipow(begin_y, 4) + -2.02801 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0435895 *lens_ipow(begin_y, 3)*begin_dy + -9.99048e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + -2.08893e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -8.94494e-05 *lens_ipow(begin_x, 6)*begin_y*lens_ipow(begin_dy, 3)+0.0f;
    float invApJ[2][2];
    const float invdetap = 1.0f/(dx1_domega0[0][0]*dx1_domega0[1][1] - dx1_domega0[0][1]*dx1_domega0[1][0]);
    invApJ[0][0] =  dx1_domega0[1][1]*invdetap;
    invApJ[1][1] =  dx1_domega0[0][0]*invdetap;
    invApJ[0][1] = -dx1_domega0[0][1]*invdetap;
    invApJ[1][0] = -dx1_domega0[1][0]*invdetap;
    for(int i=0;i<2;i++)
    {
      dx += invApJ[0][i]*delta_ap[i];
      dy += invApJ[1][i]*delta_ap[i];
    }
    out[0] =  + 45.3046 *begin_dx + 0.0505018 *begin_x + 0.0398901 *begin_x*begin_lambda + 10.554 *begin_y*begin_dx*begin_dy + 0.230489 *begin_x*begin_y*begin_dy + 0.0835558 *lens_ipow(begin_x, 2)*begin_dx + 68.3157 *lens_ipow(begin_dx, 3) + 0.00195603 *begin_x*lens_ipow(begin_y, 2) + 0.000673976 *lens_ipow(begin_x, 3) + 4.62051 *begin_x*lens_ipow(begin_dx, 2) + 0.0893859 *lens_ipow(begin_y, 2)*begin_dx + 1.28778 *begin_dx*lens_ipow(begin_lambda, 2) + 15.5772 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 681.922 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -1.10506 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 3.03577e-05 *lens_ipow(begin_x, 4)*begin_dx + -34.1744 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -9.6459e-07 *begin_x*lens_ipow(begin_y, 4) + 0.000157139 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.000115756 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.385085 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -16.8984 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -762.166 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.338811 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + 2.77952e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -0.841429 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5) + 2.23658e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 115.103 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 7);
    out[1] =  + 108.616 *begin_dy + -30.7931 *begin_dy*begin_lambda + -0.147579 *begin_y*begin_lambda + 9.65698 *begin_y*lens_ipow(begin_dx, 2) + 0.323152 *lens_ipow(begin_y, 2)*begin_dy + 15.7728 *begin_y*lens_ipow(begin_dy, 2) + 0.417173 *begin_x*begin_y*begin_dx + 583.948 *lens_ipow(begin_dx, 2)*begin_dy + 0.00453956 *lens_ipow(begin_x, 2)*begin_y + 20.489 *begin_dy*lens_ipow(begin_lambda, 2) + 0.00186761 *lens_ipow(begin_y, 3) + 301.009 *lens_ipow(begin_dy, 3) + 1.54883 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.0890778 *begin_y*lens_ipow(begin_lambda, 3) + 144.568 *begin_x*begin_dx*begin_dy*begin_lambda + -265.276 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 0.0154924 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.000375269 *lens_ipow(begin_y, 4)*begin_dy + 0.000485294 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -0.140706 *begin_x*begin_y*lens_ipow(begin_dx, 3) + 3.87351 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.0175119 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -9.79201e-07 *lens_ipow(begin_x, 4)*begin_y + -2.84299 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -1.92288e-06 *lens_ipow(begin_y, 5) + 0.0842429 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 1.71653 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 160.047 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 3);
    out[2] =  + -2.15435 *begin_dx + -0.0247778 *begin_x + -0.00107602 *begin_x*begin_lambda + -0.224009 *begin_y*begin_dx*begin_dy + -0.00523143 *begin_x*begin_y*begin_dy + -0.00135233 *lens_ipow(begin_x, 2)*begin_dx + 0.817481 *lens_ipow(begin_dx, 3) + -4.25139e-05 *begin_x*lens_ipow(begin_y, 2) + -1.51765e-05 *lens_ipow(begin_x, 3) + -0.0478267 *begin_x*lens_ipow(begin_dx, 2) + -0.00196908 *lens_ipow(begin_y, 2)*begin_dx + -0.0212488 *begin_dx*lens_ipow(begin_lambda, 3) + -0.516604 *lens_ipow(begin_dx, 3)*begin_lambda + -10.3917 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -1.078e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.453335 *begin_x*lens_ipow(begin_dx, 4) + 0.023045 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 1.03439 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.000600987 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 3.25178e-08 *begin_x*lens_ipow(begin_y, 4) + -0.000116327 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.80265e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -9.52297e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -1.25429 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000954062 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000255455 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 1.47608 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 41.0533 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 7);
    out[3] =  + -0.00921651 *begin_y + 0.933852 *begin_dy + -0.163446 *begin_dy*begin_lambda + -0.0013627 *begin_y*begin_lambda + 0.00371741 *lens_ipow(begin_y, 2)*begin_dy + 0.123824 *begin_y*lens_ipow(begin_dy, 2) + 1.60997e-05 *lens_ipow(begin_y, 3) + 0.00508672 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1600.28 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 77.3019 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + 1.60372 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.119016 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.108661 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 35.2487 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.975157 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 5.1066e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.017237 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.193954 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + 1.77729e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + 7.3523e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dx + -39.332 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + 7.49375e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -211477 *begin_x*begin_dx*lens_ipow(begin_dy, 7) + -0.722629 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 4) + -0.0107608 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + 2.38659e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8)*begin_dy + 0.00233283 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -4.25963e-07 *begin_x*lens_ipow(begin_y, 7)*begin_dx*lens_ipow(begin_dy, 2);
    float pred_out_cs[7] = {0.0f};
    if (camera_data->lens_outer_pupil_geometry == "cyl-y") lens_cylinderToCs(out, out+2, pred_out_cs, pred_out_cs+3, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius, true);
    else if (camera_data->lens_outer_pupil_geometry == "cyl-x") lens_cylinderToCs(out, out+2, pred_out_cs, pred_out_cs+3, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius, false);
    else lens_sphereToCs(out, out+2, pred_out_cs, pred_out_cs+3, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius);
    float view[3] =
    {
      scene_x - pred_out_cs[0],
      scene_y - pred_out_cs[1],
      scene_z - pred_out_cs[2]
    };
    normalise(view);
    float out_new[5];
    if (camera_data->lens_outer_pupil_geometry == "cyl-y") lens_csToCylinder(pred_out_cs, view, out_new, out_new+2, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius, true);
    else if (camera_data->lens_outer_pupil_geometry == "cyl-x") lens_csToCylinder(pred_out_cs, view, out_new, out_new+2, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius, false);
    else lens_csToSphere(pred_out_cs, view, out_new, out_new+2, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius);
    const float delta_out[] = {out_new[2] - out[2], out_new[3] - out[3]};
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    float domega2_dx0[2][2];
    domega2_dx0[0][0] =  + -0.0247778  + -0.00107602 *begin_lambda + -0.00523143 *begin_y*begin_dy + -0.00270466 *begin_x*begin_dx + -4.25139e-05 *lens_ipow(begin_y, 2) + -4.55295e-05 *lens_ipow(begin_x, 2) + -0.0478267 *lens_ipow(begin_dx, 2) + -3.23399e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.453335 *lens_ipow(begin_dx, 4) + 0.04609 *begin_x*lens_ipow(begin_dx, 3) + -0.000600987 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 3.25178e-08 *lens_ipow(begin_y, 4) + -3.60531e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -2.85689e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.25429 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.00190812 *begin_x*begin_y*begin_dx*begin_dy + 0.000766365 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 1.47608 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0[0][1] =  + -0.224009 *begin_dx*begin_dy + -0.00523143 *begin_x*begin_dy + -8.50278e-05 *begin_x*begin_y + -0.00393817 *begin_y*begin_dx + -2.156e-07 *lens_ipow(begin_x, 3)*begin_y + 1.03439 *lens_ipow(begin_dx, 3)*begin_dy + -0.00120197 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 1.30071e-07 *begin_x*lens_ipow(begin_y, 3) + -0.000348981 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -3.60531e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -9.52297e-06 *lens_ipow(begin_x, 3)*begin_dy + -0.000954062 *lens_ipow(begin_x, 2)*begin_dx*begin_dy+0.0f;
    domega2_dx0[1][0] =  + 0.00508672 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 77.3019 *begin_dx*lens_ipow(begin_dy, 3) + 1.60372 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 1.95031 *begin_x*lens_ipow(begin_dy, 3) + 0.000102132 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.034474 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 7.3523e-07 *lens_ipow(begin_y, 5)*begin_dx + -78.6639 *begin_x*lens_ipow(begin_dy, 5) + 1.49875e-08 *begin_x*lens_ipow(begin_y, 5) + -211477 *begin_dx*lens_ipow(begin_dy, 7) + -0.722629 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 4) + -0.0215217 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + 4.77319e-11 *begin_x*lens_ipow(begin_y, 8)*begin_dy + -4.25963e-07 *lens_ipow(begin_y, 7)*begin_dx*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0[1][1] =  + -0.00921651  + -0.0013627 *begin_lambda + 0.00743483 *begin_y*begin_dy + 0.123824 *lens_ipow(begin_dy, 2) + 4.82992e-05 *lens_ipow(begin_y, 2) + 0.0101734 *begin_x*begin_y*begin_dx*begin_dy + 1.60372 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.238032 *begin_y*lens_ipow(begin_dy, 3) + 0.217322 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 35.2487 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.000102132 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.017237 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.581862 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + 8.88647e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 3.67615e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx + 3.74687e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -2.16789 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4) + -0.0322825 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + 1.90927e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7)*begin_dy + 0.013997 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -2.98174e-06 *begin_x*lens_ipow(begin_y, 6)*begin_dx*lens_ipow(begin_dy, 2)+0.0f;
    float invJ[2][2];
    const float invdet = 1.0f/(domega2_dx0[0][0]*domega2_dx0[1][1] - domega2_dx0[0][1]*domega2_dx0[1][0]);
    invJ[0][0] =  domega2_dx0[1][1]*invdet;
    invJ[1][1] =  domega2_dx0[0][0]*invdet;
    invJ[0][1] = -domega2_dx0[0][1]*invdet;
    invJ[1][0] = -domega2_dx0[1][0]*invdet;
    for(int i=0;i<2;i++)
    {
      x += invJ[0][i]*delta_out[i];
      y += invJ[1][i]*delta_out[i];
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
if(out[0]*out[0]+out[1]*out[1] > camera_data->lens_outer_pupil_radius*camera_data->lens_outer_pupil_radius) error |= 16;
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.287066  + 0.832387 *begin_lambda + 0.00377883 *begin_y*begin_dy + 0.00887147 *begin_x*begin_dx + 3.78765e-05 *lens_ipow(begin_y, 2) + 9.90311e-05 *lens_ipow(begin_x, 2) + 0.199979 *lens_ipow(begin_dx, 2) + -1.14297 *lens_ipow(begin_lambda, 2) + 0.553183 *lens_ipow(begin_lambda, 3) + -52.3271 *lens_ipow(begin_dx, 4) + -0.901392 *begin_y*lens_ipow(begin_dy, 3) + -0.0135634 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -4.10089 *begin_x*lens_ipow(begin_dx, 3) + -50.0969 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000740032 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.000599113 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -6.63767e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.48246e-06 *lens_ipow(begin_y, 4) + -0.123363 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.58808 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00168849 *lens_ipow(begin_x, 3)*begin_dx + -0.025519 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -2.08671 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -8.87569e-06 *lens_ipow(begin_x, 4) + -0.0682791 *begin_x*begin_y*begin_dx*begin_dy + -0.0217798 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000318805 *lens_ipow(begin_y, 3)*begin_dy + -60522.4 *lens_ipow(begin_dy, 8);
else
  out[4] = 0.0f;
} break;
