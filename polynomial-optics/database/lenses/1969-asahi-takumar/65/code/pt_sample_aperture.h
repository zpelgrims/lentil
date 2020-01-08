case asahi__takumar__1969__65mm:
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
  pred_x =  + 39.5196 *begin_dx + 0.334219 *begin_x + 8.04654 *begin_dx*begin_lambda + 0.188519 *begin_x*begin_lambda + -5.51125 *begin_dx*lens_ipow(begin_lambda, 2) + -22.768 *begin_dx*lens_ipow(begin_dy, 2) + -22.5418 *lens_ipow(begin_dx, 3) + -0.132458 *begin_y*begin_dx*begin_dy + 0.00159413 *lens_ipow(begin_y, 2)*begin_dx + -0.130241 *begin_x*lens_ipow(begin_lambda, 2) + -0.165402 *begin_x*lens_ipow(begin_dy, 2) + -0.275309 *begin_x*lens_ipow(begin_dx, 2) + 0.00123938 *begin_x*begin_y*begin_dy + -8.73446e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00283016 *lens_ipow(begin_x, 2)*begin_dx + -7.57708e-05 *lens_ipow(begin_x, 3) + -0.279459 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.00658781 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.245526 *begin_x*lens_ipow(begin_dy, 4) + -0.00956435 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -5.69623e-08 *lens_ipow(begin_x, 5) + 0.134774 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -6.4667e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 2.23749e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*lens_ipow(begin_lambda, 2);
  pred_y =  + 39.7272 *begin_dy + 0.336227 *begin_y + 7.57255 *begin_dy*begin_lambda + 0.18659 *begin_y*begin_lambda + -5.22297 *begin_dy*lens_ipow(begin_lambda, 2) + -23.4536 *lens_ipow(begin_dy, 3) + -22.7883 *lens_ipow(begin_dx, 2)*begin_dy + -0.128843 *begin_y*lens_ipow(begin_lambda, 2) + -0.278117 *begin_y*lens_ipow(begin_dy, 2) + -0.164536 *begin_y*lens_ipow(begin_dx, 2) + 0.00277422 *lens_ipow(begin_y, 2)*begin_dy + -9.49952e-05 *lens_ipow(begin_y, 3) + -0.141509 *begin_x*begin_dx*begin_dy + 0.00125947 *begin_x*begin_y*begin_dx + -9.45247e-05 *lens_ipow(begin_x, 2)*begin_y + 0.00288068 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.247988 *begin_y*lens_ipow(begin_dx, 4) + -0.00865712 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 7.79017 *lens_ipow(begin_dy, 5)*begin_lambda + 0.12234 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + -0.0215547 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -37.7425 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + -3.34291e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 3.37208e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_lambda;
  pred_dx =  + 0.35483 *begin_dx + -0.0224734 *begin_x + 0.00686869 *begin_x*begin_lambda + -0.677992 *begin_dx*lens_ipow(begin_dy, 2) + -0.689397 *lens_ipow(begin_dx, 3) + -0.0197984 *begin_y*begin_dx*begin_dy + -8.32307e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.0048578 *begin_x*lens_ipow(begin_lambda, 2) + -0.0102079 *begin_x*lens_ipow(begin_dy, 2) + -0.0282913 *begin_x*lens_ipow(begin_dx, 2) + -6.3053e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000199478 *lens_ipow(begin_x, 2)*begin_dx + -6.50021e-06 *lens_ipow(begin_x, 3) + -0.000132909 *begin_x*begin_y*begin_dy*begin_lambda + 1.36958e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -1.03325e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 3.6907e-07 *lens_ipow(begin_x, 4)*begin_dx + -0.0577127 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + -0.00135693 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 1.32614e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -0.00142823 *begin_x*begin_y*lens_ipow(begin_dy, 5) + 1.64324e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -0.477014 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*begin_lambda + 2.28798e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda;
  pred_dy =  + 0.355267 *begin_dy + -0.0226233 *begin_y + 0.00721661 *begin_y*begin_lambda + -0.721575 *lens_ipow(begin_dy, 3) + -0.679221 *lens_ipow(begin_dx, 2)*begin_dy + -0.00514031 *begin_y*lens_ipow(begin_lambda, 2) + -0.0303871 *begin_y*lens_ipow(begin_dy, 2) + -0.0103029 *begin_y*lens_ipow(begin_dx, 2) + -0.000172531 *lens_ipow(begin_y, 2)*begin_dy + -5.28731e-06 *lens_ipow(begin_y, 3) + -0.0199397 *begin_x*begin_dx*begin_dy + -8.04082e-05 *lens_ipow(begin_x, 2)*begin_dy + -6.18092e-06 *lens_ipow(begin_x, 2)*begin_y + -0.000132546 *begin_x*begin_y*begin_dx*begin_lambda + -4.69007e-09 *lens_ipow(begin_y, 5) + -0.000286664 *begin_x*begin_y*lens_ipow(begin_dx, 3) + -6.6018e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.000144495 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 1.56589e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 2.46714 *lens_ipow(begin_dy, 7)*begin_lambda + 2.61678e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -2.81569 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5) + 5.24785e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 2) + -2.97422e-13 *lens_ipow(begin_x, 8)*begin_y*lens_ipow(begin_dy, 2);
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 39.5196  + 8.04654 *begin_lambda + -5.51125 *lens_ipow(begin_lambda, 2) + -22.768 *lens_ipow(begin_dy, 2) + -67.6254 *lens_ipow(begin_dx, 2) + -0.132458 *begin_y*begin_dy + 0.00159413 *lens_ipow(begin_y, 2) + -0.550617 *begin_x*begin_dx + 0.00283016 *lens_ipow(begin_x, 2) + -0.279459 *begin_y*lens_ipow(begin_dy, 3) + -0.0197634 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00956435 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.539097 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
  dx1_domega0(0, 1) =  + -45.5359 *begin_dx*begin_dy + -0.132458 *begin_y*begin_dx + -0.330805 *begin_x*begin_dy + 0.00123938 *begin_x*begin_y + -0.838377 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.982105 *begin_x*lens_ipow(begin_dy, 3) + -0.0191287 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.134774 *begin_x*begin_y*lens_ipow(begin_dx, 4)+0.0f;
  dx1_domega0(1, 0) =  + -45.5767 *begin_dx*begin_dy + -0.329073 *begin_y*begin_dx + -0.141509 *begin_x*begin_dy + 0.00125947 *begin_x*begin_y + 0.991952 *begin_y*lens_ipow(begin_dx, 3) + -0.0173142 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.12234 *begin_x*begin_y*lens_ipow(begin_dy, 4) + -188.712 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)+0.0f;
  dx1_domega0(1, 1) =  + 39.7272  + 7.57255 *begin_lambda + -5.22297 *lens_ipow(begin_lambda, 2) + -70.3608 *lens_ipow(begin_dy, 2) + -22.7883 *lens_ipow(begin_dx, 2) + -0.556234 *begin_y*begin_dy + 0.00277422 *lens_ipow(begin_y, 2) + -0.141509 *begin_x*begin_dx + 0.00288068 *lens_ipow(begin_x, 2)*begin_lambda + -0.00865712 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 38.9508 *lens_ipow(begin_dy, 4)*begin_lambda + 0.489359 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0646641 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -113.227 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2)+0.0f;
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
