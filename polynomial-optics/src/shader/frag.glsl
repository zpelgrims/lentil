#version 450
uniform samplerCube cubemap;
uniform samplerCube minmaxdepthmap;
uniform float dist;
uniform float exposure;
uniform float apfac;

in data
{
  vec2 sensorPos;
};

layout(location = 0) out vec4 col;
#define FLT_MAX 1e10
#define M_PI 3.141592653589793238
const float lambda = 0.550f;

//------------------------------------------------------------------------------
//---init.h---------------------------------------------------------------------
const float lens_outer_pupil_radius = 26.000000; // scene facing radius in mm
const float lens_inner_pupil_radius = 11.000000; // sensor facing radius in mm
const float lens_length = 106.056999; // overall lens length in mm
const float lens_focal_length = 41.099998; // approximate lens focal length in mm (BFL)
const float lens_aperture_pos = 47.270996; // distance aperture -> outer pupil in mm
const float lens_aperture_housing_radius = 9.000000; // lens housing radius at the aperture
const float lens_outer_pupil_curvature_radius = 85.000000; // radius of curvature of the outer pupil
const float lens_field_of_view = -0.635824; // cosine of the approximate field of view assuming a 35mm image
//------------------------------------------------------------------------------

void lens_sphereToCs(vec2 inpos, vec2 indir, out vec3 outpos, out vec3 outdir, float sphereCenter, float sphereRad)
{
  vec3 normal = vec3(inpos/sphereRad, sqrt(max(0.0f, sphereRad*sphereRad-dot(inpos, inpos)))/abs(sphereRad));
  vec3 tempDir = vec3(indir, sqrt(max(0.0f, 1.0f - dot(indir, indir))));

  vec3 ex = normalize(vec3(normal.z, 0, -normal.x));
  vec3 ey = cross(normal, ex);

  outdir = tempDir.x * ex + tempDir.y * ey + tempDir.z * normal;
  outpos = vec3(inpos, normal.z * sphereRad + sphereCenter);
}

float lens_ipow(const float a, const int exp)
{
  float ret = 1;
  for(int i = 0; i < exp; i++)
    ret *= a;
  return ret;
}

