#ifndef UNION_FIND_RAW_HPP
#define UNION_FIND_RAW_HPP

#include <vector>

class UnionFindRaw {
private:
    std::vector<int> parent;

public:
    UnionFindRaw(int n);

    int find(int u);
    void unite(int u, int v);
};

#endif