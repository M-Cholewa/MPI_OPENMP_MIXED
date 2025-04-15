#!/bin/bash

BINARY_DIR="./binary"
PROGRAMS=("openmp_pierwsze" "mpi_pierwsze" "hybryda_pierwsze" "sekwencyjnie_pierwsze")
PROCESSES=( 1 2 4 8 16 )
THREADS=( 1 2 4 8 16 )

echo "🔁 Uruchamianie wszystkich wersji z katalogu $BINARY_DIR"
echo
ile=3

for prog in "${PROGRAMS[@]}"
do
    bin_path="$BINARY_DIR/$prog"
    if [[ -f "$bin_path" ]]; then
        echo "🚀 Uruchamianie: $prog"
        echo "----------------------------"

        suma=0

        for ((i=0; i<ile; i++)); do
            echo "Uruchamianie $prog, iteracja $((i+1)) z $ile"

            if [[ "$prog" == "mpi_"* || "$prog" == "hybryda_"* ]]; then
                output=$(mpirun "$bin_path")
            else
                output=$("$bin_path")
            fi

            echo "$output"
            wynik=$(echo "$output" | grep "Czas wykonania" | awk '{print $3}')
            suma=$(echo "$suma + $wynik" | bc)
        done

        srednia=$(echo "scale=3; $suma / $ile" | bc)
        echo "Średnia: $srednia"
        

        
        echo   # pusty wiersz
    else
        echo "❌ Nie znaleziono pliku: $bin_path"
    fi
done
