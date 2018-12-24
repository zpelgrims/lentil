case angenieux_double_gauss_1953_49mm:
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
  pred_x =  + 27.6412 *begin_dx + 0.194212 *begin_x + 1.76473 *begin_dx*begin_lambda + 0.0836355 *begin_x*begin_lambda + -15.6427 *begin_dx*lens_ipow(begin_dy, 2) + -15.6168 *lens_ipow(begin_dx, 3) + -0.108718 *begin_y*begin_dx*begin_dy + -0.115429 *begin_x*lens_ipow(begin_dy, 2) + -0.224427 *begin_x*lens_ipow(begin_dx, 2) + -0.000294934 *begin_x*lens_ipow(begin_y, 2) + -0.000313961 *lens_ipow(begin_x, 3) + -8.60107e-07 *begin_x*lens_ipow(begin_y, 4) + -1.67653e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -7.78073e-07 *lens_ipow(begin_x, 5);
  pred_y =  + 27.8704 *begin_dy + 0.182264 *begin_y + 1.35479 *begin_dy*begin_lambda + 0.10441 *begin_y*begin_lambda + -15.6127 *lens_ipow(begin_dy, 3) + -15.596 *lens_ipow(begin_dx, 2)*begin_dy + -0.000308064 *lens_ipow(begin_y, 3) + -0.000297301 *lens_ipow(begin_x, 2)*begin_y + -0.397297 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.208492 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.190213 *begin_x*begin_dx*begin_dy*begin_lambda + -7.94038e-07 *lens_ipow(begin_y, 5) + -1.70633e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -8.30246e-07 *lens_ipow(begin_x, 4)*begin_y;
  pred_dx =  + 0.400532 *begin_dx + -0.0361616 *begin_x + 0.00518241 *begin_x*begin_lambda + -0.465621 *begin_dx*lens_ipow(begin_dy, 2) + -0.501443 *lens_ipow(begin_dx, 3) + -0.0203897 *begin_y*begin_dx*begin_dy + -0.0326008 *begin_x*lens_ipow(begin_dx, 2) + 0.00054533 *begin_x*begin_y*begin_dy + -1.02676e-07 *begin_x*lens_ipow(begin_y, 4) + 3.37346e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -8.43237e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -1.85072e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 2.71672e-06 *lens_ipow(begin_x, 4)*begin_dx + -8.72043e-08 *lens_ipow(begin_x, 5);
  pred_dy =  + 0.401117 *begin_dy + -0.0360984 *begin_y + 0.00512937 *begin_y*begin_lambda + -0.506095 *lens_ipow(begin_dy, 3) + -0.47239 *lens_ipow(begin_dx, 2)*begin_dy + -0.0330539 *begin_y*lens_ipow(begin_dy, 2) + -0.020712 *begin_x*begin_dx*begin_dy + 0.000536109 *begin_x*begin_y*begin_dx + -8.63369e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 2.67028e-06 *lens_ipow(begin_y, 4)*begin_dy + -8.78408e-08 *lens_ipow(begin_y, 5) + 3.23726e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -1.89979e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -1.00742e-07 *lens_ipow(begin_x, 4)*begin_y;
  Eigen::Matrix2f dx1_domega0;
  dx1_domega0(0, 0) =  + 27.6412  + 1.76473 *begin_lambda + -15.6427 *lens_ipow(begin_dy, 2) + -46.8504 *lens_ipow(begin_dx, 2) + -0.108718 *begin_y*begin_dy + -0.448854 *begin_x*begin_dx+0.0f;
  dx1_domega0(0, 1) =  + -31.2853 *begin_dx*begin_dy + -0.108718 *begin_y*begin_dx + -0.230859 *begin_x*begin_dy+0.0f;
  dx1_domega0(1, 0) =  + -31.192 *begin_dx*begin_dy + -0.416984 *begin_y*begin_dx*begin_lambda + -0.190213 *begin_x*begin_dy*begin_lambda+0.0f;
  dx1_domega0(1, 1) =  + 27.8704  + 1.35479 *begin_lambda + -46.838 *lens_ipow(begin_dy, 2) + -15.596 *lens_ipow(begin_dx, 2) + -0.794593 *begin_y*begin_dy*begin_lambda + -0.190213 *begin_x*begin_dx*begin_lambda+0.0f;
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
