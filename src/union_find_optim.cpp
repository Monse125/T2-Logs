#include "union_find_optim.hpp"  // Cambiar include

UnionFindOptim::UnionFindOptim(int n) : parent(n), size(n, 1) {
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int UnionFindOptim::find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]);  // CON compresión de caminos
    return parent[u];
}

void UnionFindOptim::unite(int u, int v) {  // Cambiar UnionFindRaw por UnionFindOptim
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return;

    // CON unión por tamaño (igual que la versión raw)
    if (size[pu] < size[pv]) {
        parent[pu] = pv;
        size[pv] += size[pu];
    } else {
        parent[pv] = pu;
        size[pu] += size[pv];
    }
}