case kodak__petzval__1948__58mm:
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
  pred_x =  + 44.4314 *begin_dx + 0.792291 *begin_x + 0.761035 *begin_dx*begin_lambda + -0.520161 *begin_dx*lens_ipow(begin_lambda, 2) + 1.38736 *begin_dx*lens_ipow(begin_dy, 2) + 0.556785 *begin_y*begin_dx*begin_dy + 0.00964987 *lens_ipow(begin_y, 2)*begin_dx + 0.14045 *begin_x*lens_ipow(begin_dy, 2) + 0.585192 *begin_x*lens_ipow(begin_dx, 2) + 0.0142849 *begin_x*begin_y*begin_dy + 0.000163413 *begin_x*lens_ipow(begin_y, 2) + 0.0200543 *lens_ipow(begin_x, 2)*begin_dx + 0.00012003 *lens_ipow(begin_x, 3) + 0.0477165 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.00351845 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 8.59177e-05 *lens_ipow(begin_x, 4)*begin_dx + 6.61567e-07 *lens_ipow(begin_x, 5) + 3.89879 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 4.29328e-09 *begin_x*lens_ipow(begin_y, 5)*begin_dy + -0.0719371 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -1.25176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.19167e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy;
  pred_y =  + 44.4236 *begin_dy + 0.792148 *begin_y + 0.776576 *begin_dy*begin_lambda + -0.526972 *begin_dy*lens_ipow(begin_lambda, 2) + 1.22909 *lens_ipow(begin_dx, 2)*begin_dy + 0.590742 *begin_y*lens_ipow(begin_dy, 2) + 0.143798 *begin_y*lens_ipow(begin_dx, 2) + 0.0203328 *lens_ipow(begin_y, 2)*begin_dy + 0.000125098 *lens_ipow(begin_y, 3) + 0.558886 *begin_x*begin_dx*begin_dy + 0.0146088 *begin_x*begin_y*begin_dx + 0.00977933 *lens_ipow(begin_x, 2)*begin_dy + 0.000168739 *lens_ipow(begin_x, 2)*begin_y + 0.0501801 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00357861 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 8.42457e-05 *lens_ipow(begin_y, 4)*begin_dy + 6.22491e-07 *lens_ipow(begin_y, 5) + 4.01293 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 1.39225e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -1.85259e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.07148e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -1.53597e-10 *lens_ipow(begin_x, 6)*begin_y*begin_lambda;
  pred_dx =  + 0.581262 *begin_dx + -0.0120733 *begin_x + -0.188563 *begin_dx*lens_ipow(begin_dy, 2) + -0.187812 *lens_ipow(begin_dx, 3) + 0.0157796 *begin_y*begin_dx*begin_dy + 0.000350991 *lens_ipow(begin_y, 2)*begin_dx + 0.00635476 *begin_x*lens_ipow(begin_dy, 2) + 0.0186098 *begin_x*lens_ipow(begin_dx, 2) + 0.000776513 *begin_x*begin_y*begin_dy + 9.42646e-06 *begin_x*lens_ipow(begin_y, 2) + 0.000991448 *lens_ipow(begin_x, 2)*begin_dx + 7.71999e-06 *lens_ipow(begin_x, 3) + -0.0276224 *lens_ipow(begin_dx, 3)*begin_lambda + 1.14239e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 4.48762e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 1.90122e-06 *lens_ipow(begin_x, 4)*begin_dx + 1.92299e-08 *lens_ipow(begin_x, 5) + 0.000374531 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -3.09718e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 6.20119e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -1.60602e-06 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 2) + -6.50098e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy;
  pred_dy =  + 0.581179 *begin_dy + -0.0120757 *begin_y + -0.184832 *lens_ipow(begin_dy, 3) + -0.188999 *lens_ipow(begin_dx, 2)*begin_dy + 0.0187917 *begin_y*lens_ipow(begin_dy, 2) + 0.00633935 *begin_y*lens_ipow(begin_dx, 2) + 0.000996438 *lens_ipow(begin_y, 2)*begin_dy + 7.77822e-06 *lens_ipow(begin_y, 3) + 0.0158122 *begin_x*begin_dx*begin_dy + 0.000776748 *begin_x*begin_y*begin_dx + 0.00035244 *lens_ipow(begin_x, 2)*begin_dy + 9.45879e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0286682 *lens_ipow(begin_dy, 3)*begin_lambda + 4.46051e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 1.8901e-06 *lens_ipow(begin_y, 4)*begin_dy + 1.90973e-08 *lens_ipow(begin_y, 5) + 1.1578e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -1.56633e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy + -6.4902e-08 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 0.000365088 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -3.00483e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 5.99372e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3);
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 44.4314  + 0.761035 *begin_lambda + -0.520161 *lens_ipow(begin_lambda, 2) + 1.38736 *lens_ipow(begin_dy, 2) + 0.556785 *begin_y*begin_dy + 0.00964987 *lens_ipow(begin_y, 2) + 1.17038 *begin_x*begin_dx + 0.0200543 *lens_ipow(begin_x, 2) + 0.14315 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.00703689 *lens_ipow(begin_x, 3)*begin_dx + 8.59177e-05 *lens_ipow(begin_x, 4) + 7.79758 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.215811 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.25176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -1.19167e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy+0.0f;
  dx1_domega0(0, 1) =  + 2.77472 *begin_dx*begin_dy + 0.556785 *begin_y*begin_dx + 0.2809 *begin_x*begin_dy + 0.0142849 *begin_x*begin_y + 15.5952 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 4.29328e-09 *begin_x*lens_ipow(begin_y, 5) + -0.143874 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_dy + -1.25176e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -1.19167e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx+0.0f;
  dx1_domega0(1, 0) =  + 2.45819 *begin_dx*begin_dy + 0.287596 *begin_y*begin_dx + 0.558886 *begin_x*begin_dy + 0.0146088 *begin_x*begin_y + 16.0517 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -1.85259e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy+0.0f;
  dx1_domega0(1, 1) =  + 44.4236  + 0.776576 *begin_lambda + -0.526972 *lens_ipow(begin_lambda, 2) + 1.22909 *lens_ipow(begin_dx, 2) + 1.18148 *begin_y*begin_dy + 0.0203328 *lens_ipow(begin_y, 2) + 0.558886 *begin_x*begin_dx + 0.00977933 *lens_ipow(begin_x, 2) + 0.15054 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.00715722 *lens_ipow(begin_y, 3)*begin_dy + 8.42457e-05 *lens_ipow(begin_y, 4) + 8.02585 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + 1.39225e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -1.85259e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 2.14296e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy*begin_lambda+0.0f;
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
