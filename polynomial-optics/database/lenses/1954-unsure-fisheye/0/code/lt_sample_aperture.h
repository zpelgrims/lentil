case unsure_fisheye_1954_0mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
Eigen::Vector3d view(
  scene_x,
  scene_y,
  scene_z + camera->lens_outer_pupil_curvature_radius
);
raytrace_normalise(view);
int error = 0;
if(1 || view(2) >= camera->lens_field_of_view)
{
  const double eps = 1e-8;
  double sqr_err = 1e30, sqr_ap_err = 1e30;
  double prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(int k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    const double begin_x = x;
    const double begin_y = y;
    const double begin_dx = dx;
    const double begin_dy = dy;
    const double begin_lambda = lambda;
    const Eigen::Vector2d pred_ap(
       + 0.707004 *begin_x + 23.4208 *begin_dx + -0.00188551 *begin_x*lens_ipow(begin_y, 2) + -0.00208898 *lens_ipow(begin_x, 3) + 0.776572 *begin_dx*lens_ipow(begin_lambda, 2) + -0.201269 *begin_x*begin_y*begin_dy + -6.30137 *begin_x*lens_ipow(begin_dx, 2) + -0.19824 *lens_ipow(begin_x, 2)*begin_dx + -6.72922 *begin_x*lens_ipow(begin_dy, 2) + 1.56629e-06 *lens_ipow(begin_x, 5) + 0.0108101 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 6.92983e-07 *lens_ipow(begin_x, 5)*begin_lambda + -0.000156886 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 6.6599e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dy + 2.46488e-06 *lens_ipow(begin_x, 5)*begin_y*begin_dy + 1.09629e-06 *lens_ipow(begin_x, 6)*begin_dx,
       + 22.3736 *begin_dy + 0.682822 *begin_y + -0.146057 *begin_x*begin_y*begin_dx + -3.16666 *begin_y*lens_ipow(begin_dx, 2) + -0.0015248 *lens_ipow(begin_x, 2)*begin_y + -0.00154583 *lens_ipow(begin_y, 3) + -5.31451 *begin_y*lens_ipow(begin_dy, 2) + -0.159127 *lens_ipow(begin_y, 2)*begin_dy + 90.0535 *lens_ipow(begin_dx, 2)*begin_dy + -0.995533 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000149752 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000110497 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 8.61306e-07 *lens_ipow(begin_y, 6)*begin_dy + 2.51578e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 2.34229e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + 6.82711e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dx
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 23.4208  + 0.776572 *lens_ipow(begin_lambda, 2) + -12.6027 *begin_x*begin_dx + -0.19824 *lens_ipow(begin_x, 2) + -0.000313773 *begin_x*lens_ipow(begin_y, 4)*begin_dx + 1.09629e-06 *lens_ipow(begin_x, 6)+0.0f;
    dx1_domega0(0, 1) =  + -0.201269 *begin_x*begin_y + -13.4584 *begin_x*begin_dy + 0.0216202 *lens_ipow(begin_x, 3)*begin_dy*begin_lambda + 6.6599e-07 *begin_x*lens_ipow(begin_y, 5) + 2.46488e-06 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    dx1_domega0(1, 0) =  + -0.146057 *begin_x*begin_y + -6.33332 *begin_y*begin_dx + 180.107 *begin_dx*begin_dy + 2.34229e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 6.82711e-07 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    dx1_domega0(1, 1) =  + 22.3736  + -10.629 *begin_y*begin_dy + -0.159127 *lens_ipow(begin_y, 2) + 90.0535 *lens_ipow(begin_dx, 2) + -1.99107 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.000149752 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -0.000110497 *lens_ipow(begin_y, 4)*begin_lambda + 8.61306e-07 *lens_ipow(begin_y, 6) + 2.51578e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)+0.0f;
    Eigen::Matrix2d invApJ;
    const double invdetap = 1.0f/(dx1_domega0(0, 0)*dx1_domega0(1, 1) - dx1_domega0(0, 1)*dx1_domega0(1, 0));
    invApJ(0, 0) =  dx1_domega0(1, 1)*invdetap;
    invApJ(1, 1) =  dx1_domega0(0, 0)*invdetap;
    invApJ(0, 1) = -dx1_domega0(0, 1)*invdetap;
    invApJ(1, 0) = -dx1_domega0(1, 0)*invdetap;
    for(int i=0;i<2;i++)
    {
      dx += invApJ(0, i)*delta_ap[i];
      dy += invApJ(1, i)*delta_ap[i];
    }
    out(0) =  + -11.6852 *begin_x + -529.432 *begin_dx + 180.333 *begin_y*begin_dx*begin_dy + 0.178531 *begin_x*lens_ipow(begin_y, 2) + 0.187638 *lens_ipow(begin_x, 3) + 22.7111 *begin_x*begin_y*begin_dy + 649.91 *begin_x*lens_ipow(begin_dx, 2) + 18.885 *lens_ipow(begin_x, 2)*begin_dx + 612.707 *begin_x*lens_ipow(begin_dy, 2) + -1.55767e+06 *lens_ipow(begin_dx, 5) + -36531.5 *begin_x*lens_ipow(begin_dx, 4) + 317.126 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.03296e-06 *lens_ipow(begin_x, 7) + -7374.79 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -11200.9 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -1.16116 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3);
    out(1) =  + -405.674 *begin_dy + -8.57411 *begin_y + 17.7367 *begin_x*begin_y*begin_dx + 0.145181 *lens_ipow(begin_x, 2)*begin_y + 0.10792 *lens_ipow(begin_y, 3) + 5.1906 *lens_ipow(begin_y, 2)*begin_dy + -27961.4 *lens_ipow(begin_dx, 2)*begin_dy + 0.0353506 *lens_ipow(begin_y, 4)*begin_dy + 2.24324 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -1.1705 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -5.81469e+08 *lens_ipow(begin_dy, 7) + -1.91601e+07 *begin_y*lens_ipow(begin_dy, 6) + 6648.46 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + 86.8057 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 3) + 0.345681 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -4636.94 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4);
    out(2) =  + -0.633003 *begin_x + -29.5345 *begin_dx + -2.11206 *begin_dx*begin_lambda + 6.32727 *begin_y*begin_dx*begin_dy + 0.00993621 *begin_x*lens_ipow(begin_y, 2) + -1098.99 *lens_ipow(begin_dx, 3) + 0.0114465 *lens_ipow(begin_x, 3) + 1.22154 *begin_x*begin_y*begin_dy + 0.939326 *lens_ipow(begin_x, 2)*begin_dx + 31.4923 *begin_x*lens_ipow(begin_dy, 2) + -1.24403e-05 *lens_ipow(begin_x, 5) + 0.00105657 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 2238.84 *begin_x*lens_ipow(begin_dy, 6) + -187.875 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 3.69995 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0201752 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3);
    out(3) =  + -36.2774 *begin_dy + -0.734093 *begin_y + 1.53653 *begin_x*begin_y*begin_dx + 42.8914 *begin_y*lens_ipow(begin_dx, 2) + 0.0135638 *lens_ipow(begin_x, 2)*begin_y + 0.0123033 *lens_ipow(begin_y, 3) + 36.9782 *begin_y*lens_ipow(begin_dy, 2) + 1.29866 *lens_ipow(begin_y, 2)*begin_dy + -2.78772e-05 *lens_ipow(begin_x, 4)*begin_y + -47686.3 *lens_ipow(begin_dy, 5) + -971.99 *begin_y*lens_ipow(begin_dy, 4) + -0.00221515 *lens_ipow(begin_x, 3)*begin_y*begin_dx + 0.000640578 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -7.20226e-08 *lens_ipow(begin_y, 7) + -0.07405 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + -1.4349e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5);
    Eigen::Vector3d pred_out_cs_pos(0,0,0);
    Eigen::Vector3d pred_out_cs_dir(0,0,0);
    Eigen::Vector2d outpos(out(0), out(1));
    Eigen::Vector2d outdir(out(2), out(3));
    if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    Eigen::Vector3d view(
      scene_x - pred_out_cs_pos(0),
      scene_y - pred_out_cs_pos(1),
      scene_z - pred_out_cs_pos(2)
    );
    raytrace_normalise(view);
    Eigen::VectorXd out_new(5); out_new.setZero();
    Eigen::Vector2d out_new_pos(0,0);
    Eigen::Vector2d out_new_dir(0,0);
    if (camera->lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
    else if (camera->lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
    out_new(0) = out_new_pos(0);
    out_new(1) = out_new_pos(1);
    out_new(2) = out_new_dir(0);
    out_new(3) = out_new_dir(1);
    const Eigen::Vector2d delta_out(out_new[2] - out[2], out_new[3] - out[3]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2d domega2_dx0;
    domega2_dx0(0, 0) =  + -0.633003  + 0.00993621 *lens_ipow(begin_y, 2) + 0.0343395 *lens_ipow(begin_x, 2) + 1.22154 *begin_y*begin_dy + 1.87865 *begin_x*begin_dx + 31.4923 *lens_ipow(begin_dy, 2) + -6.22016e-05 *lens_ipow(begin_x, 4) + 0.00316971 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 2238.84 *lens_ipow(begin_dy, 6) + -187.875 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 11.0998 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0807007 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)+0.0f;
    domega2_dx0(0, 1) =  + 6.32727 *begin_dx*begin_dy + 0.0198724 *begin_x*begin_y + 1.22154 *begin_x*begin_dy + 0.00105657 *lens_ipow(begin_x, 3)*begin_dy + -187.875 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 0) =  + 1.53653 *begin_y*begin_dx + 0.0271277 *begin_x*begin_y + -0.000111509 *lens_ipow(begin_x, 3)*begin_y + -0.00664545 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -0.07405 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + -2.8698e-07 *begin_x*lens_ipow(begin_y, 5)+0.0f;
    domega2_dx0(1, 1) =  + -0.734093  + 1.53653 *begin_x*begin_dx + 42.8914 *lens_ipow(begin_dx, 2) + 0.0135638 *lens_ipow(begin_x, 2) + 0.0369098 *lens_ipow(begin_y, 2) + 36.9782 *lens_ipow(begin_dy, 2) + 2.59732 *begin_y*begin_dy + -2.78772e-05 *lens_ipow(begin_x, 4) + -971.99 *lens_ipow(begin_dy, 4) + -0.00221515 *lens_ipow(begin_x, 3)*begin_dx + 0.00320289 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -5.04158e-07 *lens_ipow(begin_y, 6) + -0.22215 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -7.17449e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)+0.0f;
    Eigen::Matrix2d invJ;
    const double invdet = 1.0f/(domega2_dx0(0, 0)*domega2_dx0(1, 1) - domega2_dx0(0, 1)*domega2_dx0(1, 0));
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
const double begin_x = x;
const double begin_y = y;
const double begin_dx = dx;
const double begin_dy = dy;
const double begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.850771 *begin_lambda + -0.000792038 *lens_ipow(begin_y, 2) + -1.18757 *lens_ipow(begin_lambda, 2) + 0.604749 *lens_ipow(begin_lambda, 3) + -0.00185699 *lens_ipow(begin_x, 2)*begin_lambda + -0.0923117 *begin_x*begin_dx*begin_lambda + -0.176171 *begin_y*begin_dy*begin_lambda + -8.41205 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -3.35892e-06 *lens_ipow(begin_x, 4) + -0.000140256 *lens_ipow(begin_x, 3)*begin_dx + -1.18386e-05 *lens_ipow(begin_y, 4)*begin_lambda + -0.00619874 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 2.47729e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 2) + -1.49275e-06 *lens_ipow(begin_y, 5)*begin_dy + -5.25631e-07 *lens_ipow(begin_x, 5)*begin_dx + -0.000586477 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 3);
else
  out[4] = 0.0f;
} break;
