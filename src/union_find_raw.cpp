#include "union_find_raw.hpp"

UnionFindRaw::UnionFindRaw(int n) : parent(n), size(n, 1) {
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int UnionFindRaw::find(int u) {
    // SIN compresión de caminos - solo sigue el camino hasta la raíz
    while (parent[u] != u) {
        u = parent[u];
    }
    return u;
}

void UnionFindRaw::unite(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return;

    // CON unión por tamaño (igual que la versión optimizada)
    if (size[pu] < size[pv]) {
        parent[pu] = pv;
        size[pv] += size[pu];
    } else {
        parent[pv] = pu;
        size[pu] += size[pv];
    }
}