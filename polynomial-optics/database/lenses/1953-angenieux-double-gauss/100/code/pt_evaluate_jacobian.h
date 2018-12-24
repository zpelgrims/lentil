case angenieux_double_gauss_1953_100mm:
{
const float dx00 =  + -0.612819  + 0.591016 *lambda + -0.407523 *lens_ipow(lambda, 2) + 0.29064 *lens_ipow(dy, 2) + 0.460483 *lens_ipow(dx, 2) + 0.00558501 *y*dy + -0.000247535 *lens_ipow(y, 2) + 0.0180596 *x*dx + -0.000745406 *lens_ipow(x, 2)+0.0f;
const float dx01 =  + 0.1689 *dx*dy + 0.00558501 *x*dy + -0.000495069 *x*y + 0.0124694 *y*dx*lambda+0.0f;
const float dx02 =  + 99.6253  + -38.4082 *lens_ipow(dy, 2) + -115.233 *lens_ipow(dx, 2) + 0.1689 *y*dy + 0.920965 *x*dx + 0.00902978 *lens_ipow(x, 2) + 0.00623469 *lens_ipow(y, 2)*lambda+0.0f;
const float dx03 =  + -76.8165 *dx*dy + 0.1689 *y*dx + 0.58128 *x*dy + 0.00558501 *x*y+0.0f;
const float dx04 =  + 0.591016 *x + -0.815045 *x*lambda + 0.00623469 *lens_ipow(y, 2)*dx+0.0f;
const float dx10 =  + 0.165021 *dx*dy + 0.0055095 *y*dx + 0.00664929 *x*dy + -0.000498284 *x*y+0.0f;
const float dx11 =  + -0.612999  + 0.57796 *lambda + -0.383126 *lens_ipow(lambda, 2) + 0.458346 *lens_ipow(dy, 2) + 0.288674 *lens_ipow(dx, 2) + -0.000743198 *lens_ipow(y, 2) + 0.0055095 *x*dx + -0.000249142 *lens_ipow(x, 2) + 0.0323494 *y*dy*lambda+0.0f;
const float dx12 =  + -76.8796 *dx*dy + 0.577348 *y*dx + 0.165021 *x*dy + 0.0055095 *x*y+0.0f;
const float dx13 =  + 99.6623  + -115.695 *lens_ipow(dy, 2) + -38.4398 *lens_ipow(dx, 2) + 0.916692 *y*dy + 0.165021 *x*dx + 0.00332464 *lens_ipow(x, 2) + 0.0161747 *lens_ipow(y, 2)*lambda+0.0f;
const float dx14 =  + 0.57796 *y + -0.766253 *y*lambda + 0.0161747 *lens_ipow(y, 2)*dy+0.0f;
const float dx20 =  + -0.00629425  + -0.00359449 *lambda + 0.00254506 *lens_ipow(lambda, 2) + -0.00116404 *lens_ipow(dy, 2) + -2.17887e-05 *y*dy + 1.68674e-06 *lens_ipow(y, 2) + -6.72271e-05 *x*dx + 5.34799e-06 *lens_ipow(x, 2) + 0.000704959 *x*lens_ipow(dx, 3)*lambda+0.0f;
const float dx21 =  + -2.17887e-05 *x*dy + 3.37347e-06 *x*y + 0.000227454 *y*lens_ipow(dx, 3)*lambda+0.0f;
const float dx22 =  + -0.6051  + 0.706008 *lens_ipow(dx, 2) + -3.36135e-05 *lens_ipow(x, 2) + 0.508466 *lens_ipow(dy, 2)*lambda + -0.397889 *lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 0.000341181 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lambda + 0.00105744 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lambda+0.0f;
const float dx23 =  + -0.00232808 *x*dy + -2.17887e-05 *x*y + 1.01693 *dx*dy*lambda + -0.795778 *dx*dy*lens_ipow(lambda, 2)+0.0f;
const float dx24 =  + -0.00359449 *x + 0.00509011 *x*lambda + 0.508466 *dx*lens_ipow(dy, 2) + -0.795778 *dx*lens_ipow(dy, 2)*lambda + 0.000113727 *lens_ipow(y, 2)*lens_ipow(dx, 3) + 0.000352479 *lens_ipow(x, 2)*lens_ipow(dx, 3)+0.0f;
const float dx30 =  + 0.0019257 *dx*dy + -2.32218e-05 *y*dx + 3.49634e-06 *x*y+0.0f;
const float dx31 =  + -0.00702857  + -0.000818453 *lambda + -6.04879e-05 *y*dy + 5.23398e-06 *lens_ipow(y, 2) + -2.32218e-05 *x*dx + 1.74817e-06 *lens_ipow(x, 2) + -0.0200532 *lens_ipow(dx, 2)*lens_ipow(lambda, 2) + 0.000341439 *y*lens_ipow(dy, 3) + 0.0241728 *lens_ipow(dx, 2)*lens_ipow(lambda, 3)+0.0f;
const float dx32 =  + 0.673157 *dx*dy + 0.0019257 *x*dy + -2.32218e-05 *x*y + -0.0401063 *y*dx*lens_ipow(lambda, 2) + 0.0483456 *y*dx*lens_ipow(lambda, 3)+0.0f;
const float dx33 =  + -0.611318  + 0.0105566 *lambda + 0.715756 *lens_ipow(dy, 2) + 0.336579 *lens_ipow(dx, 2) + -3.02439e-05 *lens_ipow(y, 2) + 0.0019257 *x*dx + 0.000512159 *lens_ipow(y, 2)*lens_ipow(dy, 2)+0.0f;
const float dx34 =  + 0.0105566 *dy + -0.000818453 *y + -0.0401063 *y*lens_ipow(dx, 2)*lambda + 0.0725184 *y*lens_ipow(dx, 2)*lens_ipow(lambda, 2)+0.0f;
const float dx40 =  + -0.00401476 *dx*lens_ipow(dy, 2) + -0.00498555 *lens_ipow(dx, 3) + -0.000123777 *y*dx*dy + -0.000241972 *x*lens_ipow(dx, 2)+0.0f;
const float dx41 =  + -0.00502705 *lens_ipow(dy, 3) + -0.00400387 *lens_ipow(dx, 2)*dy + -0.000245989 *y*lens_ipow(dy, 2) + -0.000123777 *x*dx*dy+0.0f;
const float dx42 =  + -0.926641 *dx*lens_ipow(dy, 2) + -1.00321 *lens_ipow(dx, 3) + -0.00800775 *y*dx*dy + -0.00401476 *x*lens_ipow(dy, 2) + -0.0149567 *x*lens_ipow(dx, 2) + -0.000123777 *x*y*dy + -0.000241972 *lens_ipow(x, 2)*dx+0.0f;
const float dx43 =  + -1.00134 *lens_ipow(dy, 3) + -0.926641 *lens_ipow(dx, 2)*dy + -0.0150812 *y*lens_ipow(dy, 2) + -0.00400387 *y*lens_ipow(dx, 2) + -0.000245989 *lens_ipow(y, 2)*dy + -0.00802951 *x*dx*dy + -0.000123777 *x*y*dx+0.0f;
const float dx44 =  + 0.845399  + -2.3178 *lambda + 1.68075 *lens_ipow(lambda, 2)+0.0f;
} break;
