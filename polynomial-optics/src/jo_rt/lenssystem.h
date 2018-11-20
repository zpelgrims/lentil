#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct lens_element_t
{
  float lens_radius, thickness_short, thickness_mid, thickness_long, ior, vno, housing_radius;
  float aspheric_correction_coefficients[4];
  int aspheric;
  int anamorphic;
  char material[32];
}
lens_element_t;

typedef struct lens_t
{
  lens_element_t element[50];
  uint32_t num;                  // number of lens elements
  char name[50];                 // descriptive name
  float length;                  // length in mm, for shortest zoom
  float aperture_pos;            // aperture pos, for shortest zoom
  float focal_length;            // approximate back focal length in mm
  uint32_t aperture_element;     // index of aperture element (name "iris" or similar)
  float aperture_housing_radius; // lens housing radius at the aperture
  float outer_radius;            // curvature radius of last scene facing element
  float field_of_view;           // cosine of the approximate field of view assuming a 35mm sensor image
  float zoom;                    // 0: short, 1: long if the lens design supports it
}
lens_t;

static inline void lens_canonicalize_name(const char *filename, char *out)
{
  const char *start = filename;
  const char *end = filename;
  const char *c = filename;
  for(;*c!=0;c++) if(*c == '/') start = c+1;
  end = c;
  int i=0;
  for(;start != end;start++)
  {
    if(*start == '.') break;
    else if(*start >= 65  && *start <= 90) // caps
    {
      if(i) out[i++] = ' ';
      out[i++] = *start + 32;
    }
    else if(*start >= 48 && *start <= 59) // numbers
      out[i++] = *start;
    else if(*start < 97) // special
      out[i++] = ' ';
    else
      out[i++] = *start;
  }
  out[i++] = 0;
}

static inline float lens_get_thickness(const lens_element_t *lens, float zoom)
{
  if(zoom < .5f) return lens->thickness_short*(1.0f-2.0f*zoom) + lens->thickness_mid*2.0f*zoom;
  else           return lens->thickness_mid*(1.0f-2.0f*(zoom-.5f)) + lens->thickness_long*(zoom-.5f)*2.0f;
}

static inline float lens_get_length(const lens_t *lens)
{
  float pos = 0;
  for(int k=0;k<lens->num;k++)
    pos += lens_get_thickness(lens->element+k, lens->zoom);
  return pos;
}

static inline float lens_get_aperture_pos(const lens_t *lens)
{
  float pos = 0;
  for(int k=0;k<MIN(lens->num, lens->aperture_element);k++)
    pos += lens_get_thickness(lens->element+k, lens->zoom);
  return pos;
}

// initialise the lens struct
static inline int lens_read(lens_t *lens, const char *filename)
{
  memset(lens, 0, sizeof(lens_t));
  const int max = sizeof(lens->element)/sizeof(lens_element_t);
  lens_element_t *l = lens->element;
  FILE *f = fopen(filename, "rb");
  if(!f) return 1;
  int cnt = 0;

  float last_ior = 1.0f;
  float last_vno = 0.0f;
  float scale = 1.0f;
  float length = 0;
  lens->zoom = 0;
  while(1)
  {
    lens_element_t lem;
    memset(&lem, 0, sizeof(lens_element_t));
    char line[2048];
    if(fscanf(f, "%[^\n]", line) == EOF) break;
    if(fgetc(f) == EOF) break; // new line

    char *in = line;

    if(!strncmp(line, "#!scale", 7))
    {
      scale = atof(line + 8);
      continue;
    }
    // munch comment
    if(!strncmp(line, "//", 2) || !strncmp(line, "#", 1)) continue;
    while(in[0] == '\t' || in[0] == ' ') in++;
    lem.lens_radius = scale * strtof(in, &in);
    if(lem.lens_radius == 0.0f) return 2;
    while(in[0] == '\t' || in[0] == ' ') in++;
    lem.thickness_short = scale * strtof(in, &in);
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lem.thickness_mid = scale * strtof(in+1, &in);
    else
      lem.thickness_mid = lem.thickness_short;
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lem.thickness_long = scale * strtof(in+1, &in);
    else
      lem.thickness_long = lem.thickness_short;
    if(lem.thickness_short == 0.0f) return 3;
    if(lem.thickness_mid   == 0.0f) return 4;
    if(lem.thickness_long  == 0.0f) return 5;

    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "cx_", 3))
    {
      lem.anamorphic = 1;
      in += 3;
    }
    int i=0;
    while(in[0] != '\t' && in[0] != ' ' && in[0] != '\0') lem.material[i++] = in++[0];
    lem.material[i] = '\0';
    if(!strcasecmp(lem.material, "air"))
    {
      lem.ior = 1.0f;
      lem.vno = 0.0f;
    }
    else if(!strcasecmp(lem.material, "iris"))
    {
      lem.ior = last_ior;
      lem.vno = last_vno;
      lens->aperture_element = cnt;
      lens->aperture_pos = length;
    }
    else
    {
      while(in[0] == '\t' || in[0] == ' ') in++;
      lem.ior = strtof(in, &in);
      while(in[0] == '\t' || in[0] == ' ') in++;
      lem.vno = strtof(in, &in);
    }

    length += lem.thickness_short;

    last_ior = lem.ior;
    last_vno = lem.vno;
    if(lem.ior == 0.0f) return 6;

    while(in[0] == '\t' || in[0] == ' ') in++;
    lem.housing_radius = scale * strtof(in, &in);
    if(lem.housing_radius == 0.0f) return 7;
    if(cnt == lens->aperture_element)
      lens->aperture_housing_radius = lem.housing_radius;
    
    lem.aspheric = 0;
    for(int i = 0; i < 4; i++)
      lem.aspheric_correction_coefficients[i] = 0;
    
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "#!aspheric=", 11))
    {
      in += 11;
      lem.aspheric = strtol(in, &in, 10);
      // munch comma
      in++;
      for(int i = 0; i < 4; i++, in++)
        lem.aspheric_correction_coefficients[i] = strtof(in, &in);
    }

    l[cnt++] = lem;

    if(cnt >= max) return 8;
  }
  fclose(f);

  lens->num = cnt;
  lens->length = length;
  // approximate back focal length
  lens->focal_length = lens_get_thickness(lens->element+lens->num-1, lens->zoom);

  lens_canonicalize_name(filename, lens->name);
  return 0;
}
