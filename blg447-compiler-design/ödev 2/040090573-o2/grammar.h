#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <map>
#include <deque>
#include "Rule.h"

using namespace std;

class Grammar
{
    public:
        Grammar();
        ~Grammar();
        map<string, deque<Rule> > rules;
        deque<string> terminals;
        deque<string> nonterminals;
    private:
        string startSymbol;
};

#endif // GRAMER_H
