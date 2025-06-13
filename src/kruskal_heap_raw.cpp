#include "kruskal_heap_raw.hpp"
#include "union_find_raw.hpp"
#include <queue>
#include <functional>  // std::greater

std::vector<Edge> kruskalHeapRaw(const Graph& g) {
    int n = g.nodes.size();
    std::vector<Edge> mst;
    mst.reserve(n - 1);

    // Min-heap usando priority_queue con comparador greater
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;
    
    // Agregar todas las aristas al heap
    for (const Edge& e : g.edges) {
        heap.push(e);
    }

    UnionFindRaw dsu(n);

    while (!heap.empty() && mst.size() < static_cast<size_t>(n - 1)) {
        Edge e = heap.top();
        heap.pop();

        if (dsu.find(e.from) != dsu.find(e.to)) {
            dsu.unite(e.from, e.to);
            mst.push_back(e);
        }
    }

    return mst;
}