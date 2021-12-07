case cooke__speed_panchro__1920__75mm:
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
       + 52.6321 *begin_dx + 0.645828 *begin_x + 0.0791184 *begin_x*begin_lambda + 6.31981 *begin_dx*begin_lambda + -0.000310767 *begin_x*begin_y*begin_dy + -39.8821 *lens_ipow(begin_dx, 3) + -0.0556604 *begin_x*lens_ipow(begin_lambda, 2) + -41.3013 *begin_dx*lens_ipow(begin_dy, 2) + 1.52245e-05 *begin_x*lens_ipow(begin_y, 2) + -0.289697 *begin_x*lens_ipow(begin_dy, 2) + -0.689895 *begin_x*lens_ipow(begin_dx, 2) + 0.00105637 *lens_ipow(begin_y, 2)*begin_dx + -4.33794 *begin_dx*lens_ipow(begin_lambda, 2) + 2.88555e-05 *lens_ipow(begin_x, 3)*begin_lambda + -2.13337 *begin_y*begin_dx*begin_dy*begin_lambda + 3.95429 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -1.40871 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 9.22576e-05 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 0.202471 *begin_x*lens_ipow(begin_dy, 4) + -0.655789 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -0.0121823 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -2.4027 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -53.9922 *lens_ipow(begin_dx, 5)*begin_lambda + -2.17019 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + -0.0368727 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4) + 0.00101783 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -165.73 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 1.74247e-05 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_lambda, 3),
       + 0.641888 *begin_y + 52.7206 *begin_dy + 5.9613 *begin_dy*begin_lambda + 0.0882786 *begin_y*begin_lambda + -0.277811 *begin_y*lens_ipow(begin_dx, 2) + -0.673662 *begin_y*lens_ipow(begin_dy, 2) + -0.431014 *begin_x*begin_dx*begin_dy + -40.9004 *lens_ipow(begin_dx, 2)*begin_dy + -0.0604279 *begin_y*lens_ipow(begin_lambda, 2) + 1.80004e-05 *lens_ipow(begin_x, 2)*begin_y + -3.96818 *begin_dy*lens_ipow(begin_lambda, 2) + 1.66599e-05 *lens_ipow(begin_y, 3) + 0.0007109 *lens_ipow(begin_x, 2)*begin_dy + -39.7066 *lens_ipow(begin_dy, 3) + 0.0673625 *begin_x*begin_dx*begin_dy*begin_lambda + 0.211083 *begin_y*lens_ipow(begin_dx, 4) + -0.775387 *begin_x*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -2.49057 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -59.3268 *lens_ipow(begin_dy, 5)*begin_lambda + 0.132311 *begin_x*begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 0.00107449 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 1.10608e-05 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 2) + -0.102389 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + 6.72797e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy + 1.56836e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -22.0656 *begin_x*begin_dx*lens_ipow(begin_dy, 5)*begin_lambda + -7089.15 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 7)*lens_ipow(begin_lambda, 2) + 407.123 *begin_y*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 4)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 52.6321  + 6.31981 *begin_lambda + -119.646 *lens_ipow(begin_dx, 2) + -41.3013 *lens_ipow(begin_dy, 2) + -1.37979 *begin_x*begin_dx + 0.00105637 *lens_ipow(begin_y, 2) + -4.33794 *lens_ipow(begin_lambda, 2) + -2.13337 *begin_y*begin_dy*begin_lambda + 3.95429 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -4.22614 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 9.22576e-05 *lens_ipow(begin_y, 3)*begin_dy + -0.655789 *begin_y*lens_ipow(begin_dy, 3) + -0.0365469 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.4027 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + -269.961 *lens_ipow(begin_dx, 4)*begin_lambda + -8.68075 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + -0.0368727 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + 0.00203566 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_lambda, 2) + -828.648 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 1.74247e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0(0, 1) =  + -0.000310767 *begin_x*begin_y + -82.6025 *begin_dx*begin_dy + -0.579393 *begin_x*begin_dy + -2.13337 *begin_y*begin_dx*begin_lambda + 3.95429 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -1.40871 *begin_y*lens_ipow(begin_dx, 3) + 9.22576e-05 *lens_ipow(begin_y, 3)*begin_dx + 0.809883 *begin_x*lens_ipow(begin_dy, 3) + -1.96737 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -2.4027 *begin_y*begin_dx*lens_ipow(begin_lambda, 3) + -0.147491 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 3) + -331.459 *lens_ipow(begin_dx, 5)*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + -0.555621 *begin_y*begin_dx + -0.431014 *begin_x*begin_dy + -81.8007 *begin_dx*begin_dy + 0.0673625 *begin_x*begin_dy*begin_lambda + 0.844332 *begin_y*lens_ipow(begin_dx, 3) + -2.32616 *begin_x*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 0.396932 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.56836e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -22.0656 *begin_x*lens_ipow(begin_dy, 5)*begin_lambda + -14178.3 *begin_dx*lens_ipow(begin_dy, 7)*lens_ipow(begin_lambda, 2) + 2442.74 *begin_y*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 4)+0.0f;
    dx1_domega0(1, 1) =  + 52.7206  + 5.9613 *begin_lambda + -1.34732 *begin_y*begin_dy + -0.431014 *begin_x*begin_dx + -40.9004 *lens_ipow(begin_dx, 2) + -3.96818 *lens_ipow(begin_lambda, 2) + 0.0007109 *lens_ipow(begin_x, 2) + -119.12 *lens_ipow(begin_dy, 2) + 0.0673625 *begin_x*begin_dx*begin_lambda + -0.775387 *begin_x*lens_ipow(begin_dx, 3)*begin_lambda + -9.9623 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -296.634 *lens_ipow(begin_dy, 4)*begin_lambda + 0.264621 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.00214897 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + 1.10608e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 2) + -0.511946 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + 6.72797e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 1.56836e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -110.328 *begin_x*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -49624 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6)*lens_ipow(begin_lambda, 2) + 1628.49 *begin_y*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3)+0.0f;
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
    out(0) =  + 74.6622 *begin_dx + 0.602196 *begin_x + 0.581827 *begin_y*begin_dx*begin_dy + 0.0392768 *begin_x*begin_y*begin_dy + 0.0386544 *lens_ipow(begin_x, 2)*begin_dx + -33.0568 *lens_ipow(begin_dx, 3) + -31.5091 *begin_dx*lens_ipow(begin_dy, 2) + 0.00032498 *begin_x*lens_ipow(begin_y, 2) + 0.000258472 *lens_ipow(begin_x, 3) + 1.07194 *begin_x*lens_ipow(begin_dy, 2) + 1.08185 *begin_x*lens_ipow(begin_dx, 2) + 0.0131857 *lens_ipow(begin_y, 2)*begin_dx + 8.89532e-05 *lens_ipow(begin_x, 4)*begin_dx + 3.931 *begin_x*lens_ipow(begin_dx, 4) + 0.348059 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + -3.35151 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -2.73647 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.53103e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + 1.03237e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dy + -0.780564 *begin_x*lens_ipow(begin_dy, 4) + -0.0415416 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.00226783 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.00890017 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + 0.00204047 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 121.05 *begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + 2.39552e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + 2.55272e-09 *lens_ipow(begin_x, 7)*begin_lambda + -7.15018e-12 *lens_ipow(begin_x, 9)*lens_ipow(begin_lambda, 2);
    out(1) =  + 0.602233 *begin_y + 74.6705 *begin_dy + 1.07 *begin_y*lens_ipow(begin_dx, 2) + 0.0383261 *lens_ipow(begin_y, 2)*begin_dy + 1.07302 *begin_y*lens_ipow(begin_dy, 2) + 0.580752 *begin_x*begin_dx*begin_dy + 0.0392364 *begin_x*begin_y*begin_dx + -31.6063 *lens_ipow(begin_dx, 2)*begin_dy + 0.00032524 *lens_ipow(begin_x, 2)*begin_y + 0.000257177 *lens_ipow(begin_y, 3) + 0.0131741 *lens_ipow(begin_x, 2)*begin_dy + -33.1785 *lens_ipow(begin_dy, 3) + 0.00226089 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.774473 *begin_y*lens_ipow(begin_dx, 4) + 9.10862e-05 *lens_ipow(begin_y, 4)*begin_dy + 1.04373e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + -3.30055 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + 0.353146 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 3.98949 *begin_y*lens_ipow(begin_dy, 4) + -2.72638 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0410784 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 1.5431e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 0.00904802 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.00201908 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 2.37178e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_lambda + 121.796 *lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + 2.62126e-09 *lens_ipow(begin_y, 7)*begin_lambda + -7.25756e-12 *lens_ipow(begin_y, 9)*lens_ipow(begin_lambda, 2);
    out(2) =  + -1.55891 *begin_dx + -0.0260199 *begin_x + -0.0452008 *begin_y*begin_dx*begin_dy + -0.000965955 *begin_x*begin_y*begin_dy + -0.000414268 *lens_ipow(begin_x, 2)*begin_dx + 0.465692 *lens_ipow(begin_dx, 3) + -1.57573 *begin_dx*lens_ipow(begin_dy, 2) + -3.89556e-06 *begin_x*lens_ipow(begin_y, 2) + -1.14636e-06 *lens_ipow(begin_x, 3) + -0.0369466 *begin_x*lens_ipow(begin_dy, 2) + -0.0107324 *begin_x*lens_ipow(begin_dx, 2) + -0.000238242 *lens_ipow(begin_y, 2)*begin_dx + -1.82478e-07 *lens_ipow(begin_x, 4)*begin_dx + 0.135898 *begin_x*lens_ipow(begin_dx, 4) + 0.156515 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 4.9098 *lens_ipow(begin_dx, 5) + 0.220503 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.04809e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 6.49893 *begin_dx*lens_ipow(begin_dy, 4) + -2.2957e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 0.0452327 *begin_x*lens_ipow(begin_dy, 4) + 0.124001 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.00071012 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -3.77424e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -2.54143e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2) + -1.75655e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 13.2098 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 3.62414e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4);
    out(3) =  + -0.0260874 *begin_y + -1.565 *begin_dy + -0.000312354 *lens_ipow(begin_y, 2)*begin_dy + 0.0645932 *begin_x*begin_dx*begin_dy + 2.74028 *lens_ipow(begin_dx, 2)*begin_dy + 1.89292e-06 *lens_ipow(begin_x, 2)*begin_y + -8.38648e-07 *lens_ipow(begin_y, 3) + 0.000402049 *lens_ipow(begin_x, 2)*begin_dy + 0.710306 *lens_ipow(begin_dy, 3) + -0.00386419 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -1.11932e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 4.14787 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.0139968 *begin_y*lens_ipow(begin_dx, 4) + -1.91909e-07 *lens_ipow(begin_y, 4)*begin_dy + 2.33074 *lens_ipow(begin_dy, 5) + 0.0321421 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -3.62873e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2) + 0.0860433 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000105678 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + -0.00514285 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -1.75442e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + 1.84664e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dy, 3) + -5.23176e-07 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 2) + -2.8975e-10 *begin_x*lens_ipow(begin_y, 5)*begin_dx + 0.000306319 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 3) + 0.0123744 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.112506 *begin_y*lens_ipow(begin_dy, 6) + 13.2299 *lens_ipow(begin_dy, 7)*lens_ipow(begin_lambda, 2);
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
    domega2_dx0(0, 0) =  + -0.0260199  + -0.000965955 *begin_y*begin_dy + -0.000828536 *begin_x*begin_dx + -3.89556e-06 *lens_ipow(begin_y, 2) + -3.43909e-06 *lens_ipow(begin_x, 2) + -0.0369466 *lens_ipow(begin_dy, 2) + -0.0107324 *lens_ipow(begin_dx, 2) + -7.2991e-07 *lens_ipow(begin_x, 3)*begin_dx + 0.135898 *lens_ipow(begin_dx, 4) + 0.220503 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -3.14428e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -6.88708e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.0452327 *lens_ipow(begin_dy, 4) + -7.54848e-05 *begin_x*begin_y*begin_dx*begin_dy + -7.6243e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -1.75655e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 1.08724e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)+0.0f;
    domega2_dx0(0, 1) =  + -0.0452008 *begin_dx*begin_dy + -0.000965955 *begin_x*begin_dy + -7.79112e-06 *begin_x*begin_y + -0.000476484 *begin_y*begin_dx + 0.156515 *lens_ipow(begin_dx, 3)*begin_dy + -2.2957e-07 *lens_ipow(begin_x, 3)*begin_dy + 0.124001 *begin_dx*lens_ipow(begin_dy, 3) + 0.00142024 *begin_y*lens_ipow(begin_dx, 3) + -3.77424e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -3.5131e-05 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 1.44966e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0645932 *begin_dx*begin_dy + 3.78584e-06 *begin_x*begin_y + 0.000804098 *begin_x*begin_dy + -1.11932e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0321421 *begin_dx*lens_ipow(begin_dy, 3) + -7.25747e-06 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 7.38654e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 3) + -2.8975e-10 *lens_ipow(begin_y, 5)*begin_dx + 0.000918956 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 3) + 0.0247487 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.0260874  + -0.000624707 *begin_y*begin_dy + 1.89292e-06 *lens_ipow(begin_x, 2) + -2.51594e-06 *lens_ipow(begin_y, 2) + -0.00386419 *lens_ipow(begin_dy, 2)*begin_lambda + -2.23864e-05 *begin_x*begin_y*begin_dx*begin_dy + 0.0139968 *lens_ipow(begin_dx, 4) + -7.67638e-07 *lens_ipow(begin_y, 3)*begin_dy + -3.62873e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 0.0860433 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000317033 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0102857 *begin_y*lens_ipow(begin_dy, 3)*begin_lambda + -8.77211e-08 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -2.0927e-06 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -1.44875e-09 *begin_x*lens_ipow(begin_y, 4)*begin_dx + 0.112506 *lens_ipow(begin_dy, 6)+0.0f;
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
  out[4] =  + 0.561778  + 0.229736 *begin_lambda + 0.00252279 *begin_y*begin_dy + 0.00247301 *begin_x*begin_dx + 1.91875e-05 *lens_ipow(begin_y, 2) + 0.0974594 *lens_ipow(begin_dy, 2) + 1.82703e-05 *lens_ipow(begin_x, 2) + 0.0968208 *lens_ipow(begin_dx, 2) + -0.157055 *lens_ipow(begin_lambda, 2) + -4.65276 *lens_ipow(begin_dx, 4) + -0.207107 *begin_y*lens_ipow(begin_dy, 3) + -0.0013686 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.206752 *begin_x*lens_ipow(begin_dx, 3) + -9.22134 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -4.04537e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -4.64888 *lens_ipow(begin_dy, 4) + -4.04018e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -3.31411e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.69845e-07 *lens_ipow(begin_y, 4) + -0.00403855 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.206858 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -4.03562e-05 *lens_ipow(begin_x, 3)*begin_dx + -0.00405939 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.206535 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -1.65944e-07 *lens_ipow(begin_x, 4) + -0.00537792 *begin_x*begin_y*begin_dx*begin_dy + -0.00136793 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -4.07195e-05 *lens_ipow(begin_y, 3)*begin_dy;
else
  out[4] = 0.0f;
} break;
