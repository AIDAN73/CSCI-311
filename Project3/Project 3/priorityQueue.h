#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <string>
#include <vector>
#include <iostream>
#include "Node.h"

class priorityQueue
{
    private:

    public:

	void minHeapify(int i);
    priorityQueue();
    bool empty(); 
    int size();
    std::vector<Node*> pQueue;
    void displayPriorityQueue();
    void push(Node*);
    Node* pop();
	int search(Node* n);
};

#endif