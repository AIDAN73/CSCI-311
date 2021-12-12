// CSCI 311 - Fall 2021
// Graph class header
// Author: Carter Tillquist

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

class Graph{
  public:
    std::vector<Node> nodes;

    Graph();
    void printAdjList();
};

#endif