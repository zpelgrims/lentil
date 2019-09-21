case cooke__speed_panchro__1920__18mm:
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
       + 12.9766 *begin_dx + 0.662733 *begin_x + 0.0176878 *begin_x*begin_lambda + 0.322163 *begin_dx*begin_lambda + -0.362789 *begin_y*begin_dx*begin_dy + -0.00364467 *lens_ipow(begin_x, 2)*begin_dx + -10.1041 *lens_ipow(begin_dx, 3) + -9.68762 *begin_dx*lens_ipow(begin_dy, 2) + 0.00031596 *begin_x*lens_ipow(begin_y, 2) + -0.278293 *begin_x*lens_ipow(begin_dy, 2) + -0.74213 *begin_x*lens_ipow(begin_dx, 2) + 0.00448878 *lens_ipow(begin_y, 2)*begin_dx + 7.1231e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.000407038 *lens_ipow(begin_x, 3)*begin_lambda + -1.07264 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 2.02572 *lens_ipow(begin_dx, 5) + -1.61206e-06 *begin_x*lens_ipow(begin_y, 4) + 8.1859e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.15825 *begin_x*lens_ipow(begin_dy, 4) + -0.0300557 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.700961 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0496253 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.00695169 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -0.0210117 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 8.16694e-08 *lens_ipow(begin_x, 6)*begin_dx + -0.000101435 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 2) + -4.56498e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 2) + 3.87568e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3)*begin_dy,
       + 0.662987 *begin_y + 12.965 *begin_dy + 0.377198 *begin_dy*begin_lambda + 0.0197292 *begin_y*begin_lambda + -0.307721 *begin_y*lens_ipow(begin_dx, 2) + -0.00450013 *lens_ipow(begin_y, 2)*begin_dy + -0.790181 *begin_y*lens_ipow(begin_dy, 2) + -0.481316 *begin_x*begin_dx*begin_dy + -0.00588822 *begin_x*begin_y*begin_dx + -10.2053 *lens_ipow(begin_dx, 2)*begin_dy + -10.4048 *lens_ipow(begin_dy, 3) + 0.000419695 *lens_ipow(begin_y, 3)*begin_lambda + 0.000297637 *lens_ipow(begin_x, 2)*begin_y*begin_lambda + -0.000202156 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 2) + 0.00147169 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.99843 *lens_ipow(begin_dy, 5) + 0.0844115 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0213895 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.000313062 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + 0.000148138 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.0039002 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.000204911 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00011744 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3) + -5.74732e-09 *lens_ipow(begin_y, 7) + 13.8205 *lens_ipow(begin_dx, 6)*begin_dy + 0.682883 *begin_y*lens_ipow(begin_dx, 6) + 0.00350062 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 5)*begin_dy + -1.98836e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 12.9766  + 0.322163 *begin_lambda + -0.362789 *begin_y*begin_dy + -0.00364467 *lens_ipow(begin_x, 2) + -30.3122 *lens_ipow(begin_dx, 2) + -9.68762 *lens_ipow(begin_dy, 2) + -1.48426 *begin_x*begin_dx + 0.00448878 *lens_ipow(begin_y, 2) + -3.21791 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 10.1286 *lens_ipow(begin_dx, 4) + 8.1859e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.0300557 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.700961 *begin_y*lens_ipow(begin_dy, 3) + -0.148876 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.00695169 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + -0.0210117 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 8.16694e-08 *lens_ipow(begin_x, 6) + -0.000101435 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(0, 1) =  + -0.362789 *begin_y*begin_dx + -19.3752 *begin_dx*begin_dy + -0.556585 *begin_x*begin_dy + -1.07264 *begin_y*lens_ipow(begin_dx, 3) + 0.632998 *begin_x*lens_ipow(begin_dy, 3) + -0.0601114 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -2.10288 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0420234 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 3.87568e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3)+0.0f;
    dx1_domega0(1, 0) =  + -0.615442 *begin_y*begin_dx + -0.481316 *begin_x*begin_dy + -0.00588822 *begin_x*begin_y + -20.4107 *begin_dx*begin_dy + 0.00147169 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.0844115 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -0.0427791 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.000352319 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2) + 82.9232 *lens_ipow(begin_dx, 5)*begin_dy + 4.0973 *begin_y*lens_ipow(begin_dx, 5) + 0.0175031 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4)*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 12.965  + 0.377198 *begin_lambda + -0.00450013 *lens_ipow(begin_y, 2) + -1.58036 *begin_y*begin_dy + -0.481316 *begin_x*begin_dx + -10.2053 *lens_ipow(begin_dx, 2) + -31.2145 *lens_ipow(begin_dy, 2) + 0.00147169 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 9.99213 *lens_ipow(begin_dy, 4) + 0.168823 *begin_x*begin_y*begin_dx*begin_dy + -0.0213895 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.000148138 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.00780039 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.000409822 *lens_ipow(begin_y, 3)*begin_dy + 13.8205 *lens_ipow(begin_dx, 6) + 0.00350062 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 5)+0.0f;
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
    out(0) =  + 17.9177 *begin_dx + 0.602111 *begin_x + 0.667407 *begin_y*begin_dx*begin_dy + 0.170584 *begin_x*begin_y*begin_dy + 0.191054 *lens_ipow(begin_x, 2)*begin_dx + -7.67197 *lens_ipow(begin_dx, 3) + -6.71659 *begin_dx*lens_ipow(begin_dy, 2) + 0.00551866 *begin_x*lens_ipow(begin_y, 2) + 0.00460717 *lens_ipow(begin_x, 3) + 1.07962 *begin_x*lens_ipow(begin_dy, 2) + 1.39589 *begin_x*lens_ipow(begin_dx, 2) + 0.0543171 *lens_ipow(begin_y, 2)*begin_dx + 0.000260837 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.000203448 *lens_ipow(begin_x, 3)*begin_lambda + -1.81072e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.00298268 *lens_ipow(begin_x, 4)*begin_dx + 0.535297 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -5.93754e-05 *lens_ipow(begin_y, 4)*begin_dx + 3.75488e-05 *lens_ipow(begin_x, 5) + -1.25676e-05 *begin_x*lens_ipow(begin_y, 4) + 13.2827 *begin_dx*lens_ipow(begin_dy, 4) + 0.00304819 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.0704709 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.00456448 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.00752014 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 48.8996 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 0.00557961 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -2.14114e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3);
    out(1) =  + 0.584776 *begin_y + 17.757 *begin_dy + 0.024364 *begin_y*begin_lambda + 1.15437 *begin_y*lens_ipow(begin_dx, 2) + 0.238332 *lens_ipow(begin_y, 2)*begin_dy + 2.39581 *begin_y*lens_ipow(begin_dy, 2) + 0.668658 *begin_x*begin_dx*begin_dy + 0.162557 *begin_x*begin_y*begin_dx + -3.83382 *lens_ipow(begin_dx, 2)*begin_dy + 0.00496322 *lens_ipow(begin_x, 2)*begin_y + 0.00548197 *lens_ipow(begin_y, 3) + 0.0498067 *lens_ipow(begin_x, 2)*begin_dy + -0.0661509 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -37.7923 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -2.71646 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -168.767 *lens_ipow(begin_dy, 5)*begin_lambda + 9.89795e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 2) + 0.00527412 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 4) + 6.97982e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dx + -1.08863e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 0.76685 *begin_dy*lens_ipow(begin_lambda, 6) + -0.299378 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5)*begin_lambda + 135.79 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5)*begin_lambda + -0.00111716 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -1.72925e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_lambda + 0.032086 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 179.182 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 4206.17 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2);
    out(2) =  + -1.57309 *begin_dx + -0.108927 *begin_x + -0.138291 *begin_y*begin_dx*begin_dy + -0.0154726 *begin_x*begin_y*begin_dy + -0.00599352 *lens_ipow(begin_x, 2)*begin_dx + 0.994634 *lens_ipow(begin_dx, 3) + -0.820828 *begin_dx*lens_ipow(begin_dy, 2) + -0.000250452 *begin_x*lens_ipow(begin_y, 2) + -5.37209e-05 *lens_ipow(begin_x, 3) + -0.134057 *begin_x*lens_ipow(begin_dy, 2) + -0.0029891 *lens_ipow(begin_y, 2)*begin_dx + 0.000290484 *begin_x*begin_y*begin_dy*begin_lambda + 0.000585485 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.0479054 *begin_x*lens_ipow(begin_dx, 4) + 0.263479 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 8.12132e-07 *begin_x*lens_ipow(begin_y, 4) + -1.25433 *begin_dx*lens_ipow(begin_dy, 4) + -5.62873e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 2.08465e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 0.012459 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.000136007 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.0669365 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.000216256 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3) + 0.00686359 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_dy + 1.01202e-09 *lens_ipow(begin_x, 7) + 0.0108333 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5) + 1.81135e-08 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2) + 4.485e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 4);
    out(3) =  + -0.109054 *begin_y + -1.56897 *begin_dy + -0.00455368 *lens_ipow(begin_y, 2)*begin_dy + 0.0168874 *begin_y*lens_ipow(begin_dy, 2) + 0.276743 *begin_x*begin_dx*begin_dy + 2.82002 *lens_ipow(begin_dx, 2)*begin_dy + 0.000141049 *lens_ipow(begin_x, 2)*begin_y + 0.00702541 *lens_ipow(begin_x, 2)*begin_dy + 0.949921 *lens_ipow(begin_dy, 3) + 0.0158196 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.000106003 *lens_ipow(begin_y, 3)*begin_lambda + 0.000998087 *begin_x*begin_y*begin_dx*begin_lambda + -0.00898603 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00491352 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.00578457 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 8.18166e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -5.50313e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00020283 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + -0.022278 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + 9.52059e-07 *lens_ipow(begin_x, 5)*begin_dx*begin_dy + -0.000791127 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 4)*begin_lambda + 6.24809e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -4.99987e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.266407 *begin_x*lens_ipow(begin_dx, 7)*begin_dy + -7.18498e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + 2.58201e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7) + 0.760083 *begin_y*lens_ipow(begin_dx, 8)*begin_lambda + 1.99944e-08 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.108927  + -0.0154726 *begin_y*begin_dy + -0.011987 *begin_x*begin_dx + -0.000250452 *lens_ipow(begin_y, 2) + -0.000161163 *lens_ipow(begin_x, 2) + -0.134057 *lens_ipow(begin_dy, 2) + 0.000290484 *begin_y*begin_dy*begin_lambda + 0.00117097 *begin_x*begin_dx*begin_lambda + 0.0479054 *lens_ipow(begin_dx, 4) + 0.263479 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 8.12132e-07 *lens_ipow(begin_y, 4) + -1.68862e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 2.08465e-05 *lens_ipow(begin_y, 3)*begin_dy + 0.0249181 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00040802 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 7.08415e-09 *lens_ipow(begin_x, 6) + 0.0108333 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5) + 1.81135e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2) + 3.1395e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4)+0.0f;
    domega2_dx0(0, 1) =  + -0.138291 *begin_dx*begin_dy + -0.0154726 *begin_x*begin_dy + -0.000500903 *begin_x*begin_y + -0.00597821 *begin_y*begin_dx + 0.000290484 *begin_x*begin_dy*begin_lambda + 3.24853e-06 *begin_x*lens_ipow(begin_y, 3) + -5.62873e-06 *lens_ipow(begin_x, 3)*begin_dy + 6.25394e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 0.133873 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.000865024 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + 0.0205908 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + 1.08681e-07 *begin_x*lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + 1.794e-12 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.276743 *begin_dx*begin_dy + 0.000282098 *begin_x*begin_y + 0.0140508 *begin_x*begin_dy + 0.000998087 *begin_y*begin_dx*begin_lambda + -0.00898603 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.0115691 *begin_x*lens_ipow(begin_dy, 3) + -0.022278 *begin_y*begin_dx*lens_ipow(begin_dy, 4) + 4.7603e-06 *lens_ipow(begin_x, 4)*begin_dx*begin_dy + -0.00158225 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_lambda + -0.000149996 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.266407 *lens_ipow(begin_dx, 7)*begin_dy + -7.18498e-06 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + 5.16401e-11 *begin_x*lens_ipow(begin_y, 7)+0.0f;
    domega2_dx0(1, 1) =  + -0.109054  + -0.00910736 *begin_y*begin_dy + 0.0168874 *lens_ipow(begin_dy, 2) + 0.000141049 *lens_ipow(begin_x, 2) + 0.0158196 *lens_ipow(begin_dx, 2)*begin_lambda + -0.000318009 *lens_ipow(begin_y, 2)*begin_lambda + 0.000998087 *begin_x*begin_dx*begin_lambda + -0.00898603 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.00982704 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.00024545 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -0.000165094 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.000608489 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.022278 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.000791127 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*begin_lambda + 0.000249923 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -4.99987e-05 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -2.87399e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + 1.80741e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6) + 0.760083 *lens_ipow(begin_dx, 8)*begin_lambda + 1.39961e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*begin_lambda+0.0f;
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
  out[4] =  + 0.498477  + 0.595147 *begin_lambda + -0.0142548 *begin_x*begin_dx + -0.000398753 *lens_ipow(begin_x, 2) + -0.142073 *lens_ipow(begin_dx, 2) + -0.829578 *lens_ipow(begin_lambda, 2) + 0.407124 *lens_ipow(begin_lambda, 3) + -0.685211 *begin_y*lens_ipow(begin_dy, 3) + -0.0155019 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -5.95176 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00187079 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -3.59254 *lens_ipow(begin_dy, 4) + -0.00185358 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -6.11975e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -3.61481e-05 *lens_ipow(begin_y, 4) + -0.55411 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0562136 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.553621 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0601193 *begin_x*begin_y*begin_dx*begin_dy + -0.0155129 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.00225502 *lens_ipow(begin_y, 3)*begin_dy + -9.02138e-07 *lens_ipow(begin_x, 6) + -5.28351 *lens_ipow(begin_dx, 6) + -6.24493e-05 *lens_ipow(begin_x, 5)*begin_dx + -0.00151151 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -0.0130811 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -0.0124501 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.00108727 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 6);
else
  out[4] = 0.0f;
} break;
