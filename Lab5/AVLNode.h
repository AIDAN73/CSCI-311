// CSCI 311 - Fall 2021
// AVLNode header
// Author: Carter Tillquist

#ifndef AVLNODE_H
#define AVLNODE_H

class AVLNode{
  public:
    int value;
    int height;
    int balanceFactor;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent; // you are not required to update parent nodes but you may use them if you want
    
    AVLNode();
    AVLNode(int);
};

#endif