#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "node.h"

/**
 * Clase que implementa la estructura Union-Find
 * Permite verificar si dos nodos están en el mismo componente conexo
 */
class UnionFind {
public:
    /**
     * Encuentra la raíz del árbol que contiene al nodo dado
     * @param node Nodo del cual encontrar la raíz
     * @param useOptimization Si true, aplica compresión de caminos
     * @return Puntero a la raíz del árbol
     */
    Node* find(Node* node, bool useOptimization);
    
    /**
     * Une dos componentes conexos si están separados
     * @param root1 Raíz del primer componente
     * @param root2 Raíz del segundo componente
     * @return true si se realizó la unión, false si ya estaban unidos
     */
    bool unionSets(Node* root1, Node* root2);

private:
    /**
     * Find con compresión de caminos
     * Todos los nodos visitados apuntan directamente a la raíz
     */
    Node* findWithOptimization(Node* node);
    
    /**
     * Find sin optimización
     * Simplemente sube por los padres hasta encontrar la raíz
     */
    Node* findWithoutOptimization(Node* node);
};

#endif
