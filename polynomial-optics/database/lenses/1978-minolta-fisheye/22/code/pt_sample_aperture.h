case minolta__fisheye__1978__22mm:
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
  pred_x =  + 51.0305 *begin_dx + 0.733929 *begin_x + -1.48794 *begin_dx*begin_lambda + -0.0326085 *begin_x*begin_lambda + 87.127 *lens_ipow(begin_dx, 3) + 4.36432 *begin_x*lens_ipow(begin_dx, 2) + 0.000116309 *begin_x*lens_ipow(begin_y, 2) + 0.0649506 *lens_ipow(begin_x, 2)*begin_dx + 0.000279019 *lens_ipow(begin_x, 3) + 243.947 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 9.57984 *begin_y*begin_dx*begin_dy*begin_lambda + 0.100881 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 3.00329 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.106223 *begin_x*begin_y*begin_dy*begin_lambda + 0.000408303 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.0912152 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -262.888 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -13.3903 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -3.23379 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.11432 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 4.03962 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + -0.000573832 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 4);
  pred_y =  + 51.028 *begin_dy + 0.733959 *begin_y + -1.48445 *begin_dy*begin_lambda + -0.0327609 *begin_y*begin_lambda + 87.2516 *lens_ipow(begin_dy, 3) + 4.37067 *begin_y*lens_ipow(begin_dy, 2) + 0.0650749 *lens_ipow(begin_y, 2)*begin_dy + 0.000279958 *lens_ipow(begin_y, 3) + 0.0136364 *lens_ipow(begin_x, 2)*begin_dy + 0.000250551 *lens_ipow(begin_x, 2)*begin_y + 326.528 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 4.01016 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 12.349 *begin_x*begin_dx*begin_dy*begin_lambda + 0.142015 *begin_x*begin_y*begin_dx*begin_lambda + 0.0382774 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -298.312 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -3.65448 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -11.2652 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.129422 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.000179597 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 2) + -0.0419115 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -0.000404068 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 5);
  pred_dx =  + -0.573366 *begin_dx + -0.0277402 *begin_x + -0.124679 *begin_dx*begin_lambda + -0.0024019 *begin_x*begin_lambda + -0.923432 *begin_dx*lens_ipow(begin_dy, 2) + -1.03384 *lens_ipow(begin_dx, 3) + 0.0341049 *begin_y*begin_dx*begin_dy + 0.000426648 *lens_ipow(begin_y, 2)*begin_dx + 0.0269963 *begin_x*lens_ipow(begin_dy, 2) + 0.0598293 *begin_x*lens_ipow(begin_dx, 2) + 0.00151506 *begin_x*begin_y*begin_dy + 9.9866e-06 *begin_x*lens_ipow(begin_y, 2) + 0.00195653 *lens_ipow(begin_x, 2)*begin_dx + 1.00318e-05 *lens_ipow(begin_x, 3) + -8.10037 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.149428 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.0018353 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.285124 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00525264 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -2.03559e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -4.65976e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.0126913 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda;
  pred_dy =  + -0.464996 *begin_dy + -0.0257295 *begin_y + -0.510045 *begin_dy*begin_lambda + -0.00968482 *begin_y*begin_lambda + 0.346828 *begin_dy*lens_ipow(begin_lambda, 2) + -1.1762 *lens_ipow(begin_dy, 3) + -1.18866 *lens_ipow(begin_dx, 2)*begin_dy + 0.00659297 *begin_y*lens_ipow(begin_lambda, 2) + 0.0540254 *begin_y*lens_ipow(begin_dy, 2) + 0.0246594 *begin_y*lens_ipow(begin_dx, 2) + 0.00187123 *lens_ipow(begin_y, 2)*begin_dy + 9.61803e-06 *lens_ipow(begin_y, 3) + 0.0318267 *begin_x*begin_dx*begin_dy + 0.00152576 *begin_x*begin_y*begin_dx + 0.000400007 *lens_ipow(begin_x, 2)*begin_dy + 9.87151e-06 *lens_ipow(begin_x, 2)*begin_y + -0.00111442 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.102437 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.00147252 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -4.56616e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.0425594 *begin_x*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -0.000882806 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_lambda;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 51.0305  + -1.48794 *begin_lambda + 261.381 *lens_ipow(begin_dx, 2) + 8.72865 *begin_x*begin_dx + 0.0649506 *lens_ipow(begin_x, 2) + 243.947 *lens_ipow(begin_dy, 2)*begin_lambda + 9.57984 *begin_y*begin_dy*begin_lambda + 0.100881 *lens_ipow(begin_y, 2)*begin_lambda + -0.0912152 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -262.888 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -13.3903 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 4.03962 *begin_y*begin_dy*lens_ipow(begin_lambda, 4)+0.0f;
  dx1_domega0(0, 1) =  + 487.894 *begin_dx*begin_dy*begin_lambda + 9.57984 *begin_y*begin_dx*begin_lambda + 6.00657 *begin_x*begin_dy*begin_lambda + 0.106223 *begin_x*begin_y*begin_lambda + -525.775 *begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -13.3903 *begin_y*begin_dx*lens_ipow(begin_lambda, 3) + -6.46758 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -0.11432 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 4.03962 *begin_y*begin_dx*lens_ipow(begin_lambda, 4)+0.0f;
  dx1_domega0(1, 0) =  + 653.056 *begin_dx*begin_dy*begin_lambda + 8.02031 *begin_y*begin_dx*begin_lambda + 12.349 *begin_x*begin_dy*begin_lambda + 0.142015 *begin_x*begin_y*begin_lambda + -596.625 *begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -7.30895 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -11.2652 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.129422 *begin_x*begin_y*lens_ipow(begin_lambda, 2)+0.0f;
  dx1_domega0(1, 1) =  + 51.028  + -1.48445 *begin_lambda + 261.755 *lens_ipow(begin_dy, 2) + 8.74133 *begin_y*begin_dy + 0.0650749 *lens_ipow(begin_y, 2) + 0.0136364 *lens_ipow(begin_x, 2) + 326.528 *lens_ipow(begin_dx, 2)*begin_lambda + 12.349 *begin_x*begin_dx*begin_lambda + 0.0382774 *lens_ipow(begin_x, 2)*begin_lambda + -298.312 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -11.2652 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.0419115 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3)+0.0f;
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
