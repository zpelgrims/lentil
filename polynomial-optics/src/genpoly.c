#include <math.h>
#include <string.h>
#include "poly.h"

inline unsigned int numterms(unsigned int degree, unsigned int num_variables)
{
  float facn = 1, facd = 1, facnd = 1;
  for(int i = 2; i < degree + num_variables + 1; i++)
  {
    facnd *= i;
    if(i == degree)
      facd = facnd;
    if(i == num_variables)
      facn = facnd;
  }
  return floor(facnd / (facn * facd) + 0.5f);
}

int main(int argc, char *arg[])
{
  if(argc < 3)
  {
    fprintf(stderr, "Usage: %s degree output.poly\n", arg[0]);
    return -1;
  }
  int degree = atol(arg[1]);
  poly_system_t s;
  //Generate array {0,0,0,0,0}, {0,0,0,0,1}, {0,0,0,0,2} ... {0,0,0,1,0}
  // ... {degree, degree, ...}
  //this is essentially the degree-bit representation of a number with
  //poly_num_vars digits (with base degree)
  int numTerms = numterms(degree, poly_num_vars);
  poly_term_t *expMatrix = malloc((numTerms+1)*poly_num_vars*sizeof(poly_term_t));

  int validterms = 0;
  for(int i = 0; validterms <= numTerms; i++)
  {
    expMatrix[validterms].coeff = 0.0f;
    int tmp = i;
    for(int j = poly_num_vars-1; j >= 0; j--)
    {
      expMatrix[validterms].exp[j] = tmp%(degree+1);
      tmp /= (degree+1);
    }
    //remove terms with sum exp > degree
    int currdegree = 0;
    for(int j = 0; j < poly_num_vars; j++) currdegree += expMatrix[validterms].exp[j];
    if(currdegree <= degree)
      validterms++;
  }
  for(int i = 0; i < poly_num_vars; i++)
  {
    s.poly[i].num_terms = numTerms;
    s.poly[i].term = (poly_term_t *)malloc(sizeof(poly_term_t)*numTerms);
    int termsWritten = 0;
    for(int j = 0;j < numTerms; j++)
    {
      int *exp = expMatrix[j].exp;
      int currdegree = 0;
      for(int i = 0; i < poly_num_vars; i++) currdegree += exp[i];
      if(currdegree <= degree)
        memcpy(s.poly[i].term+(termsWritten++), expMatrix+j, sizeof(poly_term_t));
    }
  }
  fprintf(stderr, "polynomial of degree %d has %d terms\n", degree, numTerms);

  free(expMatrix);
  poly_system_sort(&s);
  poly_system_write(&s, arg[2]);
}
