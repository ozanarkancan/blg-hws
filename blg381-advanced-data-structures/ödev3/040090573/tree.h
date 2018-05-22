/*
* Course: BLG381E
* Homework #3
*
* Ozan Arkan CAN
* 040090573
*/

#ifndef TREE_H
#define TREE_H

#include "node.h"

class tree
{
    node* root;
    int m,t; //order and minimum degree
    public:
        tree();
        ~tree();
        node* getRoot();
        void setRoot(node*);
        void setOrder(int);
        int getOrder();
        void setMinimumDegree(int);
        int getMinimumDegree();
        node* search(node*, string);
        bool search(node*, string, data);
        void split(node*, int, node*);
        void insert(node*, string , deque<data>*);
        void insertNonFull(node*, string, deque<data>*);
};

#endif // TREE_H
