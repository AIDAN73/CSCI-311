// CSCI 311 - Fall 2021
// Airplane class
// Author: Aidan Murphree

#include "Airplane.h"
using namespace std;

//default constructor
Airplane::Airplane()
{
    entranceTime = 0;
    ID = 0;
    intent = "departing";
    emergency = false;
    fuel = 0;
}

//parameterized constructor
Airplane::Airplane(int Time, int id, string Intent, bool Emergency, int Fuel)
{
    entranceTime = Time;
    ID = id;
    intent = Intent;
    emergency = Emergency;
    fuel = Fuel;
}

//outputs the info for a plane according to the requirements
void Airplane::displayPlane()
{
    cout<<boolalpha << entranceTime << " " << ID << " " << intent << " " << emergency << " " << fuel << endl;
}