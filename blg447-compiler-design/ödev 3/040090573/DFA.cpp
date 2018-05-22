#include "DFA.h"
#include <iostream>

using namespace std;

int DFA::stateID = 0;

DFA::DFA(Grammar G)
{
    this->grammar = G;
    beginningState = NULL;
}

DFA::~DFA()
{
    //dtor
}

void DFA::buildDFA()
{
    State* beginning = new State();

    Rule sPrime("S^", ".S$", -1);
    deque<Rule> closureSet = closure(sPrime);
    this->beginningState = beginning;

    for(unsigned i = 0; i < closureSet.size(); i++)
        this->beginningState->items.push_back(closureSet[i]);

    this->beginningState->id = DFA::stateID;
    DFA::stateID++;
    states.push_back(this->beginningState);
    generateDFA(beginningState);
    //transition(beginning, "Deyimler");
}

void DFA::generateDFA(State* s)
{
    if(s->outgoingArcsGenerated)
        return;
    else
        s->outgoingArcsGenerated = true;
    if(DFA::contains(s->items, Rule("S^", "S$.", -1)))
        return;
    for(unsigned i = 0; i < grammar.nonterminals.size(); i++)
        transition(s, grammar.nonterminals[i]);

    for(unsigned i = 0; i < grammar.terminals.size(); i++)
        transition(s, grammar.terminals[i]);

    for(unsigned i = 0; i < s->outgoingArcs.size(); i++)
        generateDFA((s->outgoingArcs[i]).target);
}

deque<Rule> DFA::closure(Rule rule)
{
    deque<Rule> resultList;
    resultList.push_back(rule);

    for(unsigned i = 0; i < resultList.size(); i++)
    {
        Rule r = resultList[i];
        string symbol = nonTerminalSymbolAfterPeriod(r.rightSide);
        if(symbol.compare("") != 0)
        {
            deque<Rule> rulesForSymbol = this->grammar.rules[symbol];
            for(unsigned j = 0; j < rulesForSymbol.size(); j++)
            {
                Rule copyR(rulesForSymbol[j]);
                copyR.rightSide = "." + copyR.rightSide;
                if(!contains(resultList, copyR))
                    resultList.push_back(copyR);
            }
        }
    }
    return resultList;
}

void DFA::transition(State* s, string symbol)
{
    State* nextState = new State();
    deque<Rule> newStateItems;
    for(unsigned i = 0; i < s->items.size(); i++)
    {
        Rule r = s->items[i];
        string nextSymbol = symbolAfterPeriod(r.rightSide);
        if(symbol.compare(nextSymbol) == 0)
        {
            Rule copyR(r);
            copyR.rightSide = moveDot(copyR.rightSide);
            if(copyR.rightSide[copyR.rightSide.size() - 1] == '.')
                nextState->isFinalState = true;
            if(copyR.rightSide.compare("S$.") == 0 && copyR.leftSide.compare("S^") == 0)
                nextState->isEndingState = true;


            deque<Rule> closureSet = closure(copyR);

            for(unsigned j = 0; j < closureSet.size(); j++)
                if(!contains(newStateItems, closureSet[j]))
                    newStateItems.push_back(closureSet[j]);
        }
    }
    if(newStateItems.size() == 0)
        return;
    nextState->items = newStateItems;
    State* searched = searchState(*nextState);
    Edge e;
    e.arc = symbol;
    e.source = s;
    if(searched == NULL)
    {
        e.target = nextState;
        nextState->id = DFA::stateID;
        DFA::stateID++;
        states.push_back(nextState);
    }
    else
        e.target = searched;

    s->outgoingArcs.push_back(e);
}

string DFA::symbolAfterPeriod(string str)
{
    unsigned periodIndex = str.find('.');
    if(periodIndex == str.size() - 1)//Nokta katarýn sonunda
        return "";
    else
    {
        unsigned nextSymbolIndex = str.find("S", periodIndex);
        if(nextSymbolIndex == periodIndex + 1)//Noktadan sonra S var
            return "S";

        nextSymbolIndex = str.find("Deyimler", periodIndex);
        if(nextSymbolIndex == periodIndex + 1)//Noktadan sonra Deyimler var
            return "Deyimler";

        nextSymbolIndex = str.find("Deyim", periodIndex);
        if(nextSymbolIndex == periodIndex + 1)//Noktadan sonra Deyim var
            return "Deyim";

        nextSymbolIndex = str.find("Degisken", periodIndex);
        if(nextSymbolIndex == periodIndex + 1)//Noktadan sonra Deyim var
            return "Degisken";

        nextSymbolIndex = str.find("Ifade", periodIndex);
        if(nextSymbolIndex == periodIndex + 1)//Noktadan sonra Ifade var
            return "Ifade";

        nextSymbolIndex = str.find("id", periodIndex);
        if(nextSymbolIndex == periodIndex + 1)//Noktadan sonra id var
            return "id";

        return str.substr(periodIndex + 1, 1);//Noktadan sonra tek uzunlukta terminal simge var
    }
}

string DFA::nonTerminalSymbolAfterPeriod(string str)
{
    string symbol = symbolAfterPeriod(str);
    if(symbol.size() > 1 || symbol.compare("S") == 0)
        return symbol;
    else
        return "";
}

bool DFA::contains(const deque<Rule>& rules, const Rule& rule)
{
    for(unsigned i = 0; i < rules.size(); i++)
        if(rules[i] == rule)
            return true;
    return false;
}

string DFA::moveDot(string str)
{
    unsigned periodIndex = str.find('.');
    string nextSymbol = symbolAfterPeriod(str);
    unsigned remainsIndex = periodIndex + nextSymbol.size() + 1;
    string result = str.substr(0, periodIndex) + nextSymbol + "." + str.substr(remainsIndex);

    return result;
}

State* DFA::searchState(State& s)
{
    for(unsigned i = 0; i < states.size(); i++)
        if(*(states[i]) == s)
           return states[i];
    return NULL;
}
