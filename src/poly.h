#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// we currently work on x, y, dx dy, lambda
// where x y dx dy change meaning from plane/plane to spherical/spherical
// and lambda is wavelength in micrometers
#define poly_num_vars 5
#define poly_coeff_eps 1e-35f
#define real double

typedef struct poly_term_t
{
  float coeff;
  int32_t exp[poly_num_vars];
}
poly_term_t;

typedef struct poly_t
{
  int32_t num_terms;
  poly_term_t *term;
}
poly_t;

typedef struct poly_system_t
{
  poly_t poly[poly_num_vars];
}
poly_system_t;

typedef struct poly_jacobian_t
{
  poly_t poly[poly_num_vars*poly_num_vars];
}
poly_jacobian_t;

// optimised integer powers of x
real poly_pow(const real x, const int32_t exp)
{
  if(exp == 0) return 1.0f;
  if(exp == 1) return x;
  if(exp == 2) return x*x;
  const float p2 = poly_pow(x, exp/2);
  if(exp &  1) return x * p2 * p2;
  return p2 * p2;
}

// evaluate the term at point x.
real poly_term_evaluate(const poly_term_t *t, const float *x)
{
  if(fabsf(t->coeff) < poly_coeff_eps) return 0.0f;
  real out = t->coeff;
  for(int k=0;k<poly_num_vars;k++)
    out *= poly_pow(x[k], t->exp[k]);
  return out;
}

// return the evaluated polynomial at the given point x.
real poly_evaluate(const poly_t *poly, const float *x, int max_degree)
{
  real out = 0.0;
  for(int t=0;t<poly->num_terms;t++)
  {
    int degree = 0;
    for(int k=0;k<poly_num_vars;k++) degree += poly->term[t].exp[k];
    if(degree > max_degree) return out; // sorted
    out += poly_term_evaluate(poly->term+t, x);
  }
  return out;
}

// write evaluation of poly system to output *out.
void poly_system_evaluate(const poly_system_t *s, const float *x, float *out, int max_degree)
{
  for(int k=0;k<poly_num_vars;k++)
    out[k] = poly_evaluate(s->poly+k, x, max_degree);
}

void poly_destroy(poly_t *poly)
{
  free(poly->term);
  poly->term = 0;
  poly->num_terms = 0;
}

void poly_system_destroy(poly_system_t *s)
{
  for(int k=0;k<poly_num_vars;k++)
    poly_destroy(s->poly+k);
}

void poly_copy(const poly_t *p, poly_t *p2)
{
  p2->num_terms = p->num_terms;
  p2->term = (poly_term_t *)malloc(sizeof(poly_term_t)*p->num_terms);
  memcpy(p2->term, p->term, sizeof(poly_term_t)*p->num_terms);
}

void poly_system_copy(const poly_system_t *s, poly_system_t *s2)
{
  for(int k=0;k<poly_num_vars;k++)
    poly_copy(s->poly+k, s2->poly+k);
}

void poly_get_derivative(const poly_t *poly, poly_t *deriv, const int *dx)
{
  poly_copy(poly, deriv); // derivative has same configuration or less
  for(int t=0;t<poly->num_terms;t++)
  {
    poly_term_t *pt = deriv->term + t;
    pt->coeff = poly->term[t].coeff;
    for(int i=0;i<poly_num_vars;i++)
    {
      int d = dx[i]; // take d-th derivative
      while(d > 0)
      {
        pt->coeff *= pt->exp[i];
        if(pt->exp[i] == 0) break; // term vanished.
        pt->exp[i]--;
        d--;
      }
    }
  }
}

// compute jacobian. row j and column i in the jacobian (address 3*j+i) will
// contain poly[i] / dxj.
void poly_system_get_jacobian(const poly_system_t *s, poly_jacobian_t *jac)
{
  for(int i=0;i<poly_num_vars;i++) for(int j=0;j<poly_num_vars;j++)
  {
    int dx[poly_num_vars] = {0};
    dx[j] = 1;
    poly_get_derivative(s->poly+i, jac->poly + poly_num_vars*i + j, dx);
  }
}

void poly_print(const poly_t *p, const char *vname[poly_num_vars], FILE *f)
{
  static const char *vn[poly_num_vars] = {"x0", "x1", "x2", "x3", "x4"};
  for(int t=0;t<p->num_terms;t++)
  {
    if(fabsf(p->term[t].coeff) > poly_coeff_eps)
    {
      fprintf(f, " + %g ", p->term[t].coeff);
      for(int k=0;k<poly_num_vars;k++)
        if(p->term[t].exp[k] == 1)
          fprintf(f, "*%s", vname ? vname[k] : vn[k]);
        else if(p->term[t].exp[k] > 0)
          fprintf(f, "*lens_ipow(%s, %d)", vname ? vname[k] : vn[k], p->term[t].exp[k]);
    }
  }
}

