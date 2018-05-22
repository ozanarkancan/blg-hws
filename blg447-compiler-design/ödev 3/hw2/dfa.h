#ifndef DFA_H
#define DFA_H

#include "Grammar.h"
#include "State.h"

class DFA
{
    public:
        DFA(Grammar G);
        ~DFA();
        void buildDFA();
        static bool contains(const deque<Rule>& rules, const Rule& r);
        static int stateID;
        deque<State*> states;
    private:
        Grammar grammar;
        State* beginningState;
        deque<Rule> closure(Rule rule);
        void transition(State* s, string symbol);
        string nonTerminalSymbolAfterPeriod(string str);
        string symbolAfterPeriod(string str);
        string moveDot(string str);
        State* searchState(State& s);
        void generateDFA(State* s);
};

#endif // DFA_H
