// CSCI 311 - Spring 2021
// Exam 1
// Author: ** YOUR NAME HERE ***

#include <iostream>
#include <vector>
using namespace std;

/**************************
 * Your solutions go here *
 * *********************
**/


//Returns hamming distance as described in the exam document. Or, rather, finds the amount of places that have different letters between two strings. 
int hammingDist(string a, string b)
{
    if (a.length() != b.length()) return -1;            //don't try if they're not the same length
    int dist = 0; 
    for (int i=0; i<a.length(); i++)                    //simple iterative "count the differences" through the string
    {
        if (a[i] != b[i]) dist++;
    }
    return dist; 
}


//Returns the reverse of an inputted string. Won't help you read your tshirt in the mirror, unfortunately. 
string reverse(string s)
{
    if (s.length()==0) return "";                       //don't try to do anything to empty strings
    char lastLetter = s[s.size()-1];                    //unnecessary to set up these, but more readable
    string rest = s.substr(0, s.length()-1);            //it gets the last letter, then calls itself on a string without the current end

    return lastLetter+reverse(rest);
}


//Returns the "run-length" encoded version of the inputted string. Uses a for loop with a nested while loop to pick a character to look for, count the 
//consecutive amount of them, and then append the amount and the character to an answer string
string runLengthEncoding(string s)
{
    string compressedString;
    for (int i=0; i<s.length(); i++)                            //check until the end of the list
    {
        char character = s[i];                                  //letter you're condensing
        int amount = 1;                                         //we know there's at least one of them, right?
        while(s[i+1]==character && i<s.length())                //if the next one's the same letter, count up and check the next!
        {
            amount++;
            i++;
        }
        //string num = to_string(amount);
        compressedString = compressedString + to_string(amount) + character;            //append the consecutive letters to the answer string
    }
    return compressedString;
}

//used in the mergesort algorithm. Merges two already sorted vectors into one, keeping the sort
vector<int> merge(vector<int> &A, vector<int> &B)
{
    vector<int> C;                      

    while (A.size()>0 && B.size()>0)    //til one of them runs out of values
    {
        if (A[0] < B[0])                //push and then delete the smaller of the first values
        {
            C.push_back(A[0]);
            A.erase(A.begin());
        }
        else 
        {
            C.push_back(B[0]);
            B.erase(B.begin());
        }
    }

    if (A.size()>0) C.insert(C.end(), A.begin(), A.end());                      //one of the vectors will have leftovers. Add it
    else if (B.size()>0) C.insert(C.end(), B.begin(), B.end());

    return C; 
}



//if a vector has 1 or less values, it's sorted. Otherwise, it splits the vector into halves, sorts those halves, and merges the sorted halves together
vector<int> mergeSort(const vector<int> &v)
{
    if (v.size() <= 1) return v;

    int middle = v.size()/2;
    vector<int> A;
    vector<int> B;
    for (int i=0; i<middle; i++)
    {
        A.push_back(v[i]);
    }
    for (int i=middle; i<v.size(); i++)
    {
        B.push_back(v[i]);
    }

    A = mergeSort(A); 
    B = mergeSort(B); 

    return merge(A,B);
}


/*********************************************************************************************************
 * TESTING                                                                                               *
 * When testing your functions, the main below expects input in a certain format for each question.      *
 * The first line of input should always the question number (1-4). More details are provided regarding  *
 * the input for each question in the main itself.                                                       *
 * To test, you may run program and provide input by hand or you may provide a file as input directly    *
 * from the terminal. For example, suppose you compile your program to a.out and that you have a file    *
 * named "test_01.in" containing input in the appropriate format for question 1. Then running            *
 * ./a.out < test_01.in                                                                                  *
 * will run your program using the lines of test_01.in as input. This can be a good way to save time and *
 * to save different test cases when testing your code.                                                  *
 * *******************************************************************************************************/
void readIntVector(vector<int> &v, int n);

int main(){
    int question = -1;
    cout << "Question: ";
     cin >> question;

     string a = "";
     string b = "";
     int n = -1;
     vector<int> v;
     vector<int> s;
     switch(question){
        case 1: // Hamming distance
            /*************************************
            * Input format:                     *
            * 1                                 *
            * string 1, no whitespace, nonempty *
            * string 2, no whitespace, nonempty *
            * ***********************************/
            cout << "Hamming distance - Enter two strings: ";
            cin >> a >> b;
            cout << hammingDist(a, b) << endl;
        break;
        case 2: // reverse
        /**********************************************
        * Input format:                              *
        * 2                                          *
        * string to reverse, no whitespace, nonempty *
        * ********************************************/
            cout << "Reverse - Enter one string: ";
            cin >> a;
            cout << reverse(a) << endl;
        break;
        case 3: // run-length encoding
        /*********************************************
        * Input format:                             *
        * 3                                         *
        * string to encode, no whitespace, nonempty *
        * *******************************************/
            cout << "Run-length encoding - Enter one string: ";
            cin >> a;
            cout << runLengthEncoding(a) << endl;
        break;
        case 4: // merge sort
      /*************************************
       * Input format:                     *
       * 4                                 *
       * length of vector                  *
       * integers to include in the vector *
       * ***********************************/
            cout << "Merge sort - Enter the size of the vector to sort: ";
            cin >> n;
            cout << "Enter the elements of the vector: ";
            readIntVector(v, n);
            s = mergeSort(v);
            for (int i = 0; i < s.size(); i++){ cout << s[i] << " "; }
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