OS := $(shell uname)
ifeq ($(OS), Darwin)
	CXX=clang++
endif
ifeq ($(OS), Linux)
	CXX=g++
endif



CXXFLAGS=-Wall -Iext/ -D_GNU_SOURCE -fopenmp -std=c++11
ifeq ($(OS), Darwin)
	CXXFLAGS += -I/usr/local/include/cairo/ -L/usr/local/lib
endif

# OPTFLAGS=-I. -ggdb3 -Isrc/

OPTFLAGS= -O3 -DNDEBUG -ffast-math -mfpmath=sse -march=native -fexpensive-optimizations -fno-finite-math-only -I. -Isrc/
ifeq ($(OS), Linux)
	OPTFLAGS += -Wno-ignored-attributes -Wno-misleading-indentation
endif


LDFLAGS=-lm

HEADERS=\
src/lenssystem.h\
src/poly.h\
src/raytrace_draw.h\
src/raytrace.h\
src/gencode.h\
src/spectrum.h

.PHONY=all clean



ifeq ($(OS), Darwin)
    all: view fit gencode genpoly printpoly lenstable-to-json
endif
ifeq ($(OS), Linux)
    all: fit gencode genpoly printpoly lenstable-to-json
endif



ifeq ($(OS), Darwin)
view: Makefile src/view.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/view.c $(shell pkg-config --cflags --libs gtk+-2.0) ${LDFLAGS} -o bin/view ${LDFLAGS}
endif

lenstable-to-json: Makefile src/lenstable-to-json.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/lenstable-to-json.cpp -o bin/lenstable-to-json ${LDFLAGS}

fit: Makefile src/fit.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/fit.c -o bin/fit ${LDFLAGS}

genpoly: Makefile src/genpoly.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/genpoly.c -o bin/genpoly ${LDFLAGS}

parsepoly: Makefile src/parsepoly.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/parsepoly.c -o bin/parsepoly ${LDFLAGS}

printpoly: Makefile src/printpoly.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/printpoly.c -o bin/printpoly ${LDFLAGS}

gencode: Makefile src/gencode.c ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/gencode.c -o bin/gencode ${LDFLAGS}

#lt-aperture-sampling: Makefile src/sample_ap_lt.c init.h lt_sample_aperture.h ${HEADERS}
#	${CXX} ${OPTFLAGS} ${CXXFLAGS} -Irender/${lensname} src/sample_ap_lt.c -o bin/lt-aperture-sampling ${LDFLAGS}
	
#glRender: Makefile src/render_gl.c
#	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/render_gl.c ${LDFLAGS} -o bin/glRender -lGLEW -lGL -lGLU -lglfw


ifeq ($(OS), Darwin)
clean: rm -f view fit gencode genpoly printpoly lenstable_to_json #lt_convergence.dat lt_convergence_profile.dat lt-aperture-sampling
endif
ifeq ($(OS), Linux)
clean: rm -f fit gencode genpoly printpoly lenstable_to_json #lt_convergence.dat lt_convergence_profile.dat lt-aperture-sampling
endif