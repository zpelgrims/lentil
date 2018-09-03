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

  // early out
  if (lens_database[id]["focal-length-mm-raytraced"].is_null()){
    printf("No raytraced focal length found. Please run \"bin/calculate-focal-length\" first.\n");
    return 0;
  }

  float lens_focal_length_raytraced = lens_database[id]["focal-length-mm-raytraced"].get<float>();
  static lens_element_t lenses[50];

  // loading lens config with 0.0 focal length, which means no scale transform on the lens
  int lenses_cnt = lens_configuration(lenses, id, 0.0f);
  float aperture_radius = lens_get_aperture_radius(lenses, lenses_cnt);
  float fstop = static_cast<float>(lens_focal_length_raytraced)/(aperture_radius*2.0);

  lens_database[id]["fstop"] = fstop;
  printf("Added calculated f-stop of [%f] to lens database.\n", fstop);
  
  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
}
