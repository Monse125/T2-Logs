#ifndef UNION_FIND_OPTIM_HPP  // Cambiar nombre del guard
#define UNION_FIND_OPTIM_HPP

#include <vector>

class UnionFindOptim {
private:
    std::vector<int> parent;
    std::vector<int> size;

public:
    UnionFindOptim(int n);

    int find(int u);
    void unite(int u, int v);
};

#endif