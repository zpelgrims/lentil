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

static inline float lens_get_thickness(const lens_element_t *lens, float zoom)
{
  if(zoom < .5f) return lens->thickness_short*(1.0f-2.0f*zoom) + lens->thickness_mid*2.0f*zoom;
  else           return lens->thickness_mid*(1.0f-2.0f*(zoom-.5f)) + lens->thickness_long*(zoom-.5f)*2.0f;
}

float lens_get_aperture_radius(lens_element_t *l, int num)
{
  for(int k=0;k<num;k++)
  {
    if(!strcasecmp(l[k].material, "iris"))
      return l[k].housing_radius;
  }
  return 0.0f;
}

float lens_get_aperture_pos(lens_element_t *l, int num, float zoom)
{
  float pos = 0;
  int k = 0;
  while(strcasecmp(l[k].material, "iris") && k < num)
  {
      pos += lens_get_thickness(l+k, zoom);
      k++;
  }
  return pos;
}

int lens_configuration(lens_element_t *l, const char *filename, int max)
{
  FILE *f = fopen(filename, "rb");
  if(!f) return 0;
  int cnt = 0;

  float last_ior = 1.0f;
  float last_vno = 0.0f;
  float scale = 1.0f;
  while(1)
  {
    lens_element_t lens;
    memset(&lens, 0, sizeof(lens_element_t));
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
    lens.lens_radius = scale * strtof(in, &in);
    if(lens.lens_radius == 0.0f) break;
    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.thickness_short = scale * strtof(in, &in);
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lens.thickness_mid = scale * strtof(in+1, &in);
    else
      lens.thickness_mid = lens.thickness_short;
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '/')
      lens.thickness_long = scale * strtof(in+1, &in);
    else
      lens.thickness_long = lens.thickness_short;
    if(lens.thickness_short == 0.0f) break;
    if(lens.thickness_mid   == 0.0f) break;
    if(lens.thickness_long  == 0.0f) break;

    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "cx_", 3))
    {
      lens.anamorphic = 1;
      in += 3;
    }
    int i=0;
    while(in[0] != '\t' && in[0] != ' ' && in[0] != '\0') lens.material[i++] = in++[0];
    lens.material[i] = '\0';
    if(!strcasecmp(lens.material, "air"))
    {
      lens.ior = 1.0f;
      lens.vno = 0.0f;
    }
    else if(!strcasecmp(lens.material, "iris"))
    {
      lens.ior = last_ior;
      lens.vno = last_vno;
    }
    else
    {
      while(in[0] == '\t' || in[0] == ' ') in++;
      lens.ior = strtof(in, &in);
      while(in[0] == '\t' || in[0] == ' ') in++;
      lens.vno = strtof(in, &in);
    }
    last_ior = lens.ior;
    last_vno = lens.vno;
    if(lens.ior == 0.0f) break;

    while(in[0] == '\t' || in[0] == ' ') in++;
    lens.housing_radius = scale * strtof(in, &in);
    if(lens.housing_radius == 0.0f) break;
    
    lens.aspheric = 0;
    for(int i = 0; i < 4; i++)
      lens.aspheric_correction_coefficients[i] = 0;
    
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(!strncmp(in, "#!aspheric=", 11))
    {
      in += 11;
      lens.aspheric = strtol(in, &in, 10);
      // munch comma
      in++;
      for(int i = 0; i < 4; i++, in++)
        lens.aspheric_correction_coefficients[i] = strtof(in, &in);
    }

    l[cnt++] = lens;

    if(cnt >= max) break;
  }
  fclose(f);
  return cnt;
}

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
