case angenieux_double_gauss_1953_49mm:
{
const float dx00 =  + -0.513328  + 0.192173 *lambda + 0.253296 *lens_ipow(dy, 2) + 0.319553 *lens_ipow(dx, 2) + 0.0060597 *y*dy + -0.00117189 *lens_ipow(y, 2) + 0.0270347 *x*dx + -0.00256401 *lens_ipow(x, 2) + -6.93084e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -6.91908e-06 *lens_ipow(x, 4)+0.0f;
const float dx01 =  + 0.0060597 *x*dy + -0.00234378 *x*y + 0.000107169 *lens_ipow(y, 3)*dx + -4.62056e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx02 =  + 49.1433  + -20.335 *lens_ipow(dy, 2) + -59.7317 *lens_ipow(dx, 2) + 0.639107 *x*dx + 0.0135173 *lens_ipow(x, 2) + 2.67923e-05 *lens_ipow(y, 4)+0.0f;
const float dx03 =  + -40.67 *dx*dy + 0.506591 *x*dy + 0.0060597 *x*y+0.0f;
const float dx04 =  + 0.192173 *x+0.0f;
const float dx10 =  + 0.0059326 *y*dx + -0.00233199 *x*y + -4.8282e-06 *x*lens_ipow(y, 3) + 0.000105308 *lens_ipow(x, 3)*dy+0.0f;
const float dx11 =  + -0.513863  + 0.19164 *lambda + 0.32836 *lens_ipow(dy, 2) + 0.253447 *lens_ipow(dx, 2) + 0.027528 *y*dy + -0.00253893 *lens_ipow(y, 2) + 0.0059326 *x*dx + -0.001166 *lens_ipow(x, 2) + -6.98441e-06 *lens_ipow(y, 4) + -7.24231e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)+0.0f;
const float dx12 =  + -40.7058 *dx*dy + 0.506894 *y*dx + 0.0059326 *x*y+0.0f;
const float dx13 =  + 49.1383  + -59.5604 *lens_ipow(dy, 2) + -20.3529 *lens_ipow(dx, 2) + 0.656719 *y*dy + 0.013764 *lens_ipow(y, 2) + 2.6327e-05 *lens_ipow(x, 4)+0.0f;
const float dx14 =  + 0.19164 *y+0.0f;
const float dx20 =  + -0.0136628  + -0.00255248 *lambda + -0.0024947 *lens_ipow(dy, 2) + -0.00010505 *y*dy + 9.13473e-06 *lens_ipow(y, 2) + 3.34674e-05 *lens_ipow(x, 2) + 2.50396e-08 *lens_ipow(y, 4) + 7.05324e-05 *x*y*dx*dy + 1.54234e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -2.33106e-06 *lens_ipow(x, 3)*dx + 9.49917e-08 *lens_ipow(x, 4)+0.0f;
const float dx21 =  + -0.00010505 *x*dy + 1.82695e-05 *x*y + 1.00158e-07 *x*lens_ipow(y, 3) + 3.52662e-05 *lens_ipow(x, 2)*dx*dy + 1.02822e-07 *lens_ipow(x, 3)*y+0.0f;
const float dx22 =  + -0.609131  + 0.167611 *lens_ipow(dy, 2) + 0.818327 *lens_ipow(dx, 2) + 3.52662e-05 *lens_ipow(x, 2)*y*dy + -5.82766e-07 *lens_ipow(x, 4)+0.0f;
const float dx23 =  + 0.335222 *dx*dy + -0.00498941 *x*dy + -0.00010505 *x*y + 3.52662e-05 *lens_ipow(x, 2)*y*dx+0.0f;
const float dx24 =  + -0.00255248 *x+0.0f;
const float dx30 =  + 0.00468285 *dx*dy + -0.000103711 *y*dx + 1.99044e-05 *x*y + 1.07587e-07 *x*lens_ipow(y, 3) + 1.0515e-07 *lens_ipow(x, 3)*y+0.0f;
const float dx31 =  + -0.0136392  + -0.00251221 *lambda + -0.00451731 *lens_ipow(dx, 2) + 3.06973e-05 *lens_ipow(y, 2) + -0.000103711 *x*dx + 9.95221e-06 *lens_ipow(x, 2) + -2.26542e-06 *lens_ipow(y, 3)*dy + 1.04849e-07 *lens_ipow(y, 4) + 1.61381e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + 2.62875e-08 *lens_ipow(x, 4)+0.0f;
const float dx32 =  + 0.739186 *dx*dy + -0.00903462 *y*dx + 0.00468285 *x*dy + -0.000103711 *x*y+0.0f;
const float dx33 =  + -0.612494  + 0.838341 *lens_ipow(dy, 2) + 0.369593 *lens_ipow(dx, 2) + 0.00468285 *x*dx + -5.66354e-07 *lens_ipow(y, 4)+0.0f;
const float dx34 =  + -0.00251221 *y+0.0f;
const float dx40 =  + -0.00106248 *dx + 7.34702e-06 *lens_ipow(y, 2)*dx + -0.000455699 *x*lens_ipow(dx, 2) + -3.31398e-07 *lens_ipow(x, 3) + 9.36392e-05 *x*y*lens_ipow(dy, 3)+0.0f;
const float dx41 =  + -0.0106736 *lens_ipow(dy, 3) + -0.000602337 *y*lens_ipow(dy, 2) + -2.41291e-07 *lens_ipow(y, 3) + 1.4694e-05 *x*y*dx + 4.68196e-05 *lens_ipow(x, 2)*lens_ipow(dy, 3)+0.0f;
const float dx42 =  + -0.00106248 *x + -0.902476 *lens_ipow(dx, 3) + 7.34702e-06 *x*lens_ipow(y, 2) + -0.000455699 *lens_ipow(x, 2)*dx + -1.49936 *dx*lens_ipow(dy, 2)*lambda+0.0f;
const float dx43 =  + -1.05337 *lens_ipow(dy, 3) + -0.0320209 *y*lens_ipow(dy, 2) + -0.000602337 *lens_ipow(y, 2)*dy + -1.49936 *lens_ipow(dx, 2)*dy*lambda + 0.000140459 *lens_ipow(x, 2)*y*lens_ipow(dy, 2)+0.0f;
const float dx44 =  + 0.348986  + -0.472646 *lambda + -0.749681 *lens_ipow(dx, 2)*lens_ipow(dy, 2)+0.0f;
} break;
