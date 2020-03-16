case canon__unknown__1956__52mm:
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
  pred_x =  + 35.8226 *begin_dx + 0.620986 *begin_x + 0.952585 *begin_dx*begin_lambda + 0.0240883 *begin_x*begin_lambda + -22.4048 *begin_dx*lens_ipow(begin_dy, 2) + -22.4703 *lens_ipow(begin_dx, 3) + -0.390853 *begin_y*begin_dx*begin_dy + -0.243125 *begin_x*lens_ipow(begin_dy, 2) + -0.605095 *begin_x*lens_ipow(begin_dx, 2) + -0.000861823 *begin_x*begin_y*begin_dy + 8.03683 *begin_dx*lens_ipow(begin_dy, 4) + 6.07338 *lens_ipow(begin_dx, 5) + 0.178332 *begin_x*lens_ipow(begin_dy, 4) + -4.25673e-08 *begin_x*lens_ipow(begin_y, 4) + -0.00607202 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -8.845e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -2.21828e-06 *lens_ipow(begin_x, 4)*begin_dx + -3.76908 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -3.00818 *begin_y*lens_ipow(begin_dx, 5)*begin_dy + -0.0620219 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.041359 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -1.48587e-10 *lens_ipow(begin_x, 7);
  pred_y =  + 35.8327 *begin_dy + 0.621162 *begin_y + 0.951909 *begin_dy*begin_lambda + 0.0241916 *begin_y*begin_lambda + -22.0497 *lens_ipow(begin_dy, 3) + -22.9791 *lens_ipow(begin_dx, 2)*begin_dy + -0.582118 *begin_y*lens_ipow(begin_dy, 2) + -0.251728 *begin_y*lens_ipow(begin_dx, 2) + -0.400865 *begin_x*begin_dx*begin_dy + -0.00113277 *begin_x*begin_y*begin_dx + -0.45529 *begin_y*lens_ipow(begin_dy, 4) + -0.453469 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.187129 *begin_y*lens_ipow(begin_dx, 4) + -0.00940776 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.0117416 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -3.6023e-08 *lens_ipow(begin_y, 5) + -0.672725 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.0103079 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -9.13787e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -4.90184e-08 *lens_ipow(begin_x, 4)*begin_y + -2.46069 *begin_x*begin_dx*lens_ipow(begin_dy, 5) + -0.0403241 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5);
  pred_dx =  + 0.516936 *begin_dx + -0.0199858 *begin_x + 0.00458947 *begin_x*begin_lambda + -0.279581 *begin_dx*lens_ipow(begin_dy, 2) + -0.439618 *lens_ipow(begin_dx, 3) + -0.0216022 *begin_y*begin_dx*begin_dy + -0.000172431 *lens_ipow(begin_y, 2)*begin_dx + -0.00320583 *begin_x*lens_ipow(begin_lambda, 2) + -0.011121 *begin_x*lens_ipow(begin_dy, 2) + -0.0379634 *begin_x*lens_ipow(begin_dx, 2) + -0.000324638 *begin_x*begin_y*begin_dy + -6.85564e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000599383 *lens_ipow(begin_x, 2)*begin_dx + -8.74117e-06 *lens_ipow(begin_x, 3) + -4.84101e-09 *begin_x*lens_ipow(begin_y, 4) + -8.80328e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.000834145 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 6.75487 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 8.98491 *lens_ipow(begin_dx, 7) + 0.0022168 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + 0.270484 *begin_x*lens_ipow(begin_dx, 6) + -4.28863e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2);
  pred_dy =  + 0.520257 *begin_dy + -0.0199763 *begin_y + 0.00484436 *begin_y*begin_lambda + -0.486629 *lens_ipow(begin_dy, 3) + -0.336346 *lens_ipow(begin_dx, 2)*begin_dy + -0.00335392 *begin_y*lens_ipow(begin_lambda, 2) + -0.0398091 *begin_y*lens_ipow(begin_dy, 2) + -0.0117977 *begin_y*lens_ipow(begin_dx, 2) + -0.000638105 *lens_ipow(begin_y, 2)*begin_dy + -9.335e-06 *lens_ipow(begin_y, 3) + -0.0213801 *begin_x*begin_dx*begin_dy + -0.000340161 *begin_x*begin_y*begin_dx + -0.000189199 *lens_ipow(begin_x, 2)*begin_dy + -8.9745e-06 *lens_ipow(begin_x, 2)*begin_y + 9.71404 *lens_ipow(begin_dy, 7) + 24.0885 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 0.274442 *begin_y*lens_ipow(begin_dy, 6) + -3.56229e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -0.0239418 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 7.75256e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 8.07722e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 1.36766e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 3);
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 35.8226  + 0.952585 *begin_lambda + -22.4048 *lens_ipow(begin_dy, 2) + -67.4108 *lens_ipow(begin_dx, 2) + -0.390853 *begin_y*begin_dy + -1.21019 *begin_x*begin_dx + 8.03683 *lens_ipow(begin_dy, 4) + 30.3669 *lens_ipow(begin_dx, 4) + -0.00607202 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -2.21828e-06 *lens_ipow(begin_x, 4) + -11.3072 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -15.0409 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + -0.186066 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.206795 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)+0.0f;
  dx1_domega0(0, 1) =  + -44.8095 *begin_dx*begin_dy + -0.390853 *begin_y*begin_dx + -0.486249 *begin_x*begin_dy + -0.000861823 *begin_x*begin_y + 32.1473 *begin_dx*lens_ipow(begin_dy, 3) + 0.713326 *begin_x*lens_ipow(begin_dy, 3) + -0.012144 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -11.3072 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -3.00818 *begin_y*lens_ipow(begin_dx, 5) + -0.124044 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
  dx1_domega0(1, 0) =  + -45.9583 *begin_dx*begin_dy + -0.503457 *begin_y*begin_dx + -0.400865 *begin_x*begin_dy + -0.00113277 *begin_x*begin_y + -0.906939 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.748514 *begin_y*lens_ipow(begin_dx, 3) + -0.0234832 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -2.01818 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -0.0206158 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -2.46069 *begin_x*lens_ipow(begin_dy, 5)+0.0f;
  dx1_domega0(1, 1) =  + 35.8327  + 0.951909 *begin_lambda + -66.1492 *lens_ipow(begin_dy, 2) + -22.9791 *lens_ipow(begin_dx, 2) + -1.16424 *begin_y*begin_dy + -0.400865 *begin_x*begin_dx + -1.82116 *begin_y*lens_ipow(begin_dy, 3) + -0.906939 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0282233 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0117416 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.672725 *begin_x*lens_ipow(begin_dx, 3) + -0.0103079 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -12.3034 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.20162 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)+0.0f;
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
