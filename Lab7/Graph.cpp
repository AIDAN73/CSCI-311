// CSCI 311 - Fall 2021
// Graph class cpp
// Author: Carter Tillquist

#include <iostream>
#include "Graph.h"
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

//default constructor
Graph::Graph()
{
	nodes = {};
}


//prints all the neighbors of all the nodes in a tree. Simply iterates through all the nodes and prints their neighbors
void Graph::printAdjList()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		Node currentNode = nodes[i];
		cout << currentNode.id << ": ";
		for (int j = 0; j < currentNode.neighbors.size(); j++)
		{
			cout << currentNode.neighbors[j]->id << " ";
		}
		cout << endl;
	}
}

//checks if node v is a neighbor of u. Iterates through u's neighbors to see if one of their IDs matches v. 
bool Graph::isNeighbor(int u, int v)
{
	for (int i=0; i<nodes[u].neighbors.size(); i++)
	{
		if (nodes[u].neighbors[i]->id == v) return true;
	}
	return false;
}


//prepares the graph for depth first search by setting the nodes' properties, then calls the recursive DFSVisit on each of the nodes (in chase of disconnected graphs)
void Graph::DFS()
{
	for (int i=0; i < nodes.size(); i++)
	{
		nodes[i].visited = false;			//sets a baseline for all the nodes in the graph
		nodes[i].predecessor = nullptr;
		nodes[i].discovered = -1;
		nodes[i].finished = -1;
	}

	int time = 0;
	for (int j=0; j<nodes.size(); j++)			//ensures that all nodes in the graph are visited, even if they're disconnected
	{
		if (nodes[j].visited == false)
		{
			time = DFSVisit(j, time);			//recursively visits all the neighbors of the node, starting with itself
		}
	}
}

//recursively visits all of the neighbors of a given node, updating the nodes with time of discovery and when all their neighbors have visited
int Graph::DFSVisit(int s, int time)
{	
	time++;
	nodes[s].discovered = time;			//set discovered time
	nodes[s].visited = true;

	for (int i=0; i < nodes[s].neighbors.size(); i++)				//visit all the neighbors
	{
		if (nodes[s].neighbors[i]->visited == false)				//if the node hasn't been visited before, explore it further before continueing with this node
		{
			nodes[s].neighbors[i]->predecessor = &nodes[s];
			time = DFSVisit( nodes[s].neighbors[i]->id , time);
		}
	}
	time++;
	nodes[s].finished = time;				//after visiting all the neighbors and subneighbors, mark finished time
	return time;							//return time so it can be used for other subgraphs
}


//breadth first search, visiting all of a given node's neighbors before continueing on to their neighbors. Updates each node's distance from the starting point
void Graph::BFS(int s)
{
	for (int i=0; i<nodes.size(); i++)		//set all nodes to a baseline
	{
		nodes[i].dist = INT_MAX;
		nodes[i].visited = false;
		nodes[i].predecessor = nullptr;
	}

	nodes[s].dist = 0;						//starting node has distance of 0
	nodes[s].visited = true;

	vector<Node*> queue = {};
	queue.push_back(&nodes[s]);				//queue holds the list of nodes whose neighbors need to be explored 

	while (queue.size() > 0)				//visit all nodes
	{
		Node* currentNode = queue[0];		
		queue.erase(queue.begin());
		for (int j=0; j < currentNode->neighbors.size(); j++)		//visit all of this node's neighbors
		{
			if(currentNode->neighbors[j]->visited == false)
			{
				currentNode->neighbors[j]->dist = currentNode->dist + 1;			//set the neighbor's distance
				currentNode->neighbors[j]->visited = true;
				currentNode->neighbors[j]->predecessor = currentNode;
				queue.push_back(currentNode->neighbors[j]);							//add it to this list of nodes whose neighbors to explore
			}
		}
	}
}

//uses breadth first search to calculate the distance of each node from the given starting node, then adds those distances to a vector
vector<int> Graph::distancesFrom(int s)
{
	BFS(s);					//sets the distances of the graph

	vector<int> distances = {};

	for (int i=0; i < nodes.size(); i++)		//adds these distances to a vector, in the order of the nodes in the graph nodes vector
	{
		distances.push_back(nodes[i].dist);
	}
	return distances;
}
