case angenieux__double_gauss__1953__49mm:
{
const double dx00 =  + 0.192185  + 0.084184 *lambda + -0.111422 *lens_ipow(dy, 2) + -0.192698 *lens_ipow(dx, 2) + -0.000294599 *lens_ipow(y, 2) + -0.000913174 *lens_ipow(x, 2) + -8.35927e-07 *lens_ipow(y, 4) + -5.16013e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + 3.99235e-05 *lens_ipow(x, 3)*dx + -3.64498e-06 *lens_ipow(x, 4) + 0.000826769 *lens_ipow(x, 2)*y*lens_ipow(dx, 2)*dy+0.0f;
const double dx01 =  + -0.0879496 *dx*dy + -0.000589197 *x*y + -3.34371e-06 *x*lens_ipow(y, 3) + -3.44009e-06 *lens_ipow(x, 3)*y + 0.00027559 *lens_ipow(x, 3)*lens_ipow(dx, 2)*dy+0.0f;
const double dx02 =  + 27.5808  + 1.76587 *lambda + -15.2207 *lens_ipow(dy, 2) + -45.4557 *lens_ipow(dx, 2) + -0.0879496 *y*dy + -0.385395 *x*dx + 9.98088e-06 *lens_ipow(x, 4) + 0.000551179 *lens_ipow(x, 3)*y*dx*dy+0.0f;
const double dx03 =  + -30.4413 *dx*dy + -0.0879496 *y*dx + -0.222844 *x*dy + 0.00027559 *lens_ipow(x, 3)*y*lens_ipow(dx, 2)+0.0f;
const double dx04 =  + 1.76587 *dx + 0.084184 *x+0.0f;
const double dx10 =  + -0.000596344 *x*y + -0.160158 *dx*dy*lambda + -3.46983e-06 *x*lens_ipow(y, 3) + -3.22545e-06 *lens_ipow(x, 3)*y + 0.000257524 *lens_ipow(y, 3)*dx*lens_ipow(dy, 2)+0.0f;
const double dx11 =  + 0.18399  + 0.102705 *lambda + -0.00116621 *lens_ipow(y, 2) + -0.000298172 *lens_ipow(x, 2) + -0.337615 *lens_ipow(dy, 2)*lambda + -0.2008 *lens_ipow(dx, 2)*lambda + 4.43453e-05 *lens_ipow(y, 3)*dy + -5.20475e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -8.06362e-07 *lens_ipow(x, 4) + -1.15387e-08 *lens_ipow(y, 6) + 0.000772572 *x*lens_ipow(y, 2)*dx*lens_ipow(dy, 2)+0.0f;
const double dx12 =  + -30.437 *dx*dy + -0.401601 *y*dx*lambda + -0.160158 *x*dy*lambda + 0.000257524 *x*lens_ipow(y, 3)*lens_ipow(dy, 2)+0.0f;
const double dx13 =  + 27.7726  + 1.41182 *lambda + -45.3593 *lens_ipow(dy, 2) + -15.2185 *lens_ipow(dx, 2) + -0.67523 *y*dy*lambda + -0.160158 *x*dx*lambda + 1.10863e-05 *lens_ipow(y, 4) + 0.000515048 *x*lens_ipow(y, 3)*dx*dy+0.0f;
const double dx14 =  + 1.41182 *dy + 0.102705 *y + -0.337615 *y*lens_ipow(dy, 2) + -0.2008 *y*lens_ipow(dx, 2) + -0.160158 *x*dx*dy+0.0f;
const double dx20 =  + -0.0340827  + 0.00505201 *lambda + -0.0120929 *lens_ipow(dy, 2) + -0.0355752 *lens_ipow(dx, 2) + 0.000406518 *y*dy + -1.40543e-05 *lens_ipow(y, 2) + -7.5477e-05 *lens_ipow(x, 2) + -7.4543e-08 *lens_ipow(y, 4) + 5.29755e-06 *x*lens_ipow(y, 2)*dx + -3.68278e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + 9.20098e-06 *lens_ipow(x, 3)*dx + -7.48267e-10 *lens_ipow(x, 6)+0.0f;
const double dx21 =  + -0.0232404 *dx*dy + 0.000406518 *x*dy + -2.81087e-05 *x*y + -2.98172e-07 *x*lens_ipow(y, 3) + 5.29755e-06 *lens_ipow(x, 2)*y*dx + -2.45519e-07 *lens_ipow(x, 3)*y+0.0f;
const double dx22 =  + 0.400723  + -0.498788 *lens_ipow(dy, 2) + -1.51165 *lens_ipow(dx, 2) + -0.0232404 *y*dy + -0.0711505 *x*dx + 2.64878e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + 2.30025e-06 *lens_ipow(x, 4)+0.0f;
const double dx23 =  + -0.997576 *dx*dy + -0.0232404 *y*dx + -0.0241858 *x*dy + 0.000406518 *x*y+0.0f;
const double dx24 =  + 0.00505201 *x+0.0f;
const double dx30 =  + -0.0239076 *dx*dy + -6.14359e-05 *x*y + 2.36667e-06 *lens_ipow(y, 3)*dx + -8.06356e-10 *x*lens_ipow(y, 5) + 9.6298e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy + 7.7472e-08 *lens_ipow(x, 4)*y*dx+0.0f;
const double dx31 =  + -0.0339432  + 0.0051504 *lambda + -0.0352836 *lens_ipow(dy, 2) + -0.0127479 *lens_ipow(dx, 2) + -7.89202e-05 *lens_ipow(y, 2) + -3.0718e-05 *lens_ipow(x, 2) + 1.07148e-05 *lens_ipow(y, 3)*dy + 7.10001e-06 *x*lens_ipow(y, 2)*dx + -5.66547e-10 *lens_ipow(y, 6) + -2.01589e-09 *lens_ipow(x, 2)*lens_ipow(y, 4) + 4.8149e-08 *lens_ipow(x, 4)*y*dy + 1.54944e-08 *lens_ipow(x, 5)*dx+0.0f;
const double dx32 =  + -1.01674 *dx*dy + -0.0254957 *y*dx + -0.0239076 *x*dy + 2.36667e-06 *x*lens_ipow(y, 3) + 1.54944e-08 *lens_ipow(x, 5)*y+0.0f;
const double dx33 =  + 0.399397  + -1.49713 *lens_ipow(dy, 2) + -0.508372 *lens_ipow(dx, 2) + -0.0705673 *y*dy + -0.0239076 *x*dx + 2.67869e-06 *lens_ipow(y, 4) + 2.40745e-08 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const double dx34 =  + 0.0051504 *y+0.0f;
const double dx40 =  + 0.00461889 *dx*lens_ipow(dy, 2) + -4.37298e-07 *x*lens_ipow(y, 2) + 0.000111469 *lens_ipow(x, 2)*lens_ipow(dx, 3) + -1.41203e-09 *lens_ipow(x, 5) + 0.000213288 *lens_ipow(y, 2)*lens_ipow(dx, 5) + -9.88321e-06 *lens_ipow(x, 3)*lens_ipow(dy, 4)+0.0f;
const double dx41 =  + 0.00506136 *lens_ipow(dy, 3) + -4.37298e-07 *lens_ipow(x, 2)*y + 0.000148721 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + -1.5161e-09 *lens_ipow(y, 5) + 0.000426576 *x*y*lens_ipow(dx, 5)+0.0f;
const double dx42 =  + -0.913384 *dx*lens_ipow(dy, 2) + -0.924934 *lens_ipow(dx, 3) + 0.00461889 *x*lens_ipow(dy, 2) + 9.91471e-05 *lens_ipow(y, 3)*dx*dy + 0.000111469 *lens_ipow(x, 3)*lens_ipow(dx, 2) + 0.00106644 *x*lens_ipow(y, 2)*lens_ipow(dx, 4)+0.0f;
const double dx43 =  + -0.843996 *lens_ipow(dy, 3) + -0.913384 *lens_ipow(dx, 2)*dy + 0.0151841 *y*lens_ipow(dy, 2) + 0.00923778 *x*dx*dy + 4.95736e-05 *lens_ipow(y, 3)*lens_ipow(dx, 2) + -9.88321e-06 *lens_ipow(x, 4)*lens_ipow(dy, 3)+0.0f;
const double dx44 =  + 0.60193  + -1.65875 *lambda + 1.2063 *lens_ipow(lambda, 2)+0.0f;
} break;
