#include <chrono>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std; 
using namespace std::chrono;
int testNumber=0;

static const char*  star_line= "********************************************************************************"; 

//checks whether a given vector is properly sorted
bool isSorted(const vector<int> &v) 
{
    for (int i=0; i<v.size()-1; i++)
    {
        if (v[i] > v[i+1]) return false;
    }
    return true;
}

//displays all values in vector, with endl after
void displayIntVector(const vector<int> &v)        
{
    for (int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

//needed one that would take a double vector for the timing data
void displayDoubleVector(const vector<double> &v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

//generates a random vector of a given size, with values ranging begween low and high
vector<int> randomVector(int size, int low, int high)
{
    vector<int> v(size, 0);
    for (int i = 0; i<size; i++)
    {
        v[i] = rand() % (high - low + 1) + low;
    }
    return v;
}

//generates a presorted list like [0,1,2,3,4...] of a given size, used for best and worst cases
vector<int> sortedVector(int size)
{
    vector<int> v;
    for(int i=0; i<size; i++)
    {
        v.push_back(i);
    }
    return v;
}

//generates a reverse sorted list like [...,5,4,3,2,1,0] of a given size, used for worst cases
vector<int> reverseSortedVector(int size)
{
    vector<int> v;
    for(int i=size; i>0; i--)
    {
        v.push_back(i);
    }
    return v;
}

//processes a time results vector from the testSorts call. Displays the minimum, mean, standard deviation, and maximum
void displayStats(vector<double> &v)                                
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

//bubble sort vector, as detailed by pseudocode in class
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

//insert sort vector, as detailed by pseudocode in class
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

//select sort vector, as detailed by pseudocode in class
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

//quick sort vector, as detailed by pseudocode in class
vector<int> quickSort(vector<int> &v)
{
    if (v.size() <= 1) return v;

    int pivot = v[0];
    vector<int> A; 
    vector<int> B; 

    for (int i=1; i<v.size(); i++)
    {
        if (v[i] <= pivot) A.push_back(v[i]);
        else if (v[i] > pivot) B.push_back(v[i]);
    }

    A=quickSort(A);
    B=quickSort(B); 

    A.push_back(pivot);
    A.insert(A.end(), B.begin(), B.end());
    
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
        vectorsList.push_back(randomVector(100, 0, 100));         //generates the master list of random vectors that all the sorts are tested with
    }

    cout<<"\n"<<star_line<<endl<<"Testing Bubble Sort on "<<number_test_vectors<<" vectors of length 100"<<endl;
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
    cout<<star_line<<endl;


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
    cout<<star_line<<endl;


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
    //writeToNewCSV("Selection Results.csv", 100, selectionResults);
    cout<<star_line<<endl;



cout<<"Testing Quick Sort on "<<number_test_vectors<<" vectors of length 100"<<endl;
    bool quickSortSuccessful = true;                               //holds whether everything's sorted successfully
    for (int i=0; i<number_test_vectors; i++)
    {
        vector<int> testVector = vectorsList[i];                //makes a copy of the current testing vector from master list                         

        auto start = chrono::high_resolution_clock::now();                                              //start clock
        testVector = quickSort(testVector);                                                            //sort the copy
        auto end = chrono::high_resolution_clock::now();                                                //stop clock
        double elapsed = chrono::duration_cast< chrono::duration<double> > (end-start).count();         //find difference in time

        if (isSorted(testVector)) quickResults.push_back(elapsed);                                     //if it's sorted, push the runtime
        else 
        {
            quickSortSuccessful = false;               //if not, set a flag and push a -1 instead
            quickResults.push_back(-1);
        }
    }

    cout<<std::boolalpha<<"Sorting successful: "<<quickSortSuccessful<<endl;
    displayStats(quickResults);
    cout<<star_line<<endl; 
}

void runTest(int sortType, string outputFile, vector<vector<int>> &vectorsList)
{
    testNumber++;
    std::ofstream file(outputFile.c_str());                              //creates the output file
    file << "Size, Runtime"<<endl;                               //sets up a CSV

    for(int i=0; i<vectorsList.size(); i++)
    {
        vector<int> testVector = vectorsList[i];                //makes a copy of the current testing vector from master list

        auto start = chrono::high_resolution_clock::now();                                              //start clock

        switch (sortType)                                           //sort the copy based with whichever selected sort. Technically influences the timer, but this will be negligible
        {
            case 0:
                testVector = bubbleSort(testVector);
                break;
            case 1: 
                testVector = insertSort(testVector);
                break; 
            case 2: 
                testVector = selectSort(testVector);
                break; 
            case 3: 
                testVector = quickSort(testVector);
                break; 
        }
        auto end = chrono::high_resolution_clock::now();                                                //stop clock
        double elapsed = chrono::duration_cast< chrono::duration<double> > (end-start).count();         //find difference in time
        file << testVector.size() << ", " << elapsed << endl;                                           //writes the results of this test to CSV 
        cout<<"Finished vector "<<i<<" of 250"<< " in test " << testNumber << " of 12" << endl;
    }
}



/*
    This function, by the end, will generate 50 vectors for each combination of size (10, 100, 1000, 10000, 100000), algorithm (bubble, insert, select, quick), and case (worst, random, best), 
    test each combination, and record the results to 12 result CSV files. Each file contains one combination of algorithm and case, with all 250 vectors of various sizes. 

    The general structure of this is to generate a master list of vectors (ex: all the random vectors, all the presorted vectors). Then that master list (along with the file to store the data at) is passed to 
    the test functions to gather data. 
     
*/
void collectData()
{
    int currentTest = 1;

    vector<vector<int>> vectorsList;


    //start with all the random sorts
    for(int i=10; i<=10000; i=i*10)                    //10, 100, 1000, 10000
    {
        for(int j=0; j<50; j++)                         //pushes 50 vectors
        {
            vectorsList.push_back(randomVector(i, 0, 100));      //vectorsList now has 200 of the 250 vectors needed
        }   
    }
    for (int i=0; i<50; i++)    vectorsList.push_back(randomVector(40000, 0, 100));      //vectorsList now has all 250


    runTest(0, "bubbleRandom.csv", vectorsList);                            //test each algorithm on the same random vectors
    runTest(1, "insertRandom.csv", vectorsList);
    runTest(2, "selectRandom.csv", vectorsList);                    
    runTest(3, "quickRandom.csv", vectorsList);

    vectorsList.clear();                                                  //we're done with random vectors, clear the list for reuse

    //new set of random vectors for quickBest
    for(int i=10; i<=10000; i=i*10)                    //10, 100, 1000, 10000
    {
        for(int j=0; j<50; j++)                         //pushes 50 vectors
        {
            vectorsList.push_back(randomVector(i, 0, 100));      //vectorsList now has 200 of the 250 vectors needed
        }   
    }
    for (int i=0; i<50; i++)    vectorsList.push_back(randomVector(40000, 0, 100));      //vectorsList now has all 250

    runTest(3, "quickBest.csv", vectorsList);                               //random is quicksort's best case


    vectorsList.clear();                                                  //we're done with random vectors, clear the list for reuse

    //test presorted arrays
    for(int i=10; i<=10000; i=i*10)                    //10, 100, 1000, 10000
    {
        for(int j=0; j<50; j++)                         //pushes 50 vectors
        {
            vectorsList.push_back(sortedVector(i));      //vectorsList now has 200 of the 250 vectors needed
        }   
    }
    for (int i=0; i<50; i++)    vectorsList.push_back(sortedVector(40000));      //vectorsList now has all 250

    runTest(0, "bubbleBest.csv", vectorsList);                      //bubble and insert's best case is presorted, at O(n)
    runTest(1, "insertBest.csv", vectorsList);
    runTest(2, "selectBest.csv", vectorsList);                      //presorted is *technically* select's best case, but only by a single assignment of uMin. It'll always be O(n^2)
    runTest(3, "quickWorst.csv", vectorsList);                      //presorted is quick's worst case because n never gets divided by 2, only reduced by 1

    vectorsList.clear();

    //test reverse sorted arrays
    for(int i=10; i<=10000; i=i*10)                    //10, 100, 1000, 10000
    {
        for(int j=0; j<50; j++)                         //pushes 50 vectors
        {
            vectorsList.push_back(reverseSortedVector(i));      //vectorsList now has 200 of the 250 vectors needed
        }   
    }
    for (int i=0; i<50; i++)    vectorsList.push_back(reverseSortedVector(40000));      //vectorsList now has all 250

    runTest(0, "bubbleWorst.csv", vectorsList);                      //bubble and insert's worst case is reverse sorted, because they have to run both loops all the time
    runTest(1, "insertWorst.csv", vectorsList);
    runTest(2, "selectWorst.csv", vectorsList);                      //presorted is *technically* select's best case, but only by a single assignment. It'll always be O(n^2)
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
            collectData();
            break;

        case 2: 
            testSorts();
            break;
    }

}