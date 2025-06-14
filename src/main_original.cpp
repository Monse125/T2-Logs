#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * Estructura que representa un nodo en el plano bidimensional
 * Contiene coordenadas (x,y) y información para Union-Find
 */
struct Node {
    double x, y;           // Coordenadas del punto
    Node* parent;          // Puntero al padre en la estructura Union-Find
    int rank;              // Rango del nodo para Union-Find (tamaño del árbol)
    
    /**
     * Constructor que inicializa un nodo con coordenadas dadas
     * @param x_coord Coordenada x del punto
     * @param y_coord Coordenada y del punto
     */
    Node(double x_coord, double y_coord) : x(x_coord), y(y_coord), parent(this), rank(1) {}
};

/**
 * Estructura que representa una arista entre dos nodos
 * Contiene punteros a los nodos y el peso de la arista
 */
struct Edge {
    Node* u;               // Primer nodo de la arista
    Node* v;               // Segundo nodo de la arista
    double weight;         // Peso de la arista (distancia euclidiana al cuadrado)
    
    /**
     * Constructor que crea una arista entre dos nodos
     * @param node1 Primer nodo
     * @param node2 Segundo nodo
     */
    Edge(Node* node1, Node* node2) : u(node1), v(node2) {
        // Calcula el peso como el cuadrado de la distancia euclidiana
        double dx = node1->x - node2->x;
        double dy = node1->y - node2->y;
        weight = dx * dx + dy * dy;
    }
    
    /**
     * Operador de comparación para ordenar aristas por peso
     */
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

/**
 * Comparador para el heap (priority queue) de aristas
 * Como priority_queue es un max-heap, invertimos la comparación
 */
struct EdgeComparator {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.weight > b.weight;  // Para obtener un min-heap
    }
};

/**
 * Clase que implementa la estructura Union-Find
 * Permite verificar si dos nodos están en el mismo componente conexo
 */
class UnionFind {
public:
    /**
     * Encuentra la raíz del árbol que contiene al nodo dado
     * @param node Nodo del cual encontrar la raíz
     * @param useOptimization Si true, aplica compresión de caminos
     * @return Puntero a la raíz del árbol
     */
    Node* find(Node* node, bool useOptimization) {
        if (useOptimization) {
            return findWithOptimization(node);
        } else {
            return findWithoutOptimization(node);
        }
    }
    
    /**
     * Une dos componentes conexos si están separados
     * @param root1 Raíz del primer componente
     * @param root2 Raíz del segundo componente
     * @return true si se realizó la unión, false si ya estaban unidos
     */
    bool unionSets(Node* root1, Node* root2) {
        if (root1 == root2) {
            return false;  // Ya están en el mismo conjunto
        }
        
        // Union by rank: el árbol más pequeño se une al más grande
        if (root1->rank < root2->rank) {
            root1->parent = root2;
            root2->rank += root1->rank;
        } else {
            root2->parent = root1;
            root1->rank += root2->rank;
        }
        
        return true;
    }

private:
    /**
     * Find con compresión de caminos
     * Todos los nodos visitados apuntan directamente a la raíz
     */
    Node* findWithOptimization(Node* node) {
        if (node->parent != node) {
            node->parent = findWithOptimization(node->parent);  // Compresión de caminos
        }
        return node->parent;
    }
    
    /**
     * Find sin optimización
     * Simplemente sube por los padres hasta encontrar la raíz
     */
    Node* findWithoutOptimization(Node* node) {
        while (node->parent != node) {
            node = node->parent;
        }
        return node;
    }
};

/**
 * Genera puntos aleatorios en el plano [0,1] x [0,1]
 * @param n Número de puntos a generar
 * @param seed Semilla para el generador de números aleatorios
 * @return Vector de punteros a los nodos generados
 */
vector<Node*> generatePoints(int n, int seed) {
    vector<Node*> points;
    mt19937 gen(seed);
    uniform_real_distribution<double> dis(0.0, 1.0);
    
    for (int i = 0; i < n; i++) {
        double x = dis(gen);
        double y = dis(gen);
        points.push_back(new Node(x, y));
    }
    
    return points;
}

/**
 * Genera todas las aristas posibles entre los puntos dados
 * @param points Vector de puntos
 * @return Vector de aristas con sus pesos calculados
 */
vector<Edge> generateEdges(const vector<Node*>& points) {
    vector<Edge> edges;
    int n = points.size();
    
    // Genera todas las combinaciones de pares de puntos
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.emplace_back(points[i], points[j]);
        }
    }
    
    return edges;
}

/**
 * Reinicia la estructura Union-Find de todos los nodos
 * @param points Vector de puntos a reiniciar
 */
void resetUnionFind(vector<Node*>& points) {
    for (Node* node : points) {
        node->parent = node;
        node->rank = 1;
    }
}

/**
 * Implementación de Kruskal usando arreglo ordenado
 * @param points Vector de puntos
 * @param edges Vector de aristas
 * @param useOptimization Si usar compresión de caminos en Union-Find
 * @return Peso total del árbol cobertor mínimo
 */
