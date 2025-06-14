#!/bin/bash

echo "=== Compilando el programa ==="
g++ -std=c++11 -O2 -o kruskal main.cpp

if [ $? -eq 0 ]; then
    echo "Compilación exitosa"
    echo ""
    echo "=== Ejecutando experimentos ==="
    ./kruskal
else
    echo "Error en la compilación"
    exit 1
fi
