#ifndef EDGE_H
#define EDGE_H

#include "node.h"

/**
 * Estructura que representa una arista entre dos nodos
 * Contiene punteros a los nodos y el peso de la arista
 */
struct Edge {
    Node* u;               // Primer nodo de la arista
    Node* v;               // Segundo nodo de la arista
    double weight;         // Peso de la arista (distancia euclidiana al cuadrado)
    
    /**
     * Constructor que crea una arista entre dos nodos
     * @param node1 Primer nodo
     * @param node2 Segundo nodo
     */
    Edge(Node* node1, Node* node2);
    
    /**
     * Operador de comparación para ordenar aristas por peso
     */
    bool operator<(const Edge& other) const;
};

/**
 * Comparador para el heap (priority queue) de aristas
 * Como priority_queue es un max-heap, invertimos la comparación
 */
struct EdgeComparator {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.weight > b.weight;  // Para obtener un min-heap
    }
};

#endif
