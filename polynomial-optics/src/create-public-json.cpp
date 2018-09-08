#include "lenssystem.h"
#include <string>

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
  const char *id = argv[1];

  std::string lentil_path = std::getenv("LENTIL_PATH");
  std::string lens_public_database_path = lentil_path + "/../www/json/lenses_public.json";
  std::string lens_database_path = lentil_path + "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  for(auto& element : lens_database)
  {
    if (element.find("optical-elements-adjusted") != element.end()) {
      element.erase("optical-elements-adjusted");
    }
    element.erase("optical-elements-patent");
    element.erase("patent-location");
  }
  
  std::ofstream out_json(lens_public_database_path);
  out_json << std::setw(2) << lens_database << std::endl;

  printf("Written public lens database to location: %s\n", lens_public_database_path.c_str());
}
