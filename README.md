# Tarea 2 - Algoritmo de Kruskal

## Descripción
Implementación y comparación de 4 variantes del algoritmo de Kruskal para encontrar el árbol cobertor mínimo de un grafo.

## Variantes implementadas
1. **Kruskal con optimización de find + arreglo ordenado**
2. **Kruskal con optimización de find + heap**
3. **Kruskal sin optimización de find + arreglo ordenado**
4. **Kruskal sin optimización de find + heap**

## Estructura del proyecto
- `main.cpp`: Implementación principal con las 4 variantes
- `analyzer.cpp`: Analizador de resultados en C++
- `analyze_results.py`: Analizador con gráficos (requiere matplotlib)
- `README.md`: Este archivo con instrucciones
- `Makefile`: Automatización de compilación y ejecución
- `EXPERIMENTO.md`: Análisis detallado de resultados
- `results.txt`: Datos experimentales generados

## Requisitos
- **Compilador**: g++ con soporte C++11 o superior
- **Sistema**: Linux/Unix (probado en Debian)
- **Opcional**: Python3 + matplotlib para gráficos

## Instrucciones de Ejecución

### Opción 1: Uso del Makefile (Recomendado)
```bash
# Compilar ambos programas
make

# Ejecutar experimento completo (compilar + ejecutar + analizar)
make experiment

# Solo ejecutar los experimentos
make run

# Solo analizar resultados existentes
make analyze

# Limpiar archivos generados
make clean

# Ver ayuda
make help
```

### Opción 2: Compilación manual
```bash
# Compilar programa principal
g++ -std=c++11 -O2 -o kruskal main.cpp

# Compilar analizador
g++ -std=c++11 -O2 -o analyzer analyzer.cpp

# Ejecutar experimentos
./kruskal

# Analizar resultados
./analyzer
```

## Funcionamiento

### Generación de datos
- Genera 5 secuencias de N puntos para cada N ∈ {2^5, 2^6, ..., 2^12}
- Puntos aleatorios en el plano [0,1] × [0,1]
- Calcula N(N-1)/2 aristas con peso = distancia euclidiana²

### Medición de tiempos
- Usa `chrono::high_resolution_clock` para alta precisión
- Promedia 5 ejecuciones por cada configuración
- Resultados en microsegundos

### Implementación Union-Find
- **Con optimización**: Compresión de caminos en find()
- **Sin optimización**: Find tradicional subiendo por padres
- Union by rank: árbol pequeño se une al grande

### Estructuras de extracción
- **Arreglo ordenado**: `std::sort()` + acceso secuencial
- **Heap**: `std::priority_queue` con min-heap personalizado

## Resultados Principales

### Rendimiento por estructura
- **Heap consistentemente 1.5x-2.5x más rápido** que arreglo ordenado
- Para N=4096: Heap ~600ms vs Sorted ~1000ms

### Efecto de la optimización Union-Find
- **Resultado inesperado**: Optimización no mostró mejoras significativas
- Promedio ~0.93x (ligeramente peor en algunos casos)
- Explicación: Grafos completos + overhead de compresión

### Escalabilidad
- Factor de crecimiento ~4.5x al duplicar N
- Consistente con complejidad O(n² log n)

## Archivos de Salida

### results.txt
Formato: `N Sorted+Opt Heap+Opt Sorted-Opt Heap-Opt`
```
32	23	12	18	11
64	116	57	95	64
...
```

### EXPERIMENTO.md
Análisis detallado con:
- Tablas de resultados
- Interpretación de datos
- Conclusiones teóricas y prácticas

## Verificación de Correctitud
- Prueba automática con grafo pequeño conocido
- Todas las variantes producen el mismo peso de MST
- Validación: ✓ Implementación correcta

## Notas Técnicas
- Compila sin warnings con `-Wall`
- Optimización `-O2` para rendimiento
- Manejo seguro de memoria (delete explícito)
- Medición precisa con alta resolución temporal

## Limitaciones Conocidas
- Gráficos requieren Python + matplotlib (no disponible en entorno actual)
- Experimentos pueden tomar varios minutos para N grandes
- Memoria limitada para N > 4096

## Autor
Implementación para CC4102 - Diseño y Análisis de Algoritmos
