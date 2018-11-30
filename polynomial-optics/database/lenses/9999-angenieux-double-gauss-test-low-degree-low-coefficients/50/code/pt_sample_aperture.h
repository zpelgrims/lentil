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
  pred_x =  + 28.196 *begin_dx + 0.198375 *begin_x + 1.80766 *begin_dx*begin_lambda + 0.0827756 *begin_x*begin_lambda + -15.8914 *begin_dx*lens_ipow(begin_dy, 2) + -15.9078 *lens_ipow(begin_dx, 3) + -0.108256 *begin_y*begin_dx*begin_dy + -0.115596 *begin_x*lens_ipow(begin_dy, 2) + -0.22334 *begin_x*lens_ipow(begin_dx, 2) + -0.000452834 *begin_x*lens_ipow(begin_y, 2) + -0.000338389 *lens_ipow(begin_x, 3) + -6.4402e-07 *lens_ipow(begin_x, 5) + -6.25986e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -2.06068e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2);
  pred_y =  + 28.218 *begin_dy + 0.194886 *begin_y + 1.77846 *begin_dy*begin_lambda + 0.0825992 *begin_y*begin_lambda + -15.9435 *lens_ipow(begin_dy, 3) + -15.9016 *lens_ipow(begin_dx, 2)*begin_dy + -0.223052 *begin_y*lens_ipow(begin_dy, 2) + -0.11646 *begin_y*lens_ipow(begin_dx, 2) + -0.000301214 *lens_ipow(begin_y, 3) + -0.106337 *begin_x*begin_dx*begin_dy + -0.000288825 *lens_ipow(begin_x, 2)*begin_y + -7.18236e-07 *lens_ipow(begin_y, 5) + -1.55876e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -7.59872e-07 *lens_ipow(begin_x, 4)*begin_y;
  pred_dx =  + 0.41025 *begin_dx + -0.0327482 *begin_x + 0.0048542 *begin_x*begin_lambda + -0.563158 *begin_dx*lens_ipow(begin_dy, 2) + -0.558619 *lens_ipow(begin_dx, 3) + -0.0256088 *begin_y*begin_dx*begin_dy + -0.0135352 *begin_x*lens_ipow(begin_dy, 2) + -0.0389084 *begin_x*lens_ipow(begin_dx, 2) + -2.33245e-05 *begin_x*lens_ipow(begin_y, 2) + -2.96647e-05 *lens_ipow(begin_x, 3) + -6.10127e-08 *begin_x*lens_ipow(begin_y, 4) + 2.13655e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -4.15952e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 1.03474e-08 *lens_ipow(begin_x, 6)*begin_dx;
  pred_dy =  + 0.405052 *begin_dy + -0.032852 *begin_y + 0.00487978 *begin_y*begin_lambda + -0.521683 *lens_ipow(begin_dy, 3) + -0.53768 *lens_ipow(begin_dx, 2)*begin_dy + -0.0358763 *begin_y*lens_ipow(begin_dy, 2) + -0.012325 *begin_y*lens_ipow(begin_dx, 2) + -2.9703e-05 *lens_ipow(begin_y, 3) + -0.0249135 *begin_x*begin_dx*begin_dy + 0.000303941 *begin_x*begin_y*begin_dx + -2.12213e-05 *lens_ipow(begin_x, 2)*begin_y + 2.44503e-06 *lens_ipow(begin_y, 4)*begin_dy + -6.0778e-08 *lens_ipow(begin_x, 4)*begin_y + -4.99108e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5);
  Eigen::Matrix2f dx1_domega0;
  dx1_domega0(0, 0) =  + 28.196  + 1.80766 *begin_lambda + -15.8914 *lens_ipow(begin_dy, 2) + -47.7235 *lens_ipow(begin_dx, 2) + -0.108256 *begin_y*begin_dy + -0.44668 *begin_x*begin_dx+0.0f;
  dx1_domega0(0, 1) =  + -31.7828 *begin_dx*begin_dy + -0.108256 *begin_y*begin_dx + -0.231192 *begin_x*begin_dy+0.0f;
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
