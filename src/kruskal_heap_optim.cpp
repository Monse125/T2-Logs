#include "kruskal_heap_optim.hpp"
#include "union_find_optim.hpp"
#include <queue>

// Comparador personalizado para min-heap
struct EdgeComparator {
    bool operator()(const Edge& edgeA, const Edge& edgeB) const {
        return edgeA.weight > edgeB.weight;  // Para min-heap: el mayor tiene menor prioridad
    }
};

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