float eval(vec4 sensor, out vec4 outer)
{
  const float x = sensor.x+dist*sensor.p;
  const float y = sensor.y+dist*sensor.q;
  const float dx = sensor.p;
  const float dy = sensor.q;
//------------------------------------------------------------------------------
//---pt_evaluate.h--------------------------------------------------------------
const float out_x =  + 7.65755 *dx + -1.1832 *x + -1.31699 *x*lambda + 59.0708 *dx*lens_ipow(dy, 2) + 30.2171 *lens_ipow(dx, 3) + 3.50868 *y*dx*dy + 0.0564045 *lens_ipow(y, 2)*dx + 1.89452 *x*lens_ipow(lambda, 2) + 1.82807 *x*lens_ipow(dy, 2) + 3.43431 *x*lens_ipow(dx, 2) + 0.100342 *x*y*dy + 0.00029391 *x*lens_ipow(y, 2) + 0.115854 *lens_ipow(x, 2)*dx + -88.0652 *dx*lens_ipow(dy, 2)*lambda + -86.3777 *lens_ipow(dx, 3)*lambda + -3.93513 *y*dx*dy*lambda + -0.0424592 *lens_ipow(y, 2)*dx*lambda + -0.890228 *x*lens_ipow(lambda, 3) + -2.10664 *x*lens_ipow(dy, 2)*lambda + -5.9415 *x*lens_ipow(dx, 2)*lambda + -0.0935049 *x*y*dy*lambda + -0.00131724 *x*lens_ipow(y, 2)*lambda + -0.134113 *lens_ipow(x, 2)*dx*lambda + -0.00131686 *lens_ipow(x, 3)*lambda + 1.96261 *dx*lens_ipow(lambda, 4) + 101.908 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + 526.482 *lens_ipow(dx, 5) + -0.00324482 *lens_ipow(y, 3)*dx*dy + 8.24306 *x*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 53.0155 *x*lens_ipow(dx, 4) + -0.00427981 *x*lens_ipow(y, 2)*lens_ipow(dx, 2) + -8.65588e-07 *x*lens_ipow(y, 4) + 0.224784 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2) + 2.16619 *lens_ipow(x, 2)*lens_ipow(dx, 3) + 0.00167101 *lens_ipow(x, 3)*lens_ipow(dy, 2) + 0.043197 *lens_ipow(x, 3)*lens_ipow(dx, 2) + 4.50713e-05 *lens_ipow(x, 3)*y*dy + -1.50302e-06 *lens_ipow(x, 3)*lens_ipow(y, 2) + 0.000517022 *lens_ipow(x, 4)*dx + 1.46418e-06 *lens_ipow(x, 5);
const float out_y =  + 7.71401 *dy + -1.18649 *y + -1.28968 *y*lambda + 23.65 *lens_ipow(dy, 3) + 55.3595 *lens_ipow(dx, 2)*dy + 1.83742 *y*lens_ipow(lambda, 2) + 3.19029 *y*lens_ipow(dy, 2) + 1.79376 *y*lens_ipow(dx, 2) + 0.114579 *lens_ipow(y, 2)*dy + 3.2819 *x*dx*dy + 0.0974623 *x*y*dx + 0.054054 *lens_ipow(x, 2)*dy + 0.00026074 *lens_ipow(x, 2)*y + -85.8523 *lens_ipow(dy, 3)*lambda + -84.6425 *lens_ipow(dx, 2)*dy*lambda + -0.857012 *y*lens_ipow(lambda, 3) + -5.87041 *y*lens_ipow(dy, 2)*lambda + -2.00812 *y*lens_ipow(dx, 2)*lambda + -0.132185 *lens_ipow(y, 2)*dy*lambda + -0.00127448 *lens_ipow(y, 3)*lambda + -3.79908 *x*dx*dy*lambda + -0.0898042 *x*y*dx*lambda + -0.0413686 *lens_ipow(x, 2)*dy*lambda + -0.00127413 *lens_ipow(x, 2)*y*lambda + 1.85364 *dy*lens_ipow(lambda, 4) + 627.658 *lens_ipow(dy, 5) + 306.009 *lens_ipow(dx, 2)*lens_ipow(dy, 3) + 60.702 *y*lens_ipow(dy, 4) + 12.5455 *y*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 2.37913 *lens_ipow(y, 2)*lens_ipow(dy, 3) + 0.155002 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + 0.0455115 *lens_ipow(y, 3)*lens_ipow(dy, 2) + 0.000515372 *lens_ipow(y, 4)*dy + 1.34923e-06 *lens_ipow(y, 5) + 10.99 *x*dx*lens_ipow(dy, 3) + 0.323482 *x*y*dx*lens_ipow(dy, 2) + 0.137806 *lens_ipow(x, 2)*lens_ipow(dy, 3) + -2.06752e-06 *lens_ipow(x, 2)*lens_ipow(y, 3) + -0.00311015 *lens_ipow(x, 3)*dx*dy + -8.95995e-07 *lens_ipow(x, 4)*y;
const float out_dx =  + -0.11972 *dx + -0.0841805 *x + -0.31001 *dx*lambda + 0.25011 *dx*lens_ipow(lambda, 2) + -1.21064 *lens_ipow(dx, 3) + 0.0274337 *y*dx*dy + 0.00106553 *lens_ipow(y, 2)*dx + 0.000689783 *x*lens_ipow(lambda, 2) + 0.00591154 *x*lens_ipow(dy, 2) + 0.0011196 *x*y*dy + 7.24425e-05 *x*lens_ipow(y, 2) + 0.00167348 *lens_ipow(x, 2)*dx + 8.25552e-05 *lens_ipow(x, 3) + -0.021617 *y*dx*dy*lambda + -0.138261 *x*lens_ipow(dx, 2)*lambda + -0.0027825 *lens_ipow(x, 2)*dx*lambda + -1.78927e-05 *lens_ipow(x, 3)*lambda + -1.75932 *lens_ipow(dx, 3)*lens_ipow(lambda, 2) + 48.7615 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + 39.4427 *lens_ipow(dx, 5) + 0.177335 *y*dx*lens_ipow(dy, 3) + 2.05324 *y*lens_ipow(dx, 3)*dy + -0.00017805 *lens_ipow(y, 2)*dx*lens_ipow(lambda, 2) + 0.00804357 *lens_ipow(y, 2)*dx*lens_ipow(dy, 2) + 0.0240432 *lens_ipow(y, 2)*lens_ipow(dx, 3) + 2.97933 *x*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 3.91679 *x*lens_ipow(dx, 4) + 0.12038 *x*y*lens_ipow(dx, 2)*dy + 0.00120845 *x*lens_ipow(y, 2)*lens_ipow(dx, 2) + -2.85641e-06 *x*lens_ipow(y, 3)*dy + -9.26783e-08 *x*lens_ipow(y, 4) + 0.0598417 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2) + 0.157138 *lens_ipow(x, 2)*lens_ipow(dx, 3) + 0.00229961 *lens_ipow(x, 2)*y*dx*dy + 2.13803e-05 *lens_ipow(x, 2)*lens_ipow(y, 2)*dx + 0.000360894 *lens_ipow(x, 3)*lens_ipow(dy, 2) + 0.00302415 *lens_ipow(x, 3)*lens_ipow(dx, 2) + 1.21214e-05 *lens_ipow(x, 3)*y*dy + 2.69545e-05 *lens_ipow(x, 4)*dx + 4.18319e-08 *lens_ipow(x, 5);
const float out_dy =  + -0.149474 *dy + -0.0853286 *y + -0.297205 *dy*lambda + 0.00209808 *y*lambda + 0.292254 *dy*lens_ipow(lambda, 2) + 1.52805 *lens_ipow(dx, 2)*dy + 0.0923354 *y*lens_ipow(dy, 2) + 0.0384629 *y*lens_ipow(dx, 2) + 0.00359313 *lens_ipow(y, 2)*dy + 9.60037e-05 *lens_ipow(y, 3) + 0.0857599 *x*dx*dy + 0.00241961 *x*y*dx + 0.00155766 *lens_ipow(x, 2)*dy + 0.000110044 *lens_ipow(x, 2)*y + -0.206933 *y*lens_ipow(dy, 2)*lambda + -0.00430763 *lens_ipow(y, 2)*dy*lambda + -2.9279e-05 *lens_ipow(y, 3)*lambda + -2.71552 *lens_ipow(dy, 3)*lens_ipow(lambda, 2) + 27.3815 *lens_ipow(dy, 5) + -2.91598 *lens_ipow(dx, 2)*dy*lens_ipow(lambda, 2) + 2.73438 *y*lens_ipow(dy, 4) + -0.0631532 *y*lens_ipow(dx, 2)*lens_ipow(lambda, 2) + 0.173095 *y*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 0.109727 *lens_ipow(y, 2)*lens_ipow(dy, 3) + 0.00591124 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + 0.00204676 *lens_ipow(y, 3)*lens_ipow(dy, 2) + 1.67152e-05 *lens_ipow(y, 4)*dy + -0.131866 *x*dx*dy*lens_ipow(lambda, 2) + 0.144512 *x*dx*lens_ipow(dy, 3) + -0.00263452 *x*y*dx*lens_ipow(lambda, 2) + 0.0070474 *x*y*dx*lens_ipow(dy, 2) + -4.84999e-06 *x*lens_ipow(y, 3)*dx + -0.00133901 *lens_ipow(x, 2)*dy*lens_ipow(lambda, 2) + 0.00502056 *lens_ipow(x, 2)*lens_ipow(dy, 3) + 0.00407626 *lens_ipow(x, 2)*lens_ipow(dx, 2)*dy + -2.39111e-05 *lens_ipow(x, 2)*y*lens_ipow(lambda, 2) + -5.8513e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)*dy + -1.75871e-07 *lens_ipow(x, 2)*lens_ipow(y, 3) + -4.11905e-06 *lens_ipow(x, 3)*y*dx + -6.94948e-08 *lens_ipow(x, 4)*y;
const float out_transmittance =  + 0.293094  + 0.000140112 *x + 0.414358 *lens_ipow(lambda, 2) + -0.074388 *lens_ipow(dx, 2) + 0.0042754 *y*dy + -0.00233179 *lens_ipow(y, 2) + -0.395252 *lens_ipow(lambda, 3) + 0.140873 *lens_ipow(dx, 2)*lambda + 0.00966733 *y*dx*lambda + 0.0172711 *lens_ipow(y, 2)*lambda + 0.00409554 *lens_ipow(x, 2)*lambda + -0.00015258 *lens_ipow(x, 2)*dx + -7.98567e-06 *lens_ipow(x, 3) + -0.0141394 *y*lens_ipow(dx, 3) + -0.0322932 *lens_ipow(y, 2)*lens_ipow(lambda, 2) + -0.000102973 *lens_ipow(y, 3)*dx + -6.7576e-06 *lens_ipow(y, 4) + 0.0131585 *x*dx*lens_ipow(lambda, 2) + 6.47608e-05 *x*lens_ipow(y, 2)*dx + -0.00807678 *lens_ipow(x, 2)*lens_ipow(lambda, 2) + -6.73571e-05 *lens_ipow(x, 2)*y*dy + -1.30923e-05 *lens_ipow(x, 2)*lens_ipow(y, 2) + 1.15894e-06 *lens_ipow(x, 3)*y + -6.94708e-06 *lens_ipow(x, 4) + -0.0245649 *y*dx*lens_ipow(lambda, 3) + 0.0196026 *lens_ipow(y, 2)*lens_ipow(lambda, 3) + -0.00214761 *lens_ipow(y, 2)*lens_ipow(dy, 2)*lambda + -0.000134736 *lens_ipow(y, 3)*dy*lambda + 0.000178412 *lens_ipow(y, 3)*dx*lambda + 2.84901e-07 *lens_ipow(y, 4)*dx + -0.00357422 *x*y*dx*dy*lambda + -0.000235883 *x*lens_ipow(y, 2)*dx*lambda + 0.0051794 *lens_ipow(x, 2)*lens_ipow(lambda, 3) + -0.00275832 *lens_ipow(x, 2)*lens_ipow(dx, 2)*lambda + -1.83398e-06 *lens_ipow(x, 2)*y*lens_ipow(lambda, 2) + -0.00015008 *lens_ipow(x, 3)*dx*lambda + -1.88901e-06 *lens_ipow(x, 3)*y*lambda + 2.29745e-08 *lens_ipow(x, 3)*lens_ipow(y, 2) + 1.74642e-06 *lens_ipow(x, 4)*dx + 6.04957e-08 *lens_ipow(x, 5);
//------------------------------------------------------------------------------
  outer = vec4(out_x, out_y, out_dx, out_dy);
  return out_transmittance;
}

