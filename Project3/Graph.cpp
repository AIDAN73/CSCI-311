// CSCI 311 - Fall 2021
// Graph class cpp
// Author: Carter Tillquist

#include <iostream>
#include "Graph.h"
#include <vector>
#include <queue>
#include <limits.h>
#include "priorityQueue.h"
using namespace std;

Graph::Graph()
{
	nodes = {};
}

// prints all the neighbors of all the nodes in a tree. Simply iterates through all the nodes and prints their neighbors
void Graph::printAdjList()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		Node currentNode = nodes[i];
		cout << currentNode.id << ": ";
		for (int j = 0; j < currentNode.neighbors.size(); j++)
		{
			cout << "(" << currentNode.neighbors[j]->id << ", " << currentNode.distances[j] << ") ";
		}
		cout << endl;
	}
}

// checks if node v is a neighbor of u. Iterates through u's neighbors to see if one of their IDs matches v.
bool Graph::isNeighbor(int u, int v)
{
	for (int i = 0; i < nodes[u].neighbors.size(); i++)
	{
		if (nodes[u].neighbors[i]->id == v)
			return true;
	}
	return false;
}

// uses a modified BFS to check if the node v is reachable from the node u. Performs BFS and returns true if v is found, returns false otherwise
bool Graph::isReachable(int u, int v)
{
	for (int i = 0; i < nodes.size(); i++) // set all nodes to a baseline
	{
		nodes[i].visited = false;
	}

	nodes[u].visited = true;

	vector<Node *> queue = {};
	queue.push_back(&nodes[u]); // queue holds the list of nodes whose neighbors need to be explore

	while (queue.size() > 0) // visit all nodes
	{
		Node *currentNode = queue[0];
		queue.erase(queue.begin());
		for (int j = 0; j < currentNode->neighbors.size(); j++) // visit all of this node's neighbors
		{
			if (currentNode->neighbors[j]->id == v)
				return true; // if v has been found, it's reachable

			if (currentNode->neighbors[j]->visited == false)
			{
				currentNode->neighbors[j]->visited = true;
				queue.push_back(currentNode->neighbors[j]); // add it to this list of nodes whose neighbors to explore
			}
		}
	}
	return false; // if v isn't found return false
}

//used for operator overloading the node class to use for the standard priority queue library. Sets up a min heap
struct CompareDistance
{
	bool operator()(Node const &n1, Node const &n2)
	{
		return n1.dist > n2.dist;
	}
};

void Graph::dijkstra(int s)
{
	for (int i = 0; i < nodes.size(); i++) // set all nodes to a baseline
	{
		nodes[i].dist = INT_MAX;
	}

	nodes[s].dist = 0;

	priorityQueue minQueue;

	for (int j = 0; j < nodes.size(); j++) 
	{
		minQueue.push(&nodes[j]);
	}

	while (!minQueue.empty())
	{
		Node* currentNode = minQueue.peek();

		for (int k=0; k < currentNode->neighbors.size(); k++)
		{
			Node* currentNeighbor = currentNode->neighbors[k]; 

			if (currentNeighbor->dist > (currentNode->dist + currentNode->distances[currentNeighbor->id]))
			{
				currentNeighbor->dist = (currentNode->dist + currentNode->distances[currentNeighbor->id]);
			}
		}

		minQueue.minHeapify(0);				//revalidate the heap after messing with the distances
		minQueue.pop();

	}

}
