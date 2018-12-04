#include "lenssystem.h"
#include <string>
#include <iomanip>
#include "../../fmt/include/fmt/format.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


std::string construct_lens_image_www_location(std::string key, json element) {
  std::string lens_image_www_location = fmt::format("/imgs/lenses/{}/{}-{}-{}.svg", key, element["year"].get<int>(), element["company"].get<std::string>(), element["product-name"].get<std::string>());
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
    element.erase("focal-length-mm-raytraced");
    element.erase("focal-length-mm-patent");
    
    element.emplace("www-svg-location", construct_lens_image_www_location(it.key(), it.value()));
  }

  for (auto key : to_erase) {
    lens_database.erase(key);
  }
  
  std::ofstream out_json(lens_public_database_path);
  out_json << std::setw(2) << lens_database << std::endl;

  fmt::format("Written public lens database to location: {}\n", lens_public_database_path.c_str());
}


int main(int argc, char *argv[])
{
  
  std::string lentil_path = std::getenv("LENTIL_PATH");
  std::string lens_public_database_path = fmt::format("{}/../www/json/lenses_public.json", lentil_path);
  std::string lens_database_path = fmt::format("{}/database/lenses.json", lentil_path);
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  create_public_json(lens_database, lens_public_database_path);
}
