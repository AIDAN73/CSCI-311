#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
using namespace std; 
using namespace std::chrono;

bool isSorted(const vector<int> &v) //checks whether a given vector is properly sorted
{
    for (int i=0; i<v.size()-1; i++)
    {
        if (v[i] > v[i+1]) return false;
    }
    return true;
}

void displayIntVector(const vector<int> &v)        //displays all values in vector, with endl after
{
    for (int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void displayDoubleVector(const vector<double> &v)
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

void displayStats(vector<double> v)                                //pass by value because don't need to change vector
{
    double min=v[0];
    float mean;
    double stDev;
    double max=v[0];  

    for (int i=0; i<v.size(); i++)
    {
        if (v[i] < min) min = v[i];
        if (v[i] > max) max = v[i];

        mean += v[i];
    }
    mean = mean/v.size();

    for (int i=0; i<v.size(); i++)
    {
        stDev += (v[i]-mean) * (v[i]-mean);
    }

    stDev = stDev / (v.size()-1);
    stDev = sqrt(stDev); 

    cout<<"Minimum: "<<min<<"\tMean: "<<mean<<"\tStDev: "<<stDev<<"\tMaximum: "<<max<<endl;
}

vector<int> bubbleSort(vector<int> &v)
{
    int temp;
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;

        for (int i=1; i<v.size(); i++)
        {
            if (v[i-1] > v[i])
            {
                temp = v[i-1];
                v[i-1] = v[i];
                v[i] = temp;

                sorted = false;
            }
        }
    }
    return v; 
}

vector<int> insertSort(vector<int> &v)
{
    int temp;

    int i = 1;
    while (i<v.size())
    {
        int j = i;
        while ((j>0) && (v[j]<v[j-1]))
        {
            temp = v[j-1];
            v[j-1] = v[j];
            v[j] = temp;
            j--;
        }
        i++;
    }
    return v;
}

vector<int> selectSort(vector<int> &v)
{
    int uMin;
    int temp; 
    for (int i=0; i<v.size()-1; i++)
    {
        uMin = i;
        for (int j=i+1; j<v.size(); j++)
        {
            if (v[j]< v[uMin]) uMin = j;
        }
        temp = v[i];
        v[i] = v[uMin];
        v[uMin] = temp; 
    }
    return v;
}

vector<int> quickSort(vector<int> &v)
{
    if (v.size() == 1) 
    {
        cout<<"Returning "<<v[0]<<endl;
        return v;
    }

    if(v.size() < 1)
    {
        cout<<"Returning empty"<<endl;
        return v;
    }

    cout<<"Running ";
    displayIntVector(v);

    int pivot = v[0];
    vector<int> A; 
    vector<int> B; 

    for (int i=1; i<v.size(); i++)
    {
        if (v[i] <= pivot) A.push_back(v[i]);
        else if (v[i] > pivot) B.push_back(v[i]);
    }

    quickSort(A);
    quickSort(B); 

    A.push_back(pivot);
    A.insert(A.end(), B.begin(), B.end());
    cout<<"Returning ";
    displayIntVector(A);

    return A;


}




void testSorts()
{
    int number_test_vectors = 10;                               //holds the amount of test vectors, 10
    vector<vector<int>> vectorsList;                            //2d vector
    
    vector<double> bubbleResults;
    vector<double> insertionResults;
    vector<double> selectionResults;
    vector<double> quickResults;

    for (int i=0; i < number_test_vectors; i++)
    {
        vectorsList.push_back(randomVector(5, 0, 100));         //generates the master list of random vectors that all the sorts are tested with
    }

    cout<<"\n********************************************************************************"<<endl<<"Testing Bubble Sort on "<<number_test_vectors<<" vectors of length 100"<<endl;
    bool bubbleSortSuccessful = true;                               //holds whether everything's sorted successfully
    for (int i=0; i<number_test_vectors; i++)
    {
        vector<int> testVector = vectorsList[i];                //makes a copy of the current testing vector from master list

        auto start = chrono::high_resolution_clock::now();                                              //start clock
        testVector = bubbleSort(testVector);                                                            //sort the copy
        auto end = chrono::high_resolution_clock::now();                                                //stop clock
        double elapsed = chrono::duration_cast< chrono::duration<double> > (end-start).count();         //find difference in time

        if (isSorted(testVector)) bubbleResults.push_back(elapsed);                                     //if it's sorted, push the runtime
        else 
        {
            bubbleSortSuccessful = false;               //if not, set a flag and push a -1 instead
            bubbleResults.push_back(-1);
        }
    }

    cout<<std::boolalpha<<"Sorting successful: "<<bubbleSortSuccessful<<endl;
    displayStats(bubbleResults);
    cout<<"********************************************************************************"<<endl;


    cout<<"Testing Insertion Sort on "<<number_test_vectors<<" vectors of length 100"<<endl;
    bool insertionSortSuccessful = true;                               //holds whether everything's sorted successfully
    for (int i=0; i<number_test_vectors; i++)
    {
        vector<int> testVector = vectorsList[i];                //makes a copy of the current testing vector from master list                         

        auto start = chrono::high_resolution_clock::now();                                              //start clock
        testVector = insertSort(testVector);                                                            //sort the copy
        auto end = chrono::high_resolution_clock::now();                                                //stop clock
        double elapsed = chrono::duration_cast< chrono::duration<double> > (end-start).count();         //find difference in time
                         
        if (isSorted(testVector)) insertionResults.push_back(elapsed);                                     //if it's sorted, push the runtime
        else 
        {
            insertionSortSuccessful = false;               //if not, set a flag and push a -1 instead
            insertionResults.push_back(-1);
        }
    }
    cout<<std::boolalpha<<"Sorting successful: "<<insertionSortSuccessful<<endl;
    displayStats(insertionResults);
    cout<<"********************************************************************************"<<endl;


    cout<<"Testing Selection Sort on "<<number_test_vectors<<" vectors of length 100"<<endl;
    bool selectionSortSuccessful = true;                               //holds whether everything's sorted successfully
    for (int i=0; i<number_test_vectors; i++)
    {
        vector<int> testVector = vectorsList[i];                //makes a copy of the current testing vector from master list                         

        auto start = chrono::high_resolution_clock::now();                                              //start clock
        testVector = selectSort(testVector);                                                            //sort the copy
        auto end = chrono::high_resolution_clock::now();                                                //stop clock
        double elapsed = chrono::duration_cast< chrono::duration<double> > (end-start).count();         //find difference in time                   

        if (isSorted(testVector)) selectionResults.push_back(elapsed);                                     //if it's sorted, push the runtime
        else 
        {
            selectionSortSuccessful = false;               //if not, set a flag and push a -1 instead
            selectionResults.push_back(-1);
        }
    }

    cout<<std::boolalpha<<"Sorting successful: "<<selectionSortSuccessful<<endl;
    displayStats(selectionResults);
    cout<<"********************************************************************************"<<endl;



cout<<"Testing Quick Sort on "<<number_test_vectors<<" vectors of length 100"<<endl;
    bool quickSortSuccessful = true;                               //holds whether everything's sorted successfully
    for (int i=0; i<number_test_vectors; i++)
    {
        vector<int> testVector = vectorsList[i];                //makes a copy of the current testing vector from master list
        cout<<"Vector "<<i<<": "<<endl;
        displayIntVector(testVector);                         

        auto start = chrono::high_resolution_clock::now();                                              //start clock
        testVector = quickSort(testVector);                                                            //sort the copy
        auto end = chrono::high_resolution_clock::now();                                                //stop clock
        double elapsed = chrono::duration_cast< chrono::duration<double> > (end-start).count();         //find difference in time

        displayIntVector(testVector);

        if (isSorted(testVector)) quickResults.push_back(elapsed);                                     //if it's sorted, push the runtime
        else 
        {
            quickSortSuccessful = false;               //if not, set a flag and push a -1 instead
            quickResults.push_back(-1);
        }
    }

    cout<<std::boolalpha<<"Sorting successful: "<<quickSortSuccessful<<endl;
    displayStats(quickResults);
    cout<<"********************************************************************************"<<endl;

    
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
            testSorts();
            break;
    }

}