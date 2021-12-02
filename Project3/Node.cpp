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
	dist = INT_MAX;
	predecessor = nullptr;
	neighbors = {};
	distances = {};
}

Node::Node(int i)
{
	id = i;
	dist = INT_MAX;
	predecessor = nullptr;
	neighbors = {};
	distances = {};
}

void Node::displayNode()
{
	cout<<"ID: "<<id<<"\tDist: "<<dist;
}