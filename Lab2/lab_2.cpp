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
    if (n==1) return 1;                 //One dot triangle
    return triangleNum(n-1) + n;        //each nth layer of the triangle adds n dots
}

int rFib(int n)
{
    if (n==0) return 0;             //base cases
    if (n==1) return 1;

    return (rFib(n-1)+rFib(n-2));           //run the sequence down to the base case, then build it up on the returns
}

int rSumHelper(const vector<int> &v, int i)
{
    if (i >= v.size()) return 0;                //if it's at the end of the index don't add anything

    return rSumHelper(v, i+1) + v[i];           //adds the current index and passes it to the next recursion at the next index
}

int rSum(const vector<int> &v)
{
    if (v.size() == 0) return 0;                //if the vector is empty, the sum is 0
    if (v.size() == 1) return v[0];             //if the vector has a single element, the sum is that element

    return rSumHelper(v, 1) + v[0];             //call the helper to do the actual recursion
}

int rMaxHelper(const vector<int> &v, int start)
{
    if (start==1)   return v[0];                //starts at the end and iterates to the beginning

    return max(v[start-1], rMaxHelper(v, start-1));         //returns the max of the current index and the rest of the vector                    
}

int rMax(const vector<int> &v)
{
    if (v.size() == 0) return INT_MIN;                      //special case
    return rMaxHelper(v, v.size());                         //find the max
}

bool isSorted(const vector<int> &v, int start, int end)
{
    if(v.size() == 0) return true;                          //if the vector is empty, it's sorted
    if (start+1 >= end) return true;                        //it we've checked the whole vector and haven't returned yet, it's sorted
    if (v[start] > v[start+1]) return false;                //if the current index is larger than the next, it's not sorted

    return isSorted(v, start+1, end);               //if it's been sorted so far, check the next two indexes against each other
}

bool isPalindromeHelper(string s, int start, int end)
{
    if (start >= end) return true;                      //if the ends have met or passed each other it's a palindrome

    if (s[start] != s[end])  return false;              //stop if the symmetrical letters don't match each other

    return isPalindromeHelper(s, start+1, end-1);           //check the next characters inside
}

bool isPalindrome(string s)
{
    if (s.size() <= 1) return true;                 //if it has one or zero characters, it's a palindrome
    return isPalindromeHelper(s, 0, s.size()-1);    //see if it's a palindrome
}

int rBinarySearch(const vector<int> &v, int low, int high, int target)
{
    if (low>high) return -1;                //if we've checked the whole vector it ain't in here

    if (low==high)                          //if the sides have become one
        {
            if (v[low]==target) return low;     //still have to check if the least value is it
            return -1;
        }

    int mid = (low + high)/2;               //look in the middle of the vector
    if (v[mid] == target) return mid;       //we've found it!!

    if (target < v[mid]) return rBinarySearch(v, low, mid-1, target);           //if middle is high, check with the middle as the maximum

    else return rBinarySearch(v, mid+1, high, target);          //if the middle is low, check with the middle as the minimum
}

bool rSubsetSum(const vector<int> &v, int start, int target)
{
    if (start >= v.size()) return false;

    if (target - v[start] == 0) return true; 

    if (rSubsetSum(v, start+1, target)) return true;
    if (rSubsetSum(v, start+1, target-v[start])) return true;
    
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
