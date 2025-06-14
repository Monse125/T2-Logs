#!/usr/bin/env python3
"""
Script para analizar y graficar los resultados de los experimentos de Kruskal
"""

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

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
    
    return pd.DataFrame(data, columns=['N', 'Sorted+Opt', 'Heap+Opt', 'Sorted-Opt', 'Heap-Opt'])

def create_plots(df):
    """
    Crea gráficos comparativos de los resultados
    """
    plt.figure(figsize=(15, 10))
    
    # Gráfico 1: Comparación de todas las variantes
    plt.subplot(2, 2, 1)
    plt.plot(df['N'], df['Sorted+Opt'], 'b-o', label='Sorted Array + Optimización', linewidth=2)
    plt.plot(df['N'], df['Heap+Opt'], 'r-s', label='Heap + Optimización', linewidth=2)
    plt.plot(df['N'], df['Sorted-Opt'], 'g-^', label='Sorted Array - Optimización', linewidth=2)
    plt.plot(df['N'], df['Heap-Opt'], 'm-d', label='Heap - Optimización', linewidth=2)
    plt.xlabel('Número de nodos (N)')
    plt.ylabel('Tiempo de ejecución (μs)')
    plt.title('Comparación de las 4 variantes de Kruskal')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xscale('log', base=2)
    plt.yscale('log')
    
    # Gráfico 2: Efecto de la optimización en sorted array
    plt.subplot(2, 2, 2)
    plt.plot(df['N'], df['Sorted+Opt'], 'b-o', label='Con optimización', linewidth=2)
    plt.plot(df['N'], df['Sorted-Opt'], 'r-s', label='Sin optimización', linewidth=2)
    plt.xlabel('Número de nodos (N)')
    plt.ylabel('Tiempo de ejecución (μs)')
    plt.title('Efecto de la optimización - Sorted Array')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xscale('log', base=2)
    plt.yscale('log')
    
    # Gráfico 3: Efecto de la optimización en heap
    plt.subplot(2, 2, 3)
    plt.plot(df['N'], df['Heap+Opt'], 'b-o', label='Con optimización', linewidth=2)
    plt.plot(df['N'], df['Heap-Opt'], 'r-s', label='Sin optimización', linewidth=2)
    plt.xlabel('Número de nodos (N)')
    plt.ylabel('Tiempo de ejecución (μs)')
    plt.title('Efecto de la optimización - Heap')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xscale('log', base=2)
    plt.yscale('log')
    
    # Gráfico 4: Comparación entre estructuras de datos
    plt.subplot(2, 2, 4)
    plt.plot(df['N'], df['Sorted+Opt'], 'b-o', label='Sorted Array', linewidth=2)
    plt.plot(df['N'], df['Heap+Opt'], 'r-s', label='Heap', linewidth=2)
    plt.xlabel('Número de nodos (N)')
    plt.ylabel('Tiempo de ejecución (μs)')
    plt.title('Comparación de estructuras (con optimización)')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xscale('log', base=2)
    plt.yscale('log')
    
    plt.tight_layout()
    plt.savefig('kruskal_results.png', dpi=300, bbox_inches='tight')
    plt.show()

def print_analysis(df):
    """
    Imprime un análisis básico de los resultados
    """
    print("=== ANÁLISIS DE RESULTADOS ===\n")
    
    print("Datos experimentales:")
    print(df.to_string(index=False))
    print()
    
    # Calcular speedup de la optimización
    print("Speedup de la optimización:")
    sorted_speedup = df['Sorted-Opt'] / df['Sorted+Opt']
    heap_speedup = df['Heap-Opt'] / df['Heap+Opt']
    
    print(f"Sorted Array - Promedio: {sorted_speedup.mean():.2f}x")
    print(f"Heap - Promedio: {heap_speedup.mean():.2f}x")
    print()
    
    # Comparar estructuras de datos
    print("Comparación de estructuras (con optimización):")
    for i, row in df.iterrows():
        n = row['N']
        if row['Sorted+Opt'] < row['Heap+Opt']:
            faster = "Sorted Array"
            ratio = row['Heap+Opt'] / row['Sorted+Opt']
        else:
            faster = "Heap"
            ratio = row['Sorted+Opt'] / row['Heap+Opt']
        print(f"N={n}: {faster} es {ratio:.2f}x más rápido")

if __name__ == "__main__":
    try:
        df = read_results('results.txt')
        print_analysis(df)
        create_plots(df)
        print("\nGráfico guardado como 'kruskal_results.png'")
    except FileNotFoundError:
        print("Error: No se encontró el archivo 'results.txt'")
        print("Ejecuta primero el programa C++ para generar los datos.")
    except Exception as e:
        print(f"Error: {e}")
