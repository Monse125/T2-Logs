#include "node.h"

Node::Node(double x_coord, double y_coord) : x(x_coord), y(y_coord), parent(this), rank(1) {}
