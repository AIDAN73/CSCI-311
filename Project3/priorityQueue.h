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
    Node* deleteNode(int i);
    Node* pop();
    Node* peek(); 
	int search(Node* n);
};

#endif