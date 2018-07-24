//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
#ifndef DEBUG_LOG
#define DEBUG_LOG
#endif
float view[3] =
{
  scene_x,
  scene_y,
  scene_z + lens_outer_pupil_curvature_radius
};
normalise(view);
int error = 0;
if(1 || view[2] >= lens_field_of_view)
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
       + 53.3813 *begin_dx + 0.154777 *begin_x + 0.261528 *begin_x*begin_lambda + 13.3025 *begin_dx*begin_lambda + -0.0224505 *begin_y*begin_dx*begin_dy + -33.5149 *lens_ipow(begin_dx, 3) + -0.179304 *begin_x*lens_ipow(begin_lambda, 2) + -33.3313 *begin_dx*lens_ipow(begin_dy, 2) + -0.000100913 *begin_x*lens_ipow(begin_y, 2) + -9.81196e-05 *lens_ipow(begin_x, 3) + -0.172202 *begin_x*lens_ipow(begin_dy, 2) + -0.194791 *begin_x*lens_ipow(begin_dx, 2) + -9.15742 *begin_dx*lens_ipow(begin_lambda, 2) + 0.00197297 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.00135443 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.0128352 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.272568 *begin_x*lens_ipow(begin_dx, 4) + 15.7349 *lens_ipow(begin_dx, 5) + 0.477671 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 14.5467 *begin_dx*lens_ipow(begin_dy, 4) + 0.262767 *begin_x*lens_ipow(begin_dy, 4) + 0.00455317 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -9.21041e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 29.958 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.000218375 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + -0.0117472 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.0109065 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -6.45965e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4),
       + 0.154573 *begin_y + 53.3816 *begin_dy + 13.2961 *begin_dy*begin_lambda + 0.262502 *begin_y*begin_lambda + -0.172232 *begin_y*lens_ipow(begin_dx, 2) + -0.194729 *begin_y*lens_ipow(begin_dy, 2) + -0.0226905 *begin_x*begin_dx*begin_dy + -33.3032 *lens_ipow(begin_dx, 2)*begin_dy + -0.180011 *begin_y*lens_ipow(begin_lambda, 2) + -0.000101256 *lens_ipow(begin_x, 2)*begin_y + -9.14292 *begin_dy*lens_ipow(begin_lambda, 2) + -9.87738e-05 *lens_ipow(begin_y, 3) + -33.5367 *lens_ipow(begin_dy, 3) + 0.00136169 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.00197757 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.00437516 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.000123302 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 29.6641 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.262752 *begin_y*lens_ipow(begin_dx, 4) + 15.8211 *lens_ipow(begin_dy, 5) + 0.0125992 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.27136 *begin_y*lens_ipow(begin_dy, 4) + 0.468323 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 14.5036 *lens_ipow(begin_dx, 4)*begin_dy + -8.73164e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.0115973 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.0109593 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -6.01224e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)
    };
    const float delta_ap[] = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =  + 53.3813  + 13.3025 *begin_lambda + -0.0224505 *begin_y*begin_dy + -100.545 *lens_ipow(begin_dx, 2) + -33.3313 *lens_ipow(begin_dy, 2) + -0.389581 *begin_x*begin_dx + -9.15742 *lens_ipow(begin_lambda, 2) + 0.00197297 *lens_ipow(begin_x, 2)*begin_lambda + 0.00135443 *lens_ipow(begin_y, 2)*begin_lambda + 0.0256703 *begin_x*begin_y*begin_dx*begin_dy + 1.09027 *begin_x*lens_ipow(begin_dx, 3) + 78.6746 *lens_ipow(begin_dx, 4) + 0.955343 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 14.5467 *lens_ipow(begin_dy, 4) + 0.00455317 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000184208 *lens_ipow(begin_x, 3)*begin_dx + 89.8741 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000218375 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + -0.0117472 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0327196 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0[0][1] =  + -0.0224505 *begin_y*begin_dx + -66.6625 *begin_dx*begin_dy + -0.344403 *begin_x*begin_dy + 0.0128352 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 0.955343 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 58.1867 *begin_dx*lens_ipow(begin_dy, 3) + 1.05107 *begin_x*lens_ipow(begin_dy, 3) + 0.00910634 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 59.916 *lens_ipow(begin_dx, 3)*begin_dy + -0.000218375 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + -0.0234945 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0[1][0] =  + -0.344465 *begin_y*begin_dx + -0.0226905 *begin_x*begin_dy + -66.6064 *begin_dx*begin_dy + 0.00875033 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.000123302 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 59.3282 *begin_dx*lens_ipow(begin_dy, 3) + 1.05101 *begin_y*lens_ipow(begin_dx, 3) + 0.0125992 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.936647 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 58.0145 *lens_ipow(begin_dx, 3)*begin_dy + -0.0231946 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0[1][1] =  + 53.3816  + 13.2961 *begin_lambda + -0.389458 *begin_y*begin_dy + -0.0226905 *begin_x*begin_dx + -33.3032 *lens_ipow(begin_dx, 2) + -9.14292 *lens_ipow(begin_lambda, 2) + -100.61 *lens_ipow(begin_dy, 2) + 0.00136169 *lens_ipow(begin_x, 2)*begin_lambda + 0.00197757 *lens_ipow(begin_y, 2)*begin_lambda + 0.00437516 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.000123302 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 88.9923 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 79.1057 *lens_ipow(begin_dy, 4) + 0.0251984 *begin_x*begin_y*begin_dx*begin_dy + 1.08544 *begin_y*lens_ipow(begin_dy, 3) + 0.936647 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 14.5036 *lens_ipow(begin_dx, 4) + -0.000174633 *lens_ipow(begin_y, 3)*begin_dy + -0.0115973 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.032878 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
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
    out[0] =  + 99.0482 *begin_dx + -0.606384 *begin_x + 0.593166 *begin_x*begin_lambda + 1.06088 *begin_dx*begin_lambda + 0.00392189 *begin_x*begin_y*begin_dy + -48.5105 *lens_ipow(begin_dx, 3) + -0.422081 *begin_x*lens_ipow(begin_lambda, 2) + -46.9432 *begin_dx*lens_ipow(begin_dy, 2) + -0.000314401 *begin_x*lens_ipow(begin_y, 2) + -0.000239753 *lens_ipow(begin_x, 3) + 0.2425 *begin_x*lens_ipow(begin_dy, 2) + 0.00318953 *lens_ipow(begin_y, 2)*begin_dx + 0.211985 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.000116327 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0162928 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 2.53345 *begin_x*lens_ipow(begin_dx, 4) + 37.991 *lens_ipow(begin_dx, 5) + 29.7718 *begin_dx*lens_ipow(begin_dy, 4) + 4.25018 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.117375 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 3.05549 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 114.385 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 2.70561 *begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.195688 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.174217 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5) + 0.199023 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + 0.26768 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -7.90581e-05 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 5);
    out[1] =  + -0.615568 *begin_y + 99.0341 *begin_dy + 1.07734 *begin_dy*begin_lambda + 0.613505 *begin_y*begin_lambda + 0.240035 *begin_y*lens_ipow(begin_dx, 2) + 0.0039041 *begin_x*begin_y*begin_dx + -46.8003 *lens_ipow(begin_dx, 2)*begin_dy + -0.432397 *begin_y*lens_ipow(begin_lambda, 2) + -0.000241589 *lens_ipow(begin_x, 2)*begin_y + -0.000233404 *lens_ipow(begin_y, 3) + 0.00328022 *lens_ipow(begin_x, 2)*begin_dy + -48.6925 *lens_ipow(begin_dy, 3) + 0.202037 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0163519 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 1.49664 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 38.9169 *lens_ipow(begin_dy, 5) + 2.56474 *begin_y*lens_ipow(begin_dy, 4) + 28.984 *lens_ipow(begin_dx, 4)*begin_dy + 115.638 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 4.36412 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 3.06362 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.117856 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.131711 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.113267 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*begin_dy + 0.175126 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5) + 0.203267 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -8.12667e-05 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 5) + -3.84957e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7);
    out[2] =  + -0.610878 *begin_dx + -0.00635209 *begin_x + -0.00344005 *begin_x*begin_lambda + 0.00725679 *begin_dx*begin_lambda + -2.99306e-05 *begin_x*begin_y*begin_dy + -3.98322e-05 *lens_ipow(begin_x, 2)*begin_dx + 0.280311 *lens_ipow(begin_dx, 3) + 0.0023866 *begin_x*lens_ipow(begin_lambda, 2) + 1.63786e-06 *begin_x*lens_ipow(begin_y, 2) + 1.72274e-06 *lens_ipow(begin_x, 3) + -0.00104249 *begin_x*lens_ipow(begin_dy, 2) + 0.555934 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.00356735 *begin_x*lens_ipow(begin_dx, 4) + -0.182417 *lens_ipow(begin_dx, 5) + -0.49354 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.000103975 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 6.70325e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.000122482 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 6.3498e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000189896 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 2.68629e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.148049 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.000339661 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.000397502 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 1.42466e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 3.73663e-09 *lens_ipow(begin_y, 5)*begin_dx*begin_dy + 4.5138e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2) + -8.72709e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_lambda;
    out[3] =  + -0.00637173 *begin_y + -0.624157 *begin_dy + 0.0456478 *begin_dy*begin_lambda + -0.00340738 *begin_y*begin_lambda + -0.00177599 *begin_y*lens_ipow(begin_dx, 2) + -3.38122e-05 *lens_ipow(begin_y, 2)*begin_dy + 0.00185104 *begin_x*begin_dx*begin_dy + -2.87514e-05 *begin_x*begin_y*begin_dx + 0.417591 *lens_ipow(begin_dx, 2)*begin_dy + 0.00236802 *begin_y*lens_ipow(begin_lambda, 2) + 1.82639e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0324662 *begin_dy*lens_ipow(begin_lambda, 2) + 1.70422e-06 *lens_ipow(begin_y, 3) + 0.305991 *lens_ipow(begin_dy, 3) + 2.55092e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.629532 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.243999 *lens_ipow(begin_dy, 5) + 5.60702e-05 *begin_x*begin_y*lens_ipow(begin_dx, 3) + 0.000178177 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.000149917 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.347258 *lens_ipow(begin_dx, 4)*begin_dy + -4.87916e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 1.42628e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + -0.0394256 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.0145111 *begin_y*lens_ipow(begin_dy, 6) + -1.48971e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -0.36068 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5) + 0.00194489 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 6)*begin_dy;
    float pred_out_cs[7] = {0.0f};
    lens_sphereToCs(out, out+2, pred_out_cs, pred_out_cs+3, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    float view[3] =
    {
      scene_x - pred_out_cs[0],
      scene_y - pred_out_cs[1],
      scene_z - pred_out_cs[2]
    };
    normalise(view);
    float out_new[5];
    lens_csToSphere(pred_out_cs, view, out_new, out_new+2, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    const float delta_out[] = {out_new[2] - out[2], out_new[3] - out[3]};
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    float domega2_dx0[2][2];
    domega2_dx0[0][0] =  + -0.00635209  + -0.00344005 *begin_lambda + -2.99306e-05 *begin_y*begin_dy + -7.96644e-05 *begin_x*begin_dx + 0.0023866 *lens_ipow(begin_lambda, 2) + 1.63786e-06 *lens_ipow(begin_y, 2) + 5.16823e-06 *lens_ipow(begin_x, 2) + -0.00104249 *lens_ipow(begin_dy, 2) + -0.00356735 *lens_ipow(begin_dx, 4) + 0.000122482 *begin_y*lens_ipow(begin_dy, 3) + 1.26996e-05 *begin_x*begin_y*begin_dx*begin_dy + 0.000379792 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 2.68629e-06 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.000339661 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.000795005 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + 4.27397e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.000135414 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2) + -2.61813e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_lambda+0.0f;
    domega2_dx0[0][1] =  + -2.99306e-05 *begin_x*begin_dy + 3.27571e-06 *begin_x*begin_y + 0.000207951 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.000134065 *begin_y*lens_ipow(begin_dx, 3) + 0.000122482 *begin_x*lens_ipow(begin_dy, 3) + 6.3498e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 5.37258e-06 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.000339661 *begin_x*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 2.84932e-08 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2) + 1.86832e-08 *lens_ipow(begin_y, 4)*begin_dx*begin_dy + -1.74542e-07 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 4)*begin_lambda+0.0f;
    domega2_dx0[1][0] =  + 0.00185104 *begin_dx*begin_dy + -2.87514e-05 *begin_y*begin_dx + 3.65279e-06 *begin_x*begin_y + 2.55092e-06 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 5.60702e-05 *begin_y*lens_ipow(begin_dx, 3) + -9.75831e-08 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -2.97941e-05 *begin_x*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -0.36068 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5) + 0.00388978 *begin_x*lens_ipow(begin_dx, 6)*begin_dy+0.0f;
    domega2_dx0[1][1] =  + -0.00637173  + -0.00340738 *begin_lambda + -0.00177599 *lens_ipow(begin_dx, 2) + -6.76243e-05 *begin_y*begin_dy + -2.87514e-05 *begin_x*begin_dx + 0.00236802 *lens_ipow(begin_lambda, 2) + 1.82639e-06 *lens_ipow(begin_x, 2) + 5.11265e-06 *lens_ipow(begin_y, 2) + 5.10184e-06 *begin_x*begin_y*begin_dx*begin_dy + 5.60702e-05 *begin_x*lens_ipow(begin_dx, 3) + 0.000356355 *begin_y*lens_ipow(begin_dy, 3) + 0.000299834 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -9.75831e-08 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 4.27884e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.0394256 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.0145111 *lens_ipow(begin_dy, 6) + -1.48971e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda+0.0f;
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
    DEBUG_LOG;
    // reset error code for first few iterations.
    if(k<10) error = 0;
  }
}
else
  error = 128;
if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.238449  + 0.854223 *begin_lambda + -1.75589e-06 *lens_ipow(begin_x, 2) + -1.17022 *lens_ipow(begin_lambda, 2) + 0.566184 *lens_ipow(begin_lambda, 3) + -0.218043 *lens_ipow(begin_dx, 4) + -0.00500031 *begin_y*lens_ipow(begin_dy, 3) + -0.00502322 *begin_x*lens_ipow(begin_dx, 3) + -0.179247 *lens_ipow(begin_dy, 4) + -7.55927e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -9.75229e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000122169 *begin_x*begin_y*begin_dx*begin_dy + -0.00976566 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.0940186 *lens_ipow(begin_dy, 4)*begin_lambda + -6.36589e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.00859308 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -1.44888 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.02664 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000138437 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + -0.00143299 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 6) + -0.000825338 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 6) + -7.97573e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.00316514 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -0.343132 *lens_ipow(begin_dx, 6)*lens_ipow(begin_lambda, 3) + -0.00508804 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0123271 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 0.117385 *begin_x*begin_dx*lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 3) + -0.000177164 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 7)*begin_lambda;
else
  out[4] = 0.0f;
