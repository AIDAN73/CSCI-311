// CSCI 311 - Fall 2021
// Node Class
// Author: Carter Tillquist

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node{
  public:
    int id;
    int discovered;
    int finished;
    bool visited;
    Node* predecessor;
    std::string data;
    std::vector<Node*> neighbors;
    
    Node();
    Node(int);
    Node(int, std::string);
};

#endif