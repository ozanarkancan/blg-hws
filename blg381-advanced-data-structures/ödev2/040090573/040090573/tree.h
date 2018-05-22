#ifndef TREE_H
#define TREE_H

#include "node.h"

class tree
{
    node* root;
    float average;
    public:
        tree();
        ~tree();
        node* getRoot();
        void createProbabilityTree(node*);
        void createNode(node*, string, float, int, bool, int, bool*, int, int);
        void travel(node*);
        void tucoAnalyzsis(node*, float&, float&);
        void angelEyesAnalyzsis(node*, float&, float&);
        void blondieAnalyzsis(node*, float&, float&);
        void clearTree(node*);
        int simulate();
        float random();
        void showAverage();
};

#endif // TREE_H
