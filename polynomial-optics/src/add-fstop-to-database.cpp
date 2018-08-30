#include "lenssystem.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
    
  const char *id = argv[1];
  int lens_focal_length = atol(argv[2]);
    
  static lens_element_t lenses[50];
  
  int lenses_cnt = lens_configuration(lenses, id, lens_focal_length);

  float aperture_radius = lens_get_aperture_radius(lenses, lenses_cnt);
  float fstop = static_cast<float>(lens_focal_length)/(aperture_radius*2.0);
    
    

  std::string lens_database_path = std::getenv("LENTIL_PATH");
  lens_database_path += "/database/lenses.json";
  std::ifstream in_json(lens_database_path);
  json lens_database = json::parse(in_json);

  lens_database[id]["fstop"] = fstop;
  printf("Added calculated f-stop of [%f] to lens database.", fstop);
  
  std::ofstream out_json(lens_database_path);
  out_json << std::setw(2) << lens_database << std::endl;
}
