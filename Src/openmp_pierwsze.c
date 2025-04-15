#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "common.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Użycie: %s <liczba_intów> <liczba_wątków>\n", argv[0]);
        return 1;
    }

    int liczba_intow = atoi(argv[1]);
    int liczba_watkow = atoi(argv[2]);

    if (liczba_intow <= 0 || liczba_watkow <= 0) {
        fprintf(stderr, "Podano nieprawidłowe argumenty: %s %s\n", argv[1], argv[2]);
        return 1;
    }

    FILE *plik = fopen(FILENAME, "rb");
    if (!plik) {
        perror("Nie można otworzyć pliku");
        return 1;
    }

    int *liczby = malloc(liczba_intow * sizeof(int));
    int n = fread(liczby, sizeof(int), liczba_intow, plik);
    fclose(plik);

    omp_set_num_threads(liczba_watkow);

    double start = omp_get_wtime();  // START pomiaru
    int licznik_pierwszych = 0;

    #pragma omp parallel for reduction(+:licznik_pierwszych)
    for (int i = 0; i < n; i++) {
        if (czy_pierwsza(liczby[i])) {
            licznik_pierwszych++;
        }
    }

    double end = omp_get_wtime();  // KONIEC pomiaru
    printf("Znaleziono %d liczb pierwszych.\n", licznik_pierwszych);
    printf_time(end - start);

    free(liczby);
    return 0;
}
