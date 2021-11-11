#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <string>
#include <vector>
#include <iostream>
#include "Airplane.h"

class priorityQueue
{
    private:
    int queueSize;
    void minHeapify(int i);

    public:

    priorityQueue();
    bool empty(); 
    int size();
    std::vector<Airplane*> pQueue;
    void displayPriorityQueue();
    void push(Airplane*);
    Airplane* deletePlane(int i);
    Airplane* pop();
    Airplane* peek(); 
};

#endif