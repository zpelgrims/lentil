# LENS=double-gauss-1930
# LENS=double-gauss-angenieux
# LENS=wideangle-1971
# LENS=fisheye-aspherical
# LENS=canon-anamorphic
LENS=petzval
CC=gcc
CFLAGS=-D_GNU_SOURCE -std=c11 -Wall -g -I ../render/ -I../render/${LENS}
# OPTFLAGS=-ggdb3
OPTFLAGS=-O3 -march=native

all: plot.pdf

plot.pdf: Makefile plot.plt points.dat
	gnuplot plot.plt

points.dat: Makefile connect
	./connect

connect: Makefile connect.c convexhull.h
	$(CC) $(CFLAGS) $(OPTFLAGS) connect.c -o connect -lm

clean:
	rm -f connect points.dat plot.pdf
