/*
    This file is part of corona-6: radiata.

    corona-6: radiata is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    corona-6: radiata is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with corona-6: radiata.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <math.h>

static inline void spectrum_cauchy_from_abbe(const float n_d, const float V_d, float *A, float *B)
{
  if(V_d == 0.0f)
  {
    *A = n_d;
    *B = 0.0f;
    return;
  }
  const float l_C = .6563f;
  const float l_F = .4861f;
  const float l_D = .587561f;
  const float c = (l_C*l_C * l_F*l_F)/(l_C*l_C - l_F*l_F);
  *B = (n_d - 1.0f)/V_d * c;
  *A = n_d - *B/(l_D*l_D);
}

static inline float spectrum_eta_from_abbe_um(const float n_d, const float V_d, const float lambda)
{
  float A, B;
  spectrum_cauchy_from_abbe(n_d, V_d, &A, &B);

  return A + B/(lambda*lambda);
}

static inline void spectrum_xyz_to_rgb(const float *const xyz, float *rgb)
{
  const float spectrum_M_XYZtosRGB[] = // Adobe sRGB D65
  {
    3.24071,    -0.969258,    0.0556352,  
  -1.53726 ,    1.87599  ,  -0.203996  , 
  -0.498571,    0.0415557,   1.05707
  };
  for(int k=0;k<3;k++)
  {
    rgb[k] = 0.0f;
    for(int i=0;i<3;i++) rgb[k] += xyz[i]*(spectrum_M_XYZtosRGB[k+3*i]);
  }
}

//#include "colorspace.h"

static const int spectrum_xyz_lambda_min = 360;
static const int spectrum_xyz_lambda_max = 830;
static const int spectrum_xyz_size = 83 - 36 + 1;
static const int spectrum_xyz_step = 10;
static const float spectrum_x[] = {0.000000122200,0.000005958600,0.000159952000,0.002361600000,0.019109700000,0.084736000000,0.204492000000,0.314679000000,0.383734000000,0.370702000000,0.342957000000,0.254085000000,0.132349000000,0.041072000000,0.005132000000,0.015444000000,0.071358000000,0.172953000000,0.304213000000,0.451584000000,0.616053000000,0.793832000000,0.951162000000,1.074300000000,1.134300000000,1.089100000000,0.950740000000,0.754930000000,0.535110000000,0.343690000000,0.204300000000,0.112210000000,0.057930000000,0.028623000000,0.013842000000,0.006605200000,0.003144700000,0.001505700000,0.000727450000,0.000356380000,0.000177730000,0.000090151000,0.000046339000,0.000024209000,0.000012855000,0.000006913000,0.000003767100,0.000002082000};
static const float spectrum_y[] = {0.000000013398,0.000000651100,0.000017364000,0.000253400000,0.002004400000,0.008756000000,0.021391000000,0.038676000000,0.062077000000,0.089456000000,0.128201000000,0.185190000000,0.253589000000,0.339133000000,0.460777000000,0.606741000000,0.761757000000,0.875211000000,0.961988000000,0.991761000000,0.997340000000,0.955552000000,0.868934000000,0.777405000000,0.658341000000,0.527963000000,0.398057000000,0.283493000000,0.179828000000,0.107633000000,0.060281000000,0.031800400000,0.015905100000,0.007748800000,0.003717740000,0.001768470000,0.000846190000,0.000407410000,0.000198730000,0.000098428000,0.000049737000,0.000025486000,0.000013249000,0.000007012800,0.000003764730,0.000002046130,0.000001128090,0.000000629700};
static const float spectrum_z[] = {0.000000535027,0.000026143700,0.000704776000,0.010482200000,0.086010900000,0.389366000000,0.972542000000,1.553480000000,1.967280000000,1.994800000000,1.745370000000,1.317560000000,0.772125000000,0.415254000000,0.218502000000,0.112044000000,0.060709000000,0.030451000000,0.013676000000,0.003988000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000,0.000000000000};


static inline void spectrum_xyz(const float lambda, float *xyz)
{
  //if(lambda < spectrum_xyz_lambda_min || lambda > spectrum_xyz_lambda_max) { xyz[0] = xyz[1] = xyz[2] = 0.0f; return; }
  float f = (lambda - spectrum_xyz_lambda_min)/spectrum_xyz_step;
  int i = (int)f;
  f -= i;
  xyz[0] = (1-f)*spectrum_x[i] + f*spectrum_x[i+1];
  xyz[1] = (1-f)*spectrum_y[i] + f*spectrum_y[i+1];
  xyz[2] = (1-f)*spectrum_z[i] + f*spectrum_z[i+1];
}

static const float spectrum_s_white[] =
{
  1.0000, 1.0000, 0.9999, 0.9993, 0.9992, 0.9998, 1.0000, 1.0000, 1.0000, 1.0000
};
static const float spectrum_s_cyan[] =
{
  0.9710, 0.9426, 1.0007, 1.0007, 1.0007, 1.0007, 0.1564, 0.0000, 0.0000, 0.0000
};
static const float spectrum_s_magenta[] =
{
  1.0000, 1.0000, 0.9685, 0.2229, 0.0000, 0.0458, 0.8369, 1.0000, 1.0000, 0.9959 
};
static const float spectrum_s_yellow[] =
{
  0.0001, 0.0000, 0.1088, 0.6651, 1.0000, 1.0000, 0.9996, 0.9586, 0.9685, 0.9840 
};
static const float spectrum_s_red[] =
{
  0.1012, 0.0515, 0.0000, 0.0000, 0.0000, 0.0000, 0.8325, 1.0149, 1.0149, 1.0149 
};
static const float spectrum_s_green[] =
{
  0.0000, 0.0000, 0.0273, 0.7937, 1.0000, 0.9418, 0.1719, 0.0000, 0.0000, 0.0025 
};
static const float spectrum_s_blue[] =
{
  1.0000, 1.0000, 0.8916, 0.3323, 0.0000, 0.0000, 0.0003, 0.0369, 0.0483, 0.0496
};

static const float spectrum_ungamma[] =
{
  0.000000,0.080560,0.110395,0.132737,0.151280,0.167429,0.181896,0.195098,0.207307,0.218708,0.229437,0.239595,0.249261,0.258497,0.267353,0.275870,0.284083,0.292020,0.299707,0.307164,0.314409,0.321460,0.328330,0.335031,0.341576,0.347973,0.354232,0.360361,0.366368,0.372258,0.378039,0.383716,0.389294,0.394777,0.400170,0.405478,0.410703,0.415850,0.420922,0.425921,0.430851,0.435714,0.440513,0.445250,0.449927,0.454547,0.459110,0.463620,0.468078,0.472486,0.476845,0.481157,0.485422,0.489643,0.493821,0.497957,0.502052,0.506108,0.510125,0.514104,0.518046,0.521953,0.525825,0.529664,0.533469,0.537242,0.540983,0.544693,0.548374,0.552025,0.555647,0.559241,0.562808,0.566348,0.569861,0.573349,0.576811,0.580248,0.583662,0.587051,0.590417,0.593760,0.597081,0.600380,0.603657,0.606913,0.610149,0.613363,0.616558,0.619733,0.622888,0.626025,0.629142,0.632242,0.635323,0.638386,0.641432,0.644460,0.647472,0.650467,0.653445,0.656407,0.659353,0.662284,0.665199,0.668099,0.670983,0.673853,0.676709,0.679549,0.682376,0.685189,0.687988,0.690773,0.693545,0.696304,0.699050,0.701783,0.704503,0.707210,0.709905,0.712588,0.715259,0.717918,0.720565,0.723201,0.725825,0.728438,0.731039,0.733630,0.736210,0.738778,0.741336,0.743884,0.746421,0.748948,0.751465,0.753971,0.756468,0.758955,0.761432,0.763899,0.766357,0.768805,0.771244,0.773674,0.776095,0.778507,0.780910,0.783303,0.785689,0.788065,0.790433,0.792793,0.795144,0.797487,0.799821,0.802148,0.804466,0.806776,0.809079,0.811373,0.813660,0.815939,0.818211,0.820475,0.822732,0.824981,0.827222,0.829457,0.831684,0.833905,0.836118,0.838324,0.840523,0.842715,0.844901,0.847079,0.849251,0.851417,0.853576,0.855728,0.857874,0.860013,0.862146,0.864273,0.866393,0.868507,0.870615,0.872717,0.874813,0.876903,0.878987,0.881065,0.883137,0.885203,0.887264,0.889318,0.891368,0.893411,0.895449,0.897481,0.899508,0.901529,0.903545,0.905556,0.907561,0.909561,0.911556,0.913545,0.915529,0.917509,0.919483,0.921451,0.923415,0.925374,0.927328,0.929277,0.931221,0.933160,0.935095,0.937025,0.938949,0.940870,0.942785,0.944696,0.946602,0.948503,0.950401,0.952293,0.954181,0.956064,0.957944,0.959818,0.961688,0.963554,0.965416,0.967273,0.969126,0.970975,0.972820,0.974660,0.976496,0.978328,0.980156,0.981980,0.983800,0.985616,0.987428,0.989235,0.991039,0.992839,0.994635,0.996427,0.998216,1.000000
};

static inline float spectrum_rgb_to_p(const float lambda, const float *rgb)
{
  // smits-like smooth metamer construction, basis function match cie rgb backwards.
  float p = 0.0f;
  // const float corr[] = {0.467044, 0.368873, 0.351969};
  // float red = rgb[0]*corr[0], green = rgb[1]*corr[1], blue = rgb[2]*corr[2];
  float red = rgb[0], green = rgb[1], blue = rgb[2];
  float cyan = 0, yellow = 0, magenta = 0;
  const float white = fminf(red, fminf(green, blue));
  red -= white; green -= white; blue -= white;
  const int bin = (int)(10.0f*(lambda - 380.0f)/(720.0 - 380.0));
  float ww = spectrum_s_white[bin];
  p += white * ww;
  if(green > 0 && blue > 0)
  {
    cyan = fminf(green, blue);
    green -= cyan; blue -= cyan;
  }
  else if(red > 0 && blue > 0)
  {
    magenta = fminf(red, blue);
    red -= magenta; blue -= magenta;
  }
  else if(red > 0 && green > 0)
  {
    yellow = fminf(red, green);
    red -= yellow; green -= yellow;
  }

  float cw = spectrum_s_cyan[bin];
  float mw = spectrum_s_magenta[bin];
  float yw = spectrum_s_yellow[bin];
  p += cw*cyan;
  p += mw*magenta;
  p += yw*yellow;
  float rw = spectrum_s_red[bin];
  float gw = spectrum_s_green[bin];
  float bw = spectrum_s_blue[bin];
  p += red * rw;
  p += green * gw;
  p += blue * bw;
  return p;
}

static inline float spectrum_tex_to_p(const float lambda, const unsigned char *rgb)
{
  float frgb[3] = {spectrum_ungamma[rgb[0]], spectrum_ungamma[rgb[1]], spectrum_ungamma[rgb[2]]};
  return spectrum_rgb_to_p(lambda, frgb);
}

static inline void spectrum_p_to_xyz(const float lambda, const float p, float *xyz)
{
  const float corr[] = {2.291406, 2.395276, 2.650796}; // matched to convert to and fro
  float b[3];
  spectrum_xyz(lambda, b);
  for(int k=0;k<3;k++) xyz[k] = b[k]*p*corr[k];
}

/* static inline void spectrum_p_to_cam(const float lambda, const float p, float *cam) */
/* { */
/*   float xyz[3]; */
/*   spectrum_p_to_xyz(lambda, p, xyz); */
/*   colorspace_xyz_to_cam(xyz, cam); */
/* } */

static inline void spectrum_p_to_rgb(const float lambda, const float p, float *rgb)
{
  float xyz[3];
  spectrum_p_to_xyz(lambda, p, xyz);
  spectrum_xyz_to_rgb(xyz, rgb);
}

// p = 1/(700-400)
static inline float spectrum_sample_lambda(const float rand, float *pdf)
{
  if(pdf) *pdf = 1.0f/(700.0f - 300.0f);
  return 400.0f + 300.0f*rand;
}

static inline float spectrum_lambda_pdf(const float lambda)
{
  return 1.0f/(700.0f - 400.0f);
}

#if 0
// p ~ lum
static inline float spectrum_sample_lambda(const float rand, float &p)
{

}

static inline void spectrum_print_info(FILE *fd)
{
  //fprintf(fd, "spectrum : smits-style reconstruction\n");
}
#endif

#endif
