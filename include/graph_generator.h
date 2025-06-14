#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <vector>
#include "node.h"
#include "edge.h"

/**
 * Genera puntos aleatorios en el plano [0,1] x [0,1]
 * @param n Número de puntos a generar
 * @param seed Semilla para el generador de números aleatorios
 * @return Vector de punteros a los nodos generados
 */
std::vector<Node*> generatePoints(int n, int seed);

/**
 * Genera todas las aristas posibles entre los puntos dados
 * @param points Vector de puntos
 * @return Vector de aristas con sus pesos calculados
 */
std::vector<Edge> generateEdges(const std::vector<Node*>& points);

/**
 * Reinicia la estructura Union-Find de todos los nodos
 * @param points Vector de puntos a reiniciar
 */
void resetUnionFind(std::vector<Node*>& points);

#endif
