#include "union_find_raw.hpp"

UnionFindRaw::UnionFindRaw(int n) : parent(n) {
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int UnionFindRaw::find(int u) {
    // Sin compresión de caminos - solo sigue el camino hasta la raíz
    while (parent[u] != u) {
        u = parent[u];
    }
    return u;
}

void UnionFindRaw::unite(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return;
    
    // Sin unión por tamaño - simplemente conecta pu a pv
    parent[pu] = pv;
}