void sample_ap(inout vec4 sensor, inout vec4 aperture)
{
  float x = sensor.x, y = sensor.y, dx = sensor.z, dy = sensor.w;
  float out_x = aperture.x, out_y = aperture.y, out_dx = aperture.z, out_dy = aperture.w;
//------------------------------------------------------------------------------
//---pt_sample_aperture.h-------------------------------------------------------
float pred_x;
float pred_y;
float pred_dx;
float pred_dy;
float sqr_err = FLT_MAX;
for(int k=0;k<5&&sqr_err > 1e-4f;k++)
{
  const float begin_x = x + dist * dx;
  const float begin_y = y + dist * dy;
  const float begin_dx = dx;
  const float begin_dy = dy;
  const float begin_lambda = lambda;
  pred_x =  + 32.0536 *begin_dx + 0.435597 *begin_x + -0.623539 *begin_dx*begin_lambda + 0.572096 *begin_dx*lens_ipow(begin_lambda, 2) + 20.6975 *begin_dx*lens_ipow(begin_dy, 2) + 16.4465 *lens_ipow(begin_dx, 3) + 1.61835 *begin_y*begin_dx*begin_dy + 0.0159344 *lens_ipow(begin_y, 2)*begin_dx + 0.320136 *begin_x*lens_ipow(begin_dy, 2) + 1.68578 *begin_x*lens_ipow(begin_dx, 2) + 0.0173836 *begin_x*begin_y*begin_dy + 0.0287439 *lens_ipow(begin_x, 2)*begin_dx + -0.0726402 *begin_y*begin_dx*begin_dy*begin_lambda + -0.00119378 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.000102486 *lens_ipow(begin_x, 3)*begin_lambda + -8.92203 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 211.372 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 166.687 *lens_ipow(begin_dx, 5) + 8.07434 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.0730394 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.000783386 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.84714e-05 *lens_ipow(begin_y, 4)*begin_dx + -0.6217 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 11.9743 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 15.9905 *begin_x*lens_ipow(begin_dx, 4) + 0.484737 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.00392653 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.82053e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -6.66191e-07 *begin_x*lens_ipow(begin_y, 4) + -0.0136322 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 0.224935 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.631761 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.00861872 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 3.11643e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.0014672 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.0119537 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 3.39161e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -6.71729e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 8.46765e-05 *lens_ipow(begin_x, 4)*begin_dx + -1.08348e-07 *lens_ipow(begin_x, 5);
  pred_y =  + 31.8949 *begin_dy + 0.435776 *begin_y + 18.8968 *lens_ipow(begin_dy, 3) + 23.4518 *lens_ipow(begin_dx, 2)*begin_dy + 1.88682 *begin_y*lens_ipow(begin_dy, 2) + 0.388206 *begin_y*lens_ipow(begin_dx, 2) + 0.033226 *lens_ipow(begin_y, 2)*begin_dy + 1.64537 *begin_x*begin_dx*begin_dy + 0.0186206 *begin_x*begin_y*begin_dx + 0.0162683 *lens_ipow(begin_x, 2)*begin_dy + -10.6828 *lens_ipow(begin_dy, 3)*begin_lambda + -5.29801 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.809737 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.129894 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.0182638 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000123458 *lens_ipow(begin_y, 3)*begin_lambda + -0.001939 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 177.826 *lens_ipow(begin_dy, 5) + 221.031 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 17.3506 *begin_y*lens_ipow(begin_dy, 4) + 12.6722 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.697915 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.240864 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.0135848 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00157442 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 0.000105303 *lens_ipow(begin_y, 4)*begin_dy + -0.240436 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 8.50023 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.00442636 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.516794 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00939296 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 3.9397e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.0774885 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.00426163 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 3.95515e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -6.17909e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.000787916 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -2.87234e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -1.84951e-05 *lens_ipow(begin_x, 4)*begin_dy + -6.79443e-07 *lens_ipow(begin_x, 4)*begin_y;
  pred_dx =  + -0.678179 *begin_dx + -0.0407908 *begin_x + -0.0496813 *begin_dx*begin_lambda + -0.000500683 *begin_x*begin_lambda + -0.535661 *begin_dx*lens_ipow(begin_dy, 2) + 0.0279509 *begin_x*lens_ipow(begin_dy, 2) + 0.0870726 *begin_x*lens_ipow(begin_dx, 2) + 0.00125199 *begin_x*begin_y*begin_dy + 0.00289427 *lens_ipow(begin_x, 2)*begin_dx + 1.28702e-05 *lens_ipow(begin_x, 3) + -0.747607 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -3.89733 *lens_ipow(begin_dx, 3)*begin_lambda + 0.0755574 *begin_y*begin_dx*begin_dy*begin_lambda + -0.0219681 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + -0.249931 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -1.16149e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.00792602 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -7.33406e-05 *lens_ipow(begin_x, 3)*begin_lambda + 2.6776 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 5.25782 *lens_ipow(begin_dx, 5) + -0.103655 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.0498699 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0459433 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.000402427 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -5.33972e-07 *lens_ipow(begin_y, 4)*begin_dx + 0.159351 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.132039 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.56727 *begin_x*lens_ipow(begin_dx, 4) + -0.00096947 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + 4.16141e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 6.46305e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.7361e-08 *begin_x*lens_ipow(begin_y, 4) + 0.00551416 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -0.00360848 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0294104 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 5.34022e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 0.000772781 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -4.20328e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 8.63508e-06 *lens_ipow(begin_x, 4)*begin_dx + 1.87559e-08 *lens_ipow(begin_x, 5);
  pred_dy =  + -0.59517 *begin_dy + -0.039287 *begin_y + -0.325208 *begin_dy*begin_lambda + -0.00517472 *begin_y*begin_lambda + 0.234667 *begin_dy*lens_ipow(begin_lambda, 2) + -1.3352 *lens_ipow(begin_dy, 3) + -1.16895 *lens_ipow(begin_dx, 2)*begin_dy + 0.00383653 *begin_y*lens_ipow(begin_lambda, 2) + 0.00964946 *begin_y*lens_ipow(begin_dx, 2) + 0.000332014 *lens_ipow(begin_y, 2)*begin_dy + -1.03451e-05 *lens_ipow(begin_y, 3) + 0.000727064 *begin_x*begin_y*begin_dx + -0.000213539 *lens_ipow(begin_x, 2)*begin_dy + -8.58346e-06 *lens_ipow(begin_x, 2)*begin_y + -0.564996 *lens_ipow(begin_dy, 3)*begin_lambda + -0.048185 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.00127276 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -1.01832e-05 *lens_ipow(begin_y, 3)*begin_lambda + 9.89407 *lens_ipow(begin_dy, 5) + 11.291 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 1.12246 *begin_y*lens_ipow(begin_dy, 4) + 0.811923 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.0553959 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.0207152 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.00138373 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.000202594 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 1.57747e-05 *lens_ipow(begin_y, 4)*begin_dy + 5.26255e-08 *lens_ipow(begin_y, 5) + 0.462599 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.0550999 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.0401522 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00103345 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 8.41208e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00570617 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.00049963 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 5.11082e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + 1.08328e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 4.53666e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -6.34453e-07 *lens_ipow(begin_x, 4)*begin_dy + -3.01941e-08 *lens_ipow(begin_x, 4)*begin_y;
  float dx1_domega0[2][2];
  dx1_domega0[0][0] =  + 32.0536  + -0.623539 *begin_lambda + 0.572096 *lens_ipow(begin_lambda, 2) + 20.6975 *lens_ipow(begin_dy, 2) + 49.3396 *lens_ipow(begin_dx, 2) + 1.61835 *begin_y*begin_dy + 0.0159344 *lens_ipow(begin_y, 2) + 3.37155 *begin_x*begin_dx + 0.0287439 *lens_ipow(begin_x, 2) + -0.0726402 *begin_y*begin_dy*begin_lambda + -0.00119378 *lens_ipow(begin_y, 2)*begin_lambda + -26.7661 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 634.115 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 833.433 *lens_ipow(begin_dx, 4) + 24.223 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.219118 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.000783386 *lens_ipow(begin_y, 3)*begin_dy + -1.84714e-05 *lens_ipow(begin_y, 4) + -1.2434 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + 23.9486 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 63.9622 *begin_x*lens_ipow(begin_dx, 3) + 0.969474 *begin_x*begin_y*begin_dx*begin_dy + 0.00785306 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.0136322 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 0.224935 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 1.89528 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.00861872 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 3.11643e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.0239073 *lens_ipow(begin_x, 3)*begin_dx + 8.46765e-05 *lens_ipow(begin_x, 4)+0.0f;
  dx1_domega0[0][1] =  + 41.3949 *begin_dx*begin_dy + 1.61835 *begin_y*begin_dx + 0.640271 *begin_x*begin_dy + 0.0173836 *begin_x*begin_y + -0.0726402 *begin_y*begin_dx*begin_lambda + 422.743 *lens_ipow(begin_dx, 3)*begin_dy + 8.07434 *begin_y*lens_ipow(begin_dx, 3) + -0.000783386 *lens_ipow(begin_y, 3)*begin_dx + 23.9486 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.484737 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -2.82053e-05 *begin_x*lens_ipow(begin_y, 3) + 0.449869 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.00861872 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.00293439 *lens_ipow(begin_x, 3)*begin_dy + 3.39161e-05 *lens_ipow(begin_x, 3)*begin_y+0.0f;
  dx1_domega0[1][0] =  + 46.9036 *begin_dx*begin_dy + 0.776413 *begin_y*begin_dx + 1.64537 *begin_x*begin_dy + 0.0186206 *begin_x*begin_y + -10.596 *begin_dx*begin_dy*begin_lambda + -0.259788 *begin_y*begin_dx*begin_lambda + 442.063 *begin_dx*lens_ipow(begin_dy, 3) + 25.3444 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.481728 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.00314884 *lens_ipow(begin_y, 3)*begin_dx + -0.240436 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 8.50023 *begin_x*lens_ipow(begin_dy, 3) + -0.00442636 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 0.516794 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.00939296 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 3.9397e-05 *begin_x*lens_ipow(begin_y, 3) + -0.000787916 *lens_ipow(begin_x, 3)*begin_dy + -2.87234e-05 *lens_ipow(begin_x, 3)*begin_y+0.0f;
  dx1_domega0[1][1] =  + 31.8949  + 56.6904 *lens_ipow(begin_dy, 2) + 23.4518 *lens_ipow(begin_dx, 2) + 3.77364 *begin_y*begin_dy + 0.033226 *lens_ipow(begin_y, 2) + 1.64537 *begin_x*begin_dx + 0.0162683 *lens_ipow(begin_x, 2) + -32.0483 *lens_ipow(begin_dy, 2)*begin_lambda + -5.29801 *lens_ipow(begin_dx, 2)*begin_lambda + -1.61947 *begin_y*begin_dy*begin_lambda + -0.0182638 *lens_ipow(begin_y, 2)*begin_lambda + -0.001939 *lens_ipow(begin_x, 2)*begin_lambda + 889.128 *lens_ipow(begin_dy, 4) + 663.094 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 69.4025 *begin_y*lens_ipow(begin_dy, 3) + 25.3444 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 2.09375 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.240864 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.0271697 *lens_ipow(begin_y, 3)*begin_dy + 0.000105303 *lens_ipow(begin_y, 4) + -0.240436 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + 25.5007 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 1.03359 *begin_x*begin_y*begin_dx*begin_dy + 0.00939296 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.232465 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.00852327 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 3.95515e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.000787916 *lens_ipow(begin_x, 3)*begin_dx + -1.84951e-05 *lens_ipow(begin_x, 4)+0.0f;
  float invJ[2][2];
  const float invdet = 1.0f/(dx1_domega0[0][0]*dx1_domega0[1][1] - dx1_domega0[0][1]*dx1_domega0[1][0]);
  invJ[0][0] =  dx1_domega0[1][1]*invdet;
  invJ[1][1] =  dx1_domega0[0][0]*invdet;
  invJ[0][1] = -dx1_domega0[0][1]*invdet;
  invJ[1][0] = -dx1_domega0[1][0]*invdet;
  const float dx1[2] = {out_x - pred_x, out_y - pred_y};
  for(int i=0;i<2;i++)
  {
    dx += invJ[0][i]*dx1[i];
    dy += invJ[1][i]*dx1[i];
  }
  sqr_err = dx1[0]*dx1[0] + dx1[1]*dx1[1];
}
out_dx = pred_dx;
out_dy = pred_dy;
//------------------------------------------------------------------------------
  sensor = vec4(x, y, dx, dy);
  aperture = vec4(out_x, out_y, out_dx, out_dy);
}

