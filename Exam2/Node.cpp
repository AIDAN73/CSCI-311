// CSCI 311 - Fall 2021
// Node Class
// Author: Carter Tillquist

#include "Node.h"

Node::Node(){
  value = 0;
  left = nullptr;
  right = nullptr;
}

Node::Node(int v){
  value = v;
  left = nullptr;
  right = nullptr;
}

Node::~Node(){}