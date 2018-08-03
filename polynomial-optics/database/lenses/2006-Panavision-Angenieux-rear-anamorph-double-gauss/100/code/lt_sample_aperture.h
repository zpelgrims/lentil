case Panavision_Angenieux_rear_anamorph_double_gauss_2006_100mm:
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
       + 74.0947 *begin_dx + 0.818807 *begin_x + 17.151 *begin_dx*begin_lambda + -11.7868 *begin_dx*lens_ipow(begin_lambda, 2) + -43.368 *begin_dx*lens_ipow(begin_dy, 2) + -53.8698 *lens_ipow(begin_dx, 3) + -0.0734648 *begin_y*begin_dx*begin_dy + 0.00125607 *lens_ipow(begin_y, 2)*begin_dx + 0.221262 *begin_x*lens_ipow(begin_lambda, 2) + -0.275061 *begin_x*lens_ipow(begin_dy, 2) + -0.59124 *begin_x*lens_ipow(begin_dx, 2) + -5.12867e-05 *begin_x*lens_ipow(begin_y, 2) + 0.0183043 *lens_ipow(begin_x, 2)*begin_dx + 0.000324258 *lens_ipow(begin_x, 3) + -0.216147 *begin_x*lens_ipow(begin_lambda, 3) + 52.2983 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.469337 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 1.12763 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 5.7398 *begin_x*lens_ipow(begin_dx, 4) + 0.010041 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.426193 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.0118726 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.000157055 *lens_ipow(begin_x, 4)*begin_dx + 8.47955e-07 *lens_ipow(begin_x, 5) + -0.280172 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + -0.0141558 *begin_x*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 7.6213e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -0.0239262 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 2),
       + 55.4062 *begin_dy + 0.217599 *begin_y + 13.4827 *begin_dy*begin_lambda + 0.116672 *begin_y*begin_lambda + -9.17618 *begin_dy*lens_ipow(begin_lambda, 2) + -33.3432 *lens_ipow(begin_dy, 3) + -36.9199 *lens_ipow(begin_dx, 2)*begin_dy + -0.189918 *begin_y*lens_ipow(begin_dy, 2) + -0.193803 *begin_y*lens_ipow(begin_dx, 2) + -0.00412872 *lens_ipow(begin_y, 2)*begin_dy + -0.000181543 *lens_ipow(begin_y, 3) + -0.133143 *begin_x*begin_dx*begin_dy + -2.25484e-05 *lens_ipow(begin_x, 2)*begin_y + -0.0800835 *begin_y*lens_ipow(begin_lambda, 3) + -1.00074 *begin_y*lens_ipow(begin_dy, 4) + -2.84384e-05 *lens_ipow(begin_y, 4)*begin_dy + -5.0815e-07 *lens_ipow(begin_y, 5) + -1.10999 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.443053 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.864555 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.639929 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.000786098 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 2.10186e-07 *lens_ipow(begin_y, 5)*begin_lambda + 0.608564 *begin_y*lens_ipow(begin_dx, 6) + -0.0425061 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + 2.22528e-09 *begin_x*lens_ipow(begin_y, 7)*begin_dx*lens_ipow(begin_dy, 2) + 7.82131e-11 *begin_x*lens_ipow(begin_y, 8)*begin_dx*begin_dy + 7.08393e-13 *begin_x*lens_ipow(begin_y, 9)*begin_dx
    };
    const float delta_ap[] = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =  + 74.0947  + 17.151 *begin_lambda + -11.7868 *lens_ipow(begin_lambda, 2) + -43.368 *lens_ipow(begin_dy, 2) + -161.609 *lens_ipow(begin_dx, 2) + -0.0734648 *begin_y*begin_dy + 0.00125607 *lens_ipow(begin_y, 2) + -1.18248 *begin_x*begin_dx + 0.0183043 *lens_ipow(begin_x, 2) + 156.895 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.469337 *begin_y*lens_ipow(begin_dy, 3) + 2.25525 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 22.9592 *begin_x*lens_ipow(begin_dx, 3) + 0.010041 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 1.27858 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.0237452 *lens_ipow(begin_x, 3)*begin_dx + 0.000157055 *lens_ipow(begin_x, 4) + 7.6213e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -0.119631 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0[0][1] =  + -86.7359 *begin_dx*begin_dy + -0.0734648 *begin_y*begin_dx + -0.550122 *begin_x*begin_dy + 104.597 *lens_ipow(begin_dx, 3)*begin_dy + -1.40801 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 2.25525 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.0200819 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -1.12069 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + -0.0424673 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    dx1_domega0[1][0] =  + -73.8399 *begin_dx*begin_dy + -0.387606 *begin_y*begin_dx + -0.133143 *begin_x*begin_dy + -1.10999 *begin_x*lens_ipow(begin_dy, 3) + -1.32916 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.27986 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 3.65139 *begin_y*lens_ipow(begin_dx, 5) + 2.22528e-09 *begin_x*lens_ipow(begin_y, 7)*lens_ipow(begin_dy, 2) + 7.82131e-11 *begin_x*lens_ipow(begin_y, 8)*begin_dy + 7.08393e-13 *begin_x*lens_ipow(begin_y, 9)+0.0f;
    dx1_domega0[1][1] =  + 55.4062  + 13.4827 *begin_lambda + -9.17618 *lens_ipow(begin_lambda, 2) + -100.03 *lens_ipow(begin_dy, 2) + -36.9199 *lens_ipow(begin_dx, 2) + -0.379836 *begin_y*begin_dy + -0.00412872 *lens_ipow(begin_y, 2) + -0.133143 *begin_x*begin_dx + -4.00295 *begin_y*lens_ipow(begin_dy, 3) + -2.84384e-05 *lens_ipow(begin_y, 4) + -3.32997 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.443053 *begin_x*lens_ipow(begin_dx, 3) + 3.45822 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 1.27986 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.0015722 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -0.21253 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + 4.45056e-09 *begin_x*lens_ipow(begin_y, 7)*begin_dx*begin_dy + 7.82131e-11 *begin_x*lens_ipow(begin_y, 8)*begin_dx+0.0f;
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
    out[0] =  + 136.731 *begin_dx + 0.811708 *begin_x + 7.46914 *begin_dx*begin_lambda + 0.200088 *begin_x*begin_lambda + -5.66095 *begin_dx*lens_ipow(begin_lambda, 2) + -63.2176 *begin_dx*lens_ipow(begin_dy, 2) + -66.3093 *lens_ipow(begin_dx, 3) + 0.143035 *begin_y*begin_dx*begin_dy + 0.00497759 *lens_ipow(begin_y, 2)*begin_dx + -0.150089 *begin_x*lens_ipow(begin_lambda, 2) + 0.486484 *begin_x*lens_ipow(begin_dx, 2) + 0.00576804 *begin_x*begin_y*begin_dy + -0.000107763 *begin_x*lens_ipow(begin_y, 2) + 0.0558804 *lens_ipow(begin_x, 2)*begin_dx + 0.000713265 *lens_ipow(begin_x, 3) + 5.4741e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 33.1918 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -282.345 *lens_ipow(begin_dx, 5) + 0.350696 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.0317515 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.467541 *begin_x*lens_ipow(begin_dy, 4) + 0.0114558 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.54718e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -2.05197e-07 *begin_x*lens_ipow(begin_y, 4) + 0.852303 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.0297665 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.00041326 *lens_ipow(begin_x, 4)*begin_dx + 2.19934e-06 *lens_ipow(begin_x, 5);
    out[1] =  + 103.31 *begin_dy + -0.452377 *begin_y + 0.325564 *begin_y*begin_lambda + -44.7778 *lens_ipow(begin_dy, 3) + -0.223848 *begin_y*lens_ipow(begin_lambda, 2) + 0.398504 *begin_y*lens_ipow(begin_dy, 2) + -0.000423052 *lens_ipow(begin_y, 3) + 0.0136229 *begin_x*begin_y*begin_dx + 0.00204718 *lens_ipow(begin_x, 2)*begin_dy + -341.268 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 1.26785 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.000204971 *lens_ipow(begin_y, 3)*begin_lambda + 0.187807 *begin_x*begin_dx*begin_dy*begin_lambda + 21.539 *lens_ipow(begin_dy, 5) + 689.519 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -1.11564 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 1.08852 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.00783211 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -0.00312346 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.000115881 *lens_ipow(begin_y, 4)*begin_dy + -1.31559e-06 *lens_ipow(begin_y, 5) + -2.90606 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.81994 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 7.51068e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -0.0253263 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -444.443 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 0.805223 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.642069 *begin_y*lens_ipow(begin_dx, 6);
    out[2] =  + -0.868809 *begin_dx + -0.0124702 *begin_x + 0.112677 *begin_dx*begin_lambda + 9.62389e-05 *begin_x*begin_lambda + -0.0791974 *begin_dx*lens_ipow(begin_lambda, 2) + 0.387579 *lens_ipow(begin_dx, 3) + 0.000439633 *begin_y*begin_dx*begin_dy + -0.000819149 *begin_x*lens_ipow(begin_dy, 2) + -0.00349068 *begin_x*lens_ipow(begin_dx, 2) + -1.49117e-05 *begin_x*begin_y*begin_dy + 1.2668e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000365165 *lens_ipow(begin_x, 2)*begin_dx + -3.77268e-06 *lens_ipow(begin_x, 3) + 0.721032 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -4.13888e-07 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.945678 *lens_ipow(begin_dx, 5) + -3.51589e-08 *lens_ipow(begin_y, 4)*begin_dx + -0.034531 *begin_x*lens_ipow(begin_dx, 4) + 1.01221e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.50645e-09 *lens_ipow(begin_x, 5) + -2.28083 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 2.00291 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -0.344149 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 2.55668e-07 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2) + 0.00133549 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)*begin_lambda + -7.42427e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -3.75352e-10 *begin_x*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3) + 4.99752e-05 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 8);
    out[3] =  + -0.646013 *begin_dy + -0.00570658 *begin_y + 0.0451894 *begin_dy*begin_lambda + -0.00839497 *begin_y*begin_lambda + -0.0328575 *begin_dy*lens_ipow(begin_lambda, 2) + 0.312562 *lens_ipow(begin_dy, 3) + 0.484346 *lens_ipow(begin_dx, 2)*begin_dy + 0.0126182 *begin_y*lens_ipow(begin_lambda, 2) + -0.00372193 *begin_y*lens_ipow(begin_dx, 2) + 2.2413e-06 *lens_ipow(begin_y, 3) + 0.00561152 *begin_x*begin_dx*begin_dy + -0.000114837 *begin_x*begin_y*begin_dx + 1.85609e-05 *lens_ipow(begin_x, 2)*begin_dy + -0.00653246 *begin_y*lens_ipow(begin_lambda, 3) + -6.17861e-07 *lens_ipow(begin_y, 3)*begin_lambda + -0.0974948 *lens_ipow(begin_dy, 5) + 0.000344713 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 2.32861e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 6.46022e-07 *lens_ipow(begin_y, 4)*begin_dy + 6.55257e-09 *lens_ipow(begin_y, 5) + 0.00395695 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + 5.75003e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -1.97968e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -1.96206 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -0.624036 *lens_ipow(begin_dx, 6)*begin_dy + 3.26992e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 4)*begin_dy + -0.00018422 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 2.84587e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy;
    float pred_out_cs[7] = {0.0f};
    lens_sphereToCs(out, out+2, pred_out_cs, pred_out_cs+3, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius);
    float view[3] =
    {
      scene_x - pred_out_cs[0],
      scene_y - pred_out_cs[1],
      scene_z - pred_out_cs[2]
    };
    normalise(view);
    float out_new[5];
    lens_csToSphere(pred_out_cs, view, out_new, out_new+2, - camera_data->lens_outer_pupil_curvature_radius, camera_data->lens_outer_pupil_curvature_radius);
    const float delta_out[] = {out_new[2] - out[2], out_new[3] - out[3]};
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    float domega2_dx0[2][2];
    domega2_dx0[0][0] =  + -0.0124702  + 9.62389e-05 *begin_lambda + -0.000819149 *lens_ipow(begin_dy, 2) + -0.00349068 *lens_ipow(begin_dx, 2) + -1.49117e-05 *begin_y*begin_dy + 1.2668e-06 *lens_ipow(begin_y, 2) + -0.000730331 *begin_x*begin_dx + -1.1318e-05 *lens_ipow(begin_x, 2) + -4.13888e-07 *lens_ipow(begin_y, 2)*begin_lambda + -0.034531 *lens_ipow(begin_dx, 4) + 3.03662e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -7.53227e-09 *lens_ipow(begin_x, 4) + -1.48485e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -3.75352e-10 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3) + 9.99504e-05 *begin_x*begin_dx*lens_ipow(begin_lambda, 8)+0.0f;
    domega2_dx0[0][1] =  + 0.000439633 *begin_dx*begin_dy + -1.49117e-05 *begin_x*begin_dy + 2.53361e-06 *begin_x*begin_y + -8.27777e-07 *begin_x*begin_y*begin_lambda + -1.40636e-07 *lens_ipow(begin_y, 3)*begin_dx + 1.02267e-06 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 0.00267099 *begin_y*lens_ipow(begin_dx, 5)*begin_lambda + -1.48485e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_lambda + -1.87676e-09 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0[1][0] =  + 0.00561152 *begin_dx*begin_dy + -0.000114837 *begin_y*begin_dx + 3.71218e-05 *begin_x*begin_dy + 0.00395695 *begin_dx*lens_ipow(begin_dy, 3) + 1.15001e-09 *begin_x*lens_ipow(begin_y, 3) + -3.95936e-06 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.00036844 *begin_x*begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 8.53761e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
    domega2_dx0[1][1] =  + -0.00570658  + -0.00839497 *begin_lambda + 0.0126182 *lens_ipow(begin_lambda, 2) + -0.00372193 *lens_ipow(begin_dx, 2) + 6.72389e-06 *lens_ipow(begin_y, 2) + -0.000114837 *begin_x*begin_dx + -0.00653246 *lens_ipow(begin_lambda, 3) + -1.85358e-06 *lens_ipow(begin_y, 2)*begin_lambda + 0.000689427 *begin_y*lens_ipow(begin_dy, 3) + 6.98583e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 2.58409e-06 *lens_ipow(begin_y, 3)*begin_dy + 3.27628e-08 *lens_ipow(begin_y, 4) + 1.72501e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.97968e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.30797e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4)*begin_dy + -0.00018422 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 1.13835e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
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
  out[4] =  + -0.080057  + 1.26306 *begin_lambda + -2.54931 *lens_ipow(begin_lambda, 2) + 1.01941e-05 *lens_ipow(begin_y, 2) + 2.44755 *lens_ipow(begin_lambda, 3) + 0.00125951 *begin_y*begin_dy*begin_lambda + -0.917407 *lens_ipow(begin_lambda, 4) + -0.134562 *lens_ipow(begin_dy, 4) + -0.313394 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.73875 *lens_ipow(begin_dx, 4) + -0.00102213 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.0149732 *begin_y*lens_ipow(begin_dy, 3) + -0.00102315 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000121632 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.81841e-05 *lens_ipow(begin_y, 3)*begin_dy + -2.83401e-07 *lens_ipow(begin_y, 4) + -0.00300862 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0352569 *begin_x*lens_ipow(begin_dx, 3) + 0.00021485 *begin_x*begin_y*begin_dx*begin_dy + -0.000686094 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 2.12977e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -7.64326e-06 *lens_ipow(begin_x, 3)*begin_dx + -4.53347e-08 *lens_ipow(begin_x, 4) + -0.0614196 *lens_ipow(begin_dx, 4)*begin_lambda + 0.00562986 *begin_y*lens_ipow(begin_dy, 5)*begin_lambda + 1.99818e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 7.80369e-08 *begin_x*lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 7.46231e-10 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3)*begin_lambda;
else
  out[4] = 0.0f;
} break;
