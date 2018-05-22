#ifndef STATE_H
#define STATE_H

#include <deque>
#include <string>
#include "Edge.h"
#include "Rule.h"

using namespace std;

class Edge;

class State
{
    public:
        State();
        ~State();
        bool isFinalState;
        bool isEndingState;
        deque<Rule> items;
        deque<Edge> outgoingArcs;
        bool operator==(const State rhs) const;
        int id;
        bool outgoingArcsGenerated;
    private:

};

#endif // STATE_H
