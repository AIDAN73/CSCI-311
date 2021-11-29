// CSCI 311 - Fall 2021
// Graph class header
// Author: Carter Tillquist

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

class Graph{
  public:
    vector<Node> nodes;

    Graph();

    void printAdjList();
    bool isNeighbor(int, int);
    void DFS();
    int DFSVisit(int, int);
    void BFS(int);
    std::vector<int> distancesFrom(int);

    bool isTwoColorable();
    bool isConnected();
    bool hasCycle();
    bool hasCycleRecur(int);
    bool isReachable(int, int);
};

#endif