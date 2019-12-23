#include "lenssystem.h"
#include "raytrace.h"
#include <iomanip>
#include "../../fmt/include/fmt/format.h"

//json parsing
#include "../ext/json.hpp"
#include <string>
#include <fstream>
using json = nlohmann::json;



int main(int argc, char *argv[]){
  const char *id = argv[1];
  std::vector<lens_element_t> lenses;
  const double zoom = 0.0;
  const int lenses_cnt = lens_configuration(lenses, id, 0);
  const int dim_up = 1;
  const int draw_aspheric = 1;
  double err = 99999.0;
  double original_last_element_thickness = lenses[lenses_cnt-1].thickness_short;
  double optimal_thickness = 0.0;
  const double lambda = 0.55;

  for(double extra_thickness = 500.0; extra_thickness > -500.0; extra_thickness -= 0.001){

    // change last element thickness
    lenses[lenses_cnt-1].thickness_short = original_last_element_thickness + extra_thickness;
    double lens_length = 0;
    for(int i=0;i<lenses_cnt;i++) lens_length += lens_get_thickness(lenses[i], zoom);

    Eigen::Vector3d cam_pos(0,0,0);
    Eigen::Vector3d cam_dir(0,0,0);
    cam_pos(dim_up) = 0.1*lenses[lenses_cnt-1].housing_radius;

    cam_dir(2) = cam_pos(2) - 99999;
    cam_dir(dim_up) = cam_pos(dim_up);
    raytrace_normalise(cam_dir);
    for(int i=0;i<3;i++) cam_pos(i) -= 0.1f * cam_dir(i);
    
    Eigen::VectorXd in(5); in << 0,0,0,0,lambda;
    Eigen::VectorXd out(5); out << 0,0,0,0,lambda;
    Eigen::VectorXd ap(5); ap << 0,0,0,0,lambda;
    Eigen::VectorXd inrt(5); inrt << 0,0,0,0,lambda;
    Eigen::VectorXd outrt(5); outrt << 0,0,0,0,lambda;
    double t = 0.0f;
    Eigen::Vector3d n(0,0,0);

    Eigen::Vector2d outpos(0,0);
    Eigen::Vector2d outdir(0,0);
    
    if (stringcmp(lenses[0].geometry, "cyl-y")){
      // intersection with first lens element, but seems like a duplicate purpose of the algebra method above..
      cylindrical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, true);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
      cylinderToCs(outpos, outdir, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, true);
    }
    else if (stringcmp(lenses[0].geometry, "cyl-x")){
      // intersection with first lens element, but seems like a duplicate purpose of the algebra method above..
      cylindrical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n, false);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToCylinder(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
      cylinderToCs(outpos, outdir, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius, false);
    }
    else {
      // intersection with first lens element, but seems like a duplicate purpose of the algebra method above..
      spherical(cam_pos, cam_dir, t, lenses[0].lens_radius, lens_length - lenses[0].lens_radius, lenses[0].housing_radius, n);
      for(int i=0;i<3;i++) cam_dir[i] = - cam_dir[i]; // need to point away from surface (dot(n,dir) > 0)
      csToSphere(cam_pos, cam_dir, outpos, outdir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
      sphereToCs(outpos, outdir, cam_pos, cam_dir, lens_length - lenses[0].lens_radius, lenses[0].lens_radius);
    }

    in(0) = outpos(0);
    in(1) = outpos(1);
    in(2) = outdir(0);
    in(3) = outdir(1);
    
    for(int i=0;i<5;i++) inrt(i) = in(i);
    
    double distance = evaluate_reverse_intersection_y0(lenses, lenses_cnt, zoom, inrt, outrt, dim_up, draw_aspheric);

    if (distance < err && distance >= 0.0f){
      err = distance;
      optimal_thickness = lenses[lenses_cnt-1].thickness_short;
    }
  }

  if (optimal_thickness <= 0.001){
    fmt::print("Raytraced optimal offset is [{}], seems wrong.. aborting.\n", optimal_thickness);
    return 0;
  }


  // read lens database and adjust thickness of last lens element
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";
  std::ifstream in_json(lens_database_path.c_str());
  json lens_database = json::parse(in_json);

  fmt::print("Last lens element thickness supplied by patent: {}\n", lens_database[id]["optical-elements-patent"][lenses_cnt-1]["thickness"].get<float>());
  fmt::print("Last lens element thickness raytraced: {}\n", optimal_thickness);

  // should i create separate database entry to preserve the original thickness..?
  lens_database[id]["optical-elements-patent"][lenses_cnt-1]["thickness"] = optimal_thickness;

  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
  fmt::print("Written optimal offset [{}] for id [{}] to database\n", optimal_thickness, id);
}