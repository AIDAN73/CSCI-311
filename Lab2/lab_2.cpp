// CSCI 311 - Spring 2021
// Lab 2
// Author: Aidan Murphree

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

/**************************
 * Your solutions go here *
 * ************************/
int triangleNum(int n)
{
    if (n==1) return 1;
    return triangleNum(n-1) + n;
}

int rFib(int n)
{
    if (n==0) return 0;
    if (n==1) return 1;

    return (rFib(n-1)+rFib(n-2));
}

int rSumHelper(const vector<int> &v, int i)
{
    if (i >= v.size()) return 0;

    return rSumHelper(v, i+1) + v[i]; 
}

int rSum(const vector<int> &v)
{
    if (v.size() == 0) return 0;
    if (v.size() == 1) return v[0];

    return rSumHelper(v, 1) + v[0];
}

int rMaxHelper(const vector<int> &v, int start)
{
    if (start==1)   return v[0];   

    return max(v[start-1], rMaxHelper(v, start-1));                                 
}

int rMax(const vector<int> &v)
{
    if (v.size() == 0) return INT_MIN;
    return rMaxHelper(v, v.size());
}

bool isSorted(const vector<int> &v, int start, int end)
{
    if(v.size() == 0) return true;
    if (start+1 >= end) return true;
    if (v[start] > v[start+1]) return false; 

    return isSorted(v, start+1, end);
}

bool isPalindromeHelper(string s, int start, int end)
{
    if (start >= end) return true;                      //if the ends have met or passed each other it's a palindrome

    if (s[start] != s[end])  return false;              //stop if one of the pairs don't match each other

    return isPalindromeHelper(s, start+1, end-1);           //check the next characters inside
}

bool isPalindrome(string s)
{
    if (s.size() <= 1) return true;             //if it has one or zero characters, it's a palindrome
    return isPalindromeHelper(s, 0, s.size()-1);
}

int rBinarySearch(const vector<int> &v, int low, int high, int target)
{
    if (low>high) return -1;

    if (low==high)
        {
            if (v[low]==target) return low;
            return -1;
        }

    int mid = (low + high)/2;
    if (v[mid] == target) return mid;

    if (target < v[mid]) return rBinarySearch(v, low, mid, target);

    else return rBinarySearch(v, mid, high, target);   
}

bool rSubsetSum(const vector<int> &v, int start, int sum){
    return false;
}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);

int main()
{
    int question = -1;
    cout << "Question: ";
    cin >> question;

    int n = 0, start = 0, end = 0;
    vector<int> v;
    string s = "";
    switch (question)
    {
        case 1: //triangleNum
            cout << "Triangle Number n: ";
            cin >> n;
            cout << triangleNum(n) << endl;
            break;  

        case 2: //rFib
            cout << "Nth Fibonacci Number: ";
            cin >> n;
            cout << rFib(n) << endl;
            break;

        case 3: //rSum
            cout << "Recursive Sum Vector Size: ";
            cin >> n;
            cout << "Values: ";
            readIntVector(v, n);
            cout << rSum(v) << endl;
            break;

        case 4: //rMax
            cout << "Recursive Max Vector Size: ";
            cin >> n;
            cout << "Values: ";
            readIntVector(v, n);
            cout << rMax(v) << endl;
            break;

        case 5: //isSorted
            cout << "isSorted Vector Size: ";
            cin >> n;
            cout << "Start and End: ";
            cin >> start >> end;
            cout << "Values: ";
            readIntVector(v, n);
            cout << isSorted(v, start, end) << endl;
            break;

        case 6: //isPalindrome
            cout << "String: ";
            cin >> s;
            cout << isPalindrome(s) << endl;
            break;

        case 7: //rBinarySearch
            cout << "Binary Search Vector Size: ";
            cin >> n;
            cout << "Target: ";
            cin >> end;
            cout << "Values: ";
            readIntVector(v, n);
            cout << rBinarySearch(v, 0, v.size()-1, end) << endl;
            break;
      
        case 8: //rSubsetSum
            cout << "Subset Sum Vector Size: ";
            cin >> n;
            cout << "Target: ";
            cin >> end;
            cout << "Values: ";
            readIntVector(v, n);
            cout << rSubsetSum(v, 0, end) << endl;
            break;
    }

  return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n)
{
    int m = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        v.push_back(m);
    }
}
