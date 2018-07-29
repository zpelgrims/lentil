const float out_x =  + 53.3813 *dx + 0.154777 *x + 0.261528 *x*lambda + 13.3025 *dx*lambda + -0.0224505 *y*dx*dy + -33.5149 *lens_ipow(dx, 3) + -0.179304 *x*lens_ipow(lambda, 2) + -33.3313 *dx*lens_ipow(dy, 2) + -0.000100913 *x*lens_ipow(y, 2) + -9.81196e-05 *lens_ipow(x, 3) + -0.172202 *x*lens_ipow(dy, 2) + -0.194791 *x*lens_ipow(dx, 2) + -9.15742 *dx*lens_ipow(lambda, 2) + 0.00197297 *lens_ipow(x, 2)*dx*lambda + 0.00135443 *lens_ipow(y, 2)*dx*lambda + 0.0128352 *x*y*lens_ipow(dx, 2)*dy + 0.272568 *x*lens_ipow(dx, 4) + 15.7349 *lens_ipow(dx, 5) + 0.477671 *x*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 14.5467 *dx*lens_ipow(dy, 4) + 0.262767 *x*lens_ipow(dy, 4) + 0.00455317 *lens_ipow(y, 2)*dx*lens_ipow(dy, 2) + -9.21041e-05 *lens_ipow(x, 3)*lens_ipow(dx, 2) + 29.958 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + -0.000218375 *lens_ipow(x, 2)*y*dx*dy*lambda + -0.0117472 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2)*lambda + -0.0109065 *lens_ipow(y, 2)*lens_ipow(dx, 3)*lens_ipow(lambda, 2) + -6.45965e-13 *lens_ipow(x, 5)*lens_ipow(y, 4);
const float out_y =  + 0.154573 *y + 53.3816 *dy + 13.2961 *dy*lambda + 0.262502 *y*lambda + -0.172232 *y*lens_ipow(dx, 2) + -0.194729 *y*lens_ipow(dy, 2) + -0.0226905 *x*dx*dy + -33.3032 *lens_ipow(dx, 2)*dy + -0.180011 *y*lens_ipow(lambda, 2) + -0.000101256 *lens_ipow(x, 2)*y + -9.14292 *dy*lens_ipow(lambda, 2) + -9.87738e-05 *lens_ipow(y, 3) + -33.5367 *lens_ipow(dy, 3) + 0.00136169 *lens_ipow(x, 2)*dy*lambda + 0.00197757 *lens_ipow(y, 2)*dy*lambda + 0.00437516 *lens_ipow(x, 2)*lens_ipow(dx, 2)*dy + -0.000123302 *x*lens_ipow(y, 2)*dx*dy + 29.6641 *lens_ipow(dx, 2)*lens_ipow(dy, 3) + 0.262752 *y*lens_ipow(dx, 4) + 15.8211 *lens_ipow(dy, 5) + 0.0125992 *x*y*dx*lens_ipow(dy, 2) + 0.27136 *y*lens_ipow(dy, 4) + 0.468323 *y*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 14.5036 *lens_ipow(dx, 4)*dy + -8.73164e-05 *lens_ipow(y, 3)*lens_ipow(dy, 2) + -0.0115973 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy*lambda + -0.0109593 *lens_ipow(x, 2)*lens_ipow(dy, 3)*lens_ipow(lambda, 2) + -6.01224e-13 *lens_ipow(x, 4)*lens_ipow(y, 5);
const float out_dx =  + 0.400102 *dx + -0.0177451 *x + 0.0065151 *x*lambda + -0.00972886 *y*dx*dy + 6.01178e-05 *x*y*dy + 5.84495e-05 *lens_ipow(x, 2)*dx + -0.534959 *lens_ipow(dx, 3) + -0.00455593 *x*lens_ipow(lambda, 2) + -0.512289 *dx*lens_ipow(dy, 2) + -2.82159e-06 *x*lens_ipow(y, 2) + -2.74954e-06 *lens_ipow(x, 3) + -0.00566831 *x*lens_ipow(dy, 2) + -0.0142906 *x*lens_ipow(dx, 2) + -5.6025e-09 *lens_ipow(x, 3)*lens_ipow(y, 2) + 0.143072 *lens_ipow(dx, 5) + 0.00399362 *x*lens_ipow(dy, 4) + 0.473233 *lens_ipow(dx, 3)*lens_ipow(dy, 2)*lambda + 7.27853e-09 *lens_ipow(x, 3)*lens_ipow(y, 2)*lambda + -1.44085e-08 *x*lens_ipow(y, 4)*lens_ipow(dx, 2) + 3.97335e-10 *lens_ipow(x, 3)*lens_ipow(y, 3)*dy + -0.028671 *y*dx*lens_ipow(dy, 5) + -2.94065e-08 *lens_ipow(x, 5)*lens_ipow(dx, 2) + 4.03772e-10 *lens_ipow(x, 4)*lens_ipow(y, 2)*dx + 0.00151553 *x*y*lens_ipow(dx, 4)*dy + -0.0246004 *x*lens_ipow(dx, 6)*lambda + -1.79423e-11 *lens_ipow(x, 7)*lens_ipow(dy, 2) + -0.000274599 *lens_ipow(y, 3)*lens_ipow(dx, 3)*lens_ipow(dy, 3) + 7.23344e-11 *lens_ipow(x, 7)*lens_ipow(dx, 2)*lambda;
const float out_dy =  + -0.0177516 *y + 0.400086 *dy + 0.00653363 *y*lambda + -0.00564628 *y*lens_ipow(dx, 2) + 5.81312e-05 *lens_ipow(y, 2)*dy + -0.0142844 *y*lens_ipow(dy, 2) + -0.00974129 *x*dx*dy + 5.99651e-05 *x*y*dx + -0.5118 *lens_ipow(dx, 2)*dy + -0.00456705 *y*lens_ipow(lambda, 2) + -2.83229e-06 *lens_ipow(x, 2)*y + -2.7451e-06 *lens_ipow(y, 3) + -0.53431 *lens_ipow(dy, 3) + 0.00412116 *y*lens_ipow(dx, 4) + 0.140168 *lens_ipow(dy, 5) + -5.61012e-09 *lens_ipow(x, 2)*lens_ipow(y, 3) + 0.464705 *lens_ipow(dx, 2)*lens_ipow(dy, 3)*lambda + 7.28792e-09 *lens_ipow(x, 2)*lens_ipow(y, 3)*lambda + -1.31855e-08 *lens_ipow(x, 4)*y*lens_ipow(dy, 2) + -5.68574e-09 *lens_ipow(y, 5)*lens_ipow(dx, 2) + -2.94733e-08 *lens_ipow(y, 5)*lens_ipow(dy, 2) + 4.00332e-10 *lens_ipow(x, 3)*lens_ipow(y, 3)*dx + 0.00154966 *x*y*dx*lens_ipow(dy, 4) + 4.16278e-10 *lens_ipow(x, 2)*lens_ipow(y, 4)*dy + -0.0286077 *x*lens_ipow(dx, 5)*dy + -0.025514 *y*lens_ipow(dy, 6)*lambda + -0.00026292 *lens_ipow(x, 3)*lens_ipow(dx, 3)*lens_ipow(dy, 3) + 7.09145e-11 *lens_ipow(y, 7)*lens_ipow(dy, 2)*lambda;
const float out_transmittance =  + 0.444199  + 1.18306 *lambda + -2.45887 *lens_ipow(lambda, 2) + 2.40675 *lens_ipow(lambda, 3) + -0.913302 *lens_ipow(lambda, 4) + -0.182152 *lens_ipow(dx, 4) + -1.13878e-05 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -0.400114 *lens_ipow(dx, 2)*lens_ipow(dy, 2) + -0.170388 *lens_ipow(dy, 4) + -9.45966e-09 *lens_ipow(x, 2)*lens_ipow(y, 2) + -1.71569e-05 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -0.07111 *lens_ipow(dy, 4)*lambda + -8.29195e-08 *lens_ipow(y, 4)*lens_ipow(dy, 2) + -3.42358e-08 *lens_ipow(x, 4)*lens_ipow(dy, 2) + 0.00744756 *x*lens_ipow(dx, 5) + 0.023203 *y*lens_ipow(dx, 2)*lens_ipow(dy, 3) + 0.00925466 *x*dx*lens_ipow(dy, 4) + 0.0028952 *y*lens_ipow(dy, 5) + -0.00019486 *x*y*lens_ipow(dx, 3)*dy + -0.196217 *lens_ipow(dx, 6)*lambda + 0.0212423 *y*lens_ipow(dy, 7) + 1.03502e-05 *lens_ipow(x, 2)*y*lens_ipow(dy, 5) + -0.954632 *lens_ipow(dx, 4)*lens_ipow(dy, 2)*lens_ipow(lambda, 2) + 0.0739488 *x*lens_ipow(dx, 3)*lens_ipow(dy, 4) + 5.92138e-05 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lens_ipow(lambda, 5) + 0.000122752 *lens_ipow(y, 3)*lens_ipow(dx, 6)*dy + 0.000262084 *lens_ipow(x, 3)*lens_ipow(dx, 5)*lens_ipow(dy, 2) + 5.4831e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*lens_ipow(dx, 5);
