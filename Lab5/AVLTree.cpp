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
    return nullptr;
}

AVLNode* AVLTree::search(AVLNode* n, int val)
{
    return nullptr;
}

AVLNode* AVLTree::minimum()
{
    if (root == nullptr || root->left == nullptr) return root;
    else return minimum(root->left);
}

AVLNode* AVLTree::minimum(AVLNode* n)
{
    if (n->left == nullptr) return n;
    else return minimum(n->left);
}

AVLNode* AVLTree::maximum()
{
    if (root == nullptr || root->right == nullptr) return root;
    else return maximum(root->right);
}

AVLNode* AVLTree::maximum(AVLNode* n)
{
    if (n->right == nullptr) return n;
    else return minimum(n->right);
}

int getHeight(AVLNode* n)
{
    if(n->left == nullptr && n->right == nullptr) return 0;
    else if(n->left !=nullptr && n->right == nullptr) return getHeight(n->left)+1;
    else if(n->left ==nullptr && n->right != nullptr) return getHeight(n->right)+1;
    else return max(getHeight(n->left), getHeight(n->right))+1;
}

int getBalanceFactor(AVLNode* n) {return getHeight(n->right) - getHeight(n->left);}

void AVLTree::insertValue(int val)
{

}

AVLNode* AVLTree::insertValue(AVLNode* n, int val)
{
    return nullptr;
}

void AVLTree::deleteValue(int val)
{

}

AVLNode* AVLTree::deleteValue(AVLNode* n, int val)
{
    return nullptr;
}

AVLNode* AVLTree::rebalance(AVLNode* n)
{
    if(getBalanceFactor(n) < -2)
    {
        if ((n->left->left->height) > (n->left->right->height)) n=rotateRight(n);
        else n=rotateLeftRight(n);
    }
    else if(getBalanceFactor(n) > 2)
    {
        if ((n->right->right->height) > (n->right->left->height)) n=rotateLeft(n);
        else n=rotateRightLeft(n);
    }

    n->left = rebalance(n->left);
    n->right = rebalance(n->right);
    return n;
}

AVLNode* AVLTree::rotateLeft(AVLNode* n)
{
    AVLNode* temp = n->right;
    n->right = temp->left;
    n->height = getHeight(n);
    temp->left = n;
    temp->height = getHeight(temp); 
    return temp;
}

AVLNode* AVLTree::rotateRight(AVLNode* n)
{
    AVLNode* temp = n->left;
    n->left = temp->right;
    n->height = getHeight(n);
    temp->right = n;
    temp->height = getHeight(temp); 
    return temp;
}

AVLNode* AVLTree::rotateLeftRight(AVLNode* n)
{
    rotateLeft(n->left);
    rotateRight(n);
    return n;
}

AVLNode* AVLTree::rotateRightLeft(AVLNode* n)
{
    rotateRight(n->right);
    rotateLeft(n);
    return n;
}

void AVLTree::preOrder(AVLNode* n, vector<AVLNode*> &order)
{

}

void AVLTree::inOrder(AVLNode* n, vector<AVLNode*> &order)
{

}

void AVLTree::postOrder(AVLNode* n, vector<AVLNode*> &order)
{

}

