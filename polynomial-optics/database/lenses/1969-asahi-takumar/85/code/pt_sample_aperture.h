case asahi__takumar__1969__85mm:
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
  pred_x =  + 51.7353 *begin_dx + 0.338736 *begin_x + 10.3533 *begin_dx*begin_lambda + 0.176749 *begin_x*begin_lambda + -7.07507 *begin_dx*lens_ipow(begin_lambda, 2) + -29.793 *begin_dx*lens_ipow(begin_dy, 2) + -29.5833 *lens_ipow(begin_dx, 3) + -0.106863 *begin_y*begin_dx*begin_dy + 0.0012989 *lens_ipow(begin_y, 2)*begin_dx + -0.120922 *begin_x*lens_ipow(begin_lambda, 2) + -0.163605 *begin_x*lens_ipow(begin_dy, 2) + -0.280733 *begin_x*lens_ipow(begin_dx, 2) + 0.000813969 *begin_x*begin_y*begin_dy + -5.46827e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00216317 *lens_ipow(begin_x, 2)*begin_dx + -5.29176e-05 *lens_ipow(begin_x, 3) + -0.363388 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.343916 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.00598417 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.222924 *begin_x*lens_ipow(begin_dy, 4) + -0.00779999 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.016676 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda;
  pred_y =  + 51.7458 *begin_dy + 0.33896 *begin_y + 10.3081 *begin_dy*begin_lambda + 0.174589 *begin_y*begin_lambda + -7.04044 *begin_dy*lens_ipow(begin_lambda, 2) + -29.5302 *lens_ipow(begin_dy, 3) + -29.7097 *lens_ipow(begin_dx, 2)*begin_dy + -0.119324 *begin_y*lens_ipow(begin_lambda, 2) + -0.278849 *begin_y*lens_ipow(begin_dy, 2) + -0.164669 *begin_y*lens_ipow(begin_dx, 2) + 0.00214903 *lens_ipow(begin_y, 2)*begin_dy + -5.14451e-05 *lens_ipow(begin_y, 3) + -0.133046 *begin_x*begin_dx*begin_dy + 0.000880539 *begin_x*begin_y*begin_dx + 0.00123277 *lens_ipow(begin_x, 2)*begin_dy + -4.93721e-05 *lens_ipow(begin_x, 2)*begin_y + 0.228092 *begin_y*lens_ipow(begin_dx, 4) + -0.00817597 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.281369 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.00497022 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.107823 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + -1.1996e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3);
  pred_dx =  + 0.355593 *begin_dx + -0.0170617 *begin_x + 0.00472472 *begin_x*begin_lambda + -0.736706 *begin_dx*lens_ipow(begin_dy, 2) + -0.701789 *lens_ipow(begin_dx, 3) + -0.0159645 *begin_y*begin_dx*begin_dy + -5.26796e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.00317201 *begin_x*lens_ipow(begin_lambda, 2) + -0.0078683 *begin_x*lens_ipow(begin_dy, 2) + -0.0214137 *begin_x*lens_ipow(begin_dx, 2) + -5.36005e-05 *begin_x*begin_y*begin_dy + -2.87085e-06 *begin_x*lens_ipow(begin_y, 2) + -8.5757e-05 *lens_ipow(begin_x, 2)*begin_dx + -2.98739e-06 *lens_ipow(begin_x, 3) + 8.38807e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 1.38143 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0503977 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + -0.00100175 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.080475 *begin_y*begin_dx*lens_ipow(begin_dy, 5) + 4.66004e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + 6.22185e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -0.00173664 *begin_x*begin_y*lens_ipow(begin_dy, 5)*begin_lambda;
  pred_dy =  + 0.356696 *begin_dy + -0.0171159 *begin_y + 0.0048754 *begin_y*begin_lambda + -0.709894 *lens_ipow(begin_dy, 3) + -0.703228 *lens_ipow(begin_dx, 2)*begin_dy + -0.00331504 *begin_y*lens_ipow(begin_lambda, 2) + -0.0223591 *begin_y*lens_ipow(begin_dy, 2) + -0.00745347 *begin_y*lens_ipow(begin_dx, 2) + -0.000107418 *lens_ipow(begin_y, 2)*begin_dy + -2.96442e-06 *lens_ipow(begin_y, 3) + -0.0134932 *begin_x*begin_dx*begin_dy + -6.2211e-05 *begin_x*begin_y*begin_dx + -5.51196e-05 *lens_ipow(begin_x, 2)*begin_dy + -2.83616e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0283354 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.0309838 *begin_x*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.000122158 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 6.66572e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 5.09055e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -0.247445 *begin_y*lens_ipow(begin_dy, 6)*begin_lambda + -0.262282 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -0.00492972 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5)*begin_lambda;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 51.7353  + 10.3533 *begin_lambda + -7.07507 *lens_ipow(begin_lambda, 2) + -29.793 *lens_ipow(begin_dy, 2) + -88.7499 *lens_ipow(begin_dx, 2) + -0.106863 *begin_y*begin_dy + 0.0012989 *lens_ipow(begin_y, 2) + -0.561467 *begin_x*begin_dx + 0.00216317 *lens_ipow(begin_x, 2) + -0.363388 *begin_y*lens_ipow(begin_dy, 3) + -1.03175 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0179525 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00779999 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.0333519 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda+0.0f;
  dx1_domega0(0, 1) =  + -59.5859 *begin_dx*begin_dy + -0.106863 *begin_y*begin_dx + -0.327209 *begin_x*begin_dy + 0.000813969 *begin_x*begin_y + -1.09016 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.343916 *begin_y*lens_ipow(begin_dx, 3) + 0.891695 *begin_x*lens_ipow(begin_dy, 3) + -0.0156 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.016676 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda+0.0f;
  dx1_domega0(1, 0) =  + -59.4194 *begin_dx*begin_dy + -0.329338 *begin_y*begin_dx + -0.133046 *begin_x*begin_dy + 0.000880539 *begin_x*begin_y + 0.912368 *begin_y*lens_ipow(begin_dx, 3) + -0.0163519 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.844106 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.107823 *begin_x*begin_y*lens_ipow(begin_dy, 4)+0.0f;
  dx1_domega0(1, 1) =  + 51.7458  + 10.3081 *begin_lambda + -7.04044 *lens_ipow(begin_lambda, 2) + -88.5907 *lens_ipow(begin_dy, 2) + -29.7097 *lens_ipow(begin_dx, 2) + -0.557698 *begin_y*begin_dy + 0.00214903 *lens_ipow(begin_y, 2) + -0.133046 *begin_x*begin_dx + 0.00123277 *lens_ipow(begin_x, 2) + -0.00817597 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.281369 *begin_x*lens_ipow(begin_dx, 3) + -0.0149107 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.431294 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3)+0.0f;
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
