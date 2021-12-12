// CSCI 311 - Fall 2021
// Graph class header
// Author: Aidan Murphree

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

class Graph
{
public:
	vector<Node*> nodes;

	vector<vector<int>> adjMatrix;

	Graph();
	Graph(int);
	void initializeMatrix(int);

	void printAdjList();
	void printAdjMatrix();
	void printDistances();

	int findIndex(int);
	
	void dijkstra(int);
};

#endif