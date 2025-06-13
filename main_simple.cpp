#include "graph.hpp"
#include "kruskal_sorted_optim.hpp"
#include "kruskal_sorted_raw.hpp"
#include "kruskal_heap_optim.hpp"
#include "kruskal_heap_raw.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

int main() {
    int N = 32;  // 2^5 = 32 nodos para prueba
    Graph g(N);

    std::cout << "=== PRUEBA DE LAS 4 IMPLEMENTACIONES DE KRUSKAL ===\n";
    std::cout << "Grafo generado con " << g.nodes.size() << " nodos y " << g.edges.size() << " aristas.\n\n";

    // Variables para medir tiempo
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << std::fixed << std::setprecision(4);

    // ==================== PRUEBA 1: Kruskal Sorted + Union-Find Optimizado ====================
    std::cout << "1. Kruskal Ordenado + Union-Find Optimizado:\n";
    start = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mst1 = kruskalSortedOptim(g);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double weight1 = 0;
    for (const Edge& e : mst1) weight1 += e.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mst1.size() << "\n";
    std::cout << "   Peso total: " << weight1 << "\n\n";

    // ==================== PRUEBA 2: Kruskal Sorted + Union-Find Raw ====================
    std::cout << "2. Kruskal Ordenado + Union-Find Sin Optimizar:\n";
    start = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mst2 = kruskalSortedRaw(g);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double weight2 = 0;
    for (const Edge& e : mst2) weight2 += e.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mst2.size() << "\n";
    std::cout << "   Peso total: " << weight2 << "\n\n";

    // ==================== PRUEBA 3: Kruskal Heap + Union-Find Optimizado ====================
    std::cout << "3. Kruskal Heap + Union-Find Optimizado:\n";
    start = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mst3 = kruskalHeapOptim(g);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double weight3 = 0;
    for (const Edge& e : mst3) weight3 += e.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mst3.size() << "\n";
    std::cout << "   Peso total: " << weight3 << "\n\n";

    // ==================== PRUEBA 4: Kruskal Heap + Union-Find Raw ====================
    std::cout << "4. Kruskal Heap + Union-Find Sin Optimizar:\n";
    start = std::chrono::high_resolution_clock::now();
    std::vector<Edge> mst4 = kruskalHeapRaw(g);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double weight4 = 0;
    for (const Edge& e : mst4) weight4 += e.weight;
    
    std::cout << "   Tiempo: " << duration.count() << " μs\n";
    std::cout << "   Aristas MST: " << mst4.size() << "\n";
    std::cout << "   Peso total: " << weight4 << "\n\n";

    // ==================== VERIFICACIÓN ====================
    std::cout << "=== VERIFICACIÓN ===\n";
    std::cout << "¿Todos los MST tienen el mismo peso? ";
    if (weight1 == weight2 && weight2 == weight3 && weight3 == weight4) {
        std::cout << "✅ SÍ - Todas las implementaciones son correctas\n";
    } else {
        std::cout << "❌ NO - Hay diferencias entre implementaciones\n";
        std::cout << "Pesos: " << weight1 << ", " << weight2 << ", " << weight3 << ", " << weight4 << "\n";
    }

    std::cout << "¿Todos los MST tienen " << (N-1) << " aristas? ";
    if (mst1.size() == N-1 && mst2.size() == N-1 && mst3.size() == N-1 && mst4.size() == N-1) {
        std::cout << "✅ SÍ\n";
    } else {
        std::cout << "❌ NO\n";
    }

    std::cout << "\n=== PRUEBA COMPLETADA ===\n";
    return 0;
}