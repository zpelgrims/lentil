case canon__unknown__1956__35mm:
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
       + 24.2446 *begin_dx + 0.619677 *begin_x + 0.025215 *begin_x*begin_lambda + 0.599884 *begin_dx*lens_ipow(begin_lambda, 2) + -0.55281 *begin_x*lens_ipow(begin_dx, 2) + -0.324925 *begin_y*begin_dx*begin_dy + -0.19735 *begin_x*lens_ipow(begin_dy, 2) + -14.0745 *lens_ipow(begin_dx, 3) + -13.7508 *begin_dx*lens_ipow(begin_dy, 2) + 0.00120522 *lens_ipow(begin_y, 2)*begin_dx + 0.000711497 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -6.08655e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.0163565 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 3.00049 *lens_ipow(begin_dx, 5) + 0.0284011 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.56316e-07 *lens_ipow(begin_x, 5) + -0.395063 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 3.14333e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -4.61902e-10 *begin_x*lens_ipow(begin_y, 6) + 17.3072 *begin_dx*lens_ipow(begin_dy, 6) + 0.00119011 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.315991 *begin_x*lens_ipow(begin_dy, 6) + -5.6139e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 9.93732e-08 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dx, 2)*begin_dy,
       + 0.619971 *begin_y + 24.2408 *begin_dy + 0.0254621 *begin_y*begin_lambda + -0.204909 *begin_y*lens_ipow(begin_dx, 2) + -14.7356 *lens_ipow(begin_dy, 3) + -0.59286 *begin_y*lens_ipow(begin_dy, 2) + 0.627484 *begin_dy*lens_ipow(begin_lambda, 2) + -0.315038 *begin_x*begin_dx*begin_dy + -13.536 *lens_ipow(begin_dx, 2)*begin_dy + 0.00119107 *lens_ipow(begin_x, 2)*begin_dy + 1.95414e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.000883187 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.332132 *begin_y*lens_ipow(begin_dy, 4) + -3.86549e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.0187213 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.0258523 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -1.37239 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -4.95839e-10 *lens_ipow(begin_x, 6)*begin_y + 0.365576 *begin_y*lens_ipow(begin_dx, 6) + -4.26449e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + 15.185 *lens_ipow(begin_dx, 6)*begin_dy + 0.00159637 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -3.38031 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + 2.9801e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 24.2446  + 0.599884 *lens_ipow(begin_lambda, 2) + -1.10562 *begin_x*begin_dx + -0.324925 *begin_y*begin_dy + -42.2235 *lens_ipow(begin_dx, 2) + -13.7508 *lens_ipow(begin_dy, 2) + 0.00120522 *lens_ipow(begin_y, 2) + 0.000711497 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.0490695 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 15.0024 *lens_ipow(begin_dx, 4) + 0.0568022 *begin_x*begin_y*begin_dx*begin_dy + -1.18519 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 17.3072 *lens_ipow(begin_dy, 6) + 0.00238021 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + -5.6139e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dy + 1.98746e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + -0.324925 *begin_y*begin_dx + -0.394699 *begin_x*begin_dy + -27.5016 *begin_dx*begin_dy + 0.000711497 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.0284011 *begin_x*begin_y*lens_ipow(begin_dx, 2) + -0.395063 *begin_y*lens_ipow(begin_dx, 3) + 103.843 *begin_dx*lens_ipow(begin_dy, 5) + 0.00238021 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_dy + 1.89595 *begin_x*lens_ipow(begin_dy, 5) + -5.6139e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx + 9.93732e-08 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dx, 2)+0.0f;
    dx1_domega0(1, 0) =  + -0.409818 *begin_y*begin_dx + -0.315038 *begin_x*begin_dy + -27.072 *begin_dx*begin_dy + -0.0374426 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -1.37239 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + 2.19346 *begin_y*lens_ipow(begin_dx, 5) + 91.1102 *lens_ipow(begin_dx, 5)*begin_dy + 0.00159637 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3)*begin_lambda + -16.9015 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 2.9801e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(1, 1) =  + 24.2408  + -44.2069 *lens_ipow(begin_dy, 2) + -1.18572 *begin_y*begin_dy + 0.627484 *lens_ipow(begin_lambda, 2) + -0.315038 *begin_x*begin_dx + -13.536 *lens_ipow(begin_dx, 2) + 0.00119107 *lens_ipow(begin_x, 2) + 1.95414e-05 *lens_ipow(begin_y, 4) + 0.00176637 *lens_ipow(begin_y, 3)*begin_dy + -1.32853 *begin_y*lens_ipow(begin_dy, 3) + -0.0187213 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -0.0775569 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -4.11716 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -8.52898e-07 *lens_ipow(begin_y, 5)*begin_dy + 15.185 *lens_ipow(begin_dx, 6) + 0.0047891 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -10.1409 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 5.9602e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy+0.0f;
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
    out(0) =  + 34.7891 *begin_dx + 0.522937 *begin_x + 0.000636245 *lens_ipow(begin_x, 3) + 0.910885 *begin_x*lens_ipow(begin_dx, 2) + 0.739946 *begin_x*lens_ipow(begin_dy, 2) + -17.48 *lens_ipow(begin_dx, 3) + -18.6801 *begin_dx*lens_ipow(begin_dy, 2) + 0.0707989 *lens_ipow(begin_x, 2)*begin_dx + 0.00044489 *begin_x*lens_ipow(begin_y, 2) + 0.0509275 *begin_x*begin_y*begin_dy + 0.0127201 *lens_ipow(begin_y, 2)*begin_dx + 0.000269731 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 8.78215e-05 *lens_ipow(begin_x, 3)*begin_lambda + -2.24766 *begin_x*lens_ipow(begin_dx, 4) + 12.5526 *begin_dx*lens_ipow(begin_dy, 4) + -1.4222e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -0.0868561 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.0012156 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -6.7388e-07 *lens_ipow(begin_x, 5) + 0.00102673 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 36.8709 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.00298619 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.40387e-06 *begin_x*lens_ipow(begin_y, 4)*begin_lambda + 0.0669354 *begin_x*begin_y*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2);
    out(1) =  + 0.508484 *begin_y + 34.7044 *begin_dy + 0.019378 *begin_y*begin_lambda + 0.824804 *begin_y*lens_ipow(begin_dx, 2) + -15.7408 *lens_ipow(begin_dy, 3) + 1.07968 *begin_y*lens_ipow(begin_dy, 2) + 0.000751333 *lens_ipow(begin_y, 3) + 0.0762288 *lens_ipow(begin_y, 2)*begin_dy + 0.0544193 *begin_x*begin_y*begin_dx + -16.7188 *lens_ipow(begin_dx, 2)*begin_dy + 0.0128376 *lens_ipow(begin_x, 2)*begin_dy + 0.000671246 *lens_ipow(begin_x, 2)*begin_y + -5.67638e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.00119247 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.0876412 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.0318066 *begin_x*begin_y*lens_ipow(begin_dx, 3) + 0.0020152 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + -2.26959 *begin_y*lens_ipow(begin_dy, 4) + -2.38473e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -6.8731e-07 *lens_ipow(begin_y, 5) + -1.55962 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -8.69978e-07 *lens_ipow(begin_x, 4)*begin_y + 0.00122921 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 15.3494 *lens_ipow(begin_dx, 4)*begin_dy*begin_lambda;
    out(2) =  + -1.71382 *begin_dx + -0.0547798 *begin_x + 1.58511e-05 *lens_ipow(begin_x, 3) + -0.0480484 *begin_y*begin_dx*begin_dy + -0.0664615 *begin_x*lens_ipow(begin_dy, 2) + -1.09857 *begin_dx*lens_ipow(begin_dy, 2) + -0.000640502 *lens_ipow(begin_x, 2)*begin_dx + -0.00298569 *begin_x*begin_y*begin_dy + 3.48163 *lens_ipow(begin_dx, 3)*begin_lambda + 0.0392894 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -8.75209e-06 *lens_ipow(begin_x, 3)*begin_lambda + 0.151209 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.25106e-08 *begin_x*lens_ipow(begin_y, 4) + 0.0159279 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 2.43322 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -8.58484e-07 *lens_ipow(begin_y, 4)*begin_dx + -2.81139 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -0.000108446 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -0.342112 *lens_ipow(begin_dx, 5)*begin_lambda + -0.0406525 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + 0.000127936 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 5.35884e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + 1.8503e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_lambda + 6.9549e-14 *lens_ipow(begin_x, 9)*begin_lambda;
    out(3) =  + -0.0527133 *begin_y + -1.69765 *begin_dy + -0.00529584 *begin_y*begin_lambda + 0.00390598 *begin_y*lens_ipow(begin_lambda, 2) + 0.930735 *lens_ipow(begin_dy, 3) + 0.0119745 *begin_y*lens_ipow(begin_dy, 2) + 6.82739e-06 *lens_ipow(begin_y, 3) + 0.165653 *begin_x*begin_dx*begin_dy + -0.000911985 *lens_ipow(begin_y, 2)*begin_dy + 3.47215 *lens_ipow(begin_dx, 2)*begin_dy + 0.00194201 *lens_ipow(begin_x, 2)*begin_dy + 2.3132e-05 *lens_ipow(begin_x, 2)*begin_y + -2.70802e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.185939 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -3.89132 *lens_ipow(begin_dx, 4)*begin_dy + 6.19899e-05 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + 0.0030138 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.0888084 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -4.36312e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + 1.12864e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 2.88242e-14 *lens_ipow(begin_y, 9) + 3.25899e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -8.02633e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -0.0233997 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 6)*begin_lambda;
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
    domega2_dx0(0, 0) =  + -0.0547798  + 4.75532e-05 *lens_ipow(begin_x, 2) + -0.0664615 *lens_ipow(begin_dy, 2) + -0.001281 *begin_x*begin_dx + -0.00298569 *begin_y*begin_dy + 0.0392894 *lens_ipow(begin_dx, 2)*begin_lambda + -2.62563e-05 *lens_ipow(begin_x, 2)*begin_lambda + 0.151209 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.25106e-08 *lens_ipow(begin_y, 4) + -0.000325338 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0406525 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + 0.000383808 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 2.67942e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 3.7006e-08 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_lambda + 6.25941e-13 *lens_ipow(begin_x, 8)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + -0.0480484 *begin_dx*begin_dy + -0.00298569 *begin_x*begin_dy + -9.00426e-08 *begin_x*lens_ipow(begin_y, 3) + 0.0159279 *begin_dx*lens_ipow(begin_dy, 3) + -3.43394e-06 *lens_ipow(begin_y, 3)*begin_dx + 2.14353e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3) + 7.40119e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.165653 *begin_dx*begin_dy + 0.00388403 *begin_x*begin_dy + 4.6264e-05 *begin_x*begin_y + -0.185939 *lens_ipow(begin_dx, 3)*begin_dy + 0.00018597 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.00602759 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + 0.0888084 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -1.74525e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 2.25728e-10 *begin_x*lens_ipow(begin_y, 5) + -2.4079e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -0.0233997 *begin_y*begin_dx*lens_ipow(begin_dy, 6)*begin_lambda+0.0f;
    domega2_dx0(1, 1) =  + -0.0527133  + -0.00529584 *begin_lambda + 0.00390598 *lens_ipow(begin_lambda, 2) + 0.0119745 *lens_ipow(begin_dy, 2) + 2.04822e-05 *lens_ipow(begin_y, 2) + -0.00182397 *begin_y*begin_dy + 2.3132e-05 *lens_ipow(begin_x, 2) + -8.12406e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -8.72624e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dy + 5.64319e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + 2.59417e-13 *lens_ipow(begin_y, 8) + 0.00013036 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -1.60527e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -0.0233997 *begin_x*begin_dx*lens_ipow(begin_dy, 6)*begin_lambda+0.0f;
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
  out[4] =  + 0.428026  + 0.669092 *begin_lambda + -0.00856812 *begin_y*begin_dy + -0.917934 *lens_ipow(begin_lambda, 2) + -0.000117828 *lens_ipow(begin_y, 2) + -2.75349e-05 *lens_ipow(begin_x, 2) + -0.140668 *lens_ipow(begin_dy, 2) + -0.00140012 *begin_x*begin_dx + 0.443263 *lens_ipow(begin_lambda, 3) + -0.0378693 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -1.60958 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000328188 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.250632 *begin_x*lens_ipow(begin_dx, 3) + -0.000550324 *begin_x*begin_y*begin_dx*begin_dy + -0.000171223 *lens_ipow(begin_x, 3)*begin_dx + -0.00955229 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.0413526 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -2.717 *lens_ipow(begin_dx, 4) + -5.12412e-08 *lens_ipow(begin_y, 4) + -1.23914e-06 *lens_ipow(begin_x, 4) + -0.000360986 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -2.48997 *lens_ipow(begin_dy, 6) + -0.465764 *begin_y*lens_ipow(begin_dy, 7) + -0.0258935 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 8);
else
  out[4] = 0.0f;
} break;
