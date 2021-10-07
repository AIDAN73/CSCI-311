// CSCI 311 - Fall 2021
// Lab 5 Skeleton - AVLTree cpp
// Author: Carter Tillquist

#include<iostream>
#include <vector>
#include <limits.h>
#include "AVLTree.h"
using namespace std;


AVLTree::AVLTree()
{
    root = nullptr;
    size = 0;
}

AVLNode* AVLTree::getRoot()     {return root;}
int AVLTree::getSize()          {return size;}

AVLNode* AVLTree::search(int val)
{
    if (root == nullptr) return nullptr;								//this BST is empty, it doesn't even have a root. There's nothing here. Stop looking.
	if (root->value == val) return root;								//wow, the target was right at the top
	if (root->value > val) return search(root->left, val);		//if the target is less than, search left, and vice versa
	if (root->value < val) return search(root->right, val);
    return nullptr;
}

AVLNode* AVLTree::search(AVLNode* n, int val)
{
    if (n==nullptr) return nullptr;									//you have gone past a leaf. Stop looking. 
	if (n->value == val) return n;									//we found it!!!
	if (n->value > val) return search(n->left, val);				//see function above
	if (n->value < val) return search(n->right, val);
	return nullptr;
}

AVLNode* AVLTree::minimum()
{
    AVLNode* traveler = root;
    while (traveler->left != nullptr)
    {
        traveler = traveler->left;
    }
    return traveler;
}

AVLNode* AVLTree::minimum(AVLNode* n)
{
    AVLNode* traveler = n;
    while (traveler->left != nullptr)
    {
        traveler = traveler->left;
    }
    return traveler;
}

AVLNode* AVLTree::maximum()
{
    AVLNode* traveler = root;
    while (traveler->right != nullptr)
    {
        traveler = traveler->right;
    }
    return traveler;
}

AVLNode* AVLTree::maximum(AVLNode* n)
{
    
    AVLNode* traveler = n;
    while (traveler->right != nullptr)
    {
        traveler = traveler->right;
    }
    return traveler;
}

int getHeight(AVLNode* n)
{
    if(n->left == nullptr && n->right == nullptr) return 0;
    else if(n->right == nullptr) return getHeight(n->left)+1;
    else if(n->left ==nullptr) return getHeight(n->right)+1;
    else return max(n->left->height, n->right->height)+1;
}

int getBalanceFactor(AVLNode* n) 
{
    int right;
    int left;

    if(n->left == nullptr) left = -1;
    else left = n->left->height;

    if(n->right == nullptr) right = -1;
    else right = n->right->height;

    return right - left;
}

void AVLTree::insertValue(int val)
{
    if (root == nullptr)  
    {
        root = new AVLNode(val);
        size++;
    }

    else if(root->value == val) return;

    else 
    {
        if (val < root->value) root->left = insertValue(root->left, val);
        else root->right = insertValue(root->right, val);
    }

    root->height = getHeight(root);
    root->balanceFactor = getBalanceFactor(root);
    root = rebalance(root);
}

AVLNode* AVLTree::insertValue(AVLNode* n, int val)
{
    if (n == nullptr) 
    {
        n = new AVLNode(val);					//same as function above
        size++;
        return n;
    }

    else if(n->value == val) return n;

    else 
    {
        if (val < n->value) n->left = insertValue(n->left, val);
        else n->right = insertValue(n->right, val);
    }

    n->height = getHeight(n);
    n->balanceFactor = getBalanceFactor(n);
    n = rebalance(n);
    return n;
}

void AVLTree::deleteValue(int val)
{
    if (root != nullptr)
    {
        if (val < root->value) root->left = deleteValue(root->left, val);               //navigate to the thing we want to delete
        else if (val > root->value) root->right = deleteValue(root->right, val);

        else if (root->right==nullptr && root->left==nullptr)                           //no children, just set to null
        {
            root = nullptr;           
            size--;
        }
        else if (root->left==nullptr)                                                  //one child, replace with child
        {
            root = root->right;
            size--;
        }
        else if (root->right==nullptr) 
        {
            root = root->left;
            size--;
        }

        else 
        {
            AVLNode* replacement = minimum(root->right);					//find the value closest to the root in the right subtree
			root->value = replacement->value;								//replace the value, but keep the children
			root->right = deleteValue(root->right, replacement->value);		//delete the now redundant 'closest value'
        }
    }
    if (root==nullptr) return;

    root->height = getHeight(root);
    root->balanceFactor = getBalanceFactor(root);
    root = rebalance(root);
}

