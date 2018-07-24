#include "lenssystem.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
  const char *id = argv[1];
  int lens_focal_length = atol(argv[2]);
  
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  lens_database[id]["polynomial-optics"].push_back(lens_focal_length);

  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
}