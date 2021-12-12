#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <limits.h>
using namespace std;

class Node
{
public:
	int id;
	int dist;
	bool isCharger;

	bool visited;
	Node *predecessor;
	vector<Node *> neighbors;

	Node()
	{
		id = 0;
		isCharger = false;

		bool visited = false;
		dist = INT_MAX;
		predecessor = nullptr;
		neighbors = {};
	}

	Node(int i, bool c)
	{
		id = i;
		isCharger = c;

		bool visited = false;
		dist = INT_MAX;
		predecessor = nullptr;
		neighbors = {};
	}

	Node(int i, bool c, int d)
	{
		id = i;
		isCharger = c;

		bool visited = false;
		dist = d;
		predecessor = nullptr;
		neighbors = {};
	}

	void displayNode()
	{
		cout << "ID: " << id << "\tDist: " << dist;
	}
};

#endif



#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

class priorityQueue
{
    private:

    public:
	std::vector<Node*> pQueue;
	
    priorityQueue()
	{}

	bool empty() { return (pQueue.size() == 0); }

	int size() { return pQueue.size()-1; }

	void displayPriorityQueue()
	{
		for (int i = 0; i < pQueue.size(); i++)
		{
			pQueue[i]->displayNode();
			cout << endl;
		}
		cout << endl;
	}

	// updates the subheap of the priority queue starting at index i, so that it is a minheap. Allows the root of the subheap to move up the rest of the tree
	void minHeapify(int i)
	{
		int left = 2 * i + 1; // set up handy variables
		int right = 2 * i + 2;
		int parent = (i - 1) / 2;
		int minI = i;
		int heapSize = pQueue.size() - 1; // tracks the last filled index

		if (pQueue[parent] != pQueue[i] && pQueue[parent]->dist > pQueue[i]->dist)
		{
			Node *temp = pQueue[i]; // swap the min with the current index, then check the swapped subheap
			pQueue[i] = pQueue[parent];
			pQueue[parent] = temp;
			minHeapify(parent);
		}

		if (left <= heapSize && pQueue[left]->dist < pQueue[i]->dist) // if the left child is smaller, set the min to the left child
		{
			minI = left;
		}

		if (right <= heapSize && pQueue[right]->dist < pQueue[minI]->dist) // if the right child is the smallest, set the min to the right child
		{
			minI = right;
		}

		if (minI != i)
		{
			Node *temp = pQueue[i]; // swap the min with the current index, then check the swapped subheap
			pQueue[i] = pQueue[minI];
			pQueue[minI] = temp;
			minHeapify(minI);
		}
	}

	// pushes a node into the minheap and sorts it into the correct position based on its dist
	void push(Node *newNode)
	{
		pQueue.push_back(newNode); // put it in the last position
		int i = pQueue.size() - 1;
		int parent = (i - 1) / 2;

		while (i > 0 && pQueue[parent]->dist > pQueue[i]->dist) // check it against its parents, move it up if it's has less dist
		{
			Node *temp = pQueue[i];
			pQueue[i] = pQueue[parent];
			pQueue[parent] = temp;

			i = parent;
			parent = (i - 1) / 2;
		}
	}

	// deletes and returns the node with the lowest dist, while maintaining the minheap
	Node *pop()
	{
		Node *topNode = pQueue[0];
		pQueue[0] = pQueue[pQueue.size() - 1];
		pQueue.pop_back();
		minHeapify(0);
		return topNode;
	}

	// returns the index of the node n in the priority queue
	int search(Node *n)
	{
		for (int i = 0; i < pQueue.size(); i++)
		{
			if (pQueue[i] == n)
				return i;
		}
		return -1;
	}
};

#endif


