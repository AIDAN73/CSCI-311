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

Graph simplifyGraph (Graph* G, int start, int end, int maxCharge, int charge)
{
	cout<<"Start: "<<start<<" End: "<<end<<" Max Charge: "<<maxCharge<<" Charge: "<<charge<<endl;

	Graph simpG;

	//add all the important nodes to the simplified graph. No edges currently
	for (int i=0; i<G->nodes.size(); i++)
	{
		if(G->nodes[i]->isCharger  ||  G->nodes[i]->id == start  ||  G->nodes[i]->id == end)
		{
			Node* v = new Node(G->nodes[i]->id, G->nodes[i]->isCharger);
			simpG.nodes.push_back(v);
			cout<<"Added Node "<<G->nodes[i]->id<<endl;
		}
	}
	cout<<"Added "<<simpG.nodes.size()<<" Nodes"<<endl;;
	simpG.initializeMatrix(simpG.nodes.size());					//resize the simplified graph's adjacency matrix


	for (int i=0; i<simpG.nodes.size(); i++)
	{
		Node* currentImportantNode = simpG.nodes[i];

		cout<<endl<<"Connecting node "<<currentImportantNode->id<<endl;

		G->dijkstra(currentImportantNode->id);				//get the distance of all nodes from this important node
		G->printDistances();

		for (int j=0; j<simpG.nodes.size(); j++)
		{
			Node* currentImportantNeighbor = simpG.nodes[j];
			currentImportantNeighbor->dist = G->nodes[currentImportantNeighbor->id]->dist;
			//cout<<"Considering neighbor "<<currentImportantNeighbor->id<<endl;

			if(currentImportantNode->id == start)
			{
				
				if (currentImportantNeighbor->dist <= charge  &&  currentImportantNeighbor!=currentImportantNode)
				{
					simpG.nodes[i]->neighbors.push_back(simpG.nodes[j]);
					simpG.adjMatrix[i][j] = currentImportantNeighbor->dist;
					simpG.adjMatrix[j][i] = currentImportantNeighbor->dist;
					cout<<"Distance from start node "<<simpG.nodes[i]->id<<" to "<<simpG.nodes[j]->id<<" is "<<currentImportantNeighbor->dist<<endl;
				}
				else cout<<"Edge from start node "<<simpG.nodes[i]->id<<" to "<<simpG.nodes[j]->id<<" not included"<<endl;
			}

			else
			{
				if (currentImportantNeighbor->dist <= maxCharge   &&  currentImportantNeighbor!=currentImportantNode)
				{
					simpG.nodes[i]->neighbors.push_back(simpG.nodes[j]);
					simpG.adjMatrix[i][j] = currentImportantNeighbor->dist;
					simpG.adjMatrix[j][i] = currentImportantNeighbor->dist;
					cout<<"Distance from "<<simpG.nodes[i]->id<<" to "<<simpG.nodes[j]->id<<" is "<<currentImportantNeighbor->dist<<endl;
				}
				else cout<<"Edge from "<<simpG.nodes[i]->id<<" to "<<simpG.nodes[j]->id<<" not included"<<endl;
				
			}
		}
		/*
		cout<<endl<<"Neighbors of "<<simpG.nodes[i]->id<<": ";
		for(int k=0; k<simpG.nodes[i]->neighbors.size(); k++)
		{
			cout<<simpG.nodes[i]->neighbors[k]->id<<", ";
		}
		cout<<endl;
		*/
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
	currentNode = G->nodes[sPath[sPath.size()-1]]				//initialize currentNode as end of paths
	vector<int> path = {}

	for (int i=sPath.size()-1; i>=0; i--)
	{
		Node* currentNode = G->nodes[i]
		
		vector<int> subPath = {};

		path.push_back(currentNode->id);

		while (currentNode->predecessor != nullptr)
		{
			path.push_back(currentNode->predecessor->id);
			currentNode = currentNode->predecessor;
		}
		

	}
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
		//Node v(id, charger);
		Node* vPointer = new Node(id, charger);
		G.nodes.push_back(vPointer);
		cout<<endl;
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

	G.printAdjList();
	cout<<endl;
	G.printAdjMatrix();
	
	Graph simpG = simplifyGraph(&G, start, end, maxCharge, charge);

	cout<<endl;

	simpG.printAdjMatrix();
	simpG.printAdjList();

	simpG.dijkstra(simpG.findIndex(end));

	if (simpG.nodes[simpG.findIndex(start)]->dist == INT_MAX)
	{
		cout<<"No suitable path from "<<start<<" to " << end << " exists";
		return 1; 
	}

	vector<int> path = simplifiedPath(&simpG, start, end);

	cout<<endl<<"Simplified Path: "<< path[0];
	for (int i = 1; i < path.size(); i++)
	{
		cout<<", "<<path[i];
	}
	cout<<endl;

}















