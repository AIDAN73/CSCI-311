// CSCI 311 - Fall 2021
// project 3 
// Author: Aidan Murphree

#include "Node.h"
#include "Graph.h"
#include "priorityQueue.h"
#include <iostream>
#include <limits.h>



//steps through the given path of the graph, making sure that the required edges exist and the car doesn't run out of gas
bool verifyPath (Graph G, vector<int> path, int i, int c)
{
	int charge = i;										//initialize charge
	Node* currentNode = G.nodes[path[0]];				//starting point

	for (int j=1; j<path.size(); j++)													//check each step to get to the end
	{

		Node* targetNode = G.nodes[path[j]];											//holds the node the car will be traveling to in this step

		if (path[j] >= G.nodes.size()) return false;									//this node does not exist

		if (G.adjMatrix[currentNode->id][targetNode->id] == -1)		return false; 		//negative distances don't exist, this edge does not exist

		charge = charge - G.adjMatrix[currentNode->id][targetNode->id];			//remove the necessary charge and check to see if the car made it
		if (charge < 0) return false;

		if (targetNode->isCharger) charge = c; 			//if we reached a charger, reset the charge

		currentNode = targetNode; 						//made it
	}

	return true; 			//made it through the path
}

//takes a given graph and returns a similar one without all the nodes that aren't the start, end, or a charger. This graph is complete, except for the edges that are larger
//than the max charge, and edges from the start node larger than the initial charge
Graph simplifyGraph (Graph* G, int start, int end, int maxCharge, int charge)
{
	Graph simpG;

	for (int i=0; i<G->nodes.size(); i++)						//add all the nodes that are the start, end, or a charger
	{
		if(G->nodes[i]->isCharger  ||  G->nodes[i]->id == start  ||  G->nodes[i]->id == end)
		{
			Node* v = new Node(G->nodes[i]->id, G->nodes[i]->isCharger);
			simpG.nodes.push_back(v);
		}
	}

	simpG.initializeMatrix(simpG.nodes.size());					//resize the simplified graph's adjacency matrix

	//fills in the edges of the simplified graph by calling dijkstra's on each important node in the original graph, and adding the edge if the it's possible to traverse
	for (int i=0; i<simpG.nodes.size(); i++)			
	{
		Node* currentImportantNode = simpG.nodes[i];

		G->dijkstra(currentImportantNode->id);				//get the distance of all nodes from this important node

		for (int j=0; j<simpG.nodes.size(); j++)			//add an edge from this important node to each other important node if it's possible
		{
			Node* currentImportantNeighbor = simpG.nodes[j];
			currentImportantNeighbor->dist = G->nodes[currentImportantNeighbor->id]->dist;

			if(currentImportantNode->id == start || currentImportantNeighbor->id == start)		//if the edge connects the the start, it has to be traversable with the initial charge
			{
				
				if (currentImportantNeighbor->dist <= charge  &&  currentImportantNeighbor!=currentImportantNode)
				{
					simpG.nodes[i]->neighbors.push_back(simpG.nodes[j]);			//add neighbors and update the adjacency matrix
					simpG.adjMatrix[i][j] = currentImportantNeighbor->dist;
					simpG.adjMatrix[j][i] = currentImportantNeighbor->dist;
				}
			}

			else		//otherwise, the edge just has to be traversable with the max charge
			{
				if (currentImportantNeighbor->dist <= maxCharge   &&  currentImportantNeighbor!=currentImportantNode)
				{
					simpG.nodes[i]->neighbors.push_back(simpG.nodes[j]);			//add neighbors and update the adjacency matrix
					simpG.adjMatrix[i][j] = currentImportantNeighbor->dist;
					simpG.adjMatrix[j][i] = currentImportantNeighbor->dist;
				}
			}
		}
	}

	return simpG;
}


vector<int> simplifiedPath(Graph* G, int start, int end)
{
	Node* currentNode = G->nodes[G->findIndex(start)];

	vector<int> path = {};
	path.push_back(currentNode->id);

	while (currentNode->predecessor != nullptr)
	{
		path.push_back(currentNode->predecessor->id);
		currentNode = currentNode->predecessor;
	}

	return path;
}

vector<int> fullPath(Graph* G, vector<int> sPath)
{
	
	vector<int> path = {};
	path.push_back(sPath[0]);

	for (int i=0; i<sPath.size()-1; i++)
	{
		Node* currentNode = G->nodes[sPath[i]];				//initialize currentNode as end of paths
		Node* nextImportantNode = G->nodes[sPath[i+1]];

		G->dijkstra(nextImportantNode->id);
		vector<int> subPath = {};


		while (currentNode->predecessor != nullptr)
		{
			subPath.push_back(currentNode->predecessor->id);
			currentNode = currentNode->predecessor;
		}

		path.insert(path.end(), subPath.begin(), subPath.end());
	}

	return path;
}

int main()
{
	
	int numberOfNodes, numberOfEdges, maxCharge, charge;
	cin >> numberOfNodes >> numberOfEdges >> maxCharge >> charge;

	Graph G(numberOfNodes);

	int start, end;
	cin >> start >> end;

	for(int i=0; i<numberOfNodes; i++)
	{
		int id, charger;
		cin >> id >> charger;
		Node* vPointer = new Node(id, charger);
		G.nodes.push_back(vPointer);
	}

	for (int i = 0; i < numberOfEdges; i++)
	{
    	int u = -1, v = -1, d=-1;
    	cin >> u >> v >> d;
    	G.nodes[u]->neighbors.push_back(G.nodes[v]);
    	G.nodes[v]->neighbors.push_back(G.nodes[u]);

		G.adjMatrix[u][v] = d;
		G.adjMatrix[v][u] = d;
  	}

	Graph simpG = simplifyGraph(&G, start, end, maxCharge, charge);

	simpG.dijkstra(simpG.findIndex(end));

	int tripDistance = simpG.nodes[simpG.findIndex(start)]->dist;

	if (tripDistance == INT_MAX)
	{
		cout<<"No suitable path from "<<start<<" to " << end << " exists"<<endl;
		return 1; 
	}

	vector<int> sPath = simplifiedPath(&simpG, start, end);

	vector<int> path = fullPath(&G, sPath);

	cout<<"Verify Path: "<<verifyPath(G, path, charge, maxCharge)<<endl;

	cout<<tripDistance<<": ";
	for (int i = 0; i < path.size(); i++)
	{
		cout<<path[i]<<" ";
	}
	cout<<endl;
}















