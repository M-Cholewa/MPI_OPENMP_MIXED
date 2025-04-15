#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
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

    clock_t start = clock();  // START pomiaru
    int licznik_pierwszych = 0;

    for (int i = 0; i < n; i++) {
        if (czy_pierwsza(liczby[i])) {
            licznik_pierwszych++;
        }
    }

    clock_t end = clock();  // KONIEC pomiaru

    double czas_wykonania = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Znaleziono %d liczb pierwszych.\n", licznik_pierwszych);
    printf_time(czas_wykonania);

    return 0;
}
