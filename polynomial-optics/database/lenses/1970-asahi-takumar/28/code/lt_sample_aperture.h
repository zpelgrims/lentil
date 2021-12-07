case asahi__takumar__1970__28mm:
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
       + 29.1443 *begin_dx + 0.586408 *begin_x + 0.52188 *begin_dx*begin_lambda + 0.0133273 *begin_x*begin_lambda + 5.74335 *begin_dx*lens_ipow(begin_dy, 2) + 6.07114 *lens_ipow(begin_dx, 3) + 1.11936 *begin_y*begin_dx*begin_dy + 0.0233401 *lens_ipow(begin_y, 2)*begin_dx + 0.689564 *begin_x*lens_ipow(begin_dy, 2) + 1.86208 *begin_x*lens_ipow(begin_dx, 2) + 0.0527357 *begin_x*begin_y*begin_dy + 0.000744863 *begin_x*lens_ipow(begin_y, 2) + 0.0780203 *lens_ipow(begin_x, 2)*begin_dx + 0.000739898 *lens_ipow(begin_x, 3) + 3.11327e-05 *lens_ipow(begin_x, 3)*begin_lambda + 7.73494e-06 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -6.16008e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 1.09917e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 3.00171e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -3.81487e-10 *lens_ipow(begin_x, 7) + -0.0795532 *begin_x*begin_y*lens_ipow(begin_dy, 5)*begin_lambda + 1.30616e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda + 2.06478e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dy + -1.12498e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3),
       + 29.2795 *begin_dy + 0.584358 *begin_y + 0.0171163 *begin_y*begin_lambda + 0.491387 *begin_dy*lens_ipow(begin_lambda, 2) + 5.94581 *lens_ipow(begin_dy, 3) + 5.98883 *lens_ipow(begin_dx, 2)*begin_dy + 1.84181 *begin_y*lens_ipow(begin_dy, 2) + 0.705569 *begin_y*lens_ipow(begin_dx, 2) + 0.0773049 *lens_ipow(begin_y, 2)*begin_dy + 0.000751392 *lens_ipow(begin_y, 3) + 1.14136 *begin_x*begin_dx*begin_dy + 0.0537161 *begin_x*begin_y*begin_dx + 0.0237446 *lens_ipow(begin_x, 2)*begin_dy + 0.000751104 *lens_ipow(begin_x, 2)*begin_y + -3.99561e-10 *lens_ipow(begin_y, 7) + 4.06729e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 8.83436e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -4.51867e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 9.88222e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + 2.32302e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2) + -3.55721e-10 *lens_ipow(begin_x, 6)*begin_y + 4.27225e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_lambda + -8.46395e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy*begin_lambda + 7.04847e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2)*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 29.1443  + 0.52188 *begin_lambda + 5.74335 *lens_ipow(begin_dy, 2) + 18.2134 *lens_ipow(begin_dx, 2) + 1.11936 *begin_y*begin_dy + 0.0233401 *lens_ipow(begin_y, 2) + 3.72417 *begin_x*begin_dx + 0.0780203 *lens_ipow(begin_x, 2) + -6.16008e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy + 1.09917e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + 2.61233e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -2.24995e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0(0, 1) =  + 11.4867 *begin_dx*begin_dy + 1.11936 *begin_y*begin_dx + 1.37913 *begin_x*begin_dy + 0.0527357 *begin_x*begin_y + 7.73494e-06 *begin_x*lens_ipow(begin_y, 3) + -6.16008e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 6.00342e-06 *lens_ipow(begin_x, 5)*begin_dy + -0.397766 *begin_x*begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 2.06478e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)+0.0f;
    dx1_domega0(1, 0) =  + 11.9777 *begin_dx*begin_dy + 1.41114 *begin_y*begin_dx + 1.14136 *begin_x*begin_dy + 0.0537161 *begin_x*begin_y + 8.13457e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx + -4.51867e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 9.88222e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3) + 8.54451e-06 *lens_ipow(begin_y, 5)*begin_dx*begin_lambda + -8.46395e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dy*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 29.2795  + 0.491387 *lens_ipow(begin_lambda, 2) + 17.8374 *lens_ipow(begin_dy, 2) + 5.98883 *lens_ipow(begin_dx, 2) + 3.68362 *begin_y*begin_dy + 0.0773049 *lens_ipow(begin_y, 2) + 1.14136 *begin_x*begin_dx + 0.0237446 *lens_ipow(begin_x, 2) + 8.83436e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -4.51867e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 4.64604e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dy + -8.46395e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_lambda + 1.40969e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy*begin_lambda+0.0f;
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
    out(0) =  + 27.6047 *begin_dx + -0.0787885 *begin_x + 0.301944 *begin_dx*begin_lambda + -0.00673323 *begin_x*begin_lambda + -5.30653 *begin_dx*lens_ipow(begin_dy, 2) + -5.06576 *lens_ipow(begin_dx, 3) + 0.511827 *begin_y*begin_dx*begin_dy + 0.0211129 *lens_ipow(begin_y, 2)*begin_dx + 0.370001 *begin_x*lens_ipow(begin_dy, 2) + 0.885486 *begin_x*lens_ipow(begin_dx, 2) + 0.0440776 *begin_x*begin_y*begin_dy + 0.000923606 *begin_x*lens_ipow(begin_y, 2) + 0.066028 *lens_ipow(begin_x, 2)*begin_dx + 0.000929464 *lens_ipow(begin_x, 3) + 0.0185276 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 5.86058e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3) + -9.08966e-06 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 2.87777e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 2) + -0.00561359 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_lambda + -1.60648e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + 7.57372e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 3.39376e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -6.74613e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + 3.22459e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2);
    out(1) =  + 27.2138 *begin_dy + -0.0789689 *begin_y + 1.74778 *begin_dy*begin_lambda + -0.00657108 *begin_y*begin_lambda + -1.30978 *begin_dy*lens_ipow(begin_lambda, 2) + -4.85972 *lens_ipow(begin_dy, 3) + -5.25186 *lens_ipow(begin_dx, 2)*begin_dy + 0.888166 *begin_y*lens_ipow(begin_dy, 2) + 0.354009 *begin_y*lens_ipow(begin_dx, 2) + 0.065279 *lens_ipow(begin_y, 2)*begin_dy + 0.000929033 *lens_ipow(begin_y, 3) + 0.488387 *begin_x*begin_dx*begin_dy + 0.043765 *begin_x*begin_y*begin_dx + 0.0210927 *lens_ipow(begin_x, 2)*begin_dy + 0.000923415 *lens_ipow(begin_x, 2)*begin_y + -0.000352077 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 3.54074e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2) + -0.000138202 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -1.00617e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dx*begin_dy + 0.000267581 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 3.75726e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + 5.63608e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2)*begin_dy + -1.00604e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 8.24741e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 3);
    out(2) =  + -0.231266 *begin_dx + -0.035405 *begin_x + 0.000318886 *begin_x*begin_lambda + 0.295927 *begin_dx*lens_ipow(begin_dy, 2) + 0.321991 *lens_ipow(begin_dx, 3) + 0.0134198 *begin_y*begin_dx*begin_dy + 0.000205392 *lens_ipow(begin_y, 2)*begin_dx + 0.00569662 *begin_x*lens_ipow(begin_dy, 2) + 0.0205933 *begin_x*lens_ipow(begin_dx, 2) + 0.000213389 *begin_x*begin_y*begin_dy + 1.75372e-05 *begin_x*lens_ipow(begin_y, 2) + 0.000413844 *lens_ipow(begin_x, 2)*begin_dx + 1.74022e-05 *lens_ipow(begin_x, 3) + -8.5934e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy + -1.52291e-08 *begin_x*lens_ipow(begin_y, 4) + -0.030078 *begin_y*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 2.94613e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3) + -4.17526e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -2.21591e-09 *lens_ipow(begin_x, 6)*begin_dx + -4.21924e-11 *lens_ipow(begin_x, 7) + -0.0730298 *begin_x*lens_ipow(begin_dx, 6)*begin_lambda + -1.55475e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 5.01773e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.859484 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2);
    out(3) =  + -0.227173 *begin_dy + -0.0353581 *begin_y + 0.000372305 *begin_y*begin_lambda + 0.245941 *lens_ipow(begin_dy, 3) + 0.151344 *lens_ipow(begin_dx, 2)*begin_dy + 0.0170548 *begin_y*lens_ipow(begin_dy, 2) + 0.00242289 *begin_y*lens_ipow(begin_dx, 2) + 0.000314307 *lens_ipow(begin_y, 2)*begin_dy + 1.65363e-05 *lens_ipow(begin_y, 3) + 0.004657 *begin_x*begin_dx*begin_dy + 1.41833e-05 *lens_ipow(begin_x, 2)*begin_y + 0.0347067 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -7.9326e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.00190414 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.00189992 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 5.18416e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + -2.27386e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 7.98676e-05 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + 1.14283e-06 *lens_ipow(begin_x, 4)*begin_dy + -0.0219504 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + -0.0591546 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -2.17665e-09 *lens_ipow(begin_y, 6)*begin_dy + -4.13305e-11 *lens_ipow(begin_y, 7) + -1.74695e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3);
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
    domega2_dx0(0, 0) =  + -0.035405  + 0.000318886 *begin_lambda + 0.00569662 *lens_ipow(begin_dy, 2) + 0.0205933 *lens_ipow(begin_dx, 2) + 0.000213389 *begin_y*begin_dy + 1.75372e-05 *lens_ipow(begin_y, 2) + 0.000827688 *begin_x*begin_dx + 5.22065e-05 *lens_ipow(begin_x, 2) + -8.5934e-07 *lens_ipow(begin_y, 3)*begin_dy + -1.52291e-08 *lens_ipow(begin_y, 4) + -4.17526e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + -1.32955e-08 *lens_ipow(begin_x, 5)*begin_dx + -2.95347e-10 *lens_ipow(begin_x, 6) + -0.0730298 *lens_ipow(begin_dx, 6)*begin_lambda + -4.66425e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 2.00709e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + -0.859484 *lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(0, 1) =  + 0.0134198 *begin_dx*begin_dy + 0.000410783 *begin_y*begin_dx + 0.000213389 *begin_x*begin_dy + 3.50745e-05 *begin_x*begin_y + -2.57802e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy + -6.09165e-08 *begin_x*lens_ipow(begin_y, 3) + -0.030078 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 1.17845e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -1.25258e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -1.55475e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 1.00355e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_lambda+0.0f;
    domega2_dx0(1, 0) =  + 0.004657 *begin_dx*begin_dy + 2.83666e-05 *begin_x*begin_y + 0.0347067 *begin_dx*lens_ipow(begin_dy, 3) + -7.9326e-07 *lens_ipow(begin_y, 3)*begin_dx + 0.00380829 *begin_x*lens_ipow(begin_dy, 3) + 0.00379985 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 0.000103683 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -4.54771e-08 *begin_x*lens_ipow(begin_y, 3) + 0.000239603 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 4.57134e-06 *lens_ipow(begin_x, 3)*begin_dy + -5.24086e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.0353581  + 0.000372305 *begin_lambda + 0.0170548 *lens_ipow(begin_dy, 2) + 0.00242289 *lens_ipow(begin_dx, 2) + 0.000628614 *begin_y*begin_dy + 4.9609e-05 *lens_ipow(begin_y, 2) + 1.41833e-05 *lens_ipow(begin_x, 2) + -2.37978e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 5.18416e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -6.82157e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -0.0219504 *lens_ipow(begin_dy, 4)*begin_lambda + -0.0591546 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -1.30599e-08 *lens_ipow(begin_y, 5)*begin_dy + -2.89313e-10 *lens_ipow(begin_y, 6) + -1.74695e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)+0.0f;
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
  out[4] =  + 2.00847 *begin_lambda + -4.36888 *lens_ipow(begin_lambda, 2) + -0.0433574 *lens_ipow(begin_dy, 2) + -0.0271652 *lens_ipow(begin_dx, 2) + -0.00241047 *begin_y*begin_dy + -4.47081e-05 *lens_ipow(begin_y, 2) + -0.00189247 *begin_x*begin_dx + -2.65126e-05 *lens_ipow(begin_x, 2) + 4.4729 *lens_ipow(begin_lambda, 3) + -1.77278 *lens_ipow(begin_lambda, 4) + -0.593685 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.271492 *lens_ipow(begin_dx, 4) + 0.000113461 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 0.000225346 *begin_x*begin_y*begin_dx*begin_dy + 0.000119094 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -2.83501e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -1.062e-05 *lens_ipow(begin_x, 3)*begin_dx + -3.09779e-07 *lens_ipow(begin_x, 4) + -1.15192 *lens_ipow(begin_dy, 6) + -3.7942e-08 *lens_ipow(begin_y, 5)*begin_dy + -1.02644e-09 *lens_ipow(begin_y, 6) + -3.95053e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 3.84259e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -1.26218e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4);
else
  out[4] = 0.0f;
} break;
