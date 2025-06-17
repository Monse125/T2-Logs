# Tarea 2 - Algoritmo de Kruskal
## CC4102 - Diseño y Análisis de Algoritmos

Este proyecto implementa y compara 4 variaciones del algoritmo de Kruskal para encontrar el árbol de expansión mínimo de un grafo.

## Estructura del proyecto
```
include/          - Archivos de cabecera (.hpp)
src/             - Implementaciones (.cpp)  
main.cpp         - Programa principal para experimentos
results.csv      - Resultados de los experimentos (generado automáticamente)
```

## Compilación

### Prerrequisitos
- Compilador C++ compatible con C++17 (g++, clang++)
- Make (GNU Make)
- Sistema operativo: Linux/macOS/Windows

### Comandos de compilación

**Usando Makefile (recomendado):**
```bash
# Compilar ambos ejecutables
make

# Ver todos los comandos disponibles
make help
```

**Compilación manual:**
```bash
# Para el experimento completo
g++ -std=c++17 -O2 -I./include main.cpp src/*.cpp -o kruskal_experiment

# Para pruebas simples
g++ -std=c++17 -O2 -I./include main_simple.cpp src/*.cpp -o kruskal_test
```

## Ejecución

**Usando Makefile (recomendado):**
```bash
# Ejecutar experimento completo (compila automáticamente si es necesario)
make run-experiment

# Ejecutar prueba simple
make run-test

# Verificar que todo esté en orden
make check
```

**Ejecución manual:**
```bash
# Ejecutar experimento completo (puede tomar varios minutos)
./kruskal_experiment

# Prueba simple
./kruskal_test
```

## Implementaciones

El proyecto incluye 4 variaciones de Kruskal:

1. **Sorted + Optimizado**: Arreglo ordenado + Union-Find con compresión de caminos
2. **Sorted + Raw**: Arreglo ordenado + Union-Find básico
3. **Heap + Optimizado**: Min-heap + Union-Find con compresión de caminos  
4. **Heap + Raw**: Min-heap + Union-Find básico

## Resultados

Los tiempos se guardan en `results.csv` con el formato:
```
NumNodes,SortedOptim_ms,SortedRaw_ms,HeapOptim_ms,HeapRaw_ms
32,0.125,0.189,0.143,0.201
64,0.456,0.678,0.512,0.734
...
```

### Comandos útiles del Makefile

```bash
make                  # Compilar ambos ejecutables
make run-experiment   # Compilar y ejecutar experimento completo
make run-test        # Compilar y ejecutar prueba simple
make clean           # Limpiar archivos compilados
make rebuild         # Limpiar y recompilar todo
make info            # Mostrar información del proyecto
make check           # Verificar estructura del proyecto
make dist            # Crear archivo de distribución para entrega
make help            # Ver todos los comandos disponibles
```

## Salida del programa

El experimento completo genera:
- Progreso por consola para cada tamaño N ∈ {2^5, 2^6, ..., 2^12}
- Archivo `results.csv` con todos los tiempos medidos
- Tabla resumen al final

## Autores
[Agregar nombres del equipo aquí]