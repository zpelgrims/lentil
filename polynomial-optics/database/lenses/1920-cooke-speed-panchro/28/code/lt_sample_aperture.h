case cooke__speed_panchro__1920__28mm:
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
       + 19.8129 *begin_dx + 0.640924 *begin_x + 0.0965361 *begin_x*begin_lambda + 1.50609 *begin_dx*begin_lambda + -0.48781 *begin_y*begin_dx*begin_dy + -0.00324407 *begin_x*begin_y*begin_dy + -15.391 *lens_ipow(begin_dx, 3) + -0.067604 *begin_x*lens_ipow(begin_lambda, 2) + -16.0199 *begin_dx*lens_ipow(begin_dy, 2) + 4.38112e-05 *begin_x*lens_ipow(begin_y, 2) + 9.94036e-05 *lens_ipow(begin_x, 3) + -0.307563 *begin_x*lens_ipow(begin_dy, 2) + -0.719018 *begin_x*lens_ipow(begin_dx, 2) + -0.987495 *begin_dx*lens_ipow(begin_lambda, 3) + 2.87285e-05 *lens_ipow(begin_x, 4)*begin_dx + 0.0274781 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 3.41056 *begin_dx*lens_ipow(begin_dy, 4) + 0.105882 *begin_x*lens_ipow(begin_dy, 4) + 0.00176267 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.0433554 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.0245752 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.0375873 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 12.931 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -1.46515e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 5.00433e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -5.19912e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 2) + 2.43356e-10 *lens_ipow(begin_x, 7)*begin_lambda + 3.60723e-08 *begin_x*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3),
       + 0.661276 *begin_y + 19.945 *begin_dy + 1.27938 *begin_dy*begin_lambda + 0.0203018 *begin_y*begin_lambda + -0.264987 *begin_y*lens_ipow(begin_dx, 2) + -0.714263 *begin_y*lens_ipow(begin_dy, 2) + -0.357394 *begin_x*begin_dx*begin_dy + -14.8764 *lens_ipow(begin_dx, 2)*begin_dy + 0.000136979 *lens_ipow(begin_x, 2)*begin_y + -0.644039 *begin_dy*lens_ipow(begin_lambda, 2) + 0.00320034 *lens_ipow(begin_x, 2)*begin_dy + -15.5046 *lens_ipow(begin_dy, 3) + 0.00030178 *lens_ipow(begin_y, 3)*begin_lambda + -0.0186201 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.647917 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 3.67308 *lens_ipow(begin_dy, 5) + -1.04139 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.0124336 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 8.1868e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -0.0363426 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -0.000249229 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -0.000572361 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.000131582 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -4.46407e-10 *lens_ipow(begin_y, 7) + -1.29196e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 1.98165 *begin_y*lens_ipow(begin_dx, 6)*begin_lambda + -4.11886e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3) + -6.23152 *begin_y*lens_ipow(begin_dx, 8)*lens_ipow(begin_lambda, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 19.8129  + 1.50609 *begin_lambda + -0.48781 *begin_y*begin_dy + -46.1729 *lens_ipow(begin_dx, 2) + -16.0199 *lens_ipow(begin_dy, 2) + -1.43804 *begin_x*begin_dx + -0.987495 *lens_ipow(begin_lambda, 3) + 2.87285e-05 *lens_ipow(begin_x, 4) + 0.0824344 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 3.41056 *lens_ipow(begin_dy, 4) + 0.00352534 *lens_ipow(begin_x, 3)*begin_dx + 0.0867108 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + -0.0737255 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.0375873 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 38.7931 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.46515e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy + -1.03982e-06 *lens_ipow(begin_x, 5)*begin_dx+0.0f;
    dx1_domega0(0, 1) =  + -0.48781 *begin_y*begin_dx + -0.00324407 *begin_x*begin_y + -32.0397 *begin_dx*begin_dy + -0.615126 *begin_x*begin_dy + 13.6422 *begin_dx*lens_ipow(begin_dy, 3) + 0.42353 *begin_x*lens_ipow(begin_dy, 3) + 0.0433554 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.0751747 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda + 25.8621 *lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -1.46515e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 5.00433e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 1.08217e-07 *begin_x*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 0) =  + -0.529974 *begin_y*begin_dx + -0.357394 *begin_x*begin_dy + -29.7527 *begin_dx*begin_dy + -0.0372403 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -1.94375 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -1.04139 *begin_x*lens_ipow(begin_dy, 3) + -0.0248672 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 8.1868e-06 *lens_ipow(begin_x, 3)*begin_y + 11.8899 *begin_y*lens_ipow(begin_dx, 5)*begin_lambda + -49.8522 *begin_y*lens_ipow(begin_dx, 7)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(1, 1) =  + 19.945  + 1.27938 *begin_lambda + -1.42853 *begin_y*begin_dy + -0.357394 *begin_x*begin_dx + -14.8764 *lens_ipow(begin_dx, 2) + -0.644039 *lens_ipow(begin_lambda, 2) + 0.00320034 *lens_ipow(begin_x, 2) + -46.5137 *lens_ipow(begin_dy, 2) + -0.0186201 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.647917 *begin_x*lens_ipow(begin_dx, 3) + 18.3654 *lens_ipow(begin_dy, 4) + -3.12418 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0124336 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.109028 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.00114472 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.000263165 *lens_ipow(begin_y, 3)*begin_dy+0.0f;
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
    out(0) =  + 27.8383 *begin_dx + 0.595687 *begin_x + 0.0148683 *begin_x*begin_lambda + 0.659879 *begin_y*begin_dx*begin_dy + 0.104668 *begin_x*begin_y*begin_dy + 0.122813 *lens_ipow(begin_x, 2)*begin_dx + -10.5908 *lens_ipow(begin_dx, 3) + -6.96045 *begin_dx*lens_ipow(begin_dy, 2) + 0.00204667 *begin_x*lens_ipow(begin_y, 2) + 0.00191469 *lens_ipow(begin_x, 3) + 1.10243 *begin_x*lens_ipow(begin_dy, 2) + 1.44899 *begin_x*lens_ipow(begin_dx, 2) + 0.0324941 *lens_ipow(begin_y, 2)*begin_dx + 0.000787065 *lens_ipow(begin_x, 4)*begin_dx + 0.334931 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 6.49117e-06 *lens_ipow(begin_x, 5) + -0.0229346 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.0160717 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 0.0286274 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -0.371926 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 301.208 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + -6.17754e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -1.41929e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -1.50167e-09 *begin_x*lens_ipow(begin_y, 6) + 9.78954e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + 63.9036 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + -1.0463e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*begin_dx + -2.03353e-08 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 2);
    out(1) =  + 0.604681 *begin_y + 27.8262 *begin_dy + 1.08698 *begin_y*lens_ipow(begin_dx, 2) + 0.121737 *lens_ipow(begin_y, 2)*begin_dy + 1.44704 *begin_y*lens_ipow(begin_dy, 2) + 0.636282 *begin_x*begin_dx*begin_dy + 0.101806 *begin_x*begin_y*begin_dx + -6.55007 *lens_ipow(begin_dx, 2)*begin_dy + 0.0019849 *lens_ipow(begin_x, 2)*begin_y + 0.00174784 *lens_ipow(begin_y, 3) + 0.031855 *lens_ipow(begin_x, 2)*begin_dy + -10.3553 *lens_ipow(begin_dy, 3) + 0.00022311 *lens_ipow(begin_y, 3)*begin_lambda + 0.239601 *begin_y*lens_ipow(begin_dx, 4) + 0.00148129 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.052592 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 1.2853e-05 *lens_ipow(begin_y, 5)*begin_lambda + -0.0316303 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.605555 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 9.70402e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + -3.47803e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -2.18372e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 147.51 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5)*begin_lambda + -2.02594e-08 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2) + -5.27788e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3) + 795.992 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3) + 5.81649e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + 2.18248e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7);
    out(2) =  + -1.57143 *begin_dx + -0.0699663 *begin_x + -0.0849431 *begin_y*begin_dx*begin_dy + -0.00620778 *begin_x*begin_y*begin_dy + -0.00239029 *lens_ipow(begin_x, 2)*begin_dx + 0.985601 *lens_ipow(begin_dx, 3) + -0.925382 *begin_dx*lens_ipow(begin_dy, 2) + -6.31365e-05 *begin_x*lens_ipow(begin_y, 2) + -1.31428e-05 *lens_ipow(begin_x, 3) + -0.0870234 *begin_x*lens_ipow(begin_dy, 2) + -0.00112892 *lens_ipow(begin_y, 2)*begin_dx + -4.40054e-06 *lens_ipow(begin_x, 3)*begin_lambda + 0.0354808 *begin_x*lens_ipow(begin_dx, 4) + -4.36937e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.00627477 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.117709 *begin_y*begin_dx*lens_ipow(begin_dy, 5) + 0.0411319 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4) + 1.40639 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 5.52574e-11 *lens_ipow(begin_x, 7) + -0.0481005 *begin_x*begin_y*lens_ipow(begin_dx, 6)*begin_dy + 0.000991143 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 6) + 8.85543e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2) + 7.24101e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6) + -8.46573e-07 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 4) + 0.0264208 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 7) + 45.2801 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 6)*begin_lambda + -4.09106e-09 *lens_ipow(begin_x, 6)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -5.6934e-11 *begin_x*lens_ipow(begin_y, 7)*lens_ipow(begin_dy, 3);
    out(3) =  + -0.0699705 *begin_y + -1.56885 *begin_dy + 0.00240701 *begin_y*lens_ipow(begin_dx, 2) + -0.00212692 *lens_ipow(begin_y, 2)*begin_dy + 0.178989 *begin_x*begin_dx*begin_dy + 2.83011 *lens_ipow(begin_dx, 2)*begin_dy + 3.41162e-05 *lens_ipow(begin_x, 2)*begin_y + -9.50389e-06 *lens_ipow(begin_y, 3) + 0.00296542 *lens_ipow(begin_x, 2)*begin_dy + 0.846298 *lens_ipow(begin_dy, 3) + 0.00922829 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.179242 *lens_ipow(begin_dy, 3)*begin_lambda + -7.07097e-06 *lens_ipow(begin_y, 3)*begin_lambda + -2.39927e-08 *lens_ipow(begin_x, 4)*begin_y*begin_lambda + -2.31143e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.000247202 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0150896 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + 0.000459655 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 4) + 0.0177636 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + -0.000538585 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + -2.44652e-09 *lens_ipow(begin_x, 6)*begin_dy + 0.0910585 *begin_y*lens_ipow(begin_dy, 6) + 0.00905176 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5)*begin_lambda + 2.14112e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_dy, 3) + 0.195073 *begin_y*lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2) + 2.72611e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 2.12094e-13 *lens_ipow(begin_y, 9)*begin_lambda + 5.05412e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 6);
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
    domega2_dx0(0, 0) =  + -0.0699663  + -0.00620778 *begin_y*begin_dy + -0.00478057 *begin_x*begin_dx + -6.31365e-05 *lens_ipow(begin_y, 2) + -3.94284e-05 *lens_ipow(begin_x, 2) + -0.0870234 *lens_ipow(begin_dy, 2) + -1.32016e-05 *lens_ipow(begin_x, 2)*begin_lambda + 0.0354808 *lens_ipow(begin_dx, 4) + -0.000131081 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.0822638 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + 1.40639 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 3.86802e-10 *lens_ipow(begin_x, 6) + -0.0481005 *begin_y*lens_ipow(begin_dx, 6)*begin_dy + 0.00297343 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 6) + 6.1988e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2) + 2.1723e-12 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6) + -8.46573e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 4) + -2.45464e-08 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -5.6934e-11 *lens_ipow(begin_y, 7)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(0, 1) =  + -0.0849431 *begin_dx*begin_dy + -0.00620778 *begin_x*begin_dy + -0.000126273 *begin_x*begin_y + -0.00225784 *begin_y*begin_dx + 0.0125495 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.117709 *begin_dx*lens_ipow(begin_dy, 5) + -0.0481005 *begin_x*lens_ipow(begin_dx, 6)*begin_dy + 1.77109e-12 *lens_ipow(begin_x, 7)*begin_y + 4.34461e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + -3.38629e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + 0.0528416 *begin_y*lens_ipow(begin_dx, 7) + -4.09106e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 3)*begin_dy + -3.98538e-10 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.178989 *begin_dx*begin_dy + 6.82324e-05 *begin_x*begin_y + 0.00593085 *begin_x*begin_dy + -9.59708e-08 *lens_ipow(begin_x, 3)*begin_y*begin_lambda + -6.93429e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.0150896 *begin_y*begin_dx*lens_ipow(begin_dy, 4) + 0.00091931 *begin_x*begin_y*lens_ipow(begin_dy, 4) + 0.0355272 *begin_x*lens_ipow(begin_dy, 5) + -0.000538585 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + -1.46791e-08 *lens_ipow(begin_x, 5)*begin_dy + 1.28467e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 3) + 1.09044e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.0699705  + 0.00240701 *lens_ipow(begin_dx, 2) + -0.00425384 *begin_y*begin_dy + 3.41162e-05 *lens_ipow(begin_x, 2) + -2.85117e-05 *lens_ipow(begin_y, 2) + 0.00922829 *lens_ipow(begin_dy, 2)*begin_lambda + -2.12129e-05 *lens_ipow(begin_y, 2)*begin_lambda + -2.39927e-08 *lens_ipow(begin_x, 4)*begin_lambda + -2.31143e-05 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + -0.000741605 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0150896 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + 0.000459655 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + -0.00107717 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.0910585 *lens_ipow(begin_dy, 6) + 0.0181035 *begin_y*lens_ipow(begin_dy, 5)*begin_lambda + 0.195073 *lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2) + 5.45221e-08 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 3) + 1.90885e-12 *lens_ipow(begin_y, 8)*begin_lambda + 2.52706e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 6)+0.0f;
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
  out[4] =  + 0.560998  + 0.231557 *begin_lambda + 0.00652273 *begin_y*begin_dy + 0.00645543 *begin_x*begin_dx + 0.000112642 *lens_ipow(begin_y, 2) + 0.110813 *lens_ipow(begin_dy, 2) + 0.000111405 *lens_ipow(begin_x, 2) + 0.109588 *lens_ipow(begin_dx, 2) + -0.158276 *lens_ipow(begin_lambda, 2) + -4.98724 *lens_ipow(begin_dx, 4) + -0.608701 *begin_y*lens_ipow(begin_dy, 3) + -0.0106808 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.607388 *begin_x*lens_ipow(begin_dx, 3) + -9.98726 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000781654 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -4.99687 *lens_ipow(begin_dy, 4) + -0.000780754 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -1.56037e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -7.86212e-06 *lens_ipow(begin_y, 4) + -0.0313604 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.606937 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000783458 *lens_ipow(begin_x, 3)*begin_dx + -0.0314458 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.607732 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -7.82723e-06 *lens_ipow(begin_x, 4) + -0.0412211 *begin_x*begin_y*begin_dx*begin_dy + -0.0107129 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000786224 *lens_ipow(begin_y, 3)*begin_dy;
else
  out[4] = 0.0f;
} break;
