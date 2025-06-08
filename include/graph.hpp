#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "geometry.hpp"

class Graph {
public:
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    Graph(int N);  // Constructor que genera nodos aleatorios y crea todas las aristas
};

#endif