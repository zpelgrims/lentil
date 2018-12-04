#include <vector>
#include <iomanip>
#include "lenssystem.h"
#include "raytrace.h"
#include "../../fmt/include/fmt/format.h"
#include "../../Eigen/Eigen/Dense"

//json parsing
#include "../ext/json.hpp"
#include <string>
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[]){
  const char *id = argv[1];

  std::vector<lens_element_t> lenses;
  const int dim_up = 0; // needed to calculate the vertical FOV since that's the standard for anamorphic lenses
  const float zoom = 0.0f;
  const int lenses_cnt = lens_configuration(lenses, id, 0);
  float lens_length = 0;
  for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses[i], zoom);

  Eigen::Vector3f cam_pos(0, 0, 0);
  cam_pos[dim_up] = lenses[lenses_cnt-1].housing_radius * 0.5f;
  Eigen::Vector3f cam_dir(0, 0, 0);
  cam_dir[2] = cam_pos[2] + 99999;
  cam_dir[dim_up] = cam_pos[dim_up];

  const float lambda = 0.55f;
  Eigen::VectorXf inrt(5); inrt << cam_pos[0], cam_pos[1], cam_pos[2], 0.0, lambda;
  Eigen::VectorXf outrt(5); outrt << cam_dir[0], cam_dir[1], cam_dir[2], 0.0, lambda;
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