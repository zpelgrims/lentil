case angenieux_double_gauss_test_low_degree_low_coefficients_9999_49mm:
{
const float dx00 =  + 0.194212  + 0.0836355 *lambda + -0.115429 *lens_ipow(dy, 2) + -0.224427 *lens_ipow(dx, 2) + -0.000294934 *lens_ipow(y, 2) + -0.000941882 *lens_ipow(x, 2) + -8.60107e-07 *lens_ipow(y, 4) + -5.0296e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -3.89037e-06 *lens_ipow(x, 4)+0.0f;
const float dx01 =  + -0.108718 *dx*dy + -0.000589868 *x*y + -3.44043e-06 *x*lens_ipow(y, 3) + -3.35307e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx02 =  + 27.6412  + 1.76473 *lambda + -15.6427 *lens_ipow(dy, 2) + -46.8504 *lens_ipow(dx, 2) + -0.108718 *y*dy + -0.448854 *x*dx+0.0f;
const float dx03 =  + -31.2853 *dx*dy + -0.108718 *y*dx + -0.230859 *x*dy+0.0f;
const float dx04 =  + 1.76473 *dx + 0.0836355 *x+0.0f;
const float dx10 =  + -0.000594603 *x*y + -0.190213 *dx*dy*lambda + -3.41265e-06 *x*lens_ipow(y, 3) + -3.32099e-06 *lens_ipow(x, 3)*y+0.0f;
const float dx11 =  + 0.182264  + 0.10441 *lambda + -0.000924192 *lens_ipow(y, 2) + -0.000297301 *lens_ipow(x, 2) + -0.397297 *lens_ipow(dy, 2)*lambda + -0.208492 *lens_ipow(dx, 2)*lambda + -3.97019e-06 *lens_ipow(y, 4) + -5.11898e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -8.30246e-07 *lens_ipow(x, 4)+0.0f;
const float dx12 =  + -31.192 *dx*dy + -0.416984 *y*dx*lambda + -0.190213 *x*dy*lambda+0.0f;
const float dx13 =  + 27.8704  + 1.35479 *lambda + -46.838 *lens_ipow(dy, 2) + -15.596 *lens_ipow(dx, 2) + -0.794593 *y*dy*lambda + -0.190213 *x*dx*lambda+0.0f;
const float dx14 =  + 1.35479 *dy + 0.10441 *y + -0.397297 *y*lens_ipow(dy, 2) + -0.208492 *y*lens_ipow(dx, 2) + -0.190213 *x*dx*dy+0.0f;
const float dx20 =  + -0.0361616  + 0.00518241 *lambda + -0.0326008 *lens_ipow(dx, 2) + 0.00054533 *y*dy + -1.02676e-07 *lens_ipow(y, 4) + 6.74692e-06 *x*lens_ipow(y, 2)*dx + -0.000252971 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -5.55216e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + 1.08669e-05 *lens_ipow(x, 3)*dx + -4.36022e-07 *lens_ipow(x, 4)+0.0f;
const float dx21 =  + -0.0203897 *dx*dy + 0.00054533 *x*dy + -4.10704e-07 *x*lens_ipow(y, 3) + 6.74692e-06 *lens_ipow(x, 2)*y*dx + -3.70144e-07 *lens_ipow(x, 3)*y+0.0f;
const float dx22 =  + 0.400532  + -0.465621 *lens_ipow(dy, 2) + -1.50433 *lens_ipow(dx, 2) + -0.0203897 *y*dy + -0.0652016 *x*dx + 3.37346e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + 2.71672e-06 *lens_ipow(x, 4)+0.0f;
const float dx23 =  + -0.931242 *dx*dy + -0.0203897 *y*dx + 0.00054533 *x*y + -0.000168647 *lens_ipow(x, 3)*dy+0.0f;
const float dx24 =  + 0.00518241 *x+0.0f;
const float dx30 =  + -0.020712 *dx*dy + 0.000536109 *y*dx + 6.47451e-06 *x*lens_ipow(y, 2)*dy + -3.79957e-07 *x*lens_ipow(y, 3) + -4.02969e-07 *lens_ipow(x, 3)*y+0.0f;
const float dx31 =  + -0.0360984  + 0.00512937 *lambda + -0.0330539 *lens_ipow(dy, 2) + 0.000536109 *x*dx + -0.000259011 *lens_ipow(y, 2)*lens_ipow(dx, 2) + 1.06811e-05 *lens_ipow(y, 3)*dy + -4.39204e-07 *lens_ipow(y, 4) + 6.47451e-06 *lens_ipow(x, 2)*y*dy + -5.69936e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -1.00742e-07 *lens_ipow(x, 4)+0.0f;
const float dx32 =  + -0.94478 *dx*dy + -0.020712 *x*dy + 0.000536109 *x*y + -0.000172674 *lens_ipow(y, 3)*dx+0.0f;
const float dx33 =  + 0.401117  + -1.51828 *lens_ipow(dy, 2) + -0.47239 *lens_ipow(dx, 2) + -0.0661077 *y*dy + -0.020712 *x*dx + 2.67028e-06 *lens_ipow(y, 4) + 3.23726e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)+0.0f;
const float dx34 =  + 0.00512937 *y+0.0f;
const float dx40 =  + -3.95403e-07 *x*lens_ipow(y, 2) + -2.79086e-07 *lens_ipow(x, 3) + 0.0277661 *lens_ipow(dx, 5) + 0.000155883 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2)+0.0f;
const float dx41 =  + 0.00519102 *lens_ipow(dy, 3) + -0.000169766 *y*lens_ipow(dx, 2) + -3.95403e-07 *lens_ipow(x, 2)*y + 0.0227674 *lens_ipow(dx, 4)*dy + -1.61685e-09 *lens_ipow(y, 5)+0.0f;
const float dx42 =  + -0.965449 *dx*lens_ipow(dy, 2) + -0.779871 *lens_ipow(dx, 3) + -0.000169766 *lens_ipow(y, 2)*dx + 0.0910697 *y*lens_ipow(dx, 3)*dy + 0.13883 *x*lens_ipow(dx, 4) + 5.1961e-05 *lens_ipow(x, 3)*lens_ipow(dy, 2)+0.0f;
const float dx43 =  + -0.867546 *lens_ipow(dy, 3) + -0.965449 *lens_ipow(dx, 2)*dy + 0.0155731 *y*lens_ipow(dy, 2) + 0.0227674 *y*lens_ipow(dx, 4) + 0.000103922 *lens_ipow(x, 3)*dx*dy+0.0f;
const float dx44 =  + 0.241839  + -0.330918 *lambda+0.0f;
} break;
