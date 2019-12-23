case angenieux__double_gauss__1953__49mm:
{
const double dx00 =  + 0.197484  + 0.08335 *lambda + -0.000436864 *lens_ipow(y, 2) + -0.00126021 *lens_ipow(x, 2) + -0.193987 *lens_ipow(dx, 2) + -0.115566 *lens_ipow(dy, 2) + 3.41307e-05 *lens_ipow(x, 3)*dx + -9.59926e-09 *lens_ipow(x, 6) + -1.42221e-09 *lens_ipow(y, 6) + -1.34039e-08 *lens_ipow(x, 2)*lens_ipow(y, 4) + -2.16498e-08 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const double dx01 =  + -0.106556 *dx*dy + -0.000873727 *x*y + -8.53325e-09 *x*lens_ipow(y, 5) + -1.78718e-08 *lens_ipow(x, 3)*lens_ipow(y, 3) + -8.65991e-09 *lens_ipow(x, 5)*y+0.0f;
const double dx02 =  + 27.5928  + 1.74497 *lambda + -0.106556 *y*dy + -45.5281 *lens_ipow(dx, 2) + -15.544 *lens_ipow(dy, 2) + -0.387974 *x*dx + 8.53267e-06 *lens_ipow(x, 4)+0.0f;
const double dx03 =  + -0.106556 *y*dx + -31.0879 *dx*dy + -0.231133 *x*dy+0.0f;
const double dx04 =  + 1.74497 *dx + 0.08335 *x+0.0f;
const double dx10 =  + -0.000873969 *x*y + -0.107801 *dx*dy + -8.89452e-09 *x*lens_ipow(y, 5) + -1.75215e-08 *lens_ipow(x, 3)*lens_ipow(y, 3) + -8.23709e-09 *lens_ipow(x, 5)*y+0.0f;
const double dx11 =  + 0.19711  + 0.0839936 *lambda + -0.115586 *lens_ipow(dx, 2) + -0.000436985 *lens_ipow(x, 2) + -0.00125584 *lens_ipow(y, 2) + -0.194777 *lens_ipow(dy, 2) + 3.40712e-05 *lens_ipow(y, 3)*dy + -9.86184e-09 *lens_ipow(y, 6) + -2.22363e-08 *lens_ipow(x, 2)*lens_ipow(y, 4) + -1.31411e-08 *lens_ipow(x, 4)*lens_ipow(y, 2) + -1.37285e-09 *lens_ipow(x, 6)+0.0f;
const double dx12 =  + -0.231172 *y*dx + -30.9859 *dx*dy + -0.107801 *x*dy+0.0f;
const double dx13 =  + 27.5931  + 1.74531 *lambda + -45.6282 *lens_ipow(dy, 2) + -0.389554 *y*dy + -15.493 *lens_ipow(dx, 2) + -0.107801 *x*dx + 8.51781e-06 *lens_ipow(y, 4)+0.0f;
const double dx14 =  + 1.74531 *dy + 0.0839936 *y+0.0f;
const double dx20 =  + -0.0338929  + 0.00509044 *lambda + -3.07307e-05 *lens_ipow(y, 2) + -7.97341e-05 *lens_ipow(x, 2) + -0.0352866 *lens_ipow(dx, 2) + -0.0126963 *lens_ipow(dy, 2) + 1.06375e-05 *lens_ipow(x, 3)*dx + 7.51017e-06 *lens_ipow(x, 2)*y*dy + -5.57547e-10 *lens_ipow(x, 6) + 1.57255e-08 *lens_ipow(y, 5)*dy + 5.14468e-08 *x*lens_ipow(y, 4)*dx + -1.86729e-09 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const double dx21 =  + -0.0235895 *dx*dy + -6.14614e-05 *x*y + 2.50339e-06 *lens_ipow(x, 3)*dy + 7.86276e-08 *x*lens_ipow(y, 4)*dy + 1.02894e-07 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx + -7.46917e-10 *lens_ipow(x, 5)*y+0.0f;
const double dx22 =  + 0.39901  + -0.0235895 *y*dy + -1.48997 *lens_ipow(dx, 2) + -0.508143 *lens_ipow(dy, 2) + -0.0705731 *x*dx + 2.65939e-06 *lens_ipow(x, 4) + 2.57234e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const double dx23 =  + -0.0235895 *y*dx + -1.01629 *dx*dy + -0.0253925 *x*dy + 2.50339e-06 *lens_ipow(x, 3)*y + 1.57255e-08 *x*lens_ipow(y, 5)+0.0f;
const double dx24 =  + 0.00509044 *x+0.0f;
const double dx30 =  + -6.13694e-05 *x*y + -0.0237488 *dx*dy + 2.38919e-06 *lens_ipow(y, 3)*dx + -7.61431e-10 *x*lens_ipow(y, 5) + 1.03707e-07 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy + 7.92537e-08 *lens_ipow(x, 4)*y*dx+0.0f;
const double dx31 =  + -0.0339385  + 0.00517753 *lambda + -0.0128604 *lens_ipow(dx, 2) + -3.06847e-05 *lens_ipow(x, 2) + -7.93482e-05 *lens_ipow(y, 2) + -0.0352949 *lens_ipow(dy, 2) + 7.16757e-06 *x*lens_ipow(y, 2)*dx + 1.06651e-05 *lens_ipow(y, 3)*dy + -5.81985e-10 *lens_ipow(y, 6) + -1.90358e-09 *lens_ipow(x, 2)*lens_ipow(y, 4) + 5.18534e-08 *lens_ipow(x, 4)*y*dy + 1.58507e-08 *lens_ipow(x, 5)*dx+0.0f;
const double dx32 =  + -0.0257208 *y*dx + -1.01066 *dx*dy + -0.0237488 *x*dy + 2.38919e-06 *x*lens_ipow(y, 3) + 1.58507e-08 *lens_ipow(x, 5)*y+0.0f;
const double dx33 =  + 0.39878  + -1.48816 *lens_ipow(dy, 2) + -0.0705899 *y*dy + -0.505331 *lens_ipow(dx, 2) + -0.0237488 *x*dx + 2.66628e-06 *lens_ipow(y, 4) + 2.59267e-08 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const double dx34 =  + 0.00517753 *y+0.0f;
const double dx40 =  + -2.84e-07 *lens_ipow(x, 3) + -4.08123e-07 *x*lens_ipow(y, 2) + 0.000149039 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2) + 0.0277455 *lens_ipow(dx, 5)+0.0f;
const double dx41 =  + -0.000166704 *y*lens_ipow(dx, 2) + -4.08123e-07 *lens_ipow(x, 2)*y + 0.026069 *lens_ipow(dx, 4)*dy + 8.70211e-05 *lens_ipow(y, 2)*lens_ipow(dy, 3) + -1.4863e-09 *lens_ipow(y, 5) + 0.0169038 *lens_ipow(dy, 5)+0.0f;
const double dx42 =  + -0.779157 *lens_ipow(dx, 3) + -0.9802 *dx*lens_ipow(dy, 2) + -0.000166704 *lens_ipow(y, 2)*dx + 0.104276 *y*lens_ipow(dx, 3)*dy + 4.96795e-05 *lens_ipow(x, 3)*lens_ipow(dy, 2) + 0.138728 *x*lens_ipow(dx, 4)+0.0f;
const double dx43 =  + -0.871496 *lens_ipow(dy, 3) + -0.9802 *lens_ipow(dx, 2)*dy + 0.026069 *y*lens_ipow(dx, 4) + 9.9359e-05 *lens_ipow(x, 3)*dx*dy + 8.70211e-05 *lens_ipow(y, 3)*lens_ipow(dy, 2) + 0.0845189 *y*lens_ipow(dy, 4)+0.0f;
const double dx44 =  + 0.587213  + -1.60789 *lambda + 1.16312 *lens_ipow(lambda, 2)+0.0f;
} break;
