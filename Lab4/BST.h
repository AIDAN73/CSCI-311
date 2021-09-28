// CSCI 311 - Fall 2021
// Lab 4 BST header
// Author: Carter Tillquist

#ifndef BST_H
#define BST_H

#include <vector>
#include "Node.h"
using namespace std;

class BST{
  public:
    Node* root;
    int size;

    BST();
    ~BST();

    Node* search(int);
    Node* search(Node*, int);

    Node* minimum();
    Node* minimum(Node*);
    Node* maximum();
    Node* maximum(Node*);

    void insertValue(int);
    Node* insertValue(Node*, int);
    void deleteValue(int);
    Node* deleteValue(Node*, int);

    bool isBST(Node*);
    bool isBST(Node*, int, int);
  
    void preOrder(Node*, vector<Node*>&);
    void inOrder(Node*, vector<Node*>&);
    void postOrder(Node*, vector<Node*>&);
};

#endif