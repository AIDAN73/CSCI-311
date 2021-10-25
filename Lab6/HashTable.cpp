// CSCI 311 - Fall 2021
// Lab 6 - Hash Table cpp
// Author: Carter Tillquist

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "HashTable.h"

HashTable::HashTable()
{
    size = 11;
    table.resize(size, vector<string>(0));
    p = 31;
}

HashTable::HashTable(int s, int mult)
{
    size = s;
    table.resize(size, vector<string>(0));
    p = mult;
}

int HashTable::getSize() { return size; }
int HashTable::getNumElements() { return numElements;}
int HashTable::getP() { return p; }

void HashTable::printTable()
{
    cout << "HASH TABLE CONTENTS" << endl;
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].size() > 0)
        {
            cout << i << ": ";
            for (int j = 0; j < table[i].size() - 1; j++)
            {
                cout << table[i][j] << ", ";
            }
            cout << table[i][table[i].size() - 1] << endl;
        }
    }
}

int HashTable::search(string s)
{
    int hashedValue = hash(s);
    for (int i = 0; i < table[hashedValue].size(); i++)
    {
        if (table[hashedValue][i] == s) return hashedValue;
    }
    return -1;
}

void HashTable::insert(string s)
{
    int hashedValue = hash(s);
    table[hashedValue].push_back(s);
    numElements++;
}

void HashTable::remove(string s)
{
    int hashedValue = hash(s);
    for (int i = 0; i < table[hashedValue].size(); i++)
    {
        if (table[hashedValue][i] == s)  
        {
            table[hashedValue].erase(table[hashedValue].begin() + i);
            numElements--;
            return;
        }
    }
}

void HashTable::resize(int s)
{
    size = s;
    vector<vector<string>> resizedTable;
    resizedTable.resize(size, vector<string>(0));
    int hashedValue;

    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].size() > 0)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                hashedValue = hash(table[i][j]);
                resizedTable[hashedValue].push_back(table[i][j]);
            }
        }
    }
    table = resizedTable;

}

int HashTable::hash(string s)
{
    unsigned int stringSum = 0;

    for (int i=0; i < s.length(); i++)
    {
        stringSum += int(s[i])*pow(p, i);
    }

    stringSum = stringSum % size;

    return stringSum;
}