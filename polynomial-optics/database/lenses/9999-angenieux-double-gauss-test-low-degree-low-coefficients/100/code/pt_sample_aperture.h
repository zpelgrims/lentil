case angenieux_double_gauss_test_low_degree_low_coefficients_9999_100mm:
{
float pred_x;
float pred_y;
float pred_dx;
float pred_dy;
float sqr_err = FLT_MAX;
for(int k=0;k<5&&sqr_err > 1e-4f;k++)
{
  const float begin_x = x + dist * dx;
  const float begin_y = y + dist * dy;
  const float begin_dx = dx;
  const float begin_dy = dy;
  const float begin_lambda = lambda;
  pred_x =  + 53.5533 *begin_dx + 0.155085 *begin_x + 13.4794 *begin_dx*begin_lambda + 0.267639 *begin_x*begin_lambda + -9.22234 *begin_dx*lens_ipow(begin_lambda, 2) + -30.0121 *begin_dx*lens_ipow(begin_dy, 2) + -29.9178 *lens_ipow(begin_dx, 3) + -0.0761147 *begin_y*begin_dx*begin_dy + -0.185046 *begin_x*lens_ipow(begin_lambda, 2) + -0.159593 *begin_x*lens_ipow(begin_dy, 2) + -0.180895 *begin_x*lens_ipow(begin_dx, 2) + -0.000110295 *begin_x*lens_ipow(begin_y, 2) + -0.000107312 *lens_ipow(begin_x, 3) + 0.228388 *begin_x*lens_ipow(begin_dy, 4);
  pred_y =  + 53.5515 *begin_dy + 0.157591 *begin_y + 13.4912 *begin_dy*begin_lambda + 0.257999 *begin_y*begin_lambda + -9.22586 *begin_dy*lens_ipow(begin_lambda, 2) + -29.9556 *lens_ipow(begin_dy, 3) + -30.0292 *lens_ipow(begin_dx, 2)*begin_dy + -0.176885 *begin_y*lens_ipow(begin_lambda, 2) + -0.180369 *begin_y*lens_ipow(begin_dy, 2) + -0.155302 *begin_y*lens_ipow(begin_dx, 2) + -0.00010683 *lens_ipow(begin_y, 3) + -0.0759737 *begin_x*begin_dx*begin_dy + -0.000110405 *lens_ipow(begin_x, 2)*begin_y + 0.210395 *begin_y*lens_ipow(begin_dx, 4);
  pred_dx =  + 0.395899 *begin_dx + -0.0176487 *begin_x + 0.00674921 *begin_x*begin_lambda + -0.483532 *begin_dx*lens_ipow(begin_dy, 2) + -0.484063 *lens_ipow(begin_dx, 3) + -0.0106476 *begin_y*begin_dx*begin_dy + -0.00467207 *begin_x*lens_ipow(begin_lambda, 2) + -0.00495095 *begin_x*lens_ipow(begin_dy, 2) + -0.0152224 *begin_x*lens_ipow(begin_dx, 2) + 7.19631e-05 *begin_x*begin_y*begin_dy + -3.10925e-06 *begin_x*lens_ipow(begin_y, 2) + 7.15177e-05 *lens_ipow(begin_x, 2)*begin_dx + -3.29143e-06 *lens_ipow(begin_x, 3) + -4.64766e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2);
  pred_dy =  + 0.396038 *begin_dy + -0.0176122 *begin_y + 0.00661369 *begin_y*begin_lambda + -0.4848 *lens_ipow(begin_dy, 3) + -0.484217 *lens_ipow(begin_dx, 2)*begin_dy + -0.00454918 *begin_y*lens_ipow(begin_lambda, 2) + -0.0152456 *begin_y*lens_ipow(begin_dy, 2) + -0.00494986 *begin_y*lens_ipow(begin_dx, 2) + 7.04744e-05 *lens_ipow(begin_y, 2)*begin_dy + -3.28113e-06 *lens_ipow(begin_y, 3) + -0.0106545 *begin_x*begin_dx*begin_dy + 7.13093e-05 *begin_x*begin_y*begin_dx + -3.13122e-06 *lens_ipow(begin_x, 2)*begin_y + -4.54994e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2);
  Eigen::Matrix2f dx1_domega0;
  dx1_domega0(0, 0) =  + 53.5533  + 13.4794 *begin_lambda + -9.22234 *lens_ipow(begin_lambda, 2) + -30.0121 *lens_ipow(begin_dy, 2) + -89.7535 *lens_ipow(begin_dx, 2) + -0.0761147 *begin_y*begin_dy + -0.361791 *begin_x*begin_dx+0.0f;
  dx1_domega0(0, 1) =  + -60.0241 *begin_dx*begin_dy + -0.0761147 *begin_y*begin_dx + -0.319187 *begin_x*begin_dy + 0.913553 *begin_x*lens_ipow(begin_dy, 3)+0.0f;
  dx1_domega0(1, 0) =  + -60.0584 *begin_dx*begin_dy + -0.310604 *begin_y*begin_dx + -0.0759737 *begin_x*begin_dy + 0.841579 *begin_y*lens_ipow(begin_dx, 3)+0.0f;
  dx1_domega0(1, 1) =  + 53.5515  + 13.4912 *begin_lambda + -9.22586 *lens_ipow(begin_lambda, 2) + -89.8669 *lens_ipow(begin_dy, 2) + -30.0292 *lens_ipow(begin_dx, 2) + -0.360738 *begin_y*begin_dy + -0.0759737 *begin_x*begin_dx+0.0f;
  Eigen::Matrix2f invJ;
  const float invdet = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
  invJ(0, 0) =  dx1_domega0(1, 1)*invdet;
  invJ(1, 1) =  dx1_domega0(0, 0)*invdet;
  invJ(0, 1) = -dx1_domega0(0, 1)*invdet;
  invJ(1, 0) = -dx1_domega0(1, 0)*invdet;
  const Eigen::Vector2f dx1(out_x - pred_x, out_y - pred_y);
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
