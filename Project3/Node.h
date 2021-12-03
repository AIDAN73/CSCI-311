// CSCI 311 - Fall 2021
// Node Class
// Author: Aidan Murphree

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
using namespace std;

class Node
{
public:
	int id;
	int dist;
	bool isCharger;

	bool visited; 
	Node *predecessor;
	vector<Node *> neighbors;

	Node();
	Node(int i, bool c);
	Node(int i, bool c, int d);

	void displayNode();
};

#endif