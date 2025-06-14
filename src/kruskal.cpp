#include "kruskal.h"
#include "union_find.h"
#include "graph_generator.h"
#include <algorithm>
#include <queue>

double kruskalSortedArray(std::vector<Node*>& points, std::vector<Edge> edges, bool useOptimization) {
    resetUnionFind(points);
    
    // Ordena las aristas por peso
    std::sort(edges.begin(), edges.end());
    
    UnionFind uf;
    double totalWeight = 0.0;
    int edgesAdded = 0;
    int n = points.size();
    
    // Procesa aristas en orden de peso creciente
    for (const Edge& edge : edges) {
        Node* root1 = uf.find(edge.u, useOptimization);
        Node* root2 = uf.find(edge.v, useOptimization);
        
        if (uf.unionSets(root1, root2)) {
            totalWeight += edge.weight;
            edgesAdded++;
            if (edgesAdded == n - 1) {
                break;  // Ya tenemos un árbol cobertor
            }
        }
    }
    
    return totalWeight;
}

double kruskalHeap(std::vector<Node*>& points, std::vector<Edge> edges, bool useOptimization) {
    resetUnionFind(points);
    
    // Crea un min-heap de aristas
    std::priority_queue<Edge, std::vector<Edge>, EdgeComparator> pq(edges.begin(), edges.end());
    
    UnionFind uf;
    double totalWeight = 0.0;
    int edgesAdded = 0;
    int n = points.size();
    
    // Procesa aristas en orden de peso creciente
    while (!pq.empty() && edgesAdded < n - 1) {
        Edge edge = pq.top();
        pq.pop();
        
        Node* root1 = uf.find(edge.u, useOptimization);
        Node* root2 = uf.find(edge.v, useOptimization);
        
        if (uf.unionSets(root1, root2)) {
            totalWeight += edge.weight;
            edgesAdded++;
        }
    }
    
    return totalWeight;
}
