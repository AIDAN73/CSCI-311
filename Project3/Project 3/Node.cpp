// CSCI 311 - Fall 2021
// Node Class cpp
// Author: Aidan Murphree

#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

Node::Node()
{
	id = 0;
	isCharger = false;

	bool visited = false;
	dist = INT_MAX;
	predecessor = nullptr;
	neighbors = {};
}

Node::Node(int i, bool c)
{
	id = i;
	isCharger = c;

	bool visited = false;
	dist = INT_MAX;
	predecessor = nullptr;
	neighbors = {};
}

Node::Node(int i, bool c, int d)
{
	id = i;
	isCharger = c;

	bool visited = false;
	dist = d;
	predecessor = nullptr;
	neighbors = {};
}

void Node::displayNode()
{
	cout<<"ID: "<<id<<"\tDist: "<<dist;
}