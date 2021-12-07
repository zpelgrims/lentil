case kodak__petzval__1948__150mm:
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
       + 114.948 *begin_dx + 0.792735 *begin_x + 1.85549 *begin_dx*begin_lambda + 0.50855 *begin_y*begin_dx*begin_dy + 0.00501251 *begin_x*begin_y*begin_dy + 0.0081405 *lens_ipow(begin_x, 2)*begin_dx + 1.46068 *begin_dx*lens_ipow(begin_dy, 2) + 2.22848e-05 *begin_x*lens_ipow(begin_y, 2) + 1.93605e-05 *lens_ipow(begin_x, 3) + 0.111755 *begin_x*lens_ipow(begin_dy, 2) + 0.609206 *begin_x*lens_ipow(begin_dx, 2) + -1.20317 *begin_dx*lens_ipow(begin_lambda, 2) + -0.145754 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -6.62823e-06 *lens_ipow(begin_x, 3)*begin_lambda + -0.00191456 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.0199996 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 6.32549e-06 *lens_ipow(begin_x, 4)*begin_dx + 1.88619 *begin_x*lens_ipow(begin_dx, 4) + 0.0553309 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -2.95546 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 29.3293 *lens_ipow(begin_dx, 5) + 1.69083e-08 *lens_ipow(begin_x, 5) + -0.0370618 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 7.01953e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000847179 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 4.60613e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.0224274 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 3) + 2.73363e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy,
       + 0.792656 *begin_y + 114.946 *begin_dy + 1.91334 *begin_dy*begin_lambda + 0.112728 *begin_y*lens_ipow(begin_dx, 2) + 0.00803439 *lens_ipow(begin_y, 2)*begin_dy + 0.592699 *begin_y*lens_ipow(begin_dy, 2) + 0.50659 *begin_x*begin_dx*begin_dy + 0.00504931 *begin_x*begin_y*begin_dx + 1.51234 *lens_ipow(begin_dx, 2)*begin_dy + 2.27179e-05 *lens_ipow(begin_x, 2)*begin_y + -1.31753 *begin_dy*lens_ipow(begin_lambda, 2) + 2.0377e-05 *lens_ipow(begin_y, 3) + -0.0850779 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0196468 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + -0.00156488 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -8.22859e-06 *lens_ipow(begin_y, 3)*begin_lambda + 9.92389e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 6.21064e-06 *lens_ipow(begin_y, 4)*begin_dy + 12.3039 *lens_ipow(begin_dy, 5) + 0.0464923 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 4.57202e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + 1.31433 *begin_y*lens_ipow(begin_dy, 4) + -0.0363151 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 1.75412e-08 *lens_ipow(begin_y, 5) + 5.54158e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.000786698 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.0219375 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 2.70638e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 114.948  + 1.85549 *begin_lambda + 0.50855 *begin_y*begin_dy + 0.0081405 *lens_ipow(begin_x, 2) + 1.46068 *lens_ipow(begin_dy, 2) + 1.21841 *begin_x*begin_dx + -1.20317 *lens_ipow(begin_lambda, 2) + -0.291509 *begin_x*begin_dx*begin_lambda + -0.00191456 *lens_ipow(begin_x, 2)*begin_lambda + 0.0199996 *lens_ipow(begin_y, 2)*begin_lambda + 6.32549e-06 *lens_ipow(begin_x, 4) + 7.54478 *begin_x*lens_ipow(begin_dx, 3) + 0.165993 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -8.86637 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 146.646 *lens_ipow(begin_dx, 4) + -0.0370618 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 7.01953e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.00169436 *lens_ipow(begin_x, 3)*begin_dx + 0.0224274 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0(0, 1) =  + 0.50855 *begin_y*begin_dx + 0.00501251 *begin_x*begin_y + 2.92136 *begin_dx*begin_dy + 0.22351 *begin_x*begin_dy + 7.01953e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 9.21227e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 2.73363e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)+0.0f;
    dx1_domega0(1, 0) =  + 0.225456 *begin_y*begin_dx + 0.50659 *begin_x*begin_dy + 0.00504931 *begin_x*begin_y + 3.02468 *begin_dx*begin_dy + 9.92389e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 9.14404e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 2.70638e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)+0.0f;
    dx1_domega0(1, 1) =  + 114.946  + 1.91334 *begin_lambda + 0.00803439 *lens_ipow(begin_y, 2) + 1.1854 *begin_y*begin_dy + 0.50659 *begin_x*begin_dx + 1.51234 *lens_ipow(begin_dx, 2) + -1.31753 *lens_ipow(begin_lambda, 2) + -0.170156 *begin_y*begin_dy*begin_lambda + 0.0196468 *lens_ipow(begin_x, 2)*begin_lambda + -0.00156488 *lens_ipow(begin_y, 2)*begin_lambda + 9.92389e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 6.21064e-06 *lens_ipow(begin_y, 4) + 61.5197 *lens_ipow(begin_dy, 4) + 0.139477 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 5.25731 *begin_y*lens_ipow(begin_dy, 3) + -0.0363151 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 2) + 5.54158e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.0015734 *lens_ipow(begin_y, 3)*begin_dy + 0.0219375 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3)+0.0f;
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
    out(0) =  + 149.956 *begin_dx + 0.558649 *begin_x + -0.0348213 *begin_x*begin_lambda + 0.276403 *begin_y*begin_dx*begin_dy + 0.0120915 *begin_x*begin_y*begin_dy + 0.0160371 *lens_ipow(begin_x, 2)*begin_dx + -74.811 *lens_ipow(begin_dx, 3) + 0.0237644 *begin_x*lens_ipow(begin_lambda, 2) + -76.5267 *begin_dx*lens_ipow(begin_dy, 2) + 5.37991e-05 *begin_x*lens_ipow(begin_y, 2) + 4.33696e-05 *lens_ipow(begin_x, 3) + 0.460964 *begin_x*lens_ipow(begin_dy, 2) + 0.737881 *begin_x*lens_ipow(begin_dx, 2) + 0.0279193 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 6.813e-06 *lens_ipow(begin_x, 4)*begin_dx + 4.30836e-08 *lens_ipow(begin_x, 5) + 2.62191e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.0522355 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 0.000645247 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 91.7907 *begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -3.13554 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 223.091 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 5.30154e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.00109133 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 0.0311577 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 3) + 0.00181675 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + 7.30212e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.45741e-10 *lens_ipow(begin_x, 7)*lens_ipow(begin_lambda, 2);
    out(1) =  + 0.558968 *begin_y + 149.905 *begin_dy + -0.0361421 *begin_y*begin_lambda + 0.462912 *begin_y*lens_ipow(begin_dx, 2) + 0.0166677 *lens_ipow(begin_y, 2)*begin_dy + 0.710287 *begin_y*lens_ipow(begin_dy, 2) + 0.261624 *begin_x*begin_dx*begin_dy + 0.0119965 *begin_x*begin_y*begin_dx + -73.5116 *lens_ipow(begin_dx, 2)*begin_dy + 0.024748 *begin_y*lens_ipow(begin_lambda, 2) + 5.31749e-05 *lens_ipow(begin_x, 2)*begin_y + 5.04809e-05 *lens_ipow(begin_y, 3) + 0.00480087 *lens_ipow(begin_x, 2)*begin_dy + -73.17 *lens_ipow(begin_dy, 3) + 3.81262e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00143101 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 0.209848 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_dy + 3.97899e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + 0.000175076 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 3) + 3.69903e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + 1.96523e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.0018762 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 3) + 0.836481 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + 1.92426e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + 5835.93 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 6.10591e-11 *lens_ipow(begin_y, 8)*begin_dy + 3.76245e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 2) + 1.1952e-15 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 9);
    out(2) =  + -1.41321 *begin_dx + -0.0118588 *begin_x + 9.77412e-05 *begin_x*begin_lambda + 0.0101798 *begin_dx*begin_lambda + -0.0138653 *begin_y*begin_dx*begin_dy + -0.000143162 *begin_x*begin_y*begin_dy + -8.21285e-05 *lens_ipow(begin_x, 2)*begin_dx + 0.864481 *lens_ipow(begin_dx, 3) + -0.618183 *begin_dx*lens_ipow(begin_dy, 2) + -2.7724e-07 *begin_x*lens_ipow(begin_y, 2) + -1.01449e-07 *lens_ipow(begin_x, 3) + -0.00965319 *begin_x*lens_ipow(begin_dy, 2) + -0.000890623 *begin_x*lens_ipow(begin_dx, 2) + -4.8545e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.466668 *lens_ipow(begin_dx, 3)*begin_lambda + -0.254561 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.0261103 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 8.27965e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 2.85492 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 3.17613 *lens_ipow(begin_dx, 5)*begin_lambda + 0.000466553 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 0.0588437 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 0.242757 *begin_y*begin_dx*lens_ipow(begin_dy, 5) + 45.5522 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + -6.72901e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 0.663273 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.00402016 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + 23.9989 *begin_dx*lens_ipow(begin_dy, 6);
    out(3) =  + -0.0118724 *begin_y + -1.41063 *begin_dy + 0.000111561 *begin_y*begin_lambda + -6.8599e-05 *lens_ipow(begin_y, 2)*begin_dy + 0.0215586 *begin_x*begin_dx*begin_dy + -8.7764e-06 *begin_x*begin_y*begin_dx + 2.19559 *lens_ipow(begin_dx, 2)*begin_dy + 8.02004e-08 *lens_ipow(begin_x, 2)*begin_y + 0.00795387 *begin_dy*lens_ipow(begin_lambda, 2) + 4.61171e-05 *lens_ipow(begin_x, 2)*begin_dy + 0.796527 *lens_ipow(begin_dy, 3) + 0.0045424 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -0.207124 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.321692 *lens_ipow(begin_dy, 3)*begin_lambda + 1.53575 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -6.04804e-08 *lens_ipow(begin_y, 4)*begin_dy + 1.69251 *lens_ipow(begin_dy, 5) + -0.00519281 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000143928 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.0257487 *begin_y*lens_ipow(begin_dy, 4) + -3.05579e-10 *lens_ipow(begin_y, 5) + -5.26075e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.00235783 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.0413619 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0363723 *begin_x*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -2.27617 *lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + -6.13009e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -7.56777e-11 *begin_x*lens_ipow(begin_y, 5)*begin_dx*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0118588  + 9.77412e-05 *begin_lambda + -0.000143162 *begin_y*begin_dy + -0.000164257 *begin_x*begin_dx + -2.7724e-07 *lens_ipow(begin_y, 2) + -3.04347e-07 *lens_ipow(begin_x, 2) + -0.00965319 *lens_ipow(begin_dy, 2) + -0.000890623 *lens_ipow(begin_dx, 2) + 0.000933105 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + 0.0588437 *lens_ipow(begin_dx, 4)*begin_lambda + -1.3458e-05 *begin_x*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + 0.663273 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4) + -0.00402016 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4)+0.0f;
    domega2_dx0(0, 1) =  + -0.0138653 *begin_dx*begin_dy + -0.000143162 *begin_x*begin_dy + -5.54481e-07 *begin_x*begin_y + -9.709e-05 *begin_y*begin_dx + 0.0261103 *lens_ipow(begin_dx, 3)*begin_dy + 0.000165593 *begin_y*lens_ipow(begin_dx, 3) + 0.242757 *begin_dx*lens_ipow(begin_dy, 5) + -6.72901e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(1, 0) =  + 0.0215586 *begin_dx*begin_dy + -8.7764e-06 *begin_y*begin_dx + 1.60401e-07 *begin_x*begin_y + 9.22343e-05 *begin_x*begin_dy + -0.0363723 *lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -6.13009e-06 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -7.56777e-11 *lens_ipow(begin_y, 5)*begin_dx*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.0118724  + 0.000111561 *begin_lambda + -0.000137198 *begin_y*begin_dy + -8.7764e-06 *begin_x*begin_dx + 8.02004e-08 *lens_ipow(begin_x, 2) + 0.0045424 *lens_ipow(begin_dx, 2)*begin_lambda + -2.41922e-07 *lens_ipow(begin_y, 3)*begin_dy + -0.00519281 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.000287857 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0257487 *lens_ipow(begin_dy, 4) + -1.52789e-09 *lens_ipow(begin_y, 4) + -1.57823e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00235783 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.0413619 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.22602e-05 *begin_x*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -3.78388e-10 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_lambda+0.0f;
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
  out[4] =  + 0.454524  + 1.26115 *begin_lambda + 0.000132196 *begin_y*begin_dy + 0.000130271 *begin_x*begin_dx + 1.64317e-06 *lens_ipow(begin_y, 2) + 1.598e-06 *lens_ipow(begin_x, 2) + -2.61969 *lens_ipow(begin_lambda, 2) + 2.56 *lens_ipow(begin_lambda, 3) + -0.969629 *lens_ipow(begin_lambda, 4) + -0.235216 *lens_ipow(begin_dx, 4) + -0.0158847 *begin_y*lens_ipow(begin_dy, 3) + -0.000148206 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0158685 *begin_x*lens_ipow(begin_dx, 3) + -0.472377 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -5.55713e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.234833 *lens_ipow(begin_dy, 4) + -5.56982e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -5.28725e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.57359e-08 *lens_ipow(begin_y, 4) + -0.000436172 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.016181 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -5.40137e-06 *lens_ipow(begin_x, 3)*begin_dx + -0.000437067 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0160635 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -2.55848e-08 *lens_ipow(begin_x, 4) + -0.000599701 *begin_x*begin_y*begin_dx*begin_dy + -0.00014696 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -5.41414e-06 *lens_ipow(begin_y, 3)*begin_dy;
else
  out[4] = 0.0f;
} break;
