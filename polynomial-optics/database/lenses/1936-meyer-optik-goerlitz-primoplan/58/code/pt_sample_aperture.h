case meyer-optik-goerlitz_primoplan_1936_58mm:
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
  pred_x =  + 35.8897 *begin_dx + 0.576039 *begin_x + 0.000685351 *lens_ipow(begin_x, 3) + 2.40303 *begin_x*lens_ipow(begin_dx, 2) + 1.49373 *begin_y*begin_dx*begin_dy + 0.739001 *begin_x*lens_ipow(begin_dy, 2) + 21.7389 *lens_ipow(begin_dx, 3) + 15.4411 *begin_dx*lens_ipow(begin_dy, 2) + 0.0744818 *lens_ipow(begin_x, 2)*begin_dx + 0.0484408 *begin_x*begin_y*begin_dy + 0.0011795 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0424157 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -8.13414e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.000121059 *lens_ipow(begin_x, 4)*begin_dx + 0.058664 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -3.75306e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.000130558 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.0910584 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -31.5165 *lens_ipow(begin_dx, 5) + -7.98964e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 0.119697 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -2.049e-06 *lens_ipow(begin_x, 5) + -3.43656e-06 *begin_x*lens_ipow(begin_y, 4)*begin_lambda + -0.000144558 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_lambda, 3);
  pred_y =  + 0.561308 *begin_y + 36.2185 *begin_dy + 0.04417 *begin_y*begin_lambda + 0.746089 *begin_y*lens_ipow(begin_dx, 2) + 16.272 *lens_ipow(begin_dy, 3) + 2.17322 *begin_y*lens_ipow(begin_dy, 2) + 0.000495692 *lens_ipow(begin_y, 3) + 1.15644 *begin_x*begin_dx*begin_dy + 0.0670934 *lens_ipow(begin_y, 2)*begin_dy + 0.0379861 *begin_x*begin_y*begin_dx + 0.0169686 *lens_ipow(begin_x, 2)*begin_dy + 0.000321073 *lens_ipow(begin_x, 2)*begin_y + 25.6135 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.00016958 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -2.93134e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.00198509 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -8.53176e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -6.01443e-09 *lens_ipow(begin_y, 7) + -7.85671e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -0.0123992 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -0.015491 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + -3.9393e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -1.05785e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -5.14074e-07 *lens_ipow(begin_y, 6)*begin_dy;
  pred_dx =  + 1.37106 *begin_dx + -0.00679193 *begin_x + -0.150105 *begin_dx*begin_lambda + 5.62629e-05 *lens_ipow(begin_x, 3) + 0.15385 *begin_x*lens_ipow(begin_dx, 2) + 0.0886328 *begin_y*begin_dx*begin_dy + 0.0525253 *begin_x*lens_ipow(begin_dy, 2) + 1.89161 *lens_ipow(begin_dx, 3) + 2.12187 *begin_dx*lens_ipow(begin_dy, 2) + 0.0056049 *lens_ipow(begin_x, 2)*begin_dx + 0.00302633 *begin_x*begin_y*begin_dy + 0.00170452 *lens_ipow(begin_y, 2)*begin_dx + 7.72769e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -6.19791e-06 *lens_ipow(begin_x, 4)*begin_dx + 0.00563151 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -1.17075e-07 *lens_ipow(begin_x, 5) + -7.36688e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + -5.33458e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.000831263 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.00406653 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 5) + 0.000269399 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -1.07721e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dx + -1.51421e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_dy + -5.47031e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4);
  pred_dy =  + 1.55946 *begin_dy + -0.202926 *begin_dy*begin_lambda + -0.00601762 *begin_y*begin_lambda + 0.0133623 *begin_y*lens_ipow(begin_dx, 2) + 0.0805154 *begin_y*lens_ipow(begin_dy, 2) + 0.057263 *begin_x*begin_dx*begin_dy + 0.00337771 *lens_ipow(begin_y, 2)*begin_dy + 0.00253277 *begin_x*begin_y*begin_dx + 0.000746082 *lens_ipow(begin_x, 2)*begin_dy + 3.13021e-05 *lens_ipow(begin_y, 3)*begin_lambda + 3.10369e-05 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + 4.31227 *lens_ipow(begin_dy, 5) + -4.08825e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -0.223687 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.000297283 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.00862714 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.0257883 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.000497874 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -2.12399e-10 *lens_ipow(begin_x, 6)*begin_y + -2.67433e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 0.0914548 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -0.000161569 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -1.05333e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + -3.08727e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3);
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 35.8897  + 4.80606 *begin_x*begin_dx + 1.49373 *begin_y*begin_dy + 65.2168 *lens_ipow(begin_dx, 2) + 15.4411 *lens_ipow(begin_dy, 2) + 0.0744818 *lens_ipow(begin_x, 2) + 0.0424157 *lens_ipow(begin_y, 2)*begin_lambda + -0.000121059 *lens_ipow(begin_x, 4) + 0.058664 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000130558 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.273175 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -157.582 *lens_ipow(begin_dx, 4) + 0.239395 *begin_x*begin_y*begin_dx*begin_dy + -0.000144558 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 3)+0.0f;
  dx1_domega0(0, 1) =  + 1.49373 *begin_y*begin_dx + 1.478 *begin_x*begin_dy + 30.8823 *begin_dx*begin_dy + 0.0484408 *begin_x*begin_y + -8.13414e-05 *lens_ipow(begin_x, 3)*begin_y + 0.117328 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -7.98964e-05 *begin_x*lens_ipow(begin_y, 3) + 0.119697 *begin_x*begin_y*lens_ipow(begin_dx, 2)+0.0f;
  dx1_domega0(1, 0) =  + 1.49218 *begin_y*begin_dx + 1.15644 *begin_x*begin_dy + 0.0379861 *begin_x*begin_y + 51.227 *begin_dx*begin_dy*begin_lambda + -8.53176e-05 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + -0.0123992 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.046473 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -3.9393e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)+0.0f;
  dx1_domega0(1, 1) =  + 36.2185  + 48.8159 *lens_ipow(begin_dy, 2) + 4.34643 *begin_y*begin_dy + 1.15644 *begin_x*begin_dx + 0.0670934 *lens_ipow(begin_y, 2) + 0.0169686 *lens_ipow(begin_x, 2) + 25.6135 *lens_ipow(begin_dx, 2)*begin_lambda + -0.00016958 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00397019 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + -0.0371975 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.015491 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -2.11569e-05 *lens_ipow(begin_y, 5)*begin_dy + -5.14074e-07 *lens_ipow(begin_y, 6)+0.0f;
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
