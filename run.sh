#!/bin/bash

BINARY_DIR="./binary"
PROGRAMS=("openmp_pierwsze" "mpi_pierwsze" "hybryda_pierwsze")
ROZMIARY_DANYCH=(4000000 8000000 16000000 32000000 64000000)
WATKI_PROCESY=(1 2 4 8 12 16)

echo "🔁 Benchmark: wszystkie wersje z różnymi rozmiarami i konfiguracjami"
echo

for prog in "${PROGRAMS[@]}"
do
    bin_path="$BINARY_DIR/$prog"
    if [[ -f "$bin_path" ]]; then
        echo "🚀 Program: $prog"
        echo "----------------------------"
        
        for rozmiar in "${ROZMIARY_DANYCH[@]}"
        do
            for p in "${WATKI_PROCESY[@]}"
            do
                echo "▶️  $prog | Rozmiar: $rozmiar | Procesy/Wątki: $p"

                if [[ "$prog" == "openmp_pierwsze" ]]; then
                    "$bin_path" $rozmiar $p

                elif [[ "$prog" == "mpi_pierwsze" ]]; then
                    mpirun -np $p "$bin_path" $rozmiar

                elif [[ "$prog" == "hybryda_pierwsze" ]]; then
                    mpirun -np $p "$bin_path" $rozmiar $p
                fi

                echo   # pusty wiersz
            done
        done

        echo "============================"
        echo
    else
        echo "❌ Nie znaleziono pliku: $bin_path"
    fi
done
