#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#include "common.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    FILE *plik = fopen(FILENAME, "rb");
    if (!plik) {
        perror("Nie można otworzyć pliku");
        MPI_Finalize();
        return 1;
    }

    int *liczby = malloc(INT_COUNT * sizeof(int));
    int n = 0;
    while (fread(&liczby[n], sizeof(int), 1, plik) == 1) n++;
    fclose(plik);

    double start = MPI_Wtime();  // START pomiaru
    int lokalne_pierwsze = 0;

    for (int i = rank; i < n; i += size) {
        if (czy_pierwsza(liczby[i])) {
            lokalne_pierwsze++;
        }
    }

    int globalne_pierwsze = 0;
    MPI_Reduce(&lokalne_pierwsze, &globalne_pierwsze, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    double end = MPI_Wtime();  // KONIEC pomiaru

    if (rank == 0) {
        printf("Znaleziono %d liczb pierwszych.\n", globalne_pierwsze);
        printf_time(end - start);
    }

    free(liczby);
    MPI_Finalize();
    return 0;
}
