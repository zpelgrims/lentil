case kodak__petzval__1948__85mm:
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
//output: [x,y,dx,dy] point and direction on sensor
Eigen::Vector3d view(
  scene_x,
  scene_y,
  scene_z + lens_outer_pupil_curvature_radius
);
raytrace_normalise(view);
int error = 0;
if(1 || view(2) >= lens_field_of_view)
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
       + 65.1825 *begin_dx + 0.792427 *begin_x + 0.942722 *begin_dx*begin_lambda + 0.533382 *begin_y*begin_dx*begin_dy + 0.00936099 *begin_x*begin_y*begin_dy + 0.0144443 *lens_ipow(begin_x, 2)*begin_dx + 1.25818 *begin_dx*lens_ipow(begin_dy, 2) + 7.28418e-05 *begin_x*lens_ipow(begin_y, 2) + 6.70711e-05 *lens_ipow(begin_x, 3) + 0.130729 *begin_x*lens_ipow(begin_dy, 2) + 0.606349 *begin_x*lens_ipow(begin_dx, 2) + 0.00632968 *lens_ipow(begin_y, 2)*begin_dx + -0.633781 *begin_dx*lens_ipow(begin_lambda, 2) + -4.61727e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 3.10147e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -0.00622391 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 3) + 0.0640506 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 4.99658e-05 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 0.00302131 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 2.67474e-07 *lens_ipow(begin_x, 5)*begin_lambda + 1.94411e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + 3.32672e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 0.00318082 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.55993e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.000125202 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.204956 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -0.13218 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + 6706.62 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 4),
       + 0.792291 *begin_y + 65.3526 *begin_dy + 0.236246 *begin_dy*begin_lambda + 0.136052 *begin_y*lens_ipow(begin_dx, 2) + 0.0142852 *lens_ipow(begin_y, 2)*begin_dy + 0.60558 *begin_y*lens_ipow(begin_dy, 2) + 0.00954826 *begin_x*begin_y*begin_dx + -17.7662 *lens_ipow(begin_dx, 2)*begin_dy + 7.42811e-05 *lens_ipow(begin_x, 2)*begin_y + 6.32119e-05 *lens_ipow(begin_y, 3) + 0.693462 *lens_ipow(begin_dy, 3) + 69.9512 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.0278005 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 1.97307 *begin_x*begin_dx*begin_dy*begin_lambda + -1.7442 *begin_x*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.0358943 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -61.7746 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 5.45264e-05 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.00383419 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 2.7191e-07 *lens_ipow(begin_y, 5)*begin_lambda + 0.0130185 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 1.49375 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -5.56079e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 3) + 0.119447 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -9.20076e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.00283413 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00880876 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 4) + -0.357318 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 65.1825  + 0.942722 *begin_lambda + 0.533382 *begin_y*begin_dy + 0.0144443 *lens_ipow(begin_x, 2) + 1.25818 *lens_ipow(begin_dy, 2) + 1.2127 *begin_x*begin_dx + 0.00632968 *lens_ipow(begin_y, 2) + -0.633781 *lens_ipow(begin_lambda, 2) + 3.10147e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00622391 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + 0.192152 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 4.99658e-05 *lens_ipow(begin_x, 4)*begin_lambda + 0.00604262 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + 0.00636164 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -2.55993e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -0.000125202 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.409911 *begin_x*begin_dx*lens_ipow(begin_lambda, 4) + -0.528719 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 33533.1 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4)+0.0f;
    dx1_domega0(0, 1) =  + 0.533382 *begin_y*begin_dx + 0.00936099 *begin_x*begin_y + 2.51636 *begin_dx*begin_dy + 0.261459 *begin_x*begin_dy + 1.94411e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 0.00636164 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -2.55993e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -0.000250404 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.13218 *begin_x*begin_y*lens_ipow(begin_dx, 4) + 26826.5 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 0) =  + 0.272104 *begin_y*begin_dx + 0.00954826 *begin_x*begin_y + -35.5325 *begin_dx*begin_dy + 139.902 *begin_dx*begin_dy*begin_lambda + 1.97307 *begin_x*begin_dy*begin_lambda + -1.7442 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -123.549 *begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -9.20076e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 0.00566826 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 1) =  + 65.3526  + 0.236246 *begin_lambda + 0.0142852 *lens_ipow(begin_y, 2) + 1.21116 *begin_y*begin_dy + -17.7662 *lens_ipow(begin_dx, 2) + 2.08039 *lens_ipow(begin_dy, 2) + 69.9512 *lens_ipow(begin_dx, 2)*begin_lambda + 0.0278005 *lens_ipow(begin_x, 2)*begin_lambda + 1.97307 *begin_x*begin_dx*begin_lambda + -1.7442 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -0.0358943 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + -61.7746 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 5.45264e-05 *lens_ipow(begin_y, 4)*begin_lambda + 0.00766838 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 0.0130185 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + 5.97501 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 0.35834 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -9.20076e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 0.00566826 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00880876 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 4) + -0.714636 *begin_y*begin_dy*lens_ipow(begin_lambda, 5)+0.0f;
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
    out(0) =  + 84.9563 *begin_dx + 0.552862 *begin_x + -0.0113797 *begin_x*begin_lambda + 0.331963 *begin_y*begin_dx*begin_dy + 0.0231468 *begin_x*begin_y*begin_dy + 0.029092 *lens_ipow(begin_x, 2)*begin_dx + -42.3909 *lens_ipow(begin_dx, 3) + -41.2989 *begin_dx*lens_ipow(begin_dy, 2) + 0.000174597 *begin_x*lens_ipow(begin_y, 2) + 0.000141707 *lens_ipow(begin_x, 3) + 0.489072 *begin_x*lens_ipow(begin_dy, 2) + 0.731672 *begin_x*lens_ipow(begin_dx, 2) + 0.00892574 *lens_ipow(begin_y, 2)*begin_dx + 3.33209e-05 *lens_ipow(begin_x, 4)*begin_dx + 2.30816e-07 *lens_ipow(begin_x, 5) + 0.000946746 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.0784057 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.00736168 *begin_x*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -2.76395 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 150.581 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 1.21351e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.00191811 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -1.86086e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 7.48215e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + 2.63814e-05 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 2) + 2.68559e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -0.0062644 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 4) + 0.00430838 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2);
    out(1) =  + 0.556899 *begin_y + 84.949 *begin_dy + -0.0320243 *begin_y*begin_lambda + 0.502239 *begin_y*lens_ipow(begin_dx, 2) + 0.0342986 *lens_ipow(begin_y, 2)*begin_dy + 0.877712 *begin_y*lens_ipow(begin_dy, 2) + 0.356264 *begin_x*begin_dx*begin_dy + 0.0231718 *begin_x*begin_y*begin_dx + -39.8464 *lens_ipow(begin_dx, 2)*begin_dy + 0.0236218 *begin_y*lens_ipow(begin_lambda, 2) + 0.000176023 *lens_ipow(begin_x, 2)*begin_y + 0.000195113 *lens_ipow(begin_y, 3) + 0.00908 *lens_ipow(begin_x, 2)*begin_dy + -41.7877 *lens_ipow(begin_dy, 3) + -0.323281 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.0124826 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000113656 *lens_ipow(begin_y, 3)*begin_lambda + 0.000101284 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.00651749 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 5.32605e-07 *lens_ipow(begin_y, 5)*begin_lambda + 0.143311 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -1.94874e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.606722 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 2.62571e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 6.70622e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + -0.471926 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2) + -9.66983 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4)*begin_lambda + 71410.7 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 2);
    out(2) =  + -1.41418 *begin_dx + -0.0211228 *begin_x + 0.000703839 *begin_x*begin_lambda + 0.0102399 *begin_dx*begin_lambda + -0.0206775 *begin_y*begin_dx*begin_dy + -0.000248927 *lens_ipow(begin_x, 2)*begin_dx + 0.881868 *lens_ipow(begin_dx, 3) + -0.427536 *begin_dx*lens_ipow(begin_dy, 2) + -6.58998e-07 *lens_ipow(begin_x, 3) + -0.000144472 *lens_ipow(begin_y, 2)*begin_dx + -0.334716 *lens_ipow(begin_dx, 3)*begin_lambda + -0.045172 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + -0.000528123 *begin_x*lens_ipow(begin_lambda, 3) + -0.00122109 *begin_x*begin_y*begin_dy*begin_lambda + -0.453074 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.00481216 *begin_y*begin_dx*begin_dy*begin_lambda + -3.28332e-08 *lens_ipow(begin_x, 4)*begin_dx + -0.0121239 *begin_x*lens_ipow(begin_dx, 4) + -1.58738e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -0.00460347 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 0.0448282 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 1.89362e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + 0.00127375 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -0.00284926 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 19.296 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 8.10952e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 9.87107 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 3.75845 *begin_dx*lens_ipow(begin_dy, 6);
    out(3) =  + -0.0208952 *begin_y + -1.40793 *begin_dy + 0.000124671 *begin_y*begin_lambda + -0.00020066 *lens_ipow(begin_y, 2)*begin_dy + 0.0371782 *begin_x*begin_dx*begin_dy + -6.48799e-05 *begin_x*begin_y*begin_dx + 2.08235 *lens_ipow(begin_dx, 2)*begin_dy + -1.92021e-07 *lens_ipow(begin_y, 3) + 0.000128592 *lens_ipow(begin_x, 2)*begin_dy + 0.654851 *lens_ipow(begin_dy, 3) + 0.00173212 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.0552391 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -7.22779e-07 *lens_ipow(begin_y, 4)*begin_dy + 2.38478 *lens_ipow(begin_dy, 5) + -4.82754e-08 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00048236 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00147656 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.000161659 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 5.79913e-10 *lens_ipow(begin_x, 4)*begin_y + -3.50958e-09 *lens_ipow(begin_y, 5) + 0.00029746 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -1.62131 *lens_ipow(begin_dx, 4)*begin_dy + 8.7298e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + -5.15475e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.000425582 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -2.82625 *lens_ipow(begin_dy, 5)*begin_lambda + 5.63703e-05 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 4) + -0.0458422 *begin_y*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3);
    Eigen::Vector3d pred_out_cs_pos(0,0,0);
    Eigen::Vector3d pred_out_cs_dir(0,0,0);
    Eigen::Vector2d outpos(out(0), out(1));
    Eigen::Vector2d outdir(out(2), out(3));
    if (lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, true);
    else if (lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, false);
    else sphereToCs(outpos, outdir, pred_out_cs_pos, pred_out_cs_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    Eigen::Vector3d view(
      scene_x - pred_out_cs_pos(0),
      scene_y - pred_out_cs_pos(1),
      scene_z - pred_out_cs_pos(2)
    );
    raytrace_normalise(view);
    Eigen::VectorXd out_new(5); out_new.setZero();
    Eigen::Vector2d out_new_pos(0,0);
    Eigen::Vector2d out_new_dir(0,0);
    if (lens_outer_pupil_geometry == "cyl-y") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, true);
    else if (lens_outer_pupil_geometry == "cyl-x") csToCylinder(pred_out_cs_pos, view, out_new_pos, out_new_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius, false);
    else csToSphere(pred_out_cs_pos, view, out_new_pos, out_new_dir, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    out_new(0) = out_new_pos(0);
    out_new(1) = out_new_pos(1);
    out_new(2) = out_new_dir(0);
    out_new(3) = out_new_dir(1);
    const Eigen::Vector2d delta_out(out_new[2] - out[2], out_new[3] - out[3]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    Eigen::Matrix2d domega2_dx0;
    domega2_dx0(0, 0) =  + -0.0211228  + 0.000703839 *begin_lambda + -0.000497853 *begin_x*begin_dx + -1.97699e-06 *lens_ipow(begin_x, 2) + -0.045172 *lens_ipow(begin_dy, 2)*begin_lambda + -0.000528123 *lens_ipow(begin_lambda, 3) + -0.00122109 *begin_y*begin_dy*begin_lambda + -1.31333e-07 *lens_ipow(begin_x, 3)*begin_dx + -0.0121239 *lens_ipow(begin_dx, 4) + -1.58738e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + -0.00460347 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 0.0448282 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 1.89362e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + 0.00127375 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -0.00284926 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 1.6219e-08 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy+0.0f;
    domega2_dx0(0, 1) =  + -0.0206775 *begin_dx*begin_dy + -0.000288943 *begin_y*begin_dx + -0.00122109 *begin_x*begin_dy*begin_lambda + -0.00481216 *begin_dx*begin_dy*begin_lambda + -3.17477e-05 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 3.78723e-05 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 0.00127375 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -0.00284926 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 2.43286e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy+0.0f;
    domega2_dx0(1, 0) =  + 0.0371782 *begin_dx*begin_dy + -6.48799e-05 *begin_y*begin_dx + 0.000257184 *begin_x*begin_dy + -0.0552391 *lens_ipow(begin_dx, 3)*begin_dy + -4.82754e-08 *lens_ipow(begin_y, 3)*begin_dx + 0.00048236 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 2.31965e-09 *lens_ipow(begin_x, 3)*begin_y + 0.000594921 *begin_x*lens_ipow(begin_dy, 3) + 1.74596e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -0.000851164 *begin_x*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 5.63703e-05 *begin_y*begin_dx*lens_ipow(begin_lambda, 4)+0.0f;
    domega2_dx0(1, 1) =  + -0.0208952  + 0.000124671 *begin_lambda + -0.000401321 *begin_y*begin_dy + -6.48799e-05 *begin_x*begin_dx + -5.76064e-07 *lens_ipow(begin_y, 2) + 0.00173212 *lens_ipow(begin_dx, 2)*begin_lambda + -2.89112e-06 *lens_ipow(begin_y, 3)*begin_dy + -1.44826e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.00048236 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00295313 *begin_y*lens_ipow(begin_dy, 3) + 0.000323318 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 5.79913e-10 *lens_ipow(begin_x, 4) + -1.75479e-08 *lens_ipow(begin_y, 4) + 8.7298e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000154642 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 5.63703e-05 *begin_x*begin_dx*lens_ipow(begin_lambda, 4) + -0.0458422 *lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3)+0.0f;
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
if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;
const double begin_x = x;
const double begin_y = y;
const double begin_dx = dx;
const double begin_dy = dy;
const double begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.536428  + 0.640991 *begin_lambda + 8.50044e-06 *lens_ipow(begin_y, 2) + -0.885388 *lens_ipow(begin_lambda, 2) + 0.430378 *lens_ipow(begin_lambda, 3) + -0.000466239 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -3.38331e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -3.50691e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -5.78629e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.91562e-07 *lens_ipow(begin_y, 4) + -0.0155424 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00117419 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0241003 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.00189659 *begin_x*begin_y*begin_dx*begin_dy + -0.000519225 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -3.24076e-05 *lens_ipow(begin_y, 3)*begin_dy + -1.5958e-09 *lens_ipow(begin_x, 6) + -3.08558e-07 *lens_ipow(begin_x, 5)*begin_dx + -0.0146233 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -2.46425e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -0.000948906 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -0.187418 *begin_y*lens_ipow(begin_dy, 5) + 0.914971 *begin_y*lens_ipow(begin_dy, 7) + -5.53541e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -2.74326e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + -2.38845e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx + 5.20847e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 4.09671e-10 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3);
else
  out[4] = 0.0f;
} break;
