case angenieux_double_gauss_9999_50mm:
{
out[0] =  + 50.0087 *dx + -0.625383 *x + 0.70729 *x*lambda + -19.0752 *dx*lens_ipow(dy, 2) + -23.3151 *lens_ipow(dx, 3) + 0.157666 *y*dx*dy + 0.00614257 *lens_ipow(y, 2)*dx + -0.558055 *x*lens_ipow(lambda, 2) + 0.243664 *x*lens_ipow(dy, 2) + 0.233536 *x*lens_ipow(dx, 2) + 0.00539894 *x*y*dy + -0.00125972 *x*lens_ipow(y, 2) + -0.00129394 *lens_ipow(x, 3) + 0.000547845 *x*lens_ipow(y, 2)*lambda + 0.0225247 *lens_ipow(x, 2)*dx*lambda + 0.000592132 *lens_ipow(x, 3)*lambda + 0.0981907 *x*y*lens_ipow(dx, 2)*dy + -7.28386e-07 *x*lens_ipow(y, 4) + 0.0751768 *lens_ipow(x, 2)*lens_ipow(dx, 3) + 31.3603 *lens_ipow(dx, 5)*lambda + 3.21257 *x*lens_ipow(dx, 4)*lambda + 0.000245089 *lens_ipow(y, 4)*dx*lens_ipow(dy, 2) + 5.37895 *x*lens_ipow(dx, 2)*lens_ipow(dy, 4) + -4.82991e-05 *lens_ipow(x, 4)*dx*lens_ipow(lambda, 2) + -9.42516e-09 *lens_ipow(x, 5)*lens_ipow(y, 2) + -2.85556e-09 *lens_ipow(x, 7) + 4.76941 *y*lens_ipow(dx, 5)*dy*lambda + -2.9311e-11 *lens_ipow(x, 3)*lens_ipow(y, 6);
out[1] =  + 49.4517 *dy + -0.631852 *y + 0.858956 *dy*lambda + 0.7031 *y*lambda + -19.3886 *lens_ipow(dy, 3) + -19.773 *lens_ipow(dx, 2)*dy + -0.543383 *y*lens_ipow(lambda, 2) + 0.534516 *y*lens_ipow(dy, 2) + 0.259969 *y*lens_ipow(dx, 2) + 0.0175841 *lens_ipow(y, 2)*dy + -0.00120744 *lens_ipow(y, 3) + 0.180395 *x*dx*dy + 0.00786971 *x*y*dx + 0.00526514 *lens_ipow(x, 2)*dy + -0.0012916 *lens_ipow(x, 2)*y + 0.000500256 *lens_ipow(y, 3)*lambda + 0.000553391 *lens_ipow(x, 2)*y*lambda + -0.00222561 *lens_ipow(y, 3)*lens_ipow(dy, 2) + -4.38423e-05 *lens_ipow(y, 4)*dy + 0.0612953 *x*y*dx*lens_ipow(dy, 2) + -0.000952124 *x*lens_ipow(y, 2)*dx*dy + -1.88183e-05 *x*lens_ipow(y, 3)*dx + -3.33147e-09 *lens_ipow(y, 7) + -8.01055e-09 *lens_ipow(x, 2)*lens_ipow(y, 5) + 0.000282092 *lens_ipow(x, 4)*lens_ipow(dx, 2)*dy + -4.22047e-06 *lens_ipow(x, 4)*y*lens_ipow(dy, 2) + -8.45799e-09 *lens_ipow(x, 4)*lens_ipow(y, 3) + -7.47753e-12 *lens_ipow(x, 8)*y;
out[2] =  + -0.617487 *dx + -0.0123227 *x + 0.0185685 *dx*lambda + -0.00885177 *x*lambda + 0.153116 *dx*lens_ipow(dy, 2) + 0.279253 *lens_ipow(dx, 3) + 0.00725753 *x*lens_ipow(lambda, 2) + -0.00107725 *x*lens_ipow(dy, 2) + -5.80527e-05 *x*y*dy + 1.66458e-05 *x*lens_ipow(y, 2) + 1.77503e-05 *lens_ipow(x, 3) + -7.90104e-06 *x*lens_ipow(y, 2)*lambda + -0.000237102 *lens_ipow(x, 2)*dx*lambda + -8.78732e-06 *lens_ipow(x, 3)*lambda + 0.0002694 *lens_ipow(y, 2)*lens_ipow(dx, 3) + -0.00437584 *x*lens_ipow(dy, 4) + -2.56472e-07 *x*lens_ipow(y, 3)*dy + 3.63808e-05 *lens_ipow(x, 2)*y*dx*dy + 1.43766e-05 *lens_ipow(x, 3)*lens_ipow(dx, 2) + 2.95948e-08 *lens_ipow(x, 3)*lens_ipow(y, 2) + -0.309751 *lens_ipow(dx, 5)*lambda + -0.0128176 *x*lens_ipow(dx, 4)*lambda + 0.00111078 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2)*lambda + 0.000880952 *lens_ipow(x, 2)*lens_ipow(dx, 3)*lambda + 4.80978e-11 *x*lens_ipow(y, 6) + 3.98432e-11 *lens_ipow(x, 7) + 1.31811e-10 *lens_ipow(y, 7)*dx*dy + 1.85146e-15 *lens_ipow(x, 7)*lens_ipow(y, 4);
out[3] =  + -0.61682 *dy + -0.0119668 *y + 0.0113263 *dy*lambda + -0.00911808 *y*lambda + 0.328767 *lens_ipow(dy, 3) + 0.40495 *lens_ipow(dx, 2)*dy + 0.00703676 *y*lens_ipow(lambda, 2) + -0.00377317 *y*lens_ipow(dx, 2) + -0.000129118 *lens_ipow(y, 2)*dy + 1.02533e-05 *lens_ipow(y, 3) + 0.00289076 *x*dx*dy + -0.000110164 *x*y*dx + 1.4505e-05 *lens_ipow(x, 2)*y + -7.82077e-06 *lens_ipow(x, 2)*y*lambda + -0.303198 *lens_ipow(dy, 5) + -0.432733 *lens_ipow(dx, 2)*lens_ipow(dy, 3) + -0.299426 *lens_ipow(dx, 4)*dy + 0.000781458 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + 3.20858e-08 *lens_ipow(y, 5) + 2.56728e-05 *x*lens_ipow(y, 2)*dx*dy + 4.13021e-08 *lens_ipow(x, 2)*lens_ipow(y, 3) + 2.11827e-08 *lens_ipow(x, 4)*y + -2.44504e-08 *lens_ipow(y, 5)*lambda + -0.0473817 *y*lens_ipow(dy, 6) + 1.99151e-06 *x*lens_ipow(y, 3)*lens_ipow(dx, 3) + -1.00118e-09 *lens_ipow(x, 6)*dy + -4.9049e-14 *lens_ipow(x, 2)*lens_ipow(y, 8)*dy + 2.30758e-11 *lens_ipow(x, 8)*lens_ipow(dy, 3);
out_transmittance =  + 0.236859  + 0.860742 *lambda + -1.17964 *lens_ipow(lambda, 2) + 0.570311 *lens_ipow(lambda, 3) + -0.237159 *lens_ipow(dy, 4) + -0.235384 *lens_ipow(dx, 4) + -0.010597 *y*lens_ipow(dy, 3) + -0.0100229 *y*lens_ipow(dx, 2)*dy + -0.000168744 *lens_ipow(y, 2)*lens_ipow(dy, 2) + -0.000122748 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -0.0105681 *x*dx*lens_ipow(dy, 2) + -0.0101157 *x*lens_ipow(dx, 3) + -0.000127847 *x*y*dx*dy + -0.000112047 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -8.57444e-08 *lens_ipow(x, 2)*lens_ipow(y, 2) + -4.66147e-08 *lens_ipow(x, 4) + -1.38237 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lambda + 0.956783 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + -0.00142196 *lens_ipow(y, 2)*lens_ipow(dy, 4) + -0.00145854 *lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + -1.62998e-10 *lens_ipow(y, 6) + -0.00252304 *x*y*dx*lens_ipow(dy, 3) + -0.00225779 *x*y*lens_ipow(dx, 3)*dy + -0.00205028 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + -0.00151833 *lens_ipow(x, 2)*lens_ipow(dx, 4) + -2.49674e-07 *lens_ipow(x, 4)*lens_ipow(dy, 2) + -0.000723719 *lens_ipow(x, 2)*lens_ipow(dy, 4)*lambda + -1.99059e-12 *lens_ipow(x, 4)*lens_ipow(y, 4);
} break;