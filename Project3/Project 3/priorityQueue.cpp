// CSCI 311 - Fall 2021
// Priority Queue cpp
// Author: Aidan Murphree

#include "priorityQueue.h"
using namespace std;


//default constructor
priorityQueue::priorityQueue()
{

}

bool priorityQueue::empty() { return (pQueue.size() == 0); }

int priorityQueue::size()   { return pQueue.size()-1; }

void priorityQueue::displayPriorityQueue()
{
    for (int i=0; i<pQueue.size(); i++)
	{
		pQueue[i]->displayNode();
		cout<<endl;
	}
	cout<<endl;
}


//updates the subheap of the priority queue starting at index i, so that it is a minheap. Allows the root of the subheap to move up the rest of the tree
void priorityQueue::minHeapify(int i)
{
	int left = 2 * i + 1;				//set up handy variables
	int right = 2 * i + 2;
	int parent = (i-1)/2;
	int minI = i;
	int heapSize = pQueue.size()-1;		//tracks the last filled index

	if (pQueue[parent] != pQueue[i] && pQueue[parent]->dist > pQueue[i]->dist)
	{
		Node* temp = pQueue[i];				//swap the min with the current index, then check the swapped subheap
		pQueue[i] = pQueue[parent];
		pQueue[parent] = temp;
		minHeapify(parent);
	}

	if (left <= heapSize && pQueue[left]->dist < pQueue[i]->dist)		//if the left child is smaller, set the min to the left child
	{
		minI = left;
	}

	if (right <= heapSize && pQueue[right]->dist < pQueue[minI]->dist)		//if the right child is the smallest, set the min to the right child
	{
		minI = right;
	}

	if (minI != i)
	{
		Node* temp = pQueue[i];				//swap the min with the current index, then check the swapped subheap
		pQueue[i] = pQueue[minI];
		pQueue[minI] = temp;
		minHeapify(minI);
	}
}

//pushes a node into the minheap and sorts it into the correct position based on its dist
void priorityQueue::push(Node* newNode)
{
    pQueue.push_back(newNode);					//put it in the last position
    int i = pQueue.size()-1;
	int parent = (i-1)/2;

    while(i>0 && pQueue[parent]->dist > pQueue[i]->dist)				//check it against its parents, move it up if it's has less dist
	{
		Node* temp = pQueue[i];
		pQueue[i] = pQueue[parent];
		pQueue[parent] = temp;

		i = parent;
		parent = (i-1)/2;
	}
}

//deletes and returns the node with the lowest dist, while maintaining the minheap
Node* priorityQueue::pop()
{
    Node* topNode = pQueue[0];
    pQueue[0] = pQueue[pQueue.size()-1];
    pQueue.pop_back();
    minHeapify(0);
    return topNode;
}

//returns the index of the node n in the priority queue
int priorityQueue::search(Node* n)
{
	for (int i=0; i<pQueue.size(); i++)
	{
		if (pQueue[i] == n) return i;
	}
	return -1;
}