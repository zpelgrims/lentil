case meyer_optik_goerlitz__primoplan__1936__75mm:
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
       + 47.0034 *begin_dx + 0.587174 *begin_x + 1.33686 *begin_y*begin_dx*begin_dy + 0.0322488 *begin_x*begin_y*begin_dy + 0.0360982 *lens_ipow(begin_x, 2)*begin_dx + 15.6255 *lens_ipow(begin_dx, 3) + 21.4697 *begin_dx*lens_ipow(begin_dy, 2) + 0.000262752 *begin_x*lens_ipow(begin_y, 2) + 0.778028 *begin_x*lens_ipow(begin_dy, 2) + 1.69536 *begin_x*lens_ipow(begin_dx, 2) + 0.0148954 *lens_ipow(begin_y, 2)*begin_dx + 0.000428019 *lens_ipow(begin_x, 3)*begin_lambda + -5.02979e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 5.68624 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + -2.33808e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -4.53937e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 0.000119501 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 2) + 0.000414493 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -1.68624e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx + 0.0203951 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 1.03832 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -8.32952e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 2) + -2.74603e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 81.2628 *begin_x*lens_ipow(begin_dx, 6)*lens_ipow(begin_lambda, 3) + 7.6954e-05 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -8.79204e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 3313.51 *lens_ipow(begin_dx, 9)*lens_ipow(begin_lambda, 2) + -3.83583e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2),
       + 0.591943 *begin_y + 46.4005 *begin_dy + 1.5057 *begin_dy*begin_lambda + 0.824423 *begin_y*lens_ipow(begin_dx, 2) + 0.027811 *lens_ipow(begin_y, 2)*begin_dy + 1.30781 *begin_y*lens_ipow(begin_dy, 2) + 1.29332 *begin_x*begin_dx*begin_dy + 0.0322068 *begin_x*begin_y*begin_dx + 21.1912 *lens_ipow(begin_dx, 2)*begin_dy + 0.000266444 *lens_ipow(begin_x, 2)*begin_y + 0.0144468 *lens_ipow(begin_x, 2)*begin_dy + 10.8321 *lens_ipow(begin_dy, 3) + 0.000272145 *lens_ipow(begin_y, 3)*begin_lambda + -6.46083e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.00013376 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.0169126 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 13.3259 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 0.843646 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.000247138 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -2.26643e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -1.84505 *begin_y*lens_ipow(begin_dx, 6) + -3.96203e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -1.23991e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + 21.6211 *begin_y*lens_ipow(begin_dy, 6)*begin_lambda + 648.27 *lens_ipow(begin_dy, 7)*begin_lambda + -3.88112e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 1.54248e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -4.97352e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 47.0034  + 1.33686 *begin_y*begin_dy + 0.0360982 *lens_ipow(begin_x, 2) + 46.8766 *lens_ipow(begin_dx, 2) + 21.4697 *lens_ipow(begin_dy, 2) + 3.39072 *begin_x*begin_dx + 0.0148954 *lens_ipow(begin_y, 2) + 22.7449 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + 0.000119501 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 2) + 0.000828986 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.68624e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + 0.0407903 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_lambda, 2) + 3.11496 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -2.74603e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_lambda + 487.577 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 3) + 0.000153908 *begin_x*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -8.79204e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3)*begin_lambda + 29821.5 *lens_ipow(begin_dx, 8)*lens_ipow(begin_lambda, 2) + -7.67166e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2)+0.0f;
    dx1_domega0(0, 1) =  + 1.33686 *begin_y*begin_dx + 0.0322488 *begin_x*begin_y + 42.9393 *begin_dx*begin_dy + 1.55606 *begin_x*begin_dy + -2.33808e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 0.000414493 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 0.000153908 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.000263761 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + 1.64885 *begin_y*begin_dx + 1.29332 *begin_x*begin_dy + 0.0322068 *begin_x*begin_y + 42.3824 *begin_dx*begin_dy + 0.000247138 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2) + -2.26643e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -11.0703 *begin_y*lens_ipow(begin_dx, 5) + 3.08497e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 46.4005  + 1.5057 *begin_lambda + 0.027811 *lens_ipow(begin_y, 2) + 2.61562 *begin_y*begin_dy + 1.29332 *begin_x*begin_dx + 21.1912 *lens_ipow(begin_dx, 2) + 0.0144468 *lens_ipow(begin_x, 2) + 32.4963 *lens_ipow(begin_dy, 2) + 0.00013376 *lens_ipow(begin_y, 4)*begin_lambda + 0.0338253 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 53.3036 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + 2.53094 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.000494275 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy + -1.23991e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 129.726 *begin_y*lens_ipow(begin_dy, 5)*begin_lambda + 4537.89 *lens_ipow(begin_dy, 6)*begin_lambda + -3.88112e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_lambda + 1.54248e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_lambda + -9.94703e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dy*lens_ipow(begin_lambda, 2)+0.0f;
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
    out(0) =  + 74.3729 *begin_dx + 0.548261 *begin_x + 0.0427014 *begin_x*begin_lambda + 0.999157 *begin_y*begin_dx*begin_dy + 0.0546769 *begin_x*begin_y*begin_dy + 0.0355027 *lens_ipow(begin_x, 2)*begin_dx + -54.0885 *lens_ipow(begin_dx, 3) + -16.4536 *begin_dx*lens_ipow(begin_dy, 2) + 0.000502652 *begin_x*lens_ipow(begin_y, 2) + 0.00030755 *lens_ipow(begin_x, 3) + 1.15636 *begin_x*lens_ipow(begin_dy, 2) + 0.0209714 *lens_ipow(begin_y, 2)*begin_dx + 0.000157029 *lens_ipow(begin_x, 4)*begin_dx + 22.336 *begin_x*lens_ipow(begin_dx, 4) + 0.934896 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 239.46 *lens_ipow(begin_dx, 5) + 0.0190638 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -3.24376e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -7.53372e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 0.00026207 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 2) + -4.45635e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -0.0058457 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4) + 0.000411725 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + 5.17115e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -4.70474e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + -3.13612e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.64642e-08 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 2) + 1.2039e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_lambda;
    out(1) =  + 0.563745 *begin_y + 74.387 *begin_dy + 1.40325 *begin_y*lens_ipow(begin_dx, 2) + 0.0353195 *lens_ipow(begin_y, 2)*begin_dy + 0.957993 *begin_x*begin_dx*begin_dy + 0.0581066 *begin_x*begin_y*begin_dx + -16.1042 *lens_ipow(begin_dx, 2)*begin_dy + 0.000527282 *lens_ipow(begin_x, 2)*begin_y + 0.0206002 *lens_ipow(begin_x, 2)*begin_dy + -55.1489 *lens_ipow(begin_dy, 3) + 0.00100367 *lens_ipow(begin_y, 3)*begin_lambda + -1.12448 *begin_y*lens_ipow(begin_dx, 4) + 0.000142532 *lens_ipow(begin_y, 4)*begin_dy + 251.916 *lens_ipow(begin_dy, 5) + 1.00812 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 24.1404 *begin_y*lens_ipow(begin_dy, 4) + -0.000705614 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + 0.0193259 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00173492 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.228152 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.368587 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.0101003 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -3.60603e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + 9.81969 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -2.64143e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -7.39152e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -1.02618e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dy + -8.75363e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy*begin_lambda;
    out(2) =  + -1.42183 *begin_dx + -0.0241991 *begin_x + -0.000668816 *begin_x*begin_lambda + -0.0332679 *begin_y*begin_dx*begin_dy + -0.000987251 *begin_x*begin_y*begin_dy + -0.000517502 *lens_ipow(begin_x, 2)*begin_dx + 0.771737 *lens_ipow(begin_dx, 3) + -0.732032 *begin_dx*lens_ipow(begin_dy, 2) + -5.006e-06 *begin_x*lens_ipow(begin_y, 2) + -0.0268585 *begin_x*lens_ipow(begin_dy, 2) + -0.000283691 *lens_ipow(begin_y, 2)*begin_dx + -0.00955396 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 1.14598e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 2.26994e-07 *lens_ipow(begin_y, 4)*begin_dx + 8.72484e-09 *begin_x*lens_ipow(begin_y, 4) + -0.00160515 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.00108655 *begin_x*begin_y*lens_ipow(begin_dy, 3) + -3.67636e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.943887 *lens_ipow(begin_dx, 5)*begin_lambda + -0.0706228 *begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -2.95962e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 4.56802e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dy + -0.00316156 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 1.91489e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 1.06393e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*begin_dx + 2.48312e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -2.86637e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -8.12142e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3);
    out(3) =  + -0.0233939 *begin_y + -1.4288 *begin_dy + -0.00399883 *begin_y*begin_lambda + -0.000443605 *lens_ipow(begin_y, 2)*begin_dy + 0.0497743 *begin_x*begin_dx*begin_dy + -0.000117589 *begin_x*begin_y*begin_dx + 2.336 *lens_ipow(begin_dx, 2)*begin_dy + 0.00296588 *begin_y*lens_ipow(begin_lambda, 2) + 3.00341e-06 *lens_ipow(begin_x, 2)*begin_y + 0.000251606 *lens_ipow(begin_x, 2)*begin_dy + 0.858271 *lens_ipow(begin_dy, 3) + 0.00293992 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.97645 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 2.74344e-07 *lens_ipow(begin_x, 4)*begin_dy + -0.506394 *lens_ipow(begin_dy, 5) + 5.55952e-05 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -2.29517 *lens_ipow(begin_dx, 4)*begin_dy + 0.00249138 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 5.9028e-10 *lens_ipow(begin_y, 6)*begin_dy + -3.38355e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + 5.17532e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -1.24752e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + 3.47302e-14 *lens_ipow(begin_y, 9) + 3.42649e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 5.56799e-14 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5)*begin_dx + -7.27451e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*lens_ipow(begin_dy, 2) + 9.3353e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + 3.79664e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6)*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.0241991  + -0.000668816 *begin_lambda + -0.000987251 *begin_y*begin_dy + -0.001035 *begin_x*begin_dx + -5.006e-06 *lens_ipow(begin_y, 2) + -0.0268585 *lens_ipow(begin_dy, 2) + -0.00955396 *lens_ipow(begin_dx, 2)*begin_lambda + 3.43795e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 8.72484e-09 *lens_ipow(begin_y, 4) + -0.00108655 *begin_y*lens_ipow(begin_dy, 3) + -3.67636e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -8.87887e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.37041e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -0.00632312 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 7.65957e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 4.25573e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx + 1.24156e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + -8.59912e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -2.43643e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(0, 1) =  + -0.0332679 *begin_dx*begin_dy + -0.000987251 *begin_x*begin_dy + -1.0012e-05 *begin_x*begin_y + -0.000567381 *begin_y*begin_dx + 2.29197e-08 *lens_ipow(begin_x, 3)*begin_y + 9.07977e-07 *lens_ipow(begin_y, 3)*begin_dx + 3.48994e-08 *begin_x*lens_ipow(begin_y, 3) + -0.00321031 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00108655 *begin_x*lens_ipow(begin_dy, 3) + -7.35272e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -0.0706228 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 1.37041e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 3.82978e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 4.25573e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx + 9.93247e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3) + -8.59912e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -2.43643e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0497743 *begin_dx*begin_dy + -0.000117589 *begin_y*begin_dx + 6.00682e-06 *begin_x*begin_y + 0.000503213 *begin_x*begin_dy + 0.00587984 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.09738e-06 *lens_ipow(begin_x, 3)*begin_dy + 0.000166786 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.00249138 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 5.17532e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -2.49504e-08 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + 1.3706e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + 2.784e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_dx + -2.18235e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx*lens_ipow(begin_dy, 2) + 3.73412e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + 1.51866e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.0233939  + -0.00399883 *begin_lambda + -0.000887209 *begin_y*begin_dy + -0.000117589 *begin_x*begin_dx + 0.00296588 *lens_ipow(begin_lambda, 2) + 3.00341e-06 *lens_ipow(begin_x, 2) + 0.00249138 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 3.54168e-09 *lens_ipow(begin_y, 5)*begin_dy + -1.69178e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 0.000103506 *begin_x*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -3.74256e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 3.12571e-13 *lens_ipow(begin_y, 8) + 1.71325e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 2.784e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_dx + -3.63725e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*lens_ipow(begin_dy, 2) + 4.66765e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + 2.27798e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_dy+0.0f;
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
  out[4] =  + 0.499251  + 0.30352 *begin_lambda + 0.00954575 *begin_x*begin_dx + 0.000120815 *lens_ipow(begin_x, 2) + 0.194113 *lens_ipow(begin_dx, 2) + -0.205168 *lens_ipow(begin_lambda, 2) + -2.43666 *lens_ipow(begin_dx, 4) + -0.0547166 *begin_y*lens_ipow(begin_dy, 3) + -0.00216465 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.207842 *begin_x*lens_ipow(begin_dx, 3) + -3.79076 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000108067 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.82005 *lens_ipow(begin_dy, 4) + -0.000107596 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -1.37128e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.00732194 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.172062 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000117609 *lens_ipow(begin_x, 3)*begin_dx + -0.178241 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -7.37832e-07 *lens_ipow(begin_x, 4) + -0.00867062 *begin_x*begin_y*begin_dx*begin_dy + -0.00223053 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -3.77281e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -4.32804e-07 *lens_ipow(begin_y, 5)*begin_dy + -5.29755e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3) + 3.03829e-10 *lens_ipow(begin_y, 7)*begin_dy + -3.9889e-12 *lens_ipow(begin_y, 8) + -3.03021e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 4);
else
  out[4] = 0.0f;
} break;
