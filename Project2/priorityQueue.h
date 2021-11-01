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
    std::vector<Airplane*> pQueue;

    public:

    priorityQueue();
    bool empty(); 
    int size();
    void push(Airplane*);
    Airplane* pop();
    Airplane* peek(); 
};

#endif