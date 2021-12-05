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
	adjMatrix = {};
}

Graph::Graph(int i)
{
	nodes = {};

	vector<int> vect (i, -1);
	vector<vector<int>> twoDVect (i, vect);
	adjMatrix = twoDVect;
}

void Graph::initializeMatrix(int i)
{
	vector<int> vect (i, -1);
	vector<vector<int>> twoDVect (i, vect);
	adjMatrix = twoDVect;
}

int Graph::findIndex(int target)
{
	for (int i=0; i<nodes.size(); i++)
	{
		if (nodes[i]->id == target)		return i;
	}
	return -1;
}

// prints all the neighbors of all the nodes in a tree. Simply iterates through all the nodes and prints their neighbors
void Graph::printAdjList()
{
	cout<<"Adjacency List: "<<endl;
	for (int i = 0; i < nodes.size(); i++)
	{
		Node* currentNode = nodes[i];
		cout << currentNode->id << ": ";
		for (int j = 0; j < currentNode->neighbors.size(); j++)
		{
			Node* currentNeighbor = currentNode->neighbors[j];
			cout << "(" << currentNeighbor->id << ", " << adjMatrix[i][findIndex(currentNeighbor->id)] << ") ";
		}
		cout << endl;
	}
}

void Graph::printAdjMatrix()
{
	cout<<"Adjacency Matrix: "<<endl;
	for (int i=0; i<adjMatrix.size(); i++)
	{
		cout<<"\t"<<nodes[i]->id;
	}

	cout<<endl;

	for (int i=0; i<adjMatrix.size(); i++)
	{
		cout<<nodes[i]->id;
		for (int j=0; j<adjMatrix[i].size(); j++)
		{
			cout<<"\t";
			if (adjMatrix[i][j] != -1) 	cout<<adjMatrix[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}

void Graph::printDistances()
{
	for (int i=0; i<nodes.size(); i++)
	{
		cout<<nodes[i]->id<<": "<<nodes[i]->dist<<endl;
	}
	cout<<endl;
}

//dijkstra's algorithm implemented with a minHeap. Finds the minimum distances to each node from a given starting node s
void Graph::dijkstra(int s)
{
	for (int i = 0; i < nodes.size(); i++) // set all nodes to a baseline
	{
		nodes[i]->dist = INT_MAX;
		nodes[i]->predecessor = nullptr;
	}
	nodes[s]->dist = 0;

	priorityQueue minQueue;

	for (int j = 0; j < nodes.size(); j++) 
	{
		minQueue.push(nodes[j]);
	}
	

	while (!minQueue.empty())	
	{
		Node* currentNode = minQueue.pop();

		for (int k=0; k < currentNode->neighbors.size(); k++)				//for each of the curent node's neighbors
		{
			Node* currentNeighbor = currentNode->neighbors[k]; 				//holds a pointer to the current neighbor
			int possiblePathDistance = currentNode->dist + adjMatrix[findIndex(currentNode->id)][findIndex(currentNeighbor->id)];

			if (currentNeighbor->dist > possiblePathDistance && possiblePathDistance > 0)		//if the neighbor's current distance is larger than the other path
			{
				currentNeighbor->dist = possiblePathDistance;		//set it to the new path's distance
				currentNeighbor->predecessor = currentNode;
				minQueue.minHeapify(minQueue.search(currentNeighbor));
			}
		}
	}
}
