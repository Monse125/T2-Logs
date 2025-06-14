#include "union_find_optim.hpp"

UnionFindOptim::UnionFindOptim(int numNodes) : parent(numNodes), size(numNodes, 1) {
    for (int nodeIndex = 0; nodeIndex < numNodes; ++nodeIndex)
        parent[nodeIndex] = nodeIndex;
}

int UnionFindOptim::find(int node) {
    if (parent[node] != node)
        parent[node] = find(parent[node]);  // CON compresión de caminos
    return parent[node];
}

void UnionFindOptim::unite(int nodeA, int nodeB) {
    int rootA = find(nodeA);
    int rootB = find(nodeB);
    if (rootA == rootB) return;

    // CON unión por tamaño
    if (size[rootA] < size[rootB]) {
        parent[rootA] = rootB;
        size[rootB] += size[rootA];
    } else {
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
    }
}