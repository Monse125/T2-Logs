#include "union_find_optim.hpp"

/**
 * @brief Constructor de la estructura Union-Find optimizada
 * @param numNodes Número de nodos en la estructura
 * 
 * Inicializa cada nodo como su propio padre (componente individual)
 * y todos los tamaños en 1.
 */
UnionFindOptim::UnionFindOptim(int numNodes) : parent(numNodes), size(numNodes, 1) {
    for (int nodeIndex = 0; nodeIndex < numNodes; ++nodeIndex)
        parent[nodeIndex] = nodeIndex;
}

/**
 * @brief Encuentra el representante de la componente conexa del nodo (optimizado)
 * @param node Nodo del cual encontrar el representante
 * @return Índice del nodo representante de la componente
 * 
 * Implementación CON compresión de caminos: todos los nodos en el camino
 * hacia la raíz se conectan directamente a la raíz para optimizar
 * futuras consultas.
 * 
 * @complexity Tiempo: O(α(n)) amortizado, donde α es la función inversa de Ackermann
 */
int UnionFindOptim::find(int node) {
    if (parent[node] != node)
        parent[node] = find(parent[node]);  // CON compresión de caminos
    return parent[node];
}

/**
 * @brief Une dos componentes conexas en una sola (optimizado)
 * @param nodeA Primer nodo a unir
 * @param nodeB Segundo nodo a unir
 * 
 * Utiliza unión por tamaño: la componente más pequeña se conecta
 * a la más grande para mantener árboles balanceados.
 * Combinado con compresión de caminos, garantiza operaciones eficientes.
 * 
 * @complexity Tiempo: O(α(n)) amortizado, donde α es la función inversa de Ackermann
 */
void UnionFindOptim::unite(int nodeA, int nodeB) {
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