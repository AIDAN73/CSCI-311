// CSCI 311 - Fall 2021
// Node cpp
// Author: Carter Tillquist

#include "Node.h"

Node::Node(){
  id = 0;
  discovered = -1;
  finished = -1;
  visited = false;
  data = "";
  predecessor = nullptr;
  neighbors = {};
}

Node::Node(int i){
  id = i;
  discovered = -1;
  finished = -1;
  visited = false;
  data = "";
  predecessor = nullptr;
  neighbors = {};
}

Node::Node(int i, std::string d){
  id = i;
  discovered = -1;
  finished = -1;
  visited = false;
  data = d;
  predecessor = nullptr;
  neighbors = {};
}