case nikon__unknown__2014__65mm:
{
const double dx00 =  + 0.300576  + 0.214202 *lambda + -0.149684 *lens_ipow(lambda, 2) + -0.106212 *lens_ipow(dy, 2) + -0.151312 *lens_ipow(dx, 2) + -8.02976e-05 *lens_ipow(y, 2) + -0.000292366 *lens_ipow(x, 2) + 0.00162615 *y*dy*lambda + 0.00553463 *x*dx*lambda + 0.149579 *lens_ipow(dy, 4) + -4.9183e-08 *lens_ipow(y, 4) + -6.37694e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -0.00761878 *y*lens_ipow(dy, 3)*lambda + -0.0354864 *x*dx*lens_ipow(dy, 2)*lambda + 6.40721e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lambda + 0.0659996 *y*lens_ipow(dx, 4)*dy + 0.00141633 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lens_ipow(lambda, 2) + 7.48647e-08 *lens_ipow(x, 5)*dx*lambda+0.0f;
const double dx01 =  + -0.0407341 *dx*dy + 0.00241964 *y*dx + -0.000160595 *x*y + 0.00162615 *x*dy*lambda + -0.0131487 *y*lens_ipow(dx, 3) + -1.96732e-07 *x*lens_ipow(y, 3) + -4.25129e-07 *lens_ipow(x, 3)*y + -0.00761878 *x*lens_ipow(dy, 3)*lambda + 4.27147e-07 *lens_ipow(x, 3)*y*lambda + -4.30229 *lens_ipow(dx, 3)*lens_ipow(dy, 3) + 0.0659996 *x*lens_ipow(dx, 4)*dy+0.0f;
const double dx02 =  + 42.0563  + 10.1414 *lambda + -6.97731 *lens_ipow(lambda, 2) + -21.0205 *lens_ipow(dy, 2) + -66.0932 *lens_ipow(dx, 2) + -0.0407341 *y*dy + 0.00120982 *lens_ipow(y, 2) + -0.302624 *x*dx + 0.00276732 *lens_ipow(x, 2)*lambda + 26.4377 *lens_ipow(dx, 4) + -0.019723 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -0.0177432 *lens_ipow(x, 2)*lens_ipow(dy, 2)*lambda + -12.9069 *y*lens_ipow(dx, 2)*lens_ipow(dy, 3) + 0.263999 *x*y*lens_ipow(dx, 3)*dy + 0.000944219 *lens_ipow(x, 3)*dx*lens_ipow(lambda, 2) + 1.24775e-08 *lens_ipow(x, 6)*lambda+0.0f;
const double dx03 =  + -42.041 *dx*dy + -0.0407341 *y*dx + -0.212424 *x*dy + 0.00162615 *x*y*lambda + 0.598316 *x*lens_ipow(dy, 3) + -0.0228563 *x*y*lens_ipow(dy, 2)*lambda + -0.0354864 *lens_ipow(x, 2)*dx*dy*lambda + -12.9069 *y*lens_ipow(dx, 3)*lens_ipow(dy, 2) + 0.0659996 *x*y*lens_ipow(dx, 4)+0.0f;
const double dx04 =  + 10.1414 *dx + 0.214202 *x + -13.9546 *dx*lambda + -0.299369 *x*lambda + 0.00162615 *x*y*dy + 0.00276732 *lens_ipow(x, 2)*dx + -0.00761878 *x*y*lens_ipow(dy, 3) + -0.0177432 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2) + 2.13574e-07 *lens_ipow(x, 3)*lens_ipow(y, 2) + 0.000944219 *lens_ipow(x, 3)*lens_ipow(dx, 2)*lambda + 1.24775e-08 *lens_ipow(x, 6)*dx+0.0f;
const double dx10 =  + -0.0405621 *dx*dy + 0.00241006 *x*dy + -0.000160966 *x*y + 0.00165483 *y*dx*lambda + -0.0130944 *x*lens_ipow(dy, 3) + -4.11856e-07 *x*lens_ipow(y, 3) + -1.95438e-07 *lens_ipow(x, 3)*y + -0.00793088 *y*lens_ipow(dx, 3)*lambda + 4.05267e-07 *x*lens_ipow(y, 3)*lambda + -4.38213 *lens_ipow(dx, 3)*lens_ipow(dy, 3) + 0.0651743 *y*dx*lens_ipow(dy, 4)+0.0f;
const double dx11 =  + 0.300596  + 0.214154 *lambda + -0.149526 *lens_ipow(lambda, 2) + -0.151727 *lens_ipow(dy, 2) + -0.106266 *lens_ipow(dx, 2) + -0.000292948 *lens_ipow(y, 2) + -8.04831e-05 *lens_ipow(x, 2) + 0.00550197 *y*dy*lambda + 0.00165483 *x*dx*lambda + 0.148119 *lens_ipow(dx, 4) + -6.17784e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -4.88595e-08 *lens_ipow(x, 4) + -0.035145 *y*lens_ipow(dx, 2)*dy*lambda + -0.00793088 *x*lens_ipow(dx, 3)*lambda + 6.07901e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lambda + 0.00143769 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 0.0651743 *x*dx*lens_ipow(dy, 4) + 7.53247e-08 *lens_ipow(y, 5)*dy*lambda+0.0f;
const double dx12 =  + -42.0772 *dx*dy + -0.212533 *y*dx + -0.0405621 *x*dy + 0.00165483 *x*y*lambda + 0.592477 *y*lens_ipow(dx, 3) + -0.035145 *lens_ipow(y, 2)*dx*dy*lambda + -0.0237926 *x*y*lens_ipow(dx, 2)*lambda + -13.1464 *x*lens_ipow(dx, 2)*lens_ipow(dy, 3) + 0.0651743 *x*y*lens_ipow(dy, 4)+0.0f;
const double dx13 =  + 42.0453  + 10.1934 *lambda + -7.0263 *lens_ipow(lambda, 2) + -66.1378 *lens_ipow(dy, 2) + -21.0386 *lens_ipow(dx, 2) + -0.303454 *y*dy + -0.0405621 *x*dx + 0.00120503 *lens_ipow(x, 2) + 0.00275099 *lens_ipow(y, 2)*lambda + 26.3617 *lens_ipow(dy, 4) + -0.0196416 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -0.0175725 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lambda + 0.00095846 *lens_ipow(y, 3)*dy*lens_ipow(lambda, 2) + -13.1464 *x*lens_ipow(dx, 3)*lens_ipow(dy, 2) + 0.260697 *x*y*dx*lens_ipow(dy, 3) + 1.25541e-08 *lens_ipow(y, 6)*lambda+0.0f;
const double dx14 =  + 10.1934 *dy + 0.214154 *y + -14.0526 *dy*lambda + -0.299053 *y*lambda + 0.00275099 *lens_ipow(y, 2)*dy + 0.00165483 *x*y*dx + -0.0175725 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + -0.00793088 *x*y*lens_ipow(dx, 3) + 2.02634e-07 *lens_ipow(x, 2)*lens_ipow(y, 3) + 0.00095846 *lens_ipow(y, 3)*lens_ipow(dy, 2)*lambda + 1.25541e-08 *lens_ipow(y, 6)*dy+0.0f;
const double dx20 =  + -0.0215832  + 0.0071058 *lambda + -0.005099 *lens_ipow(lambda, 2) + -0.00446894 *lens_ipow(dy, 2) + -0.0123398 *lens_ipow(dx, 2) + 7.05871e-05 *y*dy + -4.9807e-06 *lens_ipow(y, 2) + 0.000104232 *x*dx + -1.54856e-05 *lens_ipow(x, 2) + -0.000268392 *y*lens_ipow(dy, 3) + -0.000489878 *y*lens_ipow(dx, 2)*dy + -6.29145e-06 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -0.000582768 *x*lens_ipow(dx, 3) + -2.58302e-08 *lens_ipow(x, 2)*lens_ipow(y, 2) + 3.83046e-08 *lens_ipow(x, 2)*lens_ipow(y, 2)*lambda + -0.00146256 *x*dx*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 3.5036e-09 *lens_ipow(x, 2)*lens_ipow(y, 3)*dy + 3.16905e-09 *lens_ipow(x, 5)*dx + 1.57895e-11 *lens_ipow(x, 3)*lens_ipow(y, 4)*dx+0.0f;
const double dx21 =  + -0.00820278 *dx*dy + 7.05871e-05 *x*dy + -9.9614e-06 *x*y + -0.000268392 *x*lens_ipow(dy, 3) + -0.000489878 *x*lens_ipow(dx, 2)*dy + -1.25829e-05 *x*y*lens_ipow(dx, 2) + -1.72201e-08 *lens_ipow(x, 3)*y + 2.55364e-08 *lens_ipow(x, 3)*y*lambda + 3.5036e-09 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy + 1.57895e-11 *lens_ipow(x, 4)*lens_ipow(y, 3)*dx+0.0f;
const double dx22 =  + 0.323165  + -0.484014 *lens_ipow(dy, 2) + -0.00820278 *y*dy + -0.0246797 *x*dx + 5.21162e-05 *lens_ipow(x, 2) + -4.12218 *lens_ipow(dx, 2)*lambda + 0.68363 *lens_ipow(dy, 4) + 2.63558 *lens_ipow(dx, 2)*lens_ipow(lambda, 2) + 4.21695 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -0.000979756 *x*y*dx*dy + -1.25829e-05 *x*lens_ipow(y, 2)*dx + -0.000874152 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -0.000731278 *lens_ipow(x, 2)*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 5.28174e-10 *lens_ipow(x, 6) + 56.82 *lens_ipow(dx, 4)*lens_ipow(lambda, 3) + -63.1026 *lens_ipow(dx, 4)*lens_ipow(lambda, 4) + 3.94737e-12 *lens_ipow(x, 4)*lens_ipow(y, 4)+0.0f;
const double dx23 =  + -0.968027 *dx*dy + -0.00820278 *y*dx + -0.00893787 *x*dy + 7.05871e-05 *x*y + 2.73452 *dx*lens_ipow(dy, 3) + 2.8113 *lens_ipow(dx, 3)*dy + -0.000805176 *x*y*lens_ipow(dy, 2) + -0.000489878 *x*y*lens_ipow(dx, 2) + -0.00146256 *lens_ipow(x, 2)*dx*dy*lens_ipow(lambda, 2) + 1.16787e-09 *lens_ipow(x, 3)*lens_ipow(y, 3)+0.0f;
const double dx24 =  + 0.0071058 *x + -0.010198 *x*lambda + -1.37406 *lens_ipow(dx, 3) + 1.75705 *lens_ipow(dx, 3)*lambda + 1.27682e-08 *lens_ipow(x, 3)*lens_ipow(y, 2) + -0.00146256 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2)*lambda + 34.092 *lens_ipow(dx, 5)*lens_ipow(lambda, 2) + -50.4821 *lens_ipow(dx, 5)*lens_ipow(lambda, 3)+0.0f;
const double dx30 =  + -0.00816137 *dx*dy + 7.2313e-05 *y*dx + -9.88305e-06 *x*y + -0.000466641 *y*dx*lens_ipow(dy, 2) + -0.000268153 *y*lens_ipow(dx, 3) + -1.22018e-05 *x*y*lens_ipow(dy, 2) + -1.80064e-08 *x*lens_ipow(y, 3) + 2.58323e-08 *x*lens_ipow(y, 3)*lambda + 3.23631e-09 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx + 1.58217e-11 *lens_ipow(x, 3)*lens_ipow(y, 4)*dy+0.0f;
const double dx31 =  + -0.021683  + 0.00739137 *lambda + -0.00535879 *lens_ipow(lambda, 2) + -0.0122547 *lens_ipow(dy, 2) + -0.00426471 *lens_ipow(dx, 2) + 6.60709e-05 *y*dy + -1.50681e-05 *lens_ipow(y, 2) + 7.2313e-05 *x*dx + -4.94152e-06 *lens_ipow(x, 2) + -0.000543228 *y*lens_ipow(dy, 3) + 8.51591e-07 *lens_ipow(y, 3)*dy + -0.000466641 *x*dx*lens_ipow(dy, 2) + -0.000268153 *x*lens_ipow(dx, 3) + -6.10089e-06 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -2.70096e-08 *lens_ipow(x, 2)*lens_ipow(y, 2) + 3.87485e-08 *lens_ipow(x, 2)*lens_ipow(y, 2)*lambda + -0.0016956 *y*lens_ipow(dx, 2)*dy*lens_ipow(lambda, 2) + 3.23631e-09 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx + -1.9331e-10 *lens_ipow(y, 6)*lens_ipow(dx, 2) + 1.58217e-11 *lens_ipow(x, 4)*lens_ipow(y, 3)*dy+0.0f;
const double dx32 =  + -0.964315 *dx*dy + -0.00852942 *y*dx + -0.00816137 *x*dy + 7.2313e-05 *x*y + 2.87105 *dx*lens_ipow(dy, 3) + 2.71105 *lens_ipow(dx, 3)*dy + -0.000466641 *x*y*lens_ipow(dy, 2) + -0.00080446 *x*y*lens_ipow(dx, 2) + -0.0016956 *lens_ipow(y, 2)*dx*dy*lens_ipow(lambda, 2) + 1.07877e-09 *lens_ipow(x, 3)*lens_ipow(y, 3) + -5.52315e-11 *lens_ipow(y, 7)*dx+0.0f;
const double dx33 =  + 0.323567  + -0.883731 *lens_ipow(dy, 2) + -0.482158 *lens_ipow(dx, 2) + -0.0245093 *y*dy + 3.30354e-05 *lens_ipow(y, 2) + -0.00816137 *x*dx + -1.06125 *lens_ipow(dy, 2)*lambda + 4.30658 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.677763 *lens_ipow(dx, 4) + -0.000814843 *lens_ipow(y, 2)*lens_ipow(dy, 2) + 2.12898e-07 *lens_ipow(y, 4) + -0.000933282 *x*y*dx*dy + -1.22018e-05 *lens_ipow(x, 2)*y*dy + 6.6113 *lens_ipow(dy, 4)*lambda + -0.000847798 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(lambda, 2) + 3.95543e-12 *lens_ipow(x, 4)*lens_ipow(y, 4)+0.0f;
const double dx34 =  + 0.00739137 *y + -0.0107176 *y*lambda + -0.353751 *lens_ipow(dy, 3) + 1.32226 *lens_ipow(dy, 5) + 1.29162e-08 *lens_ipow(x, 2)*lens_ipow(y, 3) + -0.0016956 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy*lambda+0.0f;
const double dx40 =  + -0.00161026 *lens_ipow(dx, 3) + -2.20269e-08 *lens_ipow(x, 3) + -7.54943e-05 *x*lens_ipow(dx, 2)*lambda + -0.00566818 *dx*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 1.56765e-05 *x*y*lens_ipow(dy, 3) + -3.90938e-07 *lens_ipow(y, 3)*dx*dy*lens_ipow(lambda, 2) + 9.49758e-08 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dx, 3) + -0.0374518 *lens_ipow(dx, 5)*lens_ipow(lambda, 3) + 0.0681553 *y*lens_ipow(dx, 3)*lens_ipow(dy, 5)+0.0f;
const double dx41 =  + -2.5994e-06 *y + -0.00177421 *lens_ipow(dy, 3) + -0.00691258 *lens_ipow(dx, 2)*dy*lens_ipow(lambda, 2) + -4.25402e-07 *lens_ipow(y, 3)*lens_ipow(dy, 2) + 7.83823e-06 *lens_ipow(x, 2)*lens_ipow(dy, 3) + -0.0212378 *lens_ipow(dy, 5)*lens_ipow(lambda, 2) + -1.17281e-06 *x*lens_ipow(y, 2)*dx*dy*lens_ipow(lambda, 2) + 6.33172e-08 *lens_ipow(x, 3)*y*lens_ipow(dx, 3) + -2.35828e-06 *lens_ipow(y, 3)*lens_ipow(dx, 4)*lambda + 0.0681553 *x*lens_ipow(dx, 3)*lens_ipow(dy, 5)+0.0f;
const double dx42 =  + -0.999437 *lens_ipow(dx, 3) + -0.00483079 *x*lens_ipow(dx, 2) + -4.12384 *dx*lens_ipow(dy, 2)*lambda + -7.54943e-05 *lens_ipow(x, 2)*dx*lambda + 2.7773 *dx*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -0.0138252 *y*dx*dy*lens_ipow(lambda, 2) + -0.00566818 *x*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -7.18756 *lens_ipow(dx, 5)*lambda + 7.62851 *lens_ipow(dx, 7) + -3.90938e-07 *x*lens_ipow(y, 3)*dy*lens_ipow(lambda, 2) + 9.49758e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*lens_ipow(dx, 2) + -2.35828e-06 *lens_ipow(y, 4)*lens_ipow(dx, 3)*lambda + -0.187259 *x*lens_ipow(dx, 4)*lens_ipow(lambda, 3) + 0.204466 *x*y*lens_ipow(dx, 2)*lens_ipow(dy, 5)+0.0f;
const double dx43 =  + -0.919717 *lens_ipow(dy, 3) + -0.00532264 *y*lens_ipow(dy, 2) + -0.353011 *lens_ipow(dy, 3)*lambda + -4.12384 *lens_ipow(dx, 2)*dy*lambda + 2.7773 *lens_ipow(dx, 2)*dy*lens_ipow(lambda, 2) + -0.00691258 *y*lens_ipow(dx, 2)*lens_ipow(lambda, 2) + -2.12701e-07 *lens_ipow(y, 4)*dy + -0.0113364 *x*dx*dy*lens_ipow(lambda, 2) + 2.35147e-05 *lens_ipow(x, 2)*y*lens_ipow(dy, 2) + -3.75364 *lens_ipow(dy, 5)*lambda + -0.106189 *y*lens_ipow(dy, 4)*lens_ipow(lambda, 2) + -3.90938e-07 *x*lens_ipow(y, 3)*dx*lens_ipow(lambda, 2) + 0.340776 *x*y*lens_ipow(dx, 3)*lens_ipow(dy, 4)+0.0f;
const double dx44 =  + 3.04018  + -16.6368 *lambda + 36.3576 *lens_ipow(lambda, 2) + -36.6459 *lens_ipow(lambda, 3) + 14.1754 *lens_ipow(lambda, 4) + -0.0882527 *lens_ipow(dy, 4) + -2.06192 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -3.77472e-05 *lens_ipow(x, 2)*lens_ipow(dx, 2) + 2.7773 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + -0.0138252 *y*lens_ipow(dx, 2)*dy*lambda + -0.0113364 *x*dx*lens_ipow(dy, 2)*lambda + -0.625607 *lens_ipow(dy, 6) + -1.19793 *lens_ipow(dx, 6) + -0.0424755 *y*lens_ipow(dy, 5)*lambda + -7.81877e-07 *x*lens_ipow(y, 3)*dx*dy*lambda + -5.8957e-07 *lens_ipow(y, 4)*lens_ipow(dx, 4) + -0.112355 *x*lens_ipow(dx, 5)*lens_ipow(lambda, 2)+0.0f;
} break;