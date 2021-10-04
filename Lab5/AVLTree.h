// CSCI 311 - Fall 2021
// Lab 5 AVLTree header
// Author: Carter Tillquist

#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>
#include "AVLNode.h"
using namespace std;

class AVLTree{
  public:
    AVLTree();

    AVLNode* getRoot();
    int getSize();

    AVLNode* search(int);

    AVLNode* minimum();
    AVLNode* maximum();

    void insertValue(int);
    void deleteValue(int);
  
    void preOrder(AVLNode*, vector<AVLNode*>&);
    void inOrder(AVLNode*, vector<AVLNode*>&);
    void postOrder(AVLNode*, vector<AVLNode*>&);

  private:
    AVLNode* root;
    int size;

    AVLNode* search(AVLNode*, int);
    AVLNode* minimum(AVLNode*);
    AVLNode* maximum(AVLNode*);
    AVLNode* insertValue(AVLNode*, int);
    AVLNode* deleteValue(AVLNode*, int);

    AVLNode* rebalance(AVLNode*);
    AVLNode* rotateLeft(AVLNode*);
    AVLNode* rotateRight(AVLNode*);
    AVLNode* rotateLeftRight(AVLNode*);
    AVLNode* rotateRightLeft(AVLNode*);
};

#endif