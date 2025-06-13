#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <vector>

// Union-Find optimizado (compresión de caminos + unión por tamaño)
class UnionFindOptim {
private:
    std::vector<int> parent;
    std::vector<int> size;

public:
    UnionFindOptim(int n);

    int find(int u);
    void unite(int u, int v);
};

// Union-Find sin optimizaciones (solo estructura básica)
class UnionFindRaw {
private:
    std::vector<int> parent;

public:
    UnionFindRaw(int n);

    int find(int u);
    void unite(int u, int v);
};

#endif