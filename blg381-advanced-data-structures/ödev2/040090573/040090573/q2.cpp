#include <iostream>
#include "tree.h"

using namespace std;

int main()
{
    tree q2;
    float maxT(0), minT(1), maxA(0), minA(1), maxB(0), minB(1);
    q2.createProbabilityTree(q2.getRoot());
    q2.tucoAnalyzsis(q2.getRoot(), maxT, minT);
    cout << "Tuco Analyzsis:" << endl;
    cout << "Max Probability: " << maxT << endl;
    cout << "Min Probability: " << minT << endl << endl;

    q2.angelEyesAnalyzsis(q2.getRoot(), maxA, minA);
    cout << "Angel Eyes Analyzsis:" << endl;
    cout << "Max Probability: " << maxT << endl;
    cout << "Min Probability: " << minT << endl << endl;

    q2.blondieAnalyzsis(q2.getRoot(), maxB, minB);
    cout << "Blondie Analyzsis:" << endl;
    cout << "Max Probability: " << maxT << endl;
    cout << "Min Probability: " << minT << endl << endl;

    return 0;
}

