case angenieux_double_gauss_1953_50mm:
{
float view[3] =
{
  scene_x,
  scene_y,
  scene_z + camera->lens_outer_pupil_curvature_radius
};
normalise(view);
int error = 0;
if(1 || view[2] >= camera->lens_field_of_view)
{
  const float eps = 1e-8;
  float sqr_err = 1e30, sqr_ap_err = 1e30;
  float prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(int k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err;
    prev_sqr_ap_err = sqr_ap_err;
    const float begin_x = x;
    const float begin_y = y;
    const float begin_dx = dx;
    const float begin_dy = dy;
    const float begin_lambda = lambda;
    const float pred_ap[2] = {
       + 26.7119 *begin_dx + 1.09538 *begin_x*begin_lambda + 6.60947 *begin_dx*begin_lambda + -0.0547589 *begin_y*begin_dx*begin_dy + 0.00189755 *lens_ipow(begin_x, 2)*begin_dx + -16.5359 *lens_ipow(begin_dx, 3) + -1.63151 *begin_x*lens_ipow(begin_lambda, 2) + -14.2808 *begin_dx*lens_ipow(begin_dy, 2) + -0.000478074 *begin_x*lens_ipow(begin_y, 2) + -0.000412757 *lens_ipow(begin_x, 3) + -0.184661 *begin_x*lens_ipow(begin_dy, 2) + -4.54335 *begin_dx*lens_ipow(begin_lambda, 2) + -0.356237 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.838616 *begin_x*lens_ipow(begin_lambda, 3) + 4.95014e-06 *lens_ipow(begin_y, 4)*begin_dx + 7.55289 *lens_ipow(begin_dx, 5) + 0.310712 *begin_x*lens_ipow(begin_dy, 4) + -0.0272238 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.000405637 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.0016729 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 1.38156e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -5.59676e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -2.08299e-09 *lens_ipow(begin_x, 7) + 1.51037e-09 *lens_ipow(begin_x, 7)*begin_lambda + 1.62764 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 3) + -2.43877e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6) + -0.000166531 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 5) + 3.91242e-09 *begin_x*lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2)*begin_dy,
       + 26.6478 *begin_dy + 7.07798 *begin_dy*begin_lambda + 1.14323 *begin_y*begin_lambda + -0.180053 *begin_y*lens_ipow(begin_dx, 2) + -0.142826 *begin_y*lens_ipow(begin_dy, 2) + -0.0529828 *begin_x*begin_dx*begin_dy + -15.8269 *lens_ipow(begin_dx, 2)*begin_dy + -1.77677 *begin_y*lens_ipow(begin_lambda, 2) + -0.000519123 *lens_ipow(begin_x, 2)*begin_y + -4.90498 *begin_dy*lens_ipow(begin_lambda, 2) + -0.000503188 *lens_ipow(begin_y, 3) + 0.00136072 *lens_ipow(begin_x, 2)*begin_dy + -16.844 *lens_ipow(begin_dy, 3) + 0.931493 *begin_y*lens_ipow(begin_lambda, 3) + 0.000190732 *lens_ipow(begin_y, 3)*begin_lambda + 0.0001998 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -0.000822313 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.318617 *begin_y*lens_ipow(begin_dx, 4) + 6.93717 *lens_ipow(begin_dy, 5) + -3.41864e-07 *lens_ipow(begin_x, 4)*begin_y + -0.00699567 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -0.000951 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.000114581 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -1.3737e-09 *lens_ipow(begin_y, 7) + 88.5367 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -4.94822e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -1.54899e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3) + -0.00168031 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)
    };
    const float delta_ap[] = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =  + 26.7119  + 6.60947 *begin_lambda + -0.0547589 *begin_y*begin_dy + 0.00189755 *lens_ipow(begin_x, 2) + -49.6076 *lens_ipow(begin_dx, 2) + -14.2808 *lens_ipow(begin_dy, 2) + -4.54335 *lens_ipow(begin_lambda, 2) + -0.712474 *begin_x*begin_dx*begin_lambda + 4.95014e-06 *lens_ipow(begin_y, 4) + 37.7644 *lens_ipow(begin_dx, 4) + -0.0272238 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000811273 *lens_ipow(begin_x, 3)*begin_dx + -0.0016729 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 6.51054 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -0.000832657 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 4) + 7.82484e-09 *begin_x*lens_ipow(begin_y, 7)*begin_dx*begin_dy+0.0f;
    dx1_domega0[0][1] =  + -0.0547589 *begin_y*begin_dx + -28.5616 *begin_dx*begin_dy + -0.369321 *begin_x*begin_dy + 1.24285 *begin_x*lens_ipow(begin_dy, 3) + -0.0544476 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.0016729 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + 3.91242e-09 *begin_x*lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2)+0.0f;
    dx1_domega0[1][0] =  + -0.360107 *begin_y*begin_dx + -0.0529828 *begin_x*begin_dy + -31.6538 *begin_dx*begin_dy + -0.000822313 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 1.27447 *begin_y*lens_ipow(begin_dx, 3) + 0.000114581 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2) + 354.147 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -0.00336062 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0[1][1] =  + 26.6478  + 7.07798 *begin_lambda + -0.285652 *begin_y*begin_dy + -0.0529828 *begin_x*begin_dx + -15.8269 *lens_ipow(begin_dx, 2) + -4.90498 *lens_ipow(begin_lambda, 2) + 0.00136072 *lens_ipow(begin_x, 2) + -50.532 *lens_ipow(begin_dy, 2) + -0.000822313 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 34.6859 *lens_ipow(begin_dy, 4) + -0.020987 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.001902 *lens_ipow(begin_y, 3)*begin_dy + 0.000229162 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy + 265.61 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -0.00504093 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;

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

    out[0] =  + 49.6109 *begin_dx + -0.621577 *begin_x + 0.674235 *begin_x*begin_lambda + 0.214431 *begin_y*begin_dx*begin_dy + 0.00612017 *begin_x*begin_y*begin_dy + 0.0185352 *lens_ipow(begin_x, 2)*begin_dx + -19.0762 *lens_ipow(begin_dx, 3) + -0.526696 *begin_x*lens_ipow(begin_lambda, 2) + -19.997 *begin_dx*lens_ipow(begin_dy, 2) + -0.00135091 *begin_x*lens_ipow(begin_y, 2) + -0.00120413 *lens_ipow(begin_x, 3) + 0.265561 *begin_x*lens_ipow(begin_dy, 2) + 0.547505 *begin_x*lens_ipow(begin_dx, 2) + 0.000620579 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.000501355 *lens_ipow(begin_x, 3)*begin_lambda + 0.00915562 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.0777405 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -4.20841e-05 *lens_ipow(begin_x, 4)*begin_dx + -0.00108756 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 0.0289986 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.00208955 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -4.49517e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -9.51913e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -3.46111e-09 *lens_ipow(begin_x, 7) + -7.05762e-12 *begin_x*lens_ipow(begin_y, 8) + -6.20338e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2) + 0.0285076 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 4) + 1.33412e-13 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2);
    out[1] =  + -0.613564 *begin_y + 49.7175 *begin_dy + 0.669005 *begin_y*begin_lambda + 0.246172 *begin_y*lens_ipow(begin_dx, 2) + 0.0126827 *lens_ipow(begin_y, 2)*begin_dy + 0.232757 *begin_y*lens_ipow(begin_dy, 2) + 0.00701796 *begin_x*begin_y*begin_dx + -19.0477 *lens_ipow(begin_dx, 2)*begin_dy + -0.524051 *begin_y*lens_ipow(begin_lambda, 2) + -0.00133375 *lens_ipow(begin_x, 2)*begin_y + -0.00127186 *lens_ipow(begin_y, 3) + -21.4258 *lens_ipow(begin_dy, 3) + 0.0105956 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.000544614 *lens_ipow(begin_y, 3)*begin_lambda + 0.333688 *begin_x*begin_dx*begin_dy*begin_lambda + 0.000640797 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -1.70371e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.156726 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 2.94679 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.128866 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -3.102e-09 *lens_ipow(begin_y, 7) + 0.000269581 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*begin_dy + -1.5407e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -2.72774e-09 *lens_ipow(begin_x, 6)*begin_y + 5.47118 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -8.15344e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -8.67539e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 67.1056 *lens_ipow(begin_dy, 7)*begin_lambda;
    out[2] =  + -0.614401 *begin_dx + -0.0124033 *begin_x + -0.00877929 *begin_x*begin_lambda + 0.00908301 *begin_dx*begin_lambda + -6.4694e-05 *begin_x*begin_y*begin_dy + -9.8007e-05 *lens_ipow(begin_x, 2)*begin_dx + 0.305271 *lens_ipow(begin_dx, 3) + 0.00706724 *begin_x*lens_ipow(begin_lambda, 2) + 0.148208 *begin_dx*lens_ipow(begin_dy, 2) + 1.74459e-05 *begin_x*lens_ipow(begin_y, 2) + 1.77203e-05 *lens_ipow(begin_x, 3) + -0.00111275 *begin_x*lens_ipow(begin_dy, 2) + -7.43443e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -7.39746e-06 *lens_ipow(begin_x, 3)*begin_lambda + -2.36067e-07 *lens_ipow(begin_x, 4)*begin_dx + -1.07743e-07 *lens_ipow(begin_y, 4)*begin_dx + -0.289597 *lens_ipow(begin_dx, 5) + 6.58747e-09 *begin_x*lens_ipow(begin_y, 4) + -3.09809e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -0.00453847 *begin_x*lens_ipow(begin_dy, 4) + 0.000362057 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 3.63636e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000693516 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 1.32547e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -0.0485359 *begin_x*lens_ipow(begin_dx, 6) + 3.30777e-11 *lens_ipow(begin_x, 7) + 4.41165e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6) + 0.0506785 *begin_x*begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)*begin_lambda;
    out[3] =  + -0.0119193 *begin_y + -0.614842 *begin_dy + -0.00958648 *begin_y*begin_lambda + -0.00420097 *begin_y*lens_ipow(begin_dx, 2) + 0.00389116 *begin_x*begin_dx*begin_dy + -0.000108381 *begin_x*begin_y*begin_dx + 0.428204 *lens_ipow(begin_dx, 2)*begin_dy + 0.00700915 *begin_y*lens_ipow(begin_lambda, 2) + 1.32734e-05 *lens_ipow(begin_x, 2)*begin_y + 1.40797e-05 *lens_ipow(begin_y, 3) + 0.322422 *lens_ipow(begin_dy, 3) + -0.469415 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.191137 *lens_ipow(begin_dy, 5) + 2.31037e-08 *lens_ipow(begin_x, 4)*begin_y + -0.308648 *lens_ipow(begin_dx, 4)*begin_dy + -8.0158e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -1.92001e-08 *lens_ipow(begin_x, 4)*begin_y*begin_lambda + -5.34204e-09 *lens_ipow(begin_y, 6)*begin_dy + 2.65798e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -3.59985e-10 *lens_ipow(begin_x, 6)*begin_dy + -0.000157427 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -2.54677e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_lambda + 9.48325e-14 *lens_ipow(begin_y, 9) + 3.56726e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3) + 1.47454e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + 1.24034e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*begin_dy + 2.22341e-11 *lens_ipow(begin_y, 8)*begin_dy*begin_lambda + -0.00303946 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2);

    float pred_out_cs[7] = {0.0f};
    lens_sphereToCs(out, out+2, pred_out_cs, pred_out_cs+3, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);

    float view[3] =
    {
      scene_x - pred_out_cs[0],
      scene_y - pred_out_cs[1],
      scene_z - pred_out_cs[2]
    };


    normalise(view);


    float out_new[5];
    lens_csToSphere(pred_out_cs, view, out_new, out_new+2, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);


    const float delta_out[] = {out_new[2] - out[2], out_new[3] - out[3]};
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];


    float domega2_dx0[2][2];
    domega2_dx0[0][0] =  + -0.0124033  + -0.00877929 *begin_lambda + -6.4694e-05 *begin_y*begin_dy + -0.000196014 *begin_x*begin_dx + 0.00706724 *lens_ipow(begin_lambda, 2) + 1.74459e-05 *lens_ipow(begin_y, 2) + 5.31609e-05 *lens_ipow(begin_x, 2) + -0.00111275 *lens_ipow(begin_dy, 2) + -7.43443e-06 *lens_ipow(begin_y, 2)*begin_lambda + -2.21924e-05 *lens_ipow(begin_x, 2)*begin_lambda + -9.44267e-07 *lens_ipow(begin_x, 3)*begin_dx + 6.58747e-09 *lens_ipow(begin_y, 4) + -3.09809e-07 *lens_ipow(begin_y, 3)*begin_dy + -0.00453847 *lens_ipow(begin_dy, 4) + 7.27272e-05 *begin_x*begin_y*begin_dx*begin_dy + 0.00138703 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 6.62735e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -0.0485359 *lens_ipow(begin_dx, 6) + 2.31544e-10 *lens_ipow(begin_x, 6) + 1.3235e-12 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6) + 0.0506785 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
    domega2_dx0[0][1] =  + -6.4694e-05 *begin_x*begin_dy + 3.48918e-05 *begin_x*begin_y + -1.48689e-05 *begin_x*begin_y*begin_lambda + -4.3097e-07 *lens_ipow(begin_y, 3)*begin_dx + 2.63499e-08 *begin_x*lens_ipow(begin_y, 3) + -9.29426e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.000724114 *begin_y*lens_ipow(begin_dx, 3) + 3.63636e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 2.65094e-10 *lens_ipow(begin_x, 5)*begin_y + 2.64699e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + 0.0506785 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
    domega2_dx0[1][0] =  + 0.00389116 *begin_dx*begin_dy + -0.000108381 *begin_y*begin_dx + 2.65468e-05 *begin_x*begin_y + 9.24149e-08 *lens_ipow(begin_x, 3)*begin_y + -1.60316e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -7.68005e-08 *lens_ipow(begin_x, 3)*begin_y*begin_lambda + 5.31597e-10 *begin_x*lens_ipow(begin_y, 5) + -2.15991e-09 *lens_ipow(begin_x, 5)*begin_dy + -0.000314854 *begin_x*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -5.09353e-10 *begin_x*lens_ipow(begin_y, 5)*begin_lambda + 2.14036e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3) + 1.47454e-06 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + -0.00911838 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0[1][1] =  + -0.0119193  + -0.00958648 *begin_lambda + -0.00420097 *lens_ipow(begin_dx, 2) + -0.000108381 *begin_x*begin_dx + 0.00700915 *lens_ipow(begin_lambda, 2) + 1.32734e-05 *lens_ipow(begin_x, 2) + 4.22392e-05 *lens_ipow(begin_y, 2) + 2.31037e-08 *lens_ipow(begin_x, 4) + -1.60316e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.92001e-08 *lens_ipow(begin_x, 4)*begin_lambda + -3.20523e-08 *lens_ipow(begin_y, 5)*begin_dy + 1.32899e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -0.000157427 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -1.27338e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_lambda + 8.53492e-13 *lens_ipow(begin_y, 8) + 1.07018e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2) + 5.89815e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + 7.44204e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_dy + 1.77873e-10 *lens_ipow(begin_y, 7)*begin_dy*begin_lambda+0.0f;
    
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
  out[4] =  + 0.238949  + 0.85346 *begin_lambda + -1.16866 *lens_ipow(begin_lambda, 2) + -0.000545894 *begin_y*begin_dy*begin_lambda + -0.000532821 *begin_x*begin_dx*begin_lambda + 0.564312 *lens_ipow(begin_lambda, 3) + -0.206872 *lens_ipow(begin_dx, 4) + -0.00790672 *begin_y*lens_ipow(begin_dy, 3) + -0.00013516 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00809514 *begin_x*lens_ipow(begin_dx, 3) + -0.204782 *lens_ipow(begin_dy, 4) + -8.85833e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.000243089 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.00648351 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000239826 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00654443 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.000460228 *begin_x*begin_y*begin_dx*begin_dy + -0.00013569 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.59096 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.67893e-10 *lens_ipow(begin_x, 6) + -0.000863147 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + 1.18371 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -1.68689e-10 *lens_ipow(begin_y, 6) + -0.000849445 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -2.32122e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 8.17818e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.321221 *lens_ipow(begin_dx, 6)*lens_ipow(begin_lambda, 2) + -0.341708 *lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2);
else
  out[4] = 0.0f;
} break;