Overview
------------------------
The provided code can be used to find sparse polynomials transferring rays
through a lens system.

It is part of our paper:  
Schrade, E., Hanika, J., & Dachsbacher, C. (2016). Sparse high-degree polynomials
for wide-angle lenses. In Eurographics Symposium on Rendering.

With the source code you can:

- read lens definitions and (generic) polynomials,
- fit a polynomial to a specific lens system, 
  (optionally only a specified number of terms is chosen from the polynomial
  that best fits to the lens)
- view the lens as well as rays traced through the lens system and compare the
  ray-traced rays to the output of the fitted polynomials,
- generate code from the fitted polynomials to use it in your own renderer
  (includes aperture sampling for both path tracing and light tracing)

Dependencies
------------------------
Our fitting algorithm uses the library [Eigen](http://eigen.tuxfamily.org) and
we use [GTK+](http://www.gtk.org/) and [cairo](https://www.cairographics.org/)
for our viewer. Apart from that there are no external dependencies.


Building
------------------------
We provide a Makefile for building the tools. Most of them require only a single
source file and some common headers.

The headers in folder _src_ include the following:

- __lenssystem.h__: _parse_ lens systems
- __poly.h__: _read_ and _write_ (binary) polynomials and functions to _evaluate_ and
  calculate _derivatives_
- __raytrace.h__: _trace rays_ through a lens system
- __raytrace_draw.h__: same as _raytrace.h_, but draw lines while tracing (only
  for _view_)
- __gencode.h__: helper functions to _generate code_ from polynomials, e.g. for
  aperture sampling
- __spectrum.h__: helper functions for approximating the refractive index for a
  given wavelength.

Description of the tools
------------------------
- __genpoly__: generates a generic polynomial with terms up to a defined _degree_
    and stores the polynomial to a binary file at a given _path_
    (_fit_ loads polynomials from _sorted.poly_)  
    _example: ./genpoly 11 sorted.poly_
- __parsepoly__: reads a csv file containing terms of a polynomial system and
    stores them in binary format (as _genpoly_ does)  
    _example: ./parsepoly poly.csv sorted.poly_
- __printpoly__: reads a _binary_ polynomial file (e.g. the output from _genpoly_
    or _parsepoly_) and outputs the terms to console in a csv format (that could
    be read by _parsepoly_ again)  
    _example: ./printpoly sorted.poly_
- __fit__: loads a generic polynomial from file _sorted.poly_ and fits the
    coefficients to a specified lens.  
    Additionally to the path to the _lensfile_ arguments can be set to limit
    the _maximum degree_ of terms (e.g. if _sorted.poly_ contains terms of higher
    degree that should be ignored) and the _number of terms_ per equation (if 
    _sorted.poly_ contains a larger number of terms and we search for a sparse
    solution).  
    _fit_ creates files _lensfile.fit_ and _lensfile\_ap.fit_ containing the
    fitted polynomials for the outer pupil and sensor respectively. (These files
    have the same format as _.poly_-files and can hence, be inspected using
    _printpoly_)  
    _example: ./fit lenses/fisheye-aspherical.fx 11 28_
- __view__: reads and draws a specified lens. If fitted polynomials were calculated,
    i.e. if _.fit_-files exist, both the aperture polynomial and the outer polynomial
    are evaluated as well such that their output can be compared to the ray-traced
    reference.  
    _example: ./view lenses/fisheye-aspherical.fx_
- __gencode__: generate code from a fitted polynomial. Creates header files for
    evaluating the polynomials transferring rays to the sensor / aperture, and
    for aperture sampling.  
    _example: ./gencode lenses/fisheye-aspherical.fx_  
    For examples how to use the generated code see _render/lens.h_

