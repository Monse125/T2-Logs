#include "graph.hpp"
#include "kruskal_sorted_optim.hpp"
#include <iostream>
#include <iomanip>  // para fijar decimales

int main() {
    int N = 10;  // grafo pequeño para probar
    Graph g(N);

    std::cout << "Grafo generado con " << g.nodes.size() << " nodos y " << g.edges.size() << " aristas.\n";

    // Ejecutar Kruskal con ordenamiento + find optimizado
    std::vector<Edge> mst = kruskalSortedOptim(g);

    // Calcular peso total del MST
    double total_weight = 0;
    for (const Edge& e : mst) {
        total_weight += e.weight;
    }

    std::cout << "Árbol de expansión mínima generado.\n";
    std::cout << "Cantidad de aristas en el MST: " << mst.size() << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Peso total del MST: " << total_weight << "\n";

    std::cout << "\nAristas del MST:\n";
    for (const Edge& e : mst) {
        std::cout << "(" << e.from << " - " << e.to << ") peso: " << e.weight << "\n";
    }

    return 0;
}