# This is the Makefile for 4 source files | cips.h  edge.c  imageio.c  medge.c

all: medge_parallel medge_serial

medge_parallel:
	gcc -fopenmp -o medge_parallel parallel_medge.c dep/imageio.c parallel_edge.c -Idep/

medge_serial:
	gcc -fopenmp -o medge_serial serial_medge.c dep/imageio.c serial_edge.c -Idep/

