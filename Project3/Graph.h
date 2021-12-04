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
	Graph(int i);
	void initializeMatrix(int i);

	void printAdjList();
	void printAdjMatrix();
	void printDistances();
	bool isNeighbor(int, int);

	bool isReachable(int, int);

	void dijkstra(int s);
};

#endif