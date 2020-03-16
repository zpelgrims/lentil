case angenieux__double_gauss__1953__49mm:
{
const double dx00 =  + -0.645581  + 0.737721 *lambda + -0.541384 *lens_ipow(lambda, 2) + 0.251372 *lens_ipow(dy, 2) + 0.292751 *lens_ipow(dx, 2) + 0.00634489 *y*dy + -0.00112497 *lens_ipow(y, 2) + -0.00364223 *lens_ipow(x, 2) + 0.0463251 *x*dx*lambda + 0.00174955 *lens_ipow(x, 2)*lambda + -6.98933e-06 *lens_ipow(x, 4) + -5.08534e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const double dx01 =  + 0.0108479 *y*dx + 0.00634489 *x*dy + -0.00224995 *x*y + -6.78045e-08 *lens_ipow(x, 3)*lens_ipow(y, 3)+0.0f;
const double dx02 =  + 49.0822  + -20.5624 *lens_ipow(dy, 2) + -60.7723 *lens_ipow(dx, 2) + 0.00542395 *lens_ipow(y, 2) + 0.585503 *x*dx + 0.0231625 *lens_ipow(x, 2)*lambda+0.0f;
const double dx03 =  + -41.1247 *dx*dy + 0.502743 *x*dy + 0.00634489 *x*y+0.0f;
const double dx04 =  + 0.737721 *x + -1.08277 *x*lambda + 0.0231625 *lens_ipow(x, 2)*dx + 0.000583182 *lens_ipow(x, 3)+0.0f;
const double dx10 =  + -0.00223388 *x*y + 8.10214e-05 *lens_ipow(x, 3)*dy + -4.34638e-06 *lens_ipow(x, 3)*y + -0.00498764 *lens_ipow(y, 2)*dx*dy*lambda + -2.40395e-08 *x*lens_ipow(y, 5)+0.0f;
const double dx11 =  + -0.665901  + 0.815492 *lambda + -0.561464 *lens_ipow(lambda, 2) + 0.270037 *lens_ipow(dy, 2) + 0.179023 *lens_ipow(dx, 2) + -0.00365353 *lens_ipow(y, 2) + -0.00111694 *lens_ipow(x, 2) + -1.08659e-06 *lens_ipow(x, 4) + 0.205757 *y*lens_ipow(dy, 3)*lambda + -0.00997528 *x*y*dx*dy*lambda + 1.09441e-06 *lens_ipow(y, 5)*dy + -6.00988e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)+0.0f;
const double dx12 =  + -43.9531 *dx*dy + 0.358046 *y*dx + -0.00498764 *x*lens_ipow(y, 2)*dy*lambda+0.0f;
const double dx13 =  + 49.6001  + -66.2648 *lens_ipow(dy, 2) + -21.9766 *lens_ipow(dx, 2) + 0.540073 *y*dy + 2.02553e-05 *lens_ipow(x, 4) + 0.308636 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + -0.00498764 *x*lens_ipow(y, 2)*dx*lambda + 1.82401e-07 *lens_ipow(y, 6)+0.0f;
const double dx14 =  + 0.815492 *y + -1.12293 *y*lambda + 0.102879 *lens_ipow(y, 2)*lens_ipow(dy, 3) + -0.00498764 *x*lens_ipow(y, 2)*dx*dy+0.0f;
const double dx20 =  + -0.0115036  + -0.0107814 *lambda + 0.00751845 *lens_ipow(lambda, 2) + -0.00236438 *lens_ipow(dy, 2) + -9.29027e-05 *y*dy + 9.96414e-06 *lens_ipow(y, 2) + 3.38504e-05 *lens_ipow(x, 2) + 2.33684e-08 *lens_ipow(y, 4) + 7.76852e-05 *x*y*dx*dy + 1.48245e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + -2.23195e-06 *lens_ipow(x, 3)*dx + 9.53818e-08 *lens_ipow(x, 4)+0.0f;
const double dx21 =  + -9.29027e-05 *x*dy + 1.99283e-05 *x*y + 9.34736e-08 *x*lens_ipow(y, 3) + 3.88426e-05 *lens_ipow(x, 2)*dx*dy + 9.88302e-08 *lens_ipow(x, 3)*y + 0.00155439 *y*lens_ipow(dx, 3)*lens_ipow(lambda, 2)+0.0f;
const double dx22 =  + -0.609749  + 0.172424 *lens_ipow(dy, 2) + 0.794077 *lens_ipow(dx, 2) + 3.88426e-05 *lens_ipow(x, 2)*y*dy + -5.57988e-07 *lens_ipow(x, 4) + 0.00233159 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(lambda, 2)+0.0f;
const double dx23 =  + 0.344848 *dx*dy + -0.00472877 *x*dy + -9.29027e-05 *x*y + 3.88426e-05 *lens_ipow(x, 2)*y*dx+0.0f;
const double dx24 =  + -0.0107814 *x + 0.0150369 *x*lambda + 0.00155439 *lens_ipow(y, 2)*lens_ipow(dx, 3)*lambda+0.0f;
const double dx30 =  + 0.00418177 *dx*dy + -0.000124538 *y*dx + 1.98134e-05 *x*y + 1.0013e-07 *x*lens_ipow(y, 3) + 1.00381e-07 *lens_ipow(x, 3)*y + -1.5617e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy+0.0f;
const double dx31 =  + -0.0115421  + -0.010617 *lambda + 0.00737512 *lens_ipow(lambda, 2) + -0.00466356 *lens_ipow(dx, 2) + 3.87266e-05 *lens_ipow(y, 2) + -0.000124538 *x*dx + 9.90669e-06 *lens_ipow(x, 2) + -2.17587e-06 *lens_ipow(y, 3)*dy + 1.50195e-07 *lens_ipow(x, 2)*lens_ipow(y, 2) + 2.50954e-08 *lens_ipow(x, 4) + 3.315e-10 *lens_ipow(y, 6) + -7.80849e-09 *lens_ipow(x, 4)*y*dy+0.0f;
const double dx32 =  + 0.717511 *dx*dy + -0.00932712 *y*dx + 0.00418177 *x*dy + -0.000124538 *x*y+0.0f;
const double dx33 =  + -0.611352  + 0.825766 *lens_ipow(dy, 2) + 0.358756 *lens_ipow(dx, 2) + 0.00418177 *x*dx + -5.43968e-07 *lens_ipow(y, 4) + -3.90425e-09 *lens_ipow(x, 4)*lens_ipow(y, 2)+0.0f;
const double dx34 =  + -0.010617 *y + 0.0147502 *y*lambda+0.0f;
const double dx40 =  + -0.00096636 *dx + -0.00026575 *y*dx*dy + -0.000206141 *x*lens_ipow(dy, 2) + -0.000481189 *x*lens_ipow(dx, 2) + -2.50517e-07 *lens_ipow(x, 3) + -2.49723e-11 *lens_ipow(x, 3)*lens_ipow(y, 4)+0.0f;
const double dx41 =  + -0.000978559 *dy + -0.000490844 *y*lens_ipow(dy, 2) + -0.000210874 *y*lens_ipow(dx, 2) + -2.48452e-07 *lens_ipow(y, 3) + -0.00026575 *x*dx*dy + -2.49723e-11 *lens_ipow(x, 4)*lens_ipow(y, 3)+0.0f;
const double dx42 =  + -0.00096636 *x + -0.84785 *dx*lens_ipow(dy, 2) + -0.839919 *lens_ipow(dx, 3) + -0.000210874 *lens_ipow(y, 2)*dx + -0.00026575 *x*y*dy + -0.000481189 *lens_ipow(x, 2)*dx+0.0f;
const double dx43 =  + -0.000978559 *y + -0.841845 *lens_ipow(dy, 3) + -0.84785 *lens_ipow(dx, 2)*dy + -0.000490844 *lens_ipow(y, 2)*dy + -0.00026575 *x*y*dx + -0.000206141 *lens_ipow(x, 2)*dy+0.0f;
const double dx44 =  + 0.347462  + -0.472864 *lambda+0.0f;
} break;
