case nikon__retrofocus_wideangle__1971__35mm:
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
       + 46.0468 *begin_dx + 0.771654 *begin_x + -0.0440603 *begin_x*begin_lambda + 11.5131 *lens_ipow(begin_dx, 3) + 0.0340632 *begin_x*lens_ipow(begin_lambda, 2) + 2.04106 *begin_x*lens_ipow(begin_dx, 2) + 0.0626259 *lens_ipow(begin_x, 2)*begin_dx + 0.000520133 *lens_ipow(begin_x, 3) + 51.4406 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 5.00217 *begin_y*begin_dx*begin_dy*begin_lambda + 0.0781263 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 3.06284 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.168312 *begin_x*begin_y*begin_dy*begin_lambda + 0.00201315 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -51.6044 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -4.70816 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -0.0826144 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + -2.92628 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.158485 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00189516 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 0.0114261 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 3) + 0.800313 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.000525604 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy*begin_lambda + 8.35064e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_lambda + -7.61051e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 5)*begin_dy + -1.06645e-06 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 5) + 4.91882e-10 *lens_ipow(begin_x, 8)*begin_dx*lens_ipow(begin_dy, 2) + 7.48142e-12 *lens_ipow(begin_x, 9)*lens_ipow(begin_dy, 2),
       + 46.3471 *begin_dy + 0.771389 *begin_y + -0.616797 *begin_dy*begin_lambda + -0.0292671 *begin_y*begin_lambda + 12.0594 *lens_ipow(begin_dx, 2)*begin_dy + 0.777021 *begin_y*lens_ipow(begin_dx, 2) + 1.32074 *begin_x*begin_dx*begin_dy + 0.0434403 *begin_x*begin_y*begin_dx + 0.0198605 *lens_ipow(begin_x, 2)*begin_dy + 0.000519638 *lens_ipow(begin_x, 2)*begin_y + 5.21395 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.18673 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.00197977 *lens_ipow(begin_y, 3)*begin_lambda + 62.6692 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.00183302 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -5.21776e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.000242538 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.0127585 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 4.36488e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -0.000588457 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + -6.11549e-06 *lens_ipow(begin_x, 4)*begin_dy + -0.287241 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 0.0665203 *begin_y*lens_ipow(begin_lambda, 6) + -7.74085 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 0.106401 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 4) + 3.34465e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_lambda + -207.911 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 6) + 5.83562 *begin_dy*lens_ipow(begin_lambda, 9)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 46.0468  + 34.5393 *lens_ipow(begin_dx, 2) + 4.08212 *begin_x*begin_dx + 0.0626259 *lens_ipow(begin_x, 2) + 51.4406 *lens_ipow(begin_dy, 2)*begin_lambda + 5.00217 *begin_y*begin_dy*begin_lambda + 0.0781263 *lens_ipow(begin_y, 2)*begin_lambda + -51.6044 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -4.70816 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.0826144 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 0.0114261 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + 1.60063 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -0.000525604 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + -0.000380525 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 4)*begin_dy + -5.33225e-06 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 4) + 4.91882e-10 *lens_ipow(begin_x, 8)*lens_ipow(begin_dy, 2)+0.0f;
    dx1_domega0(0, 1) =  + 102.881 *begin_dx*begin_dy*begin_lambda + 5.00217 *begin_y*begin_dx*begin_lambda + 6.12568 *begin_x*begin_dy*begin_lambda + 0.168312 *begin_x*begin_y*begin_lambda + -103.209 *begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -4.70816 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + -5.85256 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.158485 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 1.60063 *begin_x*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.000525604 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_lambda + -7.61051e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 5) + 9.83764e-10 *lens_ipow(begin_x, 8)*begin_dx*begin_dy + 1.49628e-11 *lens_ipow(begin_x, 9)*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + 24.1189 *begin_dx*begin_dy + 1.55404 *begin_y*begin_dx + 1.32074 *begin_x*begin_dy + 0.0434403 *begin_x*begin_y + -0.000242538 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -0.0255169 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.000588457 *lens_ipow(begin_x, 3)*begin_dy + 6.68931e-07 *lens_ipow(begin_y, 5)*begin_dx*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 46.3471  + -0.616797 *begin_lambda + 12.0594 *lens_ipow(begin_dx, 2) + 1.32074 *begin_x*begin_dx + 0.0198605 *lens_ipow(begin_x, 2) + 10.4279 *begin_y*begin_dy*begin_lambda + 0.18673 *lens_ipow(begin_y, 2)*begin_lambda + 188.007 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000104355 *lens_ipow(begin_y, 3)*begin_dy + -0.000242538 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.0127585 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.000588457 *lens_ipow(begin_x, 3)*begin_dx + -6.11549e-06 *lens_ipow(begin_x, 4) + -0.287241 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + -15.4817 *begin_y*begin_dy*lens_ipow(begin_lambda, 4) + 0.106401 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 4) + -623.732 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 6) + 5.83562 *lens_ipow(begin_lambda, 9)+0.0f;
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
    out(0) =  + 29.949 *begin_dx + -0.160269 *begin_x + 20.8124 *begin_dx*begin_lambda + -29.1542 *begin_dx*lens_ipow(begin_lambda, 2) + -12.0267 *begin_dx*lens_ipow(begin_dy, 2) + -5.51362 *lens_ipow(begin_dx, 3) + 0.295929 *begin_y*begin_dx*begin_dy + 0.0145537 *lens_ipow(begin_y, 2)*begin_dx + 0.607588 *begin_x*lens_ipow(begin_dy, 2) + 1.29345 *begin_x*lens_ipow(begin_dx, 2) + 0.0247493 *begin_x*begin_y*begin_dy + 0.000500303 *begin_x*lens_ipow(begin_y, 2) + 0.0469052 *lens_ipow(begin_x, 2)*begin_dx + 0.000550139 *lens_ipow(begin_x, 3) + 14.2965 *begin_dx*lens_ipow(begin_lambda, 3) + -19.7643 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 87.0989 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.167061 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + -1.32266 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 4.54352 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.289046 *begin_x*lens_ipow(begin_dx, 4) + 0.00237194 *begin_x*begin_y*lens_ipow(begin_dy, 3) + -0.0279683 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 0.111349 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -3.18628e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -0.000194032 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 0.00112255 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 8.46576e-06 *lens_ipow(begin_x, 3)*begin_y*begin_dy;
    out(1) =  + 30.2723 *begin_dy + -0.155488 *begin_y + 19.9671 *begin_dy*begin_lambda + -0.00980928 *begin_y*begin_lambda + -28.631 *begin_dy*lens_ipow(begin_lambda, 2) + -10.7945 *lens_ipow(begin_dy, 3) + -10.4171 *lens_ipow(begin_dx, 2)*begin_dy + 0.929571 *begin_y*lens_ipow(begin_dy, 2) + 0.650284 *begin_y*lens_ipow(begin_dx, 2) + 0.0391419 *lens_ipow(begin_y, 2)*begin_dy + 0.000499012 *lens_ipow(begin_y, 3) + 0.279996 *begin_x*begin_dx*begin_dy + 0.0248059 *begin_x*begin_y*begin_dx + 0.0143243 *lens_ipow(begin_x, 2)*begin_dy + 0.000499977 *lens_ipow(begin_x, 2)*begin_y + 14.0392 *begin_dy*lens_ipow(begin_lambda, 3) + -8.75593e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 0.0047392 *begin_x*begin_y*lens_ipow(begin_dx, 3) + -0.000719513 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 11.6784 *lens_ipow(begin_dy, 5)*begin_lambda + -0.0440602 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 9.53592e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 5.00097e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_lambda + 0.0919424 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5)*begin_lambda + 219.429 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 4) + 0.000646046 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 8.11923e-11 *begin_x*lens_ipow(begin_y, 7)*begin_dx*begin_lambda + 0.0453035 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4);
    out(2) =  + -1.03437 *begin_dx + -0.0260265 *begin_x + 0.00667057 *begin_x*begin_lambda + -0.0910994 *begin_dx*lens_ipow(begin_dy, 2) + 0.504604 *lens_ipow(begin_dx, 3) + 0.00375711 *begin_y*begin_dx*begin_dy + 4.96695e-05 *lens_ipow(begin_y, 2)*begin_dx + -0.00483806 *begin_x*lens_ipow(begin_lambda, 2) + 0.0126975 *begin_x*lens_ipow(begin_dx, 2) + -0.0474111 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + -0.00218544 *begin_x*begin_y*begin_dy*begin_lambda + -1.50741e-05 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -0.00165095 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -1.48219e-05 *lens_ipow(begin_x, 3)*begin_lambda + 1.19084e-05 *lens_ipow(begin_y, 3)*begin_dx*begin_dy + 1.80989e-07 *lens_ipow(begin_y, 4)*begin_dx + 0.0413368 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.101452 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.00195744 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + 0.111331 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 1.58606e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + 0.00156207 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 3) + 1.4463e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + 6.23182e-06 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -1.07413e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -9.95377e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.000491085 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -6.86378e-11 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 2)*begin_lambda;
    out(3) =  + -1.03554 *begin_dy + -0.0255481 *begin_y + 0.00485144 *begin_y*begin_lambda + 1.04269 *lens_ipow(begin_dx, 2)*begin_dy + -0.00323192 *begin_y*lens_ipow(begin_lambda, 2) + -0.0150997 *begin_y*lens_ipow(begin_dx, 2) + -0.000370955 *lens_ipow(begin_y, 2)*begin_dy + -4.98056e-06 *lens_ipow(begin_y, 3) + 0.0296174 *begin_x*begin_dx*begin_dy + -0.000591649 *begin_x*begin_y*begin_dx + -4.44597e-06 *lens_ipow(begin_x, 2)*begin_y + 1.66657 *lens_ipow(begin_dy, 3)*begin_lambda + 0.154041 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.000870886 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -1.44609 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 0.000782972 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.00129572 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 1.41548e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda + 3.71936e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -9.75015e-09 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 2) + -8.07294e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -4.66403e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -9.5228e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -8.17544e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -0.0350039 *begin_y*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3) + -1.4607e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_lambda + 3.60454e-14 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + 2.79662e-08 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 6);
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
    domega2_dx0(0, 0) =  + -0.0260265  + 0.00667057 *begin_lambda + -0.00483806 *lens_ipow(begin_lambda, 2) + 0.0126975 *lens_ipow(begin_dx, 2) + -0.0474111 *lens_ipow(begin_dy, 2)*begin_lambda + -0.00218544 *begin_y*begin_dy*begin_lambda + -1.50741e-05 *lens_ipow(begin_y, 2)*begin_lambda + -0.00330191 *begin_x*begin_dx*begin_lambda + -4.44657e-05 *lens_ipow(begin_x, 2)*begin_lambda + 0.0413368 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.101452 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.00195744 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + 0.111331 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 1.58606e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + 0.00312414 *begin_x*begin_dx*lens_ipow(begin_lambda, 3) + 4.33889e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + 6.23182e-06 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -5.37064e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -2.98613e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.000982169 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2) + -4.80465e-10 *lens_ipow(begin_x, 6)*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    domega2_dx0(0, 1) =  + 0.00375711 *begin_dx*begin_dy + 9.93391e-05 *begin_y*begin_dx + -0.00218544 *begin_x*begin_dy*begin_lambda + -3.01482e-05 *begin_x*begin_y*begin_lambda + 3.57253e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + 7.23957e-07 *lens_ipow(begin_y, 3)*begin_dx + 0.00195744 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 3.17213e-05 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 1.24636e-05 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -2.14826e-11 *lens_ipow(begin_x, 5)*begin_y + -9.95377e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -0.000491085 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_dy*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(1, 0) =  + 0.0296174 *begin_dx*begin_dy + -0.000591649 *begin_y*begin_dx + -8.89194e-06 *begin_x*begin_y + 3.71936e-05 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + -8.07294e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -9.32806e-07 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -2.85684e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -3.27018e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + -2.9214e-11 *begin_x*lens_ipow(begin_y, 5)*begin_lambda + 1.44182e-13 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)+0.0f;
    domega2_dx0(1, 1) =  + -0.0255481  + 0.00485144 *begin_lambda + -0.00323192 *lens_ipow(begin_lambda, 2) + -0.0150997 *lens_ipow(begin_dx, 2) + -0.000741909 *begin_y*begin_dy + -1.49417e-05 *lens_ipow(begin_y, 2) + -0.000591649 *begin_x*begin_dx + -4.44597e-06 *lens_ipow(begin_x, 2) + -0.00174177 *begin_y*begin_dy*begin_lambda + 0.00156594 *begin_y*begin_dy*lens_ipow(begin_lambda, 2) + 0.00259144 *begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 4.24643e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 7.43872e-05 *begin_x*begin_y*begin_dx*begin_dy*begin_lambda + -4.87508e-08 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 2) + -2.42188e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -1.39921e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -2.85684e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + -2.45263e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -0.0350039 *lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3) + -7.3035e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_lambda + 1.80227e-13 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4) + 1.39831e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 6)+0.0f;
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
  out[4] =  + 2.05381 *begin_lambda + -4.44599 *lens_ipow(begin_lambda, 2) + -0.0498478 *lens_ipow(begin_dy, 2) + -0.00168015 *begin_y*begin_dy + -1.67528e-05 *lens_ipow(begin_y, 2) + 4.5345 *lens_ipow(begin_lambda, 3) + -1.79184 *lens_ipow(begin_lambda, 4) + -2.88355 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.96247 *lens_ipow(begin_dx, 4) + -0.0330158 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0413706 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.153779 *begin_x*lens_ipow(begin_dx, 3) + -0.000327349 *begin_x*begin_y*begin_dx*begin_dy + -0.000163712 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.0035209 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -3.2022e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -8.44591e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -4.30641e-05 *lens_ipow(begin_x, 3)*begin_dx + -2.41332e-07 *lens_ipow(begin_x, 4) + -40.1927 *lens_ipow(begin_dy, 6) + -0.469616 *lens_ipow(begin_dx, 6) + -2.20743 *begin_y*lens_ipow(begin_dy, 5) + -0.049697 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.000425234 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + -1.98786e-10 *lens_ipow(begin_y, 6) + 32.0455 *lens_ipow(begin_dy, 8) + -26.0311 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 4)*begin_lambda + 2.1132 *begin_y*lens_ipow(begin_dy, 9);
else
  out[4] = 0.0f;
} break;
