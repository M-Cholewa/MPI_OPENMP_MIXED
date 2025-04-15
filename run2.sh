#!/bin/bash

BINARY_DIR="./binary"
PROGRAMS=("openmp_pierwsze" "mpi_pierwsze" "hybryda_pierwsze" "sekwencyjnie_pierwsze")
PROCESSES=( 1 2 4 8 16 )
THREADS=( 1 2 4 8 16 )

echo "🔁 Uruchamianie wszystkich wersji z katalogu $BINARY_DIR"
echo

for prog in "${PROGRAMS[@]}"
do
    bin_path="$BINARY_DIR/$prog"
    if [[ -f "$bin_path" ]]; then
        echo "🚀 Uruchamianie: $prog"
        echo "----------------------------"
        
            if [[ "$prog" == "mpi_"* || "$prog" == "hybryda_"* ]]; then
                mpirun "$bin_path"
            else
                "$bin_path"
            fi
        
        echo   # pusty wiersz
    else
        echo "❌ Nie znaleziono pliku: $bin_path"
    fi
done
