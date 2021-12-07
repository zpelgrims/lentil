case asahi__takumar__1970__50mm:
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
       + 51.3922 *begin_dx + 0.574039 *begin_x + 3.78005 *begin_dx*begin_lambda + 0.0617709 *begin_x*begin_lambda + -2.56761 *begin_dx*lens_ipow(begin_lambda, 2) + 10.1535 *begin_dx*lens_ipow(begin_dy, 2) + 4.05684 *lens_ipow(begin_dx, 3) + 1.14759 *begin_y*begin_dx*begin_dy + 0.013382 *lens_ipow(begin_y, 2)*begin_dx + -0.0427229 *begin_x*lens_ipow(begin_lambda, 2) + 0.685393 *begin_x*lens_ipow(begin_dy, 2) + 1.51615 *begin_x*lens_ipow(begin_dx, 2) + 0.0296789 *begin_x*begin_y*begin_dy + 0.000238686 *begin_x*lens_ipow(begin_y, 2) + 0.0371742 *lens_ipow(begin_x, 2)*begin_dx + 0.000205007 *lens_ipow(begin_x, 3) + 83.6811 *lens_ipow(begin_dx, 5) + 7.3973 *begin_x*lens_ipow(begin_dx, 4) + 0.269112 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.00487586 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -3.19466e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 4.46202e-05 *lens_ipow(begin_x, 4)*begin_dx + 1.49321e-07 *lens_ipow(begin_x, 5) + 0.134183 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.000567645 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4) + -4.23201e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -9.04733e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 4.59872e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_lambda,
       + 51.3364 *begin_dy + 0.574116 *begin_y + 3.66341 *begin_dy*begin_lambda + 0.0590391 *begin_y*begin_lambda + -2.4795 *begin_dy*lens_ipow(begin_lambda, 2) + 10.3778 *lens_ipow(begin_dy, 3) + 10.1878 *lens_ipow(begin_dx, 2)*begin_dy + -0.040445 *begin_y*lens_ipow(begin_lambda, 2) + 1.84056 *begin_y*lens_ipow(begin_dy, 2) + 0.658403 *begin_y*lens_ipow(begin_dx, 2) + 0.0431989 *lens_ipow(begin_y, 2)*begin_dy + 0.000234192 *lens_ipow(begin_y, 3) + 1.16759 *begin_x*begin_dx*begin_dy + 0.0291475 *begin_x*begin_y*begin_dx + 0.0134529 *lens_ipow(begin_x, 2)*begin_dy + 0.000233251 *lens_ipow(begin_x, 2)*begin_y + 0.000214349 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 3.78154e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00507316 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.33916e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy + -0.000122682 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -2.23027e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 6.67463e-07 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + 0.678603 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -0.00026519 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.000577562 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 4)*begin_dy + 3.76374e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 4) + 98.4147 *begin_x*begin_dx*lens_ipow(begin_dy, 7)*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 51.3922  + 3.78005 *begin_lambda + -2.56761 *lens_ipow(begin_lambda, 2) + 10.1535 *lens_ipow(begin_dy, 2) + 12.1705 *lens_ipow(begin_dx, 2) + 1.14759 *begin_y*begin_dy + 0.013382 *lens_ipow(begin_y, 2) + 3.03229 *begin_x*begin_dx + 0.0371742 *lens_ipow(begin_x, 2) + 418.406 *lens_ipow(begin_dx, 4) + 29.5892 *begin_x*lens_ipow(begin_dx, 3) + 0.807337 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.00975172 *lens_ipow(begin_x, 3)*begin_dx + 4.46202e-05 *lens_ipow(begin_x, 4) + 0.268367 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3) + -4.23201e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -9.04733e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + 9.19744e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + 20.307 *begin_dx*begin_dy + 1.14759 *begin_y*begin_dx + 1.37079 *begin_x*begin_dy + 0.0296789 *begin_x*begin_y + 0.40255 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.00227058 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3) + -8.46401e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -9.04733e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx+0.0f;
    dx1_domega0(1, 0) =  + 20.3757 *begin_dx*begin_dy + 1.31681 *begin_y*begin_dx + 1.16759 *begin_x*begin_dy + 0.0291475 *begin_x*begin_y + 0.000428698 *lens_ipow(begin_y, 3)*begin_dx + 3.78154e-06 *begin_x*lens_ipow(begin_y, 3) + 0.0101463 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -1.33916e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dy + -0.000245363 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -2.23027e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 0.678603 *begin_x*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -0.00026519 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 0.00231025 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy + 1.50549e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3) + 98.4147 *begin_x*lens_ipow(begin_dy, 7)*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 51.3364  + 3.66341 *begin_lambda + -2.4795 *lens_ipow(begin_lambda, 2) + 31.1334 *lens_ipow(begin_dy, 2) + 10.1878 *lens_ipow(begin_dx, 2) + 3.68112 *begin_y*begin_dy + 0.0431989 *lens_ipow(begin_y, 2) + 1.16759 *begin_x*begin_dx + 0.0134529 *lens_ipow(begin_x, 2) + 0.00507316 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.33916e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -0.000122682 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.23027e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 1.33493e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy + 2.71441 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -0.000530381 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda + 0.000577562 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 4) + 688.903 *begin_x*begin_dx*lens_ipow(begin_dy, 6)*begin_lambda+0.0f;
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
    out(0) =  + 48.7164 *begin_dx + -0.0732961 *begin_x + 3.78481 *begin_dx*begin_lambda + -0.00765776 *begin_x*begin_lambda + -2.8578 *begin_dx*lens_ipow(begin_lambda, 2) + -11.4983 *begin_dx*lens_ipow(begin_dy, 2) + -27.292 *lens_ipow(begin_dx, 3) + 0.528304 *begin_y*begin_dx*begin_dy + 0.0116589 *lens_ipow(begin_y, 2)*begin_dx + 0.283207 *begin_x*lens_ipow(begin_dy, 2) + 0.0232571 *begin_x*begin_y*begin_dy + 0.00028254 *begin_x*lens_ipow(begin_y, 2) + 0.0215017 *lens_ipow(begin_x, 2)*begin_dx + 0.000205375 *lens_ipow(begin_x, 3) + 38.1107 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 246.425 *lens_ipow(begin_dx, 5) + -0.000228291 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 3.1137 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 19.7027 *begin_x*lens_ipow(begin_dx, 4) + 0.0236672 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0642696 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.630678 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.000608191 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.0100058 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 4.42895e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 8.3372e-05 *lens_ipow(begin_x, 4)*begin_dx + 2.847e-07 *lens_ipow(begin_x, 5) + -1.40991e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx*begin_lambda;
    out(1) =  + 48.746 *begin_dy + -0.0731029 *begin_y + 3.68335 *begin_dy*begin_lambda + -0.00775688 *begin_y*begin_lambda + -2.78464 *begin_dy*lens_ipow(begin_lambda, 2) + -27.4289 *lens_ipow(begin_dy, 3) + -11.4548 *lens_ipow(begin_dx, 2)*begin_dy + 0.280248 *begin_y*lens_ipow(begin_dx, 2) + 0.0216049 *lens_ipow(begin_y, 2)*begin_dy + 0.000204878 *lens_ipow(begin_y, 3) + 0.530652 *begin_x*begin_dx*begin_dy + 0.0232235 *begin_x*begin_y*begin_dx + 0.0116839 *lens_ipow(begin_x, 2)*begin_dy + 0.00028211 *lens_ipow(begin_x, 2)*begin_y + 251.22 *lens_ipow(begin_dy, 5) + 38.1207 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 19.773 *begin_y*lens_ipow(begin_dy, 4) + 3.21524 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.627759 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.066098 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.00993927 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.000630455 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 8.28235e-05 *lens_ipow(begin_y, 4)*begin_dy + 2.85005e-07 *lens_ipow(begin_y, 5) + 0.0248479 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 4.55976e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -0.000230426 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -1.64315e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda;
    out(2) =  + -0.229348 *begin_dx + -0.0197239 *begin_x + 0.271302 *begin_dx*lens_ipow(begin_dy, 2) + 0.0070427 *begin_y*begin_dx*begin_dy + 5.11444e-05 *lens_ipow(begin_y, 2)*begin_dx + 2.87582e-06 *begin_x*lens_ipow(begin_y, 2) + 1.50807e-06 *lens_ipow(begin_x, 3) + 0.926264 *lens_ipow(begin_dx, 3)*begin_lambda + 0.00540682 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.0302485 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 9.30597e-05 *begin_x*begin_y*begin_dy*begin_lambda + 0.000194227 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 3.21847e-06 *lens_ipow(begin_x, 3)*begin_lambda + -0.939542 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 1.16878 *lens_ipow(begin_dx, 5) + -0.02759 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -1.09482e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.016527 *begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.000968566 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + 0.180281 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 2.49843e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 0.00971883 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 3.00171e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + -3.82436e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + 0.000178501 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.211014 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -1.34088e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 4) + -10.017 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5);
    out(3) =  + -0.235247 *begin_dy + -0.0199055 *begin_y + 0.00853415 *begin_dy*begin_lambda + 0.000304997 *begin_y*begin_lambda + 0.314967 *lens_ipow(begin_dy, 3) + 0.276528 *lens_ipow(begin_dx, 2)*begin_dy + 0.0121439 *begin_y*lens_ipow(begin_dy, 2) + 0.000157676 *lens_ipow(begin_y, 2)*begin_dy + 3.18164e-06 *lens_ipow(begin_y, 3) + 0.00861913 *begin_x*begin_dx*begin_dy + 5.6667e-05 *lens_ipow(begin_x, 2)*begin_dy + 3.27808e-06 *lens_ipow(begin_x, 2)*begin_y + 0.010073 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.000317406 *begin_x*begin_y*begin_dx*begin_lambda + 0.000422696 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.011292 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.000267398 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -1.56455e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.000460096 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 9.92867e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + -1.94284e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -9.07503e-08 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -9.64752e-10 *lens_ipow(begin_x, 4)*begin_y + -0.0109555 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -3.95473e-07 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.00167972 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -2.08377 *lens_ipow(begin_dy, 5)*lens_ipow(begin_lambda, 3) + -6.71206e-12 *lens_ipow(begin_y, 7)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0197239  + 2.87582e-06 *lens_ipow(begin_y, 2) + 4.52422e-06 *lens_ipow(begin_x, 2) + 0.00540682 *lens_ipow(begin_dy, 2)*begin_lambda + 0.0302485 *lens_ipow(begin_dx, 2)*begin_lambda + 9.30597e-05 *begin_y*begin_dy*begin_lambda + 0.000388454 *begin_x*begin_dx*begin_lambda + 9.65541e-06 *lens_ipow(begin_x, 2)*begin_lambda + -0.02759 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -3.28446e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.180281 *lens_ipow(begin_dx, 4)*begin_lambda + 2.49843e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 0.0194377 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 6.00343e-10 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -1.14731e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + 0.000535504 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.211014 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -6.70439e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 4)+0.0f;
    domega2_dx0(0, 1) =  + 0.0070427 *begin_dx*begin_dy + 0.000102289 *begin_y*begin_dx + 5.75164e-06 *begin_x*begin_y + 9.30597e-05 *begin_x*begin_dy*begin_lambda + -2.18964e-09 *lens_ipow(begin_x, 3)*begin_y + -0.016527 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.00193713 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 4.99685e-05 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 1.20069e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -1.14731e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy+0.0f;
    domega2_dx0(1, 0) =  + 0.00861913 *begin_dx*begin_dy + 0.000113334 *begin_x*begin_dy + 6.55615e-06 *begin_x*begin_y + 0.000317406 *begin_y*begin_dx*begin_lambda + -0.011292 *lens_ipow(begin_dx, 3)*begin_dy + -0.000267398 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -1.56455e-07 *lens_ipow(begin_y, 3)*begin_dx + 0.000920192 *begin_x*lens_ipow(begin_dy, 3) + 1.98573e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -3.88569e-09 *begin_x*lens_ipow(begin_y, 3) + -2.72251e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -3.85901e-09 *lens_ipow(begin_x, 3)*begin_y+0.0f;
    domega2_dx0(1, 1) =  + -0.0199055  + 0.000304997 *begin_lambda + 0.0121439 *lens_ipow(begin_dy, 2) + 0.000315352 *begin_y*begin_dy + 9.54491e-06 *lens_ipow(begin_y, 2) + 3.27808e-06 *lens_ipow(begin_x, 2) + 0.010073 *lens_ipow(begin_dx, 2)*begin_lambda + 0.000317406 *begin_x*begin_dx*begin_lambda + 0.000845391 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000267398 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -4.69365e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 9.92867e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -5.82853e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -9.07503e-08 *lens_ipow(begin_x, 3)*begin_dx + -9.64752e-10 *lens_ipow(begin_x, 4) + -0.0109555 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -1.58189e-06 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 0.00335945 *begin_y*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -4.69844e-11 *lens_ipow(begin_y, 6)*begin_lambda+0.0f;
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
  out[4] =  + 1.91412 *begin_lambda + -3.33239 *lens_ipow(begin_lambda, 2) + 0.00896197 *lens_ipow(begin_dx, 2) + 0.000278044 *begin_x*begin_dx + 2.88171e-06 *lens_ipow(begin_x, 2) + 7.61319 *lens_ipow(begin_lambda, 4) + -0.65819 *lens_ipow(begin_dy, 4) + -1.47063 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.810263 *lens_ipow(begin_dx, 4) + -0.0290539 *begin_y*lens_ipow(begin_dy, 3) + -0.0335802 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000731648 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00028597 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -9.8139e-06 *lens_ipow(begin_y, 3)*begin_dy + -5.9313e-08 *lens_ipow(begin_y, 4) + -0.0340015 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0377928 *begin_x*lens_ipow(begin_dx, 3) + -0.00112091 *begin_x*begin_y*begin_dx*begin_dy + -1.12695e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000288591 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000945227 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.12503e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -1.35671e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.23444e-05 *lens_ipow(begin_x, 3)*begin_dx + -7.30793e-08 *lens_ipow(begin_x, 4) + -9.59978 *lens_ipow(begin_lambda, 5) + 3.84015 *lens_ipow(begin_lambda, 6) + 0.000973169 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4);
else
  out[4] = 0.0f;
} break;
