case asahi__takumar__1969__50mm:
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
       + 30.5049 *begin_dx + 0.329174 *begin_x + 6.01689 *begin_dx*begin_lambda + 0.202922 *begin_x*begin_lambda + -4.16436 *begin_dx*lens_ipow(begin_lambda, 2) + -17.4556 *begin_dx*lens_ipow(begin_dy, 2) + -18.1709 *lens_ipow(begin_dx, 3) + -0.192721 *begin_y*begin_dx*begin_dy + -0.142731 *begin_x*lens_ipow(begin_lambda, 2) + -0.161926 *begin_x*lens_ipow(begin_dy, 2) + -0.279053 *begin_x*lens_ipow(begin_dx, 2) + 0.00165428 *begin_x*begin_y*begin_dy + -0.000111406 *begin_x*lens_ipow(begin_y, 2) + 0.0036776 *lens_ipow(begin_x, 2)*begin_dx + -0.000114397 *lens_ipow(begin_x, 3) + 0.104387 *begin_y*begin_dx*begin_dy*begin_lambda + 0.00360287 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.230411 *begin_x*lens_ipow(begin_dy, 4) + -2.10355e-07 *begin_x*lens_ipow(begin_y, 4) + -0.0124531 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -7.16216e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -1.90249e-07 *lens_ipow(begin_x, 5) + 6.61838 *lens_ipow(begin_dx, 5)*begin_lambda + 5.91987e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -0.0268584 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -8.50346 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3)*begin_lambda + 0.243122 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy*begin_lambda + -4.29393e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx*begin_dy,
       + 30.5276 *begin_dy + 0.32963 *begin_y + 5.92349 *begin_dy*begin_lambda + 0.200971 *begin_y*begin_lambda + -4.08016 *begin_dy*lens_ipow(begin_lambda, 2) + -18.0714 *lens_ipow(begin_dy, 3) + -17.5163 *lens_ipow(begin_dx, 2)*begin_dy + -0.140901 *begin_y*lens_ipow(begin_lambda, 2) + -0.277072 *begin_y*lens_ipow(begin_dy, 2) + -0.163485 *begin_y*lens_ipow(begin_dx, 2) + 0.00370915 *lens_ipow(begin_y, 2)*begin_dy + -0.000113522 *lens_ipow(begin_y, 3) + -0.19434 *begin_x*begin_dx*begin_dy + 0.0016427 *begin_x*begin_y*begin_dx + -0.000111942 *lens_ipow(begin_x, 2)*begin_y + 0.0980336 *begin_x*begin_dx*begin_dy*begin_lambda + 0.00352017 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.240269 *begin_y*lens_ipow(begin_dx, 4) + -0.0124114 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.93144e-07 *lens_ipow(begin_y, 5) + -7.08109e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -2.07091e-07 *lens_ipow(begin_x, 4)*begin_y + 5.88861 *lens_ipow(begin_dy, 5)*begin_lambda + 5.77064e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -0.0249123 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 0.265028 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4)*begin_lambda + -76.3066 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)*begin_lambda + -4.14281e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx*begin_dy
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 30.5049  + 6.01689 *begin_lambda + -4.16436 *lens_ipow(begin_lambda, 2) + -17.4556 *lens_ipow(begin_dy, 2) + -54.5126 *lens_ipow(begin_dx, 2) + -0.192721 *begin_y*begin_dy + -0.558107 *begin_x*begin_dx + 0.0036776 *lens_ipow(begin_x, 2) + 0.104387 *begin_y*begin_dy*begin_lambda + 0.00360287 *lens_ipow(begin_y, 2)*begin_lambda + -0.0124531 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 33.0919 *lens_ipow(begin_dx, 4)*begin_lambda + -0.0805753 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -25.5104 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.972488 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy*begin_lambda + -4.29393e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dy+0.0f;
    dx1_domega0(0, 1) =  + -34.9112 *begin_dx*begin_dy + -0.192721 *begin_y*begin_dx + -0.323853 *begin_x*begin_dy + 0.00165428 *begin_x*begin_y + 0.104387 *begin_y*begin_dx*begin_lambda + 0.921646 *begin_x*lens_ipow(begin_dy, 3) + -0.0249061 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -25.5104 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 0.243122 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_lambda + -4.29393e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx+0.0f;
    dx1_domega0(1, 0) =  + -35.0325 *begin_dx*begin_dy + -0.326969 *begin_y*begin_dx + -0.19434 *begin_x*begin_dy + 0.0016427 *begin_x*begin_y + 0.0980336 *begin_x*begin_dy*begin_lambda + 0.961077 *begin_y*lens_ipow(begin_dx, 3) + -0.0248228 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.265028 *begin_x*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -381.533 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3)*begin_lambda + -4.14281e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dy+0.0f;
    dx1_domega0(1, 1) =  + 30.5276  + 5.92349 *begin_lambda + -4.08016 *lens_ipow(begin_lambda, 2) + -54.2143 *lens_ipow(begin_dy, 2) + -17.5163 *lens_ipow(begin_dx, 2) + -0.554144 *begin_y*begin_dy + 0.00370915 *lens_ipow(begin_y, 2) + -0.19434 *begin_x*begin_dx + 0.0980336 *begin_x*begin_dx*begin_lambda + 0.00352017 *lens_ipow(begin_x, 2)*begin_lambda + -0.0124114 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 29.4431 *lens_ipow(begin_dy, 4)*begin_lambda + -0.0747368 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 1.06011 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + -228.92 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2)*begin_lambda + -4.14281e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx+0.0f;
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
    out(0) =  + 49.6924 *begin_dx + -0.119934 *begin_x + 0.540799 *begin_dx*begin_lambda + 0.359186 *begin_x*begin_lambda + -21.1981 *begin_dx*lens_ipow(begin_dy, 2) + -20.5364 *lens_ipow(begin_dx, 3) + 0.00695372 *lens_ipow(begin_y, 2)*begin_dx + -0.263212 *begin_x*lens_ipow(begin_lambda, 2) + 0.568779 *begin_x*lens_ipow(begin_dx, 2) + 0.0155268 *begin_x*begin_y*begin_dy + -0.000436672 *begin_x*lens_ipow(begin_y, 2) + 0.0241674 *lens_ipow(begin_x, 2)*begin_dx + -0.000323585 *lens_ipow(begin_x, 3) + 1.74931 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.000185409 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + 9.43306e-05 *lens_ipow(begin_x, 3)*begin_lambda + -1.5284e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dy + 0.000464449 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -4.33799e-07 *lens_ipow(begin_x, 5) + -6.12817 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -1.52456 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -2.12438e-05 *lens_ipow(begin_x, 4)*begin_dx*begin_lambda + 5.56321 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -9.408e-10 *begin_x*lens_ipow(begin_y, 6) + -2.03594e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -1.685e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 0.871017 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 7)*begin_lambda + -0.000171519 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3);
    out(1) =  + 49.9575 *begin_dy + -0.125186 *begin_y + 0.373043 *begin_y*begin_lambda + -20.4236 *lens_ipow(begin_dy, 3) + -21.2448 *lens_ipow(begin_dx, 2)*begin_dy + -0.275347 *begin_y*lens_ipow(begin_lambda, 2) + 0.557704 *begin_y*lens_ipow(begin_dy, 2) + 0.0247013 *lens_ipow(begin_y, 2)*begin_dy + -0.000332094 *lens_ipow(begin_y, 3) + 0.0155264 *begin_x*begin_y*begin_dx + -0.000256388 *lens_ipow(begin_x, 2)*begin_y + 1.72024 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.000166548 *lens_ipow(begin_y, 3)*begin_lambda + 0.0127017 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 0.000656243 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -1.84833e-05 *lens_ipow(begin_y, 4)*begin_dy + -5.57108e-07 *lens_ipow(begin_y, 5) + -8.74614e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.92924e-05 *lens_ipow(begin_x, 4)*begin_dy + -5.11814e-07 *lens_ipow(begin_x, 4)*begin_y + -6.26721 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 0.0278695 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.0380057 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -2.8556e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*begin_lambda + -4.78586e-05 *lens_ipow(begin_x, 4)*begin_dy*begin_lambda + 5.75419 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -5.58838e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 1.39871e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6)*begin_dy;
    out(2) =  + -0.904789 *begin_dx + -0.0179872 *begin_x + -0.00614881 *begin_x*begin_lambda + 0.0648502 *begin_dx*lens_ipow(begin_dy, 2) + 0.384909 *lens_ipow(begin_dx, 3) + 0.00484289 *begin_x*lens_ipow(begin_lambda, 2) + -0.00849818 *begin_x*lens_ipow(begin_dy, 2) + -0.000255742 *begin_x*begin_y*begin_dy + 1.02856e-05 *begin_x*lens_ipow(begin_y, 2) + -0.000225672 *lens_ipow(begin_x, 2)*begin_dx + 1.04483e-05 *lens_ipow(begin_x, 3) + -0.00335404 *begin_y*begin_dx*begin_dy*begin_lambda + -3.71101e-06 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -3.75729e-06 *lens_ipow(begin_x, 3)*begin_lambda + 1.10697e-05 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + -0.000918822 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 4.67614e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 1.34145e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 9.01824e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + 0.00167051 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_lambda + -0.0191191 *begin_x*lens_ipow(begin_dx, 4)*begin_lambda + 1.16311e-11 *begin_x*lens_ipow(begin_y, 6) + 3.51465e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 4) + 1.46335e-11 *lens_ipow(begin_x, 7) + -1.41991 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4) + -4.23094e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*begin_dx + -0.0147835 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 3) + 4.71972e-16 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 6);
    out(3) =  + -0.904259 *begin_dy + -0.017748 *begin_y + -0.00657363 *begin_y*begin_lambda + 0.394052 *lens_ipow(begin_dy, 3) + 0.722596 *lens_ipow(begin_dx, 2)*begin_dy + 0.00485492 *begin_y*lens_ipow(begin_lambda, 2) + -0.000224397 *lens_ipow(begin_y, 2)*begin_dy + 7.52641e-06 *lens_ipow(begin_y, 3) + 0.0147319 *begin_x*begin_dx*begin_dy + -0.000245623 *begin_x*begin_y*begin_dx + 7.22185e-06 *lens_ipow(begin_x, 2)*begin_y + -0.0295556 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + -1.00815e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 1.12156e-08 *lens_ipow(begin_y, 5) + -0.00087922 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.000842835 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 2.95846e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 1.05772e-05 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + 7.9637e-09 *lens_ipow(begin_x, 4)*begin_y + 0.111896 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.0512501 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -7.249e-09 *lens_ipow(begin_y, 5)*begin_lambda + -2.64357e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + -5.66827 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 3) + -0.103025 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + 0.00392288 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.00403258 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -3.36641e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6)*begin_dy;
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
    domega2_dx0(0, 0) =  + -0.0179872  + -0.00614881 *begin_lambda + 0.00484289 *lens_ipow(begin_lambda, 2) + -0.00849818 *lens_ipow(begin_dy, 2) + -0.000255742 *begin_y*begin_dy + 1.02856e-05 *lens_ipow(begin_y, 2) + -0.000451343 *begin_x*begin_dx + 3.13449e-05 *lens_ipow(begin_x, 2) + -3.71101e-06 *lens_ipow(begin_y, 2)*begin_lambda + -1.12719e-05 *lens_ipow(begin_x, 2)*begin_lambda + -0.000918822 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 4.67614e-06 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 2.6829e-05 *begin_x*begin_y*begin_dx*begin_dy + 2.70547e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.0191191 *lens_ipow(begin_dx, 4)*begin_lambda + 1.16311e-11 *lens_ipow(begin_y, 6) + 0.00010544 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + 1.02434e-10 *lens_ipow(begin_x, 6) + -1.41991 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4) + -2.53856e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx + 2.35986e-15 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6)+0.0f;
    domega2_dx0(0, 1) =  + -0.000255742 *begin_x*begin_dy + 2.05711e-05 *begin_x*begin_y + -0.00335404 *begin_dx*begin_dy*begin_lambda + -7.42201e-06 *begin_x*begin_y*begin_lambda + 3.3209e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.000918822 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 9.35228e-06 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 1.34145e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 1.80365e-08 *lens_ipow(begin_x, 3)*begin_y + 0.00334102 *begin_y*lens_ipow(begin_dx, 3)*begin_lambda + 6.97863e-11 *begin_x*lens_ipow(begin_y, 5) + -8.46187e-12 *lens_ipow(begin_x, 6)*begin_y*begin_dx + -0.0295671 *begin_y*lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 3) + 2.83183e-15 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5)+0.0f;
    domega2_dx0(1, 0) =  + 0.0147319 *begin_dx*begin_dy + -0.000245623 *begin_y*begin_dx + 1.44437e-05 *begin_x*begin_y + -0.00087922 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00168567 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 5.91693e-08 *begin_x*lens_ipow(begin_y, 3) + 3.17315e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 3.18548e-08 *lens_ipow(begin_x, 3)*begin_y + -5.28714e-08 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + 0.00784575 *begin_x*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.00806516 *begin_x*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 3) + -1.34657e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dy+0.0f;
    domega2_dx0(1, 1) =  + -0.017748  + -0.00657363 *begin_lambda + 0.00485492 *lens_ipow(begin_lambda, 2) + -0.000448793 *begin_y*begin_dy + 2.25792e-05 *lens_ipow(begin_y, 2) + -0.000245623 *begin_x*begin_dx + 7.22185e-06 *lens_ipow(begin_x, 2) + -0.0295556 *lens_ipow(begin_dx, 2)*begin_lambda + -3.02445e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 5.60782e-08 *lens_ipow(begin_y, 4) + -0.00087922 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 8.87539e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 7.9637e-09 *lens_ipow(begin_x, 4) + 0.111896 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -0.0512501 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -3.6245e-08 *lens_ipow(begin_y, 4)*begin_lambda + -7.93071e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -0.103025 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -2.01985e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5)*begin_dy+0.0f;
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
  out[4] =  + 2.13006 *begin_lambda + -4.71096 *lens_ipow(begin_lambda, 2) + 0.0287933 *lens_ipow(begin_dy, 2) + 0.0288629 *lens_ipow(begin_dx, 2) + 4.89326 *lens_ipow(begin_lambda, 3) + -0.0274442 *lens_ipow(begin_dy, 2)*begin_lambda + -0.0272431 *lens_ipow(begin_dx, 2)*begin_lambda + -1.96344 *lens_ipow(begin_lambda, 4) + -0.520377 *lens_ipow(begin_dy, 4) + -1.03826 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.521246 *lens_ipow(begin_dx, 4) + -0.024251 *begin_y*lens_ipow(begin_dy, 3) + -0.0239731 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.000709141 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.000247905 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.0240776 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.0241728 *begin_x*lens_ipow(begin_dx, 3) + -0.000907744 *begin_x*begin_y*begin_dx*begin_dy + -0.000249661 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000707169 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -7.41721e-06 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -6.97163e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -7.0294e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + -8.43327e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + -7.34918e-06 *lens_ipow(begin_x, 3)*begin_dx*begin_lambda + -2.3375e-10 *lens_ipow(begin_y, 6)*begin_lambda + -2.28085e-10 *lens_ipow(begin_x, 6)*begin_lambda + -2.61146e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4);
else
  out[4] = 0.0f;
} break;
