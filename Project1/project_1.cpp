#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
using namespace std; 
using namespace std::chrono;


vector<int> bubbleSort(vector<int> &v)
{
    int temp;

    for (int i=0; i < v.size()-1; i++)      //for each value in the array
    {
        for (int j=i; j<v.size()-1-i; j++)      
        {
            if (v[j]>v[j+1])
            {
                temp = v[j];                //if the indexes are in the wrong order, swap them
                v[j]=v[j+1];
                v[j+1]=temp;
            }
        }
    }
    return v; 
}

void insertSort(vector<int> &v)
{}

void selectSort(vector<int> &v)
{}

void quickSort(vector<int> &v)
{}



bool isSorted(const vector<int> &v) //checks whether a given vector is properly sorted
{
    for (int i=0; i<v.size(); i++)
    {
        if (v[i] > v[i+1]) return false;
    }
    return true;
}







void displayVector(const vector<int> &v)        //displays all values in vector, with endl after
{
    for (int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}


vector<int> randomVector(int size, int low, int high)
{
    vector<int> v(size, 0);
    for (int i = 0; i<size; i++)
    {
        v[i] = rand() % (high - low + 1) + low;
    }
    return v;
}


void testBubbleSort()
{
    int number_test_vectors = 10;                               //holds the amount of test vectors, 10
    

    vector<vector<int>> vectorsList;                            //2d vector
    vector<int>

    for (int i=0; i < number_test_vectors; i++)
    {
        vectorsList.push_back(randomVector(100, 0, 10));         //fills testVectors with 10 random vectors of size 100, with values from 0 to 100
    }

    for (int i=0; i<number_test_vectors; i++)
    {
        vector<int> testVector = vectorsList[i];                //makes a copy of the current testing vector

        auto start = chrono::high_resolution_clock::now();           //times bubbleSort
        bubbleSort(testVector);
        auto end = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration_cast< chrono::duration<double> > (end-start).count();
    
    }

}

int main()
{

    srand(time(NULL));

    int question = -1;
    cout<<"1: run mass test"<<endl<<"2: test specific algorithm"<<endl;
    cin>> question;

    switch (question)
    {
        case 1: 
            cout<<"running case 1"<<endl;
            break;

        case 2: 

            testBubbleSort();


            /*
            int algorithm = -1;
            cout<<endl<<"1: bubble sort"<<endl<<"2: insert sort"<<endl<<"3: select sort"<<endl<<"4: quick sort"<<endl;
            cin>> algorithm;

            switch (algorithm)
            {
                case 1: 
                    cout<<"Running bubble sort"<<endl;
                    break;
                
                case 2: 
                    cout<<"Running insert sort"<<endl;
                    break; 

                case 3: 
                    cout<<"Running select sort"<<endl;
                    break;

                case 4: 
                    cout<<"Running quick sort"<<endl;
                    break;    

            }
            */
            break;
    }

}