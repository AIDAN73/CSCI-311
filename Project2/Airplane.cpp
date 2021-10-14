// CSCI 311 - Fall 2021
// Airplane class
// Author: Carter Tillquist

#include "Airplane.h"

Airplane::Airplane()
{
    entranceTime = 0;
    ID = 0;
    intent = "departing";
    emergency = false;
    fuel = 0;
}

Airplane::Airplane(int t, int id, string i, bool em, int f)
{
    entranceTime = t;
    ID = id;
    intent = i;
    emergency = em;
    fuel = f;
}