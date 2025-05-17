#!/bin/bash

BINARY_DIR="./binary"
ROZMIARY_DANYCH=(4000000 8000000 16000000 32000000 64000000)
WATKI_PROCESY=(1 2 4 8 12 16 32)

echo "🔁 Benchmark: wszystkie wersje z różnymi rozmiarami i konfiguracjami"
echo

# ---------- OpenMP ----------
echo "🚀 Program: openmp_pierwsze"
for rozmiar in "${ROZMIARY_DANYCH[@]}"
do
    for w in "${WATKI_PROCESY[@]}"; do
        echo "▶️  OpenMP | Rozmiar: $rozmiar | Wątki: $w"
        "$BINARY_DIR/openmp_pierwsze" $rozmiar $w
        echo
    done
done
echo "============================"
echo

# ---------- MPI ----------
echo "🚀 Program: mpi_pierwsze"
for rozmiar in "${ROZMIARY_DANYCH[@]}"
do
    for p in "${WATKI_PROCESY[@]}"; do
        echo "▶️  MPI | Rozmiar: $rozmiar | Procesy: $p"
        mpirun --oversubscribe -np $p "$BINARY_DIR/mpi_pierwsze" $rozmiar
        echo
    done
done
echo "============================"
echo

# ---------- Hybryda (2 i 4 procesy) ----------
for PROC in 2 4; do
    echo "🚀 Program: hybryda_pierwsze (procesów: $PROC)"
    for rozmiar in "${ROZMIARY_DANYCH[@]}"
    do
        for w in "${WATKI_PROCESY[@]}"; do
            TOTAL=$((PROC * w))
            if [ $TOTAL -le 32 ]; then
                echo "▶️  Hybryda | Rozmiar: $rozmiar | Procesy: $PROC | Wątki: $w (łącznie $TOTAL)"
                mpirun --oversubscribe -np $PROC "$BINARY_DIR/hybryda_pierwsze" $rozmiar $w
                echo
            fi
        done
    done
    echo "============================"
    echo
done
