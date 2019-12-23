case angenieux_double_gauss_1953_100mm:
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
       + 51.0741 *begin_dx + 0.164957 *begin_x + 3.80311 *begin_dx*begin_lambda + -4.3292e-05 *lens_ipow(begin_y, 2) + 0.0746279 *begin_x*begin_lambda + -0.00255573 *begin_x*begin_dy,
       + 51.0449 *begin_dy + 0.172198 *begin_y + 3.92141 *begin_dy*begin_lambda + 0.0903945 *lens_ipow(begin_dy, 2) + 0.061443 *begin_y*begin_lambda + 0.00456087 *begin_y*begin_dy
    );
    const Eigen::Vector2f delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 51.0741  + 3.80311 *begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -0.00255573 *begin_x+0.0f;
    dx1_domega0(1, 0) = +0.0f;
    dx1_domega0(1, 1) =  + 51.0449  + 3.92141 *begin_lambda + 0.180789 *begin_dy + 0.00456087 *begin_y+0.0f;
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
    out(0) =  + 92.3584 *begin_dx + 0.0104136 *begin_y + -0.527274 *begin_x + 2.00056 *begin_dx*begin_lambda + -0.0168445 *begin_y*begin_lambda + 0.158455 *begin_x*begin_lambda;
    out(1) =  + 92.1357 *begin_dy + -0.515513 *begin_y + 2.51865 *begin_dy*begin_lambda + 0.138919 *lens_ipow(begin_dy, 2) + 0.137027 *begin_y*begin_lambda + 0.0074765 *begin_y*begin_dy;
    out(2) =  + -0.57236 *begin_dx + -7.10609e-06 *begin_y + -0.00663669 *begin_x + 0.00840292 *begin_dx*begin_lambda + 7.02599e-07 *lens_ipow(begin_y, 2) + -0.000887943 *begin_x*begin_lambda;
    out(3) =  + -0.564999 *begin_dy + -0.00678183 *begin_y + 0.00504171 *begin_dy*begin_lambda + -0.000737731 *begin_y*begin_lambda + -2.57503e-05 *begin_y*begin_dy + 8.41898e-07 *begin_x*begin_y;
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
    domega2_dx0(0, 0) =  + -0.00663669  + -0.000887943 *begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -7.10609e-06  + 1.4052e-06 *begin_y+0.0f;
    domega2_dx0(1, 0) =  + 8.41898e-07 *begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.00678183  + -0.000737731 *begin_lambda + -2.57503e-05 *begin_dy + 8.41898e-07 *begin_x+0.0f;
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
  out[4] =  + 0.330905  + 0.347233 *begin_lambda + -0.236711 *lens_ipow(begin_lambda, 2) + -0.0574053 *lens_ipow(begin_dy, 2) + -0.0610943 *lens_ipow(begin_dx, 2) + -0.000262871 *begin_x*begin_dx;
else
  out[4] = 0.0f;
} break;
