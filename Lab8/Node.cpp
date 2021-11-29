// CSCI 311 - Fall 2021
// Node cpp
// Author: Carter Tillquist

#include "Node.h"
#include <string>
#include <vector>
#include <limits.h>

Node::Node(){
  id = 0;
  dist = INT_MAX;
  discovered = -1;
  finished = -1;
  visited = false;
  color = "";
  predecessor = nullptr;
  neighbors = {};
}

Node::Node(int i){
  id = i;
  dist = INT_MAX;
  discovered = -1;
  finished = -1;
  visited = false;
  color = "";
  predecessor = nullptr;
  neighbors = {};
}