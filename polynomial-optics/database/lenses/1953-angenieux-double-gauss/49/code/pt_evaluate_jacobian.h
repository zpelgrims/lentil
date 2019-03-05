case angenieux_double_gauss_1953_49mm:
{
const float dx00 =  + -0.645099  + 0.721375 *lambda + -0.555092 *lens_ipow(lambda, 2) + 0.269599 *lens_ipow(dy, 2) + 0.549184 *lens_ipow(dx, 2) + 0.007716 *y*dy + -0.00130559 *lens_ipow(y, 2) + -0.00316481 *lens_ipow(x, 2) + 0.000559786 *lens_ipow(y, 2)*lambda + 0.080428 *x*dx*lambda + 0.00152178 *lens_ipow(x, 2)*lambda + 0.0759788 *y*lens_ipow(dx, 2)*dy + -0.00702865 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -7.98427e-06 *lens_ipow(x, 4) + -3.83629e-06 *lens_ipow(y, 4)*lens_ipow(dx, 2) + -2.63138e-09 *lens_ipow(y, 6) + -5.35178e-07 *lens_ipow(x, 2)*lens_ipow(y, 3)*dy + -3.21426e-08 *lens_ipow(x, 2)*lens_ipow(y, 4) + -0.00121857 *lens_ipow(x, 3)*dx*lens_ipow(lambda, 2) + -4.26827e-08 *lens_ipow(x, 4)*lens_ipow(y, 2) + 4.86567e-06 *lens_ipow(x, 5)*dx*lens_ipow(lambda, 3)+0.0f;
const float dx01 =  + 0.193832 *dx*dy + 0.0102074 *y*dx + 0.007716 *x*dy + -0.00261117 *x*y + 0.00111957 *x*y*lambda + 0.0721834 *y*dx*lens_ipow(dy, 2) + 0.0759788 *x*lens_ipow(dx, 2)*dy + -1.71152e-05 *lens_ipow(y, 4)*dx*dy + -1.53452e-05 *x*lens_ipow(y, 3)*lens_ipow(dx, 2) + -1.57883e-08 *x*lens_ipow(y, 5) + -5.35178e-07 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy + -4.28568e-08 *lens_ipow(x, 3)*lens_ipow(y, 3) + -1.70731e-08 *lens_ipow(x, 5)*y+0.0f;
const float dx02 =  + 48.8821  + -19.6882 *lens_ipow(dy, 2) + -56.8491 *lens_ipow(dx, 2) + 0.193832 *y*dy + 0.00510371 *lens_ipow(y, 2) + 1.09837 *x*dx + 0.040214 *lens_ipow(x, 2)*lambda + 0.0360917 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 0.151958 *x*y*dx*dy + -0.00468577 *lens_ipow(x, 3)*dx + -3.42304e-06 *lens_ipow(y, 5)*dy + -7.67258e-06 *x*lens_ipow(y, 4)*dx + -0.000304642 *lens_ipow(x, 4)*lens_ipow(lambda, 2) + 8.10945e-07 *lens_ipow(x, 6)*lens_ipow(lambda, 3)+0.0f;
const float dx03 =  + -39.3765 *dx*dy + 0.193832 *y*dx + 0.539198 *x*dy + 0.007716 *x*y + 0.0721834 *lens_ipow(y, 2)*dx*dy + 0.0759788 *x*y*lens_ipow(dx, 2) + -3.42304e-06 *lens_ipow(y, 5)*dx + -1.78393e-07 *lens_ipow(x, 3)*lens_ipow(y, 3)+0.0f;
const float dx04 =  + 0.721375 *x + -1.11018 *x*lambda + 0.000559786 *x*lens_ipow(y, 2) + 0.040214 *lens_ipow(x, 2)*dx + 0.000507259 *lens_ipow(x, 3) + -0.000609284 *lens_ipow(x, 4)*dx*lambda + 2.43284e-06 *lens_ipow(x, 6)*dx*lens_ipow(lambda, 2)+0.0f;
const float dx10 =  + 0.00537062 *y*dx + -0.00281837 *x*y + 0.277135 *dx*dy*lambda + 0.0224686 *x*dy*lambda + 0.00141272 *x*y*lambda + 0.183519 *y*dx*lens_ipow(dy, 2)*lambda + 2.6672 *dx*lens_ipow(dy, 5) + -1.84048e-08 *x*lens_ipow(y, 5) + 0.000981465 *lens_ipow(x, 3)*lens_ipow(dx, 2)*dy + -3.34952e-08 *lens_ipow(x, 3)*lens_ipow(y, 3) + -1.79407e-08 *lens_ipow(x, 5)*y+0.0f;
const float dx11 =  + -0.621037  + 0.696948 *lambda + -0.553529 *lens_ipow(lambda, 2) + 0.241088 *lens_ipow(dx, 2) + 0.0249817 *y*dy + -0.00397262 *lens_ipow(y, 2) + 0.00537062 *x*dx + -0.00140918 *lens_ipow(x, 2) + 0.38429 *lens_ipow(dy, 2)*lambda + 0.00174895 *lens_ipow(y, 2)*lambda + 0.000706359 *lens_ipow(x, 2)*lambda + 1.94318 *lens_ipow(dy, 4) + -6.60194e-05 *lens_ipow(y, 3)*dy + 0.288409 *y*lens_ipow(dy, 3)*lambda + 0.183519 *x*dx*lens_ipow(dy, 2)*lambda + 5.89866 *lens_ipow(dx, 4)*lens_ipow(dy, 2) + -2.33145e-08 *lens_ipow(y, 6) + -4.60121e-08 *lens_ipow(x, 2)*lens_ipow(y, 4) + -2.51214e-08 *lens_ipow(x, 4)*lens_ipow(y, 2) + -2.99011e-09 *lens_ipow(x, 6)+0.0f;
const float dx12 =  + -37.4735 *dx*dy + 0.482177 *y*dx + 0.00537062 *x*y + 0.277135 *x*dy*lambda + 0.183519 *x*y*lens_ipow(dy, 2)*lambda + 23.5947 *y*lens_ipow(dx, 3)*lens_ipow(dy, 2) + 2.6672 *x*lens_ipow(dy, 5) + 0.000490733 *lens_ipow(x, 4)*dx*dy+0.0f;
const float dx13 =  + 49.027  + -69.321 *lens_ipow(dy, 2) + -18.7367 *lens_ipow(dx, 2) + 0.0124908 *lens_ipow(y, 2) + 0.76858 *y*dy*lambda + 0.277135 *x*dx*lambda + 0.0112343 *lens_ipow(x, 2)*lambda + 91.0761 *lens_ipow(dy, 4) + 7.77272 *y*lens_ipow(dy, 3) + -1.65049e-05 *lens_ipow(y, 4) + 0.432614 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + 0.367039 *x*y*dx*dy*lambda + 11.7973 *y*lens_ipow(dx, 4)*dy + 13.336 *x*dx*lens_ipow(dy, 4) + 0.000245366 *lens_ipow(x, 4)*lens_ipow(dx, 2)+0.0f;
const float dx14 =  + 0.696948 *y + -1.10706 *y*lambda + 0.38429 *y*lens_ipow(dy, 2) + 0.000582984 *lens_ipow(y, 3) + 0.277135 *x*dx*dy + 0.0112343 *lens_ipow(x, 2)*dy + 0.000706359 *lens_ipow(x, 2)*y + 0.144205 *lens_ipow(y, 2)*lens_ipow(dy, 3) + 0.183519 *x*y*dx*lens_ipow(dy, 2)+0.0f;
const float dx20 =  + -0.0125123  + -0.00922338 *lambda + 0.00748852 *lens_ipow(lambda, 2) + -0.00110408 *lens_ipow(dy, 2) + -6.12117e-05 *y*dy + 1.80792e-05 *lens_ipow(y, 2) + -0.000332664 *x*dx + 5.57153e-05 *lens_ipow(x, 2) + -8.28448e-06 *lens_ipow(y, 2)*lambda + -2.42488e-05 *lens_ipow(x, 2)*lambda + -0.00449414 *lens_ipow(dy, 4) + -3.49031e-07 *lens_ipow(y, 3)*dy + 0.00143967 *x*dx*lens_ipow(dy, 2) + 0.00212179 *x*lens_ipow(dx, 3) + 7.96372e-05 *x*y*dx*dy + 7.73673e-08 *lens_ipow(x, 2)*lens_ipow(y, 2) + 4.08399e-11 *lens_ipow(y, 6) + -1.55198e-05 *lens_ipow(x, 3)*lens_ipow(dx, 3) + 2.81885e-10 *lens_ipow(x, 6) + 1.40589e-12 *lens_ipow(x, 6)*lens_ipow(y, 2) + 1.19511e-14 *lens_ipow(x, 4)*lens_ipow(y, 6) + 0.460264 *y*lens_ipow(dx, 6)*lens_ipow(dy, 3)*lambda+0.0f;
const float dx21 =  + -6.12117e-05 *x*dy + 3.61584e-05 *x*y + -1.6569e-05 *x*y*lambda + 0.0007796 *y*lens_ipow(dx, 3) + -4.83979e-07 *lens_ipow(y, 3)*dx + -1.04709e-06 *x*lens_ipow(y, 2)*dy + 3.98186e-05 *lens_ipow(x, 2)*dx*dy + 5.15782e-08 *lens_ipow(x, 3)*y + 2.4504e-10 *x*lens_ipow(y, 5) + 4.01682e-13 *lens_ipow(x, 7)*y + 1.43413e-14 *lens_ipow(x, 5)*lens_ipow(y, 5) + 0.460264 *x*lens_ipow(dx, 6)*lens_ipow(dy, 3)*lambda+0.0f;
const float dx22 =  + -0.610441  + 0.0110383 *lambda + 0.148194 *lens_ipow(dy, 2) + 0.688621 *lens_ipow(dx, 2) + -0.000166332 *lens_ipow(x, 2) + 0.0011694 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -1.20995e-07 *lens_ipow(y, 4) + 0.000719834 *lens_ipow(x, 2)*lens_ipow(dy, 2) + 0.00318269 *lens_ipow(x, 2)*lens_ipow(dx, 2) + 3.98186e-05 *lens_ipow(x, 2)*y*dy + -1.16399e-05 *lens_ipow(x, 4)*lens_ipow(dx, 2) + 2.76158 *x*y*lens_ipow(dx, 5)*lens_ipow(dy, 3)*lambda+0.0f;
const float dx23 =  + 0.296387 *dx*dy + -0.00220816 *x*dy + -6.12117e-05 *x*y + -0.0179766 *x*lens_ipow(dy, 3) + -3.49031e-07 *x*lens_ipow(y, 3) + 0.00143967 *lens_ipow(x, 2)*dx*dy + 3.98186e-05 *lens_ipow(x, 2)*y*dx + 1.38079 *x*y*lens_ipow(dx, 6)*lens_ipow(dy, 2)*lambda+0.0f;
const float dx24 =  + 0.0110383 *dx + -0.00922338 *x + 0.014977 *x*lambda + -8.28448e-06 *x*lens_ipow(y, 2) + -8.08293e-06 *lens_ipow(x, 3) + 0.460264 *x*y*lens_ipow(dx, 6)*lens_ipow(dy, 3)+0.0f;
const float dx30 =  + 0.00307779 *dx*dy + -0.000104203 *y*dx + 2.89375e-05 *x*y + 2.30472e-05 *lens_ipow(y, 2)*dx*dy + -9.67889e-07 *lens_ipow(x, 3)*dy + -9.9834e-07 *x*lens_ipow(y, 2)*dy*lambda + 7.31557e-10 *x*lens_ipow(y, 5) + 5.16782e-10 *lens_ipow(x, 3)*lens_ipow(y, 3) + 2.48418e-10 *lens_ipow(x, 5)*y + -8.99561e-10 *x*lens_ipow(y, 5)*lambda + 1.06969e-05 *lens_ipow(x, 3)*lens_ipow(dy, 3)*lambda+0.0f;
const float dx31 =  + -0.0119682  + -0.0100025 *lambda + 0.00733861 *lens_ipow(lambda, 2) + -0.00410946 *lens_ipow(dx, 2) + 4.10847e-05 *lens_ipow(y, 2) + -0.000104203 *x*dx + 1.44688e-05 *lens_ipow(x, 2) + -4.44204e-06 *lens_ipow(y, 3)*dy + 4.60945e-05 *x*y*dx*dy + -9.9834e-07 *lens_ipow(x, 2)*y*dy*lambda + 1.56957e-05 *lens_ipow(y, 3)*lens_ipow(dx, 2)*dy + 2.96985e-10 *lens_ipow(y, 6) + 1.82889e-09 *lens_ipow(x, 2)*lens_ipow(y, 4) + 3.87587e-10 *lens_ipow(x, 4)*lens_ipow(y, 2) + 4.1403e-11 *lens_ipow(x, 6) + -0.0653355 *lens_ipow(dy, 6)*lambda + 2.13318e-08 *lens_ipow(y, 5)*dy*lambda + -2.2489e-09 *lens_ipow(x, 2)*lens_ipow(y, 4)*lambda+0.0f;
const float dx32 =  + 0.845598 *dx*dy + -0.00821893 *y*dx + 0.00307779 *x*dy + -0.000104203 *x*y + -0.884979 *dx*lens_ipow(dy, 3) + -1.28197 *lens_ipow(dx, 3)*dy + 2.30472e-05 *x*lens_ipow(y, 2)*dy + 7.84783e-06 *lens_ipow(y, 4)*dx*dy+0.0f;
const float dx33 =  + -0.616863  + 0.0104117 *lambda + 0.875149 *lens_ipow(dy, 2) + 0.422799 *lens_ipow(dx, 2) + 0.00307779 *x*dx + -1.32747 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -0.320492 *lens_ipow(dx, 4) + -1.11051e-06 *lens_ipow(y, 4) + 2.30472e-05 *x*lens_ipow(y, 2)*dx + -2.41972e-07 *lens_ipow(x, 4) + -4.9917e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lambda + 3.92392e-06 *lens_ipow(y, 4)*lens_ipow(dx, 2) + -8.05524 *lens_ipow(dy, 6)*lambda + -0.392013 *y*lens_ipow(dy, 5)*lambda + 3.55529e-09 *lens_ipow(y, 6)*lambda + 8.02271e-06 *lens_ipow(x, 4)*lens_ipow(dy, 2)*lambda+0.0f;
const float dx34 =  + 0.0104117 *dy + -0.0100025 *y + 0.0146772 *y*lambda + -4.9917e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*dy + -1.15075 *lens_ipow(dy, 7) + -0.0653355 *y*lens_ipow(dy, 6) + 3.55529e-09 *lens_ipow(y, 6)*dy + -4.4978e-10 *lens_ipow(x, 2)*lens_ipow(y, 5) + 2.67424e-06 *lens_ipow(x, 4)*lens_ipow(dy, 3)+0.0f;
const float dx40 =  + -0.000554268 *dx*lambda + -0.00661154 *dx*lens_ipow(dy, 2) + -0.00811139 *lens_ipow(dx, 3) + -0.000477706 *y*dx*dy + -0.000249504 *x*lens_ipow(dy, 2) + -0.000470547 *x*lens_ipow(dx, 2) + -1.52914e-07 *x*lens_ipow(y, 2) + -1.94514e-07 *lens_ipow(x, 3) + -0.00177908 *x*lens_ipow(dx, 4) + 3.0757e-08 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx*dy + -2.33657e-16 *lens_ipow(x, 3)*lens_ipow(y, 8) + -1.75004e-16 *lens_ipow(x, 9)*lens_ipow(y, 2)+0.0f;
const float dx41 =  + -0.000559814 *dy*lambda + -0.00824271 *lens_ipow(dy, 3) + -0.00655018 *lens_ipow(dx, 2)*dy + -0.000468944 *y*lens_ipow(dy, 2) + -0.000246058 *y*lens_ipow(dx, 2) + -2.03762e-07 *lens_ipow(y, 3) + -0.000477706 *x*dx*dy + -1.52914e-07 *lens_ipow(x, 2)*y + -0.00181807 *y*lens_ipow(dy, 4) + 3.0757e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx*dy + -4.67315e-16 *lens_ipow(x, 4)*lens_ipow(y, 7) + -3.50007e-17 *lens_ipow(x, 10)*y+0.0f;
const float dx42 =  + -0.000554268 *x*lambda + -0.992548 *dx*lens_ipow(dy, 2) + -0.691441 *lens_ipow(dx, 3) + -0.0131004 *y*dx*dy + -0.000246058 *lens_ipow(y, 2)*dx + -0.00661154 *x*lens_ipow(dy, 2) + -0.0243342 *x*lens_ipow(dx, 2) + -0.000477706 *x*y*dy + -0.000470547 *lens_ipow(x, 2)*dx + -0.449267 *lens_ipow(dx, 3)*lambda + -0.00355817 *lens_ipow(x, 2)*lens_ipow(dx, 3) + 1.02523e-08 *lens_ipow(x, 3)*lens_ipow(y, 3)*dy+0.0f;
const float dx43 =  + -0.000559814 *y*lambda + -0.67714 *lens_ipow(dy, 3) + -0.992548 *lens_ipow(dx, 2)*dy + -0.0247281 *y*lens_ipow(dy, 2) + -0.00655018 *y*lens_ipow(dx, 2) + -0.000468944 *lens_ipow(y, 2)*dy + -0.0132231 *x*dx*dy + -0.000477706 *x*y*dx + -0.000249504 *lens_ipow(x, 2)*dy + -0.480698 *lens_ipow(dy, 3)*lambda + -0.00363615 *lens_ipow(y, 2)*lens_ipow(dy, 3) + 1.02523e-08 *lens_ipow(x, 3)*lens_ipow(y, 3)*dx+0.0f;
const float dx44 =  + 0.856356  + -2.34734 *lambda + 1.70336 *lens_ipow(lambda, 2) + -0.000559814 *y*dy + -0.000554268 *x*dx + -0.120174 *lens_ipow(dy, 4) + -0.112317 *lens_ipow(dx, 4)+0.0f;
} break;