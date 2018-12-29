case angenieux_double_gauss_1953_100mm:
{
out[0] =  + 51.0741 *dx + 0.164957 *x + 3.80311 *dx*lambda + -4.3292e-05 *lens_ipow(y, 2) + 0.0746279 *x*lambda + -0.00255573 *x*dy;
out[1] =  + 51.0449 *dy + 0.172198 *y + 3.92141 *dy*lambda + 0.0903945 *lens_ipow(dy, 2) + 0.061443 *y*lambda + 0.00456087 *y*dy;
out[2] =  + 0.329504 *dx + -0.0182912 *x + -0.00244742 *lens_ipow(dy, 2) + 0.0185914 *dx*lambda + 0.00185376 *x*lambda + -6.73609e-05 *x*dy;
out[3] =  + 0.000146546  + 0.331642 *dy + -0.0182062 *y + 0.0149156 *dy*lambda + 0.00170713 *y*lambda + 0.000104205 *x*dy;
out_transmittance =  + 0.588477  + 0.240844 *lambda + -0.165337 *lens_ipow(lambda, 2) + -0.062652 *lens_ipow(dy, 2) + -0.0669455 *lens_ipow(dx, 2) + 0.000297883 *y*dy;
} break;
