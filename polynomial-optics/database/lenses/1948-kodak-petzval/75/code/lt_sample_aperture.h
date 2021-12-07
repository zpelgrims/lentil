case kodak__petzval__1948__75mm:
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
       + 57.4823 *begin_dx + 0.792932 *begin_x + 0.943755 *begin_dx*begin_lambda + -0.00104947 *begin_x*begin_lambda + -0.674657 *begin_dx*lens_ipow(begin_lambda, 2) + 1.06447 *begin_dx*lens_ipow(begin_dy, 2) + 0.53491 *begin_y*begin_dx*begin_dy + 0.00733815 *lens_ipow(begin_y, 2)*begin_dx + 0.130534 *begin_x*lens_ipow(begin_dy, 2) + 0.581565 *begin_x*lens_ipow(begin_dx, 2) + 0.0103681 *begin_x*begin_y*begin_dy + 9.52381e-05 *begin_x*lens_ipow(begin_y, 2) + 0.0152241 *lens_ipow(begin_x, 2)*begin_dx + 6.84814e-05 *lens_ipow(begin_x, 3) + 2.35378e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 0.0391623 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.00218968 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 4.11882e-05 *lens_ipow(begin_x, 4)*begin_dx + 2.49864e-07 *lens_ipow(begin_x, 5) + -0.00731769 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 5.79366e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy*begin_lambda + 0.00766802 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -3.48429e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -5.99949e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 4.29734e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 902.434 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4)*begin_lambda + -0.227561 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + 0.00477086 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda,
       + 57.4524 *begin_dy + 0.791485 *begin_y + 0.976126 *begin_dy*begin_lambda + -0.703138 *begin_dy*lens_ipow(begin_lambda, 2) + 0.857903 *lens_ipow(begin_dy, 3) + 1.132 *lens_ipow(begin_dx, 2)*begin_dy + 0.661312 *begin_y*lens_ipow(begin_dy, 2) + 0.135676 *begin_y*lens_ipow(begin_dx, 2) + 0.0176535 *lens_ipow(begin_y, 2)*begin_dy + 9.89006e-05 *lens_ipow(begin_y, 3) + 0.546664 *begin_x*begin_dx*begin_dy + 0.0109245 *begin_x*begin_y*begin_dx + 0.00732155 *lens_ipow(begin_x, 2)*begin_dy + 0.000103683 *lens_ipow(begin_x, 2)*begin_y + 3.31081e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + -3.09155e-08 *lens_ipow(begin_x, 4)*begin_y + -1.75617 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -0.0632915 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 1.69709e-05 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 3.12373e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_lambda + 388.46 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -0.323506 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 9.86773e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 1.83922e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -0.157606 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + 4.07074e-10 *lens_ipow(begin_y, 7)*begin_lambda + -0.0909246 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + 1.97121e-11 *lens_ipow(begin_y, 8)*begin_dy
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 57.4823  + 0.943755 *begin_lambda + -0.674657 *lens_ipow(begin_lambda, 2) + 1.06447 *lens_ipow(begin_dy, 2) + 0.53491 *begin_y*begin_dy + 0.00733815 *lens_ipow(begin_y, 2) + 1.16313 *begin_x*begin_dx + 0.0152241 *lens_ipow(begin_x, 2) + 0.117487 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.00437935 *lens_ipow(begin_x, 3)*begin_dx + 4.11882e-05 *lens_ipow(begin_x, 4) + -0.00731769 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.015336 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -3.48429e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -1.1999e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 2707.3 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -0.227561 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda + 0.0143126 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + 2.12894 *begin_dx*begin_dy + 0.53491 *begin_y*begin_dx + 0.261069 *begin_x*begin_dy + 0.0103681 *begin_x*begin_y + 2.35378e-06 *begin_x*lens_ipow(begin_y, 3) + -0.0146354 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 5.79366e-06 *lens_ipow(begin_x, 3)*begin_y*begin_lambda + 0.015336 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -3.48429e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + 3609.73 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*begin_lambda + -0.910245 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.00477086 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + 2.264 *begin_dx*begin_dy + 0.271351 *begin_y*begin_dx + 0.546664 *begin_x*begin_dy + 0.0109245 *begin_x*begin_y + 3.12373e-06 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + 1553.84 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -0.970518 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.000197355 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.630422 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -0.0909246 *begin_x*begin_y*lens_ipow(begin_dy, 4)*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 57.4524  + 0.976126 *begin_lambda + -0.703138 *lens_ipow(begin_lambda, 2) + 2.57371 *lens_ipow(begin_dy, 2) + 1.132 *lens_ipow(begin_dx, 2) + 1.32262 *begin_y*begin_dy + 0.0176535 *lens_ipow(begin_y, 2) + 0.546664 *begin_x*begin_dx + 0.00732155 *lens_ipow(begin_x, 2) + 3.31081e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -7.0247 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -0.189874 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.69709e-05 *lens_ipow(begin_y, 4)*begin_lambda + 1165.38 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + -0.647012 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 9.86773e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.157606 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_lambda + -0.363698 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 1.97121e-11 *lens_ipow(begin_y, 8)+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 74.9367 *begin_dx + 0.559171 *begin_x + -0.0356345 *begin_x*begin_lambda + -33.8333 *begin_dx*lens_ipow(begin_dy, 2) + -36.6715 *lens_ipow(begin_dx, 3) + 0.387342 *begin_y*begin_dx*begin_dy + 0.0105698 *lens_ipow(begin_y, 2)*begin_dx + 0.0230449 *begin_x*lens_ipow(begin_lambda, 2) + 0.497955 *begin_x*lens_ipow(begin_dy, 2) + 0.683222 *begin_x*lens_ipow(begin_dx, 2) + 0.026242 *begin_x*begin_y*begin_dy + 0.000225033 *begin_x*lens_ipow(begin_y, 2) + 0.0312973 *lens_ipow(begin_x, 2)*begin_dx + 0.000170509 *lens_ipow(begin_x, 3) + 0.0366708 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + -0.0110508 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.0881114 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 0.00467901 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 8.37779e-05 *lens_ipow(begin_x, 4)*begin_dx + 4.98368e-07 *lens_ipow(begin_x, 5) + -24.1687 *begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + 966.921 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 0.013335 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.95093e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -2.24606e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 0.0464074 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 2.69425e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4) + -2.1526e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx*begin_dy;
    out(1) =  + 74.9328 *begin_dy + 0.5567 *begin_y + -0.0314397 *begin_y*begin_lambda + -36.538 *lens_ipow(begin_dy, 3) + -33.6448 *lens_ipow(begin_dx, 2)*begin_dy + 0.0234348 *begin_y*lens_ipow(begin_lambda, 2) + 0.904962 *begin_y*lens_ipow(begin_dy, 2) + 0.499684 *begin_y*lens_ipow(begin_dx, 2) + 0.0396098 *lens_ipow(begin_y, 2)*begin_dy + 0.000255214 *lens_ipow(begin_y, 3) + 0.389951 *begin_x*begin_dx*begin_dy + 0.0263001 *begin_x*begin_y*begin_dx + 0.0106163 *lens_ipow(begin_x, 2)*begin_dy + 0.000226134 *lens_ipow(begin_x, 2)*begin_y + -0.35716 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.0148585 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000153194 *lens_ipow(begin_y, 3)*begin_lambda + -12.2795 *lens_ipow(begin_dx, 4)*begin_dy + -0.00989095 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.151641 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.00814881 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 0.000147015 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 8.85507e-07 *lens_ipow(begin_y, 5)*begin_lambda + 717.515 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 0.0127703 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.64337e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -7.174e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7) + 1.62578e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5);
    out(2) =  + -1.41077 *begin_dx + -0.0237425 *begin_x + 0.000228357 *begin_x*begin_lambda + 0.00805638 *begin_dx*lens_ipow(begin_lambda, 2) + -0.609258 *begin_dx*lens_ipow(begin_dy, 2) + 0.811439 *lens_ipow(begin_dx, 3) + -0.0266665 *begin_y*begin_dx*begin_dy + -0.000187661 *lens_ipow(begin_y, 2)*begin_dx + -0.0191529 *begin_x*lens_ipow(begin_dy, 2) + -0.000581602 *begin_x*begin_y*begin_dy + -2.29633e-06 *begin_x*lens_ipow(begin_y, 2) + -0.000282644 *lens_ipow(begin_x, 2)*begin_dx + -4.30249e-07 *lens_ipow(begin_x, 3) + -0.17822 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.285396 *lens_ipow(begin_dx, 3)*begin_lambda + 1.56871 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 1.10147 *lens_ipow(begin_dx, 5) + 0.0308593 *begin_x*lens_ipow(begin_dx, 4) + -3.48159e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -7.82533e-07 *lens_ipow(begin_x, 4)*begin_dx + -4.8851e-09 *lens_ipow(begin_x, 5) + -0.0042067 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 3.26623e-05 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 10.811 *begin_dx*lens_ipow(begin_dy, 6) + 2.12768e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 6.07811e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 1.05317 *begin_y*begin_dx*lens_ipow(begin_dy, 7) + -5.56842e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2);
    out(3) =  + -1.4106 *begin_dy + -0.0237204 *begin_y + 0.000220932 *begin_y*begin_lambda + 0.00808681 *begin_dy*lens_ipow(begin_lambda, 2) + 0.865591 *lens_ipow(begin_dy, 3) + 2.0713 *lens_ipow(begin_dx, 2)*begin_dy + 0.00124743 *begin_y*lens_ipow(begin_dx, 2) + -0.000312025 *lens_ipow(begin_y, 2)*begin_dy + -9.49796e-07 *lens_ipow(begin_y, 3) + 0.0421317 *begin_x*begin_dx*begin_dy + -6.95144e-05 *begin_x*begin_y*begin_dx + 0.00017649 *lens_ipow(begin_x, 2)*begin_dy + 2.70334e-07 *lens_ipow(begin_x, 2)*begin_y + -0.361026 *lens_ipow(begin_dy, 3)*begin_lambda + 0.469788 *lens_ipow(begin_dy, 5) + 0.725501 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.0473506 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 0.00039545 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -1.3035e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 3.47813e-06 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -5.30324e-08 *lens_ipow(begin_x, 3)*begin_y*begin_dx + -2.30227 *lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + 0.000259663 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -1.02084e-07 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + -0.0123655 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 0.000604071 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + 0.000596529 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4) + 0.0143264 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 7);
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
    domega2_dx0(0, 0) =  + -0.0237425  + 0.000228357 *begin_lambda + -0.0191529 *lens_ipow(begin_dy, 2) + -0.000581602 *begin_y*begin_dy + -2.29633e-06 *lens_ipow(begin_y, 2) + -0.000565288 *begin_x*begin_dx + -1.29075e-06 *lens_ipow(begin_x, 2) + 0.0308593 *lens_ipow(begin_dx, 4) + -0.000104448 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -3.13013e-06 *lens_ipow(begin_x, 3)*begin_dx + -2.44255e-08 *lens_ipow(begin_x, 4) + -0.0042067 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 3.26623e-05 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 4.25535e-08 *begin_x*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 2.43124e-08 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_dy + -1.67053e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(0, 1) =  + -0.0266665 *begin_dx*begin_dy + -0.000375323 *begin_y*begin_dx + -0.000581602 *begin_x*begin_dy + -4.59265e-06 *begin_x*begin_y + 3.26623e-05 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + 6.38303e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 6.07811e-09 *lens_ipow(begin_x, 4)*begin_dx*begin_dy + 1.05317 *begin_dx*lens_ipow(begin_dy, 7) + -2.22737e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)+0.0f;
    domega2_dx0(1, 0) =  + 0.0421317 *begin_dx*begin_dy + -6.95144e-05 *begin_y*begin_dx + 0.000352979 *begin_x*begin_dy + 5.40667e-07 *begin_x*begin_y + -0.0473506 *lens_ipow(begin_dx, 3)*begin_dy + 0.00039545 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -2.60699e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 1.04344e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -1.59097e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.00120814 *begin_x*lens_ipow(begin_dy, 5) + 0.000596529 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4)+0.0f;
    domega2_dx0(1, 1) =  + -0.0237204  + 0.000220932 *begin_lambda + 0.00124743 *lens_ipow(begin_dx, 2) + -0.00062405 *begin_y*begin_dy + -2.84939e-06 *lens_ipow(begin_y, 2) + -6.95144e-05 *begin_x*begin_dx + 2.70334e-07 *lens_ipow(begin_x, 2) + 0.00039545 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -2.60699e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -5.30324e-08 *lens_ipow(begin_x, 3)*begin_dx + 0.000519327 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -4.08336e-07 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -0.0123655 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 0.000596529 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4) + 0.0143264 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 7)+0.0f;
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
  out[4] =  + 0.536243  + 0.642199 *begin_lambda + -0.886373 *lens_ipow(begin_lambda, 2) + 0.430306 *lens_ipow(begin_lambda, 3) + -0.0109956 *begin_y*lens_ipow(begin_dy, 3) + -0.0014622 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00037113 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -4.38639e-05 *lens_ipow(begin_y, 3)*begin_dy + -3.12592e-07 *lens_ipow(begin_y, 4) + -0.00155101 *begin_x*begin_y*begin_dx*begin_dy + -4.39688e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000373607 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000758671 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -4.48764e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -9.54764e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -3.72116e-05 *lens_ipow(begin_x, 3)*begin_dx + -3.56172e-07 *lens_ipow(begin_x, 4) + -6.2983e-10 *lens_ipow(begin_y, 6) + -1.7983e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -6.51094e-11 *lens_ipow(begin_y, 7)*begin_dy + -1.53291e-10 *lens_ipow(begin_x, 7)*begin_dx + -1.80773e-12 *lens_ipow(begin_x, 8) + 3947.27 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 4) + 0.0473381 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + 1.30911e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -2.64202e-14 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4) + -0.000234129 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 5)*begin_dy*begin_lambda + 8.92788e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_lambda;
else
  out[4] = 0.0f;
} break;
