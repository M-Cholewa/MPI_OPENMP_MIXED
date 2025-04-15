#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "common.h"

int main(int argc, char **argv) {
    FILE *plik = fopen(FILENAME, "rb");
    if (!plik) {
        perror("Nie można otworzyć pliku");
        return 1;
    }

    int *liczby = malloc(INT_COUNT * sizeof(int));
    int n = 0;
    while (fread(&liczby[n], sizeof(int), 1, plik) == 1) n++;
    fclose(plik);

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
