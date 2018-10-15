#include "lenssystem.h"
#include "../../fmt/include/fmt/format.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
  const char *id = argv[1];
  int lens_focal_length = atol(argv[2]);

  std::string lens_database_path = fmt::format("{0}/database/lenses.json", std::getenv("LENTIL_PATH"));  
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  // check if focal length already is in list
  for (const auto& i : lens_database[id]["polynomial-optics"]){
    if (i == lens_focal_length){
      fmt::print("Focal length {0} is already present in fitted focal length list.\n", lens_focal_length);
      return 0;
    }
  }

  lens_database[id]["polynomial-optics"].push_back(lens_focal_length);
  
  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
}