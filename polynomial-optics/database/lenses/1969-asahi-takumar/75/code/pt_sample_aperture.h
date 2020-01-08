case asahi__takumar__1969__75mm:
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
  pred_x =  + 45.6738 *begin_dx + 0.337152 *begin_x + 9.17616 *begin_dx*begin_lambda + 0.181237 *begin_x*begin_lambda + -6.27137 *begin_dx*lens_ipow(begin_lambda, 2) + -26.3671 *begin_dx*lens_ipow(begin_dy, 2) + -27.0473 *lens_ipow(begin_dx, 3) + -0.133001 *begin_y*begin_dx*begin_dy + 0.00143104 *lens_ipow(begin_y, 2)*begin_dx + -0.124195 *begin_x*lens_ipow(begin_lambda, 2) + -0.16488 *begin_x*lens_ipow(begin_dy, 2) + -0.280192 *begin_x*lens_ipow(begin_dx, 2) + 0.00106194 *begin_x*begin_y*begin_dy + -6.76196e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00238312 *lens_ipow(begin_x, 2)*begin_dx + -6.79531e-05 *lens_ipow(begin_x, 3) + 4.75484 *lens_ipow(begin_dx, 5) + -0.00621918 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.241217 *begin_x*lens_ipow(begin_dy, 4) + -0.00758644 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -4.30883 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 0.101893 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -5.38275 *begin_y*begin_dx*lens_ipow(begin_dy, 7) + -7.21287e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4);
  pred_y =  + 45.6991 *begin_dy + 0.337942 *begin_y + 9.07613 *begin_dy*begin_lambda + 0.179175 *begin_y*begin_lambda + -6.18285 *begin_dy*lens_ipow(begin_lambda, 2) + -27.058 *lens_ipow(begin_dy, 3) + -26.2691 *lens_ipow(begin_dx, 2)*begin_dy + -0.123169 *begin_y*lens_ipow(begin_lambda, 2) + -0.279266 *begin_y*lens_ipow(begin_dy, 2) + -0.163908 *begin_y*lens_ipow(begin_dx, 2) + 0.00237704 *lens_ipow(begin_y, 2)*begin_dy + -6.81247e-05 *lens_ipow(begin_y, 3) + -0.140408 *begin_x*begin_dx*begin_dy + 0.00105714 *begin_x*begin_y*begin_dx + 0.0014235 *lens_ipow(begin_x, 2)*begin_dy + -6.77846e-05 *lens_ipow(begin_x, 2)*begin_y + 4.91716 *lens_ipow(begin_dy, 5) + 0.237216 *begin_y*lens_ipow(begin_dx, 4) + -0.0076363 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.00603336 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.107653 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + -38.76 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + -1.65896e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 1.73343e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_lambda;
  pred_dx =  + 0.357088 *begin_dx + -0.0194228 *begin_x + 0.00567479 *begin_x*begin_lambda + -0.741251 *begin_dx*lens_ipow(begin_dy, 2) + -0.712789 *lens_ipow(begin_dx, 3) + -0.0160031 *begin_y*begin_dx*begin_dy + -7.30217e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.00390186 *begin_x*lens_ipow(begin_lambda, 2) + -0.00900144 *begin_x*lens_ipow(begin_dy, 2) + -0.0234731 *begin_x*lens_ipow(begin_dx, 2) + -6.18621e-05 *begin_x*begin_y*begin_dy + -4.26782e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000111587 *lens_ipow(begin_x, 2)*begin_dx + -4.24835e-06 *lens_ipow(begin_x, 3) + -0.0240658 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.0395955 *begin_x*lens_ipow(begin_dx, 4) + -0.000975328 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 2.68669e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 1.3718 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -0.000405426 *begin_x*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -0.121907 *begin_y*begin_dx*lens_ipow(begin_dy, 5) + 0.000129057 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 8.47575e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -3.32152e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2);
  pred_dy =  + 0.357023 *begin_dy + -0.0194519 *begin_y + 0.00574809 *begin_y*begin_lambda + -0.712948 *lens_ipow(begin_dy, 3) + -0.734823 *lens_ipow(begin_dx, 2)*begin_dy + -0.00394983 *begin_y*lens_ipow(begin_lambda, 2) + -0.0235361 *begin_y*lens_ipow(begin_dy, 2) + -0.00893646 *begin_y*lens_ipow(begin_dx, 2) + -0.000112355 *lens_ipow(begin_y, 2)*begin_dy + -4.24662e-06 *lens_ipow(begin_y, 3) + -0.0159704 *begin_x*begin_dx*begin_dy + -6.8774e-05 *begin_x*begin_y*begin_dx + -7.31271e-05 *lens_ipow(begin_x, 2)*begin_dy + -4.2483e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0393011 *begin_y*lens_ipow(begin_dy, 4) + -0.000975818 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.0254752 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + 2.71471e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 1.28168 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -3.35331e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -0.111508 *begin_x*lens_ipow(begin_dx, 5)*begin_dy + 0.000135715 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 8.40021e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -0.00198883 *begin_x*begin_y*lens_ipow(begin_dx, 5)*begin_lambda;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 45.6738  + 9.17616 *begin_lambda + -6.27137 *lens_ipow(begin_lambda, 2) + -26.3671 *lens_ipow(begin_dy, 2) + -81.1419 *lens_ipow(begin_dx, 2) + -0.133001 *begin_y*begin_dy + 0.00143104 *lens_ipow(begin_y, 2) + -0.560383 *begin_x*begin_dx + 0.00238312 *lens_ipow(begin_x, 2) + 23.7742 *lens_ipow(begin_dx, 4) + -0.0186575 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00758644 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -12.9265 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.407571 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -5.38275 *begin_y*lens_ipow(begin_dy, 7)+0.0f;
  dx1_domega0(0, 1) =  + -52.7341 *begin_dx*begin_dy + -0.133001 *begin_y*begin_dx + -0.32976 *begin_x*begin_dy + 0.00106194 *begin_x*begin_y + 0.964868 *begin_x*lens_ipow(begin_dy, 3) + -0.0151729 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -12.9265 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.101893 *begin_x*begin_y*lens_ipow(begin_dx, 4) + -37.6793 *begin_y*begin_dx*lens_ipow(begin_dy, 6)+0.0f;
  dx1_domega0(1, 0) =  + -52.5382 *begin_dx*begin_dy + -0.327817 *begin_y*begin_dx + -0.140408 *begin_x*begin_dy + 0.00105714 *begin_x*begin_y + 0.948863 *begin_y*lens_ipow(begin_dx, 3) + -0.0152726 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.107653 *begin_x*begin_y*lens_ipow(begin_dy, 4) + -193.8 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)+0.0f;
  dx1_domega0(1, 1) =  + 45.6991  + 9.07613 *begin_lambda + -6.18285 *lens_ipow(begin_lambda, 2) + -81.1739 *lens_ipow(begin_dy, 2) + -26.2691 *lens_ipow(begin_dx, 2) + -0.558532 *begin_y*begin_dy + 0.00237704 *lens_ipow(begin_y, 2) + -0.140408 *begin_x*begin_dx + 0.0014235 *lens_ipow(begin_x, 2) + 24.5858 *lens_ipow(begin_dy, 4) + -0.0076363 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0181001 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.430611 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -116.28 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2)+0.0f;
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
