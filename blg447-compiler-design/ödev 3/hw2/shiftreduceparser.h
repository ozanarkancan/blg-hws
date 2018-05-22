#ifndef SHIFTREDUCEPARSER_H
#define SHIFTREDUCEPARSER_H

#include "ParseTable.h"
#include "State.h"
#include <string>
#include <stack>

using namespace std;

class ShiftReduceParser
{
    public:
        ShiftReduceParser();
        ~ShiftReduceParser();
        void parseInput(string input);
    private:
        ParseTable pt;
        stack<string> parseStack;

};

#endif // SHIFTREDUCEPARSER_H
