#include "kruskal_sorted_optim.hpp"
#include "union_find_optim.hpp"  // Cambiar include
#include <algorithm>  // std::sort

std::vector<Edge> kruskalSortedOptim(const Graph& g) {
    int n = g.nodes.size();
    std::vector<Edge> mst;
    mst.reserve(n - 1);

    // Copia de las aristas para ordenar
    std::vector<Edge> edges = g.edges;
    std::sort(edges.begin(), edges.end());  // usa operador <

    UnionFindOptim dsu(n);

    for (const Edge& e : edges) {
        if (dsu.find(e.from) != dsu.find(e.to)) {
            dsu.unite(e.from, e.to);
            mst.push_back(e);
            if (mst.size() == static_cast<size_t>(n - 1))
                break;  // árbol de expansión mínimo completo
        }
    }

    return mst;
}