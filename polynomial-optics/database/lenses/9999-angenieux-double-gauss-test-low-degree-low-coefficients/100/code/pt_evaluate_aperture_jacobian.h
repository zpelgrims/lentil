case angenieux_double_gauss_test_low_degree_low_coefficients_9999_100mm:
{
const float dx00 =  + 0.155085  + 0.267639 *lambda + -0.185046 *lens_ipow(lambda, 2) + -0.159593 *lens_ipow(dy, 2) + -0.180895 *lens_ipow(dx, 2) + -0.000110295 *lens_ipow(y, 2) + -0.000321937 *lens_ipow(x, 2) + 0.228388 *lens_ipow(dy, 4)+0.0f;
const float dx01 =  + -0.0761147 *dx*dy + -0.000220591 *x*y+0.0f;
const float dx02 =  + 53.5533  + 13.4794 *lambda + -9.22234 *lens_ipow(lambda, 2) + -30.0121 *lens_ipow(dy, 2) + -89.7535 *lens_ipow(dx, 2) + -0.0761147 *y*dy + -0.361791 *x*dx+0.0f;
const float dx03 =  + -60.0241 *dx*dy + -0.0761147 *y*dx + -0.319187 *x*dy + 0.913553 *x*lens_ipow(dy, 3)+0.0f;
const float dx04 =  + 13.4794 *dx + 0.267639 *x + -18.4447 *dx*lambda + -0.370092 *x*lambda+0.0f;
const float dx10 =  + -0.0759737 *dx*dy + -0.00022081 *x*y+0.0f;
const float dx11 =  + 0.157591  + 0.257999 *lambda + -0.176885 *lens_ipow(lambda, 2) + -0.180369 *lens_ipow(dy, 2) + -0.155302 *lens_ipow(dx, 2) + -0.000320489 *lens_ipow(y, 2) + -0.000110405 *lens_ipow(x, 2) + 0.210395 *lens_ipow(dx, 4)+0.0f;
const float dx12 =  + -60.0584 *dx*dy + -0.310604 *y*dx + -0.0759737 *x*dy + 0.841579 *y*lens_ipow(dx, 3)+0.0f;
const float dx13 =  + 53.5515  + 13.4912 *lambda + -9.22586 *lens_ipow(lambda, 2) + -89.8669 *lens_ipow(dy, 2) + -30.0292 *lens_ipow(dx, 2) + -0.360738 *y*dy + -0.0759737 *x*dx+0.0f;
const float dx14 =  + 13.4912 *dy + 0.257999 *y + -18.4517 *dy*lambda + -0.35377 *y*lambda+0.0f;
const float dx20 =  + -0.0176487  + 0.00674921 *lambda + -0.00467207 *lens_ipow(lambda, 2) + -0.00495095 *lens_ipow(dy, 2) + -0.0152224 *lens_ipow(dx, 2) + 7.19631e-05 *y*dy + -3.10925e-06 *lens_ipow(y, 2) + 0.000143035 *x*dx + -9.87428e-06 *lens_ipow(x, 2) + -4.64766e-06 *lens_ipow(y, 2)*lens_ipow(dx, 2)+0.0f;
const float dx21 =  + -0.0106476 *dx*dy + 7.19631e-05 *x*dy + -6.21849e-06 *x*y + -9.29533e-06 *x*y*lens_ipow(dx, 2)+0.0f;
const float dx22 =  + 0.395899  + -0.483532 *lens_ipow(dy, 2) + -1.45219 *lens_ipow(dx, 2) + -0.0106476 *y*dy + -0.0304448 *x*dx + 7.15177e-05 *lens_ipow(x, 2) + -9.29533e-06 *x*lens_ipow(y, 2)*dx+0.0f;
const float dx23 =  + -0.967064 *dx*dy + -0.0106476 *y*dx + -0.00990191 *x*dy + 7.19631e-05 *x*y+0.0f;
const float dx24 =  + 0.00674921 *x + -0.00934413 *x*lambda+0.0f;
const float dx30 =  + -0.0106545 *dx*dy + 7.13093e-05 *y*dx + -6.26244e-06 *x*y + -9.09988e-06 *x*y*lens_ipow(dy, 2)+0.0f;
const float dx31 =  + -0.0176122  + 0.00661369 *lambda + -0.00454918 *lens_ipow(lambda, 2) + -0.0152456 *lens_ipow(dy, 2) + -0.00494986 *lens_ipow(dx, 2) + 0.000140949 *y*dy + -9.84338e-06 *lens_ipow(y, 2) + 7.13093e-05 *x*dx + -3.13122e-06 *lens_ipow(x, 2) + -4.54994e-06 *lens_ipow(x, 2)*lens_ipow(dy, 2)+0.0f;
const float dx32 =  + -0.968434 *dx*dy + -0.00989971 *y*dx + -0.0106545 *x*dy + 7.13093e-05 *x*y+0.0f;
const float dx33 =  + 0.396038  + -1.4544 *lens_ipow(dy, 2) + -0.484217 *lens_ipow(dx, 2) + -0.0304913 *y*dy + 7.04744e-05 *lens_ipow(y, 2) + -0.0106545 *x*dx + -9.09988e-06 *lens_ipow(x, 2)*y*dy+0.0f;
const float dx34 =  + 0.00661369 *y + -0.00909836 *y*lambda+0.0f;
const float dx40 =  + -3.41996e-08 *lens_ipow(x, 3) + 0.00915427 *dx*lens_ipow(dy, 4) + 0.0154792 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + 0.00994706 *lens_ipow(dx, 5)+0.0f;
const float dx41 =  + -4.7537e-06 *y + 0.00239031 *lens_ipow(dx, 2)*dy + 0.0103363 *lens_ipow(dy, 5)+0.0f;
const float dx42 =  + -0.891433 *dx*lens_ipow(dy, 2) + -0.844393 *lens_ipow(dx, 3) + 0.00478063 *y*dx*dy + 0.00915427 *x*lens_ipow(dy, 4) + 0.0464377 *x*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.0497353 *x*lens_ipow(dx, 4)+0.0f;
const float dx43 =  + -0.844364 *lens_ipow(dy, 3) + -0.891433 *lens_ipow(dx, 2)*dy + 0.00239031 *y*lens_ipow(dx, 2) + 0.0516817 *y*lens_ipow(dy, 4) + 0.0366171 *x*dx*lens_ipow(dy, 3) + 0.0309584 *x*lens_ipow(dx, 3)*dy+0.0f;
const float dx44 =  + 0.595521  + -1.64497 *lambda + 1.19955 *lens_ipow(lambda, 2)+0.0f;
} break;
