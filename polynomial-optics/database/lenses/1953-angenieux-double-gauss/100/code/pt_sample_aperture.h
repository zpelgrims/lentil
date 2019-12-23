case angenieux_double_gauss_1953_100mm:
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
  pred_x =  + 51.0741 *begin_dx + 0.164957 *begin_x + 3.80311 *begin_dx*begin_lambda + -4.3292e-05 *lens_ipow(begin_y, 2) + 0.0746279 *begin_x*begin_lambda + -0.00255573 *begin_x*begin_dy;
  pred_y =  + 51.0449 *begin_dy + 0.172198 *begin_y + 3.92141 *begin_dy*begin_lambda + 0.0903945 *lens_ipow(begin_dy, 2) + 0.061443 *begin_y*begin_lambda + 0.00456087 *begin_y*begin_dy;
  pred_dx =  + 0.329504 *begin_dx + -0.0182912 *begin_x + -0.00244742 *lens_ipow(begin_dy, 2) + 0.0185914 *begin_dx*begin_lambda + 0.00185376 *begin_x*begin_lambda + -6.73609e-05 *begin_x*begin_dy;
  pred_dy =  + 0.000146546  + 0.331642 *begin_dy + -0.0182062 *begin_y + 0.0149156 *begin_dy*begin_lambda + 0.00170713 *begin_y*begin_lambda + 0.000104205 *begin_x*begin_dy;
  Eigen::Matrix2f dx1_domega0;
  dx1_domega0(0, 0) =  + 51.0741  + 3.80311 *begin_lambda+0.0f;
  dx1_domega0(0, 1) =  + -0.00255573 *begin_x+0.0f;
  dx1_domega0(1, 0) = +0.0f;
  dx1_domega0(1, 1) =  + 51.0449  + 3.92141 *begin_lambda + 0.180789 *begin_dy + 0.00456087 *begin_y+0.0f;
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
