#include "graph_generator.h"
#include <random>

std::vector<Node*> generatePoints(int n, int seed) {
    std::vector<Node*> points;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    
    for (int i = 0; i < n; i++) {
        double x = dis(gen);
        double y = dis(gen);
        points.push_back(new Node(x, y));
    }
    
    return points;
}

std::vector<Edge> generateEdges(const std::vector<Node*>& points) {
    std::vector<Edge> edges;
    int n = points.size();
    
    // Genera todas las combinaciones de pares de puntos
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.emplace_back(points[i], points[j]);
        }
    }
    
    return edges;
}

void resetUnionFind(std::vector<Node*>& points) {
    for (Node* node : points) {
        node->parent = node;
        node->rank = 1;
    }
}
