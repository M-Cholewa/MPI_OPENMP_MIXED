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

    if (argc < 2) {
        if (rank == 0)
            fprintf(stderr, "Użycie: %s <liczba_intów_do_wczytania>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int liczba_intow = atoi(argv[1]);
    if (liczba_intow <= 0) {
        if (rank == 0)
            fprintf(stderr, "Podano niepoprawną liczbę: %s\n", argv[1]);
        MPI_Finalize();
        return 1;
    }

    FILE *plik = fopen(FILENAME, "rb");
    if (!plik) {
        perror("Nie można otworzyć pliku");
        MPI_Finalize();
        return 1;
    }

    int *liczby = malloc(liczba_intow * sizeof(int));
    int n = fread(liczby, sizeof(int), liczba_intow, plik);
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
