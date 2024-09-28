## -*- mode: makefile -*-

##
## This file is part of the Score-P software (http://www.score-p.org)
##
## Copyright (c) 2014, 2023,
## Technische Universitaet Dresden, Germany
##
## This software may be modified and distributed under the terms of
## a BSD-style license.  See the COPYING file in the package base
## directory for details.
##

CC     = gcc
MPICC  = mpicc
MPICXX = mpic++

CFLAGS = -g -O2

OPENMP_CFLAGS  = -fopenmp
PTHREAD_CFLAGS = -pthread

OTF2_CFLAGS  = `otf2-config --cflags`
OTF2_LDFLAGS = `otf2-config --ldflags`
OTF2_LIBS    = `otf2-config --libs`

ALL_SERIAL = \
    otf2_reader_example \
    otf2_writer_example

ALL_MPI = \
    otf2_mpi_reader_example \
    otf2_mpi_reader_example_cc \
    otf2_mpi_writer_example

ALL_OPENMP = \
    otf2_openmp_reader_example \
    otf2_openmp_writer_example

ALL_PTHREAD = \
    otf2_pthread_writer_example

all: $(ALL_SERIAL) $(ALL_MPI) $(ALL_OPENMP) $(ALL_PTHREAD)

serial: $(ALL_SERIAL)

mpi: $(ALL_MPI)

openmp: $(ALL_OPENMP)

pthread: $(ALL_PTHREAD)

otf2_reader_example.o: otf2_reader_example.c
	$(CC) $(CFLAGS) $(OTF2_CFLAGS) -c otf2_reader_example.c -o otf2_reader_example.o

otf2_reader_example: otf2_reader_example.o
	$(CC) $(CFLAGS) otf2_reader_example.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_reader_example

otf2_writer_example.o: otf2_writer_example.c
	$(CC) $(CFLAGS) $(OTF2_CFLAGS) -c otf2_writer_example.c -o otf2_writer_example.o

otf2_writer_example: otf2_writer_example.o
	$(CC) $(CFLAGS) otf2_writer_example.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_writer_example

otf2_mpi_reader_example.o: otf2_mpi_reader_example.c
	$(MPICC) $(CFLAGS) $(OTF2_CFLAGS) -c otf2_mpi_reader_example.c -o otf2_mpi_reader_example.o

otf2_mpi_reader_example: otf2_mpi_reader_example.o
	$(MPICC) $(CFLAGS) otf2_mpi_reader_example.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_mpi_reader_example

otf2_mpi_reader_example_cc.o: otf2_mpi_reader_example.cc
	$(MPICXX) $(OTF2_CFLAGS) -c otf2_mpi_reader_example.cc -o otf2_mpi_reader_example_cc.o

otf2_mpi_reader_example_cc: otf2_mpi_reader_example_cc.o
	$(MPICXX) otf2_mpi_reader_example_cc.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_mpi_reader_example_cc

otf2_mpi_writer_example.o: otf2_mpi_writer_example.c
	$(MPICC) $(CFLAGS) $(OTF2_CFLAGS) -c otf2_mpi_writer_example.c -o otf2_mpi_writer_example.o

otf2_mpi_writer_example: otf2_mpi_writer_example.o
	$(MPICC) $(CFLAGS) otf2_mpi_writer_example.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_mpi_writer_example

otf2_openmp_writer_example.o: otf2_openmp_writer_example.c
	$(CC) $(CFLAGS) $(OPENMP_CFLAGS) $(OTF2_CFLAGS) -c otf2_openmp_writer_example.c -o otf2_openmp_writer_example.o

otf2_openmp_writer_example: otf2_openmp_writer_example.o
	$(CC) $(CFLAGS) $(OPENMP_CFLAGS) otf2_openmp_writer_example.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_openmp_writer_example

otf2_openmp_reader_example.o: otf2_openmp_reader_example.c
	$(CC) $(CFLAGS) $(OPENMP_CFLAGS) $(OTF2_CFLAGS) -c otf2_openmp_reader_example.c -o otf2_openmp_reader_example.o

otf2_openmp_reader_example: otf2_openmp_reader_example.o
	$(CC) $(CFLAGS) $(OPENMP_CFLAGS) otf2_openmp_reader_example.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_openmp_reader_example

otf2_pthread_writer_example.o: otf2_pthread_writer_example.c
	$(CC) $(CFLAGS) $(PTHREAD_CFLAGS) $(OTF2_CFLAGS) -c otf2_pthread_writer_example.c -o otf2_pthread_writer_example.o

otf2_pthread_writer_example: otf2_pthread_writer_example.o
	$(CC) $(CFLAGS) $(PTHREAD_CFLAGS) otf2_pthread_writer_example.o $(OTF2_LDFLAGS) $(OTF2_LIBS) -o otf2_pthread_writer_example

clean:
	$(RM) $(ALL) $(ALL_MPI) $(ALL_OPENMP) $(ALL_PTHREAD) *.o
