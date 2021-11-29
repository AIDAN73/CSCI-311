// CSCI 311 - Fall 2021
// Graph class cpp
// Author: Carter Tillquist

#include <iostream>
#include "Graph.h"
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

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
	queue.push_back(&nodes[s]);				//queue holds the list of nodes whose neighbors need to be explore 

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

//determines if a graph is colorable with two colors such that two nodes linked by an edge cannot be the same color. Uses a modified BFS to color each node based on its predecessor's color,
//then check if any of its neighbors have the same color. 
bool Graph::isTwoColorable()
{
	for (int i = 0; i < nodes.size(); i++) // set all nodes to a baseline
	{
		nodes[i].visited = false;
		nodes[i].color = "null";
	}

	for (int i = 0; i < nodes.size(); i++)			//make sure the algorithm works with forests, where the original BST algorithm would stop at only the local graph
	{
		vector<Node *> queue = {};
		if (nodes[i].visited == false)		
		{
			nodes[i].visited = true;				//starting point of this subgraph
			nodes[i].color = "red";

			queue.push_back(&nodes[i]);
			while (queue.size() > 0) // visit all nodes reachable
			{
				Node *currentNode = queue[0];
				queue.erase(queue.begin());
				for (int j = 0; j < currentNode->neighbors.size(); j++) // visit all of this node's neighbors
				{
					Node *currentNeighbor = currentNode->neighbors[j];
					if (currentNode->neighbors[j]->visited == false)
					{
						currentNeighbor->visited = true;

						if (currentNode->color == "red")	currentNeighbor->color = "blue";			//set the neighbor's color
						if (currentNode->color == "blue")	currentNeighbor->color = "red";

						for (int k=0; k<currentNeighbor->neighbors.size(); k++)
						{
							if (currentNeighbor->neighbors[k]->color == currentNeighbor->color) return false;		//check that the neighbor doesn't share a color with any of its' neighbors
						}

						queue.push_back(currentNeighbor); // add it to the list of nodes whose neighbors to explore
					}
				}
			}
		}
	}
	return true;		//if no contradictions have been found, it's two colorable
}

//checks if a graph is connected by using BFS to set the distance of each node to the 'root'. If the graph is not connected, the distance of at least one node will be int max
bool Graph::isConnected()
{
	BFS(0);
	for (int i=0; i<nodes.size(); i++)
	{
		if (nodes[i].dist == INT_MAX) return false;
	}
	return true;
}

//returns if a graph has a cycle, using a modified DFS to tell if a node has already been visited. If a node can be accessed by two different paths, the graph must necessarily have cycle
bool Graph::hasCycle()
{
	for (int i=0; i < nodes.size(); i++)
	{
		nodes[i].visited = false;			//sets a baseline for all the nodes in the graph
		nodes[i].predecessor = nullptr;
	}

	for (int j=0; j<nodes.size(); j++)			//ensures that all nodes in the graph are visited, even if they're disconnected
	{
		if (nodes[j].visited == false)
		{
			if (hasCycleRecur(j)) return true;		//recursively visits all the neighbors of the node, starting with itself
		}
	}
	return false;
}

bool Graph::hasCycleRecur(int s) 
{	
	nodes[s].visited = true;

	for (int i=0; i < nodes[s].neighbors.size(); i++)				//visit all the neighbors
	{
		if (nodes[s].neighbors[i]->visited == true && nodes[s].neighbors[i] != nodes[s].predecessor)		return true;		//if the node has been visited before, that means there's at least two paths to this node, indicating a loop

		else if (nodes[s].neighbors[i]->visited == false)							//if the node hasn't been visited before, explore it further before continueing with this node
		{
			nodes[s].neighbors[i]->predecessor = &nodes[s];
			if (hasCycleRecur( nodes[s].neighbors[i]->id)) return true;
		}
	}
	return false;			//if no loops have been found at the this node, return true	
}

//uses a modified BFS to check if the node v is reachable from the node u. Performs BFS and returns true if v is found, returns false otherwise
bool Graph::isReachable(int u, int v)
{
	for (int i=0; i<nodes.size(); i++)		//set all nodes to a baseline
	{
		nodes[i].visited = false;
	}

	nodes[u].visited = true;

	vector<Node*> queue = {};
	queue.push_back(&nodes[u]);				//queue holds the list of nodes whose neighbors need to be explore 

	while (queue.size() > 0)				//visit all nodes
	{
		Node* currentNode = queue[0];		
		queue.erase(queue.begin());
		for (int j=0; j < currentNode->neighbors.size(); j++)		//visit all of this node's neighbors
		{
			if(currentNode->neighbors[j]->id == v) return true; 	//if v has been found, it's reachable

			if(currentNode->neighbors[j]->visited == false)
			{
				currentNode->neighbors[j]->visited = true;
				queue.push_back(currentNode->neighbors[j]);							//add it to this list of nodes whose neighbors to explore
			}
		}
	}
	return false; 	//if v isn't found return false
}