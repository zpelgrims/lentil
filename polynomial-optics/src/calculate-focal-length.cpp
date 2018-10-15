#include "lenssystem.h"
#include "raytrace.h"
#include "../../fmt/include/fmt/format.h"

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

  float cam_pos[3] = {0.0f};
  float cam_dir[3] = {0.0f};
  cam_pos[dim_up] = lenses[lenses_cnt-1].housing_radius * 0.5f;
  cam_dir[2] = cam_pos[2] + 99999;
  cam_dir[dim_up] = cam_pos[dim_up];
  //raytrace_normalise(cam_dir);

  const float lambda = 0.5f;
  float inrt[5] = {0.0f};
  float outrt[5] = {0.0f};
  inrt[0] = cam_pos[0]; 
  inrt[1] = cam_pos[1]; 
  inrt[2] = cam_pos[2];
  outrt[0] = cam_dir[0];
  outrt[1] = cam_dir[1];
  outrt[2] = cam_dir[2];
  inrt[4] = outrt[4] = lambda;

  float raytraced_focal_length = calculate_focal_length(lenses, lenses_cnt, zoom, inrt, outrt, dim_up, true);


  // read lens database and add raytraced focal length
  std::string lens_database_path = fmt::format("{}/database/lenses.json", std::getenv("LENTIL_PATH"));
  std::ifstream in_json(lens_database_path.c_str());
  json lens_database = json::parse(in_json);

  fmt::print("Focal length supplied by patent: {0}\n", lens_database[id]["focal-length-mm-patent"].get<float>());
  fmt::print("Focal length raytraced: {}\n", raytraced_focal_length);

  lens_database[id]["focal-length-mm-raytraced"] = raytraced_focal_length;

  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
  fmt::print("Written raytraced focal length {} for id {} to database\n", raytraced_focal_length, id);
}