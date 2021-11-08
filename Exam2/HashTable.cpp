// CSCI 311 - Fall 2021
// Lab 6 - Hash Table cpp
// Author: Carter Tillquist

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "HashTable.h"

//default constructor uses size of 11 and p of 31
HashTable::HashTable()
{
    size = 11;
    table.resize(size, vector<string>(0));              //put all the buckets in the 1st vector
    p = 31;
}

//parameterized constructor that lets you choose the hash table size and p value
HashTable::HashTable(int s, int mult)
{
    size = s;
    table.resize(size, vector<string>(0));
    p = mult;
}

//get functions for the private values
int HashTable::getSize() { return size; }
int HashTable::getNumElements() { return numElements;}
int HashTable::getP() { return p; }

//prints all the populated buckets of the hash table
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

//returns the hash bucket of an inputted string, if it exists in the table
int HashTable::search(string s)
{
    int hashedValue = hash(s);                                  //hash the value
    for (int i = 0; i < table[hashedValue].size(); i++)         //search one by one through the appropriate bucket for the string
    {
        if (table[hashedValue][i] == s) return hashedValue;     //if it's found, return the hash bucket
    }
    return -1;
}

//inserts an inputted string into the table in the correct bucket. Hashes the string and then pushes it to the back of the bucket
void HashTable::insert(string s)
{
    int hashedValue = hash(s);          
    table[hashedValue].push_back(s);      
    numElements++;
}

//removes an inputted string from the table. Does nothing if the string does not exist in the table already
void HashTable::remove(string s)
{
    int hashedValue = hash(s);
    for (int i = 0; i < table[hashedValue].size(); i++)     //search the appropriate bucket one by one for the string
    {
        if (table[hashedValue][i] == s)         
        {
            table[hashedValue].erase(table[hashedValue].begin() + i);       //if we found it, erase the string and update the amount of elements
            numElements--;
            return;
        }
    }
}

//changes the amount of buckets in the hash table. 
void HashTable::resize(int s)
{
    size = s;                                                   //update the amount of buckets

    vector<vector<string>> resizedTable;                        //create new 2d vector to sort the values into
    resizedTable.resize(size, vector<string>(0));               

    int hashedValue;                                 //avoid reinitializing this value every loop

    for (int i = 0; i < table.size(); i++)			//loop though every bucket
    {
        if (table[i].size() > 0)					//if the bucket isn't empty, loop through the entirety of it
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                hashedValue = hash(table[i][j]);							//rehash the value and insert it into the new table
                resizedTable[hashedValue].push_back(table[i][j]);
            }
        }
    }
    table = resizedTable;				//update the table to the resized one

}

//polynomial rolling hash function to determine the correct bucket for the inputted string
int HashTable::hash(string s)
{
    unsigned int stringSum = 0;					//unsigned to make overflows rarer

    for (int i=0; i < s.length(); i++)
    {
        stringSum += int(s[i])*pow(p, i);			//hashing function, based on string length
    }

    stringSum = stringSum % size;				//mod it to fit in the amount of buckets

    return stringSum;
}