case meyer_optik_goerlitz__primoplan__1936__58mm:
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
       + 35.8897 *begin_dx + 0.576039 *begin_x + 0.000685351 *lens_ipow(begin_x, 3) + 2.40303 *begin_x*lens_ipow(begin_dx, 2) + 1.49373 *begin_y*begin_dx*begin_dy + 0.739001 *begin_x*lens_ipow(begin_dy, 2) + 21.7389 *lens_ipow(begin_dx, 3) + 15.4411 *begin_dx*lens_ipow(begin_dy, 2) + 0.0744818 *lens_ipow(begin_x, 2)*begin_dx + 0.0484408 *begin_x*begin_y*begin_dy + 0.0011795 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 0.0424157 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -8.13414e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.000121059 *lens_ipow(begin_x, 4)*begin_dx + 0.058664 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -3.75306e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.000130558 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.0910584 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -31.5165 *lens_ipow(begin_dx, 5) + -7.98964e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 0.119697 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -2.049e-06 *lens_ipow(begin_x, 5) + -3.43656e-06 *begin_x*lens_ipow(begin_y, 4)*begin_lambda + -0.000144558 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_lambda, 3),
       + 0.561308 *begin_y + 36.2185 *begin_dy + 0.04417 *begin_y*begin_lambda + 0.746089 *begin_y*lens_ipow(begin_dx, 2) + 16.272 *lens_ipow(begin_dy, 3) + 2.17322 *begin_y*lens_ipow(begin_dy, 2) + 0.000495692 *lens_ipow(begin_y, 3) + 1.15644 *begin_x*begin_dx*begin_dy + 0.0670934 *lens_ipow(begin_y, 2)*begin_dy + 0.0379861 *begin_x*begin_y*begin_dx + 0.0169686 *lens_ipow(begin_x, 2)*begin_dy + 0.000321073 *lens_ipow(begin_x, 2)*begin_y + 25.6135 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.00016958 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -2.93134e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.00198509 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -8.53176e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -6.01443e-09 *lens_ipow(begin_y, 7) + -7.85671e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -0.0123992 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -0.015491 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + -3.9393e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -1.05785e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -5.14074e-07 *lens_ipow(begin_y, 6)*begin_dy
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 35.8897  + 4.80606 *begin_x*begin_dx + 1.49373 *begin_y*begin_dy + 65.2168 *lens_ipow(begin_dx, 2) + 15.4411 *lens_ipow(begin_dy, 2) + 0.0744818 *lens_ipow(begin_x, 2) + 0.0424157 *lens_ipow(begin_y, 2)*begin_lambda + -0.000121059 *lens_ipow(begin_x, 4) + 0.058664 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000130558 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.273175 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -157.582 *lens_ipow(begin_dx, 4) + 0.239395 *begin_x*begin_y*begin_dx*begin_dy + -0.000144558 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0(0, 1) =  + 1.49373 *begin_y*begin_dx + 1.478 *begin_x*begin_dy + 30.8823 *begin_dx*begin_dy + 0.0484408 *begin_x*begin_y + -8.13414e-05 *lens_ipow(begin_x, 3)*begin_y + 0.117328 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -7.98964e-05 *begin_x*lens_ipow(begin_y, 3) + 0.119697 *begin_x*begin_y*lens_ipow(begin_dx, 2)+0.0f;
    dx1_domega0(1, 0) =  + 1.49218 *begin_y*begin_dx + 1.15644 *begin_x*begin_dy + 0.0379861 *begin_x*begin_y + 51.227 *begin_dx*begin_dy*begin_lambda + -8.53176e-05 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + -0.0123992 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.046473 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -3.9393e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)+0.0f;
    dx1_domega0(1, 1) =  + 36.2185  + 48.8159 *lens_ipow(begin_dy, 2) + 4.34643 *begin_y*begin_dy + 1.15644 *begin_x*begin_dx + 0.0670934 *lens_ipow(begin_y, 2) + 0.0169686 *lens_ipow(begin_x, 2) + 25.6135 *lens_ipow(begin_dx, 2)*begin_lambda + -0.00016958 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00397019 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + -0.0371975 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.015491 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -2.11569e-05 *lens_ipow(begin_y, 5)*begin_dy + -5.14074e-07 *lens_ipow(begin_y, 6)+0.0f;
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
    out(0) =  + 56.2187 *begin_dx + 0.489361 *begin_x + 0.0649287 *begin_x*begin_lambda + 0.0013887 *lens_ipow(begin_x, 3) + 2.43864 *begin_x*lens_ipow(begin_dx, 2) + 1.2327 *begin_y*begin_dx*begin_dy + 1.35248 *begin_x*lens_ipow(begin_dy, 2) + -11.5155 *lens_ipow(begin_dx, 3) + 0.114392 *lens_ipow(begin_x, 2)*begin_dx + 0.00125479 *begin_x*lens_ipow(begin_y, 2) + 0.0751718 *begin_x*begin_y*begin_dy + 0.027654 *lens_ipow(begin_y, 2)*begin_dx + -0.000153648 *lens_ipow(begin_x, 4)*begin_dx + -6.10463e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.0888141 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -2.1939e-06 *begin_x*lens_ipow(begin_y, 4) + -3.46464e-06 *lens_ipow(begin_x, 5) + -7.37159e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -1.03995e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -5.44404e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -0.000154758 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_dy + -6.66224e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -1.65109e-09 *lens_ipow(begin_x, 7)*begin_y*begin_dy*begin_lambda + -0.000201733 *lens_ipow(begin_x, 4)*begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda;
    out(1) =  + 0.606993 *begin_y + 56.8264 *begin_dy + 0.774043 *begin_y*lens_ipow(begin_dx, 2) + -10.5362 *lens_ipow(begin_dy, 3) + 1.90683 *begin_y*lens_ipow(begin_dy, 2) + 0.813514 *begin_x*begin_dx*begin_dy + 0.0891075 *lens_ipow(begin_y, 2)*begin_dy + 0.0623186 *begin_x*begin_y*begin_dx + -12.631 *lens_ipow(begin_dx, 2)*begin_dy + 0.0211618 *lens_ipow(begin_x, 2)*begin_dy + 0.000457857 *lens_ipow(begin_y, 3)*begin_lambda + -4.76257e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.00210009 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -7.59623e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + 1.1563e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -3.14783e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 9.7159e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + -5.0138e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -4.35754e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6)*begin_dy + -0.000160328 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -3.42443e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx + -4.58209e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -1.48395e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)*begin_lambda + -0.000205678 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda;
    out(2) =  + -1.42801 *begin_dx + -0.0315599 *begin_x + -0.03921 *begin_y*begin_dx*begin_dy + -0.0346819 *begin_x*lens_ipow(begin_dy, 2) + -0.708683 *begin_dx*lens_ipow(begin_dy, 2) + -1.50935e-05 *begin_x*lens_ipow(begin_y, 2) + -0.00179976 *begin_x*begin_y*begin_dy + -0.000351971 *lens_ipow(begin_y, 2)*begin_dx + -0.00150909 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 1.57547 *lens_ipow(begin_dx, 3)*begin_lambda + -1.65244e-05 *lens_ipow(begin_x, 3)*begin_lambda + 2.69467e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 1.1585e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 2.11265e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -0.00211411 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 4.64987e-08 *begin_x*lens_ipow(begin_y, 4) + 4.37967e-08 *lens_ipow(begin_x, 5) + 2.32466e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.00415348 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4) + -7.51236e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 6.59296e-09 *lens_ipow(begin_x, 6)*begin_dx*begin_lambda + -5.89104 *lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 4) + 0.00372307 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -6.43453e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3);
    out(3) =  + -0.031682 *begin_y + -1.42523 *begin_dy + 0.782451 *lens_ipow(begin_dy, 3) + 0.0674778 *begin_x*begin_dx*begin_dy + -0.000834132 *lens_ipow(begin_y, 2)*begin_dy + -0.000272704 *begin_x*begin_y*begin_dx + 2.18853 *lens_ipow(begin_dx, 2)*begin_dy + 0.000473905 *lens_ipow(begin_x, 2)*begin_dy + -6.17318e-06 *lens_ipow(begin_y, 3)*begin_lambda + 2.42317e-08 *lens_ipow(begin_x, 4)*begin_y + 1.15996e-10 *lens_ipow(begin_y, 7) + 2.89187e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + 1.22287e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -3.83289e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 3) + 6.66074e-09 *lens_ipow(begin_y, 6)*begin_dy + 3.19905e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 1.25152e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -1.85928e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_lambda + 9.24569e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 2.97772e-09 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_lambda + 8.45591e-07 *begin_x*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + 1.16858e-11 *begin_x*lens_ipow(begin_y, 7)*begin_dx + -8.92544e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + 2.27798e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0315599  + -0.0346819 *lens_ipow(begin_dy, 2) + -1.50935e-05 *lens_ipow(begin_y, 2) + -0.00179976 *begin_y*begin_dy + -0.00301819 *begin_x*begin_dx*begin_lambda + -4.95731e-05 *lens_ipow(begin_x, 2)*begin_lambda + 8.08402e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 3.47551e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 2.11265e-06 *lens_ipow(begin_y, 3)*begin_dy + -0.00211411 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 4.64987e-08 *lens_ipow(begin_y, 4) + 2.18983e-07 *lens_ipow(begin_x, 4) + 4.64932e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -2.25371e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 3.95577e-08 *lens_ipow(begin_x, 5)*begin_dx*begin_lambda + 0.00744614 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -2.57381e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)+0.0f;
    domega2_dx0(0, 1) =  + -0.03921 *begin_dx*begin_dy + -3.0187e-05 *begin_x*begin_y + -0.00179976 *begin_x*begin_dy + -0.000703942 *begin_y*begin_dx + 2.69467e-06 *lens_ipow(begin_x, 3)*begin_dy + 2.31701e-07 *lens_ipow(begin_x, 3)*begin_y + 6.33794e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -0.00211411 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.85995e-07 *begin_x*lens_ipow(begin_y, 3) + 4.64932e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + -0.00830696 *begin_y*begin_dx*lens_ipow(begin_dy, 4) + -1.50247e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2) + 0.00372307 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -1.28691e-07 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0674778 *begin_dx*begin_dy + -0.000272704 *begin_y*begin_dx + 0.000947809 *begin_x*begin_dy + 9.69269e-08 *lens_ipow(begin_x, 3)*begin_y + 1.15675e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 3.66861e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + 6.3981e-10 *begin_x*lens_ipow(begin_y, 5) + 2.50305e-08 *begin_x*lens_ipow(begin_y, 4)*begin_dy + 3.69828e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 1.48886e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_lambda + 8.45591e-07 *lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 3) + 1.16858e-11 *lens_ipow(begin_y, 7)*begin_dx + 6.83395e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.031682  + -0.00166826 *begin_y*begin_dy + -0.000272704 *begin_x*begin_dx + -1.85195e-05 *lens_ipow(begin_y, 2)*begin_lambda + 2.42317e-08 *lens_ipow(begin_x, 4) + 8.11971e-10 *lens_ipow(begin_y, 6) + 8.6756e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 3.66861e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + -1.53316e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 3.99644e-08 *lens_ipow(begin_y, 5)*begin_dy + 1.59953e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + 5.00609e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -9.29643e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_lambda + 1.84914e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dy*begin_lambda + 2.97772e-09 *lens_ipow(begin_x, 5)*begin_dx*begin_lambda + 3.38236e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + 8.18007e-11 *begin_x*lens_ipow(begin_y, 6)*begin_dx + -0.000357018 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + 4.55597e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda+0.0f;
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
  out[4] =  + 0.565726  + 0.0782943 *begin_lambda + -0.141415 *lens_ipow(begin_dy, 2) + -0.000172461 *lens_ipow(begin_y, 3)*begin_dy + -0.0013932 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0993797 *begin_y*lens_ipow(begin_dy, 3) + -0.00708878 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -1.3e-06 *lens_ipow(begin_y, 4) + -1.17784e-06 *lens_ipow(begin_x, 4) + -1.35791e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.000251987 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.000230636 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + -2.77198 *lens_ipow(begin_dx, 4)*begin_lambda + -0.000264215 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -1.92632e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -0.465596 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.0227789 *begin_x*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.0218709 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -0.280991 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + -0.111773 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -1.45194e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -3.30824 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.00422892 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -4.22934e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3);
else
  out[4] = 0.0f;
} break;
