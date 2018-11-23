#include <math.h>
#include <string.h>
#include "gencode.h"
#include "raytrace.h"
#include "lenssystem.h"
#include "../../fmt/include/fmt/format.h"

//static lens_element_t lenses[50];
static std::vector<lens_element_t> lenses;
static int lenses_cnt = 0;
static float zoom = 0;

std::string dash_to_underscore(std::string text)
{
    std::replace(text.begin(), text.end(), '-', '_');
    return text;
}

int main(int argc, char **argv)
{
  FILE *f = 0;

  const char *id = argv[1];
  int lens_focal_length = atol(argv[2]);

  std::string lens_id_path = find_lens_id_location(id, lens_focal_length);
  std::string fitfile_path = lens_id_path + "fitted/exitpupil.fit";
  std::string ap_fitfile_path = lens_id_path + "fitted/aperture.fit";
  std::string pt_evaluate_h_path = lens_id_path + "code/pt_evaluate.h";
  std::string pt_evaluate_jacobian_h_path = lens_id_path + "code/pt_evaluate_jacobian.h";
  std::string pt_evaluate_aperture_h_path = lens_id_path + "code/pt_evaluate_aperture.h";
  std::string pt_evaluate_aperture_jacobian_h_path = lens_id_path + "code/pt_evaluate_aperture_jacobian.h";
  std::string pt_sample_aperture_h_path = lens_id_path + "code/pt_sample_aperture.h";
  std::string lt_sample_aperture_h_path = lens_id_path + "code/lt_sample_aperture.h";
  std::string lens_constants_path = lens_id_path + "code/lens_constants.h";
  fmt::print("Generating code from fitted files: \n");
  fmt::print("\t fitfile location: {}\n", fitfile_path);
  fmt::print("\t aperture fitfile location: {}\n", ap_fitfile_path);
  fmt::print("\t pt_evaluate.h location: {}\n", pt_evaluate_h_path);
  fmt::print("\t pt_evaluate_jacobian.h location: {}\n", pt_evaluate_jacobian_h_path);
  fmt::print("\t pt_evaluate_aperture.h location: {}\n", pt_evaluate_aperture_h_path);
  fmt::print("\t pt_evaluate_aperture_jacobian.h location: {}\n", pt_evaluate_aperture_jacobian_h_path);
  fmt::print("\t pt_sample_aperture.h location: {}\n", pt_sample_aperture_h_path);
  fmt::print("\t lt_sample_aperture.h location: {}\n", lt_sample_aperture_h_path);
  fmt::print("\t init.h location: {}\n", lens_constants_path);

  std::string json_database_location = fmt::format("{}/database/lenses.json", std::getenv("LENTIL_PATH"));
  std::ifstream in_json(json_database_location);
  json lens_database = json::parse(in_json);

  std::string case_lens_name = fmt::format("{}_{}_{}_{}mm", lens_database[id]["company"].get<std::string>(),
                                                            dash_to_underscore(lens_database[id]["product-name"].get<std::string>()),
                                                            lens_database[id]["year"].get<int>(),
                                                            lens_focal_length
  );

  poly_system_t poly, poly_ap;
  if(poly_system_read(&poly, fitfile_path.c_str()) || poly_system_read(&poly_ap, ap_fitfile_path.c_str()))
  {
    fprintf(stderr, "[gencode] could not read poly fits for lens ID `%s'!\n", id);
    exit(1);
  }

  const char *varnames_in[poly_num_vars] =  { "x", "y", "dx", "dy", "lambda" };
  const char *varnames_out[poly_num_vars] = { "x", "y", "dx", "dy", "transmittance" };



  f = fopen(pt_evaluate_h_path.c_str(), "wb");
  print_poly_system_code(f, &poly, varnames_in, varnames_out, case_lens_name.c_str());
  fclose(f);

  f = fopen(pt_evaluate_jacobian_h_path.c_str(), "wb");
  print_jacobian(f, &poly, varnames_in, case_lens_name.c_str());
  fclose(f);

  f = fopen(pt_evaluate_aperture_h_path.c_str(), "wb");
  print_poly_system_code(f, &poly_ap, varnames_in, varnames_out, case_lens_name.c_str());
  fclose(f);

  f = fopen(pt_evaluate_aperture_jacobian_h_path.c_str(), "wb");
  print_jacobian(f, &poly_ap, varnames_in, case_lens_name.c_str());
  fclose(f);

  f = fopen(pt_sample_aperture_h_path.c_str(), "wb");
  print_pt_sample_aperture(f, &poly_ap, varnames_in, varnames_out, case_lens_name.c_str());
  fclose(f);

  f = fopen(lt_sample_aperture_h_path.c_str(), "wb");
  print_lt_sample_aperture(f, &poly, &poly_ap, varnames_in, varnames_out, case_lens_name.c_str());
  fclose(f);


  lenses_cnt = lens_configuration(lenses, id, lens_focal_length);
  float lens_length = 0;
  for(int i = 0; i < lenses_cnt; i++) lens_length += lens_get_thickness(lenses[i], zoom);
  const float aperture_housing_radius = lens_get_aperture_radius(lenses, lenses_cnt);
  const float aperture_pos = lens_get_aperture_pos(lenses, lenses_cnt, zoom);
  const float bfl = lens_get_thickness(lenses[lenses_cnt-1], zoom);

  // construct lens name
  std::string lens_name = lens_database[id]["company"].get<std::string>();
  lens_name += "-";
  lens_name += lens_database[id]["product-name"].get<std::string>();
  lens_name += "-";
  lens_name += std::to_string(lens_database[id]["year"].get<int>());
  lens_name += "-";
  lens_name += std::to_string(lens_focal_length);
  

  f = fopen(lens_constants_path.c_str(), "wb");
  fprintf(f, "case %s:\n{\n", case_lens_name.c_str());
  fprintf(f, "camera->lens_name = \"%smm\"; // descriptive name of the lens\n", lens_name.c_str());
  fprintf(f, "camera->lens_outer_pupil_radius = %f; // scene facing radius in mm\n", lenses[0].housing_radius);
  fprintf(f, "camera->lens_inner_pupil_radius = %f; // sensor facing radius in mm\n", lenses[lenses_cnt-1].housing_radius);
  fprintf(f, "camera->lens_inner_pupil_curvature_radius = %f; // radius of curvature of the inner pupil\n", lenses[lenses_cnt-1].lens_radius);
  fprintf(f, "camera->lens_outer_pupil_curvature_radius = %f; // radius of curvature of the outer pupil\n", lenses[0].lens_radius);
  fprintf(f, "camera->lens_length = %f; // overall lens length in mm\n", lens_length);
  fprintf(f, "camera->lens_back_focal_length = %f; // approximate lens back focal length in mm\n", bfl);
  fprintf(f, "camera->lens_effective_focal_length = %f; // effective focal length in mm\n", static_cast<float>(lens_focal_length));
  fprintf(f, "camera->lens_aperture_pos = %f; // distance aperture -> outer pupil in mm\n", aperture_pos);
  fprintf(f, "camera->lens_aperture_housing_radius = %f; // lens housing radius at the aperture\n", aperture_housing_radius);
  fprintf(f, "camera->lens_outer_pupil_geometry = \"%s\"; // geometry of outer pupil\n", lenses[0].geometry.c_str());
  fprintf(f, "camera->lens_inner_pupil_geometry = \"%s\"; // geometry of inner pupil\n", lenses[lenses_cnt-1].geometry.c_str());
  fprintf(f, "camera->lens_fstop = %f; // effective_focal_length/(2*aperture_housing_radius)\n", lens_database[id]["fstop"].get<float>());
  fprintf(f, "camera->lens_aperture_radius_at_fstop = %f; // aperture radius at smallest fstop\n", lens_database[id]["max-fstop-aperture-radius"].get<float>());

  // calculate approximate fov for 35mm sensor
  float sensor[] = {22.f, 0, (lenses[lenses_cnt-1].housing_radius-22.f)/bfl, 0, .55};
  float out[] = {0, 0, 0, 0, 0};
  poly_system_evaluate(&poly, sensor, out, 100);
 
  const std::vector<float> inpos = {out[0], out[1]};
  const std::vector<float> indir = {out[2], out[3]};
  std::vector<float> wspos(3);
  std::vector<float> wsdir(3);

  if (stringcmp(lenses[0].geometry, "cyl-y")) cylinderToCs(inpos, indir, wspos, wsdir, 0, lenses[0].lens_radius, true);
  else if (stringcmp(lenses[0].geometry, "cyl-x")) cylinderToCs(inpos, indir, wspos, wsdir, 0, lenses[0].lens_radius, false);
  else sphereToCs(inpos, indir, wspos, wsdir, 0, lenses[0].lens_radius);
  
  raytrace_normalise(wsdir);
  wsdir[2] = wsdir[2]<-1?-1:wsdir[2]>1?1:wsdir[2];
  float fov = wsdir[2];
  fprintf(f, "camera->lens_field_of_view = %f; // cosine of the approximate field of view assuming a 35mm image\n", fov);
  fprintf(f, "} break;\n");
  fclose(f);

  exit(0);
}
