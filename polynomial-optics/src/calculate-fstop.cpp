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

  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses+i, zoom);

  for(int wedge = 1; wedge < 1000; wedge++){

    float y_wedge = lenses[0].housing_radius / (1000.0/static_cast<float>(wedge));

    float cam_pos[3] = {0.0f};
    cam_pos[dim_up] = y_wedge;
    cam_pos[2] = sqrtf(lenses[0].lens_radius*lenses[0].lens_radius - lenses[0].housing_radius*lenses[0].housing_radius);
    const float s = lenses[0].lens_radius / sqrtf(cam_pos[2]*cam_pos[2] + y_wedge*y_wedge);
    cam_pos[2] *= s;
    cam_pos[dim_up] *= s;
    cam_pos[2] += lens_length - lenses[0].lens_radius;

    float cam_dir[3] = {0.0f};
    cam_dir[2] = cam_pos[2] - 99999.0;
    cam_dir[dim_up] = cam_pos[dim_up];
    raytrace_normalise(cam_dir);
    for(int i=0;i<3;i++) cam_pos[i] -= 0.1f * cam_dir[i];
    
    float in[5] = {0.0f};
    float out[5] = {0.0f};
    float ap[5] = {0.0f};
    float inrt[5] = {0.0f};
    float outrt[5] = {0.0f};
    inrt[4] = outrt[4] = in[4] = out[4] = ap[4] = lambda;
    float t, n[3] = {0.0f};

    if (!strcasecmp(lenses[0].geometry, "cyl-y")){
      // intersection with first lens element, but seems like a duplicate purpose of the algebra method above..
      cylindrical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, true);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
      cylinderToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
    }
    else if (!strcasecmp(lenses[0].geometry, "cyl-x")){
      // intersection with first lens element, but seems like a duplicate purpose of the algebra method above..
      cylindrical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, false);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
      cylinderToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
    }
    else {
      // intersection with first lens element, but seems like a duplicate purpose of the algebra method above..
      spherical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToSphere(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
      sphereToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
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
  fmt::print("Failed at try {} of 1000\n", cnt);

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
