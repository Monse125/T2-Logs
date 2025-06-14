#include "experiment.h"
#include "kruskal.h"
#include "graph_generator.h"
#include <iostream>
#include <fstream>
#include <cmath>

void runExperiments(int n, std::vector<std::vector<long long>>& results) {
    std::cout << "Ejecutando experimentos para n = " << n << std::endl;
    
    // 4 variantes: [sorted/heap] x [with/without optimization]
    std::vector<long long> times(4, 0);
    
    // Ejecuta 5 repeticiones para cada tamaño
    for (int rep = 0; rep < 5; rep++) {
        std::vector<Node*> points = generatePoints(n, 12345 + rep);
        std::vector<Edge> edges = generateEdges(points);
        
        // Variante 1: Sorted array con optimización
        times[0] += measureTime([&]() {
            kruskalSortedArray(points, edges, true);
        });
        
        // Variante 2: Heap con optimización
        times[1] += measureTime([&]() {
            kruskalHeap(points, edges, true);
        });
        
        // Variante 3: Sorted array sin optimización
        times[2] += measureTime([&]() {
            kruskalSortedArray(points, edges, false);
        });
        
        // Variante 4: Heap sin optimización
        times[3] += measureTime([&]() {
            kruskalHeap(points, edges, false);
        });
        
        // Libera memoria
        for (Node* node : points) {
            delete node;
        }
    }
    
    // Calcula promedios
    for (int i = 0; i < 4; i++) {
        times[i] /= 5;
    }
    
    results.push_back(times);
}

void runQuickTest() {
    std::cout << "=== PRUEBA RÁPIDA ===" << std::endl;
    
    // Prueba con un grafo pequeño conocido
    std::vector<Node*> testPoints = {
        new Node(0.0, 0.0),
        new Node(1.0, 0.0),
        new Node(0.5, 1.0)
    };
    
    std::vector<Edge> testEdges = generateEdges(testPoints);
    
    std::cout << "Puntos de prueba:" << std::endl;
    for (size_t i = 0; i < testPoints.size(); i++) {
        std::cout << "  P" << i << ": (" << testPoints[i]->x << ", " << testPoints[i]->y << ")" << std::endl;
    }
    
    std::cout << "Aristas y pesos:" << std::endl;
    for (size_t i = 0; i < testEdges.size(); i++) {
        std::cout << "  E" << i << ": peso = " << testEdges[i].weight << std::endl;
    }
    
    // Ejecutar las 4 variantes
    double result1 = kruskalSortedArray(testPoints, testEdges, true);
    double result2 = kruskalHeap(testPoints, testEdges, true);
    double result3 = kruskalSortedArray(testPoints, testEdges, false);
    double result4 = kruskalHeap(testPoints, testEdges, false);
    
    std::cout << "Resultados (peso total del MST):" << std::endl;
    std::cout << "  Sorted + Opt: " << result1 << std::endl;
    std::cout << "  Heap + Opt:   " << result2 << std::endl;
    std::cout << "  Sorted - Opt: " << result3 << std::endl;
    std::cout << "  Heap - Opt:   " << result4 << std::endl;
    
    // Verificar que todos den el mismo resultado
    if (std::abs(result1 - result2) < 1e-9 && std::abs(result1 - result3) < 1e-9 && std::abs(result1 - result4) < 1e-9) {
        std::cout << "✓ Todas las variantes producen el mismo resultado" << std::endl;
    } else {
        std::cout << "✗ ERROR: Las variantes producen resultados diferentes" << std::endl;
    }
    
    // Liberar memoria
    for (Node* node : testPoints) {
        delete node;
    }
    
    std::cout << std::endl;
}

void saveResults(const std::vector<std::vector<long long>>& results) {
    std::ofstream file("results.txt");
    
    file << "# Resultados de los experimentos con Kruskal" << std::endl;
    file << "# Columnas: N, Sorted+Opt, Heap+Opt, Sorted-Opt, Heap-Opt" << std::endl;
    file << "# Tiempos en microsegundos (promedio de 5 ejecuciones)" << std::endl;
    
    for (size_t i = 0; i < results.size(); i++) {
        int n = 1 << (i + 5);  // 2^(i+5)
        file << n;
        for (int j = 0; j < 4; j++) {
            file << "\t" << results[i][j];
        }
        file << std::endl;
    }
    
    file.close();
    std::cout << "Resultados guardados en results.txt" << std::endl;
}
