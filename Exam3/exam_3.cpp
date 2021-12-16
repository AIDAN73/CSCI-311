// CSCI 311 - Fall 2021
// Exam 3
// Author: ** YOUR NAME HERE ***

#include <iostream>
#include <string>
#include <algorithm>
#include "Graph.h"
#include "Node.h"
using namespace std;

/************************************************************************************
 * A simple struct to represent directed edges                                      *
 * from - Node - the node at which the edge starts                                  *
 * to - Node - the node at which the edge ends                                      *
 * operator< - bool - defines an orderamong edges based on node ids of from then to *
 * **********************************************************************************/
struct Edge
{
	Node from;
	Node to;
	bool operator<(const Edge &v) const
	{
		if (from.id < v.from.id)
		{
			return true;
		}
		if (from.id == v.from.id && to.id < v.to.id)
		{
			return true;
		}
		return false;
	}
};

/********************************************************************************************************
 * QUESTION 1                                                                                           *
 * Write a function that prints the expression associated with the given tree rooted at the given node. *
 * Note that the edges of T will be directed away from the root.                                        *
 * ******************************************************************************************************/

void printExpressionRecursive(Graph T, int root)
{
	Node* n = &T.nodes[root];

	//cout<<"Current node: "<<n->data<<endl;
	if (n->neighbors.size() != 0)	
	{	
		printExpressionRecursive(T, n->neighbors[0]->id);
		cout<<n->data;
		printExpressionRecursive(T, n->neighbors[1]->id);
	}
	else cout<<n->data;
}


void printExpression(Graph T, int root)
{
	printExpressionRecursive(T, root);
	//cout<<endl;
}

/****************************************************************************************************************************************************
 * QUESTION 2                                                                                                                                       *
 * Write a function that makes and returns an n by m grid graph. Vertices must be labeled in increasing order from left to right and top to bottom. *
 * **************************************************************************************************************************************************/
Graph makeGrid(int r, int c)
{
	Graph G;

	for (int i=0; i<r*c; i++)
	{
		Node n(i, to_string(i)); 
		G.nodes.push_back(n);
	}



	//form rows
	for (int i=0; i<r*c; i+=c)				//start at the beginning of each row, stop when you run out of columns
	{
		for (int j=0; j<c-1; j++)
		{
			int index = i+j;
			int right = index+1;

			G.nodes[index].neighbors.push_back(&G.nodes[right]);					//center to right
			G.nodes[right].neighbors.push_back(&G.nodes[index]);					//right to center

		}
	}

	//form columns
	for (int i=0; i<c; i++)				//start at the top of each column, stop when you run out of rows
	{
		for (int j=0; i+j<r*c-c; j+=c)
		{
			int index = i+j;
			int below = index+c;

			G.nodes[index].neighbors.push_back(&G.nodes[below]);					//center to right
			G.nodes[below].neighbors.push_back(&G.nodes[index]);					//right to center

		}
	}
	return G;
}

/***********************************************************************************************************
 * QUESTION 3                                                                                              *
 * Write a function that, given a directed graph, fills vectors with tree, forward, back, and cross edges. *
 * *********************************************************************************************************/
// This function signature is provided if you would like to use it but you are not required to do so
int classifyEdgesRecur(int s, int time, Graph &G, vector<Edge> &tree, vector<Edge> &forward, vector<Edge> &back, vector<Edge> &cross)
{
	time++;
	G.nodes[s].discovered = time;			//set discovered time
	G.nodes[s].visited = true;

	for (int i=0; i < G.nodes[s].neighbors.size(); i++)				//visit all the neighbors
	{
		if (G.nodes[s].neighbors[i]->visited == false)				//if the node hasn't been visited before, explore it further before continueing with this node
		{
			G.nodes[s].neighbors[i]->predecessor = &G.nodes[s];
			time = classifyEdgesRecur( G.nodes[s].neighbors[i]->id , time, G, tree, forward, back, cross);
		}
	}
	time++;
	G.nodes[s].finished = time;				//after visiting all the neighbors and subneighbors, mark finished time
	return time;							//return time so it can be used for other subgraphs
}

void classifyEdges(Graph &G, vector<Edge> &tree, vector<Edge> &forward, vector<Edge> &back, vector<Edge> &cross)
{
	//perform DFS from root to set the discovered and finished times
	for (int i=0; i < G.nodes.size(); i++)
	{
		G.nodes[i].visited = false;			//sets a baseline for all the nodes in the graph
		G.nodes[i].predecessor = nullptr;
		G.nodes[i].discovered = -1;
		G.nodes[i].finished = -1;
	}

	int time = 0;
	for (int j=0; j<G.nodes.size(); j++)			//ensures that all nodes in the graph are visited, even if they're disconnected
	{
		if (G.nodes[j].visited == false)
		{
			time = classifyEdgesRecur(j, time, G, tree, forward, back, cross);			//recursively visits all the neighbors of the node, starting with itself
		}
	}

	for (int i=0; i<G.nodes.size(); i++)
	{
		Node* currentNode = &G.nodes[i];

		for (int j=0; j<G.nodes[i].neighbors.size(); j++)
		{
			Node* currentNeighbor = G.nodes[i].neighbors[j];

			Edge e; 												//declare an edge to sort
			e.from = *currentNode;
			e.to = *currentNeighbor;

			if (currentNeighbor->predecessor == currentNode)	tree.push_back(e);			//tree edge if the second's predecessor is the first

			else if ((currentNode->discovered < currentNeighbor->discovered) && (currentNode->finished > currentNeighbor->finished))	//forward edge if second discovered before and finished after
			{
				forward.push_back(e);
			}

			else if ((currentNode->discovered > currentNeighbor->discovered) && (currentNode->finished < currentNeighbor->finished))	//back edge if second discovered after and finished before
			{
				back.push_back(e);
			}

			else if ((currentNode->discovered > currentNeighbor->discovered) && (currentNode->finished > currentNeighbor->finished))	//cross edge if second discovered after and finished after
			{
				cross.push_back(e);
			}

			else if ((currentNode->discovered < currentNeighbor->discovered) && (currentNode->finished < currentNeighbor->finished))	//cross edge if second discovered after and finished after
			{
				cross.push_back(e);
			}
		}
	}




//way of identifying tree edges: predecessors show all tree edges

//


}

