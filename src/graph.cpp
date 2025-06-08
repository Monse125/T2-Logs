#include "graph.hpp"
#include <random>
#include <cmath>

// Constructor que genera nodos y aristas completas
Graph::Graph(int N) {
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Generar N nodos aleatorios
    nodes.reserve(N);
    for (int i = 0; i < N; ++i) {
        nodes.push_back(Node{dist(rng), dist(rng)});
    }

    // Generar todas las aristas entre pares de nodos
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double dx = nodes[i].x - nodes[j].x;
            double dy = nodes[i].y - nodes[j].y;
            double weight = dx * dx + dy * dy;
            edges.push_back(Edge{i, j, weight});
        }
    }
}