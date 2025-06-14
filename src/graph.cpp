#include "graph.hpp"
#include <random>
#include <cmath>

/**
 * @brief Constructor que genera un grafo completo aleatorio
 * @param N Número de nodos del grafo
 * @return Estructura Graph completamente inicializada con nodos y aristas
 * 
 * Este constructor:
 * 1. Genera N nodos con coordenadas (x, y) aleatorias
 * 2. Crea todas las aristas posibles entre pares de nodos (grafo completo)
 * 3. Calcula el peso de cada arista como la distancia euclidiana al cuadrado
 * 4. Resulta en un grafo con N nodos y N*(N-1)/2 aristas
 * 
 * @note El grafo generado es no dirigido (cada par de nodos tiene una sola arista)
 * @note Las coordenadas se generan en el rango [0, 1]
 * @note El peso es la distancia euclidiana al cuadrado para evitar operaciones de raíz cuadrada
 */
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