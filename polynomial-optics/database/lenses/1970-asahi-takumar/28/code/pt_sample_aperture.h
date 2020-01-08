case asahi__takumar__1970__28mm:
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
  pred_x =  + 29.1443 *begin_dx + 0.586408 *begin_x + 0.52188 *begin_dx*begin_lambda + 0.0133273 *begin_x*begin_lambda + 5.74335 *begin_dx*lens_ipow(begin_dy, 2) + 6.07114 *lens_ipow(begin_dx, 3) + 1.11936 *begin_y*begin_dx*begin_dy + 0.0233401 *lens_ipow(begin_y, 2)*begin_dx + 0.689564 *begin_x*lens_ipow(begin_dy, 2) + 1.86208 *begin_x*lens_ipow(begin_dx, 2) + 0.0527357 *begin_x*begin_y*begin_dy + 0.000744863 *begin_x*lens_ipow(begin_y, 2) + 0.0780203 *lens_ipow(begin_x, 2)*begin_dx + 0.000739898 *lens_ipow(begin_x, 3) + 3.11327e-05 *lens_ipow(begin_x, 3)*begin_lambda + 7.73494e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -6.16008e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 1.09917e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 3.00171e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -3.81487e-10 *lens_ipow(begin_x, 7) + -0.0795532 *begin_x*begin_y*lens_ipow(begin_dy, 5)*begin_lambda + 1.30616e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 2.06478e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dy + -1.12498e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3);
  pred_y =  + 29.2795 *begin_dy + 0.584358 *begin_y + 0.0171163 *begin_y*begin_lambda + 0.491387 *begin_dy*lens_ipow(begin_lambda, 2) + 5.94581 *lens_ipow(begin_dy, 3) + 5.98883 *lens_ipow(begin_dx, 2)*begin_dy + 1.84181 *begin_y*lens_ipow(begin_dy, 2) + 0.705569 *begin_y*lens_ipow(begin_dx, 2) + 0.0773049 *lens_ipow(begin_y, 2)*begin_dy + 0.000751392 *lens_ipow(begin_y, 3) + 1.14136 *begin_x*begin_dx*begin_dy + 0.0537161 *begin_x*begin_y*begin_dx + 0.0237446 *lens_ipow(begin_x, 2)*begin_dy + 0.000751104 *lens_ipow(begin_x, 2)*begin_y + -3.99561e-10 *lens_ipow(begin_y, 7) + 4.06729e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 8.83436e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -4.51867e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 9.88222e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + 2.32302e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + -3.55721e-10 *lens_ipow(begin_x, 6)*begin_y + 4.27225e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_lambda + -8.46395e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy*begin_lambda + 7.04847e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda;
  pred_dx =  + 1.23234 *begin_dx + -0.012393 *begin_x + -0.696853 *begin_dx*begin_lambda + -0.00342989 *begin_x*begin_lambda + 0.428269 *begin_dx*lens_ipow(begin_lambda, 2) + 1.14997 *begin_dx*lens_ipow(begin_dy, 2) + 1.1789 *lens_ipow(begin_dx, 3) + 0.0891675 *begin_y*begin_dx*begin_dy + 0.00236396 *lens_ipow(begin_y, 2)*begin_dx + 0.0544787 *begin_x*lens_ipow(begin_dy, 2) + 0.143822 *begin_x*lens_ipow(begin_dx, 2) + 0.0049875 *begin_x*begin_y*begin_dy + 8.64731e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00730991 *lens_ipow(begin_x, 2)*begin_dx + 8.61632e-05 *lens_ipow(begin_x, 3) + -0.000346424 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + -0.00220865 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000483235 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4) + -0.0704794 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.0130042 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 2) + -7.11809e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -4.67436e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3)*begin_lambda + 7.1603e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + 1.94388e-12 *lens_ipow(begin_x, 9)*lens_ipow(begin_dy, 2);
  pred_dy =  + 1.22815 *begin_dy + -0.0123109 *begin_y + -0.66154 *begin_dy*begin_lambda + -0.00358083 *begin_y*begin_lambda + 0.386276 *begin_dy*lens_ipow(begin_lambda, 2) + 1.10803 *lens_ipow(begin_dy, 3) + 1.12436 *lens_ipow(begin_dx, 2)*begin_dy + 0.139243 *begin_y*lens_ipow(begin_dy, 2) + 0.0523224 *begin_y*lens_ipow(begin_dx, 2) + 0.00713593 *lens_ipow(begin_y, 2)*begin_dy + 8.4697e-05 *lens_ipow(begin_y, 3) + 0.0887055 *begin_x*begin_dx*begin_dy + 0.00481934 *begin_x*begin_y*begin_dx + 0.00237222 *lens_ipow(begin_x, 2)*begin_dy + 8.72597e-05 *lens_ipow(begin_x, 2)*begin_y + -0.000123678 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 7.93259e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -0.000546651 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + -0.000304361 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*begin_dy + 3.22352e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_lambda + 0.000120368 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 4) + 0.000411861 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.00166101 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 6)*begin_lambda + -1.44471e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda;
  Eigen::Matrix2d dx1_domega0;
  dx1_domega0(0, 0) =  + 29.1443  + 0.52188 *begin_lambda + 5.74335 *lens_ipow(begin_dy, 2) + 18.2134 *lens_ipow(begin_dx, 2) + 1.11936 *begin_y*begin_dy + 0.0233401 *lens_ipow(begin_y, 2) + 3.72417 *begin_x*begin_dx + 0.0780203 *lens_ipow(begin_x, 2) + -6.16008e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy + 1.09917e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 2.61233e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -2.24995e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 3)+0.0f;
  dx1_domega0(0, 1) =  + 11.4867 *begin_dx*begin_dy + 1.11936 *begin_y*begin_dx + 1.37913 *begin_x*begin_dy + 0.0527357 *begin_x*begin_y + 7.73494e-06 *begin_x*lens_ipow(begin_y, 3) + -6.16008e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 6.00342e-06 *lens_ipow(begin_x, 5)*begin_dy + -0.397766 *begin_x*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 2.06478e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)+0.0f;
  dx1_domega0(1, 0) =  + 11.9777 *begin_dx*begin_dy + 1.41114 *begin_y*begin_dx + 1.14136 *begin_x*begin_dy + 0.0537161 *begin_x*begin_y + 8.13457e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -4.51867e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 9.88222e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 8.54451e-06 *lens_ipow(begin_y, 5)*begin_dx*begin_lambda + -8.46395e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dy*begin_lambda+0.0f;
  dx1_domega0(1, 1) =  + 29.2795  + 0.491387 *lens_ipow(begin_lambda, 2) + 17.8374 *lens_ipow(begin_dy, 2) + 5.98883 *lens_ipow(begin_dx, 2) + 3.68362 *begin_y*begin_dy + 0.0773049 *lens_ipow(begin_y, 2) + 1.14136 *begin_x*begin_dx + 0.0237446 *lens_ipow(begin_x, 2) + 8.83436e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -4.51867e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 4.64604e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy + -8.46395e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_lambda + 1.40969e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda+0.0f;
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
