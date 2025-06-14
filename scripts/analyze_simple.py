#!/usr/bin/env python3
"""
Script para analizar los resultados de los experimentos de Kruskal (sin gráficos)
"""

def read_results(filename):
    """
    Lee los resultados del archivo generado por el programa C++
    """
    data = []
    with open(filename, 'r') as f:
        for line in f:
            if line.startswith('#'):
                continue
            values = line.strip().split('\t')
            if len(values) == 5:
                n = int(values[0])
                times = [int(values[i]) for i in range(1, 5)]
                data.append([n] + times)
    
    return data

def print_analysis(data):
    """
    Imprime un análisis básico de los resultados
    """
    print("=== ANÁLISIS DE RESULTADOS ===\n")
    
    print("Datos experimentales:")
    print("N\tSorted+Opt\tHeap+Opt\tSorted-Opt\tHeap-Opt")
    print("-" * 60)
    for row in data:
        print(f"{row[0]}\t{row[1]}\t\t{row[2]}\t\t{row[3]}\t\t{row[4]}")
    print()
    
    # Calcular speedup de la optimización
    print("Speedup de la optimización:")
    sorted_speedups = []
    heap_speedups = []
    
    for row in data:
        n, sorted_opt, heap_opt, sorted_noopt, heap_noopt = row
        sorted_speedup = sorted_noopt / sorted_opt if sorted_opt > 0 else 0
        heap_speedup = heap_noopt / heap_opt if heap_opt > 0 else 0
        sorted_speedups.append(sorted_speedup)
        heap_speedups.append(heap_speedup)
        print(f"N={n}: Sorted {sorted_speedup:.2f}x, Heap {heap_speedup:.2f}x")
    
    sorted_avg = sum(sorted_speedups) / len(sorted_speedups)
    heap_avg = sum(heap_speedups) / len(heap_speedups)
    print(f"\nPromedio - Sorted Array: {sorted_avg:.2f}x")
    print(f"Promedio - Heap: {heap_avg:.2f}x")
    print()
    
    # Comparar estructuras de datos
    print("Comparación de estructuras (con optimización):")
    for row in data:
        n, sorted_opt, heap_opt, _, _ = row
        if sorted_opt < heap_opt:
            faster = "Sorted Array"
            ratio = heap_opt / sorted_opt
        else:
            faster = "Heap"
            ratio = sorted_opt / heap_opt
        print(f"N={n}: {faster} es {ratio:.2f}x más rápido")
    
    print()
    print("Comparación de estructuras (sin optimización):")
    for row in data:
        n, _, _, sorted_noopt, heap_noopt = row
        if sorted_noopt < heap_noopt:
            faster = "Sorted Array"
            ratio = heap_noopt / sorted_noopt
        else:
            faster = "Heap"
            ratio = sorted_noopt / heap_noopt
        print(f"N={n}: {faster} es {ratio:.2f}x más rápido")
    
    print()
    print("=== OBSERVACIONES ===")
    
    # Análisis de complejidad
    print("1. Efecto de la optimización Union-Find:")
    if sorted_avg > 1:
        print(f"   - La compresión de caminos mejora el rendimiento en promedio {sorted_avg:.1f}x para sorted array")
    if heap_avg > 1:
        print(f"   - La compresión de caminos mejora el rendimiento en promedio {heap_avg:.1f}x para heap")
    
    print("\n2. Comparación de estructuras de datos:")
    sorted_wins = sum(1 for row in data if row[1] < row[2])  # sorted_opt < heap_opt
    heap_wins = len(data) - sorted_wins
    
    if sorted_wins > heap_wins:
        print("   - El arreglo ordenado tiende a ser más rápido que el heap")
    elif heap_wins > sorted_wins:
        print("   - El heap tiende a ser más rápido que el arreglo ordenado")
    else:
        print("   - Ambas estructuras tienen rendimiento similar")
    
    print(f"   - Sorted Array gana en {sorted_wins}/{len(data)} casos")
    print(f"   - Heap gana en {heap_wins}/{len(data)} casos")
    
    print("\n3. Escalabilidad:")
    if len(data) >= 2:
        first_ratio = data[1][1] / data[0][1] if data[0][1] > 0 else 0
        last_ratio = data[-1][1] / data[-2][1] if data[-2][1] > 0 else 0
        print(f"   - Factor de crecimiento inicial: {first_ratio:.1f}x")
        print(f"   - Factor de crecimiento final: {last_ratio:.1f}x")

if __name__ == "__main__":
    try:
        data = read_results('results.txt')
        if data:
            print_analysis(data)
        else:
            print("No se encontraron datos válidos en results.txt")
    except FileNotFoundError:
        print("Error: No se encontró el archivo 'results.txt'")
        print("Ejecuta primero el programa C++ para generar los datos.")
    except Exception as e:
        print(f"Error: {e}")
