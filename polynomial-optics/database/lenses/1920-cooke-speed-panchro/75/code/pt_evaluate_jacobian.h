case cooke__speed_panchro__1920__75mm:
{
const double dx00 =  + 0.602196  + 0.0392768 *y*dy + 0.0773089 *x*dx + 0.00032498 *lens_ipow(y, 2) + 0.000775417 *lens_ipow(x, 2) + 1.07194 *lens_ipow(dy, 2) + 1.08185 *lens_ipow(dx, 2) + 0.000355813 *lens_ipow(x, 3)*dx + 3.931 *lens_ipow(dx, 4) + 0.696118 *x*lens_ipow(dx, 3) + -2.73647 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + 3.06206e-05 *x*lens_ipow(y, 2)*dx + 3.0971e-05 *lens_ipow(x, 2)*y*dy + -0.780564 *lens_ipow(dy, 4) + 0.00453566 *x*y*dx*dy + 0.0267005 *lens_ipow(x, 2)*lens_ipow(dx, 2) + 0.00204047 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + 2.39552e-05 *lens_ipow(y, 3)*dy*lambda + 1.7869e-08 *lens_ipow(x, 6)*lambda + -6.43516e-11 *lens_ipow(x, 8)*lens_ipow(lambda, 2)+0.0f;
const double dx01 =  + 0.581827 *dx*dy + 0.0392768 *x*dy + 0.000649959 *x*y + 0.0263713 *y*dx + -3.35151 *lens_ipow(dx, 3)*dy + 3.06206e-05 *lens_ipow(x, 2)*y*dx + 1.03237e-05 *lens_ipow(x, 3)*dy + -0.0830833 *y*lens_ipow(dx, 3) + 0.00226783 *lens_ipow(x, 2)*dx*dy + 0.00408094 *x*y*lens_ipow(dy, 2)*lambda + 7.18657e-05 *x*lens_ipow(y, 2)*dy*lambda+0.0f;
const double dx02 =  + 74.6622  + 0.581827 *y*dy + 0.0386544 *lens_ipow(x, 2) + -99.1704 *lens_ipow(dx, 2) + -31.5091 *lens_ipow(dy, 2) + 2.1637 *x*dx + 0.0131857 *lens_ipow(y, 2) + 8.89532e-05 *lens_ipow(x, 4) + 15.724 *x*lens_ipow(dx, 3) + 1.04418 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -10.0545 *y*lens_ipow(dx, 2)*dy + -5.47294 *x*dx*lens_ipow(dy, 2) + 1.53103e-05 *lens_ipow(x, 2)*lens_ipow(y, 2) + -0.124625 *lens_ipow(y, 2)*lens_ipow(dx, 2) + 0.00226783 *lens_ipow(x, 2)*y*dy + 0.0178003 *lens_ipow(x, 3)*dx + 121.05 *lens_ipow(dy, 4)*lambda+0.0f;
const double dx03 =  + 0.581827 *y*dx + 0.0392768 *x*y + -63.0183 *dx*dy + 2.14387 *x*dy + -3.35151 *y*lens_ipow(dx, 3) + -5.47294 *x*lens_ipow(dx, 2)*dy + 1.03237e-05 *lens_ipow(x, 3)*y + -3.12226 *x*lens_ipow(dy, 3) + 0.00226783 *lens_ipow(x, 2)*y*dx + 0.00408094 *x*lens_ipow(y, 2)*dy*lambda + 484.201 *dx*lens_ipow(dy, 3)*lambda + 2.39552e-05 *x*lens_ipow(y, 3)*lambda+0.0f;
const double dx04 =  + 0.00204047 *x*lens_ipow(y, 2)*lens_ipow(dy, 2) + 121.05 *dx*lens_ipow(dy, 4) + 2.39552e-05 *x*lens_ipow(y, 3)*dy + 2.55272e-09 *lens_ipow(x, 7) + -1.43004e-11 *lens_ipow(x, 9)*lambda+0.0f;
const double dx10 =  + 0.580752 *dx*dy + 0.0392364 *y*dx + 0.000650481 *x*y + 0.0263482 *x*dy + 0.00226089 *lens_ipow(y, 2)*dx*dy + 1.04373e-05 *lens_ipow(y, 3)*dx + -3.30055 *dx*lens_ipow(dy, 3) + -0.0821568 *x*lens_ipow(dy, 3) + 3.0862e-05 *x*lens_ipow(y, 2)*dy + 0.00403815 *x*y*lens_ipow(dx, 2)*lambda + 7.11534e-05 *lens_ipow(x, 2)*y*dx*lambda+0.0f;
const double dx11 =  + 0.602233  + 1.07 *lens_ipow(dx, 2) + 0.0766522 *y*dy + 1.07302 *lens_ipow(dy, 2) + 0.0392364 *x*dx + 0.00032524 *lens_ipow(x, 2) + 0.000771532 *lens_ipow(y, 2) + 0.00452177 *x*y*dx*dy + -0.774473 *lens_ipow(dx, 4) + 0.000364345 *lens_ipow(y, 3)*dy + 3.13118e-05 *x*lens_ipow(y, 2)*dx + 0.706293 *y*lens_ipow(dy, 3) + 3.98949 *lens_ipow(dy, 4) + -2.72638 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + 3.0862e-05 *lens_ipow(x, 2)*y*dy + 0.0271441 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 0.00201908 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lambda + 2.37178e-05 *lens_ipow(x, 3)*dx*lambda + 1.83488e-08 *lens_ipow(y, 6)*lambda + -6.5318e-11 *lens_ipow(y, 8)*lens_ipow(lambda, 2)+0.0f;
const double dx12 =  + 2.13999 *y*dx + 0.580752 *x*dy + 0.0392364 *x*y + -63.2127 *dx*dy + 0.00226089 *x*lens_ipow(y, 2)*dy + -3.09789 *y*lens_ipow(dx, 3) + 1.04373e-05 *x*lens_ipow(y, 3) + -3.30055 *x*lens_ipow(dy, 3) + -5.45276 *y*dx*lens_ipow(dy, 2) + 0.00403815 *lens_ipow(x, 2)*y*dx*lambda + 2.37178e-05 *lens_ipow(x, 3)*y*lambda + 487.185 *lens_ipow(dx, 3)*dy*lambda+0.0f;
const double dx13 =  + 74.6705  + 0.0383261 *lens_ipow(y, 2) + 2.14603 *y*dy + 0.580752 *x*dx + -31.6063 *lens_ipow(dx, 2) + 0.0131741 *lens_ipow(x, 2) + -99.5355 *lens_ipow(dy, 2) + 0.00226089 *x*lens_ipow(y, 2)*dx + 9.10862e-05 *lens_ipow(y, 4) + -9.90166 *x*dx*lens_ipow(dy, 2) + 1.05944 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 15.958 *y*lens_ipow(dy, 3) + -5.45276 *y*lens_ipow(dx, 2)*dy + -0.123235 *lens_ipow(x, 2)*lens_ipow(dy, 2) + 1.5431e-05 *lens_ipow(x, 2)*lens_ipow(y, 2) + 0.018096 *lens_ipow(y, 3)*dy + 121.796 *lens_ipow(dx, 4)*lambda+0.0f;
const double dx14 =  + 0.00201908 *lens_ipow(x, 2)*y*lens_ipow(dx, 2) + 2.37178e-05 *lens_ipow(x, 3)*y*dx + 121.796 *lens_ipow(dx, 4)*dy + 2.62126e-09 *lens_ipow(y, 7) + -1.45151e-11 *lens_ipow(y, 9)*lambda+0.0f;
const double dx20 =  + -0.0260199  + -0.000965955 *y*dy + -0.000828536 *x*dx + -3.89556e-06 *lens_ipow(y, 2) + -3.43909e-06 *lens_ipow(x, 2) + -0.0369466 *lens_ipow(dy, 2) + -0.0107324 *lens_ipow(dx, 2) + -7.2991e-07 *lens_ipow(x, 3)*dx + 0.135898 *lens_ipow(dx, 4) + 0.220503 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -3.14428e-05 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -6.88708e-07 *lens_ipow(x, 2)*y*dy + 0.0452327 *lens_ipow(dy, 4) + -7.54848e-05 *x*y*dx*dy + -7.6243e-05 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -1.75655e-05 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 1.08724e-11 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const double dx21 =  + -0.0452008 *dx*dy + -0.000965955 *x*dy + -7.79112e-06 *x*y + -0.000476484 *y*dx + 0.156515 *lens_ipow(dx, 3)*dy + -2.2957e-07 *lens_ipow(x, 3)*dy + 0.124001 *dx*lens_ipow(dy, 3) + 0.00142024 *y*lens_ipow(dx, 3) + -3.77424e-05 *lens_ipow(x, 2)*dx*dy + -3.5131e-05 *x*y*lens_ipow(dy, 2) + 1.44966e-11 *lens_ipow(x, 3)*lens_ipow(y, 3)+0.0f;
const double dx22 =  + -1.55891  + -0.0452008 *y*dy + -0.000414268 *lens_ipow(x, 2) + 1.39708 *lens_ipow(dx, 2) + -1.57573 *lens_ipow(dy, 2) + -0.0214647 *x*dx + -0.000238242 *lens_ipow(y, 2) + -1.82478e-07 *lens_ipow(x, 4) + 0.543593 *x*lens_ipow(dx, 3) + 0.469545 *y*lens_ipow(dx, 2)*dy + 24.549 *lens_ipow(dx, 4) + 0.441006 *x*dx*lens_ipow(dy, 2) + 6.49893 *lens_ipow(dy, 4) + 0.124001 *y*lens_ipow(dy, 3) + 0.00213036 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -3.77424e-05 *lens_ipow(x, 2)*y*dy + -5.08286e-05 *lens_ipow(x, 3)*dx + 39.6293 *lens_ipow(dx, 2)*lens_ipow(dy, 2)+0.0f;
const double dx23 =  + -0.0452008 *y*dx + -0.000965955 *x*y + -3.15146 *dx*dy + -0.0738933 *x*dy + 0.156515 *y*lens_ipow(dx, 3) + 0.441006 *x*lens_ipow(dx, 2)*dy + -2.09619e-05 *lens_ipow(x, 3)*dy + 25.9957 *dx*lens_ipow(dy, 3) + -2.2957e-07 *lens_ipow(x, 3)*y + 0.180931 *x*lens_ipow(dy, 3) + 0.372004 *y*dx*lens_ipow(dy, 2) + -3.77424e-05 *lens_ipow(x, 2)*y*dx + -3.5131e-05 *x*lens_ipow(y, 2)*dy + 26.4196 *lens_ipow(dx, 3)*dy+0.0f;
const double dx24 = +0.0f;
const double dx30 =  + 0.0645932 *dx*dy + 3.78584e-06 *x*y + 0.000804098 *x*dy + -1.11932e-05 *lens_ipow(y, 2)*dx*dy + 0.0321421 *dx*lens_ipow(dy, 3) + -7.25747e-06 *x*y*lens_ipow(dx, 2) + 7.38654e-06 *lens_ipow(x, 3)*lens_ipow(dy, 3) + -2.8975e-10 *lens_ipow(y, 5)*dx + 0.000918956 *lens_ipow(x, 2)*dx*lens_ipow(dy, 3) + 0.0247487 *x*lens_ipow(dx, 2)*lens_ipow(dy, 3)+0.0f;
const double dx31 =  + -0.0260874  + -0.000624707 *y*dy + 1.89292e-06 *lens_ipow(x, 2) + -2.51594e-06 *lens_ipow(y, 2) + -0.00386419 *lens_ipow(dy, 2)*lambda + -2.23864e-05 *x*y*dx*dy + 0.0139968 *lens_ipow(dx, 4) + -7.67638e-07 *lens_ipow(y, 3)*dy + -3.62873e-06 *lens_ipow(x, 2)*lens_ipow(dx, 2) + 0.0860433 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -0.000317033 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + -0.0102857 *y*lens_ipow(dy, 3)*lambda + -8.77211e-08 *lens_ipow(y, 4)*lens_ipow(dx, 2) + -2.0927e-06 *lens_ipow(y, 3)*dy*lens_ipow(lambda, 2) + -1.44875e-09 *x*lens_ipow(y, 4)*dx + 0.112506 *lens_ipow(dy, 6)+0.0f;
const double dx32 =  + 0.0645932 *x*dy + 5.48057 *dx*dy + -1.11932e-05 *x*lens_ipow(y, 2)*dy + 8.29574 *dx*lens_ipow(dy, 3) + 0.0559872 *y*lens_ipow(dx, 3) + 0.0321421 *x*lens_ipow(dy, 3) + -7.25747e-06 *lens_ipow(x, 2)*y*dx + 0.172087 *y*dx*lens_ipow(dy, 2) + -3.50884e-08 *lens_ipow(y, 5)*dx + -2.8975e-10 *x*lens_ipow(y, 5) + 0.000306319 *lens_ipow(x, 3)*lens_ipow(dy, 3) + 0.0247487 *lens_ipow(x, 2)*dx*lens_ipow(dy, 3)+0.0f;
const double dx33 =  + -1.565  + -0.000312354 *lens_ipow(y, 2) + 0.0645932 *x*dx + 2.74028 *lens_ipow(dx, 2) + 0.000402049 *lens_ipow(x, 2) + 2.13092 *lens_ipow(dy, 2) + -0.00772839 *y*dy*lambda + -1.11932e-05 *x*lens_ipow(y, 2)*dx + 12.4436 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -1.91909e-07 *lens_ipow(y, 4) + 11.6537 *lens_ipow(dy, 4) + 0.0964262 *x*dx*lens_ipow(dy, 2) + 0.172087 *y*lens_ipow(dx, 2)*dy + -0.000211356 *lens_ipow(y, 3)*dy*lambda + -0.0154286 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + 5.53991e-06 *lens_ipow(x, 4)*lens_ipow(dy, 2) + -5.23176e-07 *lens_ipow(y, 4)*lens_ipow(lambda, 2) + 0.000918956 *lens_ipow(x, 3)*dx*lens_ipow(dy, 2) + 0.0371231 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.675037 *y*lens_ipow(dy, 5) + 92.6096 *lens_ipow(dy, 6)*lens_ipow(lambda, 2)+0.0f;
const double dx34 =  + -0.00386419 *y*lens_ipow(dy, 2) + -0.000105678 *lens_ipow(y, 3)*lens_ipow(dy, 2) + -0.00514285 *lens_ipow(y, 2)*lens_ipow(dy, 3) + -1.04635e-06 *lens_ipow(y, 4)*dy*lambda + 26.4599 *lens_ipow(dy, 7)*lambda+0.0f;
const double dx40 =  + 0.00247301 *dx + 3.65405e-05 *x + -0.206752 *lens_ipow(dx, 3) + -8.09073e-05 *x*y*dy + -4.04018e-05 *lens_ipow(y, 2)*dx + -6.62822e-07 *x*lens_ipow(y, 2) + -0.00807709 *x*lens_ipow(dx, 2) + -0.000121068 *lens_ipow(x, 2)*dx + -0.206535 *dx*lens_ipow(dy, 2) + -6.63776e-07 *lens_ipow(x, 3) + -0.00537792 *y*dx*dy + -0.00273586 *x*lens_ipow(dy, 2)+0.0f;
const double dx41 =  + 0.00252279 *dy + 3.83749e-05 *y + -0.207107 *lens_ipow(dy, 3) + -0.0027372 *y*lens_ipow(dx, 2) + -4.04537e-05 *lens_ipow(x, 2)*dy + -8.08035e-05 *x*y*dx + -6.62822e-07 *lens_ipow(x, 2)*y + -6.79382e-07 *lens_ipow(y, 3) + -0.206858 *lens_ipow(dx, 2)*dy + -0.00811878 *y*lens_ipow(dy, 2) + -0.00537792 *x*dx*dy + -0.000122158 *lens_ipow(y, 2)*dy+0.0f;
const double dx42 =  + 0.00247301 *x + 0.193642 *dx + -18.6111 *lens_ipow(dx, 3) + -0.0027372 *lens_ipow(y, 2)*dx + -0.620257 *x*lens_ipow(dx, 2) + -18.4427 *dx*lens_ipow(dy, 2) + -4.04018e-05 *x*lens_ipow(y, 2) + -0.00807709 *lens_ipow(x, 2)*dx + -0.413717 *y*dx*dy + -4.03562e-05 *lens_ipow(x, 3) + -0.206535 *x*lens_ipow(dy, 2) + -0.00537792 *x*y*dy+0.0f;
const double dx43 =  + 0.00252279 *y + 0.194919 *dy + -0.621321 *y*lens_ipow(dy, 2) + -18.4427 *lens_ipow(dx, 2)*dy + -4.04537e-05 *lens_ipow(x, 2)*y + -18.5955 *lens_ipow(dy, 3) + -0.206858 *y*lens_ipow(dx, 2) + -0.00811878 *lens_ipow(y, 2)*dy + -0.413071 *x*dx*dy + -0.00537792 *x*y*dx + -0.00273586 *lens_ipow(x, 2)*dy + -4.07195e-05 *lens_ipow(y, 3)+0.0f;
const double dx44 =  + 0.229736  + -0.314111 *lambda+0.0f;
} break;