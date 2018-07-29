case angenieux_double_gauss_1953_100mm:
{
const float dx00 =  + -0.604972  + 0.589799 *lambda + -0.421661 *lens_ipow(lambda, 2) + 0.245533 *lens_ipow(dy, 2) + 0.00402799 *y*dy + -0.000324364 *lens_ipow(y, 2) + -0.000718661 *lens_ipow(x, 2) + 0.22487 *lens_ipow(dx, 2)*lambda + 0.000138208 *lens_ipow(y, 2)*lambda + 0.0332102 *x*dx*lambda + 2.50821 *lens_ipow(dx, 4) + 4.17814 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + 0.117107 *y*lens_ipow(dx, 2)*dy*lambda + 0.374205 *x*lens_ipow(dx, 3)*lens_ipow(dy, 2) + 0.337375 *x*lens_ipow(dx, 5) + -0.000314185 *lens_ipow(x, 3)*dx*lens_ipow(lambda, 5)+0.0f;
const float dx01 =  + 0.00402799 *x*dy + -0.000648729 *x*y + 0.0116351 *y*dx*lambda + 0.000276416 *x*y*lambda + 1.49328 *dx*lens_ipow(dy, 3) + 3.14073 *lens_ipow(dx, 3)*dy*lambda + 0.117107 *x*lens_ipow(dx, 2)*dy*lambda + 0.218922 *y*dx*lens_ipow(dy, 4) + 0.308884 *y*lens_ipow(dx, 3)*lens_ipow(dy, 2)+0.0f;
const float dx02 =  + 99.6029  + -46.567 *lens_ipow(dy, 2) + -151.317 *lens_ipow(dx, 2) + 11.501 *lens_ipow(dx, 2)*lambda + 0.00581756 *lens_ipow(y, 2)*lambda + 0.44974 *x*dx*lambda + 0.0166051 *lens_ipow(x, 2)*lambda + 28.4313 *lens_ipow(dy, 4) + 190.746 *lens_ipow(dx, 4) + 1.49328 *y*lens_ipow(dy, 3) + 10.0328 *x*lens_ipow(dx, 3) + 334.965 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + 9.42219 *y*lens_ipow(dx, 2)*dy*lambda + 8.35628 *x*dx*lens_ipow(dy, 2)*lambda + 0.234215 *x*y*dx*dy*lambda + 0.109461 *lens_ipow(y, 2)*lens_ipow(dy, 4) + 0.463326 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.561307 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.843437 *lens_ipow(x, 2)*lens_ipow(dx, 4) + -7.85462e-05 *lens_ipow(x, 4)*lens_ipow(lambda, 5)+0.0f;
const float dx03 =  + -93.134 *dx*dy + 0.491066 *x*dy + 0.00402799 *x*y + 113.725 *dx*lens_ipow(dy, 3) + 4.47985 *y*dx*lens_ipow(dy, 2) + 223.31 *lens_ipow(dx, 3)*dy*lambda + 3.14073 *y*lens_ipow(dx, 3)*lambda + 8.35628 *x*lens_ipow(dx, 2)*dy*lambda + 0.117107 *x*y*lens_ipow(dx, 2)*lambda + 0.437844 *lens_ipow(y, 2)*dx*lens_ipow(dy, 3) + 0.308884 *lens_ipow(y, 2)*lens_ipow(dx, 3)*dy + 0.374205 *lens_ipow(x, 2)*lens_ipow(dx, 3)*dy+0.0f;
const float dx04 =  + 0.589799 *x + -0.843322 *x*lambda + 3.83366 *lens_ipow(dx, 3) + 0.00581756 *lens_ipow(y, 2)*dx + 0.22487 *x*lens_ipow(dx, 2) + 0.000138208 *x*lens_ipow(y, 2) + 0.0166051 *lens_ipow(x, 2)*dx + 111.655 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + 3.14073 *y*lens_ipow(dx, 3)*dy + 4.17814 *x*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.117107 *x*y*lens_ipow(dx, 2)*dy + -0.000392731 *lens_ipow(x, 4)*dx*lens_ipow(lambda, 4)+0.0f;
const float dx10 =  + 0.117489 *dx*dy + 0.003996 *y*dx + -0.000499954 *x*y + 0.0108942 *x*dy*lambda + 0.112315 *y*dx*lens_ipow(dy, 2)*lambda + 2.7358 *dx*lens_ipow(dy, 3)*lens_ipow(lambda, 2) + 11.3545 *lens_ipow(dx, 3)*lens_ipow(dy, 3) + 0.557141 *x*lens_ipow(dx, 2)*lens_ipow(dy, 3) + 1.24571e-06 *x*lens_ipow(y, 3)*lens_ipow(lambda, 2) + -1.72141e-09 *x*lens_ipow(y, 5)+0.0f;
const float dx11 =  + -0.61982  + 0.62911 *lambda + -0.450479 *lens_ipow(lambda, 2) + 0.245367 *lens_ipow(dx, 2) + -0.000691636 *lens_ipow(y, 2) + 0.003996 *x*dx + -0.000249977 *lens_ipow(x, 2) + 0.295257 *lens_ipow(dy, 2)*lambda + 0.0334026 *y*dy*lambda + 2.2613 *lens_ipow(dy, 4) + 2.14347 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.112315 *x*dx*lens_ipow(dy, 2)*lambda + 0.331652 *y*lens_ipow(dy, 5) + 0.392684 *y*lens_ipow(dx, 2)*lens_ipow(dy, 3) + 1.86857e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(lambda, 2) + -4.30354e-09 *lens_ipow(x, 2)*lens_ipow(y, 4) + -0.000212868 *lens_ipow(y, 3)*dy*lens_ipow(lambda, 4)+0.0f;
const float dx12 =  + -82.8887 *dx*dy + 0.490733 *y*dx + 0.117489 *x*dy + 0.003996 *x*y + 4.28694 *y*dx*lens_ipow(dy, 2) + 0.112315 *x*y*lens_ipow(dy, 2)*lambda + 1400.15 *lens_ipow(dx, 3)*lens_ipow(dy, 3) + 0.392684 *lens_ipow(y, 2)*dx*lens_ipow(dy, 3) + 2.7358 *x*lens_ipow(dy, 3)*lens_ipow(lambda, 2) + 34.0634 *x*lens_ipow(dx, 2)*lens_ipow(dy, 3) + 0.557141 *lens_ipow(x, 2)*dx*lens_ipow(dy, 3)+0.0f;
const float dx13 =  + 99.5754  + -147.721 *lens_ipow(dy, 2) + -41.4444 *lens_ipow(dx, 2) + 0.117489 *x*dx + 0.590514 *y*dy*lambda + 0.0167013 *lens_ipow(y, 2)*lambda + 0.00544709 *lens_ipow(x, 2)*lambda + 9.04519 *y*lens_ipow(dy, 3) + 4.28694 *y*lens_ipow(dx, 2)*dy + 530.242 *lens_ipow(dy, 4)*lambda + 0.22463 *x*y*dx*dy*lambda + 1050.11 *lens_ipow(dx, 4)*lens_ipow(dy, 2) + 0.82913 *lens_ipow(y, 2)*lens_ipow(dy, 4) + 0.589026 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 8.20739 *x*dx*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 34.0634 *x*lens_ipow(dx, 3)*lens_ipow(dy, 2) + 0.835712 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + -5.3217e-05 *lens_ipow(y, 4)*lens_ipow(lambda, 4) + -2587.83 *lens_ipow(dy, 6)*lens_ipow(lambda, 3)+0.0f;
const float dx14 =  + 0.62911 *y + -0.900958 *y*lambda + 0.295257 *y*lens_ipow(dy, 2) + 0.0167013 *lens_ipow(y, 2)*dy + 0.00544709 *lens_ipow(x, 2)*dy + 106.048 *lens_ipow(dy, 5) + 0.112315 *x*y*dx*lens_ipow(dy, 2) + 5.4716 *x*dx*lens_ipow(dy, 3)*lambda + 1.24571e-06 *lens_ipow(x, 2)*lens_ipow(y, 3)*lambda + -0.000212868 *lens_ipow(y, 4)*dy*lens_ipow(lambda, 3) + -1109.07 *lens_ipow(dy, 7)*lens_ipow(lambda, 2)+0.0f;
const float dx20 =  + -0.00634092  + -0.00352711 *lambda + 0.00246374 *lens_ipow(lambda, 2) + -0.000770014 *lens_ipow(dy, 2) + -1.92831e-05 *y*dy + 1.76487e-06 *lens_ipow(y, 2) + -7.16153e-05 *x*dx + 5.18469e-06 *lens_ipow(x, 2) + 0.000288578 *x*dx*lens_ipow(dy, 2) + 9.96175e-06 *x*y*dx*dy + 0.000598465 *x*lens_ipow(dx, 3)*lambda + -0.00535266 *lens_ipow(dy, 6) + -0.0326943 *lens_ipow(dx, 4)*lens_ipow(dy, 2) + -0.0182562 *lens_ipow(dx, 6) + 0.00230149 *y*lens_ipow(dx, 2)*lens_ipow(dy, 3)*lambda + 6.9831e-05 *lens_ipow(x, 2)*lens_ipow(dx, 4)*lambda + 1.48313e-09 *lens_ipow(x, 2)*lens_ipow(y, 4)*lens_ipow(dx, 2)*lens_ipow(dy, 2)+0.0f;
const float dx21 =  + -1.92831e-05 *x*dy + 3.52973e-06 *x*y + 0.000204999 *y*dx*lens_ipow(dy, 2) + 0.000124463 *y*lens_ipow(dx, 3) + 4.16125e-06 *lens_ipow(y, 2)*dx*dy + 4.98087e-06 *lens_ipow(x, 2)*dx*dy + -0.0224582 *lens_ipow(dx, 5)*dy*lambda + 0.00230149 *x*lens_ipow(dx, 2)*lens_ipow(dy, 3)*lambda + 1.97751e-09 *lens_ipow(x, 3)*lens_ipow(y, 3)*lens_ipow(dx, 2)*lens_ipow(dy, 2)+0.0f;
const float dx22 =  + -0.612086  + 0.00787218 *lambda + 0.899182 *lens_ipow(dx, 2) + -3.58077e-05 *lens_ipow(x, 2) + 0.552485 *lens_ipow(dy, 2)*lambda + -0.464277 *lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -1.27508 *lens_ipow(dx, 4) + 0.0001025 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 0.000186695 *lens_ipow(y, 2)*lens_ipow(dx, 2) + 1.38708e-06 *lens_ipow(y, 3)*dy + 0.000144289 *lens_ipow(x, 2)*lens_ipow(dy, 2) + 4.98087e-06 *lens_ipow(x, 2)*y*dy + -1.38705 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + 0.000897698 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lambda + -0.130777 *x*lens_ipow(dx, 3)*lens_ipow(dy, 2) + -0.109537 *x*lens_ipow(dx, 5) + -0.112291 *y*lens_ipow(dx, 4)*dy*lambda + 0.00460297 *x*y*dx*lens_ipow(dy, 3)*lambda + 9.3108e-05 *lens_ipow(x, 3)*lens_ipow(dx, 3)*lambda + 9.88754e-10 *lens_ipow(x, 3)*lens_ipow(y, 4)*dx*lens_ipow(dy, 2)+0.0f;
const float dx23 =  + -0.00154003 *x*dy + -1.92831e-05 *x*y + 1.10497 *dx*dy*lambda + -0.928554 *dx*dy*lens_ipow(lambda, 2) + 0.000204999 *lens_ipow(y, 2)*dx*dy + 1.38708e-06 *lens_ipow(y, 3)*dx + 0.000288578 *lens_ipow(x, 2)*dx*dy + 4.98087e-06 *lens_ipow(x, 2)*y*dx + -0.924698 *lens_ipow(dx, 3)*dy*lambda + -0.032116 *x*lens_ipow(dy, 5) + -0.0653886 *x*lens_ipow(dx, 4)*dy + -0.0224582 *y*lens_ipow(dx, 5)*lambda + 0.00690446 *x*y*lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + 9.88754e-10 *lens_ipow(x, 3)*lens_ipow(y, 4)*lens_ipow(dx, 2)*dy+0.0f;
const float dx24 =  + 0.00787218 *dx + -0.00352711 *x + 0.00492748 *x*lambda + 0.552485 *dx*lens_ipow(dy, 2) + -0.928554 *dx*lens_ipow(dy, 2)*lambda + -0.462349 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + 0.000299233 *lens_ipow(x, 2)*lens_ipow(dx, 3) + -0.0224582 *y*lens_ipow(dx, 5)*dy + 0.00230149 *x*y*lens_ipow(dx, 2)*lens_ipow(dy, 3) + 2.3277e-05 *lens_ipow(x, 3)*lens_ipow(dx, 4)+0.0f;
const float dx30 =  + 0.00190851 *dx*dy + -2.95858e-05 *y*dx + 3.58744e-06 *x*y + -1.6436e-07 *x*lens_ipow(y, 2)*dy + 9.69185e-05 *y*lens_ipow(dx, 3)*lambda + 3.78872e-06 *lens_ipow(y, 2)*dx*dy*lambda + 1.65307e-06 *x*lens_ipow(y, 2)*lens_ipow(dy, 3)*lambda + -0.0681183 *dx*lens_ipow(dy, 7) + -0.336643 *lens_ipow(dx, 5)*lens_ipow(dy, 3)+0.0f;
const float dx31 =  + -0.00634096  + -0.00346076 *lambda + 0.00237198 *lens_ipow(lambda, 2) + 5.13401e-06 *lens_ipow(y, 2) + -2.95858e-05 *x*dx + 1.79372e-06 *lens_ipow(x, 2) + -0.0423527 *lens_ipow(dx, 2)*lens_ipow(lambda, 2) + -3.05455e-07 *lens_ipow(y, 3)*dy + -1.6436e-07 *lens_ipow(x, 2)*y*dy + 0.106211 *lens_ipow(dx, 2)*lens_ipow(lambda, 3) + 9.69185e-05 *x*lens_ipow(dx, 3)*lambda + 7.57743e-06 *x*y*dx*dy*lambda + -0.0726444 *lens_ipow(dx, 2)*lens_ipow(lambda, 4) + -0.0490638 *lens_ipow(dx, 2)*lens_ipow(dy, 4) + -0.0400295 *lens_ipow(dy, 6)*lambda + 1.65307e-06 *lens_ipow(x, 2)*y*lens_ipow(dy, 3)*lambda + 0.0153174 *lens_ipow(dy, 4)*lens_ipow(lambda, 4) + 1.78148e-08 *lens_ipow(y, 5)*lens_ipow(dx, 2)*dy*lambda+0.0f;
const float dx32 =  + 0.857659 *dx*dy + 0.00190851 *x*dy + -2.95858e-05 *x*y + -1.33894 *dx*lens_ipow(dy, 3) + -1.39157 *lens_ipow(dx, 3)*dy + -0.0847054 *y*dx*lens_ipow(lambda, 2) + 0.212422 *y*dx*lens_ipow(lambda, 3) + 0.000290756 *x*y*lens_ipow(dx, 2)*lambda + 3.78872e-06 *x*lens_ipow(y, 2)*dy*lambda + -0.145289 *y*dx*lens_ipow(lambda, 4) + -0.0981275 *y*dx*lens_ipow(dy, 4) + -0.0681183 *x*lens_ipow(dy, 7) + -1.68321 *x*lens_ipow(dx, 4)*lens_ipow(dy, 3) + 5.93827e-09 *lens_ipow(y, 6)*dx*dy*lambda+0.0f;
const float dx33 =  + -0.616182  + 0.00958197 *lambda + 0.970053 *lens_ipow(dy, 2) + 0.42883 *lens_ipow(dx, 2) + 0.00190851 *x*dx + -1.43226 *lens_ipow(dy, 4) + -2.00841 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -0.347893 *lens_ipow(dx, 4) + -7.63639e-08 *lens_ipow(y, 4) + -8.218e-08 *lens_ipow(x, 2)*lens_ipow(y, 2) + 3.78872e-06 *x*lens_ipow(y, 2)*dx*lambda + -0.196255 *y*lens_ipow(dx, 2)*lens_ipow(dy, 3) + -0.240177 *y*lens_ipow(dy, 5)*lambda + 2.4796e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + 0.0612694 *y*lens_ipow(dy, 3)*lens_ipow(lambda, 4) + -0.476828 *x*dx*lens_ipow(dy, 6) + -1.00993 *x*lens_ipow(dx, 5)*lens_ipow(dy, 2) + 2.96913e-09 *lens_ipow(y, 6)*lens_ipow(dx, 2)*lambda+0.0f;
const float dx34 =  + 0.00958197 *dy + -0.00346076 *y + 0.00474395 *y*lambda + -0.0847054 *y*lens_ipow(dx, 2)*lambda + 0.318634 *y*lens_ipow(dx, 2)*lens_ipow(lambda, 2) + 9.69185e-05 *x*y*lens_ipow(dx, 3) + 3.78872e-06 *x*lens_ipow(y, 2)*dx*dy + -0.290578 *y*lens_ipow(dx, 2)*lens_ipow(lambda, 3) + -0.0400295 *y*lens_ipow(dy, 6) + 8.26533e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dy, 3) + 0.0612694 *y*lens_ipow(dy, 4)*lens_ipow(lambda, 3) + 2.96913e-09 *lens_ipow(y, 6)*lens_ipow(dx, 2)*dy+0.0f;
const float dx40 =  + -0.0042972 *lens_ipow(dx, 3) + -8.43545e-05 *y*dx*dy + -8.23473e-05 *x*lens_ipow(dy, 2) + -0.00896813 *dx*lens_ipow(dy, 2)*lambda + -0.000205046 *x*lens_ipow(dx, 2)*lambda + -0.000426865 *y*lens_ipow(dx, 3)*dy + -0.00114972 *x*lens_ipow(dx, 4) + -2.7703e-05 *lens_ipow(x, 2)*lens_ipow(dx, 3)*lambda + -0.00111682 *y*dx*lens_ipow(dy, 3)*lens_ipow(lambda, 2) + -0.052724 *lens_ipow(dx, 7)*lambda+0.0f;
const float dx41 =  + -0.00286447 *lens_ipow(dy, 3) + -0.00541464 *lens_ipow(dx, 2)*dy + -0.000106287 *y*lens_ipow(dy, 2) + -7.82414e-05 *y*lens_ipow(dx, 2) + -8.43545e-05 *x*dx*dy + -0.000426865 *x*lens_ipow(dx, 3)*dy + -0.0233181 *lens_ipow(dy, 5)*lambda + -0.00221478 *y*lens_ipow(dy, 4)*lambda + -5.97218e-05 *lens_ipow(y, 2)*lens_ipow(dy, 3)*lens_ipow(lambda, 2) + -0.00111682 *x*dx*lens_ipow(dy, 3)*lens_ipow(lambda, 2) + -0.0277421 *y*lens_ipow(dx, 4)*lens_ipow(dy, 4)+0.0f;
const float dx42 =  + -0.667144 *lens_ipow(dx, 3) + -0.0108293 *y*dx*dy + -7.82414e-05 *lens_ipow(y, 2)*dx + -0.0128916 *x*lens_ipow(dx, 2) + -8.43545e-05 *x*y*dy + -3.30489 *dx*lens_ipow(dy, 2)*lambda + -0.00896813 *x*lens_ipow(dy, 2)*lambda + -0.000205046 *lens_ipow(x, 2)*dx*lambda + 2.47318 *dx*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -0.00128059 *x*y*lens_ipow(dx, 2)*dy + -0.00229943 *lens_ipow(x, 2)*lens_ipow(dx, 3) + -2.99992 *lens_ipow(dx, 5)*lambda + -2.7703e-05 *lens_ipow(x, 3)*lens_ipow(dx, 2)*lambda + -0.00111682 *x*y*lens_ipow(dy, 3)*lens_ipow(lambda, 2) + -0.369068 *x*lens_ipow(dx, 6)*lambda + -0.0554843 *lens_ipow(y, 2)*lens_ipow(dx, 3)*lens_ipow(dy, 4)+0.0f;
const float dx43 =  + -0.660234 *lens_ipow(dy, 3) + -0.00859341 *y*lens_ipow(dy, 2) + -0.00541464 *y*lens_ipow(dx, 2) + -0.000106287 *lens_ipow(y, 2)*dy + -8.43545e-05 *x*y*dx + -8.23473e-05 *lens_ipow(x, 2)*dy + -3.30489 *lens_ipow(dx, 2)*dy*lambda + -0.0179363 *x*dx*dy*lambda + 2.47318 *lens_ipow(dx, 2)*dy*lens_ipow(lambda, 2) + -0.000426865 *x*y*lens_ipow(dx, 3) + -3.03941 *lens_ipow(dy, 5)*lambda + -0.11659 *y*lens_ipow(dy, 4)*lambda + -0.00442955 *lens_ipow(y, 2)*lens_ipow(dy, 3)*lambda + -5.97218e-05 *lens_ipow(y, 3)*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -0.00335045 *x*y*dx*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -0.0554843 *lens_ipow(y, 2)*lens_ipow(dx, 4)*lens_ipow(dy, 3)+0.0f;
const float dx44 =  + 0.856098  + -2.34188 *lambda + 1.69569 *lens_ipow(lambda, 2) + -1.65244 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -0.00896813 *x*dx*lens_ipow(dy, 2) + -0.000102523 *lens_ipow(x, 2)*lens_ipow(dx, 2) + 2.47318 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + -0.506568 *lens_ipow(dy, 6) + -0.499987 *lens_ipow(dx, 6) + -0.0233181 *y*lens_ipow(dy, 5) + -0.00110739 *lens_ipow(y, 2)*lens_ipow(dy, 4) + -9.23433e-06 *lens_ipow(x, 3)*lens_ipow(dx, 3) + -3.98146e-05 *lens_ipow(y, 3)*lens_ipow(dy, 3)*lambda + -0.00223364 *x*y*dx*lens_ipow(dy, 3)*lambda + -0.052724 *x*lens_ipow(dx, 7)+0.0f;
} break;
