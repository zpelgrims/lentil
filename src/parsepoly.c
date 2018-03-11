#include <string.h>
#include <math.h>
#include "poly.h"

  
// read terms (lines) from csv: (path defined in first argument)
// coefficient;a;b;c;d;e
// a,b,c,d,e are the exponents x^a, y^b, dx^c, dy^d, lambda^e
// for each equation there is one 'block' of terms (empty line for new equation)
// -------File content:---------------------------
// coeffx1,ax1,bx1,cx1,dx1,ex1
// coeffx2,ax2,bx2,cx2,dx2,ex2
//
// coeffy1,ay1,by1,cy1,dy1,ey1
// coeffy2,ay2,by2,cy2,dy2,ey2
// coeffy3,ay3,by3,cy3,dy3,ey3
//
// coeffdx1,adx1,bdx1,cdx1,ddx1,edx1
//
// coeffdy1,ady1,bdy1,cdy1,ddy1,edy1
//
// ...
// -----------------------------------------------
// writes polynomial in binary format to file (path defined in second argument)
int main(int argc, char *arg[])
{
  if(argc < 3)
  {
    fprintf(stderr, "usage: %s input.csv output.poly\n", arg[0]);
    exit(-1);
  }
  
  FILE *f = fopen(arg[1], "r");
  if(!f)
  {
    fprintf(stderr, "Could not open file %s for reading\n", arg[1]);
    exit(-1);
  }
  
  fseek(f, 0, SEEK_END);
  unsigned int size = ftell(f);
  fseek(f, 0, SEEK_SET);
  
  poly_term_t *term = (poly_term_t*)malloc(sizeof(poly_term_t)*size);
  poly_term_t *term_ptr = term;
  int term_ctr = 0;
  int var_ctr = 0;
  
  poly_system_t s;
  
  char line[2048];
  while(fgets(line, 2048, f) != NULL)
  {
    char *in = line;
    while(in[0] == '\t' || in[0] == ' ') in++;
    if(in[0] == '#') continue;
    if(in[0] == '\n')
    {
      s.poly[var_ctr].num_terms = term_ctr;
      s.poly[var_ctr].term = term_ptr;
      term_ptr += term_ctr;
      term_ctr = 0;
      var_ctr++;
      continue;
    }
    term_ptr[term_ctr].coeff = strtof(in, &in);
    in++;
    for(int i = 0; i < poly_num_vars; i++)
    {
      while(in[0] == '\t' || in[0] == ' ') in++;
      term_ptr[term_ctr].exp[i] = strtol(in, &in, 10);
      in++;
    }
    fprintf(stderr, "x%d = %f*x^%d*y^%d*dx^%d*dy^%d*lambda^%d\n", var_ctr, term_ptr[term_ctr].coeff, term_ptr[term_ctr].exp[0], term_ptr[term_ctr].exp[1], term_ptr[term_ctr].exp[2], term_ptr[term_ctr].exp[3], term_ptr[term_ctr].exp[4]);
    term_ctr++;
  }
  if(term_ctr > 0)
  {
      s.poly[var_ctr].num_terms = term_ctr;
      s.poly[var_ctr].term = term_ptr;
      term_ptr += term_ctr;
      term_ctr = 0;
      var_ctr++;
  }
  poly_system_sort(&s);
  poly_system_write(&s, arg[2]);
}
