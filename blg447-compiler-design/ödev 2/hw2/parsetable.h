#ifndef PARSETABLE_H
#define PARSETABLE_H

#include "Grammar.h"
#include "DFA.h"
#include "Cell.h"
#include "Rule.h"
#include <map>
#include <deque>

using namespace std;

class ParseTable
{
    public:
        ParseTable();
        ~ParseTable();
        void generateTable();
        void printTable();
    private:
        map<int, map<string, deque<Cell> > > table;
        Grammar grammar;
        DFA dfa;
        Rule findReductionRule(const deque<Rule>& items) const;
};

#endif // PARSETABLE_H
