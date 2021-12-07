case asahi__takumar__1970__35mm:
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
       + 36.4268 *begin_dx + 0.585227 *begin_x + 0.656534 *begin_dx*begin_lambda + 0.0149211 *begin_x*begin_lambda + 7.4444 *begin_dx*lens_ipow(begin_dy, 2) + 7.69957 *lens_ipow(begin_dx, 3) + 1.16927 *begin_y*begin_dx*begin_dy + 0.0194054 *lens_ipow(begin_y, 2)*begin_dx + 0.66148 *begin_x*lens_ipow(begin_dy, 2) + 1.86233 *begin_x*lens_ipow(begin_dx, 2) + 0.0417592 *begin_x*begin_y*begin_dy + 0.000476698 *begin_x*lens_ipow(begin_y, 2) + 0.0622766 *lens_ipow(begin_x, 2)*begin_dx + 0.000493428 *lens_ipow(begin_x, 3) + 0.000155639 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.000339743 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 1.07857e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -6.12827e-08 *lens_ipow(begin_x, 5) + 0.000802646 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 1.36092e-08 *begin_x*lens_ipow(begin_y, 5)*begin_dy + -0.00498406 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -8.64501e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_lambda + 0.00181347 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4)*begin_lambda + 0.00552577 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4)*begin_lambda + -6.20374 *begin_y*begin_dx*lens_ipow(begin_dy, 7) + -6.94883e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.0150714 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3) + -3.94461e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda,
       + 36.4154 *begin_dy + 0.585801 *begin_y + 0.687486 *begin_dy*begin_lambda + 0.0145999 *begin_y*begin_lambda + 7.44378 *lens_ipow(begin_dy, 3) + 7.36703 *lens_ipow(begin_dx, 2)*begin_dy + 1.84738 *begin_y*lens_ipow(begin_dy, 2) + 0.639896 *begin_y*lens_ipow(begin_dx, 2) + 0.0624776 *lens_ipow(begin_y, 2)*begin_dy + 0.000489083 *lens_ipow(begin_y, 3) + 1.18781 *begin_x*begin_dx*begin_dy + 0.0415238 *begin_x*begin_y*begin_dx + 0.0198668 *lens_ipow(begin_x, 2)*begin_dy + 0.000479747 *lens_ipow(begin_x, 2)*begin_y + -0.000911249 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -5.95897e-08 *lens_ipow(begin_y, 5) + -0.000477062 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 1.82744e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.000247619 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.000509512 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -0.000319949 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + 1.1927e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -5.78164e-06 *lens_ipow(begin_x, 4)*begin_dy + 0.00192805 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_lambda + -1.49987e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -0.00340406 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -3.40325e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 0.00241709 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 6)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 36.4268  + 0.656534 *begin_lambda + 7.4444 *lens_ipow(begin_dy, 2) + 23.0987 *lens_ipow(begin_dx, 2) + 1.16927 *begin_y*begin_dy + 0.0194054 *lens_ipow(begin_y, 2) + 3.72467 *begin_x*begin_dx + 0.0622766 *lens_ipow(begin_x, 2) + 0.000311277 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000339743 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.0149522 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.00025935 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_lambda + -6.20374 *begin_y*lens_ipow(begin_dy, 7) + -6.94883e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + -3.94461e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + 14.8888 *begin_dx*begin_dy + 1.16927 *begin_y*begin_dx + 1.32296 *begin_x*begin_dy + 0.0417592 *begin_x*begin_y + -0.000339743 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 1.07857e-05 *lens_ipow(begin_x, 3)*begin_y + 0.00160529 *lens_ipow(begin_x, 3)*begin_dy*begin_lambda + 1.36092e-08 *begin_x*lens_ipow(begin_y, 5) + -0.00498406 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_lambda + 0.00725388 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.0221031 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3)*begin_lambda + -43.4262 *begin_y*begin_dx*lens_ipow(begin_dy, 6) + -6.94883e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx + -0.0602856 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -7.88922e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + 14.7341 *begin_dx*begin_dy + 1.27979 *begin_y*begin_dx + 1.18781 *begin_x*begin_dy + 0.0415238 *begin_x*begin_y + -0.000477062 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 1.82744e-05 *begin_x*lens_ipow(begin_y, 3) + 0.00101902 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -0.000319949 *lens_ipow(begin_x, 3)*begin_dy + 1.1927e-05 *lens_ipow(begin_x, 3)*begin_y + 0.00385611 *lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -1.49987e-05 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + -0.00680811 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 3) + -3.40325e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dy + 0.00483418 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_lambda, 6)+0.0f;
    dx1_domega0(1, 1) =  + 36.4154  + 0.687486 *begin_lambda + 22.3313 *lens_ipow(begin_dy, 2) + 7.36703 *lens_ipow(begin_dx, 2) + 3.69476 *begin_y*begin_dy + 0.0624776 *lens_ipow(begin_y, 2) + 1.18781 *begin_x*begin_dx + 0.0198668 *lens_ipow(begin_x, 2) + -0.000911249 *lens_ipow(begin_y, 2)*begin_lambda + -0.000477062 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.000495238 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.000319949 *lens_ipow(begin_x, 3)*begin_dx + -5.78164e-06 *lens_ipow(begin_x, 4) + -3.40325e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx+0.0f;
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
    out(0) =  + 34.013 *begin_dx + -0.077231 *begin_x + 2.46685 *begin_dx*begin_lambda + -0.00787569 *begin_x*begin_lambda + -1.89011 *begin_dx*lens_ipow(begin_lambda, 2) + -7.30244 *begin_dx*lens_ipow(begin_dy, 2) + -7.42694 *lens_ipow(begin_dx, 3) + 0.537496 *begin_y*begin_dx*begin_dy + 0.0166315 *lens_ipow(begin_y, 2)*begin_dx + 0.333408 *begin_x*lens_ipow(begin_dy, 2) + 0.826914 *begin_x*lens_ipow(begin_dx, 2) + 0.0343351 *begin_x*begin_y*begin_dy + 0.000576986 *begin_x*lens_ipow(begin_y, 2) + 0.0502348 *lens_ipow(begin_x, 2)*begin_dx + 0.000577116 *lens_ipow(begin_x, 3) + 0.0159411 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0189181 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.402836 *begin_x*lens_ipow(begin_dx, 4) + 0.000744982 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.0245148 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -0.00128853 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -1.63922e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy*begin_lambda + -1.5486e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 0.00279738 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4) + -0.000116042 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -4.40175e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 1.3009e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -0.00377192 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 2);
    out(1) =  + 33.8432 *begin_dy + -0.0774611 *begin_y + 2.74914 *begin_dy*begin_lambda + -0.00816395 *begin_y*begin_lambda + -2.03363 *begin_dy*lens_ipow(begin_lambda, 2) + -6.07492 *lens_ipow(begin_dy, 3) + -6.25575 *lens_ipow(begin_dx, 2)*begin_dy + 0.882954 *begin_y*lens_ipow(begin_dy, 2) + 0.321885 *begin_y*lens_ipow(begin_dx, 2) + 0.0518671 *lens_ipow(begin_y, 2)*begin_dy + 0.000581925 *lens_ipow(begin_y, 3) + 0.578627 *begin_x*begin_dx*begin_dy + 0.0340502 *begin_x*begin_y*begin_dx + 0.0179174 *lens_ipow(begin_x, 2)*begin_dy + 0.00058084 *lens_ipow(begin_x, 2)*begin_y + -0.00105757 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.448028 *begin_y*lens_ipow(begin_dy, 4) + 0.0246324 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.000470446 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.00145267 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -9.12517e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -0.000572487 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -1.32533e-05 *lens_ipow(begin_x, 4)*begin_dy*begin_lambda + -6.48871e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 0.654125 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + 0.0167809 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 6)*begin_dy + 0.000131796 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 6) + 4.89998e-08 *lens_ipow(begin_x, 6)*begin_dy*lens_ipow(begin_lambda, 4);
    out(2) =  + -0.22702 *begin_dx + -0.0283593 *begin_x + 0.000404443 *begin_x*begin_lambda + 0.286552 *begin_dx*lens_ipow(begin_dy, 2) + 0.0115947 *begin_y*begin_dx*begin_dy + 0.000135206 *lens_ipow(begin_y, 2)*begin_dx + 0.00516284 *begin_x*lens_ipow(begin_dy, 2) + 0.000171135 *begin_x*begin_y*begin_dy + 9.40061e-06 *begin_x*lens_ipow(begin_y, 2) + -0.00011997 *lens_ipow(begin_x, 2)*begin_dx + 6.62343e-06 *lens_ipow(begin_x, 3) + -0.00380207 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 4.80548 *lens_ipow(begin_dx, 5) + 0.514387 *begin_x*lens_ipow(begin_dx, 4) + 0.000691205 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0230746 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.000497688 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -5.53155e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -8.10201e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 5.00954e-06 *lens_ipow(begin_x, 4)*begin_dx + 1.76019e-08 *lens_ipow(begin_x, 5) + -0.0243593 *begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -0.0191939 *begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 2.37377e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3) + -7.6774e-07 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + -4.6337e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -2.35507e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -1.61055e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_lambda;
    out(3) =  + -0.230758 *begin_dy + -0.0283847 *begin_y + 0.000390904 *begin_y*begin_lambda + 0.299651 *lens_ipow(begin_dy, 3) + 0.299771 *lens_ipow(begin_dx, 2)*begin_dy + 0.0158023 *begin_y*lens_ipow(begin_dy, 2) + 0.00476643 *begin_y*lens_ipow(begin_dx, 2) + 0.000208868 *lens_ipow(begin_y, 2)*begin_dy + 8.64715e-06 *lens_ipow(begin_y, 3) + 0.0125955 *begin_x*begin_dx*begin_dy + 0.000126138 *begin_x*begin_y*begin_dx + 0.000127569 *lens_ipow(begin_x, 2)*begin_dy + 8.49105e-06 *lens_ipow(begin_x, 2)*begin_y + -0.00359898 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.000494851 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -2.38566e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.153887 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.0110358 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.00025289 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 1.84208e-06 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -0.0260346 *begin_x*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.0125017 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + 0.00064511 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 4) + 8.87666e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -8.76202e-07 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3) + 4.40698e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + -1.05453e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 2.56838e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_dy, 3);
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
    domega2_dx0(0, 0) =  + -0.0283593  + 0.000404443 *begin_lambda + 0.00516284 *lens_ipow(begin_dy, 2) + 0.000171135 *begin_y*begin_dy + 9.40061e-06 *lens_ipow(begin_y, 2) + -0.00023994 *begin_x*begin_dx + 1.98703e-05 *lens_ipow(begin_x, 2) + -0.00380207 *lens_ipow(begin_dx, 2)*begin_lambda + 0.514387 *lens_ipow(begin_dx, 4) + 0.00138241 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.0461492 *begin_x*lens_ipow(begin_dx, 3) + 0.00149307 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.65947e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -2.4306e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 2.00382e-05 *lens_ipow(begin_x, 3)*begin_dx + 8.80096e-08 *lens_ipow(begin_x, 4) + -7.6774e-07 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + -4.6337e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -4.71013e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -4.83164e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + 0.0115947 *begin_dx*begin_dy + 0.000270412 *begin_y*begin_dx + 0.000171135 *begin_x*begin_dy + 1.88012e-05 *begin_x*begin_y + -5.53155e-07 *lens_ipow(begin_x, 3)*begin_dy + -1.6204e-08 *lens_ipow(begin_x, 3)*begin_y + -0.0243593 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -0.0191939 *lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 9.49508e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -2.30322e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -1.39011e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -4.71013e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_lambda + -6.44219e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.0125955 *begin_dx*begin_dy + 0.000126138 *begin_y*begin_dx + 0.000255138 *begin_x*begin_dy + 1.69821e-05 *begin_x*begin_y + -2.38566e-07 *lens_ipow(begin_y, 3)*begin_dx + -0.0260346 *lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + 0.0250034 *begin_x*lens_ipow(begin_dy, 5) + 0.00129022 *begin_x*begin_y*lens_ipow(begin_dy, 4) + 1.77533e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -2.62861e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3) + 1.32209e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx*begin_dy + -4.2181e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + 1.54103e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.0283847  + 0.000390904 *begin_lambda + 0.0158023 *lens_ipow(begin_dy, 2) + 0.00476643 *lens_ipow(begin_dx, 2) + 0.000417736 *begin_y*begin_dy + 2.59414e-05 *lens_ipow(begin_y, 2) + 0.000126138 *begin_x*begin_dx + 8.49105e-06 *lens_ipow(begin_x, 2) + -0.00359898 *lens_ipow(begin_dy, 2)*begin_lambda + 0.000989702 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -7.15698e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.153887 *lens_ipow(begin_dy, 4)*begin_lambda + 0.0220717 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 0.00075867 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 7.36833e-06 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 0.00064511 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + 1.77533e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 3) + -8.76202e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + 1.76279e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -5.27263e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)+0.0f;
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
  out[4] =  + 2.00858 *begin_lambda + -4.37567 *lens_ipow(begin_lambda, 2) + -0.00763709 *lens_ipow(begin_dy, 2) + -0.0318356 *lens_ipow(begin_dx, 2) + -0.000303137 *begin_y*begin_dy + -0.00152429 *begin_x*begin_dx + -1.89933e-05 *lens_ipow(begin_x, 2) + 4.48883 *lens_ipow(begin_lambda, 3) + -1.78333 *lens_ipow(begin_lambda, 4) + -0.619654 *lens_ipow(begin_dy, 4) + -0.284657 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.200171 *lens_ipow(begin_dx, 4) + -0.0392203 *begin_y*lens_ipow(begin_dy, 3) + -0.00154259 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -9.33305e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -3.16343e-05 *lens_ipow(begin_y, 3)*begin_dy + -2.89055e-07 *lens_ipow(begin_y, 4) + -0.000407693 *begin_x*begin_y*begin_dx*begin_dy + -1.35039e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -9.65193e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.36601e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -3.75694e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -4.52746e-08 *lens_ipow(begin_x, 5)*begin_dx + -8.09392e-10 *lens_ipow(begin_x, 6) + 2.10666e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 3) + 6.70578e-13 *lens_ipow(begin_x, 8) + -9.93837e-16 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + -5.26913e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 5);
else
  out[4] = 0.0f;
} break;
