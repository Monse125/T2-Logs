#include "kruskal_heap_optim.hpp"
#include "union_find_optim.hpp"
#include <queue>

/**
 * @brief Comparador personalizado para crear un min-heap de aristas
 * 
 * Este comparador invierte el orden natural de comparación para que
 * std::priority_queue funcione como min-heap en lugar de max-heap.
 */
struct EdgeComparator {
    /**
     * @brief Operador de comparación para min-heap
     * @param edgeA Primera arista a comparar
     * @param edgeB Segunda arista a comparar
     * @return true si edgeA tiene mayor peso que edgeB (para min-heap)
     */
    bool operator()(const Edge& edgeA, const Edge& edgeB) const {
        return edgeA.weight > edgeB.weight;  // Para min-heap: el mayor tiene menor prioridad
    }
};

/**
 * @brief Implementación optimizada del algoritmo de Kruskal usando heap y Union-Find
 * @param graph Grafo de entrada con nodos y aristas
 * @return Vector de aristas que forman el árbol de expansión mínimo
 * 
 * Esta implementación utiliza:
 * - Un min-heap (priority_queue) para ordenar aristas por peso
 * - Union-Find con optimizaciones (compresión de caminos y unión por rango)
 * - Selección greedy de aristas de menor peso que no formen ciclos
 * 
 * @complexity Tiempo: O(E log E + E α(V)) donde α es la función inversa de Ackermann
 * @complexity Espacio: O(E + V)
 */
std::vector<Edge> kruskalHeapOptim(const Graph& graph) {
    int numNodes = graph.nodes.size();
    std::vector<Edge> mst;
    mst.reserve(numNodes - 1);

    // Min-heap usando comparador personalizado
    std::priority_queue<Edge, std::vector<Edge>, EdgeComparator> edgeHeap;
    
    // Agregar todas las aristas al heap
    for (const Edge& currentEdge : graph.edges) {
        edgeHeap.push(currentEdge);
    }

    UnionFindOptim unionFind(numNodes);

    while (!edgeHeap.empty() && mst.size() < static_cast<size_t>(numNodes - 1)) {
        Edge currentEdge = edgeHeap.top();
        edgeHeap.pop();

        if (unionFind.find(currentEdge.from) != unionFind.find(currentEdge.to)) {
            unionFind.unite(currentEdge.from, currentEdge.to);
            mst.push_back(currentEdge);
        }
    }

    return mst;
}