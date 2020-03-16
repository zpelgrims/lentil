case minolta__fisheye__1978__28mm:
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
  pred_x =  + 65.9378 *begin_dx + 0.76074 *begin_x + -4.69765 *begin_dx*begin_lambda + -0.133134 *begin_x*begin_lambda + 111.311 *begin_dx*lens_ipow(begin_dy, 2) + 111.242 *lens_ipow(begin_dx, 3) + 3.315 *begin_y*begin_dx*begin_dy + 0.021483 *lens_ipow(begin_y, 2)*begin_dx + 0.0913347 *begin_x*lens_ipow(begin_lambda, 2) + 4.37835 *begin_x*lens_ipow(begin_dx, 2) + 0.0512073 *lens_ipow(begin_x, 2)*begin_dx + 0.000173408 *lens_ipow(begin_x, 3) + 3.0545 *begin_dx*lens_ipow(begin_lambda, 3) + 5.9538 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.16575 *begin_x*begin_y*begin_dy*begin_lambda + 0.000949947 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -10.8685 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.301757 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00169969 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 6.52783 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.180696 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 0.00100043 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3);
  pred_y =  + 66.4563 *begin_dy + 0.760083 *begin_y + -7.53454 *begin_dy*begin_lambda + -0.130819 *begin_y*begin_lambda + 5.12406 *begin_dy*lens_ipow(begin_lambda, 2) + 111.291 *lens_ipow(begin_dy, 3) + 111.328 *lens_ipow(begin_dx, 2)*begin_dy + 0.0891919 *begin_y*lens_ipow(begin_lambda, 2) + 4.38218 *begin_y*lens_ipow(begin_dy, 2) + 0.0512712 *lens_ipow(begin_y, 2)*begin_dy + 0.00017376 *lens_ipow(begin_y, 3) + 3.29932 *begin_x*begin_dx*begin_dy + 0.021268 *lens_ipow(begin_x, 2)*begin_dy + 0.000174259 *lens_ipow(begin_x, 2)*begin_y + 5.34431 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.167621 *begin_x*begin_y*begin_dx*begin_lambda + -7.3717 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.322193 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.308168 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.00417008 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.185918 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 3) + 3.97146 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4);
  pred_dx =  + -0.477124 *begin_dx + -0.0204242 *begin_x + -0.460016 *begin_dx*begin_lambda + -0.0068016 *begin_x*begin_lambda + 0.306345 *begin_dx*lens_ipow(begin_lambda, 2) + -1.36997 *begin_dx*lens_ipow(begin_dy, 2) + -1.34275 *lens_ipow(begin_dx, 3) + 0.0209847 *begin_y*begin_dx*begin_dy + 0.000231183 *lens_ipow(begin_y, 2)*begin_dx + 0.0044704 *begin_x*lens_ipow(begin_lambda, 2) + 0.016849 *begin_x*lens_ipow(begin_dy, 2) + 0.0368385 *begin_x*lens_ipow(begin_dx, 2) + 0.000893973 *begin_x*begin_y*begin_dy + 4.64716e-06 *begin_x*lens_ipow(begin_y, 2) + 0.00110442 *lens_ipow(begin_x, 2)*begin_dx + 4.63701e-06 *lens_ipow(begin_x, 3) + -0.020381 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.0176663 *begin_x*lens_ipow(begin_dy, 4) + -0.00147023 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.214948 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -0.00308894 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -7.70117e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_lambda;
  pred_dy =  + -0.47896 *begin_dy + -0.0204441 *begin_y + -0.471637 *begin_dy*begin_lambda + -0.00705896 *begin_y*begin_lambda + 0.322065 *begin_dy*lens_ipow(begin_lambda, 2) + -1.23506 *lens_ipow(begin_dy, 3) + -1.17555 *lens_ipow(begin_dx, 2)*begin_dy + 0.004854 *begin_y*lens_ipow(begin_lambda, 2) + 0.0402509 *begin_y*lens_ipow(begin_dy, 2) + 0.0200021 *begin_y*lens_ipow(begin_dx, 2) + 0.00113988 *lens_ipow(begin_y, 2)*begin_dy + 4.75677e-06 *lens_ipow(begin_y, 3) + 0.0231768 *begin_x*begin_dx*begin_dy + 0.000933759 *begin_x*begin_y*begin_dx + 0.000259414 *lens_ipow(begin_x, 2)*begin_dy + 5.13545e-06 *lens_ipow(begin_x, 2)*begin_y + -2.84022 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.00486326 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.00206316 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -0.185061 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 0.000120673 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -7.86947e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2);
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 65.9378  + -4.69765 *begin_lambda + 111.311 *lens_ipow(begin_dy, 2) + 333.726 *lens_ipow(begin_dx, 2) + 3.315 *begin_y*begin_dy + 0.021483 *lens_ipow(begin_y, 2) + 8.7567 *begin_x*begin_dx + 0.0512073 *lens_ipow(begin_x, 2) + 3.0545 *lens_ipow(begin_lambda, 3)+0.0f;
  dx1_domega0(0, 1) =  + 222.623 *begin_dx*begin_dy + 3.315 *begin_y*begin_dx + 11.9076 *begin_x*begin_dy*begin_lambda + 0.16575 *begin_x*begin_y*begin_lambda + -21.737 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.301757 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 13.0557 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + 0.180696 *begin_x*begin_y*lens_ipow(begin_lambda, 3)+0.0f;
  dx1_domega0(1, 0) =  + 222.655 *begin_dx*begin_dy + 3.29932 *begin_x*begin_dy + 10.6886 *begin_y*begin_dx*begin_lambda + 0.167621 *begin_x*begin_y*begin_lambda + -14.7434 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.322193 *begin_x*lens_ipow(begin_dy, 3) + -0.308168 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 0.185918 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 7.94292 *begin_y*begin_dx*lens_ipow(begin_lambda, 4)+0.0f;
  dx1_domega0(1, 1) =  + 66.4563  + -7.53454 *begin_lambda + 5.12406 *lens_ipow(begin_lambda, 2) + 333.872 *lens_ipow(begin_dy, 2) + 111.328 *lens_ipow(begin_dx, 2) + 8.76437 *begin_y*begin_dy + 0.0512712 *lens_ipow(begin_y, 2) + 3.29932 *begin_x*begin_dx + 0.021268 *lens_ipow(begin_x, 2) + 0.966579 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.0125102 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)+0.0f;
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
