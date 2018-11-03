#include "lenssystem.h"
#include "raytrace.h"
#include <string>
#include "../../fmt/include/fmt/format.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
  const char *id = argv[1];

  std::string lens_database_path = fmt::format("{}/database/lenses.json", std::getenv("LENTIL_PATH"));
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);


  static lens_element_t lenses[50];

  // loading lens config with focallength=0, which means no scale transform on the lens
  int lenses_cnt = lens_configuration(lenses, id, 0);

  float zoom = 0.0f;
  int dim_up = 0;
  const float lambda = 0.55f;
  std::vector<float> positiondata = {0.0, 0.0};
  float lens_length = 0.0;
  int draw_aspheric = 1;
  float max_aperture_radius = 0.0f;
  float prev_best_aperture_radius = 0.0f;
  int cnt = 0;
  const int max_tries = 1000;

  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses+i, zoom);

  for(int wedge = 1; wedge < max_tries; wedge++){

    float cam_pos[3] = {0.0, 0.0, 9999.0f};
    float y_wedge = lenses[0].housing_radius / (static_cast<float>(max_tries)/static_cast<float>(wedge));
    cam_pos[dim_up] = y_wedge;

    float cam_dir[3] = {0.0, 0.0, -cam_pos[2]*10.0f};
    cam_dir[dim_up] = cam_pos[dim_up];
    raytrace_normalise(cam_dir);
    
    float in[5] = {0.0f};
    float out[5] = {0.0f};
    float ap[5] = {0.0f};
    float inrt[5] = {0.0f};
    float outrt[5] = {0.0f};
    inrt[4] = outrt[4] = in[4] = out[4] = ap[4] = lambda;
    float t, n[3] = {0.0f};

    if (!strcasecmp(lenses[0].geometry, "cyl-y")){
      cylindrical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, true);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
    }
    else if (!strcasecmp(lenses[0].geometry, "cyl-x")){
      cylindrical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, false);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
    }
    else {
      spherical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToSphere(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
    }

    for(int i=0;i<5;i++) inrt[i] = in[i];
    
    // evaluate until ray is blocked, positiondata will still have value of previous ray
    if (!evaluate_reverse_fstop(lenses, lenses_cnt, zoom, inrt, outrt, dim_up, draw_aspheric, positiondata, max_aperture_radius)){
      break;
    } else {
      prev_best_aperture_radius = max_aperture_radius;
    }

    cnt += 1;
  }

  fmt::print("Last valid exit vertex position: [{}, {}]\n", positiondata[0], positiondata[1]);
  fmt::print("Failed at try {} of {}\n", cnt, max_tries);

  float theta = std::atan(positiondata[1] / positiondata[0]);
  float fstop = 1.0 / (std::sin(theta)* 2.0);

  if ((fstop != fstop) || (fstop == 0.0)){
    fmt::print("f-stop has an incorrect value [{}], aborting\n", fstop);
    return 0;
  }


  lens_database[id]["fstop"] = fstop;
  fmt::print("Added calculated f-stop [{}] to lens database.\n", fstop);
  lens_database[id]["max-fstop-aperture-radius"] = prev_best_aperture_radius;
  fmt::print("Added maximum aperture radius [{}] to lens database.\n", prev_best_aperture_radius);

  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
}
