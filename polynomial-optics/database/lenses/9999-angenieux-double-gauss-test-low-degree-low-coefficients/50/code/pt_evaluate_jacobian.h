case angenieux_double_gauss_test_low_degree_low_coefficients_9999_50mm:
{
const float dx00 =  + -0.511723  + 0.189872 *lambda + 0.252909 *lens_ipow(dy, 2) + 0.318411 *lens_ipow(dx, 2) + 0.00592114 *y*dy + -0.0011197 *lens_ipow(y, 2) + 0.0264421 *x*dx + -0.00249454 *lens_ipow(x, 2) + -6.50134e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -6.14372e-06 *lens_ipow(x, 4)+0.0f;
const float dx01 =  + 0.00592114 *x*dy + -0.0022394 *x*y + 0.000102228 *lens_ipow(y, 3)*dx + -4.33423e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx02 =  + 50.1459  + -20.779 *lens_ipow(dy, 2) + -60.986 *lens_ipow(dx, 2) + 0.636822 *x*dx + 0.0132211 *lens_ipow(x, 2) + 2.55569e-05 *lens_ipow(y, 4)+0.0f;
const float dx03 =  + -41.558 *dx*dy + 0.505818 *x*dy + 0.00592114 *x*y+0.0f;
const float dx04 =  + 0.189872 *x+0.0f;
const float dx10 =  + 0.00582584 *y*dx + -0.0022233 *x*y + -4.52678e-06 *x*lens_ipow(y, 3) + 0.000101196 *lens_ipow(x, 3)*dy+0.0f;
const float dx11 =  + -0.512954  + 0.190038 *lambda + 0.329953 *lens_ipow(dy, 2) + 0.252932 *lens_ipow(dx, 2) + 0.02703 *y*dy + -0.00245958 *lens_ipow(y, 2) + 0.00582584 *x*dx + -0.00111165 *lens_ipow(x, 2) + -6.27128e-06 *lens_ipow(y, 4) + -6.79017e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)+0.0f;
const float dx12 =  + -41.5749 *dx*dy + 0.505864 *y*dx + 0.00582584 *x*y+0.0f;
const float dx13 =  + 50.136  + -60.6884 *lens_ipow(dy, 2) + -20.7874 *lens_ipow(dx, 2) + 0.659906 *y*dy + 0.013515 *lens_ipow(y, 2) + 2.52991e-05 *lens_ipow(x, 4)+0.0f;
const float dx14 =  + 0.190038 *y+0.0f;
const float dx20 =  + -0.0134161  + -0.00247318 *lambda + -0.00243114 *lens_ipow(dy, 2) + -0.000100289 *y*dy + 8.72631e-06 *lens_ipow(y, 2) + 3.19944e-05 *lens_ipow(x, 2) + 2.22203e-08 *lens_ipow(y, 4) + 6.55096e-05 *x*y*dx*dy + 1.37938e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -2.15776e-06 *lens_ipow(x, 3)*dx + 8.28669e-08 *lens_ipow(x, 4)+0.0f;
const float dx21 =  + -0.000100289 *x*dy + 1.74526e-05 *x*y + 8.88811e-08 *x*lens_ipow(y, 3) + 3.27548e-05 *lens_ipow(x, 2)*dx*dy + 9.19584e-08 *lens_ipow(x, 3)*y+0.0f;
const float dx22 =  + -0.609054  + 0.167404 *lens_ipow(dy, 2) + 0.815817 *lens_ipow(dx, 2) + 3.27548e-05 *lens_ipow(x, 2)*y*dy + -5.39441e-07 *lens_ipow(x, 4)+0.0f;
const float dx23 =  + 0.334807 *dx*dy + -0.00486228 *x*dy + -0.000100289 *x*y + 3.27548e-05 *lens_ipow(x, 2)*y*dx+0.0f;
const float dx24 =  + -0.00247318 *x+0.0f;
const float dx30 =  + 0.00456728 *dx*dy + -9.96712e-05 *y*dx + 1.88615e-05 *x*y + 9.61326e-08 *x*lens_ipow(y, 3) + 9.48153e-08 *lens_ipow(x, 3)*y+0.0f;
const float dx31 =  + -0.0133897  + -0.00244101 *lambda + -0.00440674 *lens_ipow(dx, 2) + 2.94885e-05 *lens_ipow(y, 2) + -9.96712e-05 *x*dx + 9.43077e-06 *lens_ipow(x, 2) + -2.1269e-06 *lens_ipow(y, 3)*dy + 9.10981e-08 *lens_ipow(y, 4) + 1.44199e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + 2.37038e-08 *lens_ipow(x, 4)+0.0f;
const float dx32 =  + 0.737955 *dx*dy + -0.00881348 *y*dx + 0.00456728 *x*dy + -9.96712e-05 *x*y+0.0f;
const float dx33 =  + -0.612368  + 0.836069 *lens_ipow(dy, 2) + 0.368978 *lens_ipow(dx, 2) + 0.00456728 *x*dx + -5.31726e-07 *lens_ipow(y, 4)+0.0f;
const float dx34 =  + -0.00244101 *y+0.0f;
const float dx40 =  + -0.000752645 *dx + -0.000356494 *x*lens_ipow(dx, 2) + -2.63257e-07 *x*lens_ipow(y, 2) + -2.56013e-07 *lens_ipow(x, 3)+0.0f;
const float dx41 =  + -0.000554902 *dy + -0.000186823 *y*lens_ipow(dx, 2) + -2.58917e-07 *lens_ipow(y, 3) + -2.63257e-07 *lens_ipow(x, 2)*y+0.0f;
const float dx42 =  + -0.000752645 *x + -0.874963 *lens_ipow(dx, 3) + -0.000186823 *lens_ipow(y, 2)*dx + -0.000356494 *lens_ipow(x, 2)*dx + -1.28379 *dx*lens_ipow(dy, 2)*lambda+0.0f;
const float dx43 =  + -0.048889 *dy + -0.000554902 *y + -0.570512 *lens_ipow(dy, 3) + -1.28379 *lens_ipow(dx, 2)*dy*lambda+0.0f;
const float dx44 =  + 0.348894  + -0.473278 *lambda + -0.641895 *lens_ipow(dx, 2)*lens_ipow(dy, 2)+0.0f;
} break;
