case asahi__takumar__1970__22mm:
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
       + 23.0154 *begin_dx + 0.586679 *begin_x + 0.0122911 *begin_x*begin_lambda + 0.370786 *begin_dx*lens_ipow(begin_lambda, 2) + 4.63789 *begin_dx*lens_ipow(begin_dy, 2) + 4.65475 *lens_ipow(begin_dx, 3) + 1.18214 *begin_y*begin_dx*begin_dy + 0.0311629 *lens_ipow(begin_y, 2)*begin_dx + 0.696488 *begin_x*lens_ipow(begin_dy, 2) + 1.85087 *begin_x*lens_ipow(begin_dx, 2) + 0.0685757 *begin_x*begin_y*begin_dy + 0.00121114 *begin_x*lens_ipow(begin_y, 2) + 0.0988237 *lens_ipow(begin_x, 2)*begin_dx + 0.0012123 *lens_ipow(begin_x, 3) + 7.08548e-05 *lens_ipow(begin_x, 3)*begin_lambda + -0.00108664 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + -2.76434e-05 *lens_ipow(begin_y, 4)*begin_dx + -4.08336e-07 *lens_ipow(begin_x, 5) + 0.000701882 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -2.32928e-09 *begin_x*lens_ipow(begin_y, 6) + -0.000113497 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 9.89296e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 4.73509e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -2.27477e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 7.93525e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -0.000386548 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.00201174 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 6) + -1.25643e-11 *lens_ipow(begin_x, 9)*lens_ipow(begin_dx, 2),
       + 22.8925 *begin_dy + 0.585689 *begin_y + 0.435732 *begin_dy*begin_lambda + 0.0162423 *begin_y*begin_lambda + 4.64388 *lens_ipow(begin_dy, 3) + 4.51208 *lens_ipow(begin_dx, 2)*begin_dy + 1.83358 *begin_y*lens_ipow(begin_dy, 2) + 0.619339 *begin_y*lens_ipow(begin_dx, 2) + 0.0975939 *lens_ipow(begin_y, 2)*begin_dy + 0.00119192 *lens_ipow(begin_y, 3) + 1.13719 *begin_x*begin_dx*begin_dy + 0.0644392 *begin_x*begin_y*begin_dx + 0.0302182 *lens_ipow(begin_x, 2)*begin_dy + 0.00119276 *lens_ipow(begin_x, 2)*begin_y + 0.00167998 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.00138992 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 4.98425e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 2.90685e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -0.0392615 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 0.00075907 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -4.69719e-09 *lens_ipow(begin_y, 7) + 4.68483e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + 8.88838e-09 *lens_ipow(begin_y, 7)*begin_lambda + -1.70326 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 5) + 6.10699e-07 *lens_ipow(begin_y, 6)*begin_dy*lens_ipow(begin_lambda, 3) + 1.52515e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 1.48252e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*lens_ipow(begin_dy, 2) + 7.24271e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 23.0154  + 0.370786 *lens_ipow(begin_lambda, 2) + 4.63789 *lens_ipow(begin_dy, 2) + 13.9642 *lens_ipow(begin_dx, 2) + 1.18214 *begin_y*begin_dy + 0.0311629 *lens_ipow(begin_y, 2) + 3.70175 *begin_x*begin_dx + 0.0988237 *lens_ipow(begin_x, 2) + -0.00108664 *lens_ipow(begin_y, 3)*begin_dy + -2.76434e-05 *lens_ipow(begin_y, 4) + -0.00034049 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.27477e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dy + -0.000773095 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy*begin_lambda + -2.51287e-11 *lens_ipow(begin_x, 9)*begin_dx+0.0f;
    dx1_domega0(0, 1) =  + 9.27579 *begin_dx*begin_dy + 1.18214 *begin_y*begin_dx + 1.39298 *begin_x*begin_dy + 0.0685757 *begin_x*begin_y + -0.00108664 *lens_ipow(begin_y, 3)*begin_dx + 0.00140376 *begin_x*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 1.97859e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 4.73509e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -2.27477e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 1.58705e-05 *lens_ipow(begin_x, 5)*begin_dy + -0.000386548 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.00402347 *lens_ipow(begin_x, 3)*begin_dy*lens_ipow(begin_lambda, 6)+0.0f;
    dx1_domega0(1, 0) =  + 9.02417 *begin_dx*begin_dy + 1.23868 *begin_y*begin_dx + 1.13719 *begin_x*begin_dy + 0.0644392 *begin_x*begin_y + 0.00335996 *lens_ipow(begin_y, 3)*begin_dx + -0.00138992 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 4.98425e-05 *begin_x*lens_ipow(begin_y, 3) + 2.90685e-05 *lens_ipow(begin_x, 3)*begin_y + -0.117785 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -6.81305 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 5) + 1.48252e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + 1.44854e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*begin_dx*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 22.8925  + 0.435732 *begin_lambda + 13.9316 *lens_ipow(begin_dy, 2) + 4.51208 *lens_ipow(begin_dx, 2) + 3.66717 *begin_y*begin_dy + 0.0975939 *lens_ipow(begin_y, 2) + 1.13719 *begin_x*begin_dx + 0.0302182 *lens_ipow(begin_x, 2) + -0.00138992 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.00151814 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 9.36965e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy + 6.10699e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_lambda, 3) + 3.05029e-05 *lens_ipow(begin_y, 5)*begin_dy*lens_ipow(begin_lambda, 4) + 2.96505e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + 7.24271e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)+0.0f;
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
    out(0) =  + 21.4102 *begin_dx + -0.0787327 *begin_x + 1.27236 *begin_dx*begin_lambda + -0.00752615 *begin_x*begin_lambda + -0.925817 *begin_dx*lens_ipow(begin_lambda, 2) + -4.20676 *begin_dx*lens_ipow(begin_dy, 2) + -3.89788 *lens_ipow(begin_dx, 3) + 0.505644 *begin_y*begin_dx*begin_dy + 0.0274011 *lens_ipow(begin_y, 2)*begin_dx + 0.362863 *begin_x*lens_ipow(begin_dy, 2) + 0.887677 *begin_x*lens_ipow(begin_dx, 2) + 0.0559931 *begin_x*begin_y*begin_dy + 0.00150315 *begin_x*lens_ipow(begin_y, 2) + 0.0823746 *lens_ipow(begin_x, 2)*begin_dx + 0.00149962 *lens_ipow(begin_x, 3) + 0.0124433 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.000767625 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.00392392 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + -2.43517e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.000200768 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 3) + 4.62921e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.4778e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 1.03392e-05 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + 0.0387103 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 5)*begin_lambda + -4.43558e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx*begin_lambda + 2.83885e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2)*begin_lambda + -3.09876e-12 *begin_x*lens_ipow(begin_y, 8) + -1.00785e-08 *lens_ipow(begin_x, 7)*lens_ipow(begin_dx, 2);
    out(1) =  + 21.4312 *begin_dy + -0.0766241 *begin_y + 1.20813 *begin_dy*begin_lambda + -0.00930579 *begin_y*begin_lambda + -0.878772 *begin_dy*lens_ipow(begin_lambda, 2) + -4.23132 *lens_ipow(begin_dy, 3) + -4.37573 *lens_ipow(begin_dx, 2)*begin_dy + 0.84176 *begin_y*lens_ipow(begin_dy, 2) + 0.349106 *begin_y*lens_ipow(begin_dx, 2) + 0.0827994 *lens_ipow(begin_y, 2)*begin_dy + 0.00148358 *lens_ipow(begin_y, 3) + 0.492672 *begin_x*begin_dx*begin_dy + 0.0554535 *begin_x*begin_y*begin_dx + 0.0273003 *lens_ipow(begin_x, 2)*begin_dy + 0.00147724 *lens_ipow(begin_x, 2)*begin_y + 3.21196e-07 *lens_ipow(begin_y, 5)*begin_lambda + 0.00158045 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0105345 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4) + -4.21758e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -0.0293738 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + 0.000106049 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*begin_dy + -1.33968e-06 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2)*begin_dy + -0.000302831 *begin_x*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + 0.000386308 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.33518e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 1.55424 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 7)*begin_lambda + 0.00107161 *begin_x*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 5) + 9.62262e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4);
    out(2) =  + -0.231039 *begin_dx + -0.045184 *begin_x + 0.000710693 *begin_x*begin_lambda + 0.307401 *begin_dx*lens_ipow(begin_dy, 2) + 0.315218 *lens_ipow(begin_dx, 3) + 0.0166482 *begin_y*begin_dx*begin_dy + 0.000339549 *lens_ipow(begin_y, 2)*begin_dx + 0.00885783 *begin_x*lens_ipow(begin_dy, 2) + 0.0275613 *begin_x*lens_ipow(begin_dx, 2) + 0.000239599 *begin_x*begin_y*begin_dy + 3.28932e-05 *begin_x*lens_ipow(begin_y, 2) + 0.000572291 *lens_ipow(begin_x, 2)*begin_dx + 3.39655e-05 *lens_ipow(begin_x, 3) + -0.00434139 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + -0.00524647 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 2.4652e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 7.24006 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 4.31178e-06 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.124387 *begin_x*lens_ipow(begin_dx, 6)*begin_lambda + 3.88291e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6)*begin_dx + 4.44024e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 7.51292e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3)*begin_lambda + 7.81234e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.3386e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 4)*begin_lambda + -1.24505e-12 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2)*begin_lambda + -3.97407e-13 *lens_ipow(begin_x, 9)*begin_lambda + -0.011121 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + 2.67507e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5);
    out(3) =  + -0.229785 *begin_dy + -0.0451151 *begin_y + 0.000603328 *begin_y*begin_lambda + 0.287859 *lens_ipow(begin_dy, 3) + 0.278624 *lens_ipow(begin_dx, 2)*begin_dy + 0.0254983 *begin_y*lens_ipow(begin_dy, 2) + 0.005402 *begin_y*lens_ipow(begin_dx, 2) + 0.000613212 *lens_ipow(begin_y, 2)*begin_dy + 3.43692e-05 *lens_ipow(begin_y, 3) + 0.015178 *begin_x*begin_dx*begin_dy + 0.000253386 *lens_ipow(begin_x, 2)*begin_dy + 3.17325e-05 *lens_ipow(begin_x, 2)*begin_y + 0.000232509 *begin_x*begin_y*begin_dx*begin_lambda + 1.39547e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00039424 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -0.0439566 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.00943941 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -1.93589e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 6.90505e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 2.12163e-09 *lens_ipow(begin_x, 6)*begin_dy + 2.7775e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)*begin_lambda + -1.78018e-10 *lens_ipow(begin_y, 7)*begin_lambda + -6.08221e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3)*begin_lambda + -7.76845e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -3.90188 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)*begin_lambda + -2.96768e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 1.85664e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 2.09235e-07 *lens_ipow(begin_x, 6)*lens_ipow(begin_dy, 5);
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
    domega2_dx0(0, 0) =  + -0.045184  + 0.000710693 *begin_lambda + 0.00885783 *lens_ipow(begin_dy, 2) + 0.0275613 *lens_ipow(begin_dx, 2) + 0.000239599 *begin_y*begin_dy + 3.28932e-05 *lens_ipow(begin_y, 2) + 0.00114458 *begin_x*begin_dx + 0.000101896 *lens_ipow(begin_x, 2) + -0.00434139 *lens_ipow(begin_dy, 2)*begin_lambda + -0.00524647 *lens_ipow(begin_dx, 2)*begin_lambda + 2.4652e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.124387 *lens_ipow(begin_dx, 6)*begin_lambda + 7.76582e-11 *begin_x*lens_ipow(begin_y, 6)*begin_dx + 1.7761e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 7.81234e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 6.69301e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 4)*begin_lambda + -8.71536e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*begin_lambda + -3.57666e-12 *lens_ipow(begin_x, 8)*begin_lambda + -0.0333631 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + 1.07003e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)+0.0f;
    domega2_dx0(0, 1) =  + 0.0166482 *begin_dx*begin_dy + 0.000679097 *begin_y*begin_dx + 0.000239599 *begin_x*begin_dy + 6.57864e-05 *begin_x*begin_y + 4.9304e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 1.72471e-05 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 2.32975e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx + 4.44024e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3)*begin_dy + 4.50775e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3)*begin_lambda + 3.12494e-05 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -2.4901e-12 *lens_ipow(begin_x, 7)*begin_y*begin_lambda + 5.35014e-07 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 5)+0.0f;
    domega2_dx0(1, 0) =  + 0.015178 *begin_dx*begin_dy + 0.000506772 *begin_x*begin_dy + 6.3465e-05 *begin_x*begin_y + 0.000232509 *begin_y*begin_dx*begin_lambda + 0.00078848 *begin_x*lens_ipow(begin_dy, 3) + -1.93589e-05 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 1.38101e-08 *begin_x*lens_ipow(begin_y, 4)*begin_dy + 1.27298e-08 *lens_ipow(begin_x, 5)*begin_dy + -1.82466e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_lambda + -0.000233054 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -3.90188 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)*begin_lambda + -8.90303e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 7.42655e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 1.25541e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 5)+0.0f;
    domega2_dx0(1, 1) =  + -0.0451151  + 0.000603328 *begin_lambda + 0.0254983 *lens_ipow(begin_dy, 2) + 0.005402 *lens_ipow(begin_dx, 2) + 0.00122642 *begin_y*begin_dy + 0.000103108 *lens_ipow(begin_y, 2) + 3.17325e-05 *lens_ipow(begin_x, 2) + 0.000232509 *begin_x*begin_dx*begin_lambda + 4.18641e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0439566 *lens_ipow(begin_dy, 4)*begin_lambda + 0.0188788 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -5.80768e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 2.76202e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + 1.38875e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2)*begin_lambda + -1.24613e-09 *lens_ipow(begin_y, 6)*begin_lambda + -6.08221e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*begin_lambda + -7.76845e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -8.90303e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 7.42655e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda+0.0f;
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
  out[4] =  + 2.00959 *begin_lambda + -4.37266 *lens_ipow(begin_lambda, 2) + -0.0423814 *lens_ipow(begin_dy, 2) + -0.044001 *lens_ipow(begin_dx, 2) + -0.00252994 *begin_y*begin_dy + -5.99766e-05 *lens_ipow(begin_y, 2) + -0.00216814 *begin_x*begin_dx + -3.57978e-05 *lens_ipow(begin_x, 2) + 4.47903 *lens_ipow(begin_lambda, 3) + -1.77643 *lens_ipow(begin_lambda, 4) + -0.000464373 *begin_x*begin_y*begin_dx*begin_dy + -3.35769e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000585185 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -3.34944e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.86385e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -4.84473e-05 *lens_ipow(begin_x, 3)*begin_dx + -1.09602e-06 *lens_ipow(begin_x, 4) + -3.35653 *lens_ipow(begin_dy, 6) + -2.74921 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -2.95328 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -0.648584 *lens_ipow(begin_dx, 6) + -0.193892 *begin_y*lens_ipow(begin_dy, 5) + -2.27302e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -1.01845e-06 *lens_ipow(begin_y, 5)*begin_dy + -1.36605e-08 *lens_ipow(begin_y, 6) + -1.29215e-12 *lens_ipow(begin_x, 8) + -1.18831e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + -2.26883e-14 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2);
else
  out[4] = 0.0f;
} break;
