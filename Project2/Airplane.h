// CSCI 311 - Fall 2021
// Airplane class header
// Author: Aidan Murphree

#include <string>
using std::string;


#ifndef AIRPLANE_H
#define AIRPLANE_H

class Airplane{
  public:
    int entranceTime;
    int ID;
    string intent;
    bool emergency;
    int fuel;
    
    
    Airplane();
    Airplane(int t, int id, string i, bool em, int f);
};

#endif