vec4 traceRay(vec3 position, vec3 direction, float transmittance)
{
  vec4 ret = vec4(0,0,0,1);
  vec3 pos = position;
  vec3 dir = direction;

  float near = 2*lens_outer_pupil_curvature_radius;
  float far = 20000;
  float t[12];
  t[0] = (-pos.x-near)/dir.x;
  t[1] = (-pos.x+near)/dir.x;
  t[2] = (-pos.y-near)/dir.y;
  t[3] = (-pos.y+near)/dir.y;
  t[4] = (-pos.z-near)/dir.z;
  t[5] = (-pos.z+near)/dir.z;

  t[6] = (-pos.x-far)/dir.x;
  t[7] = (-pos.x+far)/dir.x;
  t[8] = (-pos.y-far)/dir.y;
  t[9] = (-pos.y+far)/dir.y;
  t[10] = (-pos.z-far)/dir.z;
  t[11] = (-pos.z+far)/dir.z;

  int mint = 0;
  for(int i = 1; i < 6; i++)
    if((t[mint] < 0 || t[mint] > t[i]) && t[i] > 0)
      mint = i;

  int maxt = mint;
  for(int i = 0; i < 6; i++)
    if((t[maxt+6] < 0 || t[maxt+6] > t[i+6]) && t[i+6] > 0)
      maxt = i;

  int faceIdx = mint>>1;
  int faceIdx2 = maxt>>1;
  int sig = sign(mint&1)*2-1;
  int sig2 = sign(maxt&1)*2-1;

  vec3 r0 = (pos + t[mint] * dir)/(near*2)+0.5;
  r0[faceIdx] = 0;
  vec3 rmax = (pos + t[mint+6] * dir)/(far*2)+0.5;
  rmax[faceIdx] = sig;
  vec3 rd = rmax - r0;
  rd = normalize(rd);

  vec3 lookupOff = vec3(-1);
  lookupOff[faceIdx] = sig;

  vec3 lookupFac = vec3(2);
  lookupFac[faceIdx] = 0;

  vec3 r02 = (pos + t[maxt] * dir)/(near*2)+0.5;
  r02[faceIdx2] = 0;
  vec3 rmax2 = (pos + t[maxt+6] * dir)/(far*2)+0.5;
  rmax2[faceIdx2] = sig2;
  vec3 rd2 = rmax2 - r02;
  rd2 = normalize(rd2);

  vec3 lookupOff2 = vec3(-1);
  lookupOff2[faceIdx2] = sig2;

  vec3 lookupFac2 = vec3(2);
  lookupFac2[faceIdx2] = 0;

  const int maxLod = 9;
  int lod = maxLod;
  vec4 color = vec4(1);
  // factor for size of one texel (1 = whole image in 1 texel, 
  // 1/2 = 2 texels for whole image, ...) texelSize = 1/(2^(10-lod))
  int numIterations = 0;

  for(int i = 0; i < 20; i++,numIterations++)
  {
    if(r0[(faceIdx+1)%3] > 1 || r0[(faceIdx+2)%3] > 1 || r0[(faceIdx+1)%3] < 0 || r0[(faceIdx+2)%3] < 0)
    {
      if(faceIdx == faceIdx2)
        break;
      float prevDepth = r0[faceIdx];
      faceIdx = faceIdx2;
      sig = sig2;
      lookupOff = lookupOff2;
      lookupFac = lookupFac2;
      rd = rd2;
      r0 = r02;
      float t = (prevDepth - abs(r0[faceIdx])) / abs(rd[faceIdx]);
      r0 += t * rd;

      lod = maxLod;
    }

    float texelSize = 1.0f/(1<<(9-lod));

    vec2 minmaxDepth = (textureLod(minmaxdepthmap, r0 * lookupFac + lookupOff, lod).rg)/(far);
    //TODO dependency on dimensions of ray bundle
    color.rgb = textureLod(cubemap, r0 * lookupFac + lookupOff, 0).rgb;
    color.rgb = textureLod(cubemap, r0 * lookupFac + lookupOff, 0).rgb;
    float dist = -1;

    // if the current position is before the min-plane, choose max step size s.t. we reach the min-plane,
    // if current ray position is between min and max depth, look at higher resolution depth (i.e. lod = lod-1)
    // otherwise (current depth greater than the maximum) go to next texel but choose lower resolution for next iteration
    // in any case the maximum step size is also limited by the texel size.
    if(abs(r0[faceIdx]) < minmaxDepth.r)
      dist = (minmaxDepth.r - abs(r0[faceIdx])) / abs(rd[faceIdx]);
    else if(abs(r0[faceIdx]) < minmaxDepth.g)
    {
      if(minmaxDepth.g - minmaxDepth.r < 1e-2)
        break;
      lod = max(lod-1, 0);numIterations--;
      continue;
    }
    else
    {
      lod = min(lod+1, maxLod);numIterations--;
      continue;
    }

    vec2 inTexelPos = mod(vec2(r0[(faceIdx+1)%3], r0[(faceIdx+2)%3]), texelSize);
    vec2 inTexelDir = vec2(rd[(faceIdx+1)%3], rd[(faceIdx+2)%3]);

    vec2 texelBorder = vec2(sign(inTexelDir.x)*texelSize, sign(inTexelDir.y)*texelSize);
    texelBorder = clamp(texelBorder, 0, texelSize);
    vec2 texelIntersect = (texelBorder-inTexelPos) / (inTexelDir);
    dist = min(texelIntersect.x, min(dist, texelIntersect.y));

    r0 += dist*(1+1e-7) * rd;
  }
  color.rgb *= transmittance;
  ret += color;
  return ret;
}

