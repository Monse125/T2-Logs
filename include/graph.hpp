#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "geometry.hpp"


/**
 * @class Graph
 * @brief Representa un grafo completo con nodos posicionados aleatoriamente en un plano 2D
 * 
 * Esta clase genera automáticamente un grafo completo donde:
 * - Los nodos se posicionan aleatoriamente en coordenadas 2D
 * - Se crean todas las aristas posibles entre todos los pares de nodos
 * - El peso de cada arista corresponde a la distancia euclidiana entre los nodos
 * 
 */

class Graph {
public:
    std::vector<Node> nodes; ///< Vector de nodos con coordenadas (x, y) aleatorias
    std::vector<Edge> edges; ///< Vector de todas las aristas del grafo completo

    Graph(int N);  // Constructor que genera nodos aleatorios y crea todas las aristas
};

#endif