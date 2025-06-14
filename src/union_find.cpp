#include "union_find.h"

Node* UnionFind::find(Node* node, bool useOptimization) {
    if (useOptimization) {
        return findWithOptimization(node);
    } else {
        return findWithoutOptimization(node);
    }
}

bool UnionFind::unionSets(Node* root1, Node* root2) {
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

Node* UnionFind::findWithOptimization(Node* node) {
    if (node->parent != node) {
        node->parent = findWithOptimization(node->parent);  // Compresión de caminos
    }
    return node->parent;
}

Node* UnionFind::findWithoutOptimization(Node* node) {
    while (node->parent != node) {
        node = node->parent;
    }
    return node;
}
