OS := $(shell uname)
ifeq ($(OS), Darwin)
	CXX=clang++
endif
ifeq ($(OS), Linux)
	CXX=g++
endif


CXXFLAGS = -Wall -D_GNU_SOURCE -fopenmp -std=c++17 -DFMT_HEADER_ONLY
CXXFLAGS += -I/usr/local/include/cairo/ -L/usr/local/lib
OPTFLAGS = -DNDEBUG -ffast-math -mfpmath=sse -march=native -fno-finite-math-only -fexpensive-optimizations -I. -Isrc/
#OPTFLAGS += -g #debug symbols
OPTFLAGS += -O3
LDFLAGS = -lm

HEADERS=\
src/lenssystem.h\
src/poly.h\
src/raytrace_draw.h\
src/raytrace.h\
src/gencode.h\
src/spectrum.h

.PHONY=all clean

all: \
	view \
	create-public-json \
	calculate-fstop \
	generate-lens-defines \
	calculate-infinity-focus-lens-offset \
	calculate-focal-length \
	fit \
	gencode \
	genpoly \
	printpoly \
	print-lens-path \
	add-fitted-focal-length

view: Makefile src/view.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/view.cpp $(shell pkg-config --cflags --libs gtk+-3.0) ${LDFLAGS} -o bin/view ${LDFLAGS}

print-lens-path: Makefile src/print-lens-path.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/print-lens-path.cpp -o bin/print-lens-path ${LDFLAGS}

calculate-fstop: Makefile src/calculate-fstop.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/calculate-fstop.cpp -o bin/calculate-fstop ${LDFLAGS}

create-public-json: Makefile src/create-public-json.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/create-public-json.cpp -o bin/create-public-json ${LDFLAGS}

add-fitted-focal-length: Makefile src/add-fitted-focal-length.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/add-fitted-focal-length.cpp -o bin/add-fitted-focal-length ${LDFLAGS}

generate-lens-defines: Makefile src/generate-lens-defines.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/generate-lens-defines.cpp -o bin/generate-lens-defines ${LDFLAGS}

calculate-infinity-focus-lens-offset: Makefile src/calculate-infinity-focus-lens-offset.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/calculate-infinity-focus-lens-offset.cpp -o bin/calculate-infinity-focus-lens-offset ${LDFLAGS}

calculate-focal-length: Makefile src/calculate-focal-length.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/calculate-focal-length.cpp -o bin/calculate-focal-length ${LDFLAGS}

fit: Makefile src/fit.c ${HEADERS} ext/ProgressBar.hpp
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

clean: rm -f view view create-public-json calculate-fstop calculate-focal-length calculate-infinity-focus-lens-offset fit gencode genpoly printpoly print-lens-path add-fitted-focal-length generate-lens-defines #lt_convergence.dat lt_convergence_profile.dat lt-aperture-sampling
