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
       + 53.5533 *begin_dx + 0.155085 *begin_x + 13.4794 *begin_dx*begin_lambda + 0.267639 *begin_x*begin_lambda + -9.22232 *begin_dx*lens_ipow(begin_lambda, 2) + -30.0121 *begin_dx*lens_ipow(begin_dy, 2) + -29.9178 *lens_ipow(begin_dx, 3) + -0.0761147 *begin_y*begin_dx*begin_dy + -0.185046 *begin_x*lens_ipow(begin_lambda, 2) + -0.159593 *begin_x*lens_ipow(begin_dy, 2) + -0.180895 *begin_x*lens_ipow(begin_dx, 2) + -0.000110295 *begin_x*lens_ipow(begin_y, 2) + -0.000107312 *lens_ipow(begin_x, 3) + 0.228388 *begin_x*lens_ipow(begin_dy, 4),
       + 53.5515 *begin_dy + 0.157591 *begin_y + 13.4912 *begin_dy*begin_lambda + 0.257999 *begin_y*begin_lambda + -9.22587 *begin_dy*lens_ipow(begin_lambda, 2) + -29.9556 *lens_ipow(begin_dy, 3) + -30.0292 *lens_ipow(begin_dx, 2)*begin_dy + -0.176885 *begin_y*lens_ipow(begin_lambda, 2) + -0.180369 *begin_y*lens_ipow(begin_dy, 2) + -0.155302 *begin_y*lens_ipow(begin_dx, 2) + -0.00010683 *lens_ipow(begin_y, 3) + -0.0759737 *begin_x*begin_dx*begin_dy + -0.000110405 *lens_ipow(begin_x, 2)*begin_y + 0.210394 *begin_y*lens_ipow(begin_dx, 4)
    );
    const Eigen::Vector2f delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2f dx1_domega0;
    dx1_domega0(0, 0) =  + 53.5533  + 13.4794 *begin_lambda + -9.22232 *lens_ipow(begin_lambda, 2) + -30.0121 *lens_ipow(begin_dy, 2) + -89.7535 *lens_ipow(begin_dx, 2) + -0.0761147 *begin_y*begin_dy + -0.361791 *begin_x*begin_dx+0.0f;
    dx1_domega0(0, 1) =  + -60.0241 *begin_dx*begin_dy + -0.0761147 *begin_y*begin_dx + -0.319187 *begin_x*begin_dy + 0.913554 *begin_x*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 0) =  + -60.0584 *begin_dx*begin_dy + -0.310603 *begin_y*begin_dx + -0.0759737 *begin_x*begin_dy + 0.841578 *begin_y*lens_ipow(begin_dx, 3)+0.0f;
    dx1_domega0(1, 1) =  + 53.5515  + 13.4912 *begin_lambda + -9.22587 *lens_ipow(begin_lambda, 2) + -89.8669 *lens_ipow(begin_dy, 2) + -30.0292 *lens_ipow(begin_dx, 2) + -0.360738 *begin_y*begin_dy + -0.0759737 *begin_x*begin_dx+0.0f;
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
    out(0) =  + 99.6253 *begin_dx + -0.612819 *begin_x + 0.591016 *begin_x*begin_lambda + -38.4082 *begin_dx*lens_ipow(begin_dy, 2) + -38.4111 *lens_ipow(begin_dx, 3) + 0.1689 *begin_y*begin_dx*begin_dy + -0.407523 *begin_x*lens_ipow(begin_lambda, 2) + 0.29064 *begin_x*lens_ipow(begin_dy, 2) + 0.460483 *begin_x*lens_ipow(begin_dx, 2) + 0.00558501 *begin_x*begin_y*begin_dy + -0.000247535 *begin_x*lens_ipow(begin_y, 2) + 0.00902978 *lens_ipow(begin_x, 2)*begin_dx + -0.000248469 *lens_ipow(begin_x, 3) + 0.00623469 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda;
    out(1) =  + 99.6623 *begin_dy + -0.612999 *begin_y + 0.57796 *begin_y*begin_lambda + -38.5652 *lens_ipow(begin_dy, 3) + -38.4398 *lens_ipow(begin_dx, 2)*begin_dy + -0.383126 *begin_y*lens_ipow(begin_lambda, 2) + 0.458346 *begin_y*lens_ipow(begin_dy, 2) + 0.288674 *begin_y*lens_ipow(begin_dx, 2) + -0.000247733 *lens_ipow(begin_y, 3) + 0.165021 *begin_x*begin_dx*begin_dy + 0.0055095 *begin_x*begin_y*begin_dx + 0.00332464 *lens_ipow(begin_x, 2)*begin_dy + -0.000249142 *lens_ipow(begin_x, 2)*begin_y + 0.0161747 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda;
    out(2) =  + -0.6051 *begin_dx + -0.00629425 *begin_x + -0.00359449 *begin_x*begin_lambda + 0.235336 *lens_ipow(begin_dx, 3) + 0.00254506 *begin_x*lens_ipow(begin_lambda, 2) + -0.00116404 *begin_x*lens_ipow(begin_dy, 2) + -2.17887e-05 *begin_x*begin_y*begin_dy + 1.68674e-06 *begin_x*lens_ipow(begin_y, 2) + -3.36135e-05 *lens_ipow(begin_x, 2)*begin_dx + 1.78266e-06 *lens_ipow(begin_x, 3) + 0.508466 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.397889 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.000113727 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 0.000352479 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda;
    out(3) =  + -0.611318 *begin_dy + -0.00702857 *begin_y + 0.0105566 *begin_dy*begin_lambda + -0.000818453 *begin_y*begin_lambda + 0.238585 *lens_ipow(begin_dy, 3) + 0.336579 *lens_ipow(begin_dx, 2)*begin_dy + -3.02439e-05 *lens_ipow(begin_y, 2)*begin_dy + 1.74466e-06 *lens_ipow(begin_y, 3) + 0.0019257 *begin_x*begin_dx*begin_dy + -2.32218e-05 *begin_x*begin_y*begin_dx + 1.74817e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0200532 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.00017072 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.0241728 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3);
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
    domega2_dx0(0, 0) =  + -0.00629425  + -0.00359449 *begin_lambda + 0.00254506 *lens_ipow(begin_lambda, 2) + -0.00116404 *lens_ipow(begin_dy, 2) + -2.17887e-05 *begin_y*begin_dy + 1.68674e-06 *lens_ipow(begin_y, 2) + -6.72271e-05 *begin_x*begin_dx + 5.34799e-06 *lens_ipow(begin_x, 2) + 0.000704959 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -2.17887e-05 *begin_x*begin_dy + 3.37347e-06 *begin_x*begin_y + 0.000227454 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.0019257 *begin_dx*begin_dy + -2.32218e-05 *begin_y*begin_dx + 3.49634e-06 *begin_x*begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.00702857  + -0.000818453 *begin_lambda + -6.04879e-05 *begin_y*begin_dy + 5.23398e-06 *lens_ipow(begin_y, 2) + -2.32218e-05 *begin_x*begin_dx + 1.74817e-06 *lens_ipow(begin_x, 2) + -0.0200532 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000341439 *begin_y*lens_ipow(begin_dy, 3) + 0.0241728 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3)+0.0f;
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
  out[4] =  + 0.240858  + 0.845399 *begin_lambda + -1.1589 *lens_ipow(begin_lambda, 2) + 0.560249 *lens_ipow(begin_lambda, 3) + -0.250334 *lens_ipow(begin_dy, 4) + -0.46332 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.250803 *lens_ipow(begin_dx, 4) + -0.00502705 *begin_y*lens_ipow(begin_dy, 3) + -0.00400387 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000122994 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00401476 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00498555 *begin_x*lens_ipow(begin_dx, 3) + -0.000123777 *begin_x*begin_y*begin_dx*begin_dy + -0.000120986 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2);
else
  out[4] = 0.0f;
} break;
