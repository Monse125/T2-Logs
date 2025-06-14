#include "union_find_raw.hpp"

UnionFindRaw::UnionFindRaw(int numNodes) : parent(numNodes), size(numNodes, 1) {
    for (int nodeIndex = 0; nodeIndex < numNodes; ++nodeIndex)
        parent[nodeIndex] = nodeIndex;
}

int UnionFindRaw::find(int node) {
    // SIN compresión de caminos - solo sigue el camino hasta la raíz
    while (parent[node] != node) {
        node = parent[node];
    }
    return node;
}

void UnionFindRaw::unite(int nodeA, int nodeB) {
    int rootA = find(nodeA);
    int rootB = find(nodeB);
    if (rootA == rootB) return;

    // CON unión por tamaño (igual que la versión optimizada)
    if (size[rootA] < size[rootB]) {
        parent[rootA] = rootB;
        size[rootB] += size[rootA];
    } else {
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
    }
}