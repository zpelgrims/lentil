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
  float lens_radius_original;
  float thickness_short;
  float thickness_mid;
  float thickness_long;
  float ior;
  float vno;
  float housing_radius;
  float aspheric_correction_coefficients[4];
  int aspheric;
  int anamorphic;
  bool cylinder_axis_y;
  char material[32];
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

// reading .fx lens description files
int lens_configuration_fx(lens_element_t *l, const char *filename, int max)
{
  FILE *f = fopen(filename, "rb");
  if(!f) return 0;
  int cnt = 0;

  float last_ior = 1.0f;
  float last_vno = 0.0f;
  float scale = 1.0f;
  while(1)
  {
    lens_element_t lens;
    memset(&lens, 0, sizeof(lens_element_t));
    char line[2048];
    if(fscanf(f, "%[^\n]", line) == EOF) break;
    if(fgetc(f) == EOF) break; // new line

    char *in = line;

    if(!strncmp(line, "#!scale", 7))
    {
      scale = atof(line + 8);
      continue;
    }
    // munch comment
    if(!strncmp(line, "//", 2) || !strncmp(line, "#", 1)) continue;
    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.lens_radius = scale * strtof(in, &in);
    if(lens.lens_radius == 0.0f) break;
    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.thickness_short = scale * strtof(in, &in);
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lens.thickness_mid = scale * strtof(in+1, &in);
    else
      lens.thickness_mid = lens.thickness_short;
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lens.thickness_long = scale * strtof(in+1, &in);
    else
      lens.thickness_long = lens.thickness_short;
    if(lens.thickness_short == 0.0f) break;
    if(lens.thickness_mid   == 0.0f) break;
    if(lens.thickness_long  == 0.0f) break;

    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "cx_", 3))
    {
      lens.anamorphic = 1;
      in += 3;
    }
    int i=0;
    while(in[0] != '\t' && in[0] != ' ' && in[0] != '\0') lens.material[i++] = in++[0];
    lens.material[i] = '\0';
    if(!strcasecmp(lens.material, "air"))
    {
      lens.ior = 1.0f;
      lens.vno = 0.0f;
    }
    else if(!strcasecmp(lens.material, "iris"))
    {
      lens.ior = last_ior;
      lens.vno = last_vno;
    }
    else
    {
      while(in[0] == '\t' || in[0] == ' ') in++;
      lens.ior = strtof(in, &in);
      while(in[0] == '\t' || in[0] == ' ') in++;
      lens.vno = strtof(in, &in);
    }
    last_ior = lens.ior;
    last_vno = lens.vno;
    if(lens.ior == 0.0f) break;

    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.housing_radius = scale * strtof(in, &in);
    if(lens.housing_radius == 0.0f) break;
    
    lens.aspheric = 0;
    for(int i = 0; i < 4; i++)
      lens.aspheric_correction_coefficients[i] = 0;
    
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "#!aspheric=", 11))
    {
      in += 11;
      lens.aspheric = strtol(in, &in, 10);
      // munch comma
      in++;
      for(int i = 0; i < 4; i++, in++)
        lens.aspheric_correction_coefficients[i] = strtof(in, &in);
    }

    l[cnt++] = lens;

    if(cnt >= max) break;
  }
  fclose(f);
  return cnt;
}


