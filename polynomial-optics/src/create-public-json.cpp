#include "lenssystem.h"
#include <string>

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


std::string construct_lens_image_www_location(std::string key, json element) {
  std::string lens_image_www_location = "/www/public/imgs/lenses/";
  lens_image_www_location += key;
  lens_image_www_location += "/";
  lens_image_www_location += std::to_string(element["year"].get<int>());
  lens_image_www_location += "-";
  lens_image_www_location += element["company"].get<std::string>();
  lens_image_www_location += "-";
  lens_image_www_location += element["product-name"].get<std::string>();
  lens_image_www_location += ".svg";

  return lens_image_www_location;
}

void create_public_json(json lens_database, std::string lens_public_database_path) {
  std::vector<std::string> to_erase = {};

  for (auto it = lens_database.begin(); it != lens_database.end(); ++it) {
    
    auto &element = it.value();

    if (element["production-ready"].get<bool>() == false) {
      to_erase.push_back(it.key());
      continue;
    }

    if (element.find("optical-elements-adjusted") != element.end()) {
      element.erase("optical-elements-adjusted");
    }
    element.erase("optical-elements-patent");
    element.erase("patent-location");
    element.erase("focal-length-mm-raytraced");
    element.erase("focal-length-mm-patent");
    
    element.emplace("www-svg-location", construct_lens_image_www_location(it.key(), it.value()));
  }

  for (auto key : to_erase) {
    lens_database.erase(key);
  }
  
  std::ofstream out_json(lens_public_database_path);
  out_json << std::setw(2) << lens_database << std::endl;

  printf("Written public lens database to location: %s\n", lens_public_database_path.c_str());
}


int main(int argc, char *argv[])
{
  
  std::string lentil_path = std::getenv("LENTIL_PATH");
  std::string lens_public_database_path = lentil_path + "/../www/json/lenses_public.json";
  std::string lens_database_path = lentil_path + "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  create_public_json(lens_database, lens_public_database_path);
}
