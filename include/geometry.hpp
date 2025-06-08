#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

/**
 * @struct Node
 * @brief Representa un nodo en un plano cartesiano 2D
 * 
 * Esta estructura almacena las coordenadas x e y de un nodo que es un punto. :D
 */
struct Node {
    double x; ///< Coordenada X del punto
    double y; ///< Coordenada Y del punto
};


/**
 * @struct Edge
 * @brief Representa una arista entre dos nodos con peso asociado
 * 
 * Esta estructura define una arista dirigida entre dos nodos, incluyendo
 * el peso o costo de la conexión.
 */

struct Edge {
    int from;      ///< Índice del nodo origen
    int to;        ///< Índice del nodo destino  
    double weight; ///< Peso o costo de la arista (típicamente distancia euclidiana)

    /**
     * @brief Operador de comparación menor que para ordenamiento
     * @param other Otra arista a comparar
     * @return true si el peso de esta arista es menor que el de la otra
     * 
     * Este operador permite ordenar las aristas por peso de menor a mayor,
     * lo cual es esencial para el algoritmo de Kruskal que procesa las
     * aristas en orden ascendente de peso.
     */
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};


#endif // GEOMETRY_HPP