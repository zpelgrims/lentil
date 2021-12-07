case asahi__takumar__1969__65mm:
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
       + 39.5196 *begin_dx + 0.334219 *begin_x + 8.04654 *begin_dx*begin_lambda + 0.188519 *begin_x*begin_lambda + -5.51125 *begin_dx*lens_ipow(begin_lambda, 2) + -22.768 *begin_dx*lens_ipow(begin_dy, 2) + -22.5418 *lens_ipow(begin_dx, 3) + -0.132458 *begin_y*begin_dx*begin_dy + 0.00159413 *lens_ipow(begin_y, 2)*begin_dx + -0.130241 *begin_x*lens_ipow(begin_lambda, 2) + -0.165402 *begin_x*lens_ipow(begin_dy, 2) + -0.275309 *begin_x*lens_ipow(begin_dx, 2) + 0.00123938 *begin_x*begin_y*begin_dy + -8.73446e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00283016 *lens_ipow(begin_x, 2)*begin_dx + -7.57708e-05 *lens_ipow(begin_x, 3) + -0.279459 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.00658781 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.245526 *begin_x*lens_ipow(begin_dy, 4) + -0.00956435 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -5.69623e-08 *lens_ipow(begin_x, 5) + 0.134774 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -6.4667e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 2.23749e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*lens_ipow(begin_lambda, 2),
       + 39.7272 *begin_dy + 0.336227 *begin_y + 7.57255 *begin_dy*begin_lambda + 0.18659 *begin_y*begin_lambda + -5.22297 *begin_dy*lens_ipow(begin_lambda, 2) + -23.4536 *lens_ipow(begin_dy, 3) + -22.7883 *lens_ipow(begin_dx, 2)*begin_dy + -0.128843 *begin_y*lens_ipow(begin_lambda, 2) + -0.278117 *begin_y*lens_ipow(begin_dy, 2) + -0.164536 *begin_y*lens_ipow(begin_dx, 2) + 0.00277422 *lens_ipow(begin_y, 2)*begin_dy + -9.49952e-05 *lens_ipow(begin_y, 3) + -0.141509 *begin_x*begin_dx*begin_dy + 0.00125947 *begin_x*begin_y*begin_dx + -9.45247e-05 *lens_ipow(begin_x, 2)*begin_y + 0.00288068 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.247988 *begin_y*lens_ipow(begin_dx, 4) + -0.00865712 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 7.79017 *lens_ipow(begin_dy, 5)*begin_lambda + 0.12234 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + -0.0215547 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -37.7425 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + -3.34291e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 3.37208e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 39.5196  + 8.04654 *begin_lambda + -5.51125 *lens_ipow(begin_lambda, 2) + -22.768 *lens_ipow(begin_dy, 2) + -67.6254 *lens_ipow(begin_dx, 2) + -0.132458 *begin_y*begin_dy + 0.00159413 *lens_ipow(begin_y, 2) + -0.550617 *begin_x*begin_dx + 0.00283016 *lens_ipow(begin_x, 2) + -0.279459 *begin_y*lens_ipow(begin_dy, 3) + -0.0197634 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00956435 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.539097 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + -45.5359 *begin_dx*begin_dy + -0.132458 *begin_y*begin_dx + -0.330805 *begin_x*begin_dy + 0.00123938 *begin_x*begin_y + -0.838377 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.982105 *begin_x*lens_ipow(begin_dy, 3) + -0.0191287 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.134774 *begin_x*begin_y*lens_ipow(begin_dx, 4)+0.0f;
    dx1_domega0(1, 0) =  + -45.5767 *begin_dx*begin_dy + -0.329073 *begin_y*begin_dx + -0.141509 *begin_x*begin_dy + 0.00125947 *begin_x*begin_y + 0.991952 *begin_y*lens_ipow(begin_dx, 3) + -0.0173142 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.12234 *begin_x*begin_y*lens_ipow(begin_dy, 4) + -188.712 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)+0.0f;
    dx1_domega0(1, 1) =  + 39.7272  + 7.57255 *begin_lambda + -5.22297 *lens_ipow(begin_lambda, 2) + -70.3608 *lens_ipow(begin_dy, 2) + -22.7883 *lens_ipow(begin_dx, 2) + -0.556234 *begin_y*begin_dy + 0.00277422 *lens_ipow(begin_y, 2) + -0.141509 *begin_x*begin_dx + 0.00288068 *lens_ipow(begin_x, 2)*begin_lambda + -0.00865712 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 38.9508 *lens_ipow(begin_dy, 4)*begin_lambda + 0.489359 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0646641 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -113.227 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2)+0.0f;
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
    out(0) =  + 64.3915 *begin_dx + -0.122385 *begin_x + 0.838693 *begin_dx*begin_lambda + 0.339505 *begin_x*begin_lambda + -25.4004 *begin_dx*lens_ipow(begin_dy, 2) + -26.2626 *lens_ipow(begin_dx, 3) + 0.0782274 *begin_y*begin_dx*begin_dy + 0.00621154 *lens_ipow(begin_y, 2)*begin_dx + -0.229952 *begin_x*lens_ipow(begin_lambda, 2) + 0.607747 *begin_x*lens_ipow(begin_dx, 2) + 0.0119236 *begin_x*begin_y*begin_dy + -0.00019319 *begin_x*lens_ipow(begin_y, 2) + 0.019495 *lens_ipow(begin_x, 2)*begin_dx + -0.000144502 *lens_ipow(begin_x, 3) + 1.93435 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.0257972 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0207736 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -9.43424e-06 *lens_ipow(begin_x, 4)*begin_dx + -1.7271e-07 *lens_ipow(begin_x, 5) + -6.71147 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 6.0173 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 4.88285e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -5.12168e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -3.24968e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda;
    out(1) =  + 64.4692 *begin_dy + -0.119511 *begin_y + 0.836626 *begin_dy*begin_lambda + 0.338848 *begin_y*begin_lambda + -26.5361 *lens_ipow(begin_dy, 3) + -27.3906 *lens_ipow(begin_dx, 2)*begin_dy + -0.230665 *begin_y*lens_ipow(begin_lambda, 2) + 0.586206 *begin_y*lens_ipow(begin_dy, 2) + 0.0198401 *lens_ipow(begin_y, 2)*begin_dy + -0.000149789 *lens_ipow(begin_y, 3) + 0.0122742 *begin_x*begin_y*begin_dx + 0.00566293 *lens_ipow(begin_x, 2)*begin_dy + -0.000198788 *lens_ipow(begin_x, 2)*begin_y + 1.86069 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -1.96083e-07 *lens_ipow(begin_y, 5) + -6.81709 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -1.47277 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.000556074 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -1.61347e-05 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -1.48202e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_lambda + 6.1512 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -1.43762e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -1.06462e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 0.131763 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5)*begin_lambda;
    out(2) =  + -0.906605 *begin_dx + -0.0138309 *begin_x + -0.00448538 *begin_x*begin_lambda + 0.0817525 *begin_dx*lens_ipow(begin_dy, 2) + 0.402169 *lens_ipow(begin_dx, 3) + 1.18249e-05 *lens_ipow(begin_y, 2)*begin_dx + 0.00316418 *begin_x*lens_ipow(begin_lambda, 2) + -0.000154485 *begin_x*begin_y*begin_dy + 4.12418e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000121704 *lens_ipow(begin_x, 2)*begin_dx + 4.07857e-06 *lens_ipow(begin_x, 3) + -0.023944 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.080944 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.00646414 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 0.00125021 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.0723792 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 3.7094e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.67699e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -2.29058e-10 *lens_ipow(begin_x, 6)*begin_dx + 0.000738641 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 9.83509e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -1.1748e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_lambda + -0.0109977 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 4) + -0.00133644 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2);
    out(3) =  + -0.907499 *begin_dy + -0.0138368 *begin_y + -0.00451251 *begin_y*begin_lambda + 0.407949 *lens_ipow(begin_dy, 3) + 0.837714 *lens_ipow(begin_dx, 2)*begin_dy + 0.00319621 *begin_y*lens_ipow(begin_lambda, 2) + -0.00586501 *begin_y*lens_ipow(begin_dx, 2) + -0.000108321 *lens_ipow(begin_y, 2)*begin_dy + 4.17557e-06 *lens_ipow(begin_y, 3) + 0.0127144 *begin_x*begin_dx*begin_dy + -0.000151866 *begin_x*begin_y*begin_dx + 3.97356e-06 *lens_ipow(begin_x, 2)*begin_y + 3.83841e-05 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -0.587039 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.806776 *lens_ipow(begin_dx, 4)*begin_dy + -3.46288e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.0175388 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.000221662 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -1.0853e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -2.33706e-10 *lens_ipow(begin_y, 6)*begin_dy + 7.31741e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 2.81052e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 0.00578884 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -2.96472e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0138309  + -0.00448538 *begin_lambda + 0.00316418 *lens_ipow(begin_lambda, 2) + -0.000154485 *begin_y*begin_dy + 4.12418e-06 *lens_ipow(begin_y, 2) + -0.000243408 *begin_x*begin_dx + 1.22357e-05 *lens_ipow(begin_x, 2) + -0.023944 *lens_ipow(begin_dy, 2)*begin_lambda + 0.080944 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.00646414 *lens_ipow(begin_dx, 4)*begin_lambda + -0.0723792 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 7.4188e-08 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -5.03096e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.37435e-09 *lens_ipow(begin_x, 5)*begin_dx + 0.000738641 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 4.91754e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -5.87401e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_lambda + -0.00400931 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(0, 1) =  + 2.36499e-05 *begin_y*begin_dx + -0.000154485 *begin_x*begin_dy + 8.24836e-06 *begin_x*begin_y + 0.00250042 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 1.11282e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -1.67699e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_dy + 0.00147728 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + 3.93404e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3) + -4.69921e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_lambda + -0.0219954 *begin_y*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 4)+0.0f;
    domega2_dx0(1, 0) =  + 0.0127144 *begin_dx*begin_dy + -0.000151866 *begin_y*begin_dx + 7.94711e-06 *begin_x*begin_y + 7.67682e-05 *begin_x*begin_dy*begin_lambda + -0.0175388 *lens_ipow(begin_dx, 3)*begin_dy + 0.000443325 *begin_x*lens_ipow(begin_dy, 3) + -2.1706e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 7.31741e-05 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 1.12421e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -1.18589e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.0138368  + -0.00451251 *begin_lambda + 0.00319621 *lens_ipow(begin_lambda, 2) + -0.00586501 *lens_ipow(begin_dx, 2) + -0.000216642 *begin_y*begin_dy + 1.25267e-05 *lens_ipow(begin_y, 2) + -0.000151866 *begin_x*begin_dx + 3.97356e-06 *lens_ipow(begin_x, 2) + -1.03887e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.1706e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.40224e-09 *lens_ipow(begin_y, 5)*begin_dy + 0.000146348 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + 8.43156e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 0.0115777 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -8.89415e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_lambda+0.0f;
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
  out[4] =  + 2.14127 *begin_lambda + -4.75845 *lens_ipow(begin_lambda, 2) + 0.0132411 *lens_ipow(begin_dy, 2) + 0.0125829 *lens_ipow(begin_dx, 2) + 4.96095 *lens_ipow(begin_lambda, 3) + -1.99734 *lens_ipow(begin_lambda, 4) + -0.514546 *lens_ipow(begin_dy, 4) + -1.02535 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.506941 *lens_ipow(begin_dx, 4) + -0.0183329 *begin_y*lens_ipow(begin_dy, 3) + -0.0184655 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000411549 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000155501 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0183739 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0180057 *begin_x*lens_ipow(begin_dx, 3) + -0.000531674 *begin_x*begin_y*begin_dx*begin_dy + -0.000148117 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000406462 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -2.01494e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.90819e-06 *lens_ipow(begin_x, 3)*begin_dx + -2.9431e-06 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -3.46764e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -1.53892e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -3.87169e-11 *lens_ipow(begin_x, 6);
else
  out[4] = 0.0f;
} break;
