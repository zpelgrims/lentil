case angenieux_double_gauss_test_low_degree_low_coefficients_9999_50mm:
{
const float dx00 =  + 0.198375  + 0.0827756 *lambda + -0.115596 *lens_ipow(dy, 2) + -0.22334 *lens_ipow(dx, 2) + -0.000452834 *lens_ipow(y, 2) + -0.00101517 *lens_ipow(x, 2) + -3.2201e-06 *lens_ipow(x, 4) + -1.87796e-08 *lens_ipow(x, 2)*lens_ipow(y, 4) + -1.03034e-08 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const float dx01 =  + -0.108256 *dx*dy + -0.000905668 *x*y + -2.50395e-08 *lens_ipow(x, 3)*lens_ipow(y, 3) + -4.12137e-09 *lens_ipow(x, 5)*y+0.0f;
const float dx02 =  + 28.196  + 1.80766 *lambda + -15.8914 *lens_ipow(dy, 2) + -47.7235 *lens_ipow(dx, 2) + -0.108256 *y*dy + -0.44668 *x*dx+0.0f;
const float dx03 =  + -31.7828 *dx*dy + -0.108256 *y*dx + -0.231192 *x*dy+0.0f;
const float dx04 =  + 1.80766 *dx + 0.0827756 *x+0.0f;
const float dx10 =  + -0.106337 *dx*dy + -0.00057765 *x*y + -3.11752e-06 *x*lens_ipow(y, 3) + -3.03949e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx11 =  + 0.194886  + 0.0825992 *lambda + -0.223052 *lens_ipow(dy, 2) + -0.11646 *lens_ipow(dx, 2) + -0.000903643 *lens_ipow(y, 2) + -0.000288825 *lens_ipow(x, 2) + -3.59118e-06 *lens_ipow(y, 4) + -4.67629e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -7.59872e-07 *lens_ipow(x, 4)+0.0f;
const float dx12 =  + -31.8032 *dx*dy + -0.23292 *y*dx + -0.106337 *x*dy+0.0f;
const float dx13 =  + 28.218  + 1.77846 *lambda + -47.8306 *lens_ipow(dy, 2) + -15.9016 *lens_ipow(dx, 2) + -0.446103 *y*dy + -0.106337 *x*dx+0.0f;
const float dx14 =  + 1.77846 *dy + 0.0825992 *y+0.0f;
const float dx20 =  + -0.0327482  + 0.0048542 *lambda + -0.0135352 *lens_ipow(dy, 2) + -0.0389084 *lens_ipow(dx, 2) + -2.33245e-05 *lens_ipow(y, 2) + -8.8994e-05 *lens_ipow(x, 2) + -6.10127e-08 *lens_ipow(y, 4) + 6.40966e-06 *lens_ipow(x, 2)*y*dy + -2.07976e-09 *lens_ipow(x, 4)*lens_ipow(y, 2) + 6.20845e-08 *lens_ipow(x, 5)*dx+0.0f;
const float dx21 =  + -0.0256088 *dx*dy + -4.6649e-05 *x*y + -2.44051e-07 *x*lens_ipow(y, 3) + 2.13655e-06 *lens_ipow(x, 3)*dy + -8.31904e-10 *lens_ipow(x, 5)*y+0.0f;
const float dx22 =  + 0.41025  + -0.563158 *lens_ipow(dy, 2) + -1.67586 *lens_ipow(dx, 2) + -0.0256088 *y*dy + -0.0778168 *x*dx + 1.03474e-08 *lens_ipow(x, 6)+0.0f;
const float dx23 =  + -1.12632 *dx*dy + -0.0256088 *y*dx + -0.0270704 *x*dy + 2.13655e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx24 =  + 0.0048542 *x+0.0f;
const float dx30 =  + -0.0249135 *dx*dy + 0.000303941 *y*dx + -4.24426e-05 *x*y + -2.43112e-07 *lens_ipow(x, 3)*y + -9.98216e-10 *x*lens_ipow(y, 5)+0.0f;
const float dx31 =  + -0.032852  + 0.00487978 *lambda + -0.0358763 *lens_ipow(dy, 2) + -0.012325 *lens_ipow(dx, 2) + -8.9109e-05 *lens_ipow(y, 2) + 0.000303941 *x*dx + -2.12213e-05 *lens_ipow(x, 2) + 9.7801e-06 *lens_ipow(y, 3)*dy + -6.0778e-08 *lens_ipow(x, 4) + -2.49554e-09 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const float dx32 =  + -1.07536 *dx*dy + -0.02465 *y*dx + -0.0249135 *x*dy + 0.000303941 *x*y+0.0f;
const float dx33 =  + 0.405052  + -1.56505 *lens_ipow(dy, 2) + -0.53768 *lens_ipow(dx, 2) + -0.0717526 *y*dy + -0.0249135 *x*dx + 2.44503e-06 *lens_ipow(y, 4)+0.0f;
const float dx34 =  + 0.00487978 *y+0.0f;
const float dx40 =  + 0.00474008 *lens_ipow(dx, 3) + -4.27798e-07 *x*lens_ipow(y, 2) + 0.000138178 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2) + -1.34612e-09 *lens_ipow(x, 5)+0.0f;
const float dx41 =  + 0.00474008 *lens_ipow(dy, 3) + -4.27798e-07 *lens_ipow(x, 2)*y + 0.000134261 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + -1.37229e-09 *lens_ipow(y, 5)+0.0f;
const float dx42 =  + -0.90026 *dx*lens_ipow(dy, 2) + -0.886473 *lens_ipow(dx, 3) + 0.0142202 *x*lens_ipow(dx, 2) + 8.95073e-05 *lens_ipow(y, 3)*dx*dy + 4.60595e-05 *lens_ipow(x, 3)*lens_ipow(dy, 2)+0.0f;
const float dx43 =  + -0.886514 *lens_ipow(dy, 3) + -0.90026 *lens_ipow(dx, 2)*dy + 0.0142202 *y*lens_ipow(dy, 2) + 4.47536e-05 *lens_ipow(y, 3)*lens_ipow(dx, 2) + 9.21189e-05 *lens_ipow(x, 3)*dx*dy+0.0f;
const float dx44 =  + 0.599547  + -1.65165 *lambda + 1.20103 *lens_ipow(lambda, 2)+0.0f;
} break;
