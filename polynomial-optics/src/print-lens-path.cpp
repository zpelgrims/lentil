#include "lenssystem.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;

#include "../../fmt/include/fmt/format.h"

int main(int argc, char *argv[])
{
  const char *id = argv[1];
  
  std::string lens_database_path = fmt::format("{}/database/lenses.json", std::getenv("LENTIL_PATH"));
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  std::string lens_path = fmt::format("{}-{}-{}", lens_database[id]["year"].get<int>(), 
                                                  lens_database[id]["company"].get<std::string>(), 
                                                  lens_database[id]["product-name"].get<std::string>()
  );

  fmt::print("{}", lens_path);
}