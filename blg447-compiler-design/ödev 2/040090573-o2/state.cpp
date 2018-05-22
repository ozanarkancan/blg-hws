#include "state.h"
#include "DFA.h"

using namespace std;

State::State()
{
    isFinalState = false;
    isEndingState = false;
    outgoingArcsGenerated = false;
}

State::~State()
{
    //dtor
}

bool State::operator==(const State rhs) const
{
    if(rhs.items.size() != items.size())
        return false;
    for(unsigned i = 0 ; i < items.size(); i++)
        if(!DFA::contains(rhs.items, items[i]))
            return false;
    for(unsigned i = 0 ; i < rhs.items.size(); i++)
        if(!DFA::contains(items, rhs.items[i]))
            return false;


    return true;
}
