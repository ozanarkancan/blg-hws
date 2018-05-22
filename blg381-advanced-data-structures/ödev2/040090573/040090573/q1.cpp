#include <iostream>
#include "tree.h"

using namespace std;

int main()
{
    tree q1;
    q1.createProbabilityTree(q1.getRoot());
    q1.travel(q1.getRoot());
    return 0;
}
