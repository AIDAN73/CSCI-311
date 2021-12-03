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

// prints all the neighbors of all the nodes in a tree. Simply iterates through all the nodes and prints their neighbors
void Graph::printAdjList()
{
	cout<<"Adjacency List: "<<endl;
	for (int i = 0; i < nodes.size(); i++)
	{
		cout<<"Printing line "<<i<<" of "<< nodes.size()<<endl;
		Node* currentNode = &nodes[i];
		cout << currentNode->id << ": ";
		for (int j = 0; j < currentNode->neighbors.size(); j++)
		{
			Node* currentNeighbor = currentNode->neighbors[j];
			cout << "(" << currentNeighbor->id << ", " << adjMatrix[currentNode->id][currentNeighbor->id] << ") ";
		}
		cout << endl;
	}
}

void Graph::printAdjMatrix()
{
	cout<<"Adjacency Matrix: "<<endl;
	for (int i=0; i<adjMatrix.size(); i++)
	{
		cout<<"\t"<<i;
	}

	cout<<endl;

	for (int i=0; i<adjMatrix.size(); i++)
	{
		cout<<i;
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
		cout<<i<<": "<<nodes[i].dist<<endl;
	}
	cout<<endl;
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

//dijkstra's algorithm implemented with a minHeap. Finds the minimum distances to each node from a given starting node s
void Graph::dijkstra(int s)
{
	cout<<"Dijkstra's from "<<s<<endl;
	for (int i = 0; i < nodes.size(); i++) // set all nodes to a baseline
	{
		nodes[i].dist = INT_MAX;
		nodes[i].predecessor = nullptr;
	}

	//printDistances();	

	nodes[s].dist = 0;

	//printDistances();

	priorityQueue minQueue;

	for (int j = 0; j < nodes.size(); j++) 
	{
		minQueue.push(&nodes[j]);
	}
	//minQueue.displayPriorityQueue();

	while (!minQueue.empty())	
	{
		//cout<<"Here"<<endl;
		Node* currentNode = minQueue.pop();
		//cout<<"Current Node: "<<currentNode->id<<endl;
		for (int k=0; k < currentNode->neighbors.size(); k++)				//for each of the curent node's neighbors
		{
			//cout<<"\tLoop "<<k<<endl;
			Node* currentNeighbor = currentNode->neighbors[k]; 				//holds a pointer to the current neighbor
			//cout<<"\tCurrent Neighbor: "<<currentNeighbor->id<<endl;

			if (currentNeighbor->dist > (currentNode->dist + adjMatrix[currentNode->id][currentNeighbor->id]))		//if the neighbor's current distance is larger than the other path
			{
				currentNeighbor->dist = (currentNode->dist + adjMatrix[currentNode->id][currentNeighbor->id]);		//set it to the new path's distance
				currentNeighbor->predecessor = currentNode;
				minQueue.minHeapify(minQueue.search(currentNeighbor));
				//cout<<"\tminheapified"<<endl;
			}
		}
		//minQueue.displayPriorityQueue();
		
	}
	//printDistances();
	
	//cout<<"Out of while"<<endl;

}
