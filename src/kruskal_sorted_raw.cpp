#include "kruskal_sorted_raw.hpp"
#include "union_find_raw.hpp"
#include <algorithm>

std::vector<Edge> kruskalSortedRaw(const Graph& graph) {
    int numNodes = graph.nodes.size();
    std::vector<Edge> mst;
    mst.reserve(numNodes - 1);

    // Copia de las aristas para ordenar
    std::vector<Edge> sortedEdges = graph.edges;
    std::sort(sortedEdges.begin(), sortedEdges.end());

    UnionFindRaw unionFind(numNodes);

    for (const Edge& currentEdge : sortedEdges) {
        if (unionFind.find(currentEdge.from) != unionFind.find(currentEdge.to)) {
            unionFind.unite(currentEdge.from, currentEdge.to);
            mst.push_back(currentEdge);
            if (mst.size() == static_cast<size_t>(numNodes - 1))
                break;
        }
    }

    return mst;
}