double kruskalSortedArray(vector<Node*>& points, vector<Edge> edges, bool useOptimization) {
    resetUnionFind(points);
    
    // Ordena las aristas por peso
    sort(edges.begin(), edges.end());
    
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

/**
 * Implementación de Kruskal usando heap (priority queue)
 * @param points Vector de puntos
 * @param edges Vector de aristas
 * @param useOptimization Si usar compresión de caminos en Union-Find
 * @return Peso total del árbol cobertor mínimo
 */
double kruskalHeap(vector<Node*>& points, vector<Edge> edges, bool useOptimization) {
    resetUnionFind(points);
    
    // Crea un min-heap de aristas
    priority_queue<Edge, vector<Edge>, EdgeComparator> pq(edges.begin(), edges.end());
    
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

/**
 * Mide el tiempo de ejecución de una función
 * @param func Función a ejecutar
 * @return Tiempo de ejecución en microsegundos
 */
template<typename Func>
long long measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

/**
 * Ejecuta una prueba rápida para validar la implementación
 */
void runQuickTest() {
    cout << "=== PRUEBA RÁPIDA ===" << endl;
    
    // Prueba con un grafo pequeño conocido
    vector<Node*> testPoints = {
        new Node(0.0, 0.0),
        new Node(1.0, 0.0),
        new Node(0.5, 1.0)
    };
    
    vector<Edge> testEdges = generateEdges(testPoints);
    
    cout << "Puntos de prueba:" << endl;
    for (size_t i = 0; i < testPoints.size(); i++) {
        cout << "  P" << i << ": (" << testPoints[i]->x << ", " << testPoints[i]->y << ")" << endl;
    }
    
    cout << "Aristas y pesos:" << endl;
    for (size_t i = 0; i < testEdges.size(); i++) {
        cout << "  E" << i << ": peso = " << testEdges[i].weight << endl;
    }
    
    // Ejecutar las 4 variantes
    double result1 = kruskalSortedArray(testPoints, testEdges, true);
    double result2 = kruskalHeap(testPoints, testEdges, true);
    double result3 = kruskalSortedArray(testPoints, testEdges, false);
    double result4 = kruskalHeap(testPoints, testEdges, false);
    
    cout << "Resultados (peso total del MST):" << endl;
    cout << "  Sorted + Opt: " << result1 << endl;
    cout << "  Heap + Opt:   " << result2 << endl;
    cout << "  Sorted - Opt: " << result3 << endl;
    cout << "  Heap - Opt:   " << result4 << endl;
    
    // Verificar que todos den el mismo resultado
    if (abs(result1 - result2) < 1e-9 && abs(result1 - result3) < 1e-9 && abs(result1 - result4) < 1e-9) {
        cout << "✓ Todas las variantes producen el mismo resultado" << endl;
    } else {
        cout << "✗ ERROR: Las variantes producen resultados diferentes" << endl;
    }
    
    // Liberar memoria
    for (Node* node : testPoints) {
        delete node;
    }
    
    cout << endl;
}
void runExperiments(int n, vector<vector<long long>>& results) {
    cout << "Ejecutando experimentos para n = " << n << endl;
    
    // 4 variantes: [sorted/heap] x [with/without optimization]
    vector<long long> times(4, 0);
    
    // Ejecuta 5 repeticiones para cada tamaño
    for (int rep = 0; rep < 5; rep++) {
        vector<Node*> points = generatePoints(n, 12345 + rep);
        vector<Edge> edges = generateEdges(points);
        
        // Variante 1: Sorted array con optimización
        times[0] += measureTime([&]() {
            kruskalSortedArray(points, edges, true);
        });
        
        // Variante 2: Heap con optimización
        times[1] += measureTime([&]() {
            kruskalHeap(points, edges, true);
        });
        
        // Variante 3: Sorted array sin optimización
        times[2] += measureTime([&]() {
            kruskalSortedArray(points, edges, false);
        });
        
        // Variante 4: Heap sin optimización
        times[3] += measureTime([&]() {
            kruskalHeap(points, edges, false);
        });
        
        // Libera memoria
        for (Node* node : points) {
            delete node;
        }
    }
    
    // Calcula promedios
    for (int i = 0; i < 4; i++) {
        times[i] /= 5;
    }
    
    results.push_back(times);
}

/**
 * Guarda los resultados en un archivo
 * @param results Matriz con los tiempos de ejecución
 */
void saveResults(const vector<vector<long long>>& results) {
    ofstream file("results.txt");
    
    file << "# Resultados de los experimentos con Kruskal" << endl;
    file << "# Columnas: N, Sorted+Opt, Heap+Opt, Sorted-Opt, Heap-Opt" << endl;
    file << "# Tiempos en microsegundos (promedio de 5 ejecuciones)" << endl;
    
    for (size_t i = 0; i < results.size(); i++) {
        int n = 1 << (i + 5);  // 2^(i+5)
        file << n;
        for (int j = 0; j < 4; j++) {
            file << "\t" << results[i][j];
        }
        file << endl;
    }
    
    file.close();
    cout << "Resultados guardados en results.txt" << endl;
}

/**
 * Función principal que ejecuta todos los experimentos
 */
int main() {
    cout << "=== Tarea 2: Algoritmo de Kruskal ===" << endl;
    cout << "Implementación de 4 variantes del algoritmo de Kruskal" << endl << endl;
    
    // Ejecutar prueba rápida primero
    runQuickTest();
    
    cout << "Ejecutando experimentos completos..." << endl << endl;
    
    vector<vector<long long>> results;
    
    // Ejecuta experimentos para n = 2^5, 2^6, ..., 2^12
    for (int exp = 5; exp <= 12; exp++) {
        int n = 1 << exp;  // 2^exp
        runExperiments(n, results);
    }
    
    // Guarda resultados
    saveResults(results);
    
    cout << endl << "=== Experimentos completados ===" << endl;
    cout << "Los resultados han sido guardados en results.txt" << endl;
    cout << "Puedes usar estos datos para crear gráficos comparativos." << endl;
    cout << "Ejecuta 'python3 analyze_results.py' para generar gráficos automáticamente." << endl;
    
    return 0;
}
