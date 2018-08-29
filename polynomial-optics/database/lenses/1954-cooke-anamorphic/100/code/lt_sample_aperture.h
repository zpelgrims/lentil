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
       + 45.8346 *begin_dx + 0.072029 *begin_x + 10.5615 *begin_y*begin_dx*begin_dy + 0.230691 *begin_x*begin_y*begin_dy + 0.0018659 *begin_x*lens_ipow(begin_y, 2) + 1.15105 *begin_x*lens_ipow(begin_dx, 2) + 0.0862307 *lens_ipow(begin_y, 2)*begin_dx + 3.19087 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 18.7122 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.0202041 *begin_x*lens_ipow(begin_lambda, 3) + 0.144219 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 591.545 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 4.87128e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 70.1906 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 0.00471506 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 0.0393111 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -9.73852e-07 *begin_x*lens_ipow(begin_y, 4) + 0.000853952 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -15.758 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.51985 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -545.774 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.0902823 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 3) + -0.00518424 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + 264.939 *lens_ipow(begin_dx, 5)*begin_lambda + 4.60888e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.713043 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 0.000550574 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 3) + 1.08044e-05 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 5),
       + 110.39 *begin_dy + -32.8199 *begin_dy*begin_lambda + -0.120491 *begin_y*begin_lambda + 0.328465 *lens_ipow(begin_y, 2)*begin_dy + 15.961 *begin_y*lens_ipow(begin_dy, 2) + 18.2262 *begin_dy*lens_ipow(begin_lambda, 2) + 0.0018724 *lens_ipow(begin_y, 3) + 315.616 *lens_ipow(begin_dy, 3) + 17.125 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 1080.62 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.496503 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.754668 *begin_x*begin_y*begin_dx*begin_lambda + 46.4296 *begin_x*begin_dx*begin_dy*begin_lambda + 0.00822273 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 0.0160401 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0037117 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 3.39255e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.0938072 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -2.27782e-06 *lens_ipow(begin_y, 5) + -0.141639 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -0.00598473 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -6.31412e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 0.246662 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.00102745 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 2) + 0.0270785 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000504414 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 17.9584 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + 0.00123881 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 6)
    };
    const float delta_ap[] = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =  + 45.8346  + 10.5615 *begin_y*begin_dy + 2.3021 *begin_x*begin_dx + 0.0862307 *lens_ipow(begin_y, 2) + 6.38174 *begin_x*begin_dx*begin_lambda + 0.144219 *lens_ipow(begin_x, 2)*begin_lambda + 591.545 *lens_ipow(begin_dy, 2)*begin_lambda + 210.572 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.0786222 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.000853952 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 1.55955 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -545.774 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.0902823 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + 1324.69 *lens_ipow(begin_dx, 4)*begin_lambda + 4.60888e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -2.13913 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000550574 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0[0][1] =  + 10.5615 *begin_y*begin_dx + 0.230691 *begin_x*begin_y + 37.4244 *begin_x*begin_dy*begin_lambda + 1183.09 *begin_dx*begin_dy*begin_lambda + -31.516 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -1091.55 *begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + 4.60888e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx+0.0f;
    dx1_domega0[1][0] =  + 34.2501 *begin_y*begin_dx*begin_lambda + 2161.23 *begin_dx*begin_dy*begin_lambda + 0.754668 *begin_x*begin_y*begin_lambda + 46.4296 *begin_x*begin_dy*begin_lambda + 0.0160401 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.0037117 *begin_x*lens_ipow(begin_y, 3) + 0.187614 *lens_ipow(begin_y, 3)*begin_dx + -0.283278 *lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -0.00598473 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + 0.054157 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.000504414 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0[1][1] =  + 110.39  + -32.8199 *begin_lambda + 0.328465 *lens_ipow(begin_y, 2) + 31.922 *begin_y*begin_dy + 18.2262 *lens_ipow(begin_lambda, 2) + 946.849 *lens_ipow(begin_dy, 2) + 1080.62 *lens_ipow(begin_dx, 2)*begin_lambda + 0.496503 *lens_ipow(begin_x, 2)*begin_lambda + 46.4296 *begin_x*begin_dx*begin_lambda + 0.0160401 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.493323 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + 0.00102745 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 2) + 53.8753 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3)+0.0f;
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
    out[0] =  + 45.1299 *begin_dx + 0.0547915 *begin_x + 0.0335861 *begin_x*begin_lambda + 1.03222 *begin_dx*begin_lambda + 10.3378 *begin_y*begin_dx*begin_dy + 0.229037 *begin_x*begin_y*begin_dy + 0.0845842 *lens_ipow(begin_x, 2)*begin_dx + 65.8135 *lens_ipow(begin_dx, 3) + 0.00195235 *begin_x*lens_ipow(begin_y, 2) + 0.000574072 *lens_ipow(begin_x, 3) + 4.61926 *begin_x*lens_ipow(begin_dx, 2) + 0.0908599 *lens_ipow(begin_y, 2)*begin_dx + 15.2135 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.000159916 *lens_ipow(begin_x, 3)*begin_lambda + 647.528 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -1.22395e-06 *begin_x*lens_ipow(begin_y, 4) + 0.00435393 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + -16.0613 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -683.245 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.0106202 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 3) + 0.147476 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + 0.000668408 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3) + 0.0451765 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 2182.59 *lens_ipow(begin_dx, 7) + -2.78452 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5) + 1.32628e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 4.91098e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2) + 42.8533 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 7);
    out[1] =  + 107.555 *begin_dy + -20.8297 *begin_dy*begin_lambda + -0.14262 *begin_y*begin_lambda + 0.341381 *lens_ipow(begin_y, 2)*begin_dy + 16.5558 *begin_y*lens_ipow(begin_dy, 2) + 0.00210329 *lens_ipow(begin_y, 3) + 312 *lens_ipow(begin_dy, 3) + 257.352 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 0.046678 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 2) + 17.8295 *begin_dy*lens_ipow(begin_lambda, 4) + 2.45521 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 107.674 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 4.43444 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 2.75735 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -3.8173e-06 *lens_ipow(begin_y, 5) + 5779.89 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.048985 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -127.742 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -6805.01 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -1.04178e-06 *lens_ipow(begin_x, 4)*begin_y*begin_lambda + -3.24637 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -0.054712 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 3) + -303.169 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -7.90788e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 0.0237244 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -5.2461 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 3) + 0.458288 *begin_y*lens_ipow(begin_lambda, 8) + 0.00157201 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 4)*begin_lambda;
    out[2] =  + -2.15749 *begin_dx + -0.0250214 *begin_x + -0.000623142 *begin_x*begin_lambda + -0.221156 *begin_y*begin_dx*begin_dy + -0.00521228 *begin_x*begin_y*begin_dy + 1.37937 *lens_ipow(begin_dx, 3) + -4.41954e-05 *begin_x*lens_ipow(begin_y, 2) + -0.00200889 *lens_ipow(begin_y, 2)*begin_dx + -0.107155 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -1.99762 *lens_ipow(begin_dx, 3)*begin_lambda + -0.336599 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + -3.2506e-05 *lens_ipow(begin_x, 3)*begin_lambda + -0.00261784 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -12.7866 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 1.02142e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 4.12732e-08 *begin_x*lens_ipow(begin_y, 4) + -0.000153833 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + -4.22808e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.0079717 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.346503 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 12.9437 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -3.47055e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -3.0152e-09 *lens_ipow(begin_x, 6)*begin_dx + -7.91354e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3) + -3.08691e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -0.000704217 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4) + 26.7011 *begin_y*lens_ipow(begin_dx, 5)*begin_dy + 0.584062 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy;
    out[3] =  + -0.0076263 *begin_y + 1.00242 *begin_dy + -0.316473 *begin_dy*begin_lambda + -0.00993046 *begin_y*begin_lambda + 0.0045692 *lens_ipow(begin_y, 2)*begin_dy + 0.24853 *begin_y*lens_ipow(begin_dy, 2) + 0.00753626 *begin_y*lens_ipow(begin_lambda, 2) + 2.80279e-05 *lens_ipow(begin_y, 3) + 0.000560175 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 2) + 1.3046 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.0535956 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -3.36394e-08 *lens_ipow(begin_y, 5) + 0.432933 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.000280821 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -1.45168 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 6067.33 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -0.000622746 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 3) + 153.009 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -0.0596003 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 3) + -0.244844 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_dy + 54.0421 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 4) + -9837.29 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 31.5323 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 4) + 0.0255917 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 4) + 2.37088 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + -401.059 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -2.84138e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + -4.79738 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 5);
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
    domega2_dx0[0][0] =  + -0.0250214  + -0.000623142 *begin_lambda + -0.00521228 *begin_y*begin_dy + -4.41954e-05 *lens_ipow(begin_y, 2) + -0.107155 *lens_ipow(begin_dx, 2)*begin_lambda + -0.336599 *lens_ipow(begin_dy, 2)*begin_lambda + -9.75181e-05 *lens_ipow(begin_x, 2)*begin_lambda + -0.00523568 *begin_x*begin_dx*begin_lambda + 3.06425e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 4.12732e-08 *lens_ipow(begin_y, 4) + -8.45617e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.346503 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -3.47055e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -1.80912e-08 *lens_ipow(begin_x, 5)*begin_dx + -6.17382e-08 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -0.00211265 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + 0.584062 *begin_y*lens_ipow(begin_dx, 4)*begin_dy+0.0f;
    domega2_dx0[0][1] =  + -0.221156 *begin_dx*begin_dy + -0.00521228 *begin_x*begin_dy + -8.83908e-05 *begin_x*begin_y + -0.00401778 *begin_y*begin_dx + 1.65093e-07 *begin_x*lens_ipow(begin_y, 3) + -0.000461499 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -8.45617e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.0159434 *begin_y*lens_ipow(begin_dx, 3) + -1.38822e-05 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.000316542 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -1.23476e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + 26.7011 *lens_ipow(begin_dx, 5)*begin_dy + 0.584062 *begin_x*lens_ipow(begin_dx, 4)*begin_dy+0.0f;
    domega2_dx0[1][0] =  + 0.00112035 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 0.0535956 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.865866 *begin_x*lens_ipow(begin_dy, 3) + -0.00124549 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 153.009 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -0.0596003 *begin_y*begin_dx*lens_ipow(begin_lambda, 3) + 0.0511834 *begin_x*begin_dy*lens_ipow(begin_lambda, 4) + 2.37088 *begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + -401.059 *begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -1.13655e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + -9.59477 *begin_x*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 5)+0.0f;
    domega2_dx0[1][1] =  + -0.0076263  + -0.00993046 *begin_lambda + 0.0091384 *begin_y*begin_dy + 0.24853 *lens_ipow(begin_dy, 2) + 0.00753626 *lens_ipow(begin_lambda, 2) + 8.40836e-05 *lens_ipow(begin_y, 2) + 0.000560175 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 1.3046 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.0535956 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -1.68197e-07 *lens_ipow(begin_y, 4) + 0.000842462 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -1.45168 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.000622746 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + -0.0596003 *begin_x*begin_dx*lens_ipow(begin_lambda, 3) + -0.489688 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + -1.42069e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)+0.0f;
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
  out[4] =  + 0.289339  + 0.830007 *begin_lambda + -0.0110328 *begin_y*begin_dy + -0.0226925 *begin_x*begin_dx + -9.31306e-05 *lens_ipow(begin_y, 2) + -0.409063 *lens_ipow(begin_dy, 2) + -0.000221868 *lens_ipow(begin_x, 2) + -0.568149 *lens_ipow(begin_dx, 2) + -1.13829 *lens_ipow(begin_lambda, 2) + 0.550138 *lens_ipow(begin_lambda, 3) + 72.6792 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00290532 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.15533 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -9.59772e-05 *lens_ipow(begin_x, 3)*begin_dx + 2.95483 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -8.57246e-07 *lens_ipow(begin_x, 4) + 0.0287314 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.183598 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + 0.00670806 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -5.06444e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -14.2289 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000887711 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 2) + 2.09193e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -485.97 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -5990.27 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 0.000167391 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 0.062366 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4)*begin_dy + -8.21482e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6);
else
  out[4] = 0.0f;
} break;
