#include "graph.hpp"
#include <iostream>

int main() {
    int N = 34;
    Graph g(N);

    std::cout << "Grafo con " << g.nodes.size() << " nodos y " << g.edges.size() << " aristas." << std::endl;

    return 0;
}