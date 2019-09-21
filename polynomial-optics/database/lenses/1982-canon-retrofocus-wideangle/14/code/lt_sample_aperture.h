case canon__retrofocus_wideangle__1982__14mm:
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
       + 30.6704 *begin_dx + 0.615218 *begin_x + -0.0905149 *begin_x*begin_lambda + -0.375113 *begin_dx*begin_lambda + 2.78314 *begin_y*begin_dx*begin_dy + 0.0867423 *begin_x*begin_y*begin_dy + 0.139254 *lens_ipow(begin_x, 2)*begin_dx + 25.7829 *lens_ipow(begin_dx, 3) + 0.0614983 *begin_x*lens_ipow(begin_lambda, 2) + 27.8055 *begin_dx*lens_ipow(begin_dy, 2) + 0.00137595 *begin_x*lens_ipow(begin_y, 2) + 0.00142908 *lens_ipow(begin_x, 3) + 1.11093 *begin_x*lens_ipow(begin_dy, 2) + 3.81506 *begin_x*lens_ipow(begin_dx, 2) + 0.0484956 *lens_ipow(begin_y, 2)*begin_dx + -0.000230485 *lens_ipow(begin_x, 3)*begin_lambda + -0.0179786 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -0.301572 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.000326963 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.148063 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 0.000212904 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 0.00939915 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 1.64013e-06 *lens_ipow(begin_x, 5)*begin_lambda + 7.07194e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -1.71042e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 39.2573 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + 4.17497e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 2) + 1.20478e-08 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*begin_lambda,
       + 0.611816 *begin_y + 30.6644 *begin_dy + -0.372275 *begin_dy*begin_lambda + -0.0760021 *begin_y*begin_lambda + 1.09382 *begin_y*lens_ipow(begin_dx, 2) + 0.140663 *lens_ipow(begin_y, 2)*begin_dy + 3.95291 *begin_y*lens_ipow(begin_dy, 2) + 2.7734 *begin_x*begin_dx*begin_dy + 0.086057 *begin_x*begin_y*begin_dx + 27.7602 *lens_ipow(begin_dx, 2)*begin_dy + 0.0490308 *begin_y*lens_ipow(begin_lambda, 2) + 0.00135816 *lens_ipow(begin_x, 2)*begin_y + 0.00143467 *lens_ipow(begin_y, 3) + 0.0483889 *lens_ipow(begin_x, 2)*begin_dy + 26.0794 *lens_ipow(begin_dy, 3) + -0.622678 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.027974 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000317849 *lens_ipow(begin_y, 3)*begin_lambda + 0.000463158 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.0286159 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 2.92368e-06 *lens_ipow(begin_y, 5)*begin_lambda + 9.91681 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.840873 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.00601163 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 9.60607e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -5.08146e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 3.73959e-06 *lens_ipow(begin_x, 5)*begin_y*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 5.5858e-08 *lens_ipow(begin_x, 6)*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 30.6704  + -0.375113 *begin_lambda + 2.78314 *begin_y*begin_dy + 0.139254 *lens_ipow(begin_x, 2) + 77.3487 *lens_ipow(begin_dx, 2) + 27.8055 *lens_ipow(begin_dy, 2) + 7.63012 *begin_x*begin_dx + 0.0484956 *lens_ipow(begin_y, 2) + -0.0179786 *lens_ipow(begin_x, 2)*begin_lambda + -0.603145 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.000326963 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.444188 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 0.000212904 *lens_ipow(begin_x, 4)*begin_lambda + 0.0187983 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -1.71042e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + 78.5146 *begin_x*begin_dx*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + 2.40956e-08 *begin_x*lens_ipow(begin_y, 6)*begin_dx*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + 2.78314 *begin_y*begin_dx + 0.0867423 *begin_x*begin_y + 55.6109 *begin_dx*begin_dy + 2.22185 *begin_x*begin_dy + -0.000326963 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 7.07194e-06 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + -1.71042e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 2) + 157.029 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 0) =  + 2.18764 *begin_y*begin_dx + 2.7734 *begin_x*begin_dy + 0.086057 *begin_x*begin_y + 55.5204 *begin_dx*begin_dy + 0.0120233 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + -5.08146e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dy + 3.73959e-06 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 1) =  + 30.6644  + -0.372275 *begin_lambda + 0.140663 *lens_ipow(begin_y, 2) + 7.90582 *begin_y*begin_dy + 2.7734 *begin_x*begin_dx + 27.7602 *lens_ipow(begin_dx, 2) + 0.0483889 *lens_ipow(begin_x, 2) + 78.2382 *lens_ipow(begin_dy, 2) + -1.24536 *begin_y*begin_dy*begin_lambda + -0.027974 *lens_ipow(begin_y, 2)*begin_lambda + 0.000463158 *lens_ipow(begin_y, 4)*begin_lambda + 0.0572317 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 39.6672 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 2.52262 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.0120233 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -5.08146e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx + 7.47918e-06 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 1.11716e-07 *lens_ipow(begin_x, 6)*begin_y*begin_dy*lens_ipow(begin_lambda, 2)+0.0f;
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
    out(0) =  + 13.6643 *begin_dx + -1.65808 *begin_x + -0.363089 *begin_x*begin_lambda + 1.35431 *begin_y*begin_dx*begin_dy + 0.0708303 *begin_x*begin_y*begin_dy + 0.127716 *lens_ipow(begin_x, 2)*begin_dx + 23.2357 *lens_ipow(begin_dx, 3) + 0.231819 *begin_x*lens_ipow(begin_lambda, 2) + 23.6367 *begin_dx*lens_ipow(begin_dy, 2) + 0.00364284 *begin_x*lens_ipow(begin_y, 2) + 0.00368265 *lens_ipow(begin_x, 3) + 0.934148 *begin_x*lens_ipow(begin_dy, 2) + 2.30731 *begin_x*lens_ipow(begin_dx, 2) + -0.00601454 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.298888 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -5.16512e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.209985 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000102248 *lens_ipow(begin_x, 4)*begin_dx + -1.7002e-05 *lens_ipow(begin_y, 4)*begin_dx + -3.30604e-06 *lens_ipow(begin_x, 5) + 0.00646073 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -3.23374e-06 *begin_x*lens_ipow(begin_y, 4) + -8.32709e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -0.56209 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 0.190672 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.400994 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.00773579 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 0.34233 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 3);
    out(1) =  + -1.73789 *begin_y + 13.7447 *begin_dy + -0.0975007 *begin_y*begin_lambda + 1.04234 *begin_y*lens_ipow(begin_dx, 2) + 0.139687 *lens_ipow(begin_y, 2)*begin_dy + 2.64583 *begin_y*lens_ipow(begin_dy, 2) + 1.63598 *begin_x*begin_dx*begin_dy + 0.0732121 *begin_x*begin_y*begin_dx + 27.3518 *lens_ipow(begin_dx, 2)*begin_dy + 0.00371322 *lens_ipow(begin_x, 2)*begin_y + 0.00393782 *lens_ipow(begin_y, 3) + 0.0532805 *lens_ipow(begin_x, 2)*begin_dy + 49.48 *lens_ipow(begin_dy, 3)*begin_lambda + -5.38528e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -6.10285e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -7.1818e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -3.17431e-06 *lens_ipow(begin_x, 4)*begin_y + 0.173997 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.00801688 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + -9.43856e-06 *lens_ipow(begin_y, 5)*begin_lambda + -3.10115 *begin_dy*lens_ipow(begin_lambda, 5) + 288.371 *lens_ipow(begin_dx, 4)*begin_dy*lens_ipow(begin_lambda, 2) + -0.000601034 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 2) + 6.9132e-06 *lens_ipow(begin_x, 5)*begin_dx*begin_dy*begin_lambda + 1.03751e-08 *lens_ipow(begin_y, 7)*lens_ipow(begin_lambda, 2) + 0.0495299 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 2) + -7.4987e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 7.26336e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7);
    out(2) =  + -0.392667 *begin_dx + -0.0252026 *begin_x + 0.0117613 *begin_x*begin_lambda + -0.00721868 *begin_dx*begin_lambda + 0.00729413 *begin_y*begin_dx*begin_dy + -0.000779865 *lens_ipow(begin_x, 2)*begin_dx + 0.422921 *lens_ipow(begin_dx, 3) + -0.00810304 *begin_x*lens_ipow(begin_lambda, 2) + 0.419655 *begin_dx*lens_ipow(begin_dy, 2) + -1.28879e-05 *begin_x*lens_ipow(begin_y, 2) + -0.000114027 *lens_ipow(begin_y, 2)*begin_dx + 7.74353e-05 *lens_ipow(begin_x, 3)*begin_lambda + -0.00373863 *begin_x*begin_y*begin_dy*begin_lambda + -0.00561975 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 9.8187e-07 *lens_ipow(begin_y, 4)*begin_dx + -0.116022 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.000149539 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + -4.51533e-08 *lens_ipow(begin_x, 5) + 4.48443e-05 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.000446303 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 0.00690297 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00420238 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 9.29423e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + -9.59854e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 3.30648e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2) + -1.03612e-11 *lens_ipow(begin_x, 7)*begin_y*begin_dy + 2.57444e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 3) + -2.46961e-09 *lens_ipow(begin_x, 7)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2);
    out(3) =  + -0.0250603 *begin_y + -0.396508 *begin_dy + 0.0111308 *begin_y*begin_lambda + 0.00803064 *begin_x*begin_dx*begin_dy + 0.576234 *lens_ipow(begin_dx, 2)*begin_dy + -0.00741492 *begin_y*lens_ipow(begin_lambda, 2) + 3.9068e-05 *lens_ipow(begin_x, 2)*begin_y + 1.21666e-05 *lens_ipow(begin_y, 3) + -0.000467346 *lens_ipow(begin_x, 2)*begin_dy + 0.417951 *lens_ipow(begin_dy, 3) + -0.0089164 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.00472189 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -3.41241e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00897309 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -1.44361e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -2.71178e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -4.74949e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -1.30174e-07 *lens_ipow(begin_x, 4)*begin_y + -4.21851e-08 *lens_ipow(begin_y, 5) + -2.42178e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -0.00551441 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 2.94163e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -1.20495e-08 *lens_ipow(begin_x, 5)*begin_y*begin_dx + 1.00619e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -4.67344e-07 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 2) + -1.66392e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_dx + 2.32864e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 3) + 1.54692e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7);
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
    domega2_dx0(0, 0) =  + -0.0252026  + 0.0117613 *begin_lambda + -0.00155973 *begin_x*begin_dx + -0.00810304 *lens_ipow(begin_lambda, 2) + -1.28879e-05 *lens_ipow(begin_y, 2) + 0.000232306 *lens_ipow(begin_x, 2)*begin_lambda + -0.00373863 *begin_y*begin_dy*begin_lambda + -0.00561975 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000448618 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + -2.25766e-07 *lens_ipow(begin_x, 4) + -0.000446303 *begin_y*lens_ipow(begin_dy, 3) + 0.00690297 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00420238 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 0.000278827 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + -4.79927e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 1.65324e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -7.25281e-11 *lens_ipow(begin_x, 6)*begin_y*begin_dy + 1.54466e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 3) + -1.72873e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(0, 1) =  + 0.00729413 *begin_dx*begin_dy + -2.57759e-05 *begin_x*begin_y + -0.000228055 *begin_y*begin_dx + -0.00373863 *begin_x*begin_dy*begin_lambda + -0.00561975 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 3.92748e-06 *lens_ipow(begin_y, 3)*begin_dx + -0.116022 *lens_ipow(begin_dx, 3)*begin_dy + 0.000134533 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.000446303 *begin_x*lens_ipow(begin_dy, 3) + 0.00690297 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.00420238 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -1.91971e-10 *lens_ipow(begin_x, 5)*begin_y + -1.03612e-11 *lens_ipow(begin_x, 7)*begin_dy+0.0f;
    domega2_dx0(1, 0) =  + 0.00803064 *begin_dx*begin_dy + 7.8136e-05 *begin_x*begin_y + -0.000934691 *begin_x*begin_dy + -3.41241e-06 *lens_ipow(begin_y, 3)*begin_dx + -2.88722e-07 *begin_x*lens_ipow(begin_y, 3) + -8.13535e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -5.20697e-07 *lens_ipow(begin_x, 3)*begin_y + -4.84357e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -6.02475e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 2.01239e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.86938e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2) + -8.31961e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx + 6.18768e-15 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 7)+0.0f;
    domega2_dx0(1, 1) =  + -0.0250603  + 0.0111308 *begin_lambda + -0.00741492 *lens_ipow(begin_lambda, 2) + 3.9068e-05 *lens_ipow(begin_x, 2) + 3.64998e-05 *lens_ipow(begin_y, 2) + -0.0089164 *lens_ipow(begin_dx, 2)*begin_lambda + -0.00944379 *begin_y*begin_dy*begin_lambda + -1.02372e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.0179462 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -4.33083e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.71178e-06 *lens_ipow(begin_x, 3)*begin_dx + -0.000142485 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -1.30174e-07 *lens_ipow(begin_x, 4) + -2.10926e-07 *lens_ipow(begin_y, 4) + -4.84357e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.0110288 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 1.47082e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -1.20495e-08 *lens_ipow(begin_x, 5)*begin_dx + 2.01239e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -4.67344e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -4.99177e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx + 1.39718e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3) + 1.08284e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6)+0.0f;
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
  out[4] =  + 1.08028 *begin_lambda + -1.83212e-05 *lens_ipow(begin_y, 2) + -1.21147e-05 *lens_ipow(begin_x, 2) + -1.80749 *lens_ipow(begin_lambda, 2) + -0.00293391 *begin_y*begin_dy*begin_lambda + -0.00175543 *begin_x*begin_dx*begin_lambda + -0.0775133 *lens_ipow(begin_dy, 2)*begin_lambda + 1.14512 *lens_ipow(begin_lambda, 3) + -2.92643 *lens_ipow(begin_dx, 4) + -0.0721319 *begin_x*lens_ipow(begin_dx, 3) + -4.8756 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0490404 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0471919 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -1.06684e-07 *lens_ipow(begin_x, 4) + -0.000882115 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -1.15816e-07 *lens_ipow(begin_y, 4)*begin_lambda + -4.25061e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -0.197156 *lens_ipow(begin_lambda, 6) + -46.414 *lens_ipow(begin_dy, 6) + -0.0108687 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -1.4354 *begin_y*lens_ipow(begin_dy, 5) + -8.83701e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*begin_lambda + -28.8213 *lens_ipow(begin_dx, 8) + -777.51 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4)*begin_lambda + -0.00252577 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -1.62677e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 5) + -0.0509131 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)*begin_lambda + -1551.36 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 8)*begin_lambda;
else
  out[4] = 0.0f;
} break;
