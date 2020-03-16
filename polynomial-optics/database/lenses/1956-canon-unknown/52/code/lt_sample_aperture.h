case canon__unknown__1956__52mm:
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
       + 35.8226 *begin_dx + 0.620986 *begin_x + 0.952585 *begin_dx*begin_lambda + 0.0240883 *begin_x*begin_lambda + -22.4048 *begin_dx*lens_ipow(begin_dy, 2) + -22.4703 *lens_ipow(begin_dx, 3) + -0.390853 *begin_y*begin_dx*begin_dy + -0.243125 *begin_x*lens_ipow(begin_dy, 2) + -0.605095 *begin_x*lens_ipow(begin_dx, 2) + -0.000861823 *begin_x*begin_y*begin_dy + 8.03683 *begin_dx*lens_ipow(begin_dy, 4) + 6.07338 *lens_ipow(begin_dx, 5) + 0.178332 *begin_x*lens_ipow(begin_dy, 4) + -4.25673e-08 *begin_x*lens_ipow(begin_y, 4) + -0.00607202 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -8.845e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2) + -2.21828e-06 *lens_ipow(begin_x, 4)*begin_dx + -3.76908 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + -3.00818 *begin_y*lens_ipow(begin_dx, 5)*begin_dy + -0.0620219 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.041359 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -1.48587e-10 *lens_ipow(begin_x, 7),
       + 35.8327 *begin_dy + 0.621162 *begin_y + 0.951909 *begin_dy*begin_lambda + 0.0241916 *begin_y*begin_lambda + -22.0497 *lens_ipow(begin_dy, 3) + -22.9791 *lens_ipow(begin_dx, 2)*begin_dy + -0.582118 *begin_y*lens_ipow(begin_dy, 2) + -0.251728 *begin_y*lens_ipow(begin_dx, 2) + -0.400865 *begin_x*begin_dx*begin_dy + -0.00113277 *begin_x*begin_y*begin_dx + -0.45529 *begin_y*lens_ipow(begin_dy, 4) + -0.453469 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.187129 *begin_y*lens_ipow(begin_dx, 4) + -0.00940776 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -0.0117416 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -3.6023e-08 *lens_ipow(begin_y, 5) + -0.672725 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.0103079 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + -9.13787e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -4.90184e-08 *lens_ipow(begin_x, 4)*begin_y + -2.46069 *begin_x*begin_dx*lens_ipow(begin_dy, 5) + -0.0403241 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 35.8226  + 0.952585 *begin_lambda + -22.4048 *lens_ipow(begin_dy, 2) + -67.4108 *lens_ipow(begin_dx, 2) + -0.390853 *begin_y*begin_dy + -1.21019 *begin_x*begin_dx + 8.03683 *lens_ipow(begin_dy, 4) + 30.3669 *lens_ipow(begin_dx, 4) + -0.00607202 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -2.21828e-06 *lens_ipow(begin_x, 4) + -11.3072 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -15.0409 *begin_y*lens_ipow(begin_dx, 4)*begin_dy + -0.186066 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.206795 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)+0.0f;
    dx1_domega0(0, 1) =  + -44.8095 *begin_dx*begin_dy + -0.390853 *begin_y*begin_dx + -0.486249 *begin_x*begin_dy + -0.000861823 *begin_x*begin_y + 32.1473 *begin_dx*lens_ipow(begin_dy, 3) + 0.713326 *begin_x*lens_ipow(begin_dy, 3) + -0.012144 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -11.3072 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -3.00818 *begin_y*lens_ipow(begin_dx, 5) + -0.124044 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy+0.0f;
    dx1_domega0(1, 0) =  + -45.9583 *begin_dx*begin_dy + -0.503457 *begin_y*begin_dx + -0.400865 *begin_x*begin_dy + -0.00113277 *begin_x*begin_y + -0.906939 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.748514 *begin_y*lens_ipow(begin_dx, 3) + -0.0234832 *lens_ipow(begin_y, 2)*begin_dx*begin_dy + -2.01818 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + -0.0206158 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -2.46069 *begin_x*lens_ipow(begin_dy, 5)+0.0f;
    dx1_domega0(1, 1) =  + 35.8327  + 0.951909 *begin_lambda + -66.1492 *lens_ipow(begin_dy, 2) + -22.9791 *lens_ipow(begin_dx, 2) + -1.16424 *begin_y*begin_dy + -0.400865 *begin_x*begin_dx + -1.82116 *begin_y*lens_ipow(begin_dy, 3) + -0.906939 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0282233 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.0117416 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.672725 *begin_x*lens_ipow(begin_dx, 3) + -0.0103079 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -12.3034 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + -0.20162 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4)+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 51.6563 *begin_dx + 0.523722 *begin_x + -24.2005 *begin_dx*lens_ipow(begin_dy, 2) + -27.1569 *lens_ipow(begin_dx, 3) + 0.00889498 *lens_ipow(begin_y, 2)*begin_dx + 0.809667 *begin_x*lens_ipow(begin_dy, 2) + 0.819783 *begin_x*lens_ipow(begin_dx, 2) + 0.036461 *begin_x*begin_y*begin_dy + 0.00024367 *begin_x*lens_ipow(begin_y, 2) + 0.0455555 *lens_ipow(begin_x, 2)*begin_dx + 0.00100706 *lens_ipow(begin_x, 3)*begin_lambda + -0.467476 *begin_x*lens_ipow(begin_dy, 4) + 0.000673556 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + 0.00056091 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.000962391 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 2) + 0.000446225 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 54.7534 *lens_ipow(begin_dx, 5)*begin_lambda + 210.952 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + 133.741 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + -0.0517292 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -9.72867e-10 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + 0.0832333 *begin_x*lens_ipow(begin_lambda, 7);
    out(1) =  + 51.5871 *begin_dy + 0.509272 *begin_y + 0.0171012 *begin_y*begin_lambda + -25.6073 *lens_ipow(begin_dy, 3) + -29.9096 *lens_ipow(begin_dx, 2)*begin_dy + 0.886045 *begin_y*lens_ipow(begin_dy, 2) + 0.857553 *begin_y*lens_ipow(begin_dx, 2) + 0.047616 *lens_ipow(begin_y, 2)*begin_dy + 0.000337546 *lens_ipow(begin_y, 3) + 0.0398231 *begin_x*begin_y*begin_dx + 0.0100237 *lens_ipow(begin_x, 2)*begin_dy + 0.000321503 *lens_ipow(begin_x, 2)*begin_y + 59.0442 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 64.1486 *lens_ipow(begin_dx, 4)*begin_dy + 0.110438 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 0.00460004 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + 4.98491e-05 *lens_ipow(begin_y, 4)*begin_dy + 1.17293 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + -0.00928132 *begin_x*begin_y*lens_ipow(begin_dx, 3) + -2.04794e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.000652643 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + -5.38956e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3);
    out(2) =  + -1.70514 *begin_dx + -0.0364797 *begin_x + -0.00034037 *begin_x*begin_lambda + -1.36131 *begin_dx*lens_ipow(begin_dy, 2) + 0.889745 *lens_ipow(begin_dx, 3) + -0.0495115 *begin_y*begin_dx*begin_dy + -0.000244209 *lens_ipow(begin_y, 2)*begin_dx + -0.0491957 *begin_x*lens_ipow(begin_dy, 2) + 0.00773053 *begin_x*lens_ipow(begin_dx, 2) + -0.00168401 *begin_x*begin_y*begin_dy + -4.78389e-06 *begin_x*lens_ipow(begin_y, 2) + -0.00045409 *lens_ipow(begin_x, 2)*begin_dx + 1.65356e-06 *lens_ipow(begin_x, 3) + 0.288011 *lens_ipow(begin_dx, 3)*begin_lambda + -0.000546333 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.00133579 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -2.50162e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 2.72453e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -0.929664 *lens_ipow(begin_dx, 5)*lens_ipow(begin_lambda, 2) + -1.45494e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 1.59233e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 2.67202e-11 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2);
    out(3) =  + -1.69535 *begin_dy + -0.0362357 *begin_y + -0.000429944 *begin_y*begin_lambda + 0.88532 *lens_ipow(begin_dy, 3) + 3.45709 *lens_ipow(begin_dx, 2)*begin_dy + -0.000647438 *lens_ipow(begin_y, 2)*begin_dy + 0.111134 *begin_x*begin_dx*begin_dy + 0.000879633 *lens_ipow(begin_x, 2)*begin_dy + 6.41826e-06 *lens_ipow(begin_x, 2)*begin_y + -4.11426 *lens_ipow(begin_dx, 4)*begin_dy + 0.0102869 *begin_y*lens_ipow(begin_dy, 4) + 0.0267431 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.0011937 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.0408203 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.137731 *begin_x*lens_ipow(begin_dx, 3)*begin_dy + 9.54291e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 2.3662e-05 *lens_ipow(begin_x, 3)*begin_dx*begin_dy + 4.06471e-07 *lens_ipow(begin_y, 4)*begin_dy*begin_lambda + 0.00200002 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -1.00442e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_lambda + 1.41819e-11 *lens_ipow(begin_y, 7)*begin_lambda + 6.83956e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3);
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
    domega2_dx0(0, 0) =  + -0.0364797  + -0.00034037 *begin_lambda + -0.0491957 *lens_ipow(begin_dy, 2) + 0.00773053 *lens_ipow(begin_dx, 2) + -0.00168401 *begin_y*begin_dy + -4.78389e-06 *lens_ipow(begin_y, 2) + -0.00090818 *begin_x*begin_dx + 4.96067e-06 *lens_ipow(begin_x, 2) + -0.00267158 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -7.50487e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 2.72453e-07 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -4.36483e-06 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 6.36933e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + 1.33601e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)+0.0f;
    domega2_dx0(0, 1) =  + -0.0495115 *begin_dx*begin_dy + -0.000488417 *begin_y*begin_dx + -0.00168401 *begin_x*begin_dy + -9.56779e-06 *begin_x*begin_y + -0.00109267 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + 8.17358e-07 *begin_x*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -1.45494e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_dy + 3.18466e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dx + 5.34403e-11 *lens_ipow(begin_x, 5)*begin_y+0.0f;
    domega2_dx0(1, 0) =  + 0.111134 *begin_dx*begin_dy + 0.00175927 *begin_x*begin_dy + 1.28365e-05 *begin_x*begin_y + 0.0408203 *begin_dx*lens_ipow(begin_dy, 3) + -0.137731 *lens_ipow(begin_dx, 3)*begin_dy + 1.90858e-08 *begin_x*lens_ipow(begin_y, 3) + 7.09861e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + 0.00400004 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + -2.00883e-08 *begin_x*lens_ipow(begin_y, 3)*begin_lambda + 0.000136791 *begin_x*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(1, 1) =  + -0.0362357  + -0.000429944 *begin_lambda + -0.00129488 *begin_y*begin_dy + 6.41826e-06 *lens_ipow(begin_x, 2) + 0.0102869 *lens_ipow(begin_dy, 4) + 0.0267431 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.00238741 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 2.86287e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 1.62589e-06 *lens_ipow(begin_y, 3)*begin_dy*begin_lambda + -3.01325e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_lambda + 9.92736e-11 *lens_ipow(begin_y, 6)*begin_lambda + 6.83956e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3)+0.0f;
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
if(out[0]*out[0]+out[1]*out[1] > camera->lens_outer_pupil_radius*camera->lens_outer_pupil_radius) error |= 16;
const double begin_x = x;
const double begin_y = y;
const double begin_dx = dx;
const double begin_dy = dy;
const double begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.499588  + 0.271573 *begin_lambda + -0.185782 *lens_ipow(begin_lambda, 2) + -0.131613 *lens_ipow(begin_dy, 2) + -0.00487529 *begin_y*begin_dy + -5.10803e-05 *lens_ipow(begin_y, 2) + -3.79632 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -2.5089 *lens_ipow(begin_dx, 4) + -0.117041 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00107758 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.121797 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.169813 *begin_x*lens_ipow(begin_dx, 3) + -0.00420154 *begin_x*begin_y*begin_dx*begin_dy + -4.14131e-05 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.0011558 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.00482165 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -4.23812e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -4.399e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + -6.55402e-05 *lens_ipow(begin_x, 3)*begin_dx + -3.54137e-07 *lens_ipow(begin_x, 4) + -2.28511 *lens_ipow(begin_dy, 6) + -0.052381 *begin_y*lens_ipow(begin_dy, 5);
else
  out[4] = 0.0f;
} break;
