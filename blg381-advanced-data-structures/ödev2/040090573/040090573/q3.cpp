#include <iostream>
#include "tree.h"
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
    tree q3;
    q3.createProbabilityTree(q3.getRoot());
    float min(10), max(0), average(0);
    for(int i = 0; i < 200; i++)
    {
        int tmp = q3.simulate();
        average += tmp;
        if(tmp > max)
            max = tmp;
        if(tmp < min)
            min = tmp;
    }

    cout << "Average winning case: " << average/200 << endl;
    cout << "Best winning: " << min << endl;
    cout << "Worst winning: " << max << endl;

}