AVLNode* AVLTree::deleteValue(AVLNode* n, int val)
{
    if (n != nullptr)
    {
        if (val < n->value) n->left = deleteValue(n->left, val);
        else if (val > n->value) n->right = deleteValue(n->right, val);

        else if (n->right==nullptr && n->left==nullptr) 
        {
            n = nullptr;
            size--;
        }
        else if (n->left==nullptr) 
        {
            n = n->right;
            size--;
        }
        else if (n->right==nullptr) 
        {
            n = n->left;
            size--;
        }

        else 
        {
            AVLNode* replacement = minimum(n->right);					
			n->value = replacement->value;								
			n->right = deleteValue(n->right, replacement->value);		
        }
    }
    if (n==nullptr) return n;

    n->height = getHeight(n);
    n->balanceFactor = getBalanceFactor(n);
    n = rebalance(n);
    return n;
}

AVLNode* AVLTree::rebalance(AVLNode* n)
{
    if (n->balanceFactor == 2)
    {
        if (n->right->balanceFactor > 0) return rotateLeft(n);
        else if (n->right->balanceFactor < 0) return rotateRightLeft(n);
    }
    else if(n->balanceFactor == -2)
    {
        if (n->left->balanceFactor < 0) return rotateRight(n);
        else if (n->left->balanceFactor > 0) return rotateLeftRight(n);
    }

    return n;
}

AVLNode* AVLTree::rotateLeft(AVLNode* y)
{
    AVLNode* x = y->right;
    y->right = x->left;
    y->height = getHeight(y);
    x->left = y;
    x->height = getHeight(x); 
    return x;
}

AVLNode* AVLTree::rotateRight(AVLNode* y)
{
    AVLNode* x = y->left;
    y->left = x->right;
    y->height = getHeight(y);
    x->right = y;
    x->height = getHeight(x); 
    return x;
}

AVLNode* AVLTree::rotateLeftRight(AVLNode* y)
{
    //rotate left
    AVLNode* x = y->left;
    AVLNode* z = x->right;
    x->right = z->left;
    x->height = getHeight(x);
    z->left = x;
    y->left = z;
    //rotate right
    y->left = z->right;
    y->height = getHeight(y);
    z->right = y;
    z->height = getHeight(z);
    return z;
}

AVLNode* AVLTree::rotateRightLeft(AVLNode* y)
{
    //rotate right
    AVLNode* x = y->right;
    AVLNode* z = x->left;
    x->left = z->right;
    x->height = getHeight(x);
    z->right = x;
    y->right = z;
    //rotate left
    y->right = z->left;
    y->height = getHeight(y);
    z->left = y;
    z->height = getHeight(z);
    return z;
}

void AVLTree::preOrder(AVLNode* n, vector<AVLNode*> &order)
{
    if (n != nullptr)									//don't try to display an empty node
	{
		order.push_back(n);
		AVLTree::preOrder(n->left, order);					//then call it on the left and then the right
		AVLTree::preOrder(n->right, order);
	}
}

void AVLTree::inOrder(AVLNode* n, vector<AVLNode*> &order)
{
    if (n != nullptr)									//don't try to display an empty node
	{				
		AVLTree::inOrder(n->left, order);					//go all the way left
		order.push_back(n);
		AVLTree::inOrder(n->right, order);					//then go all the way right
	}
}

void AVLTree::postOrder(AVLNode* n, vector<AVLNode*> &order)
{
    if (n != nullptr)									//don't try to display an empty node
	{				
		AVLTree::postOrder(n->left, order);					//go all the way left
		AVLTree::postOrder(n->right, order);					//then go all the way right
		order.push_back(n);
	}
}

