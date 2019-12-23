case angenieux__double_gauss__1953__49mm:
{
const double dx00 =  + -0.636603  + 0.724233 *lambda + -0.00113165 *lens_ipow(y, 2) + -0.00417867 *lens_ipow(x, 2) + 0.00630502 *y*dy + 0.297063 *lens_ipow(dx, 2) + -0.530259 *lens_ipow(lambda, 2) + 0.250268 *lens_ipow(dy, 2) + 0.00177623 *lens_ipow(x, 2)*lambda + 0.0465761 *x*dx*lambda + -2.15184e-08 *lens_ipow(x, 6) + -4.88815e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const double dx01 =  + -0.0022633 *x*y + 0.00630502 *x*dy + 0.0109486 *y*dx + -6.51753e-08 *lens_ipow(x, 3)*lens_ipow(y, 3)+0.0f;
const double dx02 =  + 49.0721  + -60.523 *lens_ipow(dx, 2) + -20.6523 *lens_ipow(dy, 2) + 0.594127 *x*dx + 0.00547431 *lens_ipow(y, 2) + 0.0232881 *lens_ipow(x, 2)*lambda+0.0f;
const double dx03 =  + -41.3046 *dx*dy + 0.00630502 *x*y + 0.500537 *x*dy+0.0f;
const double dx04 =  + 0.724233 *x + -1.06052 *x*lambda + 0.000592076 *lens_ipow(x, 3) + 0.0232881 *lens_ipow(x, 2)*dx+0.0f;
const double dx10 =  + 0.00642504 *y*dx + -0.00162805 *x*y + 0.0113487 *x*dy + -5.91255e-06 *lens_ipow(x, 3)*y + -6.18235e-06 *x*lens_ipow(y, 3)+0.0f;
const double dx11 =  + -0.467832  + 0.104946 *lambda + 0.00642504 *x*dx + 0.246686 *lens_ipow(dx, 2) + -0.000814023 *lens_ipow(x, 2) + -0.00415803 *lens_ipow(y, 2) + 0.525409 *lens_ipow(dy, 2)*lambda + 0.00214325 *lens_ipow(y, 2)*lambda + 0.0475703 *y*dy*lambda + -1.47814e-06 *lens_ipow(x, 4) + -9.27352e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -2.29591e-08 *lens_ipow(y, 6)+0.0f;
const double dx12 =  + 0.00642504 *x*y + 0.493371 *y*dx + -41.3542 *dx*dy+0.0f;
const double dx13 =  + 49.0535  + -60.8044 *lens_ipow(dy, 2) + 0.00567435 *lens_ipow(x, 2) + -20.6771 *lens_ipow(dx, 2) + 1.05082 *y*dy*lambda + 0.0237852 *lens_ipow(y, 2)*lambda+0.0f;
const double dx14 =  + 0.104946 *y + 0.525409 *y*lens_ipow(dy, 2) + 0.000714418 *lens_ipow(y, 3) + 0.0237852 *lens_ipow(y, 2)*dy+0.0f;
const double dx20 =  + -0.0123666  + -0.0098959 *lambda + 1.35313e-05 *lens_ipow(y, 2) + 6.19861e-05 *lens_ipow(x, 2) + 0.00755466 *lens_ipow(lambda, 2) + -2.10891e-05 *lens_ipow(x, 2)*lambda + 2.11676e-08 *lens_ipow(y, 4) + 9.62976e-05 *x*y*dx*dy + -1.63535e-06 *lens_ipow(x, 2)*y*dy + -0.000273529 *lens_ipow(x, 2)*lens_ipow(dy, 4) + 8.19045e-10 *lens_ipow(x, 4)*lens_ipow(y, 2) + -1.8274e-08 *lens_ipow(x, 5)*dx+0.0f;
const double dx21 =  + 2.70627e-05 *x*y + 8.46706e-08 *x*lens_ipow(y, 3) + 4.81488e-05 *lens_ipow(x, 2)*dx*dy + -5.45117e-07 *lens_ipow(x, 3)*dy + 0.00186345 *y*lens_ipow(dx, 3)*lens_ipow(lambda, 2) + 3.27618e-10 *lens_ipow(x, 5)*y+0.0f;
const double dx22 =  + -0.609913  + 0.774029 *lens_ipow(dx, 2) + 0.182025 *lens_ipow(dy, 2) + 4.81488e-05 *lens_ipow(x, 2)*y*dy + 0.00279518 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(lambda, 2) + -3.04567e-09 *lens_ipow(x, 6)+0.0f;
const double dx23 =  + 0.364049 *dx*dy + 4.81488e-05 *lens_ipow(x, 2)*y*dx + -5.45117e-07 *lens_ipow(x, 3)*y + -0.000364705 *lens_ipow(x, 3)*lens_ipow(dy, 3)+0.0f;
const double dx24 =  + -0.0098959 *x + 0.0151093 *x*lambda + -7.0297e-06 *lens_ipow(x, 3) + 0.00186345 *lens_ipow(y, 2)*lens_ipow(dx, 3)*lambda+0.0f;
const double dx30 =  + -0.000126838 *y*dx + 2.00195e-05 *x*y + 0.00425551 *dx*dy + 9.80827e-08 *lens_ipow(x, 3)*y + 9.80352e-08 *x*lens_ipow(y, 3) + -1.53531e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy+0.0f;
const double dx31 =  + -0.0116902  + -0.0100684 *lambda + -0.000126838 *x*dx + -0.00465873 *lens_ipow(dx, 2) + 1.00098e-05 *lens_ipow(x, 2) + 3.89883e-05 *lens_ipow(y, 2) + 0.00685957 *lens_ipow(lambda, 2) + -2.20262e-06 *lens_ipow(y, 3)*dy + 2.45207e-08 *lens_ipow(x, 4) + 1.47053e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + 3.24034e-10 *lens_ipow(y, 6) + -7.67656e-09 *lens_ipow(x, 4)*y*dy+0.0f;
const double dx32 =  + -0.000126838 *x*y + -0.00931745 *y*dx + 0.715381 *dx*dy + 0.00425551 *x*dy+0.0f;
const double dx33 =  + -0.611143  + 0.821823 *lens_ipow(dy, 2) + 0.357691 *lens_ipow(dx, 2) + 0.00425551 *x*dx + -5.50655e-07 *lens_ipow(y, 4) + -3.83828e-09 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const double dx34 =  + -0.0100684 *y + 0.0137191 *y*lambda+0.0f;
const double dx40 =  + -0.000969273 *dx + -0.000488427 *x*lens_ipow(dx, 2) + -0.000221918 *x*lens_ipow(dy, 2) + -0.00027197 *y*dx*dy + -3.42981e-07 *x*lens_ipow(y, 2) + -1.29742e-09 *lens_ipow(x, 5)+0.0f;
const double dx41 =  + -0.000952343 *dy + -0.000479308 *y*lens_ipow(dy, 2) + -0.00027197 *x*dx*dy + -0.000217874 *y*lens_ipow(dx, 2) + -3.42981e-07 *lens_ipow(x, 2)*y + -1.31034e-09 *lens_ipow(y, 5)+0.0f;
const double dx42 =  + -0.000969273 *x + -0.000488427 *lens_ipow(x, 2)*dx + -0.83926 *lens_ipow(dx, 3) + -0.840745 *dx*lens_ipow(dy, 2) + -0.00027197 *x*y*dy + -0.000217874 *lens_ipow(y, 2)*dx+0.0f;
const double dx43 =  + -0.000952343 *y + -0.835498 *lens_ipow(dy, 3) + -0.000479308 *lens_ipow(y, 2)*dy + -0.000221918 *lens_ipow(x, 2)*dy + -0.840745 *lens_ipow(dx, 2)*dy + -0.00027197 *x*y*dx+0.0f;
const double dx44 =  + 0.347751  + -0.473178 *lambda+0.0f;
} break;
