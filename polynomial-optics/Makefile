# it is assumed linux doesn't have cairomm installed, so src/view cannot be compiled

OS := $(shell uname)
ifeq ($(OS), Darwin)
	CXX=clang++
endif
ifeq ($(OS), Linux)
	CXX=g++
endif



CXXFLAGS=-Wall -D_GNU_SOURCE -fopenmp -std=c++11 -DFMT_HEADER_ONLY
ifeq ($(OS), Darwin)
	CXXFLAGS += -I/usr/local/include/cairo/ -L/usr/local/lib
endif

# OPTFLAGS=-I. -ggdb3 -Isrc/

#OPTFLAGS= -ffast-math -mfpmath=sse -march=native -fexpensive-optimizations -fno-finite-math-only -I. -Isrc/
OPTFLAGS= -O3 -DNDEBUG -ffast-math -mfpmath=sse -march=native -fno-finite-math-only -I. -Isrc/
ifeq ($(OS), Linux)
	OPTFLAGS += -Wno-ignored-attributes -Wno-misleading-indentation
endif

#debug symbols for debugging with gdb
OPTFLAGS += -g

LDFLAGS = -lm

HEADERS=\
src/lenssystem.h\
src/poly.h\
src/raytrace_draw.h\
src/raytrace.h\
src/gencode.h\
src/spectrum.h

.PHONY=all clean


#all: view


#ifeq ("draw","true")
ifeq ($(OS), Darwin)
    all: \
	view \
	create-public-json \
	calculate-fstop \
	calculate-infinity-focus-lens-offset \
	calculate-focal-length \
	fit \
	gencode \
	genpoly \
	printpoly \
	print-lens-path \
	add-fitted-focal-length \
	generate-lens-defines
endif
ifeq ($(OS), Linux)
    all: \
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
endif
#endif


ifeq ($(OS), Darwin)
view: Makefile src/view.cpp ${HEADERS}
	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/view.cpp $(shell pkg-config --cflags --libs gtk+-3.0) ${LDFLAGS} -o bin/view ${LDFLAGS}
endif

#ifeq ("draw","true")
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
#endif

#lt-aperture-sampling: Makefile src/sample_ap_lt.c init.h lt_sample_aperture.h ${HEADERS}
#	${CXX} ${OPTFLAGS} ${CXXFLAGS} -Irender/${lensname} src/sample_ap_lt.c -o bin/lt-aperture-sampling ${LDFLAGS}
	
#glRender: Makefile src/render_gl.c
#	${CXX} ${OPTFLAGS} ${CXXFLAGS} src/render_gl.c ${LDFLAGS} -o bin/glRender -lGLEW -lGL -lGLU -lglfw


#clean: rm -f view
#ifeq ("draw","true")
ifeq ($(OS), Darwin)
clean: rm -f view view create-public-json calculate-fstop calculate-focal-length calculate-infinity-focus-lens-offset fit gencode genpoly printpoly print-lens-path add-fitted-focal-length generate-lens-defines #lt_convergence.dat lt_convergence_profile.dat lt-aperture-sampling
endif
ifeq ($(OS), Linux)
clean: rm -f view create-public-json calculate-fstop calculate-focal-length calculate-infinity-focus-lens-offset fit gencode genpoly printpoly print-lens-path add-fitted-focal-length generate-lens-defines #lt_convergence.dat lt_convergence_profile.dat lt-aperture-sampling
endif
#endif