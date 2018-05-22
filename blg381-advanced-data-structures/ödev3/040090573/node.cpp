/*
* Course: BLG381E
* Homework #3
*
* Ozan Arkan CAN
* 040090573
*/

#include "node.h"

node::node()
{
    numberOfKeys = 0;
    leaf = true;
}

node::~node()
{
    for(int i = 0; i < dataSets.size(); i++)
    {
        delete dataSets[i];
    }
}

int node::getNumberOfKeys(){ return numberOfKeys; }

void node::setNumberOfKeys(int num){ numberOfKeys = num; }

bool node::getLeaf(){ return leaf; }

void node::setLeaf(bool lf){ leaf = lf; }

int node::getFound(){ return found; }

void node::setFound(int val){ found = val; }
