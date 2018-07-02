CC=clang
CXX=clang++

CFLAGS=\
-I/usr/local/include/cairo/\
-L/usr/local/lib\
-std=c11\
-Wall\
-Iext/\
-D_GNU_SOURCE\
-fopenmp

CXXFLAGS=\
-I/usr/local/include/cairo/\
-L/usr/local/lib\
-Wall\
-Iext/\
-D_GNU_SOURCE\
-fopenmp\
-std=c++11

# OPTFLAGS=-I. -ggdb3 -Isrc/

OPTFLAGS=\
-O3\
-ffast-math\
-mfpmath=sse\
-march=native\
-fexpensive-optimizations\
-DNDEBUG\
-fno-finite-math-only\
-I.\
-Isrc/

LDFLAGS=-lm

HEADERS=\
src/lenssystem.h\
src/poly.h\
src/raytrace_draw.h\
src/raytrace.h\
src/gencode.h\
src/spectrum.h

.PHONY=all clean

all: view fit gencode fresnel genpoly printpoly sample-plot

view: Makefile src/view.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/view.c $(shell pkg-config --cflags --libs gtk+-2.0) ${LDFLAGS} -o bin/view ${LDFLAGS}

sample-plot: Makefile src/sample-plot.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/sample-plot.c -o bin/sample-plot ${LDFLAGS}

fresnel: Makefile src/fresnel.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/fresnel.c -o bin/fresnel ${LDFLAGS}

fit: Makefile src/fit.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/fit.c -o bin/fit ${LDFLAGS}

genpoly: Makefile src/genpoly.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXLAGS} src/genpoly.c -o bin/genpoly ${LDFLAGS}

parsepoly: Makefile src/parsepoly.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/parsepoly.c -o bin/parsepoly ${LDFLAGS}

printpoly: Makefile src/printpoly.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/printpoly.c -o bin/printpoly ${LDFLAGS}

gencode: Makefile src/gencode.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/gencode.c -o bin/gencode ${LDFLAGS}

lt-aperture-sampling: Makefile src/sample_ap_lt.c init.h lt_sample_aperture.h ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} -Irender/${lensname} src/sample_ap_lt.c -o bin/lt-aperture-sampling ${LDFLAGS}
	
glRender: Makefile src/render_gl.c
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/render_gl.c ${LDFLAGS} -o bin/glRender -lGLEW -lGL -lGLU -lglfw

clean:
	rm -f view fit gencode fresnel fresnel.dat genpoly printpoly sample-plot sample-plot.dat lt_convergence.dat lt_convergence_profile.dat lt-aperture-sampling
