#include "union_find_raw.hpp"

/**
 * @brief Constructor de la estructura Union-Find sin optimizaciones
 * @param numNodes Número de nodos en la estructura
 * 
 * Inicializa cada nodo como su propio padre (componente individual)
 * y todos los tamaños en 1.
 */
UnionFindRaw::UnionFindRaw(int numNodes) : parent(numNodes), size(numNodes, 1) {
    for (int nodeIndex = 0; nodeIndex < numNodes; ++nodeIndex)
        parent[nodeIndex] = nodeIndex;
}

/**
 * @brief Encuentra el representante de la componente conexa del nodo
 * @param node Nodo del cual encontrar el representante
 * @return Índice del nodo representante de la componente
 * 
 * Implementación SIN compresión de caminos - solo sigue el camino
 * hasta la raíz sin optimizar para futuras consultas.
 * 
 * @complexity Tiempo: O(h) donde h es la altura del árbol (puede ser O(n) en el peor caso)
 */
int UnionFindRaw::find(int node) {
    // SIN compresión de caminos - solo sigue el camino hasta la raíz
    while (parent[node] != node) {
        node = parent[node];
    }
    return node;
}

/**
 * @brief Une dos componentes conexas en una sola
 * @param nodeA Primer nodo a unir
 * @param nodeB Segundo nodo a unir
 * 
 * Utiliza unión por tamaño: la componente más pequeña se conecta
 * a la más grande para mantener árboles balanceados.
 * 
 * @complexity Tiempo: O(h) donde h es la altura del árbol
 */
void UnionFindRaw::unite(int nodeA, int nodeB) {
    int rootA = find(nodeA);
    int rootB = find(nodeB);

    // Si ambos nodos apuntan a la misma raíz, se debe descartar la arista
    if (rootA == rootB) return;

    // CON unión por tamaño
    if (size[rootA] < size[rootB]) {
        parent[rootA] = rootB;
        size[rootB] += size[rootA];
    } else {
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
    }
}