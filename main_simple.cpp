#include "graph.hpp"
#include "kruskal_sorted_optim.hpp"
#include "kruskal_sorted_raw.hpp"
#include "kruskal_heap_optim.hpp"
#include "kruskal_heap_raw.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

int main() {
    int numNodes = 32;  // 2^5 = 32 nodos para prueba
    Graph testGraph(numNodes);

    std::cout << "=== PRUEBA DE LAS 4 IMPLEMENTACIONES DE KRUSKAL ===\n";
    std::cout << "Grafo generado con " << testGraph.nodes.size() << " nodos y " << testGraph.edges.size() << " aristas.\n\n";

    // Variables para medir tiempo
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    std::cout << std::fixed << std::setprecision(4);

    // ==================== PRUEBA 1: Kruskal Sorted + Union-Find Optimizado ====================
    std::cout << "1. Kruskal Ordenado + Union-Find Optimizado:\n";
    startTime = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mstSortedOptim = kruskalSortedOptim(testGraph);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    
    double weightSortedOptim = 0;
    for (const Edge& edge : mstSortedOptim) weightSortedOptim += edge.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mstSortedOptim.size() << "\n";
    std::cout << "   Peso total: " << weightSortedOptim << "\n\n";

    // ==================== PRUEBA 2: Kruskal Sorted + Union-Find Raw ====================
    std::cout << "2. Kruskal Ordenado + Union-Find Sin Optimizar:\n";
    startTime = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mstSortedRaw = kruskalSortedRaw(testGraph);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    
    double weightSortedRaw = 0;
    for (const Edge& edge : mstSortedRaw) weightSortedRaw += edge.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mstSortedRaw.size() << "\n";
    std::cout << "   Peso total: " << weightSortedRaw << "\n\n";

    // ==================== PRUEBA 3: Kruskal Heap + Union-Find Optimizado ====================
    std::cout << "3. Kruskal Heap + Union-Find Optimizado:\n";
    startTime = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mstHeapOptim = kruskalHeapOptim(testGraph);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    
    double weightHeapOptim = 0;
    for (const Edge& edge : mstHeapOptim) weightHeapOptim += edge.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mstHeapOptim.size() << "\n";
    std::cout << "   Peso total: " << weightHeapOptim << "\n\n";

    // ==================== PRUEBA 4: Kruskal Heap + Union-Find Raw ====================
    std::cout << "4. Kruskal Heap + Union-Find Sin Optimizar:\n";
    startTime = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mstHeapRaw = kruskalHeapRaw(testGraph);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    
    double weightHeapRaw = 0;
    for (const Edge& edge : mstHeapRaw) weightHeapRaw += edge.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mstHeapRaw.size() << "\n";
    std::cout << "   Peso total: " << weightHeapRaw << "\n\n";

    // ==================== VERIFICACIÓN ====================
    std::cout << "=== VERIFICACIÓN ===\n";
    std::cout << "¿Todos los MST tienen el mismo peso? ";
    if (weightSortedOptim == weightSortedRaw && weightSortedRaw == weightHeapOptim && weightHeapOptim == weightHeapRaw) {
        std::cout << "✅ SÍ - Todas las implementaciones son correctas\n";
    } else {
        std::cout << "❌ NO - Hay diferencias entre implementaciones\n";
        std::cout << "Pesos: " << weightSortedOptim << ", " << weightSortedRaw << ", " << weightHeapOptim << ", " << weightHeapRaw << "\n";
    }

    std::cout << "¿Todos los MST tienen " << (numNodes-1) << " aristas? ";
    if (mstSortedOptim.size() == numNodes-1 && mstSortedRaw.size() == numNodes-1 && mstHeapOptim.size() == numNodes-1 && mstHeapRaw.size() == numNodes-1) {
        std::cout << "✅ SÍ\n";
    } else {
        std::cout << "❌ NO\n";
    }

    std::cout << "\n=== PRUEBA COMPLETADA ===\n";
    return 0;
}