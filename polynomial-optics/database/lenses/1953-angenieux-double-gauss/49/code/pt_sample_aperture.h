case angenieux__double_gauss__1953__49mm:
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
  pred_x =  + 0.197484 *begin_x + 27.5928 *begin_dx + 1.74497 *begin_dx*begin_lambda + 0.08335 *begin_x*begin_lambda + -0.106556 *begin_y*begin_dx*begin_dy + -0.000436864 *begin_x*lens_ipow(begin_y, 2) + -15.176 *lens_ipow(begin_dx, 3) + -15.544 *begin_dx*lens_ipow(begin_dy, 2) + -0.000420072 *lens_ipow(begin_x, 3) + -0.193987 *begin_x*lens_ipow(begin_dx, 2) + -0.115566 *begin_x*lens_ipow(begin_dy, 2) + 8.53267e-06 *lens_ipow(begin_x, 4)*begin_dx + -1.37132e-09 *lens_ipow(begin_x, 7) + -1.42221e-09 *begin_x*lens_ipow(begin_y, 6) + -4.46795e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -4.32995e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2);
  pred_y =  + 27.5931 *begin_dy + 0.19711 *begin_y + 1.74531 *begin_dy*begin_lambda + 0.0839936 *begin_y*begin_lambda + -0.115586 *begin_y*lens_ipow(begin_dx, 2) + -0.000436985 *lens_ipow(begin_x, 2)*begin_y + -15.2094 *lens_ipow(begin_dy, 3) + -0.000418615 *lens_ipow(begin_y, 3) + -0.194777 *begin_y*lens_ipow(begin_dy, 2) + -15.493 *lens_ipow(begin_dx, 2)*begin_dy + -0.107801 *begin_x*begin_dx*begin_dy + 8.51781e-06 *lens_ipow(begin_y, 4)*begin_dy + -1.40883e-09 *lens_ipow(begin_y, 7) + -4.44726e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -4.38036e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -1.37285e-09 *lens_ipow(begin_x, 6)*begin_y;
  pred_dx =  + -0.0338929 *begin_x + 0.39901 *begin_dx + 0.00509044 *begin_x*begin_lambda + -0.0235895 *begin_y*begin_dx*begin_dy + -3.07307e-05 *begin_x*lens_ipow(begin_y, 2) + -0.496655 *lens_ipow(begin_dx, 3) + -0.508143 *begin_dx*lens_ipow(begin_dy, 2) + -2.6578e-05 *lens_ipow(begin_x, 3) + -0.0352866 *begin_x*lens_ipow(begin_dx, 2) + -0.0126963 *begin_x*lens_ipow(begin_dy, 2) + 2.65939e-06 *lens_ipow(begin_x, 4)*begin_dx + 2.50339e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -7.96496e-11 *lens_ipow(begin_x, 7) + 1.57255e-08 *begin_x*lens_ipow(begin_y, 5)*begin_dy + 2.57234e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -3.73458e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2);
  pred_dy =  + 0.39878 *begin_dy + -0.0339385 *begin_y + 0.00517753 *begin_y*begin_lambda + -0.0128604 *begin_y*lens_ipow(begin_dx, 2) + -3.06847e-05 *lens_ipow(begin_x, 2)*begin_y + -0.496055 *lens_ipow(begin_dy, 3) + -2.64494e-05 *lens_ipow(begin_y, 3) + -0.0352949 *begin_y*lens_ipow(begin_dy, 2) + -0.505331 *lens_ipow(begin_dx, 2)*begin_dy + -0.0237488 *begin_x*begin_dx*begin_dy + 2.38919e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 2.66628e-06 *lens_ipow(begin_y, 4)*begin_dy + -8.31407e-11 *lens_ipow(begin_y, 7) + -3.80715e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 2.59267e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + 1.58507e-08 *lens_ipow(begin_x, 5)*begin_y*begin_dx;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 27.5928  + 1.74497 *begin_lambda + -0.106556 *begin_y*begin_dy + -45.5281 *lens_ipow(begin_dx, 2) + -15.544 *lens_ipow(begin_dy, 2) + -0.387974 *begin_x*begin_dx + 8.53267e-06 *lens_ipow(begin_x, 4)+0.0f;
  dx1_domega0(0, 1) =  + -0.106556 *begin_y*begin_dx + -31.0879 *begin_dx*begin_dy + -0.231133 *begin_x*begin_dy+0.0f;
  dx1_domega0(1, 0) =  + -0.231172 *begin_y*begin_dx + -30.9859 *begin_dx*begin_dy + -0.107801 *begin_x*begin_dy+0.0f;
  dx1_domega0(1, 1) =  + 27.5931  + 1.74531 *begin_lambda + -45.6282 *lens_ipow(begin_dy, 2) + -0.389554 *begin_y*begin_dy + -15.493 *lens_ipow(begin_dx, 2) + -0.107801 *begin_x*begin_dx + 8.51781e-06 *lens_ipow(begin_y, 4)+0.0f;
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
