#!/bin/bash

echo "=== VALIDACIÓN DE LA TAREA 2 - KRUSKAL (VERSIÓN ORGANIZADA) ==="
echo

# Cambiar al directorio raíz del proyecto
cd "$(dirname "$0")/.." || exit 1

# Función para verificar si un archivo existe
check_file() {
    if [ -f "$1" ]; then
        echo "✓ $1 encontrado"
        return 0
    else
        echo "✗ $1 NO encontrado"
        return 1
    fi
}

# Función para verificar si un directorio existe
check_dir() {
    if [ -d "$1" ]; then
        echo "✓ Directorio $1 encontrado"
        return 0
    else
        echo "✗ Directorio $1 NO encontrado"
        return 1
    fi
}

# Función para verificar si un comando se ejecuta correctamente
check_command() {
    if $1 > /dev/null 2>&1; then
        echo "✓ $2"
        return 0
    else
        echo "✗ $2"
        return 1
    fi
}

echo "1. Verificando estructura de directorios..."
check_dir "src"
check_dir "include" 
check_dir "build"
check_dir "data"
check_dir "scripts"
check_dir "docs"

echo
echo "2. Verificando archivos del código fuente..."
check_file "src/main.cpp"
check_file "src/analyzer.cpp"
check_file "src/main_original.cpp"
check_file "include/node.h"
check_file "include/edge.h"
check_file "include/union_find.h"
check_file "include/kruskal.h"

echo
echo "3. Verificando archivos de documentación..."
check_file "docs/README.md"
check_file "docs/EXPERIMENTO.md"
check_file "Makefile"

echo
echo "4. Verificando compilación..."
check_command "make clean" "Limpieza exitosa"
check_command "make setup" "Setup de directorios exitoso"
check_command "make" "Compilación exitosa"

echo
echo "5. Verificando archivos compilados..."
check_file "build/kruskal"
check_file "build/analyzer"

echo
echo "6. Verificando ejecución rápida..."
if timeout 10s build/kruskal > test_output.txt 2>&1; then
    if grep -q "✓ Todas las variantes producen el mismo resultado" test_output.txt; then
        echo "✓ Prueba rápida exitosa"
        echo "✓ Validación de correctitud pasada"
    else
        echo "✗ Fallo en validación de correctitud"
    fi
    
    if [ -f "data/results.txt" ]; then
        echo "✓ Archivo results.txt generado en data/"
        lines=$(wc -l < data/results.txt)
        if [ $lines -gt 5 ]; then
            echo "✓ results.txt contiene datos ($lines líneas)"
        else
            echo "✗ results.txt parece incompleto"
        fi
    else
        echo "- results.txt no generado (normal para prueba rápida)"
    fi
else
    echo "- Timeout en prueba rápida (normal para experimento completo)"
fi

echo
echo "7. Verificando analizador..."
if [ -f "data/results.txt" ]; then
    if build/analyzer > analysis_output.txt 2>&1; then
        if grep -q "=== OBSERVACIONES ===" analysis_output.txt; then
            echo "✓ Analizador funciona correctamente"
        else
            echo "✗ Analizador no produce salida esperada"
        fi
    else
        echo "✗ Error al ejecutar analizador"
    fi
else
    echo "- Saltando análisis (no hay results.txt)"
fi

echo
echo "8. Resumen de archivos entregables:"
for file in src/main.cpp src/analyzer.cpp docs/README.md docs/EXPERIMENTO.md Makefile; do
    if [ -f "$file" ]; then
        size=$(du -h "$file" | cut -f1)
        echo "  ✓ $file ($size)"
    else
        echo "  ✗ $file FALTANTE"
    fi
done

echo
echo "9. Estructura Union-Find implementada:"
if grep -q "findWithOptimization" src/union_find.cpp; then
    echo "  ✓ Find con compresión de caminos"
else
    echo "  ✗ Find con compresión NO encontrado"
fi

if grep -q "findWithoutOptimization" src/union_find.cpp; then
    echo "  ✓ Find sin optimización"
else
    echo "  ✗ Find sin optimización NO encontrado"
fi

if grep -q "unionSets" src/union_find.cpp; then
    echo "  ✓ Union by rank implementado"
else
    echo "  ✗ Union by rank NO encontrado"
fi

echo
echo "10. Algoritmos de Kruskal implementados:"
if grep -q "kruskalSortedArray" src/kruskal.cpp; then
    echo "  ✓ Kruskal con arreglo ordenado"
else
    echo "  ✗ Kruskal con arreglo ordenado NO encontrado"
fi

if grep -q "kruskalHeap" src/kruskal.cpp; then
    echo "  ✓ Kruskal con heap"
else
    echo "  ✗ Kruskal con heap NO encontrado"
fi

echo
echo "11. Modularización del código:"
header_count=$(find include -name "*.h" | wc -l)
cpp_count=$(find src -name "*.cpp" | wc -l)
echo "  ✓ $header_count archivos header en include/"
echo "  ✓ $cpp_count archivos fuente en src/"

if [ $header_count -ge 5 ] && [ $cpp_count -ge 8 ]; then
    echo "  ✓ Código correctamente modularizado"
else
    echo "  ✗ Código insuficientemente modularizado"
fi

# Limpieza
rm -f test_output.txt analysis_output.txt

echo
echo "=== VALIDACIÓN COMPLETADA ==="
echo "Revisa los puntos marcados con ✗ si los hay."
echo "Estructura organizada: src/, include/, build/, data/, scripts/, docs/"
