// CSCI 311 - Fall 2021
// Airplane class header
// Author: Aidan Murphree

#include <string>
#include <iostream>
#include <iomanip>



#ifndef AIRPLANE_H
#define AIRPLANE_H

class Airplane
{
    public:

    int entranceTime;
    int ID;
    string intent;
    bool emergency;
    int fuel;
    
    
    
    Airplane();
    Airplane(int Time, int id, string Intent, bool Emergency, int Fuel);

    void displayPlane(); 
    
};

#endif