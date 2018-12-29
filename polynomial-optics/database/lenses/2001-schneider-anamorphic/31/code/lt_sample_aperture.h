case schneider_anamorphic_2001_31mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
Eigen::Vector3f view(
  scene_x,
  scene_y,
  scene_z + camera->lens_outer_pupil_curvature_radius
);
raytrace_normalise(view);
int error = 0;
if(1 || view(2) >= camera->lens_field_of_view)
{
  const float eps = 1e-8;
  float sqr_err = 1e30, sqr_ap_err = 1e30;
  float prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(int k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    const float begin_x = x;
    const float begin_y = y;
    const float begin_dx = dx;
    const float begin_dy = dy;
    const float begin_lambda = lambda;
    const Eigen::Vector2f pred_ap(
       + 38.6869 *begin_dx + 0.623429 *begin_x + -15.5632 *begin_dx*lens_ipow(begin_dy, 2) + -10.2649 *lens_ipow(begin_dx, 3) + -7.18963e-05 *lens_ipow(begin_x, 3) + -1.96893e-05 *lens_ipow(begin_y, 4)*begin_dx + -1.59481e-06 *begin_x*lens_ipow(begin_y, 4) + -0.00121203 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.250188 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000748826 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3) + -5.62142e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -5.0424e-05 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2) + -1.23857e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -1.02029e-06 *lens_ipow(begin_x, 6)*begin_dx + -6.44904e-09 *lens_ipow(begin_x, 7) + -6.40073e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dy*begin_lambda + 0.00185366 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -9.86971e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dy*begin_lambda,
       + 37.2224 *begin_dy + 0.599597 *begin_y + 1.83247 *begin_dy*begin_lambda + 0.0442879 *begin_y*begin_lambda + -9.07413e-05 *lens_ipow(begin_y, 3) + -58.6984 *lens_ipow(begin_dy, 5) + -217.082 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -1.6474e-06 *lens_ipow(begin_x, 4)*begin_y + -2.10924e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -6.37569e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + -7.22385e-07 *lens_ipow(begin_y, 6)*begin_dy + -5.35111e-09 *lens_ipow(begin_y, 7) + 3.92133e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy + -9.74215e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -5.47593e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + -3.10257e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dx + 0.00476083 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -6.4367e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dx*begin_lambda
    );
    const Eigen::Vector2f delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 38.6869  + -15.5632 *lens_ipow(begin_dy, 2) + -30.7948 *lens_ipow(begin_dx, 2) + -1.96893e-05 *lens_ipow(begin_y, 4) + 0.250188 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.00224648 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -5.62142e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -0.000100848 *lens_ipow(begin_x, 5)*begin_dx + -1.02029e-06 *lens_ipow(begin_x, 6) + 0.00370733 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -31.1265 *begin_dx*begin_dy + -0.00242406 *lens_ipow(begin_x, 3)*begin_dy + 0.500376 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -6.40073e-07 *begin_x*lens_ipow(begin_y, 5)*begin_lambda + 0.00185366 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -9.86971e-07 *lens_ipow(begin_x, 5)*begin_y*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + -434.165 *begin_dx*lens_ipow(begin_dy, 3) + -1.27514e-05 *lens_ipow(begin_y, 5)*begin_dx + 3.92133e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dy + -3.10257e-07 *lens_ipow(begin_x, 5)*begin_y + 0.00476083 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -6.4367e-07 *begin_x*lens_ipow(begin_y, 5)*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 37.2224  + 1.83247 *begin_lambda + -293.492 *lens_ipow(begin_dy, 4) + -651.247 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.21849e-05 *lens_ipow(begin_y, 5)*begin_dy + -7.22385e-07 *lens_ipow(begin_y, 6) + 3.92133e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -5.47593e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 0.00952165 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda+0.0f;
    Eigen::Matrix2f invApJ;
    const float invdetap = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
    invApJ(0, 0) =  dx1_domega0(1, 1)*invdetap;
    invApJ(1, 1) =  dx1_domega0(0, 0)*invdetap;
    invApJ(0, 1) = -dx1_domega0(0, 1)*invdetap;
    invApJ(1, 0) = -dx1_domega0(1, 0)*invdetap;
    for(int i=0;i<2;i++)
    {
      dx += invApJ(0, i)*delta_ap[i];
      dy += invApJ(1, i)*delta_ap[i];
    }
    out(0) =  + 31.8082 *begin_dx + -1.23537 *begin_x + -9.91225 *begin_dx*lens_ipow(begin_dy, 2) + -15.471 *lens_ipow(begin_dx, 3) + -0.000205774 *begin_x*lens_ipow(begin_y, 2) + -0.0154073 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.000631676 *lens_ipow(begin_x, 4)*begin_dx + -7.10896e-06 *lens_ipow(begin_x, 5) + 0.000359243 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 4.80768e-06 *lens_ipow(begin_x, 5)*begin_lambda + 0.102008 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.34602e-05 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -0.000211805 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -4.21218e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -8.24076e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -5.7631e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -7.99923e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 0.0427392 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4)*begin_lambda;
    out(1) =  + 61.049 *begin_dy + -0.953977 *begin_y + 0.0510768 *begin_y*begin_lambda + -16.2447 *lens_ipow(begin_dy, 3) + -0.000313115 *lens_ipow(begin_x, 2)*begin_y + -364.164 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -3.66302e-06 *lens_ipow(begin_x, 4)*begin_y + -0.000534794 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_lambda + -0.0554581 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -1.12917e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + -1.58772e-08 *lens_ipow(begin_y, 7) + -1.68985e-06 *begin_x*lens_ipow(begin_y, 5)*begin_dx + -0.0168704 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -3.27484e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -5.47452e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -1.61274 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -2.93214e-06 *lens_ipow(begin_y, 6)*begin_dy*begin_lambda + 0.00891428 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda;
    out(2) =  + 0.294276 *begin_dx + -0.0432053 *begin_x + -0.0169962 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -3.88338e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -8.37588e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -7.80635e-08 *lens_ipow(begin_x, 5) + 9.1092e-08 *lens_ipow(begin_x, 5)*begin_lambda + -1.06519e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3) + -1.22962e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -2.53998e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -5.61965e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -6.91443e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -1.01356e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -8.82771e-09 *lens_ipow(begin_x, 5)*begin_y*begin_dy + -3.47763e-08 *lens_ipow(begin_x, 6)*begin_dx + -2.5112e-10 *lens_ipow(begin_x, 7) + -0.0104834 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -1.88293e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2)*begin_lambda;
    out(3) =  + -0.0162106 *begin_y + -4.06389e-05 *lens_ipow(begin_x, 2)*begin_dy + 4.69628e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -8.59992e-07 *lens_ipow(begin_y, 4)*begin_dy + 0.000664881 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -8.11642e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -8.73015e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + -8.42142e-11 *lens_ipow(begin_y, 7) + -4.9574e-07 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy + -1.1358e-08 *begin_x*lens_ipow(begin_y, 5)*begin_dx + -7.0029e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -2.68054e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -2.97391e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -3.66062e-11 *lens_ipow(begin_x, 6)*begin_y + 0.000145295 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 5.9445e-06 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 3) + -8.50769e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)*begin_lambda + -2.14786e-08 *lens_ipow(begin_y, 6)*begin_dy*begin_lambda;
    Eigen::Vector3f pred_out_cs_pos(0,0,0);
    Eigen::Vector3f pred_out_cs_dir(0,0,0);
    Eigen::Vector2f outpos(out(0), out(1));
    Eigen::Vector2f outdir(out(2), out(3));
    if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    Eigen::Vector3f view(
      scene_x - pred_out_cs_pos(0),
      scene_y - pred_out_cs_pos(1),
      scene_z - pred_out_cs_pos(2)
    );
    raytrace_normalise(view);
    Eigen::VectorXf out_new(5); out_new.setZero();
    Eigen::Vector2f out_new_pos(0,0);
    Eigen::Vector2f out_new_dir(0,0);
    if (camera->lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    out_new(0) = out_new_pos(0);
    out_new(1) = out_new_pos(1);
    out_new(2) = out_new_dir(0);
    out_new(3) = out_new_dir(1);
    const Eigen::Vector2f delta_out(out_new[2] - out[2], out_new[3] - out[3]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2f domega2_dx0;
    domega2_dx0(0, 0) =  + -0.0432053  + -0.0169962 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -7.76676e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -2.51276e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -3.90317e-07 *lens_ipow(begin_x, 4) + 4.5546e-07 *lens_ipow(begin_x, 4)*begin_lambda + -1.22962e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -5.07996e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.12393e-07 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -2.07433e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -3.04069e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -4.41386e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dy + -2.08658e-07 *lens_ipow(begin_x, 5)*begin_dx + -1.75784e-09 *lens_ipow(begin_x, 6) + -0.0209669 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -9.41463e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -7.76676e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -1.67518e-07 *lens_ipow(begin_x, 3)*begin_y + -4.26076e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -4.91846e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -7.61995e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -2.24786e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -2.07433e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + -4.05426e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -8.82771e-09 *lens_ipow(begin_x, 5)*begin_dy+0.0f;
    domega2_dx0(1, 0) =  + -8.12778e-05 *begin_x*begin_dy + 0.00132976 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -2.43493e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -4.9574e-07 *lens_ipow(begin_y, 4)*begin_dx*begin_dy + -1.1358e-08 *lens_ipow(begin_y, 5)*begin_dx + -1.40058e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -5.36108e-08 *begin_x*lens_ipow(begin_y, 4)*begin_dy + -5.94782e-10 *begin_x*lens_ipow(begin_y, 5) + -2.19637e-10 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.0162106  + 1.40888e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -3.43997e-06 *lens_ipow(begin_y, 3)*begin_dy + -8.11642e-07 *lens_ipow(begin_x, 3)*begin_dx + -4.36507e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -5.895e-10 *lens_ipow(begin_y, 6) + -1.98296e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -5.679e-08 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -2.10087e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -1.07222e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -1.48696e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -3.66062e-11 *lens_ipow(begin_x, 6) + 0.000435886 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 2.3778e-05 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 3) + -4.25384e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2)*begin_lambda + -1.28871e-07 *lens_ipow(begin_y, 5)*begin_dy*begin_lambda+0.0f;
    Eigen::Matrix2f invJ;
    const float invdet = 1.0f/(domega2_dx0(0, 0)*domega2_dx0(1, 1) - domega2_dx0(0, 1)*domega2_dx0(1, 0));
    invJ(0, 0) =  domega2_dx0(1, 1)*invdet;
    invJ(1, 1) =  domega2_dx0(0, 0)*invdet;
    invJ(0, 1) = -domega2_dx0(0, 1)*invdet;
    invJ(1, 0) = -domega2_dx0(1, 0)*invdet;
    for(int i=0;i<2;i++)
    {
      x += 0.72 * invJ(0, i) * delta_out[i];
      y += 0.72 * invJ(1, i) * delta_out[i];
    }
    if(sqr_err>prev_sqr_err) error |= 1;
    if(sqr_ap_err>prev_sqr_ap_err) error |= 2;
    if(out[0]!=out[0]) error |= 4;
    if(out[1]!=out[1]) error |= 8;
    // reset error code for first few iterations.
    if(k<10) error = 0;
  }
}
else
  error = 128;
if(out[0]*out[0]+out[1]*out[1] > camera->lens_outer_pupil_radius*camera->lens_outer_pupil_radius) error |= 16;
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.189975  + 0.360881 *begin_lambda + -0.244167 *lens_ipow(begin_lambda, 2) + -0.00183336 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00173719 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -7.34568e-05 *lens_ipow(begin_y, 3)*begin_dy + -0.036827 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00366526 *begin_x*begin_y*begin_dx*begin_dy + -0.00012353 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.00161881 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000104627 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -2.27292e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -4.06601e-09 *lens_ipow(begin_y, 6) + -4.96369e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 2) + -1.16706e-09 *lens_ipow(begin_y, 7)*begin_dy + -5.97833e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 2) + -1.94923e-09 *lens_ipow(begin_x, 7)*begin_dx + -1.58072e-11 *lens_ipow(begin_x, 8);
else
  out[4] = 0.0f;
} break;
