case angenieux_double_gauss_test_low_degree_low_coefficients_9999_50mm:
{
const float dx00 =  + -0.514073  + 0.193023 *lambda + 0.254673 *lens_ipow(dy, 2) + 0.306425 *lens_ipow(dx, 2) + 0.00639941 *y*dy + -0.00107932 *lens_ipow(y, 2) + 0.0258725 *x*dx + -0.00260794 *lens_ipow(x, 2) + -6.13477e-06 *lens_ipow(x, 4) + -4.40043e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const float dx01 =  + 0.00639941 *x*dy + -0.00215865 *x*y + 0.018882 *y*dx*lambda + -5.86724e-08 *lens_ipow(x, 3)*lens_ipow(y, 3)+0.0f;
const float dx02 =  + 50.062  + -20.9598 *lens_ipow(dy, 2) + -61.4802 *lens_ipow(dx, 2) + 0.61285 *x*dx + 0.0129362 *lens_ipow(x, 2) + 0.00944102 *lens_ipow(y, 2)*lambda+0.0f;
const float dx03 =  + -41.9196 *dx*dy + 0.509346 *x*dy + 0.00639941 *x*y+0.0f;
const float dx04 =  + 0.193023 *x + 0.00944102 *lens_ipow(y, 2)*dx+0.0f;
const float dx10 =  + 0.00645673 *y*dx + -0.00180917 *x*y + 0.0190294 *x*dy*lambda + -5.64476e-06 *lens_ipow(x, 3)*y + -2.22192e-08 *x*lens_ipow(y, 5)+0.0f;
const float dx11 =  + -0.50326  + 0.194546 *lambda + 0.298569 *lens_ipow(dy, 2) + 0.255843 *lens_ipow(dx, 2) + 0.0254383 *y*dy + -0.00349689 *lens_ipow(y, 2) + 0.00645673 *x*dx + -0.000904587 *lens_ipow(x, 2) + -1.41119e-06 *lens_ipow(x, 4) + -5.5548e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const float dx12 =  + -42.2558 *dx*dy + 0.511686 *y*dx + 0.00645673 *x*y+0.0f;
const float dx13 =  + 50.0743  + -61.5347 *lens_ipow(dy, 2) + -21.1279 *lens_ipow(dx, 2) + 0.597138 *y*dy + 0.0127191 *lens_ipow(y, 2) + 0.00951468 *lens_ipow(x, 2)*lambda+0.0f;
const float dx14 =  + 0.194546 *y + 0.00951468 *lens_ipow(x, 2)*dy+0.0f;
const float dx20 =  + -0.0136882  + -0.00244039 *lambda + -0.00228497 *lens_ipow(dy, 2) + -8.13024e-05 *y*dy + 1.17087e-05 *lens_ipow(y, 2) + 4.61325e-05 *lens_ipow(x, 2) + 2.05227e-08 *lens_ipow(y, 4) + 8.02143e-05 *x*y*dx*dy + 8.22696e-10 *lens_ipow(x, 4)*lens_ipow(y, 2) + -1.48029e-08 *lens_ipow(x, 5)*dx+0.0f;
const float dx21 =  + -8.13024e-05 *x*dy + 2.34174e-05 *x*y + 8.2091e-08 *x*lens_ipow(y, 3) + 4.01072e-05 *lens_ipow(x, 2)*dx*dy + 0.000955578 *y*lens_ipow(dx, 3)*lambda + 3.29079e-10 *lens_ipow(x, 5)*y+0.0f;
const float dx22 =  + -0.61015  + 0.173841 *lens_ipow(dy, 2) + 0.785017 *lens_ipow(dx, 2) + 4.01072e-05 *lens_ipow(x, 2)*y*dy + 0.00143337 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lambda + -2.46716e-09 *lens_ipow(x, 6)+0.0f;
const float dx23 =  + 0.347681 *dx*dy + -0.00456994 *x*dy + -8.13024e-05 *x*y + 4.01072e-05 *lens_ipow(x, 2)*y*dx+0.0f;
const float dx24 =  + -0.00244039 *x + 0.000477789 *lens_ipow(y, 2)*lens_ipow(dx, 3)+0.0f;
const float dx30 =  + 0.00456833 *dx*dy + -9.96915e-05 *y*dx + 1.89683e-05 *x*y + 9.54694e-08 *x*lens_ipow(y, 3) + 9.43216e-08 *lens_ipow(x, 3)*y+0.0f;
const float dx31 =  + -0.0134572  + -0.0024402 *lambda + -0.0044064 *lens_ipow(dx, 2) + 3.62559e-05 *lens_ipow(y, 2) + -9.96915e-05 *x*dx + 9.48415e-06 *lens_ipow(x, 2) + -2.13584e-06 *lens_ipow(y, 3)*dy + 1.43204e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + 2.35804e-08 *lens_ipow(x, 4) + 2.83416e-10 *lens_ipow(y, 6)+0.0f;
const float dx32 =  + 0.738066 *dx*dy + -0.00881281 *y*dx + 0.00456833 *x*dy + -9.96915e-05 *x*y+0.0f;
const float dx33 =  + -0.612338  + 0.835519 *lens_ipow(dy, 2) + 0.369033 *lens_ipow(dx, 2) + 0.00456833 *x*dx + -5.33959e-07 *lens_ipow(y, 4)+0.0f;
const float dx34 =  + -0.0024402 *y+0.0f;
const float dx40 =  + -0.000752644 *dx + -0.000356494 *x*lens_ipow(dx, 2) + -2.63257e-07 *x*lens_ipow(y, 2) + -2.56013e-07 *lens_ipow(x, 3)+0.0f;
const float dx41 =  + -0.000554902 *dy + -0.000186823 *y*lens_ipow(dx, 2) + -2.58917e-07 *lens_ipow(y, 3) + -2.63257e-07 *lens_ipow(x, 2)*y+0.0f;
const float dx42 =  + -0.000752644 *x + -0.874963 *lens_ipow(dx, 3) + -0.000186823 *lens_ipow(y, 2)*dx + -0.000356494 *lens_ipow(x, 2)*dx + -1.28379 *dx*lens_ipow(dy, 2)*lambda+0.0f;
const float dx43 =  + -0.048889 *dy + -0.000554902 *y + -0.570512 *lens_ipow(dy, 3) + -1.28379 *lens_ipow(dx, 2)*dy*lambda+0.0f;
const float dx44 =  + 0.348894  + -0.473278 *lambda + -0.641895 *lens_ipow(dx, 2)*lens_ipow(dy, 2)+0.0f;
} break;
