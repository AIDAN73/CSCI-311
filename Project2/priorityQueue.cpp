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

void priorityQueue::push(Airplane*)
{

}

Airplane* priorityQueue::pop()
{

}

Airplane* priorityQueue::peek()
{
    return pQueue[0];
}