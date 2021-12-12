// CSCI 311 - Fall 2021
// Graph class cpp
// Author: Carter Tillquist

#include <iostream>
#include "Graph.h"
#include <vector>
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

//resizes the adjacency matrix of the graph to the size inputted
void Graph::initializeMatrix(int i)
{
	vector<int> vect (i, -1);
	vector<vector<int>> twoDVect (i, vect);
	adjMatrix = twoDVect;
}

//returns of the index of the node in the graphs node list with an id of target
int Graph::findIndex(int target)
{
	for (int i=0; i<nodes.size(); i++)
	{
		if (nodes[i]->id == target)		return i;
	}
	return -1;
}

// prints all the neighbors of all the nodes in a tree, used for debugging. Simply iterates through all the nodes and prints their neighbors and distances in the form 
//Node: (neighbor, distance), (neighbor2, distance2)...
void Graph::printAdjList()
{
	cout<<"Adjacency List: "<<endl;
	for (int i = 0; i < nodes.size(); i++)				//for each node
	{
		Node* currentNode = nodes[i];					
		cout << currentNode->id << ": ";	
		for (int j = 0; j < currentNode->neighbors.size(); j++)			//for each of the node's neighbors
		{
			Node* currentNeighbor = currentNode->neighbors[j];
			cout << "(" << currentNeighbor->id << ", " << adjMatrix[i][findIndex(currentNeighbor->id)] << ") ";			//print the neighbor's ID and distance
		}
		cout << endl;
	}
}

//prints the adjacency matrix of the graph, used for debugging
void Graph::printAdjMatrix()
{
	cout<<"Adjacency Matrix: "<<endl;
	for (int i=0; i<adjMatrix.size(); i++)			//print top axis
	{
		cout<<"\t"<<nodes[i]->id;
	}

	cout<<endl;

	for (int i=0; i<adjMatrix.size(); i++)
	{
		cout<<nodes[i]->id;								//print this line of the left axis
		for (int j=0; j<adjMatrix[i].size(); j++)
		{
			cout<<"\t";
			if (adjMatrix[i][j] != -1) 	cout<<adjMatrix[i][j];		//print the edge length between nodes[i] and nodes[j] if it exists
		}
		cout<<endl;
	}
	cout<<endl;
}

//prints a simple list of each node is the nodes list's set distance. Used for checking that dijkstra's worked
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
		nodes[i]->predecessor = nullptr;			//predecessor is used for working out the path 
	}

	nodes[s]->dist = 0;				//starting node distance is always 0

	priorityQueue minQueue;

	for (int j = 0; j < nodes.size(); j++) 				//this is the slow method of initializing a minQueue, but oh well
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
				currentNeighbor->predecessor = currentNode;			//set the predecessor
				minQueue.minHeapify(minQueue.search(currentNeighbor));		//reheapify after changing the values in the minHeap
			}
		}
	}
}
