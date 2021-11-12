// CSCI 311 - Fall 2021
// Airplane class header
// Author: Aidan Murphree

#include <string>
#include <iostream>


#ifndef AIRPLANE_H
#define AIRPLANE_H

class Airplane
{
    public:

    int entranceTime;
    int ID;
    std::string intent;
    bool emergency;
    int fuel;
    
    
    
    Airplane();
    Airplane(int Time, int id, std::string Intent, bool Emergency, int Fuel);

    void displayPlane(); 
    
};

#endif