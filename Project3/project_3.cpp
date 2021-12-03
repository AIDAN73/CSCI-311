// CSCI 311 - Fall 2021
// project 3 
// Author: Aidan Murphree

#include "Node.h"
#include "Graph.h"
#include "priorityQueue.h"
#include <iostream>



//steps through the given path of the graph, making sure that the required edges exist and the car doesn't run out of gas
bool verifyPath (Graph G, vector<int> path, int i, int c)
{
	int charge = i;										//initialize charge
	Node* currentNode = &G.nodes[path[0]];				//starting point

	for (int j=1; j<path.size(); j++)													//check each step to get to the end
	{

		Node* targetNode = &G.nodes[path[j]];											//holds the node the car will be traveling to in this step

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
	G->dijkstra(start);
	cout<<"Completed dijkstra"<<endl;
	G->printDistances();
	Graph simpG;

	for (int i=0; i<G->nodes.size(); i++)
	{
		if(G->nodes[i].isCharger  ||  G->nodes[i].id == start  ||  G->nodes[i].id == end)
		{
			if(G->nodes[i].dist <= maxCharge)
				simpG.nodes.push_back(G->nodes[i]);
		}
	}
	cout<<"Added "<<simpG.nodes.size()+1<<" Nodes"<<endl;;
	simpG.initializeMatrix(simpG.nodes.size());

	

	for (int i=0; i<simpG.nodes.size(); i++)
	{
		Node* currentImportantNode = &simpG.nodes[i];

		cout<<endl<<"Doing neighbors of "<<currentImportantNode->id<<endl;

		G->dijkstra(currentImportantNode->id);				//get the distance of all nodes from this important node
		G->printDistances();

		for (int j=0; j<currentImportantNode->neighbors.size(); j++)
		{
			
			Node* currentImportantNeighbor = currentImportantNode->neighbors[j];

			simpG.adjMatrix[currentImportantNode->id][currentImportantNeighbor->id] = currentImportantNeighbor->dist;
			cout<<"Updating the distance of ("<<currentImportantNode->id<<", "<<currentImportantNeighbor->id<<")"<<endl;

			//simpG.adjMatrix[currentImportantNeighbor->id][currentImportantNode->id] = currentImportantNeighbor->dist;
			cout<<"Updating the distance of ("<<currentImportantNeighbor->id<<", "<<currentImportantNode->id<<")"<<endl;
		}

		for(int i=0; i<simpG.nodes.size(); i++)
		{
			simpG.nodes[i].displayNode();
			cout<<endl;
		}
		
		//simpG.printAdjMatrix();
		//simpG.printAdjList();
	}

	return simpG;
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
		Node v(id, charger);
		G.nodes.push_back(v);
	}

	for (int i = 0; i < numberOfEdges; i++)
	{
    	int u = -1, v = -1, d=-1;
    	cin >> u >> v >> d;
    	G.nodes[u].neighbors.push_back(&G.nodes[v]);
    	G.nodes[v].neighbors.push_back(&G.nodes[u]);

		G.adjMatrix[u][v] = d;
		G.adjMatrix[v][u] = d;
  	}


	G.printAdjList();
	cout<<endl;
	G.printAdjMatrix();

	//G.dijkstra(start);

	//vector<int> path{0, 1, 3, 2};
	//cout<<endl<<verifyPath(G, path, 15, 20)<<endl;

/*
	G.dijkstra(start);

	G.printDistances();

	G.dijkstra(2);

	G.printDistances();
*/

	simplifyGraph(&G, start, end, maxCharge, charge); 
	//Graph simpG = 
	//simpG.printAdjList();
	//simpG.printAdjMatrix();
	
}















