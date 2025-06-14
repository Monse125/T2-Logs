#include "graph.hpp"
#include "kruskal_sorted_optim.hpp"
#include "kruskal_sorted_raw.hpp"
#include "kruskal_heap_optim.hpp"
#include "kruskal_heap_raw.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <vector>
#include <cmath>

struct ExperimentResult {
    int numNodes;
    double sortedOptimTime;
    double sortedRawTime;
    double heapOptimTime;
    double heapRawTime;
};


/*
Flujo del experimento:
main.cpp
│
├─ Para cada tamaño N ∈ {25, 26, ..., 212}:
│   ├─ Repetir 5 veces:
│   │   ├─ Generar grafo aleatorio completo (Graph g)
│   │   ├─ Ejecutar kruskal_sorted_optim(g) y medir tiempo
│   │   ├─ Ejecutar kruskal_heap_optim(g) y medir tiempo
│   │   ├─ Ejecutar kruskal_sorted_raw(g) y medir tiempo
│   │   ├─ Ejecutar kruskal_heap_raw(g) y medir tiempo
│   │   └─ Guardar resultados en estructura local
│   └─ Calcular promedios y guardar en archivo CSV o similar
│
└─ Final: Graficar o procesar resultados

*/


int main() {
    std::cout << "=== INICIANDO EXPERIMENTO COMPLETO DE KRUSKAL ===\n";
    std::cout << "Midiendo tiempos para N ∈ {2^5, 2^6, ..., 2^12}\n";
    std::cout << "5 repeticiones por cada tamaño\n\n";

    std::vector<ExperimentResult> results;
    
    // Para cada tamaño N ∈ {2^5, 2^6, ..., 2^12}
    for (int exponent = 5; exponent <= 12; ++exponent) {
        int numNodes = static_cast<int>(std::pow(2, exponent));
        
        std::cout << "Probando con N = 2^" << exponent << " = " << numNodes << " nodos...\n";
        
        // Acumuladores para promedios
        double totalSortedOptimTime = 0.0;
        double totalSortedRawTime = 0.0;
        double totalHeapOptimTime = 0.0;
        double totalHeapRawTime = 0.0;
        
        // Repetir 5 veces para cada tamaño
        for (int iteration = 1; iteration <= 5; ++iteration) {
            std::cout << "  Iteración " << iteration << "/5...";
            
            // Generar grafo aleatorio completo
            Graph testGraph(numNodes);
            
            // Variables para medir tiempo
            auto startTime = std::chrono::high_resolution_clock::now();
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            
            // ==================== Kruskal Sorted + Union-Find Optimizado ====================
            startTime = std::chrono::high_resolution_clock::now();
            std::vector<Edge> mstSortedOptim = kruskalSortedOptim(testGraph);
            endTime = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            double sortedOptimTime = duration.count() / 1000.0; // convertir a milisegundos
            totalSortedOptimTime += sortedOptimTime;
            
            // ==================== Kruskal Sorted + Union-Find Raw ====================
            startTime = std::chrono::high_resolution_clock::now();
            std::vector<Edge> mstSortedRaw = kruskalSortedRaw(testGraph);
            endTime = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            double sortedRawTime = duration.count() / 1000.0; // convertir a milisegundos
            totalSortedRawTime += sortedRawTime;
            
            // ==================== Kruskal Heap + Union-Find Optimizado ====================
            startTime = std::chrono::high_resolution_clock::now();
            std::vector<Edge> mstHeapOptim = kruskalHeapOptim(testGraph);
            endTime = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            double heapOptimTime = duration.count() / 1000.0; // convertir a milisegundos
            totalHeapOptimTime += heapOptimTime;
            
            // ==================== Kruskal Heap + Union-Find Raw ====================
            startTime = std::chrono::high_resolution_clock::now();
            std::vector<Edge> mstHeapRaw = kruskalHeapRaw(testGraph);
            endTime = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            double heapRawTime = duration.count() / 1000.0; // convertir a milisegundos
            totalHeapRawTime += heapRawTime;
            
            // Verificación rápida (solo en la primera iteración)
            if (iteration == 1) {
                double weight1 = 0, weight2 = 0, weight3 = 0, weight4 = 0;
                for (const Edge& edge : mstSortedOptim) weight1 += edge.weight;
                for (const Edge& edge : mstSortedRaw) weight2 += edge.weight;
                for (const Edge& edge : mstHeapOptim) weight3 += edge.weight;
                for (const Edge& edge : mstHeapRaw) weight4 += edge.weight;
                
                if (std::abs(weight1 - weight2) > 1e-6 || std::abs(weight2 - weight3) > 1e-6 || 
                    std::abs(weight3 - weight4) > 1e-6) {
                    std::cout << " ❌ ERROR: Pesos diferentes!\n";
                    return 1;
                }
            }
            
            std::cout << " ✅\n";
        }
        
        // Calcular promedios
        ExperimentResult result;
        result.numNodes = numNodes;
        result.sortedOptimTime = totalSortedOptimTime / 5.0;
        result.sortedRawTime = totalSortedRawTime / 5.0;
        result.heapOptimTime = totalHeapOptimTime / 5.0;
        result.heapRawTime = totalHeapRawTime / 5.0;
        
        results.push_back(result);
        
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "  Promedios (ms): Sorted-Optim=" << result.sortedOptimTime 
                  << ", Sorted-Raw=" << result.sortedRawTime
                  << ", Heap-Optim=" << result.heapOptimTime
                  << ", Heap-Raw=" << result.heapRawTime << "\n\n";
    }
    
    // ==================== Guardar resultados en CSV ====================
    std::cout << "Guardando resultados en 'results.csv'...\n";
    
    std::ofstream csvFile("results.csv");
    csvFile << "NumNodes,SortedOptim_ms,SortedRaw_ms,HeapOptim_ms,HeapRaw_ms\n";
    
    for (const ExperimentResult& result : results) {
        csvFile << std::fixed << std::setprecision(6);
        csvFile << result.numNodes << ","
                << result.sortedOptimTime << ","
                << result.sortedRawTime << ","
                << result.heapOptimTime << ","
                << result.heapRawTime << "\n";
    }
    
    csvFile.close();
    
    // ==================== Mostrar resumen final ====================
    std::cout << "\n=== RESUMEN FINAL ===\n";
    std::cout << std::setw(10) << "N" 
              << std::setw(15) << "Sorted-Optim" 
              << std::setw(15) << "Sorted-Raw" 
              << std::setw(15) << "Heap-Optim" 
              << std::setw(15) << "Heap-Raw" << "\n";
    std::cout << std::string(70, '-') << "\n";
    
    for (const ExperimentResult& result : results) {
        std::cout << std::fixed << std::setprecision(3);
        std::cout << std::setw(10) << result.numNodes
                  << std::setw(15) << result.sortedOptimTime
                  << std::setw(15) << result.sortedRawTime
                  << std::setw(15) << result.heapOptimTime
                  << std::setw(15) << result.heapRawTime << "\n";
    }
    
    std::cout << "\n=== EXPERIMENTO COMPLETADO ===\n";
    std::cout << "Archivo 'results.csv' generado para análisis posterior.\n";
    
    return 0;
}