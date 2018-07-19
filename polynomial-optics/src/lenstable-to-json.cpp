#include "lenssystem.h"

//json parsing
#include "../ext/json.hpp"
#include <fstream>
using json = nlohmann::json;


int main(int argc, char *argv[])
{
    lens_element_t lenses[50];
    char lensfilename[512] = "";
    char lens_name[512];

    strncpy(lensfilename, argv[1], 512);
    const char *id = argv[2];

    lens_canonicalize_name(lensfilename, lens_name);
    lenstable_to_json(lenses, lensfilename, id);
}