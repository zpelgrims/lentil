case angenieux_double_gauss_1953_100mm:
{
out[0] =  + 92.3584 *dx + 0.0104136 *y + -0.527274 *x + 2.00056 *dx*lambda + -0.0168445 *y*lambda + 0.158455 *x*lambda;
out[1] =  + 92.1357 *dy + -0.515513 *y + 2.51865 *dy*lambda + 0.138919 *lens_ipow(dy, 2) + 0.137027 *y*lambda + 0.0074765 *y*dy;
out[2] =  + -0.57236 *dx + -7.10609e-06 *y + -0.00663669 *x + 0.00840292 *dx*lambda + 7.02599e-07 *lens_ipow(y, 2) + -0.000887943 *x*lambda;
out[3] =  + -0.564999 *dy + -0.00678183 *y + 0.00504171 *dy*lambda + -0.000737731 *y*lambda + -2.57503e-05 *y*dy + 8.41898e-07 *x*y;
out_transmittance =  + 0.330905  + 0.347233 *lambda + -0.236711 *lens_ipow(lambda, 2) + -0.0574053 *lens_ipow(dy, 2) + -0.0610943 *lens_ipow(dx, 2) + -0.000262871 *x*dx;
} break;
