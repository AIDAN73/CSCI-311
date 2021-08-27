// CSCI 311 - Spring 2021
// Lab 1
// Author: Aidan Murphree

#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
using namespace std;

/**************************
 * Your solutions go here *
 * ************************/
int collatzLength(int n)
{
    int colNum=0;           //collatz number
    while (n!=1)            //iterate until at 1, end of conjecture
    {
        if (n%2==0) n=n/2;          //even case
        else n = 3*n+1;             //odd case
        colNum++;                   //count up
    }
    return colNum;
}

void printStats(const vector<int> &v)
{
    if (v.size()==0)
    {
        cout<<"Empty vector"<<endl;
        return;

    } 
    int min = v[0];                 //setup stats to write
    int max = v[0];
    double mean = 0;

    for (int i=0; i<v.size(); i++)          //iterate through array
    {
        if (v[i] < min) min = v[i];         //min case, max case
        if (v[i] > max) max = v[i];
        mean += v[i];                       //add up mean
    }
    mean = mean / v.size();                 //divide mean
    cout<<min <<" "<<mean<<" "<<max<<endl;          //display
}

int sumMultiples(const vector<int> &v, int n)
{
    int sum=0;
    for (int i=0; i<n; i++)                     //check each number up to max
    {
        for (int j=0; j<v.size(); j++)          //check each element in the array to see if it's a multiple
        {
            if (i % v[j] == 0)                  //if it's a multiple
            {
                sum += i;                       //then add the number being checked to the sum
                break;                      //and stop checking through the array (don't add duplicates)
            }
        }
    }
    return sum;
}

void greaterThanK(vector<int> &v, int k)
{
    for (int i=0; i<v.size(); i++)
    {
        if (v[i] <= k)
        {
            v.erase(v.begin()+i);
            i--;
        }
    }
}

void pivot(vector<int> &v, int k)
{
    int i=0;
    int j=v.size()-1;                //one starts at the beginning, one at the end

    while (i < j)                      //while the two sides haven't passed each other
    {
        for (i; i<j; i++)
        {
            if (v[i] > k) break;
        }
        for (j; j>i; j--)
        {
            if (v[j] <= k) break;
        }

        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

bool isSubarray(const vector<string> &a, const vector<string> &b)
{
    for (int i=0; i<b.size(); i++)              //check through B
    {
        //cout<<"Checking "<<i<<endl;
        if (b[i]==a[0])                        //if this index of B is the same as the start of A
        {
            for (int j=0; j<=a.size(); j++)      //for the size of A (except for the value we already checked)
            {
                //cout<<"Subchecking "<<j<<endl;
                if (j==a.size()) return true;          //if we're at the end of A and everything has matched, it's a subset

                if (a[j] != b[i+j]) 
                {
                    //cout<<"breaking"<<endl;
                    break;                //if they don't match exit
                }
            }
        }
    }
    return false;                   
}

bool isPrimeA(int n)
{ 
    for (int i=2; i<n; i++)
    {
        if (n%i==0) return false;   
    }
    return true;
}

int sumPrimesA(int n)
{
    int sum=0;

    for (int i=2; i<n; i++)     //test everything up to n, skipping 0 and 1 
    {
        if (isPrimeA(i)) sum+=i;        //use isPrimeA
    }
    return sum;
}

bool isPrimeB(int n)
{ 
    for (int i=2; i<=sqrt(n); i++)
    {
        if (n%i==0) return false;   
    }
    return true;
}

int sumPrimesB(int n)
{
    int sum=0;

    for (int i=2; i<n; i++)     //test everything up to n, skipping 0 and 1 
    {
        if (isPrimeB(i)) sum+=i;    //use isPrimeB
    }





    return sum;
}

int sieveOfErathosthenes(int n)
{  
    int sum=0;
    vector<int> v;

    for (int i=0; i<n; i++)         //including 0 and 1 so that the vector index matches the value
    {
        v.push_back(i);
    }

    for (int i=2; i<=sqrt(n); i++)          //only work with the indexes after 1 though
    {
        if (v[i]!=0)
        {
            for(int j=2*i; j<v.size(); j+=i)
            {
                //cout<<"Zeroing "<<v[j]<<endl;
                v[j]=0;
            }
        }
    }

    for (int i=2; i<v.size(); i++)
    {
        //cout<<"Adding "<<v[i]<<endl;
        sum+=v[i];
    }

    return sum;
}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);
void timePrimes();

int main(){
    int question = -1;
    cin >> question;

    int n = 0, k = 0, m = 0;
    vector<int> v;
    string s = "";
    vector<string> a;
    vector<string> b;

    switch (question){
        case 1: //collatzLength
            cin >> n;
            cout << collatzLength(n) << endl;
            break;

        case 2: //printStats
            cin >> n;
            readIntVector(v, n);
            printStats(v);
            break;

        case 3: //sumMultiples
            cin >> n;
            readIntVector(v, n);
            cin >> k;
            cout << sumMultiples(v, k) << endl;
            break;
        case 4: //greaterThanK
            cin >> n;
            readIntVector(v, n);
            cin >> k;
            greaterThanK(v, k);
            for (int j = 0; j < v.size(); j++){ cout << v[j] << " "; }
            break;
        case 5: //pivot
            cin >> n;
            readIntVector(v, n);
            cin >> k;
            pivot(v, k);
            for (int j = 0; j < v.size(); j++){ cout << v[j] << " "; }
            break;
        case 6: //isSubarray
            cin >> n >> m;
            for (int i = 0; i < n; i++){
                cin >> s;
                a.push_back(s);
            }
            for (int i = 0; i < m; i++){
                cin >> s;
                b.push_back(s);
            }
            cout << isSubarray(a, b) << endl;
            break;
        case 7: //primes
            cin >> n;
            cout << sumPrimesA(n) << " " << sumPrimesB(n) << " " << sieveOfErathosthenes(n) << endl;
            break;
        case 8: //time primes
            timePrimes();
            break;
    }

    return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n){
    int m = 0;
    for (int i = 0; i < n; i++){
        cin >> m;
        v.push_back(m);
    }
}

/***************************************************************************************************
 * Testing run times of different approaches to finding the sum of prime numbers under a threshold *
 * *************************************************************************************************/
void timePrimes(){
    int sum = -1;
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    double elapsed = -1;
    vector<int> x = {10, 100, 1000, 10000, 100000, 500000};
    for (int i = 0; i < x.size(); i++)
    {
        cout << "Value: " << x[i] << endl;

        start = chrono::high_resolution_clock::now();
        sum = sumPrimesA(x[i]);
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
        cout << "A ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

        start = chrono::high_resolution_clock::now();
        sum = sumPrimesB(x[i]);
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
        cout << "B ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

        start = chrono::high_resolution_clock::now();
        sum = sieveOfErathosthenes(x[i]);
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
        cout << "C ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;
        cout << endl << endl;
    }

    cout << "Sieve of Erathosthenes on primes below 1 million" << endl;
    start = chrono::high_resolution_clock::now();
    long sum2 = sieveOfErathosthenes(1000000);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "Sum: " << sum2 << ", Time elapsed: " << elapsed << endl;
    cout << endl << endl;
}

