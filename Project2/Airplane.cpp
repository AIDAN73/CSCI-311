// CSCI 311 - Fall 2021
// Airplane class
// Author: Aidan Murphree

#include "Airplane.h"
using namespace std;

Airplane::Airplane()
{
    entranceTime = 0;
    ID = 0;
    intent = "departing";
    emergency = false;
    fuel = 0;
}

Airplane::Airplane(int Time, int id, string Intent, bool Emergency, int Fuel)
{
    entranceTime = Time;
    ID = id;
    intent = Intent;
    emergency = Emergency;
    fuel = Fuel;
}

void Airplane::displayPlane()
{
    
    cout<<left<<boolalpha<<"ID: "<<setw(5)<<ID<<"Entrance Time: "<<setw(4)<<entranceTime<<"Intent: "<<setw(12)<<intent<<"Emergency: "<<setw(7)<<emergency<<"Fuel: "<<fuel<<endl;
}