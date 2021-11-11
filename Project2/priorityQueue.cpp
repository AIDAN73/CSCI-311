// CSCI 311 - Fall 2021
// Airplane class
// Author: Aidan Murphree

#include "priorityQueue.h"
using namespace std;


priorityQueue::priorityQueue()
{
    queueSize = 0;
    if (pQueue.size()==0); 
}

bool priorityQueue::empty()
{
    if (pQueue.size() == 0) return true;
    return false;
}

int priorityQueue::size()   { return queueSize; }

void priorityQueue::displayPriorityQueue()
{
    for (int i=0; i<pQueue.size(); i++)
	{
		pQueue[i]->displayPlane();
	}
}

void priorityQueue::minHeapify(int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int minI = i;
	int heapSize = pQueue.size()-1;

	if (left <= heapSize && pQueue[left]->fuel < pQueue[i]->fuel)
	{
		minI = left;
	}
	if (right <= heapSize && pQueue[right]->fuel < pQueue[minI]->fuel)
	{
		minI = right;
	}
	if (minI != i)
	{
		Airplane* temp = pQueue[i];
		pQueue[i] = pQueue[minI];
		pQueue[minI] = temp;
		minHeapify(minI);
	}
}

void priorityQueue::push(Airplane* newPlane)
{
    pQueue.push_back(newPlane);
    int i = pQueue.size()-1;
	int parent = (i-1)/2;

    while(i>0 && pQueue[parent]->fuel > pQueue[i]->fuel)
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

Airplane* priorityQueue::peek()
{
    return pQueue[0];
}

