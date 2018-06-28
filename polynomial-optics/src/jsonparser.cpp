#include "../ext/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main(){

	// read database
	std::ifstream in_json("/Users/zeno/lentil/database/lenses.json");
	json j = json::parse(in_json);

	// also works
	// auto focal_length = j["01"]["optical-elements-patent"]["radius-x"].get<float>();
	// std::cout << focal_length << std::endl;
	
	for (const auto& lens : j["01"]["optical-elements-patent"]) {
	    auto ior = lens["ior"];
	    std::cout << ior << std::endl;
	}

}