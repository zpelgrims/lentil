case angenieux_double_gauss_test_low_degree_low_coefficients_9999_50mm:
{
const float dx00 =  + 0.195015  + 0.0827779 *lambda + -0.115813 *lens_ipow(dy, 2) + -0.223652 *lens_ipow(dx, 2) + -0.000287134 *lens_ipow(y, 2) + -0.000921232 *lens_ipow(x, 2) + -7.82062e-07 *lens_ipow(y, 4) + -4.5885e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -3.4898e-06 *lens_ipow(x, 4)+0.0f;
const float dx01 =  + -0.107283 *dx*dy + -0.000574268 *x*y + -3.12825e-06 *x*lens_ipow(y, 3) + -3.059e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx02 =  + 28.2028  + 1.80203 *lambda + -15.9536 *lens_ipow(dy, 2) + -47.749 *lens_ipow(dx, 2) + -0.107283 *y*dy + -0.447305 *x*dx+0.0f;
const float dx03 =  + -31.9073 *dx*dy + -0.107283 *y*dx + -0.231626 *x*dy+0.0f;
const float dx04 =  + 1.80203 *dx + 0.0827779 *x+0.0f;
const float dx10 =  + -0.106337 *dx*dy + -0.00057765 *x*y + -3.11752e-06 *x*lens_ipow(y, 3) + -3.03949e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx11 =  + 0.194886  + 0.0825992 *lambda + -0.223052 *lens_ipow(dy, 2) + -0.11646 *lens_ipow(dx, 2) + -0.000903643 *lens_ipow(y, 2) + -0.000288825 *lens_ipow(x, 2) + -3.59118e-06 *lens_ipow(y, 4) + -4.67629e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -7.59872e-07 *lens_ipow(x, 4)+0.0f;
const float dx12 =  + -31.8032 *dx*dy + -0.23292 *y*dx + -0.106337 *x*dy+0.0f;
const float dx13 =  + 28.218  + 1.77846 *lambda + -47.8306 *lens_ipow(dy, 2) + -15.9016 *lens_ipow(dx, 2) + -0.446103 *y*dy + -0.106337 *x*dx+0.0f;
const float dx14 =  + 1.77846 *dy + 0.0825992 *y+0.0f;
const float dx20 =  + -0.0353125  + 0.00499552 *lambda + -0.0247944 *lens_ipow(dx, 2) + 0.000520086 *y*dy + -9.68896e-08 *lens_ipow(y, 4) + 7.66312e-06 *x*lens_ipow(y, 2)*dx + -0.000236607 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -0.000438303 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -4.61795e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -4.38984e-07 *lens_ipow(x, 4)+0.0f;
const float dx21 =  + -0.0195668 *dx*dy + 0.000520086 *x*dy + -3.87558e-07 *x*lens_ipow(y, 3) + 7.66312e-06 *lens_ipow(x, 2)*y*dx + -3.07863e-07 *lens_ipow(x, 3)*y+0.0f;
const float dx22 =  + 0.40557  + -0.461261 *lens_ipow(dy, 2) + -1.56135 *lens_ipow(dx, 2) + -0.0195668 *y*dy + -0.0495888 *x*dx + 3.83156e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -0.000292202 *lens_ipow(x, 3)*dx+0.0f;
const float dx23 =  + -0.922521 *dx*dy + -0.0195668 *y*dx + 0.000520086 *x*y + -0.000157738 *lens_ipow(x, 3)*dy+0.0f;
const float dx24 =  + 0.00499552 *x+0.0f;
const float dx30 =  + -0.0198376 *dx*dy + 0.000518584 *y*dx + 7.68508e-06 *x*lens_ipow(y, 2)*dy + -3.0954e-07 *x*lens_ipow(y, 3) + -3.85861e-07 *lens_ipow(x, 3)*y+0.0f;
const float dx31 =  + -0.0352615  + 0.00498467 *lambda + -0.0256105 *lens_ipow(dy, 2) + 0.000518584 *x*dx + -0.000423582 *lens_ipow(y, 2)*lens_ipow(dy, 2) + -0.0002424 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -4.45114e-07 *lens_ipow(y, 4) + 7.68508e-06 *lens_ipow(x, 2)*y*dy + -4.6431e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -9.64654e-08 *lens_ipow(x, 4)+0.0f;
const float dx32 =  + -0.934194 *dx*dy + -0.0198376 *x*dy + 0.000518584 *x*y + -0.0001616 *lens_ipow(y, 3)*dx+0.0f;
const float dx33 =  + 0.406097  + -1.57618 *lens_ipow(dy, 2) + -0.467097 *lens_ipow(dx, 2) + -0.0512211 *y*dy + -0.0198376 *x*dx + -0.000282388 *lens_ipow(y, 3)*dy + 3.84254e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)+0.0f;
const float dx34 =  + 0.00498467 *y+0.0f;
const float dx40 =  + -3.6583e-07 *x*lens_ipow(y, 2) + -2.51506e-07 *lens_ipow(x, 3) + 0.0201495 *lens_ipow(dx, 5) + 3.01833e-05 *lens_ipow(y, 2)*lens_ipow(dx, 3) + 0.000144914 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2)+0.0f;
const float dx41 =  + 0.00478496 *lens_ipow(dy, 3) + -3.6583e-07 *lens_ipow(x, 2)*y + 0.000144342 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + -1.41131e-09 *lens_ipow(y, 5) + 6.03666e-05 *x*y*lens_ipow(dx, 3)+0.0f;
const float dx42 =  + -0.950887 *dx*lens_ipow(dy, 2) + -0.856598 *lens_ipow(dx, 3) + 9.62281e-05 *lens_ipow(y, 3)*dx*dy + 0.100747 *x*lens_ipow(dx, 4) + 9.055e-05 *x*lens_ipow(y, 2)*lens_ipow(dx, 2) + 4.83047e-05 *lens_ipow(x, 3)*lens_ipow(dy, 2)+0.0f;
const float dx43 =  + -0.871787 *lens_ipow(dy, 3) + -0.950887 *lens_ipow(dx, 2)*dy + 0.0143549 *y*lens_ipow(dy, 2) + 4.81141e-05 *lens_ipow(y, 3)*lens_ipow(dx, 2) + 9.66094e-05 *lens_ipow(x, 3)*dx*dy+0.0f;
const float dx44 =  + 0.241685  + -0.330588 *lambda+0.0f;
} break;
