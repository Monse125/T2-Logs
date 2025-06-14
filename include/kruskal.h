#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include "node.h"
#include "edge.h"

/**
 * Implementación de Kruskal usando arreglo ordenado
 * @param points Vector de puntos
 * @param edges Vector de aristas
 * @param useOptimization Si usar compresión de caminos en Union-Find
 * @return Peso total del árbol cobertor mínimo
 */
double kruskalSortedArray(std::vector<Node*>& points, std::vector<Edge> edges, bool useOptimization);

/**
 * Implementación de Kruskal usando heap (priority queue)
 * @param points Vector de puntos
 * @param edges Vector de aristas
 * @param useOptimization Si usar compresión de caminos en Union-Find
 * @return Peso total del árbol cobertor mínimo
 */
double kruskalHeap(std::vector<Node*>& points, std::vector<Edge> edges, bool useOptimization);

#endif