int poly_system_read(poly_system_t *s, const char *filename)
{
  FILE *f = fopen(filename, "rb");
  int r = 0;
  if(!f) return 1;
  for(int k=0;k<poly_num_vars;k++)
  {
    r = fread(&s->poly[k].num_terms, sizeof(int32_t), 1, f);
    if(r != 1) { fclose(f); return 1; }
    s->poly[k].term = (poly_term_t *)malloc(sizeof(poly_term_t)*s->poly[k].num_terms);
    r = fread(s->poly[k].term, sizeof(poly_term_t), s->poly[k].num_terms, f);
    if(r != s->poly[k].num_terms) { fclose(f); return 1; }
  }
  fclose(f);
  return 0;
}

int poly_system_write(poly_system_t *s, const char *filename)
{
  FILE *f = fopen(filename, "wb");
  int r = 0;
  if(!f) return 1;
  for(int k=0;k<poly_num_vars;k++)
  {
    int32_t num_terms = s->poly[k].num_terms;
    r = fwrite(&num_terms, sizeof(int32_t), 1, f);
    if(r != 1) { fclose(f); return 1; }
    r = fwrite(s->poly[k].term, sizeof(poly_term_t), num_terms, f);
    if(r != num_terms) { fclose(f); return 1; }
  }
  fclose(f);
  return 0;
}

// write the coefficients of the polynomial p to the given coefficient array
// coeff. skip all terms with degree > max_degree. returns the number
// of written coefficients. coeff can be 0 to just return the count up front.
int poly_get_coeffs(const poly_t *p, const int max_degree, float *coeff)
{
  int cnt = 0;
  for(int t=0;t<p->num_terms;t++)
  {
    int degree = 0;
    for(int k=0;k<poly_num_vars;k++) degree += p->term[t].exp[k];
    if(degree <= max_degree)
    {
      if(coeff) coeff[cnt] = p->term[t].coeff;
      cnt++;
    }
    else break;
  }
  return cnt;
}

// write the coefficients of the polynomial p to the given coefficient array
// coeff. skip all terms with degree > max_degree. returns the number
// of written coefficients. coeff can be 0 to just return the count up front.
int poly_system_get_coeffs(const poly_system_t *s, const int max_degree, float *coeff)
{
  int cnt = 0;
  for(int j=0;j<poly_num_vars;j++) // don't dump lambda == lambda
    cnt += poly_get_coeffs(s->poly + j, max_degree, coeff ? coeff + cnt : 0);
  return cnt;
}

// set the coefficients of the given polynomial to the ones in the buffer.
// skip all terms with degree > max_degree. returns the number of set
// coefficients for sanity checking.
int poly_set_coeffs(poly_t *p, const int max_degree, const float *coeff)
{
  int cnt = 0;
  for(int t=0;t<p->num_terms;t++)
  {
    int degree = 0;
    for(int k=0;k<poly_num_vars;k++) degree += p->term[t].exp[k];
    if(degree <= max_degree)
    {
      p->term[t].coeff = coeff[cnt];
      cnt++;
    }
    else break; // input was sorted by degree. first > max is the end of our list.
  }
  return cnt;
}

// set the coefficients of the given polynomial to the ones in the buffer.
// skip all terms with degree > max_degree. returns the number of set
// coefficients for sanity checking.
int poly_system_set_coeffs(poly_system_t *s, const int max_degree, const float *coeff)
{
  int cnt = 0;
  for(int j=0;j<poly_num_vars;j++)
    cnt += poly_set_coeffs(s->poly+j, max_degree, coeff ? coeff + cnt : 0);
  return cnt;
}

int poly_term_get_degree(poly_term_t *p)
{
    int cnt = 0;
    for(int j=0;j<poly_num_vars;j++) cnt += p->exp[j];
    return cnt;
}

int _compare(const void *aa, const void *bb)
{
  poly_term_t *a = (poly_term_t *)aa;
  poly_term_t *b = (poly_term_t *)bb;
  int degree_a = 0, degree_b = 0;
  for(int k=0;k<poly_num_vars;k++) degree_a += a->exp[k];
  for(int k=0;k<poly_num_vars;k++) degree_b += b->exp[k];
  return degree_a - degree_b;
}

void poly_system_sort(poly_system_t *s)
{
  for(int k=0;k<poly_num_vars;k++)
    qsort(s->poly[k].term, s->poly[k].num_terms, sizeof(poly_term_t), &_compare);
}
