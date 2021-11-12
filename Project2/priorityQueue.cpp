// CSCI 311 - Fall 2021
// Airplane class
// Author: Aidan Murphree

#include "priorityQueue.h"
using namespace std;


//default constructor
priorityQueue::priorityQueue()
{}

bool priorityQueue::empty() { return (pQueue.size() == 0); }

int priorityQueue::size()   { return pQueue.size()-1; }

void priorityQueue::displayPriorityQueue()
{
    for (int i=0; i<pQueue.size(); i++)
	{
		pQueue[i]->displayPlane();
	}
}

//updates the subheap of the priority queue starting at index i, so that it is a minheap
void priorityQueue::minHeapify(int i)
{
	int left = 2 * i + 1;				//set up handy variables
	int right = 2 * i + 2;
	int minI = i;
	int heapSize = pQueue.size()-1;		//tracks the last filled index

	if (left <= heapSize && pQueue[left]->fuel < pQueue[i]->fuel)		//if the left child is smaller, set the min to the left child
	{
		minI = left;
	}
	if (right <= heapSize && pQueue[right]->fuel < pQueue[minI]->fuel)		//if the right child is the smallest, set the min to the right child
	{
		minI = right;
	}
	if (minI != i)
	{
		Airplane* temp = pQueue[i];				//swap the min with the current index, then check the swapped subheap
		pQueue[i] = pQueue[minI];
		pQueue[minI] = temp;
		minHeapify(minI);
	}
}

//pushes a plane into the minheap and sorts it into the correct position based on its fuel
void priorityQueue::push(Airplane* newPlane)
{
    pQueue.push_back(newPlane);					//put it in the last position
    int i = pQueue.size()-1;
	int parent = (i-1)/2;

    while(i>0 && pQueue[parent]->fuel > pQueue[i]->fuel)				//check it against its parents, move it up if it's has less fuel
	{
		Airplane* temp = pQueue[i];
		pQueue[i] = pQueue[parent];
		pQueue[parent] = temp;

		i = parent;
	}
}

//deletes and returns the plane with the lowest fuel, while maintaining the minheap
Airplane* priorityQueue::pop()
{
    Airplane* plane = pQueue[0];
    pQueue[0] = pQueue[pQueue.size()-1];
    pQueue.pop_back();
    minHeapify(0);
    return plane;
}

//deletes a plane from the priority queue based on its index. Used to move critically low fuel planes from the middle of the priority queue to the emergency arrivals 
Airplane* priorityQueue::deletePlane(int i)
{
	Airplane* plane = pQueue[i];
    pQueue[i] = pQueue[pQueue.size()-1];		//replace index with last value
    pQueue.pop_back();							//get rid of last value
	int parent = (i-1)/2;

	while (i>0 && pQueue[parent]->fuel > pQueue[i]->fuel)		//sends value up until it belongs
	{
		Airplane* temp = pQueue[i];
		pQueue[i] = pQueue[parent];
		pQueue[parent] = temp;
		i = parent;
	}

    minHeapify(i);				//re minheapify after all the shuffling
	return plane;
}

//returns but does not delete the first plane in the minheap
Airplane* priorityQueue::peek()
{
    return pQueue[0];
}

