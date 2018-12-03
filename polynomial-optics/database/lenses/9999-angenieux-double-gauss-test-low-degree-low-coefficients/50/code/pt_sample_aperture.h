case angenieux_double_gauss_test_low_degree_low_coefficients_9999_50mm:
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
  pred_x =  + 28.2028 *begin_dx + 0.195015 *begin_x + 1.80203 *begin_dx*begin_lambda + 0.0827779 *begin_x*begin_lambda + -15.9536 *begin_dx*lens_ipow(begin_dy, 2) + -15.9163 *lens_ipow(begin_dx, 3) + -0.107283 *begin_y*begin_dx*begin_dy + -0.115813 *begin_x*lens_ipow(begin_dy, 2) + -0.223652 *begin_x*lens_ipow(begin_dx, 2) + -0.000287134 *begin_x*lens_ipow(begin_y, 2) + -0.000307077 *lens_ipow(begin_x, 3) + -7.82062e-07 *begin_x*lens_ipow(begin_y, 4) + -1.5295e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -6.97961e-07 *lens_ipow(begin_x, 5);
  pred_y =  + 28.218 *begin_dy + 0.194886 *begin_y + 1.77846 *begin_dy*begin_lambda + 0.0825992 *begin_y*begin_lambda + -15.9435 *lens_ipow(begin_dy, 3) + -15.9016 *lens_ipow(begin_dx, 2)*begin_dy + -0.223052 *begin_y*lens_ipow(begin_dy, 2) + -0.11646 *begin_y*lens_ipow(begin_dx, 2) + -0.000301214 *lens_ipow(begin_y, 3) + -0.106337 *begin_x*begin_dx*begin_dy + -0.000288825 *lens_ipow(begin_x, 2)*begin_y + -7.18236e-07 *lens_ipow(begin_y, 5) + -1.55876e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -7.59872e-07 *lens_ipow(begin_x, 4)*begin_y;
  pred_dx =  + 0.40557 *begin_dx + -0.0353125 *begin_x + 0.00499552 *begin_x*begin_lambda + -0.461261 *begin_dx*lens_ipow(begin_dy, 2) + -0.52045 *lens_ipow(begin_dx, 3) + -0.0195668 *begin_y*begin_dx*begin_dy + -0.0247944 *begin_x*lens_ipow(begin_dx, 2) + 0.000520086 *begin_x*begin_y*begin_dy + -9.68896e-08 *begin_x*lens_ipow(begin_y, 4) + 3.83156e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -7.88691e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -0.000146101 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.53932e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -8.77968e-08 *lens_ipow(begin_x, 5);
  pred_dy =  + 0.406097 *begin_dy + -0.0352615 *begin_y + 0.00498467 *begin_y*begin_lambda + -0.525395 *lens_ipow(begin_dy, 3) + -0.467097 *lens_ipow(begin_dx, 2)*begin_dy + -0.0256105 *begin_y*lens_ipow(begin_dy, 2) + -0.0198376 *begin_x*begin_dx*begin_dy + 0.000518584 *begin_x*begin_y*begin_dx + -0.000141194 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -8.08001e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -8.90227e-08 *lens_ipow(begin_y, 5) + 3.84254e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -1.5477e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -9.64654e-08 *lens_ipow(begin_x, 4)*begin_y;
  Eigen::Matrix2f dx1_domega0;
  dx1_domega0(0, 0) =  + 28.2028  + 1.80203 *begin_lambda + -15.9536 *lens_ipow(begin_dy, 2) + -47.749 *lens_ipow(begin_dx, 2) + -0.107283 *begin_y*begin_dy + -0.447305 *begin_x*begin_dx+0.0f;
  dx1_domega0(0, 1) =  + -31.9073 *begin_dx*begin_dy + -0.107283 *begin_y*begin_dx + -0.231626 *begin_x*begin_dy+0.0f;
  dx1_domega0(1, 0) =  + -31.8032 *begin_dx*begin_dy + -0.23292 *begin_y*begin_dx + -0.106337 *begin_x*begin_dy+0.0f;
  dx1_domega0(1, 1) =  + 28.218  + 1.77846 *begin_lambda + -47.8306 *lens_ipow(begin_dy, 2) + -15.9016 *lens_ipow(begin_dx, 2) + -0.446103 *begin_y*begin_dy + -0.106337 *begin_x*begin_dx+0.0f;
  Eigen::Matrix2f invJ;
  const float invdet = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
  invJ(0, 0) =  dx1_domega0(1, 1)*invdet;
  invJ(1, 1) =  dx1_domega0(0, 0)*invdet;
  invJ(0, 1) = -dx1_domega0(0, 1)*invdet;
  invJ(1, 0) = -dx1_domega0(1, 0)*invdet;
  const std::vector<float> dx1 = {out_x - pred_x, out_y - pred_y};
  for(int i=0;i<2;i++)
  {
    dx += invJ(0, i)*dx1[i];
    dy += invJ(1, i)*dx1[i];
  }
  sqr_err = dx1[0]*dx1[0] + dx1[1]*dx1[1];
}
out_dx = pred_dx;
out_dy = pred_dy;
} break;
