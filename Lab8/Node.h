// CSCI 311 - Fall 2021
// Node Class
// Author: Carter Tillquist

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
using namespace std;

class Node{
  public:
    int id;
    int dist;
    int discovered;
    int finished;
    bool visited;
    Node* predecessor;
    string color;
    vector<Node*> neighbors;
    
    Node();
    Node(int);
};

#endif