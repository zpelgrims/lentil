case asahi__takumar__1970__22mm:
{
const double dx00 =  + -0.0787327  + -0.00752615 *lambda + 0.362863 *lens_ipow(dy, 2) + 0.887677 *lens_ipow(dx, 2) + 0.0559931 *y*dy + 0.00150315 *lens_ipow(y, 2) + 0.164749 *x*dx + 0.00449885 *lens_ipow(x, 2) + 0.0248867 *x*dx*lens_ipow(dy, 2) + -0.00230288 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -4.87034e-05 *x*lens_ipow(y, 3)*dx*dy + -0.000602304 *lens_ipow(x, 2)*y*lens_ipow(dy, 3) + 1.38876e-05 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dx, 2) + -9.91121e-05 *lens_ipow(x, 3)*y*dx*dy + 5.16958e-05 *lens_ipow(x, 4)*lens_ipow(dy, 2) + 0.0774205 *x*lens_ipow(dx, 5)*lambda + -8.87116e-07 *x*lens_ipow(y, 4)*dx*lambda + 1.41943e-05 *lens_ipow(x, 4)*lens_ipow(dx, 2)*lambda + -3.09876e-12 *lens_ipow(y, 8) + -7.05498e-08 *lens_ipow(x, 6)*lens_ipow(dx, 2)+0.0f;
const double dx01 =  + 0.505644 *dx*dy + 0.0548023 *y*dx + 0.0559931 *x*dy + 0.00300631 *x*y + -0.0117717 *lens_ipow(y, 2)*dx*lens_ipow(dy, 3) + -7.30551e-05 *lens_ipow(x, 2)*lens_ipow(y, 2)*dx*dy + -0.000200768 *lens_ipow(x, 3)*lens_ipow(dy, 3) + 9.25843e-06 *lens_ipow(x, 3)*y*lens_ipow(dx, 2) + -2.4778e-05 *lens_ipow(x, 4)*dx*dy + -1.77423e-06 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx*lambda + -2.47901e-11 *x*lens_ipow(y, 7)+0.0f;
const double dx02 =  + 21.4102  + 1.27236 *lambda + -0.925817 *lens_ipow(lambda, 2) + -4.20676 *lens_ipow(dy, 2) + -11.6936 *lens_ipow(dx, 2) + 0.505644 *y*dy + 0.0274011 *lens_ipow(y, 2) + 1.77535 *x*dx + 0.0823746 *lens_ipow(x, 2) + 0.0124433 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -0.00153525 *lens_ipow(x, 3)*dx + -0.00392392 *lens_ipow(y, 3)*lens_ipow(dy, 3) + -2.43517e-05 *lens_ipow(x, 2)*lens_ipow(y, 3)*dy + 9.25843e-06 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx + -2.4778e-05 *lens_ipow(x, 4)*y*dy + 0.193551 *lens_ipow(x, 2)*lens_ipow(dx, 4)*lambda + -4.43558e-07 *lens_ipow(x, 2)*lens_ipow(y, 4)*lambda + 5.67771e-06 *lens_ipow(x, 5)*dx*lambda + -2.01571e-08 *lens_ipow(x, 7)*dx+0.0f;
const double dx03 =  + -8.41351 *dx*dy + 0.505644 *y*dx + 0.725725 *x*dy + 0.0559931 *x*y + 0.0248867 *lens_ipow(x, 2)*dx*dy + -0.0117717 *lens_ipow(y, 3)*dx*lens_ipow(dy, 2) + -2.43517e-05 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx + -0.000602304 *lens_ipow(x, 3)*y*lens_ipow(dy, 2) + -2.4778e-05 *lens_ipow(x, 4)*y*dx + 2.06783e-05 *lens_ipow(x, 5)*dy+0.0f;
const double dx04 =  + 1.27236 *dx + -0.00752615 *x + -1.85163 *dx*lambda + 0.0387103 *lens_ipow(x, 2)*lens_ipow(dx, 5) + -4.43558e-07 *lens_ipow(x, 2)*lens_ipow(y, 4)*dx + 2.83885e-06 *lens_ipow(x, 5)*lens_ipow(dx, 2)+0.0f;
const double dx10 =  + 0.492672 *dx*dy + 0.0554535 *y*dx + 0.0546007 *x*dy + 0.00295447 *x*y + 0.0031609 *x*y*lens_ipow(dy, 2)*lambda + -0.0293738 *lens_ipow(y, 2)*lens_ipow(dx, 3)*dy + 0.000424196 *lens_ipow(x, 3)*lens_ipow(dx, 2)*dy + -0.000302831 *lens_ipow(y, 4)*dx*lens_ipow(dy, 3) + 0.000772616 *x*lens_ipow(y, 3)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 4.00556e-05 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx*lens_ipow(dy, 2) + 3.10849 *x*lens_ipow(dy, 7)*lambda + 0.00107161 *lens_ipow(y, 4)*dx*lens_ipow(dy, 5) + 3.84905e-06 *lens_ipow(x, 3)*lens_ipow(y, 3)*lens_ipow(dy, 4)+0.0f;
const double dx11 =  + -0.0766241  + -0.00930579 *lambda + 0.84176 *lens_ipow(dy, 2) + 0.349106 *lens_ipow(dx, 2) + 0.165599 *y*dy + 0.00445073 *lens_ipow(y, 2) + 0.0554535 *x*dx + 0.00147724 *lens_ipow(x, 2) + 1.60598e-06 *lens_ipow(y, 4)*lambda + 0.00158045 *lens_ipow(x, 2)*lens_ipow(dy, 2)*lambda + 0.0316034 *lens_ipow(y, 2)*lens_ipow(dx, 4) + -2.10879e-05 *lens_ipow(y, 4)*lens_ipow(dy, 2) + -0.0587476 *x*y*lens_ipow(dx, 3)*dy + -8.03809e-06 *lens_ipow(y, 5)*lens_ipow(dx, 2)*dy + -0.00121132 *x*lens_ipow(y, 3)*dx*lens_ipow(dy, 3) + 0.00115892 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 4.00556e-05 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx*lens_ipow(dy, 2) + 0.00428644 *x*lens_ipow(y, 3)*dx*lens_ipow(dy, 5) + 2.88679e-06 *lens_ipow(x, 4)*lens_ipow(y, 2)*lens_ipow(dy, 4)+0.0f;
const double dx12 =  + -8.75146 *dx*dy + 0.698212 *y*dx + 0.492672 *x*dy + 0.0554535 *x*y + 0.0421379 *lens_ipow(y, 3)*lens_ipow(dx, 3) + -0.0881214 *x*lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + 0.000212098 *lens_ipow(x, 4)*dx*dy + -2.67936e-06 *lens_ipow(y, 6)*dx*dy + -0.000302831 *x*lens_ipow(y, 4)*lens_ipow(dy, 3) + 0.000772616 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx*lens_ipow(dy, 2) + 1.33518e-05 *lens_ipow(x, 3)*lens_ipow(y, 3)*lens_ipow(dy, 2) + 0.00107161 *x*lens_ipow(y, 4)*lens_ipow(dy, 5)+0.0f;
const double dx13 =  + 21.4312  + 1.20813 *lambda + -0.878772 *lens_ipow(lambda, 2) + -12.694 *lens_ipow(dy, 2) + -4.37573 *lens_ipow(dx, 2) + 1.68352 *y*dy + 0.0827994 *lens_ipow(y, 2) + 0.492672 *x*dx + 0.0273003 *lens_ipow(x, 2) + 0.0031609 *lens_ipow(x, 2)*y*dy*lambda + -8.43515e-06 *lens_ipow(y, 5)*dy + -0.0293738 *x*lens_ipow(y, 2)*lens_ipow(dx, 3) + 0.000106049 *lens_ipow(x, 4)*lens_ipow(dx, 2) + -1.33968e-06 *lens_ipow(y, 6)*lens_ipow(dx, 2) + -0.000908492 *x*lens_ipow(y, 4)*dx*lens_ipow(dy, 2) + 0.000772616 *lens_ipow(x, 2)*lens_ipow(y, 3)*lens_ipow(dx, 2)*dy + 2.67037e-05 *lens_ipow(x, 3)*lens_ipow(y, 3)*dx*dy + 10.8797 *lens_ipow(x, 2)*lens_ipow(dy, 6)*lambda + 0.00535805 *x*lens_ipow(y, 4)*dx*lens_ipow(dy, 4) + 3.84905e-06 *lens_ipow(x, 4)*lens_ipow(y, 3)*lens_ipow(dy, 3)+0.0f;
const double dx14 =  + 1.20813 *dy + -0.00930579 *y + -1.75754 *dy*lambda + 3.21196e-07 *lens_ipow(y, 5) + 0.00158045 *lens_ipow(x, 2)*y*lens_ipow(dy, 2) + 1.55424 *lens_ipow(x, 2)*lens_ipow(dy, 7)+0.0f;
const double dx20 =  + -0.045184  + 0.000710693 *lambda + 0.00885783 *lens_ipow(dy, 2) + 0.0275613 *lens_ipow(dx, 2) + 0.000239599 *y*dy + 3.28932e-05 *lens_ipow(y, 2) + 0.00114458 *x*dx + 0.000101896 *lens_ipow(x, 2) + -0.00434139 *lens_ipow(dy, 2)*lambda + -0.00524647 *lens_ipow(dx, 2)*lambda + 2.4652e-05 *lens_ipow(y, 2)*lens_ipow(dy, 2) + -0.124387 *lens_ipow(dx, 6)*lambda + 7.76582e-11 *x*lens_ipow(y, 6)*dx + 1.7761e-05 *lens_ipow(x, 3)*y*lens_ipow(dx, 3)*dy + 7.81234e-06 *lens_ipow(y, 4)*lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + 6.69301e-06 *lens_ipow(x, 4)*lens_ipow(dx, 4)*lambda + -8.71536e-12 *lens_ipow(x, 6)*lens_ipow(y, 2)*lambda + -3.57666e-12 *lens_ipow(x, 8)*lambda + -0.0333631 *lens_ipow(x, 2)*lens_ipow(dx, 6)*lens_ipow(dy, 2) + 1.07003e-06 *lens_ipow(x, 3)*lens_ipow(y, 2)*lens_ipow(dx, 5)+0.0f;
const double dx21 =  + 0.0166482 *dx*dy + 0.000679097 *y*dx + 0.000239599 *x*dy + 6.57864e-05 *x*y + 4.9304e-05 *x*y*lens_ipow(dy, 2) + 1.72471e-05 *lens_ipow(y, 3)*dx*lens_ipow(dy, 2)*lambda + 2.32975e-10 *lens_ipow(x, 2)*lens_ipow(y, 5)*dx + 4.44024e-06 *lens_ipow(x, 4)*lens_ipow(dx, 3)*dy + 4.50775e-07 *lens_ipow(y, 5)*lens_ipow(dx, 3)*lambda + 3.12494e-05 *x*lens_ipow(y, 3)*lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + -2.4901e-12 *lens_ipow(x, 7)*y*lambda + 5.35014e-07 *lens_ipow(x, 4)*y*lens_ipow(dx, 5)+0.0f;
const double dx22 =  + -0.231039  + 0.307401 *lens_ipow(dy, 2) + 0.945655 *lens_ipow(dx, 2) + 0.0166482 *y*dy + 0.000339549 *lens_ipow(y, 2) + 0.0551226 *x*dx + 0.000572291 *lens_ipow(x, 2) + -0.0104929 *x*dx*lambda + 21.7202 *lens_ipow(dx, 2)*lens_ipow(dy, 4) + 4.31178e-06 *lens_ipow(y, 4)*lens_ipow(dy, 2)*lambda + -0.746322 *x*lens_ipow(dx, 5)*lambda + 3.88291e-11 *lens_ipow(x, 2)*lens_ipow(y, 6) + 1.33207e-05 *lens_ipow(x, 4)*y*lens_ipow(dx, 2)*dy + 2.25388e-07 *lens_ipow(y, 6)*lens_ipow(dx, 2)*lambda + 1.56247e-05 *x*lens_ipow(y, 4)*dx*lens_ipow(dy, 2)*lambda + 5.35441e-06 *lens_ipow(x, 5)*lens_ipow(dx, 3)*lambda + -0.0667263 *lens_ipow(x, 3)*lens_ipow(dx, 5)*lens_ipow(dy, 2) + 1.33754e-06 *lens_ipow(x, 4)*lens_ipow(y, 2)*lens_ipow(dx, 4)+0.0f;
const double dx23 =  + 0.614803 *dx*dy + 0.0166482 *y*dx + 0.0177157 *x*dy + 0.000239599 *x*y + -0.00868277 *x*dy*lambda + 4.9304e-05 *x*lens_ipow(y, 2)*dy + 28.9602 *lens_ipow(dx, 3)*lens_ipow(dy, 3) + 8.62356e-06 *lens_ipow(y, 4)*dx*dy*lambda + 4.44024e-06 *lens_ipow(x, 4)*y*lens_ipow(dx, 3) + 1.56247e-05 *x*lens_ipow(y, 4)*lens_ipow(dx, 2)*dy*lambda + -0.0222421 *lens_ipow(x, 3)*lens_ipow(dx, 6)*dy+0.0f;
const double dx24 =  + 0.000710693 *x + -0.00434139 *x*lens_ipow(dy, 2) + -0.00524647 *x*lens_ipow(dx, 2) + 4.31178e-06 *lens_ipow(y, 4)*dx*lens_ipow(dy, 2) + -0.124387 *x*lens_ipow(dx, 6) + 7.51292e-08 *lens_ipow(y, 6)*lens_ipow(dx, 3) + 7.81234e-06 *x*lens_ipow(y, 4)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 1.3386e-06 *lens_ipow(x, 5)*lens_ipow(dx, 4) + -1.24505e-12 *lens_ipow(x, 7)*lens_ipow(y, 2) + -3.97407e-13 *lens_ipow(x, 9)+0.0f;
const double dx30 =  + 0.015178 *dx*dy + 0.000506772 *x*dy + 6.3465e-05 *x*y + 0.000232509 *y*dx*lambda + 0.00078848 *x*lens_ipow(dy, 3) + -1.93589e-05 *lens_ipow(y, 3)*dx*lens_ipow(dy, 2) + 1.38101e-08 *x*lens_ipow(y, 4)*dy + 1.27298e-08 *lens_ipow(x, 5)*dy + -1.82466e-05 *lens_ipow(x, 2)*y*lens_ipow(dx, 3)*lambda + -0.000233054 *lens_ipow(x, 2)*y*lens_ipow(dx, 3)*lens_ipow(dy, 2) + -3.90188 *lens_ipow(dx, 5)*lens_ipow(dy, 3)*lambda + -8.90303e-07 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx*lens_ipow(dy, 2)*lambda + 7.42655e-10 *lens_ipow(x, 3)*lens_ipow(y, 4)*dy*lambda + 1.25541e-06 *lens_ipow(x, 5)*lens_ipow(dy, 5)+0.0f;
const double dx31 =  + -0.0451151  + 0.000603328 *lambda + 0.0254983 *lens_ipow(dy, 2) + 0.005402 *lens_ipow(dx, 2) + 0.00122642 *y*dy + 0.000103108 *lens_ipow(y, 2) + 3.17325e-05 *lens_ipow(x, 2) + 0.000232509 *x*dx*lambda + 4.18641e-05 *lens_ipow(y, 2)*lens_ipow(dy, 2) + -0.0439566 *lens_ipow(dy, 4)*lambda + 0.0188788 *y*lens_ipow(dx, 2)*lens_ipow(dy, 3) + -5.80768e-05 *x*lens_ipow(y, 2)*dx*lens_ipow(dy, 2) + 2.76202e-08 *lens_ipow(x, 2)*lens_ipow(y, 3)*dy + 1.38875e-06 *lens_ipow(y, 4)*lens_ipow(dy, 2)*lambda + -1.24613e-09 *lens_ipow(y, 6)*lambda + -6.08221e-06 *lens_ipow(x, 3)*lens_ipow(dx, 3)*lambda + -7.76845e-05 *lens_ipow(x, 3)*lens_ipow(dx, 3)*lens_ipow(dy, 2) + -8.90303e-07 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx*lens_ipow(dy, 2)*lambda + 7.42655e-10 *lens_ipow(x, 4)*lens_ipow(y, 3)*dy*lambda+0.0f;
const double dx32 =  + 0.557248 *dx*dy + 0.010804 *y*dx + 0.015178 *x*dy + 0.000232509 *x*y*lambda + 0.0188788 *lens_ipow(y, 2)*dx*lens_ipow(dy, 3) + -1.93589e-05 *x*lens_ipow(y, 3)*lens_ipow(dy, 2) + -1.82466e-05 *lens_ipow(x, 3)*y*lens_ipow(dx, 2)*lambda + -0.000233054 *lens_ipow(x, 3)*y*lens_ipow(dx, 2)*lens_ipow(dy, 2) + -19.5094 *x*lens_ipow(dx, 4)*lens_ipow(dy, 3)*lambda + -2.96768e-07 *lens_ipow(x, 3)*lens_ipow(y, 3)*lens_ipow(dy, 2)*lambda+0.0f;
const double dx33 =  + -0.229785  + 0.863576 *lens_ipow(dy, 2) + 0.278624 *lens_ipow(dx, 2) + 0.0509966 *y*dy + 0.000613212 *lens_ipow(y, 2) + 0.015178 *x*dx + 0.000253386 *lens_ipow(x, 2) + 2.79094e-05 *lens_ipow(y, 3)*dy + 0.00118272 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -0.175826 *y*lens_ipow(dy, 3)*lambda + 0.0283182 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + -3.87179e-05 *x*lens_ipow(y, 3)*dx*dy + 6.90505e-09 *lens_ipow(x, 2)*lens_ipow(y, 4) + 2.12163e-09 *lens_ipow(x, 6) + 5.55501e-07 *lens_ipow(y, 5)*dy*lambda + -0.000155369 *lens_ipow(x, 3)*y*lens_ipow(dx, 3)*dy + -11.7057 *x*lens_ipow(dx, 5)*lens_ipow(dy, 2)*lambda + -5.93535e-07 *lens_ipow(x, 3)*lens_ipow(y, 3)*dx*dy*lambda + 1.85664e-10 *lens_ipow(x, 4)*lens_ipow(y, 4)*lambda + 1.04618e-06 *lens_ipow(x, 6)*lens_ipow(dy, 4)+0.0f;
const double dx34 =  + 0.000603328 *y + 0.000232509 *x*y*dx + -0.0439566 *y*lens_ipow(dy, 4) + 2.7775e-07 *lens_ipow(y, 5)*lens_ipow(dy, 2) + -1.78018e-10 *lens_ipow(y, 7) + -6.08221e-06 *lens_ipow(x, 3)*y*lens_ipow(dx, 3) + -3.90188 *x*lens_ipow(dx, 5)*lens_ipow(dy, 3) + -2.96768e-07 *lens_ipow(x, 3)*lens_ipow(y, 3)*dx*lens_ipow(dy, 2) + 1.85664e-10 *lens_ipow(x, 4)*lens_ipow(y, 4)*dy+0.0f;
const double dx40 =  + -0.00216814 *dx + -7.15956e-05 *x + -0.000464373 *y*dx*dy + -3.35769e-05 *lens_ipow(y, 2)*dx + -0.00117037 *x*lens_ipow(dx, 2) + -6.69887e-05 *x*y*dy + -3.7277e-06 *x*lens_ipow(y, 2) + -0.000145342 *lens_ipow(x, 2)*dx + -4.3841e-06 *lens_ipow(x, 3) + -1.03372e-11 *lens_ipow(x, 7) + -4.75323e-13 *lens_ipow(x, 3)*lens_ipow(y, 6) + -1.81507e-13 *lens_ipow(x, 7)*lens_ipow(y, 2)+0.0f;
const double dx41 =  + -0.00252994 *dy + -0.000119953 *y + -0.000464373 *x*dx*dy + -6.71539e-05 *x*y*dx + -3.34944e-05 *lens_ipow(x, 2)*dy + -3.7277e-06 *lens_ipow(x, 2)*y + -0.193892 *lens_ipow(dy, 5) + -9.09209e-05 *lens_ipow(y, 3)*lens_ipow(dy, 2) + -5.09227e-06 *lens_ipow(y, 4)*dy + -8.19632e-08 *lens_ipow(y, 5) + -7.12985e-13 *lens_ipow(x, 4)*lens_ipow(y, 5) + -4.53767e-14 *lens_ipow(x, 8)*y+0.0f;
const double dx42 =  + -0.0880021 *dx + -0.00216814 *x + -0.000464373 *x*y*dy + -3.35769e-05 *x*lens_ipow(y, 2) + -0.00117037 *lens_ipow(x, 2)*dx + -4.84473e-05 *lens_ipow(x, 3) + -5.49842 *dx*lens_ipow(dy, 4) + -11.8131 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + -3.8915 *lens_ipow(dx, 5)+0.0f;
const double dx43 =  + -0.0847628 *dy + -0.00252994 *y + -0.000464373 *x*y*dx + -3.34944e-05 *lens_ipow(x, 2)*y + -20.1392 *lens_ipow(dy, 5) + -10.9968 *lens_ipow(dx, 2)*lens_ipow(dy, 3) + -5.90657 *lens_ipow(dx, 4)*dy + -0.969459 *y*lens_ipow(dy, 4) + -4.54604e-05 *lens_ipow(y, 4)*dy + -1.01845e-06 *lens_ipow(y, 5)+0.0f;
const double dx44 =  + 2.00959  + -8.74532 *lambda + 13.4371 *lens_ipow(lambda, 2) + -7.10573 *lens_ipow(lambda, 3)+0.0f;
} break;