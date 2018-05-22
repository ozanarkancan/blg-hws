#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

using namespace std;

class node
{
    bool isWinSituation;
    bool isTucoLive;
    bool* order;
    float probability;
    node** children;
    string situation;
    int  numberOfChild;
    int currentStep;
    int AngelEyesMisses;
    int BlondieMisses;
    public:
        node(int);
        ~node();
        string getSituation();
        void setSitiuation(string);
        void setLivingSituation(bool);
        bool getLivingSituation();
        int getCurrentStep();
        void updateCurrentStep(int);
        void updateProbability(float);
        float getProbability();
        void updateWinSituation(bool);
        int getNumberOfChild();
        node* getChild(int);
        bool getWinSituation();
        bool* getOrder();
        void updateOrder(bool, bool, bool);
        void setAngelEyesMisses(int);
        void setBlondieMisses(int);
        int getAngelEyesMisses();
        int getBlondieMisses();
        friend class tree;
    protected:
};

#endif // NODE_H
