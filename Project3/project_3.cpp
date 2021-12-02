// CSCI 311 - Fall 2021
// project 3 
// Author: Aidan Murphree

#include "Node.h"
#include "Graph.h"




bool verifyPath (Graph G, vector<int> path, int i, int c)
{
	int charge = i;
	Node* currentNode = &G.nodes[path[0]];

	for (int j=1; j<path.size(); j++)
	{
		Node* targetNode = &G.nodes[path[j]];
		charge = charge - G.adjMatrix[currentNode->id][targetNode->id];
		
		if (charge < 0) return false;

		if (targetNode->isCharger) charge = c; 

		currentNode = targetNode; 
	}
}
