#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
	vector<Node*> nodes;
	vector<vector<int>> adjMatrix;

	Graph()
	{
		nodes = {};
		adjMatrix = {};
	}

	Graph(int i)
	{
		nodes = {};

		vector<int> vect(i, -1);
		vector<vector<int>> twoDVect(i, vect);
		adjMatrix = twoDVect;
	}

	// resizes the adjacency matrix of the graph to the size inputted
	void initializeMatrix(int i)
	{
		vector<int> vect(i, -1);
		vector<vector<int>> twoDVect(i, vect);
		adjMatrix = twoDVect;
	}

	// returns of the index of the node in the graphs node list with an id of target
	int findIndex(int target)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i]->id == target)
				return i;
		}
		return -1;
	}

	// prints all the neighbors of all the nodes in a tree, used for debugging. Simply iterates through all the nodes and prints their neighbors and distances in the form
	// Node: (neighbor, distance), (neighbor2, distance2)...
	void printAdjList()
	{
		cout << "Adjacency List: " << endl;
		for (int i = 0; i < nodes.size(); i++) // for each node
		{
			Node *currentNode = nodes[i];
			cout << currentNode->id << ": ";
			for (int j = 0; j < currentNode->neighbors.size(); j++) // for each of the node's neighbors
			{
				Node *currentNeighbor = currentNode->neighbors[j];
				cout << "(" << currentNeighbor->id << ", " << adjMatrix[i][findIndex(currentNeighbor->id)] << ") "; // print the neighbor's ID and distance
			}
			cout << endl;
		}
	}

	// prints the adjacency matrix of the graph, used for debugging
	void printAdjMatrix()
	{
		cout << "Adjacency Matrix: " << endl;
		for (int i = 0; i < adjMatrix.size(); i++) // print top axis
		{
			cout << "\t" << nodes[i]->id;
		}

		cout << endl;

		for (int i = 0; i < adjMatrix.size(); i++)
		{
			cout << nodes[i]->id; // print this line of the left axis
			for (int j = 0; j < adjMatrix[i].size(); j++)
			{
				cout << "\t";
				if (adjMatrix[i][j] != -1)
					cout << adjMatrix[i][j]; // print the edge length between nodes[i] and nodes[j] if it exists
			}
			cout << endl;
		}
		cout << endl;
	}

	// prints a simple list of each node is the nodes list's set distance. Used for checking that dijkstra's worked
	void printDistances()
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			cout << nodes[i]->id << ": " << nodes[i]->dist << endl;
		}
		cout << endl;
	}

	// dijkstra's algorithm implemented with a minHeap. Finds the minimum distances to each node from a given starting node s
	void dijkstra(int s)
	{
		for (int i = 0; i < nodes.size(); i++) // set all nodes to a baseline
		{
			nodes[i]->dist = INT_MAX;
			nodes[i]->predecessor = nullptr; // predecessor is used for working out the path
		}

		nodes[s]->dist = 0; // starting node distance is always 0

		priorityQueue minQueue;

		for (int j = 0; j < nodes.size(); j++) // this is the slow method of initializing a minQueue, but oh well
		{
			minQueue.push(nodes[j]);
		}

		while (!minQueue.empty())
		{
			Node *currentNode = minQueue.pop();

			for (int k = 0; k < currentNode->neighbors.size(); k++) // for each of the curent node's neighbors
			{
				Node *currentNeighbor = currentNode->neighbors[k]; // holds a pointer to the current neighbor

				int possiblePathDistance = currentNode->dist + adjMatrix[findIndex(currentNode->id)][findIndex(currentNeighbor->id)];

				if (currentNeighbor->dist > possiblePathDistance && possiblePathDistance > 0) // if the neighbor's current distance is larger than the other path
				{
					currentNeighbor->dist = possiblePathDistance;		   // set it to the new path's distance
					currentNeighbor->predecessor = currentNode;			   // set the predecessor
					minQueue.minHeapify(minQueue.search(currentNeighbor)); // reheapify after changing the values in the minHeap
				}
			}
		}
	}
};

#endif


/*******************************************************************************
******************************MAIN SECTION OF CODE******************************
*******************************************************************************/

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


