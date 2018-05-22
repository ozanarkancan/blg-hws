#ifndef PASCALTRIANGLESOLUTION_H
#define PASCALTRIANGLESOLUTION_H

#include "BigUnsignedInt.h"


class PascalTriangleSolution
{
    private:
        BigUnsignedInt getPascalValue(unsigned int i, unsigned int j);
    public:
        void solve(unsigned int maxN, unsigned int k);
};

#endif // PASCALTRIANGLESOLUTION_H
