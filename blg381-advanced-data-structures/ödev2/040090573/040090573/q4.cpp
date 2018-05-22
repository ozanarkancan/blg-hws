#include <iostream>
#include "tree.h"

using namespace std;

int main()
{
    tree q4;
    q4.createProbabilityTree(q4.getRoot());
    q4.showAverage();
    return 0;
}
