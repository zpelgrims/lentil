#include "lenssystem.h"
#include "raytrace.h"
#include <string>
#include <iomanip>
#include <vector>
#include "../../fmt/include/fmt/format.h"
#include "../../Eigen/Eigen/Dense"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
  const char *id = argv[1];
  const int focallength = std::atoi(argv[2]);

  std::string lens_database_path = fmt::format("{}/database/lenses.json", std::getenv("LENTIL_PATH"));
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);


  std::vector<lens_element_t> lenses;

  // loading lens config with focallength=0, which means no scale transform on the lens
  const int lenses_cnt = lens_configuration(lenses, id, focallength);

  const float zoom = 0.0f;
  const int dim_up = 0;
  const float lambda = 0.55f;
  Eigen::Vector2f positiondata(0, 0);
  float lens_length = 0.0;
  const int draw_aspheric = 1;
  float max_aperture_radius = 0.0f;
  float prev_best_aperture_radius = 0.0f;
  int cnt = 0;
  const int max_tries = 1000;

  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses[i], zoom);

  for(int wedge = 1; wedge < max_tries; wedge++){

    Eigen::Vector3f cam_pos(0.0, 0.0, 9999.0f);
    float y_wedge = lenses[0].housing_radius / (static_cast<float>(max_tries)/static_cast<float>(wedge));
    cam_pos(dim_up) = y_wedge;

    Eigen::Vector3f cam_dir(0.0, 0.0, -cam_pos(2)*10.0f);
    cam_dir(dim_up) = cam_pos(dim_up);
    raytrace_normalise(cam_dir);
    
    Eigen::VectorXf in(0,0,0,0,0);
    Eigen::VectorXf out(0,0,0,0,0);
    Eigen::VectorXf ap(0,0,0,0,0);
    in(4) = out(4) = ap(4) = lambda;
    float t = 0.0;
    Eigen::VectorXf n(0,0,0);
    
    Eigen::Vector2f outpos(0,0);
    Eigen::Vector2f outdir(0,0);
    
    // intersection on first lens element
    if (stringcmp(lenses[0].geometry, "cyl-y")){
      cylindrical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, true);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
    }
    else if (stringcmp(lenses[0].geometry, "cyl-x")){
      cylindrical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, false);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
    }
    else {
      spherical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToSphere(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
    }

    in(0) = outpos(0);
    in(1) = outpos(1);
    in(2) = outdir(0);
    in(3) = outdir(1);
    
    // evaluate until ray is blocked, positiondata will still have value of previous ray
    if (evaluate_reverse_fstop(lenses, lenses_cnt, zoom, in, out, dim_up, draw_aspheric, positiondata, max_aperture_radius)){
      prev_best_aperture_radius = max_aperture_radius;
    } else break;

    cnt += 1;
  }

  fmt::print("Last valid exit vertex position: [{}, {}]\n", positiondata(0), positiondata(1));
  fmt::print("Failed at try {} of {}\n", cnt, max_tries);

  float theta = std::atan(positiondata(1) / positiondata(0));
  float fstop = 1.0 / (std::sin(theta)* 2.0);

  if ((fstop != fstop) || (fstop == 0.0)){
    fmt::print("f-stop has an incorrect value [{}], aborting\n", fstop);
    return 0;
  }


  std::string focallength_str = (focallength == 0) ? "unscaled" : std::to_string(focallength);
  lens_database[id]["fstop"][focallength_str] = fstop;
  fmt::print("Added calculated f-stop [{}] for focallength [{}] to lens database.\n", fstop, focallength);
  lens_database[id]["max-fstop-aperture-radius"][focallength_str] = prev_best_aperture_radius;
  fmt::print("Added maximum aperture radius [{}] for focallength [{}] to lens database.\n", prev_best_aperture_radius, focallength);


  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
}
