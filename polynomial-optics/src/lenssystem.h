#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../../fmt/include/fmt/format.h"


//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


typedef struct lens_element_t
{
  float lens_radius;
  float thickness_short;
  float thickness_mid;
  float thickness_long;
  float ior;
  float vno;
  float housing_radius;
  std::vector<float> aspheric_correction_coefficients;
  int aspheric;
  std::string material;
  std::string geometry;
} lens_element_t;


// case insensitive string comparison
inline bool stringcmp(const std::string& a, const std::string& b) {
  unsigned int sz = a.size();
  if (b.size() != sz) {
    return false;
  }
  for (unsigned int i = 0; i < sz; ++i){
    if (std::tolower(a[i]) != std::tolower(b[i])) {
      return false;
    }
  }

  return true;
}

static inline float lens_get_thickness(const lens_element_t l, const float zoom) {
  if(zoom < .5f) return l.thickness_short * (1.0f - 2.0f*zoom) + l.thickness_mid * 2.0f * zoom;
  else           return l.thickness_mid * (1.0f - 2.0f*(zoom - 0.5f)) + l.thickness_long * (zoom - 0.5f) * 2.0f;
}


float lens_get_aperture_radius(const std::vector<lens_element_t> l, const int num) {
  for(int k=0;k<num;k++) {
    if (stringcmp(l[k].material, "iris")) return l[k].housing_radius;
  }
  return 0.0f;
}


float lens_get_aperture_pos(const std::vector<lens_element_t> l, const int num, const float zoom) {
  float pos = 0;
  int k = 0;
  while(!stringcmp(l[k].material, "iris") && k < num) {
      pos += lens_get_thickness(l[k], zoom);
      k++;
  }
  return pos;
}


float lens_get_aperture_pos_reverse(const std::vector<lens_element_t> l, const int num, const float zoom) {
  float pos = 0.0;
  for(int i = num; i>0; i--) {
    pos += lens_get_thickness(l[i], zoom);
    if(stringcmp(l[i].material, "iris")) return pos;
  }

  fmt::print("Couldn't find aperture element!");
  return 0.0f;
}


int lens_get_aperture_element(const std::vector<lens_element_t> l, const int lenses_cnt) {
  for (int k = 0; k < lenses_cnt - 1; k++) {
    if (stringcmp(l[k].material, "iris")) return k;
  }

  fmt::print("Couldn't find aperture element!");
  return 0;
}


// read json database
int lens_configuration(std::vector<lens_element_t> &l, const char *id, const int target_focal_length)
{
  l.clear();

  // need to put this in a try except block, it segfaults without any information when LENTIL_PATH is not set...
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  fmt::print("LENTIL_PATH: {}\n", lens_database_path);

  std::string polynomial_optics = "polynomial-optics";
  if (!(lens_database_path.find(polynomial_optics) != std::string::npos)) {
    fmt::print("LENTIL_PATH has not set correctly! Point it to the polynomial-optics folder. \n");
    return -1;
  }

  lens_database_path += "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  int cnt = 0;
  float last_ior = 1.0f;
  float last_vno = 0.0f;
  
  // calculate lens scale
  float scale = 1.0f;
//--> will fail if patent focallength is empty
  if (target_focal_length != 0){ // dirty way of checking if we want to adjust the scale at all (e.g when calculating the raytraced focal length, we don't want to do this)
    if (lens_database[id]["focal-length-mm-raytraced"].empty()){
      scale = target_focal_length / lens_database[id]["focal-length-mm-patent"].get<float>();
    } else {
      scale = target_focal_length / lens_database[id]["focal-length-mm-raytraced"].get<float>();
    }
  }

  std::string optical_elements_switch = "optical-elements-patent";
  if (!lens_database[id]["optical-elements-adjusted"].empty()) {
    optical_elements_switch = "optical-elements-adjusted";
  }
  
  for (const auto& json_lens_element : lens_database[id][optical_elements_switch]) {

      lens_element_t *lens = new lens_element_t;

      lens->lens_radius = scale * json_lens_element["radius"].get<float>();
      lens->housing_radius = scale * json_lens_element["housing-radius"].get<float>();
      
      if (json_lens_element["thickness"].is_array()){
        lens->thickness_short = scale * json_lens_element["thickness"][0].get<float>();
        lens->thickness_mid = scale * json_lens_element["thickness"][1].get<float>();
        lens->thickness_long = scale * json_lens_element["thickness"][2].get<float>();
      } else {
        lens->thickness_short = scale * json_lens_element["thickness"].get<float>();
      }

      lens->material = json_lens_element["material"].get<std::string>();
      if (stringcmp(lens->material, "air")){
        lens->ior = 1.0f;
        lens->vno = 0.0f;
      } else if (stringcmp(lens->material, "iris")){
        lens->ior = last_ior;
        lens->vno = last_vno;
      } else {
        lens->ior = json_lens_element["ior"].get<float>();
        lens->vno = json_lens_element["abbe"].get<float>();
      }
      last_ior = lens->ior;
      last_vno = lens->vno;

      lens->geometry = json_lens_element["lens-geometry"].get<std::string>();

      // aspherical
      if (json_lens_element["aspherical-equation"].is_array()){
        lens->aspheric = 1;
        lens->geometry = "aspherical";
        for(int i = 0; i < 4; i++, i++){
          lens->aspheric_correction_coefficients.push_back(json_lens_element["aspherical-equation"][i].get<float>());
        }
      } else {
        lens->aspheric = 0;
        for(int i = 0; i < 4; i++){
          lens->aspheric_correction_coefficients.push_back(0.0);
        }
      }

      // add lens to lens struct
      cnt++;
      l.push_back(*lens);
  }

  return cnt;
}


// return path to e.g: $LENTIL_PATH/database/lenses/1927-zeiss-biotar/58/
std::string find_lens_id_location(const char *id, const int lens_focal_length){
  std::string json_database_location = fmt::format("{}/database/lenses.json", std::getenv("LENTIL_PATH"));
  std::ifstream in_json(json_database_location);
  json lens_database = json::parse(in_json);

  return fmt::format("{}/database/lenses/{}-{}-{}/{}/", 
                      std::getenv("LENTIL_PATH"),
                      lens_database[id]["year"].get<int>(),
                      (lens_database[id]["company"] == nullptr) ? "unknown" : lens_database[id]["company"].get<std::string>(),
                      lens_database[id]["product-name"].get<std::string>(),
                      lens_focal_length
  );
}


inline void add_to_thickness_last_element(std::vector<lens_element_t> &l, const float sensorshift, const int lenses_cnt, const float thickness_original) {
  l[lenses_cnt-1].thickness_short = thickness_original + sensorshift;
}