// CSCI 311 - Fall 2021
// Exam 2
// Author: Aidan Murphree

#include <iostream>
#include <vector>
#include <string>
#include "BST.h"
#include "HashTable.h"
using namespace std;

/**********************************************************************
 * QUESTION 1                                                         *
 * Write a function that, given a node of a BST, inverts its subtree. *
 * This function should return the root of the new substree           *
 * ********************************************************************/
Node *swapChildren(Node *v)
{
	Node* temp = v->left;
	v->left = v->right;
	v->right = temp;
}

Node *invertBST(Node *v)
{
	if (v->left == nullptr && v->right == nullptr) return v;

	if (v->left != nullptr) v->left = invertBST(v->left);
	if (v->right != nullptr) v->right = invertBST(v->right);

	swapChildren(v);

	return v;
}

/********************************************************************************************
 * QUESTION 2                                                                               *
 * Write a function that returns true if the given vector is a min-heap and false otherwise *
 * ******************************************************************************************/

bool isMinHeapRecursive( const vector<int> &v, int position)
{
	int lastPosition = v.size()-1;
	int leftChild = 2*position+1;
	int rightChild = 2*position+2;

	if (position > lastPosition) return true;	

	if (leftChild <= lastPosition)				//if the left child exists, check if the parent is larger than it
	{
		if (v[position] > v[leftChild]) return false;
	}

	if ((rightChild) <= lastPosition)				//if the right child exists, check if the parent is larger than it
	{
		if (v[position] > v[rightChild]) return false;
	}

	return isMinHeapRecursive(v, leftChild) && isMinHeapRecursive(v, rightChild);
}


bool isMinHeap(const vector<int> &v)
{
	if (v.size() == 0) return true;
	return isMinHeapRecursive(v, 0);
}


/****************************************************************************
 * QUESTION 3                                                               *
 * Use the maxHeapify and pop functions below to write a heapsort function. *
 * It might be worthwhile to implement a constructMaxHep function as well.  *
 * **************************************************************************/

/**************************************************************************************
 * Given a vector that represents a max-heap where a single value at index i might be *
 * out of order, rearrange the values so the vector is a true max-heap                *
 * v - vector<int>& - the vector representing a max-heap                              *
 * i - int - the index of the value that may be out of order                          *
 * heapSize - int - the size of the heap. Note that this may be < v.size()            *
 * ************************************************************************************/
void maxHeapify(vector<int> &v, int i, int heapSize)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int maxI = i;
	if (left < heapSize && v[left] > v[i])
	{
		maxI = left;
	}
	if (right < heapSize && v[right] > v[maxI])
	{
		maxI = right;
	}
	if (maxI != i)
	{
		int temp = v[i];
		v[i] = v[maxI];
		v[maxI] = temp;
		maxHeapify(v, maxI, heapSize);
	}
}

/***************************************************************************
 * Remove and return the maximum value of a max-heap                       *
 * v - vector<int>& - a max-heap                                           *
 * heapSize - int - the size of the heap. Note that this may be < v.size() *
 * *************************************************************************/
int pop(vector<int> &v, int heapSize)
{
	int max = v[0];
	v[0] = v[heapSize - 1];
	maxHeapify(v, 0, heapSize - 1);
	return max;
}

void heapsort(vector<int> &v)
{
}

/***********************************************************************************
 * QUESTION 4                                                                      *
 * Write a function to determine whether or not vector A is a subset of vector B.  *
 * You may assume that these vectors represent sets. In particular, you may ignore *
 * duplicate values.                                                               *
 * *********************************************************************************/
bool isSubset(const vector<string> &A, const vector<string> &B)
{
	return false;
}

/********************************************************************************************************
 * TESTING                                                                                              *
 * When testing your functions, the main below expects input in a certain format for each question.     *
 * The first line of input should always the question number (1-4). More details are provided regarding *
 * the input for each question in the main itself.                                                      *
 * To test, you may run program and provide input by hand or you may provide a file as input directly   *
 * from the terminal For example, suppose you compile your program to a.out and that you have a file    *
 * named "test_1.in" containing input in the appropriate format for question 1. Then running            *
 * ./a.out < test_1.in                                                                                  *
 * will run your program using the lines of test_1.in as input. This can be a good way to save time and *
 * to save different test cases when testing your code.                                                 *
 * ******************************************************************************************************/
void readIntVector(vector<int> &v, int n);
void readStringVector(vector<string> &v, int n);
int main()
{
	int question = -1;
	cin >> question;

	// Declaring variables to use in the switch
	int n = -1, m = -1;
	vector<int> v;
	vector<string> A;
	vector<string> B;
	vector<Node *> order;

	switch (question)
	{
	case 1:
	{ // invert BST
		/***********************************
		 * Input format:                   *
		 * 1                               *
		 * the number of nodes in the tree *
		 * integers to include in the tree *
		 * *********************************/
		cout << "INVERTBST" << endl;
		cin >> n;
		readIntVector(v, n);
		BST *T = new BST();
		for (int i = 0; i < v.size(); i++)
		{
			T->insertValue(v[i]);
		}
		invertBST(T->root);
		T->preOrder(T->root, order);
		cout << "PREORDER: ";
		for (int i = 0; i < order.size() - 1; i++)
		{
			cout << order[i]->value << ", ";
		}
		cout << order[order.size() - 1]->value << endl;
		break;
	}
	case 2:
	{ // is min-heap
		/**************************
		 * Input format:          *
		 * 2                      *
		 * number of elements     *
		 * integers in the vector *
		 * ************************/
		cout << "ISMINHEAP" << endl;
		cin >> n;
		readIntVector(v, n);
		cout << isMinHeap(v) << endl;
		break;
	}
	case 3:
	{ // heapsort
		/**************************
		 * Input format:          *
		 * 3                      *
		 * number of elements     *
		 * integers in the vector *
		 * ************************/
		cout << "HEAPSORT" << endl;
		cin >> n;
		readIntVector(v, n);
		heapsort(v);
		for (int i = 0; i < v.size() - 1; i++)
		{
			cout << v[i] << ", ";
		}
		cout << v[v.size() - 1] << endl;
		break;
	}
	case 4:
	 // is sub(multi)set
      /*******************************************
       * Input format:                           *
       * 4                                       *
       * number of elements in the first vector  *
       * strings in the first vector             *
       * number of elements in the second vector *
       * strings in the second vector            *
       * *****************************************/
      cout << "ISSUBSET" << endl;
      cin >> n;
      readStringVector(A, n);
      cin >> m;
      readStringVector(B, m);
      cout << isSubset(A, B) << endl;
      break;
    
    default:
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

/****************************************************
 * Read a vector of strings in from cin             *
 * v - vector<string> & - the string vector to fill *
 * n - int - the number of strings to read          *
 * **************************************************/
void readStringVector(vector<string> &v, int n)
{
	string m = "";
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		v.push_back(m);
	}
}