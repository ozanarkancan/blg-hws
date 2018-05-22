#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <deque>
#include <string>

using namespace std;

struct data
{
    short int x,y;
};

class node
{
    int numberOfKeys;
    bool leaf;
    int found;
    public:
        node();
        ~node();
        deque<string> keys;
        deque<node*> children;
        deque<deque<data>*> dataSets;
        int getNumberOfKeys();
        void setNumberOfKeys(int);
        bool getLeaf();
        void setLeaf(bool);
        int getFound();
        void setFound(int);
        friend class tree;

};

#endif // NODE_H
