#include "lenssystem.h"
#include "raytrace.h"

//json parsing
#include "../ext/json.hpp"
#include <string>
#include <fstream>
using json = nlohmann::json;



int main(int argc, char *argv[]){
  const char *id = argv[1];

  static lens_element_t lenses[50];
  float zoom = 0.0f;

  int lenses_cnt = lens_configuration(lenses, id, 0);
  float lens_length = 0;
  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses+i, zoom);
  

  int dim_up = 1;
  int draw_aspheric = 1;


/*
  // read lens database and add raytraced focal length
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";

  std::ifstream in_json(lens_database_path.c_str());
  json lens_database = json::parse(in_json);

  printf("Focal length supplied by patent: %f\n", lens_database[id]["focal-length-mm-patent"].get<float>());
  printf("Focal length raytraced: %f\n", raytraced_focal_length);

  lens_database[id]["focal-length-mm-raytraced"] = raytraced_focal_length;

  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;

  printf("Written raytraced focal length [%f] for id [%s] to database\n", raytraced_focal_length, id);
*/





  // write simple linear search for optimal last element thickness, so focal point falls on origin
  const float len = lens_length/10.0f;
  const float y = 0.5*lenses[0].housing_radius;

  float err = 99999.0;
  float original_last_element_thickness = lenses[lenses_cnt-1].thickness_mid;
  float optimal_thickness = 0.0f;

  for(int extra_thickness = -20.0; extra_thickness < 20.0; extra_thickness += 0.01){

    // change last element thickness
    lenses[lenses_cnt-1].thickness_mid = original_last_element_thickness + extra_thickness;

    float cam_pos[3] = {0.0f};
    float cam_dir[3] = {0.0f};
    cam_pos[dim_up] = y;


    cam_dir[2] = cam_pos[2] - 99999;
    cam_dir[dim_up] = cam_pos[dim_up];
    raytrace_normalise(cam_dir);
    for(int i=0;i<3;i++) cam_pos[i] -= 0.1f * cam_dir[i];


    const float lambda = 0.5f;
    float in[5] = {0.0f};
    float out[5] = {0.0f};
    float ap[5] = {0.0f};
    float inrt[5] = {0.0f};
    float outrt[5] = {0.0f};
    inrt[4] = outrt[4] = in[4] = out[4] = ap[4] = lambda;
    float t, n[3] = {0.0f};

    spherical(cam_pos, cam_dir, &t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n);
    
    for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)

    csToSphere(cam_pos, cam_dir, in, in+2, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
    sphereToCs(in, in + 2, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);

    for(int i=0;i<5;i++) inrt[i] = in[i];

    
    float distance = evaluate_reverse_intersection_y0(lenses, lenses_cnt, zoom, inrt, outrt, dim_up, draw_aspheric);
    if (distance < err && err >= 0.0f){
      err = distance;
      optimal_thickness = lenses[lenses_cnt-1].thickness_mid;
      printf("distance: %f\n", distance);
    }
    // else break to avoid further calculations since it repeats linearly?
  }

  printf("Optimal thickness: %f\n", optimal_thickness);
  return optimal_thickness;
}