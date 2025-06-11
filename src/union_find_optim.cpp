#include "union_find.hpp"

UnionFindOptim::UnionFindOptim(int n) : parent(n), size(n, 1) {
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int UnionFindOptim::find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]);  // compresión de caminos
    return parent[u];
}

void UnionFindOptim::unite(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return;

    // unión por tamaño
    if (size[pu] < size[pv]) {
        parent[pu] = pv;
        size[pv] += size[pu];
    } else {
        parent[pv] = pu;
        size[pu] += size[pv];
    }
}