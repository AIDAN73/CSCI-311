// CSCI 311 - Fall 2021
// Lab 3 - BST cpp skeleton
// Author: *** YOUR NAME HERE ***

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"
using namespace std;

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{

}

//searches the binary tree for an inputted value. Returns the node containing the value if found, or nullptr if not found. This opening code lets 
//the user not provide the root explicitly in the arguments
Node* BST::search(int target)
{
	if (root == nullptr) return nullptr;								//this BST is empty, it doesn't even have a root. There's nothing here. Stop looking.
	if (root->value == target) return root;								//wow, the target was right at the top
	if (root->value > target) return search(root->left, target);		//if the target is less than, search left, and vice versa
	if (root->value < target) return search(root->right, target);
    return nullptr;														//it yelled at me if I didn't let it return something without an if statement
}

//once the root's been checked, this is the recursive call that does most of the legwork.
Node* BST::search(Node* n, int target)
{
	if (n==nullptr) return nullptr;										//you have gone past a leaf. Stop looking. 
	if (n->value == target) return n;									//we found it!!!
	if (n->value > target) return search(n->left, target);				//see function above
	if (n->value < target) return search(n->right, target);
	return nullptr;
}

Node* BST::minimum()
{		
  	return nullptr;
}

Node* BST::minimum(Node* n)
{
  	return nullptr;
}

Node* BST::maximum()
{
  	return nullptr;
}

Node* BST::maximum(Node* n)
{
  	return nullptr;
}

//insert things into the BST, ignoring all repeat values. Traverses according to if the value is greater or less than the root, then inserts the value at the first open space.
//This really only checks if the root is empty, then calls the recursive function below. To use, simply put the value you want to insert alone in the args
void BST::insertValue(int val)
{
    if (root==nullptr)   root = new Node(val);				//if the root is empty, insert the value there and start the BST
	else if (root->value == val) return;					//if the root is the value already, don't insert anything (repeat)
    else 
    {
        if (val < root->value)								//call the recursive function depending if the value should be to the left or right
        {
            root->left = insertValue(root->left, val);		//updates the left child with the one returned by the recursive
        }
        else
        {
            root->right = insertValue(root->right, val);
        }
    }
    
}

//recursive function that actually inserts things past the root. Ignores repeat values. This isn't really for direct use, more to be called by the function above. 
Node* BST::insertValue(Node* n, int val)
{
	if (n == nullptr) n = new Node(val);					//same as function above
	if (n->value == val) return n;

    else 
    {
        if (val < n->value)
        {
            n->left = insertValue(n->left, val);
        }
        else
        {
            n->right = insertValue(n->right, val);
        }
    }
    return n;												//returns the given node (updated or not) so that the tree retains its structure
}

void BST::deleteValue(int val)
{

}

Node* BST::deleteValue(Node* n, int val)
{
	return nullptr;
}

//checks if a BST is actually a BST, returning a boolean. Rules are that if a left child is larger or a right child is smaller than a parent, it's not a binary search tree
bool BST::isBST(Node* n)
{
	if (n == nullptr) return true;															//checks the three things the function can see at the current node
	if ((n->left != nullptr) && n->left->value > n->value) return false;
	if ((n->right != nullptr) && n->right->value < n->value) return false;

	return (isBST(n->left)) && (isBST(n->right));											//checks what it can see at the child nodes
}

//not sure what this is supposed to do
bool BST::isBST(Node* n, int low, int high)
{

  	return false;
}

//lists the leftmost nodes first, then the right ones
void BST::preOrder(Node* n, vector<Node*> &order)
{
	if (n != nullptr)									//don't try to display an empty node
	{
		cout<<n->value<<" ";							//otherwise, if we're on a node, display it
		BST::preOrder(n->left, order);					//then call it on the left and then the right
		BST::preOrder(n->right, order);
	}
}

void BST::inOrder(Node* n, vector<Node*> &order)
{
}

void BST::postOrder(Node* n, vector<Node*> &order)
{
}
