#pragma once
#include "stdbool.h"
#include "math.h"

#define INT_COUNT 50000000U
#define FILENAME "liczby_50_000_000.bin"


bool czy_pierwsza(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    int sqrt_n = (int)sqrt(n);
    for (int i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) 
        return false;
    }
    return true;
}


void printf_time(double time)
{
    printf("Czas wykonania: %.3f\n", time);
}