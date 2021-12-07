case cooke__speed_panchro__1920__40mm:
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
       + 28.7526 *begin_dx + 0.659683 *begin_x + 0.0225658 *begin_x*begin_lambda + 0.838809 *begin_dx*begin_lambda + -0.355265 *begin_y*begin_dx*begin_dy + -22.264 *lens_ipow(begin_dx, 3) + -21.2417 *begin_dx*lens_ipow(begin_dy, 2) + 7.3305e-05 *begin_x*lens_ipow(begin_y, 2) + 5.35676e-05 *lens_ipow(begin_x, 3) + -0.285035 *begin_x*lens_ipow(begin_dy, 2) + -0.721997 *begin_x*lens_ipow(begin_dx, 2) + 0.0022198 *lens_ipow(begin_y, 2)*begin_dx + 7.03968e-06 *lens_ipow(begin_x, 4)*begin_dx + -0.319535 *begin_x*lens_ipow(begin_dx, 4) + -1.17233 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -6.83104e-08 *begin_x*lens_ipow(begin_y, 4) + -9.75998 *begin_dx*lens_ipow(begin_dy, 4) + 7.61872e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -0.0226686 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -1.27293 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0229699 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.0116368 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.000410143 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.000159652 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 0.492022 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + 5.08348e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -1.82397e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -0.724248 *begin_x*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 4),
       + 0.64034 *begin_y + 28.0678 *begin_dy + 3.37459 *begin_dy*begin_lambda + 0.0938781 *begin_y*begin_lambda + -0.277055 *begin_y*lens_ipow(begin_dx, 2) + -0.719888 *begin_y*lens_ipow(begin_dy, 2) + -0.394178 *begin_x*begin_dx*begin_dy + -21.6382 *lens_ipow(begin_dx, 2)*begin_dy + -0.065173 *begin_y*lens_ipow(begin_lambda, 2) + 7.29728e-05 *lens_ipow(begin_x, 2)*begin_y + -2.29991 *begin_dy*lens_ipow(begin_lambda, 2) + 5.6478e-05 *lens_ipow(begin_y, 3) + 0.00172258 *lens_ipow(begin_x, 2)*begin_dy + -22.184 *lens_ipow(begin_dy, 3) + -0.0166547 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.785544 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.239336 *begin_y*lens_ipow(begin_dx, 4) + 8.54678e-06 *lens_ipow(begin_y, 4)*begin_dy + -7.07638e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 4.03032e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -0.345384 *begin_y*lens_ipow(begin_dy, 4) + 0.000480384 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.0112172 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.0056026 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -0.417486 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5)*begin_lambda + -14.4717 *begin_x*begin_dx*lens_ipow(begin_dy, 5)*begin_lambda + -1.77795 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2) + 0.934025 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 7)*lens_ipow(begin_lambda, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 28.7526  + 0.838809 *begin_lambda + -0.355265 *begin_y*begin_dy + -66.792 *lens_ipow(begin_dx, 2) + -21.2417 *lens_ipow(begin_dy, 2) + -1.44399 *begin_x*begin_dx + 0.0022198 *lens_ipow(begin_y, 2) + 7.03968e-06 *lens_ipow(begin_x, 4) + -1.27814 *begin_x*lens_ipow(begin_dx, 3) + -3.51699 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -9.75998 *lens_ipow(begin_dy, 4) + 7.61872e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.0226686 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -1.27293 *begin_y*lens_ipow(begin_dy, 3) + -0.0689097 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0116368 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.000820286 *lens_ipow(begin_x, 3)*begin_dx + 0.000159652 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -0.355265 *begin_y*begin_dx + -42.4835 *begin_dx*begin_dy + -0.570069 *begin_x*begin_dy + -1.17233 *begin_y*lens_ipow(begin_dx, 3) + -39.0399 *begin_dx*lens_ipow(begin_dy, 3) + -0.0453373 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -3.81879 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0232736 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.000159652 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + 1.96809 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + 5.08348e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -3.64793e-07 *lens_ipow(begin_x, 5)*begin_dy + -2.89699 *begin_x*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 4)+0.0f;
    dx1_domega0(1, 0) =  + -0.55411 *begin_y*begin_dx + -0.394178 *begin_x*begin_dy + -43.2764 *begin_dx*begin_dy + -0.0333093 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -2.35663 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.957343 *begin_y*lens_ipow(begin_dx, 3) + 4.03032e-06 *lens_ipow(begin_x, 3)*begin_y + -0.0224344 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -14.4717 *begin_x*lens_ipow(begin_dy, 5)*begin_lambda + -1.77795 *begin_x*begin_y*lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 1) =  + 28.0678  + 3.37459 *begin_lambda + -1.43978 *begin_y*begin_dy + -0.394178 *begin_x*begin_dx + -21.6382 *lens_ipow(begin_dx, 2) + -2.29991 *lens_ipow(begin_lambda, 2) + 0.00172258 *lens_ipow(begin_x, 2) + -66.5521 *lens_ipow(begin_dy, 2) + -0.0166547 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.785544 *begin_x*lens_ipow(begin_dx, 3) + 8.54678e-06 *lens_ipow(begin_y, 4) + -1.38154 *begin_y*lens_ipow(begin_dy, 3) + 0.000960768 *lens_ipow(begin_y, 3)*begin_dy + -0.0112172 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.0224104 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -2.08743 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -72.3584 *begin_x*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -10.6677 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 2) + 6.53817 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2)+0.0f;
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
    out(0) =  + 39.8032 *begin_dx + 0.602998 *begin_x + 0.585201 *begin_y*begin_dx*begin_dy + 0.0752952 *begin_x*begin_y*begin_dy + 0.0805075 *lens_ipow(begin_x, 2)*begin_dx + -16.0756 *lens_ipow(begin_dx, 3) + -15.335 *begin_dx*lens_ipow(begin_dy, 2) + 0.00110254 *begin_x*lens_ipow(begin_y, 2) + 0.000834625 *lens_ipow(begin_x, 3) + 1.08931 *begin_x*lens_ipow(begin_dy, 2) + 1.28465 *begin_x*lens_ipow(begin_dx, 2) + 0.0226669 *lens_ipow(begin_y, 2)*begin_dx + 0.000108323 *lens_ipow(begin_x, 3)*begin_lambda + -1.1917e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 1.03457 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.000877799 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -2.79106e-07 *begin_x*lens_ipow(begin_y, 4) + 20.3827 *begin_dx*lens_ipow(begin_dy, 4) + -3.22655e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 75.5701 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.126888 *begin_x*begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 0.967375 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 6.47285 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 0.000746873 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 0.0430127 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 4.2221e-06 *lens_ipow(begin_x, 5)*begin_lambda + -2.47604 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + -0.00151913 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3);
    out(1) =  + 0.604253 *begin_y + 39.8586 *begin_dy + 0.973402 *begin_y*lens_ipow(begin_dx, 2) + 0.0769561 *lens_ipow(begin_y, 2)*begin_dy + 1.15273 *begin_y*lens_ipow(begin_dy, 2) + 0.529298 *begin_x*begin_dx*begin_dy + 0.0717074 *begin_x*begin_y*begin_dx + -19.2527 *lens_ipow(begin_dx, 2)*begin_dy + 0.00107434 *lens_ipow(begin_x, 2)*begin_y + 0.000797916 *lens_ipow(begin_y, 3) + 0.0228254 *lens_ipow(begin_x, 2)*begin_dy + -18.1159 *lens_ipow(begin_dy, 3) + 0.000107863 *lens_ipow(begin_y, 3)*begin_lambda + -0.0210276 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.00243569 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 88.6288 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 4.76403e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00196183 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + 4.55689e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + 0.00108978 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 53.4768 *lens_ipow(begin_dx, 4)*begin_dy + 5.40644e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.00160772 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.000828847 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.0465428 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 4.87525e-06 *lens_ipow(begin_y, 5)*begin_lambda + 6.58545 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 1.02216 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda;
    out(2) =  + -1.56323 *begin_dx + -0.0488751 *begin_x + -0.070106 *begin_y*begin_dx*begin_dy + -0.0031572 *begin_x*begin_y*begin_dy + -0.00146839 *lens_ipow(begin_x, 2)*begin_dx + 0.506736 *lens_ipow(begin_dx, 3) + -1.13455 *begin_dx*lens_ipow(begin_dy, 2) + -2.24618e-05 *begin_x*lens_ipow(begin_y, 2) + -7.06141e-06 *lens_ipow(begin_x, 3) + -0.0634172 *begin_x*lens_ipow(begin_dy, 2) + -0.0191735 *begin_x*lens_ipow(begin_dx, 2) + -0.000678409 *lens_ipow(begin_y, 2)*begin_dx + 6.13566e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 1.26609e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.0035781 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -5.92758e-07 *lens_ipow(begin_x, 4)*begin_dx + 0.345353 *begin_x*lens_ipow(begin_dx, 4) + 0.00616425 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.206655 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 5.26754 *lens_ipow(begin_dx, 5) + 0.375998 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.0088536 *begin_x*lens_ipow(begin_dy, 4) + 0.0017719 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.00437312 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 8.6245 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -3.09565e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.0416559 *begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -6.8115e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6)*begin_dx;
    out(3) =  + -0.0489169 *begin_y + -1.56463 *begin_dy + -0.00121456 *lens_ipow(begin_y, 2)*begin_dy + -0.007726 *begin_y*lens_ipow(begin_dy, 2) + 0.115792 *begin_x*begin_dx*begin_dy + 2.6881 *lens_ipow(begin_dx, 2)*begin_dy + 1.24567e-05 *lens_ipow(begin_x, 2)*begin_y + -4.92102e-06 *lens_ipow(begin_y, 3) + 0.00131018 *lens_ipow(begin_x, 2)*begin_dy + 0.699846 *lens_ipow(begin_dy, 3) + -1.39393e-06 *lens_ipow(begin_y, 3)*begin_lambda + 0.00768971 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.0785436 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -2.69958e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0186512 *begin_y*lens_ipow(begin_dx, 4) + -1.17054e-06 *lens_ipow(begin_y, 4)*begin_dy + 1.88167e-06 *lens_ipow(begin_x, 4)*begin_dy + 3.18213 *lens_ipow(begin_dy, 5) + -0.0032049 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.000836249 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.163295 *begin_y*lens_ipow(begin_dy, 4) + 0.00111087 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.000224038 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -9.64764e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -3.63817e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.00112263 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -5.58174e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy + 7.2723e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2);
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
    domega2_dx0(0, 0) =  + -0.0488751  + -0.0031572 *begin_y*begin_dy + -0.00293678 *begin_x*begin_dx + -2.24618e-05 *lens_ipow(begin_y, 2) + -2.11842e-05 *lens_ipow(begin_x, 2) + -0.0634172 *lens_ipow(begin_dy, 2) + -0.0191735 *lens_ipow(begin_dx, 2) + 0.000122713 *begin_x*begin_dx*begin_lambda + 3.79828e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.0035781 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -2.37103e-06 *lens_ipow(begin_x, 3)*begin_dx + 0.345353 *lens_ipow(begin_dx, 4) + 0.0123285 *begin_x*lens_ipow(begin_dx, 3) + 0.375998 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.0088536 *lens_ipow(begin_dy, 4) + 0.00874624 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -3.09565e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -2.7246e-14 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx+0.0f;
    domega2_dx0(0, 1) =  + -0.070106 *begin_dx*begin_dy + -0.0031572 *begin_x*begin_dy + -4.49237e-05 *begin_x*begin_y + -0.00135682 *begin_y*begin_dx + 2.53219e-08 *lens_ipow(begin_x, 3)*begin_y + 0.0035781 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.206655 *lens_ipow(begin_dx, 3)*begin_dy + 0.0035438 *begin_y*lens_ipow(begin_dx, 3) + -6.1913e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0416559 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -4.0869e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_dx+0.0f;
    domega2_dx0(1, 0) =  + 0.115792 *begin_dx*begin_dy + 2.49134e-05 *begin_x*begin_y + 0.00262037 *begin_x*begin_dy + 0.0153794 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.0785436 *lens_ipow(begin_dx, 3)*begin_dy + -2.69958e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 7.52669e-06 *lens_ipow(begin_x, 3)*begin_dy + -0.0032049 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00222175 *begin_x*lens_ipow(begin_dy, 3) + 0.000672115 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -7.27633e-05 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.00112263 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -2.2327e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy + 2.18169e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(1, 1) =  + -0.0489169  + -0.00242912 *begin_y*begin_dy + -0.007726 *lens_ipow(begin_dy, 2) + 1.24567e-05 *lens_ipow(begin_x, 2) + -1.4763e-05 *lens_ipow(begin_y, 2) + -4.18179e-06 *lens_ipow(begin_y, 2)*begin_lambda + -5.39916e-05 *begin_x*begin_y*begin_dx*begin_dy + 0.0186512 *lens_ipow(begin_dx, 4) + -4.68217e-06 *lens_ipow(begin_y, 3)*begin_dy + -0.0032049 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.0016725 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.163295 *lens_ipow(begin_dy, 4) + -0.000289429 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -3.63817e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.00112263 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -2.2327e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + 2.18169e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)+0.0f;
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
  out[4] =  + 0.561663  + 0.229879 *begin_lambda + 0.00471132 *begin_y*begin_dy + 0.00466919 *begin_x*begin_dx + 5.85542e-05 *lens_ipow(begin_y, 2) + 0.107016 *lens_ipow(begin_dy, 2) + 5.77037e-05 *lens_ipow(begin_x, 2) + 0.106875 *lens_ipow(begin_dx, 2) + -0.157072 *lens_ipow(begin_lambda, 2) + -4.91916 *lens_ipow(begin_dx, 4) + -0.420982 *begin_y*lens_ipow(begin_dy, 3) + -0.00517016 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.420364 *begin_x*lens_ipow(begin_dx, 3) + -9.81945 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000267363 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -4.91501 *lens_ipow(begin_dy, 4) + -0.000267244 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -3.781e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.93504e-06 *lens_ipow(begin_y, 4) + -0.0152694 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.418096 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00027019 *lens_ipow(begin_x, 3)*begin_dx + -0.0153284 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.418704 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -1.91779e-06 *lens_ipow(begin_x, 4) + -0.0199714 *begin_x*begin_y*begin_dx*begin_dy + -0.00518135 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000271936 *lens_ipow(begin_y, 3)*begin_dy;
else
  out[4] = 0.0f;
} break;
