case asahi__takumar__1969__58mm:
{
double pred_x;
double pred_y;
double pred_dx;
double pred_dy;
double sqr_err = FLT_MAX;
for(int k=0;k<5&&sqr_err > 1e-4f;k++)
{
  const double begin_x = x + dist * dx;
  const double begin_y = y + dist * dy;
  const double begin_dx = dx;
  const double begin_dy = dy;
  const double begin_lambda = lambda;
  pred_x =  + 35.3504 *begin_dx + 0.332363 *begin_x + 6.97928 *begin_dx*begin_lambda + 0.191351 *begin_x*begin_lambda + -4.80586 *begin_dx*lens_ipow(begin_lambda, 2) + -20.3723 *begin_dx*lens_ipow(begin_dy, 2) + -20.1465 *lens_ipow(begin_dx, 3) + -0.131496 *begin_y*begin_dx*begin_dy + -0.133966 *begin_x*lens_ipow(begin_lambda, 2) + -0.128929 *begin_x*lens_ipow(begin_dy, 2) + -0.272339 *begin_x*lens_ipow(begin_dx, 2) + 0.00123259 *begin_x*begin_y*begin_dy + -8.13897e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00301142 *lens_ipow(begin_x, 2)*begin_dx + -8.77939e-05 *lens_ipow(begin_x, 3) + 0.00293381 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.2949 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.0184865 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.18574e-07 *begin_x*lens_ipow(begin_y, 4) + -4.20053e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -9.8336e-08 *lens_ipow(begin_x, 5) + 3.56329e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -0.0195012 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.074804 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4);
  pred_y =  + 35.372 *begin_dy + 0.33302 *begin_y + 6.83847 *begin_dy*begin_lambda + 0.19069 *begin_y*begin_lambda + -4.6714 *begin_dy*lens_ipow(begin_lambda, 2) + -20.1086 *lens_ipow(begin_dy, 3) + -20.0429 *lens_ipow(begin_dx, 2)*begin_dy + -0.133313 *begin_y*lens_ipow(begin_lambda, 2) + -0.273146 *begin_y*lens_ipow(begin_dy, 2) + -0.160689 *begin_y*lens_ipow(begin_dx, 2) + 0.003187 *lens_ipow(begin_y, 2)*begin_dy + -8.68112e-05 *lens_ipow(begin_y, 3) + -0.152337 *begin_x*begin_dx*begin_dy + 0.00124609 *begin_x*begin_y*begin_dx + -8.49409e-05 *lens_ipow(begin_x, 2)*begin_y + 0.00302293 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.222472 *begin_y*lens_ipow(begin_dx, 4) + -0.0108468 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.0183e-07 *lens_ipow(begin_y, 5) + 0.0156842 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -4.09e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -1.07898e-07 *lens_ipow(begin_x, 4)*begin_y + 3.49524e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -0.0214537 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2);
  pred_dx =  + 0.357561 *begin_dx + -0.0253258 *begin_x + 0.00806322 *begin_x*begin_lambda + -0.697798 *begin_dx*lens_ipow(begin_dy, 2) + -0.78774 *lens_ipow(begin_dx, 3) + -0.022616 *begin_y*begin_dx*begin_dy + -9.21474e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.00567841 *begin_x*lens_ipow(begin_lambda, 2) + -0.010936 *begin_x*lens_ipow(begin_dy, 2) + -0.0338437 *begin_x*lens_ipow(begin_dx, 2) + -0.000115133 *begin_x*begin_y*begin_dy + -8.5487e-06 *begin_x*lens_ipow(begin_y, 2) + -0.00024058 *lens_ipow(begin_x, 2)*begin_dx + -9.22568e-06 *lens_ipow(begin_x, 3) + 0.551515 *lens_ipow(begin_dx, 5) + -1.91019e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 2.3529e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -1.35646e-11 *begin_x*lens_ipow(begin_y, 6) + 1.74617e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + 2.05129e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 8.98293e-10 *lens_ipow(begin_x, 6)*begin_dx + -2.65595e-07 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 4) + -6.69187e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 2) + 154.671 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 4)*begin_lambda;
  pred_dy =  + 0.355879 *begin_dy + -0.0254446 *begin_y + 0.00841777 *begin_y*begin_lambda + -0.723072 *lens_ipow(begin_dy, 3) + -0.694961 *lens_ipow(begin_dx, 2)*begin_dy + -0.00595967 *begin_y*lens_ipow(begin_lambda, 2) + -0.0338035 *begin_y*lens_ipow(begin_dy, 2) + -0.0108788 *begin_y*lens_ipow(begin_dx, 2) + -0.000239358 *lens_ipow(begin_y, 2)*begin_dy + -9.16709e-06 *lens_ipow(begin_y, 3) + -0.0225832 *begin_x*begin_dx*begin_dy + -0.000113396 *begin_x*begin_y*begin_dx + -9.15125e-05 *lens_ipow(begin_x, 2)*begin_dy + -8.47201e-06 *lens_ipow(begin_x, 2)*begin_y + -1.94504e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.33551e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 8.99913e-10 *lens_ipow(begin_y, 6)*begin_dy + 1.99827e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 1.70736e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -1.36642e-11 *lens_ipow(begin_x, 6)*begin_y + -7.02255e-11 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2) + -2.75169e-07 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 4) + 13.8536 *lens_ipow(begin_dy, 9)*begin_lambda + 151.703 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 5)*begin_lambda;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 35.3504  + 6.97928 *begin_lambda + -4.80586 *lens_ipow(begin_lambda, 2) + -20.3723 *lens_ipow(begin_dy, 2) + -60.4394 *lens_ipow(begin_dx, 2) + -0.131496 *begin_y*begin_dy + -0.544679 *begin_x*begin_dx + 0.00301142 *lens_ipow(begin_x, 2) + 0.00293381 *lens_ipow(begin_y, 2)*begin_lambda + -0.2949 *begin_y*lens_ipow(begin_dy, 3) + 0.0369729 *begin_x*begin_y*begin_dx*begin_dy + -0.0585036 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.074804 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)+0.0f;
  dx1_domega0(0, 1) =  + -40.7446 *begin_dx*begin_dy + -0.131496 *begin_y*begin_dx + -0.257857 *begin_x*begin_dy + 0.00123259 *begin_x*begin_y + -0.8847 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.0184865 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -0.299216 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 3)+0.0f;
  dx1_domega0(1, 0) =  + -40.0858 *begin_dx*begin_dy + -0.321378 *begin_y*begin_dx + -0.152337 *begin_x*begin_dy + 0.00124609 *begin_x*begin_y + 0.889887 *begin_y*lens_ipow(begin_dx, 3) + -0.0216937 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0156842 *begin_x*begin_y*lens_ipow(begin_dy, 2)+0.0f;
  dx1_domega0(1, 1) =  + 35.372  + 6.83847 *begin_lambda + -4.6714 *lens_ipow(begin_lambda, 2) + -60.3259 *lens_ipow(begin_dy, 2) + -20.0429 *lens_ipow(begin_dx, 2) + -0.546291 *begin_y*begin_dy + 0.003187 *lens_ipow(begin_y, 2) + -0.152337 *begin_x*begin_dx + 0.00302293 *lens_ipow(begin_x, 2)*begin_lambda + -0.0108468 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.0313684 *begin_x*begin_y*begin_dx*begin_dy + -0.064361 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
  Eigen::Matrix2d invJ;
  const double invdet = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
  invJ(0, 0) =  dx1_domega0(1, 1)*invdet;
  invJ(1, 1) =  dx1_domega0(0, 0)*invdet;
  invJ(0, 1) = -dx1_domega0(0, 1)*invdet;
  invJ(1, 0) = -dx1_domega0(1, 0)*invdet;
  const Eigen::Vector2d dx1(out_x - pred_x, out_y - pred_y);
  for(int i=0;i<2;i++)
  {
    dx += invJ(0, i)*dx1(i);
    dy += invJ(1, i)*dx1(i);
  }
  sqr_err = dx1(0)*dx1(0) + dx1(1)*dx1(1);
}
out_dx = pred_dx;
out_dy = pred_dy;
} break;