vec2 lens_sample_aperture(vec2 r, const float radius, const int blades)
{
  const int tri = int(r.x*blades);
  // rescale:
  r.x = r.x*blades - tri;

  // sample triangle:
  vec2 bary = vec2(1.0f-r.y, r.y)*sqrt(r.x);

  vec2 p1, p2;
  p1 = vec2(sin(2.0f*M_PI/blades * (tri+1)), cos(2.0f*M_PI/blades * (tri+1)));
  p2 = vec2(sin(2.0f*M_PI/blades * tri), cos(2.0f*M_PI/blades * tri));

  return radius * (bary.x * p1 + bary.y * p2);
}

void main()
{    
  vec4 center = vec4(sensorPos, -sensorPos/(lens_length-lens_aperture_pos+dist));
  vec3 p, d;
  float t;
  vec4 color;

  for(int i = 0; i < 144; i++)
  {
    vec4 ray = center;
    //sample aperture (as disk)
    vec4 aperture = vec4(0);
    vec2 s = fract(vec2(1,89)*i/float(144));
    aperture.xy = lens_sample_aperture(s, lens_aperture_housing_radius*apfac, 5);
    sample_ap(ray, aperture);
    vec4 outer;
    float t = eval(ray, outer);
    lens_sphereToCs(outer.xy, outer.zw, p, d, 0, lens_outer_pupil_curvature_radius);
    if(length(outer.xy) > lens_outer_pupil_radius)
      t = 0;
    color += traceRay(p, d, t);
  }
  col = color/color.a/exposure;
}
