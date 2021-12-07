case minolta__fisheye__1978__28mm:
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
       + 65.9378 *begin_dx + 0.76074 *begin_x + -4.69765 *begin_dx*begin_lambda + -0.133134 *begin_x*begin_lambda + 111.311 *begin_dx*lens_ipow(begin_dy, 2) + 111.242 *lens_ipow(begin_dx, 3) + 3.315 *begin_y*begin_dx*begin_dy + 0.021483 *lens_ipow(begin_y, 2)*begin_dx + 0.0913347 *begin_x*lens_ipow(begin_lambda, 2) + 4.37835 *begin_x*lens_ipow(begin_dx, 2) + 0.0512073 *lens_ipow(begin_x, 2)*begin_dx + 0.000173408 *lens_ipow(begin_x, 3) + 3.0545 *begin_dx*lens_ipow(begin_lambda, 3) + 5.9538 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.16575 *begin_x*begin_y*begin_dy*begin_lambda + 0.000949947 *begin_x*lens_ipow(begin_y, 2)*begin_lambda + -10.8685 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + -0.301757 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 2) + -0.00169969 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 6.52783 *begin_x*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.180696 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 0.00100043 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3),
       + 66.4563 *begin_dy + 0.760083 *begin_y + -7.53454 *begin_dy*begin_lambda + -0.130819 *begin_y*begin_lambda + 5.12406 *begin_dy*lens_ipow(begin_lambda, 2) + 111.291 *lens_ipow(begin_dy, 3) + 111.328 *lens_ipow(begin_dx, 2)*begin_dy + 0.0891919 *begin_y*lens_ipow(begin_lambda, 2) + 4.38218 *begin_y*lens_ipow(begin_dy, 2) + 0.0512712 *lens_ipow(begin_y, 2)*begin_dy + 0.00017376 *lens_ipow(begin_y, 3) + 3.29932 *begin_x*begin_dx*begin_dy + 0.021268 *lens_ipow(begin_x, 2)*begin_dy + 0.000174259 *lens_ipow(begin_x, 2)*begin_y + 5.34431 *begin_y*lens_ipow(begin_dx, 2)*begin_lambda + 0.167621 *begin_x*begin_y*begin_dx*begin_lambda + -7.3717 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + 0.322193 *begin_x*begin_dx*lens_ipow(begin_dy, 3) + -0.308168 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.00417008 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 0.185918 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 3) + 3.97146 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4)
    );
    const Eigen::Vector2d delta_ap(ap_x - pred_ap[0], ap_y - pred_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    Eigen::Matrix2d dx1_domega0;
    dx1_domega0(0, 0) =  + 65.9378  + -4.69765 *begin_lambda + 111.311 *lens_ipow(begin_dy, 2) + 333.726 *lens_ipow(begin_dx, 2) + 3.315 *begin_y*begin_dy + 0.021483 *lens_ipow(begin_y, 2) + 8.7567 *begin_x*begin_dx + 0.0512073 *lens_ipow(begin_x, 2) + 3.0545 *lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0(0, 1) =  + 222.623 *begin_dx*begin_dy + 3.315 *begin_y*begin_dx + 11.9076 *begin_x*begin_dy*begin_lambda + 0.16575 *begin_x*begin_y*begin_lambda + -21.737 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + -0.301757 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 13.0557 *begin_x*begin_dy*lens_ipow(begin_lambda, 3) + 0.180696 *begin_x*begin_y*lens_ipow(begin_lambda, 3)+0.0f;
    dx1_domega0(1, 0) =  + 222.655 *begin_dx*begin_dy + 3.29932 *begin_x*begin_dy + 10.6886 *begin_y*begin_dx*begin_lambda + 0.167621 *begin_x*begin_y*begin_lambda + -14.7434 *begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 0.322193 *begin_x*lens_ipow(begin_dy, 3) + -0.308168 *begin_x*begin_y*lens_ipow(begin_lambda, 2) + 0.185918 *begin_x*begin_y*lens_ipow(begin_lambda, 3) + 7.94292 *begin_y*begin_dx*lens_ipow(begin_lambda, 4)+0.0f;
    dx1_domega0(1, 1) =  + 66.4563  + -7.53454 *begin_lambda + 5.12406 *lens_ipow(begin_lambda, 2) + 333.872 *lens_ipow(begin_dy, 2) + 111.328 *lens_ipow(begin_dx, 2) + 8.76437 *begin_y*begin_dy + 0.0512712 *lens_ipow(begin_y, 2) + 3.29932 *begin_x*begin_dx + 0.021268 *lens_ipow(begin_x, 2) + 0.966579 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 0.0125102 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)+0.0f;
    Eigen::Matrix2d invApJ = dx1_domega0.inverse().eval();
    Eigen::Vector2d solution_dir = invApJ * delta_ap;
    dx += solution_dir(0);
    dy += solution_dir(1);
    out(0) =  + 27.7218 *begin_dx + -0.381626 *begin_x + 1.11455 *begin_dx*begin_lambda + -0.248894 *begin_x*begin_lambda + 6.40713 *begin_dx*lens_ipow(begin_dy, 2) + 0.488427 *begin_y*begin_dx*begin_dy + 0.00888042 *lens_ipow(begin_y, 2)*begin_dx + 0.184291 *begin_x*lens_ipow(begin_lambda, 2) + 0.412994 *begin_x*lens_ipow(begin_dy, 2) + 0.0130952 *begin_x*begin_y*begin_dy + 8.1243e-05 *begin_x*lens_ipow(begin_y, 2) + 2.41294 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.064039 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 0.000254231 *lens_ipow(begin_x, 3)*begin_lambda + 191.383 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 3) + -0.000334575 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + -270.479 *lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 4) + -4.03276 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 4) + -0.247584 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 4) + 10.4037 *begin_y*lens_ipow(begin_dx, 5)*begin_dy*begin_lambda + 0.197818 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)*begin_lambda + 0.203665 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 5);
    out(1) =  + 28.2551 *begin_dy + -0.377339 *begin_y + -0.208813 *begin_y*begin_lambda + 5.73877 *lens_ipow(begin_dx, 2)*begin_dy + 0.419395 *begin_y*lens_ipow(begin_dx, 2) + 0.461555 *begin_x*begin_dx*begin_dy + 0.0130355 *begin_x*begin_y*begin_dx + 0.00855988 *lens_ipow(begin_x, 2)*begin_dy + 8.14035e-05 *lens_ipow(begin_x, 2)*begin_y + 0.170939 *begin_y*lens_ipow(begin_lambda, 3) + 38.0278 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + 9.33143 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2) + 0.224021 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 0.00806679 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + -11.0729 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + -0.265756 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 0.00204267 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 3) + 1.76142 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.0274549 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + -0.00270767 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 4) + 3.29809 *begin_dy*lens_ipow(begin_lambda, 7) + -88.0672 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 5);
    out(2) =  + -0.23344 *begin_dx + -0.0315891 *begin_x + 0.000532788 *begin_x*begin_lambda + 5.12056e-05 *lens_ipow(begin_y, 2)*begin_dx + 4.47098e-06 *begin_x*lens_ipow(begin_y, 2) + 1.04754 *lens_ipow(begin_dx, 3)*begin_lambda + 0.000200832 *lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 0.00723584 *begin_x*lens_ipow(begin_dy, 2)*begin_lambda + 0.0363482 *begin_x*lens_ipow(begin_dx, 2)*begin_lambda + 0.000122196 *begin_x*begin_y*begin_dy*begin_lambda + 0.000560984 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + 1.4255e-05 *lens_ipow(begin_x, 3)*begin_lambda + 0.00100493 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -0.00251738 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.00236633 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + 2.13346e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 2.07461e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 1.8501 *begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.0427969 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -2.79078e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 3) + -0.000272255 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 4) + 1.81522e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_lambda, 4);
    out(3) =  + -0.231761 *begin_dy + -0.0312466 *begin_y + 0.719318 *lens_ipow(begin_dx, 2)*begin_dy + 0.00665683 *begin_y*lens_ipow(begin_dx, 2) + 0.0162727 *begin_x*begin_dx*begin_dy + 8.70047e-05 *begin_x*begin_y*begin_dx + 4.36731e-06 *lens_ipow(begin_x, 2)*begin_y + 1.00853e-05 *lens_ipow(begin_y, 3)*begin_lambda + 0.000590934 *lens_ipow(begin_x, 2)*begin_dy*begin_lambda + 1.33396 *lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -4.05271e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2) + -0.000600117 *lens_ipow(begin_x, 2)*begin_dy*lens_ipow(begin_lambda, 2) + 1.21603e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy + 4.99498e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 0.0720382 *begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.00103276 *lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 0.160929 *begin_x*begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.00232056 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.0111267 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*begin_lambda + 0.000375235 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.00805384 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.0003181 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2);
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
    domega2_dx0(0, 0) =  + -0.0315891  + 0.000532788 *begin_lambda + 4.47098e-06 *lens_ipow(begin_y, 2) + 0.00723584 *lens_ipow(begin_dy, 2)*begin_lambda + 0.0363482 *lens_ipow(begin_dx, 2)*begin_lambda + 0.000122196 *begin_y*begin_dy*begin_lambda + 0.00112197 *begin_x*begin_dx*begin_lambda + 4.2765e-05 *lens_ipow(begin_x, 2)*begin_lambda + -0.00251738 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.00473266 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + 6.40039e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 6.22382e-07 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -8.37235e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 3) + -0.00054451 *begin_x*begin_dx*lens_ipow(begin_lambda, 4) + 5.44567e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 4)+0.0f;
    domega2_dx0(0, 1) =  + 0.000102411 *begin_y*begin_dx + 8.94196e-06 *begin_x*begin_y + 0.000401664 *begin_y*begin_dx*begin_lambda + 0.000122196 *begin_x*begin_dy*begin_lambda + 0.00200986 *begin_y*lens_ipow(begin_dx, 3) + -0.00251738 *begin_x*lens_ipow(begin_dx, 2)*begin_dy + 2.07461e-07 *lens_ipow(begin_x, 3)*begin_dy + 0.0427969 *begin_dx*begin_dy*lens_ipow(begin_lambda, 3)+0.0f;
    domega2_dx0(1, 0) =  + 0.0162727 *begin_dx*begin_dy + 8.70047e-05 *begin_y*begin_dx + 8.73462e-06 *begin_x*begin_y + 0.00118187 *begin_x*begin_dy*begin_lambda + -0.00120023 *begin_x*begin_dy*lens_ipow(begin_lambda, 2) + 2.43206e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 9.98996e-09 *begin_x*lens_ipow(begin_y, 3) + 0.160929 *begin_dx*lens_ipow(begin_dy, 3)*begin_lambda + 0.00232056 *begin_y*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.0222534 *begin_x*lens_ipow(begin_dy, 3)*begin_lambda + 0.00075047 *begin_x*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + -0.0161077 *begin_x*lens_ipow(begin_dy, 3)*lens_ipow(begin_lambda, 2) + -0.0006362 *begin_x*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
    domega2_dx0(1, 1) =  + -0.0312466  + 0.00665683 *lens_ipow(begin_dx, 2) + 8.70047e-05 *begin_x*begin_dx + 4.36731e-06 *lens_ipow(begin_x, 2) + 3.0256e-05 *lens_ipow(begin_y, 2)*begin_lambda + -1.21581e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 2.43206e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 1.49849e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 0.0720382 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 0.00206553 *begin_y*begin_dy*lens_ipow(begin_lambda, 3) + 0.00232056 *begin_x*begin_dx*lens_ipow(begin_dy, 2)*begin_lambda + 0.000375235 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*begin_lambda + -0.0003181 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 2)+0.0f;
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
  out[4] =  + 2.44404 *begin_lambda + -5.54827 *lens_ipow(begin_lambda, 2) + -0.132699 *lens_ipow(begin_dx, 2) + -0.00405603 *begin_x*begin_dx + -2.49776e-05 *lens_ipow(begin_x, 2) + 5.89998 *lens_ipow(begin_lambda, 3) + -2.41918 *lens_ipow(begin_lambda, 4) + -6.9291 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -3.79022 *lens_ipow(begin_dx, 4) + -0.0737708 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.0785865 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -0.104404 *begin_x*lens_ipow(begin_dx, 3) + 8.12739e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx + -0.000352383 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.000794638 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + -246.544 *lens_ipow(begin_dy, 6) + -15.9793 *begin_y*lens_ipow(begin_dy, 5) + -0.424847 *lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.00582798 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + -4.40369e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -1.94026e-07 *lens_ipow(begin_y, 5)*begin_dy + -4.88188e-10 *lens_ipow(begin_y, 6);
else
  out[4] = 0.0f;
} break;
