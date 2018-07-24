#include "lenssystem.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
  const char *id = argv[1];
  
  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  std::string lens_path = std::to_string(lens_database[id]["year"].get<int>());
  lens_path += "-";
  lens_path += lens_database[id]["company"].get<std::string>();
  lens_path += "-";
  lens_path += lens_database[id]["product-name"].get<std::string>();
  
  std::cout << lens_path << std::endl;
}