// read json database
int lens_configuration(lens_element_t *l, const char *id, int target_focal_length)
{
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  int cnt = 0;
  float last_ior = 1.0f;
  float last_vno = 0.0f;
  
  // calculate lens scale
  float scale = 1.0f;
//--> will fail if patent focallength is empty
  if (lens_database[id]["focal-length-mm-raytraced"].empty()){
    scale = target_focal_length / lens_database[id]["focal-length-mm-patent"].get<float>();
  } else {
    scale = target_focal_length / lens_database[id]["focal-length-mm-raytraced"].get<float>();
  }
  
  
  for (const auto& json_lens_element : lens_database[id]["optical-elements-patent"]) {

      lens_element_t lens;
      memset(&lens, 0, sizeof(lens_element_t));

      lens.lens_radius = scale * json_lens_element["radius"].get<float>();
      lens.lens_radius_original = scale * json_lens_element["radius"].get<float>();     
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
      auto lens_geometry = json_lens_element["lens-geometry"];
      if (lens_geometry == "cyl-y"){
        lens.anamorphic = 1;
        lens.cylinder_axis_y = true;
      } else if (lens_geometry == "cyl-x"){
        lens.anamorphic = 1;
        lens.cylinder_axis_y = false;
      } else {
        lens.anamorphic = 0;
      }

      // aspherical
      if (json_lens_element["aspherical-equation"].is_array()){
        lens.aspheric = 1;
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


// convert .fx files to .json
// WATCH OUT: DO NOT UPDATE LENSES WITH THIS, AS ALL DATA GETS DELETED AND RE-WRITTEN CURRENTLY
// need to implement reading previous attributes, this is just meant for initial lens conversion now
bool lenstable_to_json(lens_element_t *l, const char *filename, const char *id)
{
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  // check if something already exists on provided lens id
  if (lens_database[id].empty() == false){
    printf("WATCH OUT: a lens with id %s already exists: \n", id);
    std::cout << std::setw(2) << lens_database[id] << std::endl;
    char type = '\0';
    while(prompt_for_char("Do you want to overwrite this lens? [y/n]", type))
    {
        if(type != 'y'){
            printf("Conversion cancelled.\n");
            return false;
        }
    }
  }

  // read .fx file and store data in struct
  FILE *f = fopen(filename, "rb");
  if(!f) return false;
  int cnt = 0;
  float last_ior = 1.0f;
  float last_vno = 0.0f;
  float scale = 1.0f;
  while(1)
  {
    lens_element_t lens;
    memset(&lens, 0, sizeof(lens_element_t));
    char line[2048];
    if(fscanf(f, "%[^\n]", line) == EOF) break;
    if(fgetc(f) == EOF) break; // new line

    char *in = line;

    if(!strncmp(line, "#!scale", 7))
    {
      scale = atof(line + 8);
      continue;
    }
    // munch comment
    if(!strncmp(line, "//", 2) || !strncmp(line, "#", 1)) continue;
    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.lens_radius = strtof(in, &in);
    if(lens.lens_radius == 0.0f) break;
    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.thickness_short = strtof(in, &in);
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lens.thickness_mid = strtof(in+1, &in);
    else
      lens.thickness_mid = lens.thickness_short;
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lens.thickness_long = strtof(in+1, &in);
    else
      lens.thickness_long = lens.thickness_short;
    if(lens.thickness_short == 0.0f) break;
    if(lens.thickness_mid   == 0.0f) break;
    if(lens.thickness_long  == 0.0f) break;

    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "cx_", 3))
    {
      lens.anamorphic = 1;
      in += 3;
    }
    int i=0;
    while(in[0] != '\t' && in[0] != ' ' && in[0] != '\0') lens.material[i++] = in++[0];
    lens.material[i] = '\0';
    if(!strcasecmp(lens.material, "air"))
    {
      lens.ior = 1.0f;
      lens.vno = 0.0f;
    }
    else if(!strcasecmp(lens.material, "iris"))
    {
      lens.ior = last_ior;
      lens.vno = last_vno;
    }
    else
    {
      while(in[0] == '\t' || in[0] == ' ') in++;
      lens.ior = strtof(in, &in);
      while(in[0] == '\t' || in[0] == ' ') in++;
      lens.vno = strtof(in, &in);
    }
    last_ior = lens.ior;
    last_vno = lens.vno;
    if(lens.ior == 0.0f) break;

    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.housing_radius = strtof(in, &in);
    if(lens.housing_radius == 0.0f) break;
    
    lens.aspheric = 0;
    for(int i = 0; i < 4; i++)
      lens.aspheric_correction_coefficients[i] = 0;
    
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "#!aspheric=", 11))
    {
      in += 11;
      lens.aspheric = strtol(in, &in, 10);
      // munch comma
      in++;
      for(int i = 0; i < 4; i++, in++)
        lens.aspheric_correction_coefficients[i] = strtof(in, &in);
    }

    l[cnt++] = lens;
  }
  fclose(f);
  

  // delete all old data in lens database
  lens_database[id].clear();

  // fill database with new data
  json lens_data;
  for (int i=0; i<cnt;i++){
    lens_data["optical-elements-patent"][i]["radius"] = l[i].lens_radius;
    if(l[i].thickness_short == l[i].thickness_mid && l[i].thickness_mid == l[i].thickness_long){
      lens_data["optical-elements-patent"][i]["thickness"] = l[i].thickness_short;
    } else {
      std::vector<float> thickness_zoom = {l[i].thickness_short, l[i].thickness_mid, l[i].thickness_long};
      lens_data["optical-elements-patent"][i]["thickness"] = thickness_zoom;
    }
    lens_data["optical-elements-patent"][i]["material"] = l[i].material;
    lens_data["optical-elements-patent"][i]["ior"] = l[i].ior;
    lens_data["optical-elements-patent"][i]["abbe"] = l[i].vno;
    lens_data["optical-elements-patent"][i]["housing_radius"] = l[i].housing_radius;
    
    if(l[i].aspheric == 1){
      lens_data["optical-elements-patent"][i]["lens-geometry"] = "aspherical";
      std::vector<float> aspherical_equation = {};
      for(int j=0;j<4;j++){
        aspherical_equation.push_back(l[i].aspheric_correction_coefficients[j]);
      }
      lens_data["optical-elements-patent"][i]["aspherical-equation"] = aspherical_equation;
    } else if (l[i].anamorphic == 1){
      if (l[i].cylinder_axis_y == true){
        lens_data["optical-elements-patent"][i]["lens-geometry"] = "cyl-y";
      } else {
        lens_data["optical-elements-patent"][i]["lens-geometry"] = "cyl-x";
      }
      lens_data["optical-elements-patent"][i]["aspherical-equation"] = nullptr;
    } else {
      lens_data["optical-elements-patent"][i]["lens-geometry"] = "spherical";
      lens_data["optical-elements-patent"][i]["aspherical-equation"] = nullptr;
    }
  }

  // various other required user-input
  std::setprecision(5);
  printf("Company name?\n");
  std::cin >> lens_data["company"];
  if (lens_data["company"] == 0) lens_data["company"] = nullptr;

  printf("Product name?\n");
  std::cin >> lens_data["product-name"];
  if (lens_data["product-name"] == 0) lens_data["product-name"] = nullptr;

  printf("Patent year?\n");
  std::cin >> lens_data["year"];
  if (lens_data["year"] == 0) lens_data["year"] = nullptr;

  printf("Patent number?\n");
  std::cin >> lens_data["patent-number"];
  if (lens_data["patent-number"] == 0) lens_data["patent-number"] = nullptr;

  printf("Patent location?\n");
  std::cin >> lens_data["patent-location"];
  if (lens_data["patent-location"] == 0) lens_data["patent-location"] = nullptr;

  printf("Notes?\n");
  std::cin >> lens_data["notes"];
  if (lens_data["notes"] == 0) lens_data["notes"] = nullptr;

  printf("Prime?\n");
  std::cin >> lens_data["prime"];
  if (lens_data["prime"] == "") lens_data["prime"] = nullptr;
  else if (lens_data["prime"] == 1 || lens_data["prime"] == "y") lens_data["prime"] = true;
  else if (lens_data["prime"] == 0 || lens_data["prime"] == "n") lens_data["prime"] = false;

  printf("Focal length from patent in mm?\n");
  std::cin >> lens_data["focal-length-mm-patent"];
  if (lens_data["focal-length-mm-patent"] == 0) lens_data["focal-length-mm-patent"] = nullptr;
  

// TODO: THESE NEED TO CHANGE TO A LIST OF FITTED FOCAL LENGTHS
  lens_data["polynomial-optics"] = {};
  lens_data["polynomial-optics-aperture"] = {};

  // implementation version NULL
  lens_data["implementation-version"] = nullptr;
  // raytraced focal length NULL
  lens_data["focal-length-mm-raytraced"] = nullptr;
  // fstop NULL
  lens_data["fstop"] = nullptr;

    
  lens_database[id] = lens_data;
  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;

  printf("Lens added to id %s \n", id);
  return true;
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