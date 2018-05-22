#ifndef COMBINATORIALSOLUTION_H
#define COMBINATORIALSOLUTION_H

#include "BigUnsignedInt.h"

class CombinatorialSolution
{
    private:
        BigUnsignedInt makeCombination(unsigned int n, unsigned int k);
        BigUnsignedInt factorial(unsigned int n);
        BigUnsignedInt makeCombinationEfficient(unsigned int n, unsigned int k);
        BigUnsignedInt factorialEfficient(unsigned int n);
    public:
        void solve(unsigned int n, unsigned int k);
        void solveEfficient(unsigned int n, unsigned int k);
};

#endif // COMBINATORIALSOLUTION_H
