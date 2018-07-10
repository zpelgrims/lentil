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
int lens_configuration(lens_element_t *l, const char *filename, int max, const int id)
{
  // read database
//--> write some kind of return false if no file mechanism
  std::ifstream in_json(filename);
  json lens_database = json::parse(in_json);

  int cnt = 0;
  float last_ior = 1.0f;
  float last_vno = 0.0f;
  
  // calculate lens scale
  float scale = 1.0f;
//--> do something with focallength here
  float target_focallength = 100.0;
  if (lens_database[id]["focal-length-mm-raytraced"].empty()){
    scale = target_focallength / lens_database[id]["focal-length-mm-patent"].get<float>();
  } else {
    scale = target_focallength / lens_database[id]["focal-length-mm-raytraced"].get<float>();
  }
  printf("scale: %f \n", scale);
  

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
        if (tmp.length() == 1)
        {
            readch = tmp[0];
        }
        else
        {
            // For most input, char zero is an appropriate sentinel
            readch = '\0';
        }
        return true;
    }
    return false;
}


// convert .fx files to .json
bool lenstable_to_json(lens_element_t *l, const char *filename, const int id)
{
  std::ifstream in_json("/Users/zeno/lentil/polynomial-optics/database/lenses.json");
  json lens_database = json::parse(in_json);

  // check if something already exists on provided lens id
  if (lens_database[std::to_string(id)].empty() == false){
    printf("WATCH OUT: a lens with id %d already exists: \n", id);
    std::cout << std::setw(2) << lens_database[std::to_string(id)] << std::endl;
    char type = '\0';
    while(prompt_for_char("Do you want to overwrite this lens? [y/n]", type))
    {
        if(type != 'y'){
            printf("Conversion cancelled by user \n");
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
  lens_database[std::to_string(id)].clear();

  // fill database with new data
  json lens_data;
  for (int i=0; i<cnt;i++){
    lens_data[id]["optical-elements-patent"][i]["radius"] = l[i].lens_radius;
    if(l[i].thickness_short == l[i].thickness_mid && l[i].thickness_mid == l[i].thickness_long){
      lens_data[id]["optical-elements-patent"][i]["thickness"] = l[i].thickness_short;
    } else {
      std::vector<float> thickness_zoom = {l[i].thickness_short, l[i].thickness_mid, l[i].thickness_long};
      lens_data[id]["optical-elements-patent"][i]["thickness"] = thickness_zoom;
    }
    lens_data[id]["optical-elements-patent"][i]["material"] = l[i].material;
    lens_data[id]["optical-elements-patent"][i]["ior"] = l[i].ior;
    lens_data[id]["optical-elements-patent"][i]["abbe"] = l[i].vno;
    lens_data[id]["optical-elements-patent"][i]["housing_radius"] = l[i].housing_radius;
    
    if(l[i].aspheric == 1){
      lens_data[id]["optical-elements-patent"][i]["lens-geometry"] = "aspherical";
      std::vector<float> aspherical_equation = {};
      for(int j=0;j<4;j++){
        aspherical_equation.push_back(l[i].aspheric_correction_coefficients[j]);
      }
      lens_data[id]["optical-elements-patent"][i]["aspherical-equation"] = aspherical_equation;
    } else if (l[i].anamorphic == 1){
      if (l[i].cylinder_axis_y == true){
        lens_data[id]["optical-elements-patent"][i]["lens-geometry"] = "cyl-y";
      } else {
        lens_data[id]["optical-elements-patent"][i]["lens-geometry"] = "cyl-x";
      }
      lens_data[id]["optical-elements-patent"][i]["aspherical-equation"] = nullptr;
    } else {
      lens_data[id]["optical-elements-patent"][i]["lens-geometry"] = "spherical";
      lens_data[id]["optical-elements-patent"][i]["aspherical-equation"] = nullptr;
    }
  }

  /* add user input:
  some of these need to be defaulted to nullptr, or read from previous state?
    company
    product-name
    year
    patent-number
    patent-location
    implementation-version
    notes
    prime
    focal-lenth-mm-patent
    focal-length-mm-raytraced
    focal-lengths-fitted
    fstop
    polynomial-optics
    polynomial-optics-aperture
  */
    
  lens_database[std::to_string(id)] = lens_data;
  std::ofstream out_json("/Users/zeno/lentil/polynomial-optics/database/lenses.json");
  out_json << std::setw(2) << lens_database << std::endl;

  printf("Lens added to id %d \n", id);
  return true;
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
