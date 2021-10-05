// CSCI 311 - Fall 2021
// AVLNode cpp
// Author: Carter Tillquist

#include "AVLNode.h"

AVLNode::AVLNode(){
  value = 0;
  height = 0;
  balanceFactor = 0;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

AVLNode::AVLNode(int v){
  value = v;
  height = 0;
  balanceFactor = 0;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}