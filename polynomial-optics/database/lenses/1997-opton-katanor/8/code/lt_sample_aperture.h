case opton__katanor__1997__8mm:
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
       + 18.7155 *begin_dx + 0.212004 *begin_x + 1.63457 *begin_dx*lens_ipow(begin_dy, 2) + 1.37548 *lens_ipow(begin_dx, 3) + 0.833112 *begin_y*begin_dx*begin_dy + 0.12976 *begin_x*lens_ipow(begin_dy, 2) + 0.929414 *begin_x*lens_ipow(begin_dx, 2) + -0.00133904 *begin_x*lens_ipow(begin_y, 2) + -0.00108509 *lens_ipow(begin_x, 3) + 0.00938185 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.00699149 *begin_x*begin_y*begin_dy*begin_lambda + 0.0200721 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 5.32923 *begin_dx*lens_ipow(begin_dy, 4) + 11.0318 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 7.9547 *lens_ipow(begin_dx, 5) + 0.488131 *begin_x*lens_ipow(begin_dx, 4) + 0.0298308 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -9.57654e-06 *lens_ipow(begin_x, 5) + -0.747441 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -0.000470283 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.000403633 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 4.42048e-06 *lens_ipow(begin_x, 5)*begin_lambda + 0.000115456 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2)*begin_lambda + -7.89244e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -3.97933e-06 *lens_ipow(begin_x, 5)*begin_y*begin_dy*begin_lambda + -3.78966e-06 *lens_ipow(begin_y, 6)*begin_dx*lens_ipow(begin_lambda, 2) + -1.86558e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -3.12644e-11 *begin_x*lens_ipow(begin_y, 10),
       + 18.7159 *begin_dy + 0.21049 *begin_y + 1.70613 *lens_ipow(begin_dy, 3) + 1.53398 *lens_ipow(begin_dx, 2)*begin_dy + 0.969774 *begin_y*lens_ipow(begin_dy, 2) + 0.132787 *begin_y*lens_ipow(begin_dx, 2) + -0.00102434 *lens_ipow(begin_y, 3) + 0.86662 *begin_x*begin_dx*begin_dy + -0.0010268 *lens_ipow(begin_x, 2)*begin_y + 0.0149868 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.00705968 *begin_x*begin_y*begin_dx*begin_lambda + 0.0102134 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 5.74135 *lens_ipow(begin_dy, 5) + 11.7558 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 6.0209 *lens_ipow(begin_dx, 4)*begin_dy + -1.04835e-05 *lens_ipow(begin_y, 5) + -0.0017076 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -1.4277e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.00169232 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -7.82022e-06 *lens_ipow(begin_x, 4)*begin_y + -0.777232 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + 5.31462e-06 *lens_ipow(begin_y, 5)*begin_lambda + -0.000143882 *lens_ipow(begin_x, 4)*begin_dy*begin_lambda + -2.85648e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -1.59902e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + -5.68608e-08 *begin_x*lens_ipow(begin_y, 7)*begin_dx + -5.11094e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -1.33292e-07 *lens_ipow(begin_y, 8)*begin_dy*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 18.7155  + 1.63457 *lens_ipow(begin_dy, 2) + 4.12645 *lens_ipow(begin_dx, 2) + 0.833112 *begin_y*begin_dy + 1.85883 *begin_x*begin_dx + 0.00938185 *lens_ipow(begin_y, 2)*begin_lambda + 0.0200721 *lens_ipow(begin_x, 2)*begin_lambda + 5.32923 *lens_ipow(begin_dy, 4) + 33.0955 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 39.7735 *lens_ipow(begin_dx, 4) + 1.95252 *begin_x*lens_ipow(begin_dx, 3) + 0.0894923 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -2.24232 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.000470283 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -0.000403633 *lens_ipow(begin_x, 4)*begin_lambda + -3.78966e-06 *lens_ipow(begin_y, 6)*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(0, 1) =  + 3.26914 *begin_dx*begin_dy + 0.833112 *begin_y*begin_dx + 0.259521 *begin_x*begin_dy + 0.00699149 *begin_x*begin_y*begin_lambda + 21.3169 *begin_dx*lens_ipow(begin_dy, 3) + 22.0637 *lens_ipow(begin_dx, 3)*begin_dy + 0.000230912 *begin_x*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -7.89244e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_lambda + -3.97933e-06 *lens_ipow(begin_x, 5)*begin_y*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + 3.06797 *begin_dx*begin_dy + 0.265575 *begin_y*begin_dx + 0.86662 *begin_x*begin_dy + 0.00705968 *begin_x*begin_y*begin_lambda + 23.5116 *begin_dx*lens_ipow(begin_dy, 3) + 24.0836 *lens_ipow(begin_dx, 3)*begin_dy + -0.0017076 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -0.00169232 *lens_ipow(begin_x, 3)*begin_dy + -1.59902e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_lambda + -5.68608e-08 *begin_x*lens_ipow(begin_y, 7)+0.0f;
    dx1_domega0(1, 1) =  + 18.7159  + 5.11838 *lens_ipow(begin_dy, 2) + 1.53398 *lens_ipow(begin_dx, 2) + 1.93955 *begin_y*begin_dy + 0.86662 *begin_x*begin_dx + 0.0149868 *lens_ipow(begin_y, 2)*begin_lambda + 0.0102134 *lens_ipow(begin_x, 2)*begin_lambda + 28.7067 *lens_ipow(begin_dy, 4) + 35.2674 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 6.0209 *lens_ipow(begin_dx, 4) + -0.0017076 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.00169232 *lens_ipow(begin_x, 3)*begin_dx + -2.3317 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.000143882 *lens_ipow(begin_x, 4)*begin_lambda + -2.85648e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_lambda + -1.02219e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dy + -1.33292e-07 *lens_ipow(begin_y, 8)*begin_lambda+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 7.22481 *begin_dx + -3.66916 *begin_x + 1.13935 *begin_dx*begin_lambda + -0.107979 *begin_x*begin_lambda + 0.0497219 *lens_ipow(begin_y, 2)*begin_dx + 0.0849807 *begin_x*lens_ipow(begin_dx, 2) + 0.00600088 *begin_x*lens_ipow(begin_y, 2) + 0.00624019 *lens_ipow(begin_x, 3) + 0.177711 *begin_x*begin_y*begin_dy*begin_lambda + 0.210299 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -0.161629 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.171108 *begin_x*begin_y*lens_ipow(begin_dy, 3) + -0.3263 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.000736275 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -5.92794e-05 *begin_x*lens_ipow(begin_y, 4) + 0.00134687 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 0.00075912 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.000124396 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.00117025 *lens_ipow(begin_x, 4)*begin_dx + -0.233864 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 3) + -0.000239904 *lens_ipow(begin_x, 5)*begin_lambda + 0.000219276 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 2) + 224.685 *lens_ipow(begin_dx, 9) + -35.8209 *begin_y*begin_dx*lens_ipow(begin_dy, 7) + -220.156 *begin_y*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + 0.0252482 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 5) + -170.111 *begin_x*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + 2141.21 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 6)*begin_lambda;
    out(1) =  + 7.35994 *begin_dy + -3.66475 *begin_y + 1.1629 *begin_dy*begin_lambda + -0.101463 *begin_y*begin_lambda + -2.19358 *lens_ipow(begin_dy, 3) + 0.00565994 *lens_ipow(begin_y, 3) + 0.0471934 *lens_ipow(begin_x, 2)*begin_dy + 0.00448502 *lens_ipow(begin_x, 2)*begin_y + 0.186474 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.105916 *begin_x*begin_y*begin_dx*begin_lambda + 0.00125623 *lens_ipow(begin_y, 4)*begin_dy + 0.00156435 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -0.203183 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -0.000203478 *lens_ipow(begin_y, 5)*begin_lambda + -0.709852 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 78.5292 *lens_ipow(begin_dy, 7) + 0.00018357 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 2) + -0.524387 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -2.13244e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + 5.95196e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -2.28766e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -6.83984e-07 *lens_ipow(begin_x, 6)*begin_y + -165.431 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6) + -245.723 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5) + -29.6761 *begin_x*lens_ipow(begin_dx, 7)*begin_dy + -1.38489e-05 *begin_x*lens_ipow(begin_y, 6)*begin_dx*begin_dy + 0.0286787 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 5) + 2186.56 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3)*begin_lambda;
    out(2) =  + -0.13587 *begin_dx + -0.066524 *begin_x + 0.0130168 *begin_dx*begin_lambda + 0.00465117 *begin_x*begin_lambda + 0.0406427 *begin_dx*lens_ipow(begin_dy, 2) + 0.027374 *lens_ipow(begin_dx, 3) + 0.000251407 *begin_x*lens_ipow(begin_y, 2) + -0.000869781 *lens_ipow(begin_x, 2)*begin_dx + 0.000355825 *lens_ipow(begin_x, 3) + -0.00161326 *begin_x*begin_y*begin_dy*begin_lambda + 0.413343 *begin_dx*lens_ipow(begin_dy, 4) + 0.784638 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.421791 *lens_ipow(begin_dx, 5) + 0.00225631 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -3.99103e-06 *lens_ipow(begin_y, 4)*begin_dx + -0.0044946 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -2.82341e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 1.49506e-06 *begin_x*lens_ipow(begin_y, 4) + -3.5227e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -2.90841e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 2.63178e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -2.8845e-05 *lens_ipow(begin_x, 4)*begin_dx + 9.37519e-07 *lens_ipow(begin_x, 5) + 0.00192499 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -0.00677485 *begin_x*begin_y*lens_ipow(begin_dy, 5) + -0.000105174 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 5) + -0.000109281 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 5) + -0.000948575 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 7);
    out(3) =  + -0.136414 *begin_dy + -0.0666188 *begin_y + 0.0127708 *begin_dy*begin_lambda + 0.00457627 *begin_y*begin_lambda + 0.0495904 *lens_ipow(begin_dy, 3) + 0.117236 *lens_ipow(begin_dx, 2)*begin_dy + -0.00204596 *begin_y*lens_ipow(begin_dx, 2) + -0.000867126 *lens_ipow(begin_y, 2)*begin_dy + 0.000379246 *lens_ipow(begin_y, 3) + -0.000611837 *lens_ipow(begin_x, 2)*begin_dy + 0.000477685 *lens_ipow(begin_x, 2)*begin_y + -0.00440404 *begin_x*begin_y*begin_dx*begin_lambda + 0.320002 *lens_ipow(begin_dy, 5) + -3.03489e-05 *lens_ipow(begin_y, 4)*begin_dy + 0.00405186 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.00237707 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -3.25788e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 2.33356 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5) + 1.04051e-08 *lens_ipow(begin_y, 7) + -0.0101119 *begin_x*begin_y*lens_ipow(begin_dx, 5) + -4.59191e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dx + 3.03579e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -0.000204388 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.000102521 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 5) + -0.00010398 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 5) + -4.21288e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_dx + -15.3524 *begin_x*lens_ipow(begin_dx, 7)*lens_ipow(begin_dy, 3) + -0.022289 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4);
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
    domega2_dx0(0, 0) =  + -0.066524  + 0.00465117 *begin_lambda + 0.000251407 *lens_ipow(begin_y, 2) + -0.00173956 *begin_x*begin_dx + 0.00106748 *lens_ipow(begin_x, 2) + -0.00161326 *begin_y*begin_dy*begin_lambda + -0.0044946 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -2.82341e-05 *lens_ipow(begin_y, 3)*begin_dy + 1.49506e-06 *lens_ipow(begin_y, 4) + -7.04539e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -8.72522e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 7.89533e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00011538 *lens_ipow(begin_x, 3)*begin_dx + 4.68759e-06 *lens_ipow(begin_x, 4) + 0.00192499 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -0.00677485 *begin_y*lens_ipow(begin_dy, 5) + -0.000105174 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 5) + -0.000327842 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 5) + -0.0037943 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 7)+0.0f;
    domega2_dx0(0, 1) =  + 0.000502814 *begin_x*begin_y + -0.00161326 *begin_x*begin_dy*begin_lambda + 0.00451262 *begin_y*lens_ipow(begin_dx, 3) + -1.59641e-05 *lens_ipow(begin_y, 3)*begin_dx + -0.0044946 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -8.47022e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 5.98022e-06 *begin_x*lens_ipow(begin_y, 3) + -7.04539e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx + -2.90841e-05 *lens_ipow(begin_x, 3)*begin_dy + 5.26355e-06 *lens_ipow(begin_x, 3)*begin_y + 0.00192499 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + -0.00677485 *begin_x*lens_ipow(begin_dy, 5) + -0.000210348 *begin_x*begin_y*lens_ipow(begin_lambda, 5)+0.0f;
    domega2_dx0(1, 0) =  + -0.00122367 *begin_x*begin_dy + 0.00095537 *begin_x*begin_y + -0.00440404 *begin_y*begin_dx*begin_lambda + 0.00405186 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.00475413 *begin_x*lens_ipow(begin_dy, 3) + -6.51575e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -0.0101119 *begin_y*lens_ipow(begin_dx, 5) + -4.59191e-07 *lens_ipow(begin_y, 5)*begin_dx + 6.07158e-08 *begin_x*lens_ipow(begin_y, 5) + -0.000613165 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00020796 *begin_x*begin_y*lens_ipow(begin_lambda, 5) + -2.10644e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx + -15.3524 *lens_ipow(begin_dx, 7)*lens_ipow(begin_dy, 3) + -0.022289 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4)+0.0f;
    domega2_dx0(1, 1) =  + -0.0666188  + 0.00457627 *begin_lambda + -0.00204596 *lens_ipow(begin_dx, 2) + -0.00173425 *begin_y*begin_dy + 0.00113774 *lens_ipow(begin_y, 2) + 0.000477685 *lens_ipow(begin_x, 2) + -0.00440404 *begin_x*begin_dx*begin_lambda + -0.000121396 *lens_ipow(begin_y, 3)*begin_dy + 0.00405186 *begin_x*begin_dx*lens_ipow(begin_lambda, 2) + -6.51575e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 7.28358e-08 *lens_ipow(begin_y, 6) + -0.0101119 *begin_x*lens_ipow(begin_dx, 5) + -2.29596e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx + 1.51789e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -0.000204388 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + -0.000307564 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 5) + -0.00010398 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 5) + -1.26386e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx + -0.0668669 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4)+0.0f;
    Eigen::Matrix2d invJ = domega2_dx0.inverse().eval();
    Eigen::Vector2d solution_pos = 0.72 * invJ * delta_out; // default newton-raphson
    x += solution_pos(0);
    y += solution_pos(1);
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
  out[4] =  + -0.0818696  + 1.31494 *begin_lambda + -2.60344 *lens_ipow(begin_lambda, 2) + -0.000664144 *begin_y*begin_dy + -0.000551075 *begin_x*begin_dx + 2.45113 *lens_ipow(begin_lambda, 3) + -0.900521 *lens_ipow(begin_lambda, 4) + -0.105226 *lens_ipow(begin_dy, 4) + -0.21402 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.1052 *lens_ipow(begin_dx, 4) + -0.000367576 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -2.59867e-06 *lens_ipow(begin_y, 4) + -0.000391611 *begin_x*begin_y*begin_dx*begin_dy + -5.23038e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -2.67358e-06 *lens_ipow(begin_x, 4) + -0.0006847 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_lambda + -1.4906e-05 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -0.0314894 *begin_y*lens_ipow(begin_dy, 5) + -0.000161724 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -0.0310621 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.0301986 *begin_x*lens_ipow(begin_dx, 5) + -7.15797e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_lambda + -0.00145141 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -0.764751 *lens_ipow(begin_dy, 8) + -0.81172 *lens_ipow(begin_dx, 8) + -36.3476 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 4) + 0.452695 *begin_x*begin_y*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3) + -17.8266 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 8)*begin_lambda;
else
  out[4] = 0.0f;
} break;
