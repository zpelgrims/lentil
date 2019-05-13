case unsure_fisheye_1954_0mm:
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
  pred_x =  + 0.707004 *begin_x + 23.4208 *begin_dx + -0.00188551 *begin_x*lens_ipow(begin_y, 2) + -0.00208898 *lens_ipow(begin_x, 3) + 0.776572 *begin_dx*lens_ipow(begin_lambda, 2) + -0.201269 *begin_x*begin_y*begin_dy + -6.30137 *begin_x*lens_ipow(begin_dx, 2) + -0.19824 *lens_ipow(begin_x, 2)*begin_dx + -6.72922 *begin_x*lens_ipow(begin_dy, 2) + 1.56629e-06 *lens_ipow(begin_x, 5) + 0.0108101 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 6.92983e-07 *lens_ipow(begin_x, 5)*begin_lambda + -0.000156886 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 6.6599e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dy + 2.46488e-06 *lens_ipow(begin_x, 5)*begin_y*begin_dy + 1.09629e-06 *lens_ipow(begin_x, 6)*begin_dx;
  pred_y =  + 22.3736 *begin_dy + 0.682822 *begin_y + -0.146057 *begin_x*begin_y*begin_dx + -3.16666 *begin_y*lens_ipow(begin_dx, 2) + -0.0015248 *lens_ipow(begin_x, 2)*begin_y + -0.00154583 *lens_ipow(begin_y, 3) + -5.31451 *begin_y*lens_ipow(begin_dy, 2) + -0.159127 *lens_ipow(begin_y, 2)*begin_dy + 90.0535 *lens_ipow(begin_dx, 2)*begin_dy + -0.995533 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000149752 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000110497 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 8.61306e-07 *lens_ipow(begin_y, 6)*begin_dy + 2.51578e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 2.34229e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + 6.82711e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dx;
  pred_dx =  + -0.0319212 *begin_x + -0.000812328 *begin_x*lens_ipow(begin_y, 2) + 94.8173 *lens_ipow(begin_dx, 3) + 119.055 *begin_dx*lens_ipow(begin_dy, 2) + -0.00102157 *lens_ipow(begin_x, 3) + -0.0852385 *begin_x*begin_y*begin_dy + -0.0905213 *lens_ipow(begin_x, 2)*begin_dx + 0.000182154 *lens_ipow(begin_x, 4)*begin_dx + -2381.26 *begin_dx*lens_ipow(begin_dy, 4) + 2.67578e-06 *lens_ipow(begin_x, 5) + 0.839644 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 4.12376e-09 *begin_x*lens_ipow(begin_y, 6) + -0.271093 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4) + -1.01855e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -6.78883e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 1.22357e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2);
  pred_dy =  + -0.027436 *begin_y + 0.170672 *begin_dy*begin_lambda + -0.0981654 *begin_x*begin_y*begin_dx + -2.45392 *begin_y*lens_ipow(begin_dx, 2) + -0.00104628 *lens_ipow(begin_x, 2)*begin_y + 116.775 *lens_ipow(begin_dy, 3) + -0.0009518 *lens_ipow(begin_y, 3) + -0.086071 *lens_ipow(begin_y, 2)*begin_dy + -0.200291 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 1.36866e-06 *lens_ipow(begin_x, 4)*begin_y + 2.95181e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -4.26505e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + 6.9997e-09 *lens_ipow(begin_y, 7) + -0.293993 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 0.00496394 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.0821351 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*begin_dy;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 23.4208  + 0.776572 *lens_ipow(begin_lambda, 2) + -12.6027 *begin_x*begin_dx + -0.19824 *lens_ipow(begin_x, 2) + -0.000313773 *begin_x*lens_ipow(begin_y, 4)*begin_dx + 1.09629e-06 *lens_ipow(begin_x, 6)+0.0f;
  dx1_domega0(0, 1) =  + -0.201269 *begin_x*begin_y + -13.4584 *begin_x*begin_dy + 0.0216202 *lens_ipow(begin_x, 3)*begin_dy*begin_lambda + 6.6599e-07 *begin_x*lens_ipow(begin_y, 5) + 2.46488e-06 *lens_ipow(begin_x, 5)*begin_y+0.0f;
  dx1_domega0(1, 0) =  + -0.146057 *begin_x*begin_y + -6.33332 *begin_y*begin_dx + 180.107 *begin_dx*begin_dy + 2.34229e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 6.82711e-07 *lens_ipow(begin_x, 5)*begin_y+0.0f;
  dx1_domega0(1, 1) =  + 22.3736  + -10.629 *begin_y*begin_dy + -0.159127 *lens_ipow(begin_y, 2) + 90.0535 *lens_ipow(begin_dx, 2) + -1.99107 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.000149752 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -0.000110497 *lens_ipow(begin_y, 4)*begin_lambda + 8.61306e-07 *lens_ipow(begin_y, 6) + 2.51578e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)+0.0f;
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
