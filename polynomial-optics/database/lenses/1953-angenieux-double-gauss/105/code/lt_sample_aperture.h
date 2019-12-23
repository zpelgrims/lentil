case angenieux__double_gauss__1953__105mm:
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
       + 56.3087 *begin_dx + 0.156651 *begin_x + 0.258755 *begin_x*begin_lambda + 14.0751 *begin_dx*begin_lambda + -9.73039 *begin_dx*lens_ipow(begin_lambda, 2) + -9.34163e-05 *lens_ipow(begin_x, 3) + -0.207774 *begin_x*lens_ipow(begin_dx, 2) + -0.0342282 *begin_y*begin_dx*begin_dy + -0.172519 *begin_x*lens_ipow(begin_dy, 2) + -34.9741 *lens_ipow(begin_dx, 3) + -0.176972 *begin_x*lens_ipow(begin_lambda, 2) + -34.8129 *begin_dx*lens_ipow(begin_dy, 2) + -9.4603e-05 *begin_x*lens_ipow(begin_y, 2) + 0.0010461 *lens_ipow(begin_y, 2)*begin_dx + 0.00211667 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.271262 *begin_x*lens_ipow(begin_dx, 4) + 15.1711 *begin_dx*lens_ipow(begin_dy, 4) + -0.00464763 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.52875 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 15.6367 *lens_ipow(begin_dx, 5) + 0.265624 *begin_x*lens_ipow(begin_dy, 4) + 0.0126243 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 31.0198 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.00918067 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda,
       + 0.156422 *begin_y + 56.3115 *begin_dy + 14.0711 *begin_dy*begin_lambda + 0.259668 *begin_y*begin_lambda + -0.17783 *begin_y*lens_ipow(begin_lambda, 2) + -0.17361 *begin_y*lens_ipow(begin_dx, 2) + -34.9925 *lens_ipow(begin_dy, 3) + -0.206411 *begin_y*lens_ipow(begin_dy, 2) + -9.72667 *begin_dy*lens_ipow(begin_lambda, 2) + -9.34083e-05 *lens_ipow(begin_y, 3) + -0.0345475 *begin_x*begin_dx*begin_dy + -34.7687 *lens_ipow(begin_dx, 2)*begin_dy + 0.00104257 *lens_ipow(begin_x, 2)*begin_dy + -9.44768e-05 *lens_ipow(begin_x, 2)*begin_y + 0.00210945 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 15.7303 *lens_ipow(begin_dy, 5) + 30.5478 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.266563 *begin_y*lens_ipow(begin_dy, 4) + -0.00464253 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 15.0222 *lens_ipow(begin_dx, 4)*begin_dy + 0.527253 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.012571 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.269931 *begin_y*lens_ipow(begin_dx, 4) + -0.00891039 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 56.3087  + 14.0751 *begin_lambda + -9.73039 *lens_ipow(begin_lambda, 2) + -0.415548 *begin_x*begin_dx + -0.0342282 *begin_y*begin_dy + -104.922 *lens_ipow(begin_dx, 2) + -34.8129 *lens_ipow(begin_dy, 2) + 0.0010461 *lens_ipow(begin_y, 2) + 0.00211667 *lens_ipow(begin_x, 2)*begin_lambda + 1.08505 *begin_x*lens_ipow(begin_dx, 3) + 15.1711 *lens_ipow(begin_dy, 4) + -0.0139429 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.0575 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 78.1835 *lens_ipow(begin_dx, 4) + 0.0252486 *begin_x*begin_y*begin_dx*begin_dy + 93.0595 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00918067 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda+0.0f;
    dx1_domega0(0, 1) =  + -0.0342282 *begin_y*begin_dx + -0.345039 *begin_x*begin_dy + -69.6257 *begin_dx*begin_dy + 60.6846 *begin_dx*lens_ipow(begin_dy, 3) + 1.0575 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 1.0625 *begin_x*lens_ipow(begin_dy, 3) + 0.0126243 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 62.0396 *lens_ipow(begin_dx, 3)*begin_dy + -0.0183613 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0(1, 0) =  + -0.347219 *begin_y*begin_dx + -0.0345475 *begin_x*begin_dy + -69.5374 *begin_dx*begin_dy + 61.0956 *begin_dx*lens_ipow(begin_dy, 3) + 60.0889 *lens_ipow(begin_dx, 3)*begin_dy + 1.05451 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.012571 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 1.07972 *begin_y*lens_ipow(begin_dx, 3) + -0.0178208 *lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda+0.0f;
    dx1_domega0(1, 1) =  + 56.3115  + 14.0711 *begin_lambda + -104.977 *lens_ipow(begin_dy, 2) + -0.412823 *begin_y*begin_dy + -9.72667 *lens_ipow(begin_lambda, 2) + -0.0345475 *begin_x*begin_dx + -34.7687 *lens_ipow(begin_dx, 2) + 0.00104257 *lens_ipow(begin_x, 2) + 0.00210945 *lens_ipow(begin_y, 2)*begin_lambda + 78.6515 *lens_ipow(begin_dy, 4) + 91.6434 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 1.06625 *begin_y*lens_ipow(begin_dy, 3) + -0.0139276 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 15.0222 *lens_ipow(begin_dx, 4) + 1.05451 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0251419 *begin_x*begin_y*begin_dx*begin_dy + -0.00891039 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_lambda+0.0f;
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
    out(0) =  + 104.283 *begin_dx + -0.604711 *begin_x + 0.559077 *begin_x*begin_lambda + 1.88591 *begin_dx*begin_lambda + -0.000207844 *lens_ipow(begin_x, 3) + 0.16019 *begin_x*lens_ipow(begin_dx, 2) + 0.247335 *begin_x*lens_ipow(begin_dy, 2) + -54.8643 *lens_ipow(begin_dx, 3) + -0.37374 *begin_x*lens_ipow(begin_lambda, 2) + -45.5852 *begin_dx*lens_ipow(begin_dy, 2) + 0.0050139 *lens_ipow(begin_x, 2)*begin_dx + -0.000221945 *begin_x*lens_ipow(begin_y, 2) + 0.00392862 *begin_x*begin_y*begin_dy + 0.0033936 *lens_ipow(begin_y, 2)*begin_dx + 2.34375 *begin_x*lens_ipow(begin_dx, 4) + 0.0494838 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3) + 2.07909 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 52.9208 *lens_ipow(begin_dx, 5) + 0.0581811 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.41756 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 79.1018 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 1.66507 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + 0.0939669 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 4) + 0.153656 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 4);
    out(1) =  + -0.497303 *begin_y + 104.94 *begin_dy + 0.155185 *begin_y*begin_lambda + -48.7492 *lens_ipow(begin_dy, 3) + -0.000211153 *lens_ipow(begin_y, 3) + 0.145654 *begin_x*begin_dx*begin_dy + 0.0038186 *begin_x*begin_y*begin_dx + -42.7293 *lens_ipow(begin_dx, 2)*begin_dy + 0.00361929 *lens_ipow(begin_x, 2)*begin_dy + -0.00022272 *lens_ipow(begin_x, 2)*begin_y + 0.696317 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.0155305 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 2.7353 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.0513 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 81.6487 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -1.27958 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 59.8369 *lens_ipow(begin_dy, 5)*begin_lambda + -3.39268 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + 4.21531 *begin_y*lens_ipow(begin_dy, 4)*begin_lambda + 1.81754 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 3.53326 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 0.157453 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 5) + 0.174401 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -6.37658e-05 *lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 5);
    out(2) =  + -0.61395 *begin_dx + -0.00604072 *begin_x + -0.00323115 *begin_x*begin_lambda + 0.00989609 *begin_dx*begin_lambda + 1.49936e-06 *lens_ipow(begin_x, 3) + -0.00080346 *begin_x*lens_ipow(begin_dy, 2) + 0.29886 *lens_ipow(begin_dx, 3) + 0.00224468 *begin_x*lens_ipow(begin_lambda, 2) + 1.51276e-06 *begin_x*lens_ipow(begin_y, 2) + -1.81245e-05 *begin_x*begin_y*begin_dy + 0.59259 *begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + -1.09696e-07 *lens_ipow(begin_x, 4)*begin_dx + 4.70525e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 5.66758e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.234441 *lens_ipow(begin_dx, 5) + -0.132878 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.540235 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.000102067 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 3.18747e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 3) + 5.86451e-07 *lens_ipow(begin_x, 4)*begin_dx*lens_ipow(begin_dy, 2) + -0.00413131 *begin_x*lens_ipow(begin_dy, 6) + -0.0142793 *begin_x*lens_ipow(begin_dx, 6) + 0.00212068 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.00189804 *begin_x*begin_y*lens_ipow(begin_dx, 6)*begin_dy;
    out(3) =  + -0.00598486 *begin_y + -0.614899 *begin_dy + 0.0101927 *begin_dy*begin_lambda + -0.00338063 *begin_y*begin_lambda + 0.0023877 *begin_y*lens_ipow(begin_lambda, 2) + -0.00166545 *begin_y*lens_ipow(begin_dx, 2) + 0.309525 *lens_ipow(begin_dy, 3) + 1.39687e-06 *lens_ipow(begin_y, 3) + 0.00178603 *begin_x*begin_dx*begin_dy + -3.19256e-05 *lens_ipow(begin_y, 2)*begin_dy + -1.95075e-05 *begin_x*begin_y*begin_dx + 0.418449 *lens_ipow(begin_dx, 2)*begin_dy + 1.51807e-06 *lens_ipow(begin_x, 2)*begin_y + -0.257041 *lens_ipow(begin_dy, 5) + 0.000136172 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.60995 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 2.7209e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.000131399 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -0.353973 *lens_ipow(begin_dx, 4)*begin_dy + -0.00538212 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0143226 *begin_y*lens_ipow(begin_dy, 6) + 6.41712e-09 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + -0.0648816 *begin_x*begin_dx*lens_ipow(begin_dy, 7) + -0.319272 *begin_x*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3);
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
    domega2_dx0(0, 0) =  + -0.00604072  + -0.00323115 *begin_lambda + 4.49808e-06 *lens_ipow(begin_x, 2) + -0.00080346 *lens_ipow(begin_dy, 2) + 0.00224468 *lens_ipow(begin_lambda, 2) + 1.51276e-06 *lens_ipow(begin_y, 2) + -1.81245e-05 *begin_y*begin_dy + -4.38782e-07 *lens_ipow(begin_x, 3)*begin_dx + 9.4105e-06 *begin_x*begin_y*begin_dx*begin_dy + 1.27499e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + 2.3458e-06 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + -0.00413131 *lens_ipow(begin_dy, 6) + -0.0142793 *lens_ipow(begin_dx, 6) + 0.00212068 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.00189804 *begin_y*lens_ipow(begin_dx, 6)*begin_dy+0.0f;
    domega2_dx0(0, 1) =  + 3.02552e-06 *begin_x*begin_y + -1.81245e-05 *begin_x*begin_dy + 4.70525e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.000113352 *begin_y*lens_ipow(begin_dx, 3) + 0.000204134 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.00212068 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.00189804 *begin_x*lens_ipow(begin_dx, 6)*begin_dy+0.0f;
    domega2_dx0(1, 0) =  + 0.00178603 *begin_dx*begin_dy + -1.95075e-05 *begin_y*begin_dx + 3.03613e-06 *begin_x*begin_y + 2.7209e-06 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -0.0648816 *begin_dx*lens_ipow(begin_dy, 7) + -0.319272 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.00598486  + -0.00338063 *begin_lambda + 0.0023877 *lens_ipow(begin_lambda, 2) + -0.00166545 *lens_ipow(begin_dx, 2) + 4.19061e-06 *lens_ipow(begin_y, 2) + -6.38512e-05 *begin_y*begin_dy + -1.95075e-05 *begin_x*begin_dx + 1.51807e-06 *lens_ipow(begin_x, 2) + 0.000272345 *begin_y*lens_ipow(begin_dy, 3) + 5.4418e-06 *begin_x*begin_y*begin_dx*begin_dy + 0.000262798 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00538212 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.0143226 *lens_ipow(begin_dy, 6) + 3.20856e-08 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2)+0.0f;
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
  out[4] =  + 0.238955  + 0.852347 *begin_lambda + -1.16722 *lens_ipow(begin_lambda, 2) + -1.52053e-06 *lens_ipow(begin_x, 2) + 0.563964 *lens_ipow(begin_lambda, 3) + -0.00410241 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -3.34491e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00476124 *begin_x*lens_ipow(begin_dx, 3) + -0.230302 *lens_ipow(begin_dy, 4) + -0.000133897 *begin_x*begin_y*begin_dx*begin_dy + -0.00464841 *begin_y*lens_ipow(begin_dy, 3) + -5.3683e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -0.00425522 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -8.9981e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.213373 *lens_ipow(begin_dx, 4) + -1.49512 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*begin_lambda + 1.07924 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.000297217 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000254507 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4) + -0.00020742 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)*begin_lambda + -1.47829e-06 *lens_ipow(begin_y, 3)*begin_dy*lens_ipow(begin_lambda, 3) + -0.2752 *lens_ipow(begin_dx, 6)*lens_ipow(begin_lambda, 2) + -1.95288e-06 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_lambda, 4) + -0.00112877 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 6)*begin_lambda;
else
  out[4] = 0.0f;
} break;
