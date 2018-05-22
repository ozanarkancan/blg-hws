#include "ParseTable.h"
#include "Edge.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

ParseTable::ParseTable() : dfa(grammar)
{
}

ParseTable::~ParseTable()
{
}

void ParseTable::generateTable()
{
    dfa.buildDFA();

    for(unsigned i = 0; i < dfa.states.size(); i++)
    {
        State* s = dfa.states[i];
        if(s->isEndingState)
            continue;
        if(s->items[0] == Rule("S^", "S.$", -1))
        {
            Cell c;
            c.isAcceptance = true;
            c.action = "acc";
            (table[s->id]["$"]).push_back(c);
            continue;
        }

        if(s->isFinalState)
        {
            Cell c;
            c.action = "r";
            Rule reductionRule = findReductionRule(s->items);
            c.no = reductionRule.id;

            for(unsigned j = 0; j < grammar.nonterminals.size(); j++)
                (table[s->id][grammar.nonterminals[j]]).push_back(c);

            for(unsigned j = 0; j < grammar.terminals.size(); j++)
                (table[s->id][grammar.terminals[j]]).push_back(c);
        }

        for(unsigned j = 0; j < s->outgoingArcs.size(); j++)
        {
            Edge e = s->outgoingArcs[j];

            Cell c;
            c.no = e.target->id;

            bool contains = count(grammar.terminals.begin(), grammar.terminals.end(), e.arc) == 0 ? false : true;

            if(contains)
                c.action = "s";
            else
                c.action = "g";

            (table[s->id][e.arc]).push_back(c);
        }
    }
}

Rule ParseTable::findReductionRule(const deque<Rule>& items) const
{
    Rule r;
    for(unsigned i = 0; i < items.size(); i++)
    {
        r = items[i];
        if(*(r.rightSide.end()) == '.')
            return r;
    }
    return r;
}

void ParseTable::printTable()
{
    ofstream out("parseTable");

    cout << "State\t";
    out << "State\t";;
    for(unsigned i = 0; i < grammar.nonterminals.size(); i++)
    {
        cout << grammar.nonterminals[i] << "\t";
        out << grammar.nonterminals[i] << "\t";
    }

    for(unsigned i = 0; i < grammar.terminals.size(); i++)
    {
        cout << grammar.terminals[i] << "\t";
        out << grammar.terminals[i] << "\t";
    }

    cout << endl;
    out << endl;

    for(unsigned i = 0; i < dfa.states.size(); i++)
    {
        State* s = dfa.states[i];
        if(s->isEndingState)
            continue;
        cout << s->id << "\t";
        out << s->id << "\t";

        for(unsigned j = 0; j < grammar.nonterminals.size(); j++)
        {
            deque<Cell> entries = table[s->id][grammar.nonterminals[j]];
            if(entries.size() == 1)
            {
                Cell c = entries[0];
                cout << c.action;
                out << c.action;

                if(!c.isAcceptance)
                {
                    cout << c.no;
                    out << c.no;
                }
                cout << "\t";
                out << "\t";
            }
            else if(entries.size() > 1)//Conflict
            {
                Cell c = entries[0];
                cout << c.action << c.no;
                out << c.action << c.no;

                for(unsigned k = 1; k < entries.size(); k++)
                {
                    c = entries[k];
                    cout << "/" << c.action << c.no;
                    out << "/" << c.action << c.no;
                }
                cout << "\t";
                out << "\t";
            }
            else
            {
                cout << "\t";
                out << "\t";
            }
        }

        for(unsigned j = 0; j < grammar.terminals.size(); j++)
        {
            deque<Cell> entries = table[s->id][grammar.terminals[j]];
            if(entries.size() == 1)
            {
                Cell c = entries[0];
                cout << c.action;
                out << c.action;
                if(!c.isAcceptance)
                {
                    cout << c.no;
                    out << c.no;
                }

                cout << "\t";
                out << "\t";
            }
            else if(entries.size() > 1)//Conflict
            {
                Cell c = entries[0];
                cout << c.action << c.no;
                out << c.action << c.no;

                for(unsigned k = 1; k < entries.size(); k++)
                {
                    c = entries[k];
                    cout << "/" << c.action << c.no;
                    out << "/" << c.action << c.no;
                }
                cout << "\t";
                out << "\t";
            }
            else
            {
                cout << "\t";
                out << "\t";
            }
        }

        cout << endl;
        out << endl;
    }
    out.close();
}

Cell ParseTable::getCell(int state, string token)
{
    if(state == 5 && token.compare("[") == 0)
        return table[state][token][1];
	if((table[state][token]).size() == 0)
        throw "Ayristirma hatasi!";
    return table[state][token][0];
}

Grammar ParseTable::getGrammar()
{
    return grammar;
}
