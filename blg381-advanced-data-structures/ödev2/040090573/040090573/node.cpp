#include "node.h"

node::node(int size = 0)
{
    probability = 1;
    isWinSituation = false;
    isTucoLive = true;
    numberOfChild = size;
    AngelEyesMisses = 0;
    BlondieMisses = 0;
    order = new bool[3];
    updateOrder(false, false, false);

    if(size != 0)
        children = new node*[size];
    else
        children = NULL;

    for(int i = 0; i < size; i++)
        children[i] = NULL;
}

node::~node()
{
    delete[] children;
}

string node::getSituation() { return situation; }

void node::setSitiuation(string str) { situation = str; }

float node::getProbability() { return probability; }

void node::updateProbability(float probability) { this->probability *= probability; }

void node::updateWinSituation(bool situation = true) { isWinSituation = situation; }

int node::getNumberOfChild() { return numberOfChild; }

node* node::getChild(int index) { return children[index]; }

void node::setLivingSituation(bool situation) { isTucoLive = situation;}

bool node::getLivingSituation() { return isTucoLive;}

int node::getCurrentStep() { return currentStep; }

void node::updateCurrentStep(int step) { currentStep = step; }

bool node::getWinSituation() { return isWinSituation; }

bool* node::getOrder() { return order; }

void node::updateOrder(bool forTuco, bool forAngelEyes, bool forBlondie)
{
    order[0] = forTuco;
    order[1] = forAngelEyes;
    order[2] = forBlondie;
}

int node::getAngelEyesMisses() { return AngelEyesMisses; }

int node::getBlondieMisses() { return BlondieMisses; }

void node::setAngelEyesMisses(int misses) { AngelEyesMisses = misses; }

void node::setBlondieMisses(int misses) { BlondieMisses = misses; }
