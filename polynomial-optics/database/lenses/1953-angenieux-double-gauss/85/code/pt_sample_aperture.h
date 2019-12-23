case angenieux__double_gauss__1953__85mm:
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
  pred_x =  + 45.5498 *begin_dx + 0.151196 *begin_x + 0.273694 *begin_x*begin_lambda + 11.6248 *begin_dx*begin_lambda + -8.01172 *begin_dx*lens_ipow(begin_lambda, 2) + -0.000142485 *lens_ipow(begin_x, 3) + -0.176638 *begin_x*lens_ipow(begin_dx, 2) + -0.0284183 *begin_y*begin_dx*begin_dy + -0.15572 *begin_x*lens_ipow(begin_dy, 2) + -28.2318 *lens_ipow(begin_dx, 3) + -0.188388 *begin_x*lens_ipow(begin_lambda, 2) + -26.1766 *begin_dx*lens_ipow(begin_dy, 2) + -0.000123348 *begin_x*lens_ipow(begin_y, 2) + 0.00259477 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.0104329 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 11.9638 *lens_ipow(begin_dx, 5) + 0.215298 *begin_x*lens_ipow(begin_dy, 4) + 0.0115168 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -8.00724e-08 *begin_x*lens_ipow(begin_y, 4) + -0.0225047 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.000414222 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + -3.63043e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 107.131 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 1.18347 *begin_x*lens_ipow(begin_dx, 6)*begin_lambda;
  pred_y =  + 0.152609 *begin_y + 45.3785 *begin_dy + 11.7108 *begin_dy*begin_lambda + 0.272013 *begin_y*begin_lambda + -0.186622 *begin_y*lens_ipow(begin_lambda, 2) + -0.161807 *begin_y*lens_ipow(begin_dx, 2) + -27.5264 *lens_ipow(begin_dy, 3) + -0.200653 *begin_y*lens_ipow(begin_dy, 2) + -8.01158 *begin_dy*lens_ipow(begin_lambda, 2) + -0.00014469 *lens_ipow(begin_y, 3) + -0.0419784 *begin_x*begin_dx*begin_dy + 0.00148334 *lens_ipow(begin_y, 2)*begin_dy + -25.607 *lens_ipow(begin_dx, 2)*begin_dy + 0.00121585 *lens_ipow(begin_x, 2)*begin_dy + -0.000143192 *lens_ipow(begin_x, 2)*begin_y + 11.3829 *lens_ipow(begin_dy, 5) + -0.00748748 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.260173 *begin_y*lens_ipow(begin_dy, 4) + -0.00563263 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.016367 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.208047 *begin_y*lens_ipow(begin_dx, 4) + 3.05906 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 130.888 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -1.25884e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5);
  pred_dx =  + 0.397709 *begin_dx + -0.0208989 *begin_x + 0.0081748 *begin_x*begin_lambda + -4.58474e-06 *lens_ipow(begin_x, 3) + -0.0167667 *begin_x*lens_ipow(begin_dx, 2) + -0.0117403 *begin_y*begin_dx*begin_dy + -0.00680048 *begin_x*lens_ipow(begin_dy, 2) + -0.495453 *lens_ipow(begin_dx, 3) + -0.00578456 *begin_x*lens_ipow(begin_lambda, 2) + -0.484623 *begin_dx*lens_ipow(begin_dy, 2) + 8.37626e-05 *lens_ipow(begin_x, 2)*begin_dx + -4.6092e-06 *begin_x*lens_ipow(begin_y, 2) + 8.17495e-05 *begin_x*begin_y*begin_dy + -1.1966e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.00538987 *begin_x*lens_ipow(begin_dy, 4) + 0.000316299 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.48989e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + 9.64221e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -2.67321e-08 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 8.37332e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -2.91935e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2) + -0.0246728 *begin_x*lens_ipow(begin_dx, 6) + -0.000548026 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -3.37626e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 2);
  pred_dy =  + -0.0208668 *begin_y + 0.397742 *begin_dy + 0.00821603 *begin_y*begin_lambda + -0.00581897 *begin_y*lens_ipow(begin_lambda, 2) + -0.00704051 *begin_y*lens_ipow(begin_dx, 2) + -0.495179 *lens_ipow(begin_dy, 3) + -0.016861 *begin_y*lens_ipow(begin_dy, 2) + -4.84118e-06 *lens_ipow(begin_y, 3) + -0.0116788 *begin_x*begin_dx*begin_dy + 8.43729e-05 *lens_ipow(begin_y, 2)*begin_dy + 7.79295e-05 *begin_x*begin_y*begin_dx + -0.489982 *lens_ipow(begin_dx, 2)*begin_dy + -4.66735e-06 *lens_ipow(begin_x, 2)*begin_y + -1.14572e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.000303151 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00500173 *begin_y*lens_ipow(begin_dx, 4) + 1.47732e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -0.0240695 *begin_y*lens_ipow(begin_dy, 6) + -2.47648e-08 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + 1.01335e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -2.7792e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + 9.57905e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 5.97397e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 4)*begin_dy + -0.887715 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5)*begin_lambda;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 45.5498  + 11.6248 *begin_lambda + -8.01172 *lens_ipow(begin_lambda, 2) + -0.353275 *begin_x*begin_dx + -0.0284183 *begin_y*begin_dy + -84.6954 *lens_ipow(begin_dx, 2) + -26.1766 *lens_ipow(begin_dy, 2) + 0.00259477 *lens_ipow(begin_x, 2)*begin_lambda + 0.0104329 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 59.8189 *lens_ipow(begin_dx, 4) + 0.0230336 *begin_x*begin_y*begin_dx*begin_dy + -0.0225047 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.000414222 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 321.394 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 7.10084 *begin_x*lens_ipow(begin_dx, 5)*begin_lambda+0.0f;
  dx1_domega0(0, 1) =  + -0.0284183 *begin_y*begin_dx + -0.31144 *begin_x*begin_dy + -52.3531 *begin_dx*begin_dy + 0.0208658 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.86119 *begin_x*lens_ipow(begin_dy, 3) + 0.0115168 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -0.0450094 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda + -0.000414222 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + 428.525 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)+0.0f;
  dx1_domega0(1, 0) =  + -0.323614 *begin_y*begin_dx + -0.0419784 *begin_x*begin_dy + -51.2139 *begin_dx*begin_dy + -0.014975 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.016367 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.832187 *begin_y*lens_ipow(begin_dx, 3) + 12.2362 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 523.553 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)+0.0f;
  dx1_domega0(1, 1) =  + 45.3785  + 11.7108 *begin_lambda + -82.5792 *lens_ipow(begin_dy, 2) + -0.401306 *begin_y*begin_dy + -8.01158 *lens_ipow(begin_lambda, 2) + -0.0419784 *begin_x*begin_dx + 0.00148334 *lens_ipow(begin_y, 2) + -25.607 *lens_ipow(begin_dx, 2) + 0.00121585 *lens_ipow(begin_x, 2) + 56.9146 *lens_ipow(begin_dy, 4) + -0.00748748 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.04069 *begin_y*lens_ipow(begin_dy, 3) + -0.0168979 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.0327341 *begin_x*begin_y*begin_dx*begin_dy + 6.11812 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + 392.665 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)+0.0f;
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
