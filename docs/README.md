# Tarea 2 - Algoritmo de Kruskal

## Descripción
Implementación y comparación de 4 variantes del algoritmo de Kruskal para encontrar el árbol cobertor mínimo de un grafo.

## Estructura del Proyecto
```
T2-Logs/
├── src/                 # Código fuente
│   ├── main.cpp         # Programa principal modular
│   ├── main_original.cpp # Versión original (un archivo)
│   ├── analyzer.cpp     # Analizador de resultados
│   ├── node.cpp         # Implementación de nodos
│   ├── edge.cpp         # Implementación de aristas
│   ├── union_find.cpp   # Estructura Union-Find
│   ├── graph_generator.cpp # Generador de grafos
│   ├── kruskal.cpp      # Algoritmos de Kruskal
│   └── experiment.cpp   # Sistema de experimentación
├── include/             # Headers
│   ├── node.h
│   ├── edge.h
│   ├── union_find.h
│   ├── graph_generator.h
│   ├── kruskal.h
│   └── experiment.h
├── build/               # Ejecutables compilados
├── data/                # Datos y resultados
├── scripts/             # Scripts de utilidad
│   ├── validate.sh      # Validación del proyecto
│   ├── run.sh          # Script de ejecución
│   └── analyze_*.py    # Scripts de análisis
├── docs/                # Documentación
│   ├── README.md        # Este archivo
│   ├── EXPERIMENTO.md   # Análisis detallado
│   ├── ENTREGA.md       # Información de entrega
│   └── *.pdf           # PDFs del curso
└── Makefile            # Sistema de compilación
```

## Variantes Implementadas
1. **Kruskal con optimización de find + arreglo ordenado**
2. **Kruskal con optimización de find + heap**
3. **Kruskal sin optimización de find + arreglo ordenado**
4. **Kruskal sin optimización de find + heap**

## Requisitos
- **Compilador**: g++ con soporte C++11 o superior
- **Sistema**: Linux/Unix (probado en Debian)
- **Opcional**: Python3 + matplotlib para gráficos

## Instrucciones de Uso

### Compilación y Ejecución Rápida
```bash
# Compilar, ejecutar y analizar (recomendado)
make experiment

# Ver ayuda completa
make help
```

### Comandos Individuales
```bash
# Compilar versión modular
make

# Compilar versión original (un archivo)
make original

# Ejecutar solo experimentos
make run

# Analizar resultados existentes
make analyze

# Validar proyecto completo
make validate

# Limpiar archivos generados
make clean
```

## Características Técnicas

### Arquitectura Modular
- **Separación clara** de responsabilidades
- **Headers independientes** para cada módulo
- **Compilación incremental** optimizada
- **Fácil mantenimiento** y extensión

### Implementación Union-Find
- **Con optimización**: Compresión de caminos en find()
- **Sin optimización**: Find tradicional subiendo por padres
- **Union by rank**: Árbol pequeño se une al grande

### Estructuras de Extracción
- **Arreglo ordenado**: `std::sort()` + acceso secuencial
- **Heap**: `std::priority_queue` con min-heap personalizado

### Sistema de Medición
- **Alta precisión**: `chrono::high_resolution_clock`
- **Promedios estadísticos**: 5 ejecuciones por configuración
- **Resultados reproducibles**: Semillas fijas para aleatoriedad

## Resultados Principales

### Rendimiento por Estructura
- **Heap 1.5x-2.5x más rápido** que arreglo ordenado
- **Escalabilidad**: Factor ~4.5x al duplicar N
- **Complejidad**: Consistente con O(n² log n)

### Efecto de la Optimización Union-Find
- **Resultado inesperado**: No mostró mejoras significativas
- **Explicación**: Grafos completos + overhead de compresión
- **Lección**: Importancia de validación experimental

## Archivos de Salida

### data/results.txt
```
N	Sorted+Opt	Heap+Opt	Sorted-Opt	Heap-Opt
32	23		12		18		11
64	116		57		95		64
...
```

### Análisis Automático
- Tablas comparativas
- Cálculos de speedup
- Observaciones teóricas
- Conclusiones prácticas

## Validación y Pruebas

### Correctitud
- **Prueba automática** con grafo conocido
- **Validación cruzada**: Las 4 variantes producen el mismo MST
- **Verificación**: ✓ Todas las implementaciones correctas

### Rendimiento
- **Benchmarks reproducibles**
- **Medición precisa** con alta resolución
- **Control de variables** (semillas, repeticiones)

## Mantenimiento

### Agregar Nueva Variante
1. Implementar función en `src/kruskal.cpp`
2. Declarar en `include/kruskal.h`
3. Actualizar `src/experiment.cpp`
4. Recompilar con `make`

### Modificar Experimentación
1. Editar parámetros en `src/experiment.cpp`
2. Ajustar rangos de N o repeticiones
3. Recompilar y ejecutar `make experiment`

## Notas Técnicas
- **Sin warnings**: Compila limpio con `-Wall`
- **Optimización**: Flag `-O2` para rendimiento
- **Memoria segura**: Delete explícito, sin leaks
- **Portable**: Usa solo librerías estándar C++

## Limitaciones
- **Memoria**: Limitado para N > 4096 en sistemas pequeños
- **Tiempo**: Experimentos completos toman varios minutos
- **Plataforma**: Optimizado para sistemas Unix/Linux

## Autor
Implementación para CC4102 - Diseño y Análisis de Algoritmos
Estructura modular y sistema de build profesional
