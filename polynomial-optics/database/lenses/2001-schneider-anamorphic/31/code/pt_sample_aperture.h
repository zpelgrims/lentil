case schneider_anamorphic_2001_31mm:
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
  pred_x =  + 38.6869 *begin_dx + 0.623429 *begin_x + -15.5632 *begin_dx*lens_ipow(begin_dy, 2) + -10.2649 *lens_ipow(begin_dx, 3) + -7.18963e-05 *lens_ipow(begin_x, 3) + -1.96893e-05 *lens_ipow(begin_y, 4)*begin_dx + -1.59481e-06 *begin_x*lens_ipow(begin_y, 4) + -0.00121203 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.250188 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000748826 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3) + -5.62142e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -5.0424e-05 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2) + -1.23857e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -1.02029e-06 *lens_ipow(begin_x, 6)*begin_dx + -6.44904e-09 *lens_ipow(begin_x, 7) + -6.40073e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dy*begin_lambda + 0.00185366 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -9.86971e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dy*begin_lambda;
  pred_y =  + 37.2224 *begin_dy + 0.599597 *begin_y + 1.83247 *begin_dy*begin_lambda + 0.0442879 *begin_y*begin_lambda + -9.07413e-05 *lens_ipow(begin_y, 3) + -58.6984 *lens_ipow(begin_dy, 5) + -217.082 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -1.6474e-06 *lens_ipow(begin_x, 4)*begin_y + -2.10924e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -6.37569e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + -7.22385e-07 *lens_ipow(begin_y, 6)*begin_dy + -5.35111e-09 *lens_ipow(begin_y, 7) + 3.92133e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy + -9.74215e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -5.47593e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + -3.10257e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dx + 0.00476083 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -6.4367e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dx*begin_lambda;
  pred_dx =  + 0.219524 *begin_dx + -0.0219672 *begin_x + 0.000269331 *lens_ipow(begin_y, 2)*begin_dx + -1.2613e-05 *lens_ipow(begin_x, 3) + -3.75861e-06 *lens_ipow(begin_y, 4)*begin_dx + -1.269e-07 *begin_x*lens_ipow(begin_y, 4) + -2.46519e-06 *lens_ipow(begin_x, 4)*begin_dx + 0.5445 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.0471803 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.000885637 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + -1.9291e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -4.77659e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -1.99425e-10 *lens_ipow(begin_x, 7) + -4.69614 *lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 3) + -1.56897e-06 *lens_ipow(begin_y, 5)*begin_dx*begin_dy*begin_lambda + -5.47469e-08 *begin_x*lens_ipow(begin_y, 5)*begin_dy*begin_lambda + -1.67569e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2)*begin_lambda + -3.85454e-08 *lens_ipow(begin_x, 6)*begin_dx*begin_lambda;
  pred_dy =  + 0.227531 *begin_dy + -0.0236691 *begin_y + 0.00281601 *begin_y*begin_lambda + -0.265699 *lens_ipow(begin_dy, 3) + -0.026078 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.00878765 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.00059136 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -1.35623e-05 *lens_ipow(begin_y, 4)*begin_dy + -1.15776e-07 *lens_ipow(begin_y, 5) + -0.00305004 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -1.45868e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -8.28982e-08 *lens_ipow(begin_x, 4)*begin_y + 0.0269015 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -1.26265e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 0.975691 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000412294 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -3.52237e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + -1.31084e-08 *lens_ipow(begin_x, 5)*begin_y*begin_dx;
  Eigen::Matrix2f dx1_domega0;
  dx1_domega0(0, 0) =  + 38.6869  + -15.5632 *lens_ipow(begin_dy, 2) + -30.7948 *lens_ipow(begin_dx, 2) + -1.96893e-05 *lens_ipow(begin_y, 4) + 0.250188 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.00224648 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -5.62142e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -0.000100848 *lens_ipow(begin_x, 5)*begin_dx + -1.02029e-06 *lens_ipow(begin_x, 6) + 0.00370733 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy*begin_lambda+0.0f;
  dx1_domega0(0, 1) =  + -31.1265 *begin_dx*begin_dy + -0.00242406 *lens_ipow(begin_x, 3)*begin_dy + 0.500376 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -6.40073e-07 *begin_x*lens_ipow(begin_y, 5)*begin_lambda + 0.00185366 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -9.86971e-07 *lens_ipow(begin_x, 5)*begin_y*begin_lambda+0.0f;
  dx1_domega0(1, 0) =  + -434.165 *begin_dx*lens_ipow(begin_dy, 3) + -1.27514e-05 *lens_ipow(begin_y, 5)*begin_dx + 3.92133e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dy + -3.10257e-07 *lens_ipow(begin_x, 5)*begin_y + 0.00476083 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -6.4367e-07 *begin_x*lens_ipow(begin_y, 5)*begin_lambda+0.0f;
  dx1_domega0(1, 1) =  + 37.2224  + 1.83247 *begin_lambda + -293.492 *lens_ipow(begin_dy, 4) + -651.247 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.21849e-05 *lens_ipow(begin_y, 5)*begin_dy + -7.22385e-07 *lens_ipow(begin_y, 6) + 3.92133e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -5.47593e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 0.00952165 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda+0.0f;
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
