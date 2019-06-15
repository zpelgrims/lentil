case angenieux__double_gauss__1953__105mm:
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
  pred_x =  + 56.3087 *begin_dx + 0.156651 *begin_x + 0.258755 *begin_x*begin_lambda + 14.0751 *begin_dx*begin_lambda + -9.73039 *begin_dx*lens_ipow(begin_lambda, 2) + -9.34163e-05 *lens_ipow(begin_x, 3) + -0.207774 *begin_x*lens_ipow(begin_dx, 2) + -0.0342282 *begin_y*begin_dx*begin_dy + -0.172519 *begin_x*lens_ipow(begin_dy, 2) + -34.9741 *lens_ipow(begin_dx, 3) + -0.176972 *begin_x*lens_ipow(begin_lambda, 2) + -34.8129 *begin_dx*lens_ipow(begin_dy, 2) + -9.4603e-05 *begin_x*lens_ipow(begin_y, 2) + 0.0010461 *lens_ipow(begin_y, 2)*begin_dx + 0.00211667 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.271262 *begin_x*lens_ipow(begin_dx, 4) + 15.1711 *begin_dx*lens_ipow(begin_dy, 4) + -0.00464763 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.52875 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 15.6367 *lens_ipow(begin_dx, 5) + 0.265624 *begin_x*lens_ipow(begin_dy, 4) + 0.0126243 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 31.0198 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.00918067 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda;
  pred_y =  + 0.156422 *begin_y + 56.3115 *begin_dy + 14.0711 *begin_dy*begin_lambda + 0.259668 *begin_y*begin_lambda + -0.17783 *begin_y*lens_ipow(begin_lambda, 2) + -0.17361 *begin_y*lens_ipow(begin_dx, 2) + -34.9925 *lens_ipow(begin_dy, 3) + -0.206411 *begin_y*lens_ipow(begin_dy, 2) + -9.72667 *begin_dy*lens_ipow(begin_lambda, 2) + -9.34083e-05 *lens_ipow(begin_y, 3) + -0.0345475 *begin_x*begin_dx*begin_dy + -34.7687 *lens_ipow(begin_dx, 2)*begin_dy + 0.00104257 *lens_ipow(begin_x, 2)*begin_dy + -9.44768e-05 *lens_ipow(begin_x, 2)*begin_y + 0.00210945 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 15.7303 *lens_ipow(begin_dy, 5) + 30.5478 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.266563 *begin_y*lens_ipow(begin_dy, 4) + -0.00464253 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 15.0222 *lens_ipow(begin_dx, 4)*begin_dy + 0.527253 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.012571 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.269931 *begin_y*lens_ipow(begin_dx, 4) + -0.00891039 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda;
  pred_dx =  + 0.399399 *begin_dx + -0.0167231 *begin_x + 0.00605479 *begin_x*begin_lambda + -2.60643e-06 *lens_ipow(begin_x, 3) + -0.0140089 *begin_x*lens_ipow(begin_dx, 2) + -0.00918629 *begin_y*begin_dx*begin_dy + -0.00545788 *begin_x*lens_ipow(begin_dy, 2) + -0.515856 *lens_ipow(begin_dx, 3) + -0.00422298 *begin_x*lens_ipow(begin_lambda, 2) + -0.502928 *begin_dx*lens_ipow(begin_dy, 2) + 5.26091e-05 *lens_ipow(begin_x, 2)*begin_dx + -3.25927e-06 *begin_x*lens_ipow(begin_y, 2) + 5.17145e-05 *begin_x*begin_y*begin_dy + 1.18659e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.00369565 *begin_x*lens_ipow(begin_dy, 4) + 2.97138e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 0.00127774 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -0.0635998 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 3.81812e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -1.81867e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4) + 1.01115 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 0.637442 *lens_ipow(begin_dx, 7)*begin_lambda + -5.59176e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 0.0071969 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 6)*begin_lambda;
  pred_dy =  + -0.0167441 *begin_y + 0.397923 *begin_dy + 0.00602849 *begin_y*begin_lambda + -0.00418466 *begin_y*lens_ipow(begin_lambda, 2) + -0.00551434 *begin_y*lens_ipow(begin_dx, 2) + -0.494299 *lens_ipow(begin_dy, 3) + -0.0136625 *begin_y*lens_ipow(begin_dy, 2) + -2.47332e-06 *lens_ipow(begin_y, 3) + -0.0093055 *begin_x*begin_dx*begin_dy + 5.20743e-05 *lens_ipow(begin_y, 2)*begin_dy + 4.97569e-05 *begin_x*begin_y*begin_dx + -0.492373 *lens_ipow(begin_dx, 2)*begin_dy + -2.41802e-06 *lens_ipow(begin_x, 2)*begin_y + -4.71815e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.000182971 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00396357 *begin_y*lens_ipow(begin_dx, 4) + 6.72087e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -9.45428e-09 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + 3.6068e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -1.09e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + 3.24394e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -0.0329447 *begin_y*lens_ipow(begin_dy, 6)*begin_lambda + 0.00414113 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 6)*begin_dy + -0.815668 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5)*begin_lambda;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 56.3087  + 14.0751 *begin_lambda + -9.73039 *lens_ipow(begin_lambda, 2) + -0.415548 *begin_x*begin_dx + -0.0342282 *begin_y*begin_dy + -104.922 *lens_ipow(begin_dx, 2) + -34.8129 *lens_ipow(begin_dy, 2) + 0.0010461 *lens_ipow(begin_y, 2) + 0.00211667 *lens_ipow(begin_x, 2)*begin_lambda + 1.08505 *begin_x*lens_ipow(begin_dx, 3) + 15.1711 *lens_ipow(begin_dy, 4) + -0.0139429 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.0575 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 78.1835 *lens_ipow(begin_dx, 4) + 0.0252486 *begin_x*begin_y*begin_dx*begin_dy + 93.0595 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00918067 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
  dx1_domega0(0, 1) =  + -0.0342282 *begin_y*begin_dx + -0.345039 *begin_x*begin_dy + -69.6257 *begin_dx*begin_dy + 60.6846 *begin_dx*lens_ipow(begin_dy, 3) + 1.0575 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.0625 *begin_x*lens_ipow(begin_dy, 3) + 0.0126243 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 62.0396 *lens_ipow(begin_dx, 3)*begin_dy + -0.0183613 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
  dx1_domega0(1, 0) =  + -0.347219 *begin_y*begin_dx + -0.0345475 *begin_x*begin_dy + -69.5374 *begin_dx*begin_dy + 61.0956 *begin_dx*lens_ipow(begin_dy, 3) + 60.0889 *lens_ipow(begin_dx, 3)*begin_dy + 1.05451 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.012571 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 1.07972 *begin_y*lens_ipow(begin_dx, 3) + -0.0178208 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
  dx1_domega0(1, 1) =  + 56.3115  + 14.0711 *begin_lambda + -104.977 *lens_ipow(begin_dy, 2) + -0.412823 *begin_y*begin_dy + -9.72667 *lens_ipow(begin_lambda, 2) + -0.0345475 *begin_x*begin_dx + -34.7687 *lens_ipow(begin_dx, 2) + 0.00104257 *lens_ipow(begin_x, 2) + 0.00210945 *lens_ipow(begin_y, 2)*begin_lambda + 78.6515 *lens_ipow(begin_dy, 4) + 91.6434 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.06625 *begin_y*lens_ipow(begin_dy, 3) + -0.0139276 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 15.0222 *lens_ipow(begin_dx, 4) + 1.05451 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0251419 *begin_x*begin_y*begin_dx*begin_dy + -0.00891039 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda+0.0f;
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
