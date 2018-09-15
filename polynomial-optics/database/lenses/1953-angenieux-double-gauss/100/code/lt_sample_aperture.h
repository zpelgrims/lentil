case angenieux_double_gauss_1953_100mm:
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
       + 53.368 *begin_dx + 0.154173 *begin_x + 13.3439 *begin_dx*begin_lambda + 0.26366 *begin_x*begin_lambda + -9.18561 *begin_dx*lens_ipow(begin_lambda, 2) + -33.2685 *begin_dx*lens_ipow(begin_dy, 2) + -33.5163 *lens_ipow(begin_dx, 3) + -0.022706 *begin_y*begin_dx*begin_dy + -0.180979 *begin_x*lens_ipow(begin_lambda, 2) + -0.173349 *begin_x*lens_ipow(begin_dy, 2) + -0.19424 *begin_x*lens_ipow(begin_dx, 2) + -0.000101075 *begin_x*lens_ipow(begin_y, 2) + -9.81721e-05 *lens_ipow(begin_x, 3) + 0.00133304 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.00195819 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 14.3695 *begin_dx*lens_ipow(begin_dy, 4) + 29.4852 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 15.7155 *lens_ipow(begin_dx, 5) + 0.00433777 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.266565 *begin_x*lens_ipow(begin_dy, 4) + 0.471407 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.27174 *begin_x*lens_ipow(begin_dx, 4) + 0.0125253 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000129187 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -9.4332e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.011584 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.0105079 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -6.35762e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4),
       + 53.3126 *begin_dy + 0.15413 *begin_y + 13.6022 *begin_dy*begin_lambda + 0.263764 *begin_y*begin_lambda + -9.40104 *begin_dy*lens_ipow(begin_lambda, 2) + -33.8532 *lens_ipow(begin_dy, 3) + -33.3318 *lens_ipow(begin_dx, 2)*begin_dy + -0.181196 *begin_y*lens_ipow(begin_lambda, 2) + -0.193336 *begin_y*lens_ipow(begin_dy, 2) + -0.17203 *begin_y*lens_ipow(begin_dx, 2) + -9.83005e-05 *lens_ipow(begin_y, 3) + -0.0225367 *begin_x*begin_dx*begin_dy + 0.000554925 *lens_ipow(begin_x, 2)*begin_dy + -0.000101 *lens_ipow(begin_x, 2)*begin_y + 0.00195325 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 16.8773 *lens_ipow(begin_dy, 5) + 29.9523 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 14.5414 *lens_ipow(begin_dx, 4)*begin_dy + 0.267088 *begin_y*lens_ipow(begin_dy, 4) + 0.468686 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.260471 *begin_y*lens_ipow(begin_dx, 4) + -9.30644e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.0126359 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00449158 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.0119848 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.000235998 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -0.0213871 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5)*begin_lambda + -6.24227e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)
    };
    const float delta_ap[] = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =  + 53.368  + 13.3439 *begin_lambda + -9.18561 *lens_ipow(begin_lambda, 2) + -33.2685 *lens_ipow(begin_dy, 2) + -100.549 *lens_ipow(begin_dx, 2) + -0.022706 *begin_y*begin_dy + -0.38848 *begin_x*begin_dx + 0.00133304 *lens_ipow(begin_y, 2)*begin_lambda + 0.00195819 *lens_ipow(begin_x, 2)*begin_lambda + 14.3695 *lens_ipow(begin_dy, 4) + 88.4555 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 78.5776 *lens_ipow(begin_dx, 4) + 0.00433777 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.942814 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 1.08696 *begin_x*lens_ipow(begin_dx, 3) + 0.0250505 *begin_x*begin_y*begin_dx*begin_dy + -0.000129187 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.000188664 *lens_ipow(begin_x, 3)*begin_dx + -0.011584 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0315237 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0[0][1] =  + -66.537 *begin_dx*begin_dy + -0.022706 *begin_y*begin_dx + -0.346699 *begin_x*begin_dy + 57.4779 *begin_dx*lens_ipow(begin_dy, 3) + 58.9703 *lens_ipow(begin_dx, 3)*begin_dy + 0.00867553 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.06626 *begin_x*lens_ipow(begin_dy, 3) + 0.942814 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.0125253 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -0.000129187 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -0.0231681 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0[1][0] =  + -66.6635 *begin_dx*begin_dy + -0.34406 *begin_y*begin_dx + -0.0225367 *begin_x*begin_dy + 59.9045 *begin_dx*lens_ipow(begin_dy, 3) + 58.1656 *lens_ipow(begin_dx, 3)*begin_dy + 0.937373 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 1.04189 *begin_y*lens_ipow(begin_dx, 3) + 0.0126359 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.00898316 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.0239696 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -0.000235998 *begin_x*lens_ipow(begin_y, 2)*begin_dy*begin_lambda+0.0f;
    dx1_domega0[1][1] =  + 53.3126  + 13.6022 *begin_lambda + -9.40104 *lens_ipow(begin_lambda, 2) + -101.56 *lens_ipow(begin_dy, 2) + -33.3318 *lens_ipow(begin_dx, 2) + -0.386671 *begin_y*begin_dy + -0.0225367 *begin_x*begin_dx + 0.000554925 *lens_ipow(begin_x, 2) + 0.00195325 *lens_ipow(begin_y, 2)*begin_lambda + 84.3866 *lens_ipow(begin_dy, 4) + 89.8568 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 14.5414 *lens_ipow(begin_dx, 4) + 1.06835 *begin_y*lens_ipow(begin_dy, 3) + 0.937373 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000186129 *lens_ipow(begin_y, 3)*begin_dy + 0.0252718 *begin_x*begin_y*begin_dx*begin_dy + 0.00449158 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.0119848 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.000235998 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.106935 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda+0.0f;
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
    out[0] =  + 99.6029 *begin_dx + -0.604972 *begin_x + 0.589799 *begin_x*begin_lambda + -46.567 *begin_dx*lens_ipow(begin_dy, 2) + -50.4391 *lens_ipow(begin_dx, 3) + -0.421661 *begin_x*lens_ipow(begin_lambda, 2) + 0.245533 *begin_x*lens_ipow(begin_dy, 2) + 0.00402799 *begin_x*begin_y*begin_dy + -0.000324364 *begin_x*lens_ipow(begin_y, 2) + -0.000239554 *lens_ipow(begin_x, 3) + 3.83366 *lens_ipow(begin_dx, 3)*begin_lambda + 0.00581756 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.22487 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.000138208 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0166051 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 28.4313 *begin_dx*lens_ipow(begin_dy, 4) + 38.1492 *lens_ipow(begin_dx, 5) + 1.49328 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 2.50821 *begin_x*lens_ipow(begin_dx, 4) + 111.655 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 3.14073 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 4.17814 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.117107 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.109461 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4) + 0.154442 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.187102 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.168687 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5) + -7.85462e-05 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 5);
    out[1] =  + 99.5754 *begin_dy + -0.61982 *begin_y + 0.62911 *begin_y*begin_lambda + -49.2403 *lens_ipow(begin_dy, 3) + -41.4444 *lens_ipow(begin_dx, 2)*begin_dy + -0.450479 *begin_y*lens_ipow(begin_lambda, 2) + 0.245367 *begin_y*lens_ipow(begin_dx, 2) + -0.000230545 *lens_ipow(begin_y, 3) + 0.117489 *begin_x*begin_dx*begin_dy + 0.003996 *begin_x*begin_y*begin_dx + -0.000249977 *lens_ipow(begin_x, 2)*begin_y + 0.295257 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0167013 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.00544709 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 2.2613 *begin_y*lens_ipow(begin_dy, 4) + 2.14347 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 106.048 *lens_ipow(begin_dy, 5)*begin_lambda + 0.112315 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 350.037 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 0.165826 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5) + 0.196342 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 2.7358 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 11.3545 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 0.278571 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 6.22855e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -8.60707e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -5.3217e-05 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 4) + -369.689 *lens_ipow(begin_dy, 7)*lens_ipow(begin_lambda, 3);
    out[2] =  + -0.612086 *begin_dx + -0.00634092 *begin_x + 0.00787218 *begin_dx*begin_lambda + -0.00352711 *begin_x*begin_lambda + 0.299727 *lens_ipow(begin_dx, 3) + 0.00246374 *begin_x*lens_ipow(begin_lambda, 2) + -0.000770014 *begin_x*lens_ipow(begin_dy, 2) + -1.92831e-05 *begin_x*begin_y*begin_dy + 1.76487e-06 *begin_x*lens_ipow(begin_y, 2) + -3.58077e-05 *lens_ipow(begin_x, 2)*begin_dx + 1.72823e-06 *lens_ipow(begin_x, 3) + 0.552485 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.464277 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.255015 *lens_ipow(begin_dx, 5) + 0.0001025 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 6.22315e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 1.38708e-06 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 0.000144289 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 4.98087e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -0.462349 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 0.000299233 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.00535266 *begin_x*lens_ipow(begin_dy, 6) + -0.0326943 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -0.0182562 *begin_x*lens_ipow(begin_dx, 6) + -0.0224582 *begin_y*lens_ipow(begin_dx, 5)*begin_dy*begin_lambda + 0.00230149 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 2.3277e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4)*begin_lambda + 4.94377e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2);
    out[3] =  + -0.616182 *begin_dy + -0.00634096 *begin_y + 0.00958197 *begin_dy*begin_lambda + -0.00346076 *begin_y*begin_lambda + 0.323351 *lens_ipow(begin_dy, 3) + 0.42883 *lens_ipow(begin_dx, 2)*begin_dy + 0.00237198 *begin_y*lens_ipow(begin_lambda, 2) + 1.71134e-06 *lens_ipow(begin_y, 3) + 0.00190851 *begin_x*begin_dx*begin_dy + -2.95858e-05 *begin_x*begin_y*begin_dx + 1.79372e-06 *lens_ipow(begin_x, 2)*begin_y + -0.286451 *lens_ipow(begin_dy, 5) + -0.669471 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.347893 *lens_ipow(begin_dx, 4)*begin_dy + -0.0423527 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -7.63639e-08 *lens_ipow(begin_y, 4)*begin_dy + -8.218e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.106211 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 9.69185e-05 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 3.78872e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -0.0726444 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -0.0490638 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.0400295 *begin_y*lens_ipow(begin_dy, 6)*begin_lambda + 8.26533e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.0153174 *begin_y*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 4) + -0.0681183 *begin_x*begin_dx*lens_ipow(begin_dy, 7) + -0.336643 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + 2.96913e-09 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda;
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
    domega2_dx0[0][0] =  + -0.00634092  + -0.00352711 *begin_lambda + 0.00246374 *lens_ipow(begin_lambda, 2) + -0.000770014 *lens_ipow(begin_dy, 2) + -1.92831e-05 *begin_y*begin_dy + 1.76487e-06 *lens_ipow(begin_y, 2) + -7.16153e-05 *begin_x*begin_dx + 5.18469e-06 *lens_ipow(begin_x, 2) + 0.000288578 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 9.96175e-06 *begin_x*begin_y*begin_dx*begin_dy + 0.000598465 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + -0.00535266 *lens_ipow(begin_dy, 6) + -0.0326943 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -0.0182562 *lens_ipow(begin_dx, 6) + 0.00230149 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 6.9831e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*begin_lambda + 1.48313e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0[0][1] =  + -1.92831e-05 *begin_x*begin_dy + 3.52973e-06 *begin_x*begin_y + 0.000204999 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.000124463 *begin_y*lens_ipow(begin_dx, 3) + 4.16125e-06 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 4.98087e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.0224582 *lens_ipow(begin_dx, 5)*begin_dy*begin_lambda + 0.00230149 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 1.97751e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0[1][0] =  + 0.00190851 *begin_dx*begin_dy + -2.95858e-05 *begin_y*begin_dx + 3.58744e-06 *begin_x*begin_y + -1.6436e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 9.69185e-05 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 3.78872e-06 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 1.65307e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -0.0681183 *begin_dx*lens_ipow(begin_dy, 7) + -0.336643 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0[1][1] =  + -0.00634096  + -0.00346076 *begin_lambda + 0.00237198 *lens_ipow(begin_lambda, 2) + 5.13401e-06 *lens_ipow(begin_y, 2) + -2.95858e-05 *begin_x*begin_dx + 1.79372e-06 *lens_ipow(begin_x, 2) + -0.0423527 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -3.05455e-07 *lens_ipow(begin_y, 3)*begin_dy + -1.6436e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.106211 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 9.69185e-05 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + 7.57743e-06 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + -0.0726444 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -0.0490638 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.0400295 *lens_ipow(begin_dy, 6)*begin_lambda + 1.65307e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 0.0153174 *lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 4) + 1.78148e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda+0.0f;
    float invJ[2][2];
    const float invdet = 1.0f/(domega2_dx0[0][0]*domega2_dx0[1][1] - domega2_dx0[0][1]*domega2_dx0[1][0]);
    invJ[0][0] =  domega2_dx0[1][1]*invdet;
    invJ[1][1] =  domega2_dx0[0][0]*invdet;
    invJ[0][1] = -domega2_dx0[0][1]*invdet;
    invJ[1][0] = -domega2_dx0[1][0]*invdet;
    for(int i=0;i<2;i++)
    {
      x += 0.72 * invJ[0][i] * delta_out[i];
      y += 0.72 * invJ[1][i] * delta_out[i];
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
  out[4] =  + 0.237617  + 0.856098 *begin_lambda + -1.17094 *lens_ipow(begin_lambda, 2) + 0.565231 *lens_ipow(begin_lambda, 3) + -0.165059 *lens_ipow(begin_dy, 4) + -0.166786 *lens_ipow(begin_dx, 4) + -0.00286447 *begin_y*lens_ipow(begin_dy, 3) + -0.00541464 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -5.31436e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -3.91207e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0042972 *begin_x*lens_ipow(begin_dx, 3) + -8.43545e-05 *begin_x*begin_y*begin_dx*begin_dy + -4.11736e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.65244 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.00896813 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.000102523 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 1.23659 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000426865 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.000574858 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -0.506568 *lens_ipow(begin_dy, 6)*begin_lambda + -0.499987 *lens_ipow(begin_dx, 6)*begin_lambda + -0.0233181 *begin_y*lens_ipow(begin_dy, 5)*begin_lambda + -0.00110739 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -9.23433e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*begin_lambda + -1.99073e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.00111682 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.052724 *begin_x*lens_ipow(begin_dx, 7)*begin_lambda + -0.0138711 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4);
else
  out[4] = 0.0f;
} break;
