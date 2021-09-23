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

Node* BST::search(int target)
{
    return nullptr;
}

Node* BST::search(Node* n, int target)
{
	if (n==nullptr) return nullptr;
	if (n->value == target) return n;
	if (n->value > target) return search(n->left, target);
	if (n->value < target) return search(n->left, target);
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

void BST::insertValue(int val)
{
    if(root==nullptr)   root = new Node(val);
    else 
    {
        if (val < root->value)
        {
            root->left = insertValue(root->left, val);
        }
        else
        {
            root->right = insertValue(root->right, val);
        }
    }
    
}

Node* BST::insertValue(Node* n, int val)
{
	if (n == nullptr) n = new Node(val);

    else 
    {
        if (val < root->value)
        {
            root->left = insertValue(n->left, val);
        }
        else
        {
            root->right = insertValue(n->right, val);
        }
    }
    return n;
}

void BST::deleteValue(int val)
{

}

Node* BST::deleteValue(Node* n, int val)
{
	return nullptr;
}

bool BST::isBST(Node* n)
{
	if (n == nullptr) return true;
	if ((n->left != nullptr) && n->left->value > n->value) return false;
	if ((n->right != nullptr) && n->right->value < n->value) return false;

	return (isBST(n->left)) && (isBST(n->right));
}

bool BST::isBST(Node* n, int low, int high)
{

  	return false;
}

void BST::preOrder(Node* n, vector<Node*> &order)
{
	if (n != nullptr)
	{
		cout<<n->value<<" "<<endl;
		BST::preOrder(n->left, order);
		BST::preOrder(n->right, order);
	}
}

void BST::inOrder(Node* n, vector<Node*> &order)
{
}

void BST::postOrder(Node* n, vector<Node*> &order)
{
}
