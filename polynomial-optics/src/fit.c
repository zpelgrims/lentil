//todo: better .fit paths/names

#include "../../Eigen/Eigen/Dense"
#include "raytrace.h"
#include "poly.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <vector>
#include <algorithm>

#include "../../fmt/include/fmt/format.h"
#include "../ext/ProgressBar.hpp"

#include <cstdlib>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

#define MATCHING_PURSUIT
#define OMP_ALLOW_REPLACING
#define OMP_CALCULATE_EXACT_ERROR

//#define OMP_DEBUG_OUTPUT
//#define ONLY_OUTER_POLY
//#define WITHOUT_TRANSMITTANCE

std::vector<lens_element_t> lenses;
static int lenses_cnt = 0;
static const float zoom = 0.0f;
static int max_degree = 15;
//1=allow aspheric elements, 0=use only spherical ones (without correction terms)
static int aspheric_elements = 1;

//stop when error is smaller than eps - one threshold per equation x, y, dx, dy, transmittance
//if zero: stop only when replacing a term doesn't decrease the error.
//static const float eps[] = {1e-6, 1e-6, 1e-8, 1e-8, 1e-9};
static const float eps[] = {0, 0, 0, 0, 0};

int main(int argc, char *argv[])
{
  const char *id = argv[1];
  int lens_focal_length = atol(argv[2]);
  max_degree = atol(argv[3]);
  if(max_degree < 1) max_degree = 1;
  int max_coeffs = 10000;
  max_coeffs = atol(argv[4]);
  const char *sorted_poly_path = argv[5];

  lenses_cnt = lens_configuration(lenses, id, lens_focal_length);
  const float p_dist = lens_get_thickness(lenses[lenses_cnt-1], zoom);
  const float p_rad = lenses[lenses_cnt-1].housing_radius;

  std::string lens_id_path = find_lens_id_location(id, lens_focal_length);
  std::string fitfile_path = lens_id_path + "fitted/exitpupil.fit";
  std::string ap_fitfile_path = lens_id_path + "fitted/aperture.fit";
  fmt::print("Starting fitting: \n");
  fmt::print("\t exitpupil.fit location: {}\n", fitfile_path.c_str());
  fmt::print("\t aperture.fit location: {}\n", ap_fitfile_path.c_str());

  // load generic 1233-coefficient degree 9 polynomial template with all zero coeffs:
  poly_system_t poly, poly_ap;
  if(poly_system_read(&poly, sorted_poly_path) || poly_system_read(&poly_ap, sorted_poly_path))
  {
    fmt::print("[fit] could not read `sorted.poly' template!\n");
    exit(1);
  }
  // already storing sorted:
  // poly_system_sort(&poly);
  // poly_system_sort(&poly_ap);

  const int coeff_size = std::max(poly_system_get_coeffs(&poly, max_degree, 0),
                             poly_system_get_coeffs(&poly_ap, max_degree, 0));
  float *coeff = (float *)malloc(sizeof(float)*coeff_size);

  const int sample_cnt = 15000;
  float *sample = (float *)malloc(sample_cnt*sizeof(float)*5);
  float *sample_in = (float *)malloc(sample_cnt*sizeof(float)*5);

  int valid = 0;
  while(1)
  {
    const float u = drand48(), v = drand48(), w = drand48(), x = drand48(), y = drand48();

    // zeno: what are all these arbitrary values..?
    std::vector<float> ray_in = {
      // p_rad * 4.0f * (x-0.5f),
      // p_rad * 4.0f * (y-0.5f),
      35.0f/2.0f - x*35.0f, // 35mm film, isotropic
      35.0f/2.0f - y*35.0f,
      p_rad/p_dist * cosf(2.0f*M_PI*u)*sqrtf(v),
      p_rad/p_dist * sinf(2.0f*M_PI*u)*sqrtf(v),
      0.4f + 0.3f*w //random wavelength between 400 and 700
    };
    ray_in[2] -= ray_in[0] / p_dist;
    ray_in[3] -= ray_in[1] / p_dist;
    std::vector<float> out(5);
    int error = evaluate(lenses, lenses_cnt, zoom, ray_in, out, aspheric_elements);
    if(!error)
    {
      for(int k=0;k<5;k++) sample_in[5*valid + k] = ray_in[k];
      for(int k=0;k<5;k++) sample[valid + k*sample_cnt] = out[k];
      valid++;
    }

    if(valid >= sample_cnt) break;
  }
  fmt::print("[ sensor->outer pp ] optimising {0} coeffs by {1}/{2} valid sample points\n", coeff_size, valid, sample_cnt);
  const char *outvname[] = {"x", "y", "dx", "dy", "transmittance"};

  // ===================================================================================================
  // evaluate poly sensor -> outer pupil
  // ===================================================================================================
  {
    int sumCoeffs = 0;
    int maxSumCoeffs = 0;
    float errorSum = 0.0f;
    #ifdef WITHOUT_TRANSMITTANCE
    for(int j = 0; j < 4; j++)
    #else
    for(int j = 0; j < 5; j++)
    #endif
    {
      const int degree_coeff_size = poly_get_coeffs(poly.poly + j, max_degree, 0);
      int coeff_cnt = degree_coeff_size;
      const int degree_num_samples = valid;

      //Matrix containing evaluations of all terms (rows) for each input sample (columns)
      Eigen::MatrixXd A(degree_coeff_size, degree_num_samples);
      for(int y = 0; y < degree_num_samples; y++)
      {
        for(int x = 0; x < degree_coeff_size; x++)
        {
          poly_term_t term = poly.poly[j].term[x];
          term.coeff = 1;
          A(x,y) = poly_term_evaluate(&term, sample_in+5*y);
        }
      }
      //reference output vector
      Eigen::VectorXd b(degree_num_samples);
      for(int y = 0; y < degree_num_samples; y++)
      {
        b(y) = sample[j*sample_cnt+y];
      }
#ifdef MATCHING_PURSUIT
      Eigen::VectorXd result = Eigen::ArrayXd::Zero(degree_coeff_size);
      Eigen::VectorXd residual = b;

      #ifndef OMP_CALCULATE_EXACT_ERROR
      Eigen::VectorXd factor(degree_coeff_size);
      for(int i = 0; i < degree_coeff_size; i++)
        factor(i) = 1 / (A.row(i).norm() * (poly_term_get_degree(poly.poly[j].term+i)+1.0));
      #endif

      Eigen::VectorXd used(degree_coeff_size);
      int permutation[degree_coeff_size];
      for(int i = 0; i < degree_coeff_size; i++) permutation[i] = i;
      used.setZero();
      coeff_cnt = 0;

      double preverror = 1e30;
      Eigen::VectorXd prod(degree_coeff_size);
      prod.setZero();

      ProgressBar progressBarSensorOuterPP(degree_coeff_size, 70, '#', '-');
      
      #ifndef OMP_ALLOW_REPLACING
      for(int i = 0; coeff_cnt < max_coeffs; i++)
      #else
      for(int i = 0; coeff_cnt < degree_coeff_size; i++)
      #endif
      {
        ++progressBarSensorOuterPP;
        progressBarSensorOuterPP.display();

        int maxidx = 0;

        #ifndef OMP_CALCULATE_EXACT_ERROR
        prod = (Eigen::ArrayXd(A * residual) * Eigen::ArrayXd(factor) * (1-Eigen::ArrayXd(used))).abs();
        prod.maxCoeff(&maxidx);
        #else
        {
          Eigen::MatrixXd tmp(degree_num_samples, coeff_cnt+1);
          for(int k = 0; k < coeff_cnt; k++)
            tmp.col(k) = A.row(permutation[k]).transpose();
          for(int c = 0; c < degree_coeff_size; c++)
          {
            if(used(c) > 0)
              prod(c) = 1e30;
            else if(prod(c) == 0)
            {
              tmp.col(coeff_cnt) = A.row(c).transpose();
              Eigen::VectorXd result = (tmp.transpose()*tmp).ldlt().solve(tmp.transpose()*b);
              prod(c) = (b-tmp*result).squaredNorm();
            }
          }
        }
        prod.minCoeff(&maxidx);
        #endif

        if(used(maxidx) > 0)
          break;
        used(maxidx) = 1;

        if(coeff_cnt < max_coeffs)
        {
          permutation[coeff_cnt] = maxidx;
          coeff_cnt++;
          //recalculate weights of terms:
          prod.setZero();
        }
        else
        {
          double minerror = 1e30;
          int minidx = 0;

          for(int c = 0; c < coeff_cnt; c++)
          {
            Eigen::MatrixXd tmp(degree_num_samples, coeff_cnt);
            for(int k = 0; k < coeff_cnt; k++)
              tmp.col(k) = A.row(c!=k?permutation[k]:maxidx).transpose();
            double newerror = (b-tmp*(tmp.transpose()*tmp).ldlt().solve(tmp.transpose()*b)).squaredNorm();
            if(newerror < minerror)
            {
              minerror = newerror;
              minidx = c;
            }
          }
          if(minerror < preverror)
          {
            used(permutation[minidx]) = 0;
            permutation[minidx] = maxidx;
            #ifdef OMP_DEBUG_OUTPUT
            fmt::print("[{}] {}\n", i, minerror);
            #endif
            i=0;
            //reset used for new residual:
            used.setZero();
            for(int i = 0; i < coeff_cnt; i++)
              used(permutation[i]) = 1;
            prod.setZero();
          }
          #ifdef OMP_DEBUG_OUTPUT
          else
            fmt::print(" {} ", i);
          #endif
        }

        Eigen::MatrixXd tmp = Eigen::ArrayXXd::Zero(degree_num_samples, coeff_cnt);
        for(int k = 0; k < coeff_cnt; k++)
          tmp.col(k) = A.row(permutation[k]).transpose();
        result = (tmp.transpose()*tmp).ldlt().solve(tmp.transpose()*b);
        residual = b-tmp*result;
        if(residual.squaredNorm() < eps[j] * degree_num_samples) break;
        preverror = residual.squaredNorm();
      }

      progressBarSensorOuterPP.done();

      Eigen::VectorXd coeffs = Eigen::ArrayXd::Zero(degree_coeff_size);
      for(int k = 0; k < coeff_cnt; k++)
        coeffs(permutation[k]) = result(k);
      result = coeffs;
#else
      Eigen::VectorXd result = (A*A.transpose()).ldlt().solve(A*b);
      Eigen::VectorXd residual = b-A.transpose()*result;
#endif
      float error = residual.squaredNorm() / degree_num_samples;

      sumCoeffs += coeff_cnt;
      maxSumCoeffs += degree_coeff_size;

      for(int i = 0; i < degree_coeff_size; i++) coeff[i] = result[i];
      poly_set_coeffs(poly.poly + j, max_degree, coeff);

      fmt::print("{}: {}\n", outvname[j], error);
      errorSum += error;
    }

    fmt::print("\ndegree {} has {}/{} coeffs, fitting error {}\n", max_degree, sumCoeffs, maxSumCoeffs, errorSum);
  }

  // write optimised poly
  fmt::print("output poly has {} coeffs.\n", poly_system_get_coeffs(&poly, max_degree, 0));
  poly_system_write(&poly, fitfile_path.c_str());

  // ===================================================================================================
  // evaluate_aperture poly sensor -> aperture
  // ===================================================================================================
  memset(sample, 0, sizeof(float)*sample_cnt*5);
  for(int i=0;i<valid;i++)
  {
    //float *ray_in = sample_in+5*i;
    std::vector<float> ray_in = {sample_in[5*i], sample_in[(5*i)+1], sample_in[(5*i)+2], sample_in[(5*i)+3], sample_in[(5*i)+4]}; //not sure about this, could be wrong
    std::vector<float> out(5);
    int error = evaluate_aperture(lenses, lenses_cnt, zoom, ray_in, out, aspheric_elements);
    (void)error; // silence non-debug build warning
    assert(error == 0);
    for(int k=0;k<5;k++)
      sample[i+k*sample_cnt] = out[k];
  }
  fmt::print("[ sensor->aperture ] optimising %d coeffs by %d/%d valid sample points\n", coeff_size, valid, sample_cnt);

  {
    int sumCoeffs = 0;
    int maxSumCoeffs = 0;
    float errorSum = 0.0f;
    #ifdef ONLY_OUTER_POLY
    for(int j = 0; j < 0; j++)
    #else
    #ifdef WITHOUT_TRANSMITTANCE
    for(int j = 0; j < 4; j++)
    #else
    for(int j = 0; j < 5; j++)
    #endif
    #endif
    {
      const int degree_coeff_size = poly_get_coeffs(poly_ap.poly + j, max_degree, 0);
      int coeff_cnt = degree_coeff_size;
      const int degree_num_samples = valid;

      //Matrix containing evaluations of all terms (rows) for each input sample (columns)
      Eigen::MatrixXd A(degree_coeff_size, degree_num_samples);
      for(int y = 0; y < degree_num_samples; y++)
      {
        for(int x = 0; x < degree_coeff_size; x++)
        {
          poly_term_t term = poly_ap.poly[j].term[x];
          term.coeff = 1;
          A(x,y) = poly_term_evaluate(&term, sample_in+5*y);
        }
      }
      //reference output vector
      Eigen::VectorXd b(degree_num_samples);
      for(int y = 0; y < degree_num_samples; y++)
      {
        b(y) = sample[j*sample_cnt+y];
      }
#ifdef MATCHING_PURSUIT
      Eigen::VectorXd result = Eigen::ArrayXd::Zero(degree_coeff_size);
      Eigen::VectorXd residual = b;

      #ifndef OMP_CALCULATE_EXACT_ERROR
      Eigen::VectorXd factor(degree_coeff_size);
      for(int i = 0; i < degree_coeff_size; i++)
        factor(i) = 1 / (A.row(i).norm() * (poly_term_get_degree(poly.poly[j].term+i)+1.0));
      #endif

      Eigen::VectorXd used(degree_coeff_size);
      int permutation[degree_coeff_size];
      for(int i = 0; i < degree_coeff_size; i++) permutation[i] = i;
      used.setZero();
      coeff_cnt = 0;

      double preverror = 1e30;
      Eigen::VectorXd prod(degree_coeff_size);
      prod.setZero();

      ProgressBar progressBarSensorAperture(degree_coeff_size, 70, '#', '-');

      #ifndef OMP_ALLOW_REPLACING
      for(int i = 0; coeff_cnt < max_coeffs; i++)
      #else
      for(int i = 0; coeff_cnt < degree_coeff_size; i++)
      #endif
      {
        ++progressBarSensorAperture;
        progressBarSensorAperture.display();

        int maxidx = 0;

        #ifndef OMP_CALCULATE_EXACT_ERROR
        prod = (Eigen::ArrayXd(A * residual) * Eigen::ArrayXd(factor) * (1-Eigen::ArrayXd(used))).abs();
        prod.maxCoeff(&maxidx);
        #else
        {
          Eigen::MatrixXd tmp(degree_num_samples, coeff_cnt+1);
          for(int k = 0; k < coeff_cnt; k++)
            tmp.col(k) = A.row(permutation[k]).transpose();
          for(int c = 0; c < degree_coeff_size; c++)
          {
            if(used(c) > 0)
              prod(c) = 1e30;
            else if(prod(c) == 0)
            {
              tmp.col(coeff_cnt) = A.row(c).transpose();
              Eigen::VectorXd result = (tmp.transpose()*tmp).ldlt().solve(tmp.transpose()*b);
              prod(c) = (b-tmp*result).squaredNorm();
            }
          }
        }
        prod.minCoeff(&maxidx);
        #endif

        if(used(maxidx) > 0)
          break;
        used(maxidx) = 1;

        if(coeff_cnt < max_coeffs)
        {
          permutation[coeff_cnt] = maxidx;
          coeff_cnt++;
          //recalculate weights of terms:
          prod.setZero();
        }
        else
        {
          double minerror = 1e30;
          int minidx = 0;

          for(int c = 0; c < coeff_cnt; c++)
          {
            Eigen::MatrixXd tmp(degree_num_samples, coeff_cnt);
            for(int k = 0; k < coeff_cnt; k++)
              tmp.col(k) = A.row(c!=k?permutation[k]:maxidx).transpose();
            double newerror = (b-tmp*(tmp.transpose()*tmp).ldlt().solve(tmp.transpose()*b)).squaredNorm();
            if(newerror < minerror)
            {
              minerror = newerror;
              minidx = c;
            }
          }
          if(minerror < preverror)
          {
            used(permutation[minidx]) = 0;
            permutation[minidx] = maxidx;
            #ifdef OMP_DEBUG_OUTPUT
            fmt::print("[{}] {}\n", i, minerror);
            #endif
            i=0;
            //reset used for new residual:
            used.setZero();
            for(int i = 0; i < coeff_cnt; i++)
              used(permutation[i]) = 1;
            prod.setZero();
          }
          #ifdef OMP_DEBUG_OUTPUT
          else
            fmt::print(" {} ", i);
          #endif
        }

        Eigen::MatrixXd tmp = Eigen::ArrayXXd::Zero(degree_num_samples, coeff_cnt);
        for(int k = 0; k < coeff_cnt; k++)
          tmp.col(k) = A.row(permutation[k]).transpose();
        result = (tmp.transpose()*tmp).ldlt().solve(tmp.transpose()*b);
        residual = b-tmp*result;
        if(residual.squaredNorm() < eps[j] * degree_num_samples) break;
        preverror = residual.squaredNorm();
      }

      progressBarSensorAperture.done();

      Eigen::VectorXd coeffs = Eigen::ArrayXd::Zero(degree_coeff_size);
      for(int k = 0; k < coeff_cnt; k++)
        coeffs(permutation[k]) = result(k);
      result = coeffs;
#else
      Eigen::VectorXd result = (A*A.transpose()).ldlt().solve(A*b);
      Eigen::VectorXd residual = b-A.transpose()*result;
#endif
      float error = residual.squaredNorm() / degree_num_samples;

      sumCoeffs += coeff_cnt;
      maxSumCoeffs += degree_coeff_size;

      for(int i = 0; i < degree_coeff_size; i++) coeff[i] = result[i];
      poly_set_coeffs(poly_ap.poly + j, max_degree, coeff);

      fmt::print("{}: {}\n", outvname[j], error);
      errorSum += error;
    }
    fmt::print("\ndegree {} has {}/{} coeffs, fitting error {}\n", max_degree, sumCoeffs, maxSumCoeffs, errorSum);
  }

  fmt::print("output aperture poly has {} coeffs.\n", poly_system_get_coeffs(&poly_ap, max_degree, 0));
  poly_system_write(&poly_ap, ap_fitfile_path.c_str());
  exit(0);
}
