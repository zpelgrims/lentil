#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>


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
  float aspheric_correction_coefficients[4];
  int aspheric;
  char material[32];
  //std::string geometry;
  char geometry[50];
} lens_element_t;


static inline float lens_get_thickness(const lens_element_t *lens, float zoom)
{
  if(zoom < .5f){
    return lens->thickness_short * (1.0f - 2.0f*zoom) + lens->thickness_mid * 2.0f * zoom;
  }
  else {
    return lens->thickness_mid * (1.0f - 2.0f*(zoom - 0.5f)) + lens->thickness_long * (zoom - 0.5f) * 2.0f;
  }
}


float lens_get_aperture_radius(lens_element_t *l, int num)
{
  for(int k=0;k<num;k++)
  {
    if(!strcasecmp(l[k].material, "iris"))
      return l[k].housing_radius;
  }
  return 0.0f;
}


float lens_get_aperture_pos(lens_element_t *l, int num, float zoom)
{
  float pos = 0;
  int k = 0;
  while(strcasecmp(l[k].material, "iris") && k < num)
  {
      pos += lens_get_thickness(l+k, zoom);
      k++;
  }
  return pos;
}


// read json database
int lens_configuration(lens_element_t *l, const char *id, int target_focal_length)
{
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  std::string polynomial_optics = "polynomial-optics";
  if (!(lens_database_path.find(polynomial_optics) != std::string::npos)) {
    printf("LENTIL_PATH has not set correctly! Point it to the polynomial-optics folder. \n");
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

  for (const auto& json_lens_element : lens_database[id]["optical-elements-patent"]) {

      lens_element_t lens;
      memset(&lens, 0, sizeof(lens_element_t));

      lens.lens_radius = scale * json_lens_element["radius"].get<float>();
      lens.housing_radius = scale * json_lens_element["housing-radius"].get<float>();
      
      if (json_lens_element["thickness"].is_array()){
        lens.thickness_short = scale * json_lens_element["thickness"][0].get<float>();
        lens.thickness_mid = scale * json_lens_element["thickness"][1].get<float>();
        lens.thickness_long = scale * json_lens_element["thickness"][2].get<float>();
      } else {
        lens.thickness_short = scale * json_lens_element["thickness"].get<float>();
      }

      strcpy(lens.material, json_lens_element["material"].get<std::string>().c_str());
      if (strcmp(lens.material, "air") == 0){
        lens.ior = 1.0f;
        lens.vno = 0.0f;
      } else if (strcmp(lens.material, "iris") == 0){
        lens.ior = last_ior;
        lens.vno = last_vno;
      } else {
        lens.ior = json_lens_element["ior"].get<float>();
        lens.vno = json_lens_element["abbe"].get<float>();
      }
      last_ior = lens.ior;
      last_vno = lens.vno;

      // anamorphic
      std::string lens_geometry = json_lens_element["lens-geometry"].get<std::string>();
      if (lens_geometry == "cyl-y"){
        strcpy(lens.geometry, "cyl-y");
      } else if (lens_geometry == "cyl-x"){
        strcpy(lens.geometry, "cyl-x");
      } else {
        strcpy(lens.geometry, "spherical");
      }

      // aspherical
      if (json_lens_element["aspherical-equation"].is_array()){
        lens.aspheric = 1;
        strcpy(lens.geometry, "aspherical");
        for(int i = 0; i < 4; i++, i++){
          lens.aspheric_correction_coefficients[i] = json_lens_element["aspherical-equation"][i].get<float>();
        }
      } else {
        lens.aspheric = 0;
        for(int i = 0; i < 4; i++){
          lens.aspheric_correction_coefficients[i] = 0;
        }
      }

      // add lens to lens struct
      l[cnt++] = lens;
  }

  return cnt;
}


bool prompt_for_char( const char* prompt, char& readch )
{
    std::string tmp;
    std::cout << prompt << std::endl;
    if (std::getline(std::cin, tmp))
    {
        // Only accept single character input
        if (tmp.length() == 1) readch = tmp[0];
        else readch = '\0'; // For most input, char zero is an appropriate sentinel
        return true;
    }
    return false;
}


// return path to e.g: $LENTIL_PATH/database/lenses/1927-zeiss-biotar/58/
std::string find_lens_id_location(const char *id, const int lens_focal_length){
  std::string json_database_location = "";
  json_database_location += std::getenv("LENTIL_PATH");
  json_database_location += "/database/lenses.json";
  std::ifstream in_json(json_database_location);
  json lens_database = json::parse(in_json);

  std::string lens_id_path = "";
  lens_id_path += std::getenv("LENTIL_PATH");
  lens_id_path += "/database/lenses/";
  lens_id_path += std::to_string(lens_database[id]["year"].get<int>());
  lens_id_path += "-";
  if (lens_database[id]["company"] == nullptr) lens_id_path += "unknown";
  else lens_id_path += lens_database[id]["company"].get<std::string>();
  lens_id_path += "-";
  lens_id_path += lens_database[id]["product-name"].get<std::string>();
  lens_id_path += "/";
  lens_id_path += std::to_string(lens_focal_length);
  lens_id_path += "/";

  return lens_id_path;
}


static inline void lens_canonicalize_name(const char *filename, char *out)
{
  const char *start = filename;
  const char *end = filename;
  const char *c = filename;
  for(;*c!=0;c++) if(*c == '/') start = c+1;
  end = c;
  int i=0;
  for(;start != end;start++)
  {
    if(*start == '.') break;
    else if(*start >= 65  && *start <= 90) // caps
    {
      if(i) out[i++] = ' ';
      out[i++] = *start + 32;
    }
    else if(*start >= 48 && *start <= 59) // numbers
      out[i++] = *start;
    else if(*start < 97) // special
      out[i++] = ' ';
    else
      out[i++] = *start;
  }
  out[i++] = 0;
}