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
	int discovered;
	int finished;
	bool visited;
	Node *predecessor;
	vector<Node *> neighbors;
	vector<int> distances;

	Node();
	Node(int);

	void displayNode();
};

#endif