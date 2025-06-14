#ifndef NODE_H
#define NODE_H

/**
 * Estructura que representa un nodo en el plano bidimensional
 * Contiene coordenadas (x,y) y información para Union-Find
 */
struct Node {
    double x, y;           // Coordenadas del punto
    Node* parent;          // Puntero al padre en la estructura Union-Find
    int rank;              // Rango del nodo para Union-Find (tamaño del árbol)
    
    /**
     * Constructor que inicializa un nodo con coordenadas dadas
     * @param x_coord Coordenada x del punto
     * @param y_coord Coordenada y del punto
     */
    Node(double x_coord, double y_coord);
};

#endif
