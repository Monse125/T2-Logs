#include "kruskal_sorted_optim.hpp"
#include "union_find_optim.hpp"
#include <algorithm>

/**
 * @brief Implementación optimizada del algoritmo de Kruskal usando ordenamiento y Union-Find
 * @param graph Grafo de entrada con nodos y aristas
 * @return Vector de aristas que forman el árbol de expansión mínimo
 * 
 * Esta implementación utiliza:
 * - Ordenamiento completo de todas las aristas por peso (std::sort)
 * - Union-Find CON optimizaciones (compresión de caminos y unión por rango)
 * - Selección greedy de aristas en orden ascendente de peso
 * 
 * @complexity Tiempo: O(E log E + E α(V)) donde α es la función inversa de Ackermann
 * @complexity Espacio: O(E + V)
 * @note El ordenamiento inicial domina la complejidad temporal
 */
std::vector<Edge> kruskalSortedOptim(const Graph& graph) {
    int numNodes = graph.nodes.size();
    std::vector<Edge> mst;
    mst.reserve(numNodes - 1);

    // Copia de las aristas para ordenar
    std::vector<Edge> sortedEdges = graph.edges;
    std::sort(sortedEdges.begin(), sortedEdges.end());

    UnionFindOptim unionFind(numNodes);

    for (const Edge& currentEdge : sortedEdges) {
        if (unionFind.find(currentEdge.from) != unionFind.find(currentEdge.to)) {
            unionFind.unite(currentEdge.from, currentEdge.to);
            mst.push_back(currentEdge);
            if (mst.size() == static_cast<size_t>(numNodes - 1))
                break;  // árbol de expansión mínimo completo
        }
    }

    return mst;
}