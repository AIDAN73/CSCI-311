// CSCI 311 - Fall 2021
// Graph class cpp
// Author: Carter Tillquist

#include <iostream>
#include "Graph.h"

Graph::Graph(){
  nodes = {};
}

void Graph::printAdjList(){
  for (int i = 0; i < nodes.size(); i++){
    std::cout << nodes[i].id << ": ";
    for (int j = 0; j < nodes[i].neighbors.size(); j++){
      std::cout << nodes[i].neighbors[j]->id << " ";
    }
    std::cout << std::endl;
  }
}