/********************************************************************************************************
 * TESTING                                                                                              *
 * When testing your functions, the main below expects input in a certain format for each question.     *
 * The first line of input should always the question number (1-3). More details are provided regarding *
 * the input for each question in the main itself.                                                      *
 * To test, you may run program and provide input by hand or you may provide a file as input directly   *
 * from the terminal For example, suppose you compile your program to a.out and that you have a file    *
 * named "test_1.in" containing input in the appropriate format for question 1. Then running            *
 * ./a.out < test_1.in                                                                                  *
 * will run your program using the lines of test_1.in as input. This can be a good way to save time and *
 * to save different test cases when testing your code.                                                 *
 * ******************************************************************************************************/
Graph makeAST();
Graph makeDirectedGraph();
int main()
{
	int question = -1;
	cin >> question;

	// Declaring variables to use in the switch
	int n = -1, m = -1;
	vector<Edge> tree;
	vector<Edge> forward;
	vector<Edge> back;
	vector<Edge> cross;

	switch (question)
	{
	case 1:
	{ // print expression
		/*************************************************************************************
		 * Input format:                                                                     *
		 * 1                                                                                 *
		 * the number of nodes and edges in the tree separated by a space                    *
		 * pairs of node ids and the string data to be held in the node separated by a space *
		 * pairs of space separated integers representing tree edges                         *
		 * ***********************************************************************************/
		cout << "PRINT EXPRESSION" << endl;
		Graph T = makeAST();
		printExpression(T, 0);
		break;
	}
	case 2:
	{ // make grid
		/*******************************************************************
		 * Input format:                                                   *
		 * 2                                                               *
		 * the number of rows and columns in the grid separated by a space *
		 * *****************************************************************/
		cout << "MAKE GRID" << endl;
		cin >> n >> m;
		Graph G = makeGrid(n, m);
		G.printAdjList();
		break;
	}
	case 3:
	{ // classify edges
		/*******************************************************************
		 * Input format:                                                   *
		 * 3                                                               *
		 * the number of nodes and edges in the graph separated by a space *
		 * pairs of space separated integers representing directed edges   *
		 * *****************************************************************/
		cout << "CLASSIFY EDGES" << endl;
		Graph G = makeDirectedGraph();
		classifyEdges(G, tree, forward, back, cross);
		sort(tree.begin(), tree.end());
		sort(forward.begin(), forward.end());
		sort(back.begin(), back.end());
		sort(cross.begin(), cross.end());
		cout << "Tree edges: ";
		for (int i = 0; i < tree.size(); i++)
		{
			cout << "(" << tree[i].from.id << ", " << tree[i].to.id << ") ";
		}
		cout << endl;
		cout << "Forward edges: ";
		for (int i = 0; i < forward.size(); i++)
		{
			cout << "(" << forward[i].from.id << ", " << forward[i].to.id << ") ";
		}
		cout << endl;
		cout << "Back edges: ";
		for (int i = 0; i < back.size(); i++)
		{
			cout << "(" << back[i].from.id << ", " << back[i].to.id << ") ";
		}
		cout << endl;
		cout << "Cross edges: ";
		for (int i = 0; i < cross.size(); i++)
		{
			cout << "(" << cross[i].from.id << ", " << cross[i].to.id << ") ";
		}
		cout << endl;
		break;
	}
	default:
		break;
	}

	return 0;
}

/*****************************************************************************************************************************
 * A function to collect input from the user for making an abstract syntax tree. The first line of input should include two  *
 * integers, n and m, representing the number of nodes and the number of edges in the graph. The following n lines each      *
 * contain an integer representing a node and a string representing the data to be held in that node. The following m lines  *
 * each contain a pair of space separated integers representing directed edges in the graph.                                 *
 * return - Graph - an abstract syntax tree constructed based on the user input                                                              *
 * ***************************************************************************************************************************/
Graph makeAST()
{
	int n = 0, m = 0;
	cin >> n >> m;
	int u = -1, v = -1;
	string data = "";
	Graph G;
	for (int i = 0; i < n; i++)
	{
		cin >> u >> data;
		Node w(u, data);
		G.nodes.push_back(w);
	}
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		G.nodes[u].neighbors.push_back(&G.nodes[v]);
	}
	return G;
}



/*********************************************************************************************************************
 * A function to collect input from the user for making a directed graph. The first line of input should include two *
 * integers, n and m, representing the number of nodes and the number of edges in the graph. The following m lines   *
 * each contain a pair of space separated integers representing directed edges in the graph.                         *
 * return - Graph - a graph constructed based on the user input                                                      *
 * *******************************************************************************************************************/
Graph makeDirectedGraph()
{
	int n = 0, m = 0;
	cin >> n >> m;
	Graph G;
	for (int i = 0; i < n; i++)
	{
		Node v(i);
		G.nodes.push_back(v);
	}
	for (int i = 0; i < m; i++)
	{
		int u = -1, v = -1;
		cin >> u >> v;
		G.nodes[u].neighbors.push_back(&G.nodes[v]);
	}
	return G;
}