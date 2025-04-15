CC = gcc
MPICC = mpicc

CFLAGS = -Wall -O2
OMPFLAGS = -fopenmp

TARGETS = sekwencyjnie_pierwsze openmp_pierwsze mpi_pierwsze hybryda_pierwsze
INCLUDE_DIR = Include
SRC_DIR = Src
BINARY_DIR = ./binary

all: $(TARGETS)

sekwencyjnie_pierwsze: $(SRC_DIR)/sekwencyjnie_pierwsze.c
	$(CC) $(CFLAGS) $^ -o $(BINARY_DIR)/$@ -lm -I$(INCLUDE_DIR)

openmp_pierwsze: $(SRC_DIR)/openmp_pierwsze.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $(BINARY_DIR)/$@ -lm -I$(INCLUDE_DIR)

mpi_pierwsze: $(SRC_DIR)/mpi_pierwsze.c
	$(MPICC) $(CFLAGS) $^ -o $(BINARY_DIR)/$@ -lm -I$(INCLUDE_DIR)

hybryda_pierwsze: $(SRC_DIR)/hybryda_pierwsze.c
	$(MPICC) $(CFLAGS) $(OMPFLAGS) $^ -o $(BINARY_DIR)/$@ -lm -I$(INCLUDE_DIR)

clean:
	rm -r $(BINARY_DIR)/*

rebuild: clean all