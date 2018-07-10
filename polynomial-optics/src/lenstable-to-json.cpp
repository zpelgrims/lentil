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
    int id = 0;

    if(argc > 2){
        strncpy(lensfilename, argv[1], 512);
        id = atol(argv[2]);
    } else {
        printf("Too few arguments provided \n");
    }

    lens_canonicalize_name(lensfilename, lens_name);
    lenstable_to_json(lenses, lensfilename, id);
}