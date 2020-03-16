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
  pred_x =  + 27.5808 *begin_dx + 0.192185 *begin_x + 1.76587 *begin_dx*begin_lambda + 0.084184 *begin_x*begin_lambda + -15.2207 *begin_dx*lens_ipow(begin_dy, 2) + -15.1519 *lens_ipow(begin_dx, 3) + -0.0879496 *begin_y*begin_dx*begin_dy + -0.111422 *begin_x*lens_ipow(begin_dy, 2) + -0.192698 *begin_x*lens_ipow(begin_dx, 2) + -0.000294599 *begin_x*lens_ipow(begin_y, 2) + -0.000304391 *lens_ipow(begin_x, 3) + -8.35927e-07 *begin_x*lens_ipow(begin_y, 4) + -1.72004e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 9.98088e-06 *lens_ipow(begin_x, 4)*begin_dx + -7.28996e-07 *lens_ipow(begin_x, 5) + 0.00027559 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy;
  pred_y =  + 27.7726 *begin_dy + 0.18399 *begin_y + 1.41182 *begin_dy*begin_lambda + 0.102705 *begin_y*begin_lambda + -15.1198 *lens_ipow(begin_dy, 3) + -15.2185 *lens_ipow(begin_dx, 2)*begin_dy + -0.000388737 *lens_ipow(begin_y, 3) + -0.000298172 *lens_ipow(begin_x, 2)*begin_y + -0.337615 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.2008 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.160158 *begin_x*begin_dx*begin_dy*begin_lambda + 1.10863e-05 *lens_ipow(begin_y, 4)*begin_dy + -1.73492e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -8.06362e-07 *lens_ipow(begin_x, 4)*begin_y + -1.64839e-09 *lens_ipow(begin_y, 7) + 0.000257524 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2);
  pred_dx =  + 0.400723 *begin_dx + -0.0340827 *begin_x + 0.00505201 *begin_x*begin_lambda + -0.498788 *begin_dx*lens_ipow(begin_dy, 2) + -0.503882 *lens_ipow(begin_dx, 3) + -0.0232404 *begin_y*begin_dx*begin_dy + -0.0120929 *begin_x*lens_ipow(begin_dy, 2) + -0.0355752 *begin_x*lens_ipow(begin_dx, 2) + 0.000406518 *begin_x*begin_y*begin_dy + -1.40543e-05 *begin_x*lens_ipow(begin_y, 2) + -2.5159e-05 *lens_ipow(begin_x, 3) + -7.4543e-08 *begin_x*lens_ipow(begin_y, 4) + 2.64878e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -1.22759e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 2.30025e-06 *lens_ipow(begin_x, 4)*begin_dx + -1.06895e-10 *lens_ipow(begin_x, 7);
  pred_dy =  + 0.399397 *begin_dy + -0.0339432 *begin_y + 0.0051504 *begin_y*begin_lambda + -0.499045 *lens_ipow(begin_dy, 3) + -0.508372 *lens_ipow(begin_dx, 2)*begin_dy + -0.0352836 *begin_y*lens_ipow(begin_dy, 2) + -0.0127479 *begin_y*lens_ipow(begin_dx, 2) + -2.63067e-05 *lens_ipow(begin_y, 3) + -0.0239076 *begin_x*begin_dx*begin_dy + -3.0718e-05 *lens_ipow(begin_x, 2)*begin_y + 2.67869e-06 *lens_ipow(begin_y, 4)*begin_dy + 2.36667e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -8.09353e-11 *lens_ipow(begin_y, 7) + -4.03178e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 2.40745e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + 1.54944e-08 *lens_ipow(begin_x, 5)*begin_y*begin_dx;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 27.5808  + 1.76587 *begin_lambda + -15.2207 *lens_ipow(begin_dy, 2) + -45.4557 *lens_ipow(begin_dx, 2) + -0.0879496 *begin_y*begin_dy + -0.385395 *begin_x*begin_dx + 9.98088e-06 *lens_ipow(begin_x, 4) + 0.000551179 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy+0.0f;
  dx1_domega0(0, 1) =  + -30.4413 *begin_dx*begin_dy + -0.0879496 *begin_y*begin_dx + -0.222844 *begin_x*begin_dy + 0.00027559 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)+0.0f;
  dx1_domega0(1, 0) =  + -30.437 *begin_dx*begin_dy + -0.401601 *begin_y*begin_dx*begin_lambda + -0.160158 *begin_x*begin_dy*begin_lambda + 0.000257524 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)+0.0f;
  dx1_domega0(1, 1) =  + 27.7726  + 1.41182 *begin_lambda + -45.3593 *lens_ipow(begin_dy, 2) + -15.2185 *lens_ipow(begin_dx, 2) + -0.67523 *begin_y*begin_dy*begin_lambda + -0.160158 *begin_x*begin_dx*begin_lambda + 1.10863e-05 *lens_ipow(begin_y, 4) + 0.000515048 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy+0.0f;
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
