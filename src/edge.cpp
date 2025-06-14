#include "edge.h"
#include <cmath>

Edge::Edge(Node* node1, Node* node2) : u(node1), v(node2) {
    // Calcula el peso como el cuadrado de la distancia euclidiana
    double dx = node1->x - node2->x;
    double dy = node1->y - node2->y;
    weight = dx * dx + dy * dy;
}

bool Edge::operator<(const Edge& other) const {
    return weight < other.weight;
}
