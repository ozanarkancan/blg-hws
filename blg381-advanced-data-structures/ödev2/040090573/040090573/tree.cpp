#include "tree.h"
#include <time.h>
#include <iostream>
#include <cstdlib>

using namespace std;

tree::tree()
{
    average = 0;
    bool order[] = {false, false, false};
    createNode(root, "root", 1, 3, true, 1, order, 0, 0);
}

tree::~tree()
{
    clearTree(root);
}

node* tree::getRoot() { return root; }

void tree::showAverage() { cout << "Average running step: " << average << endl;}

void tree::createNode(node* newNode, string situation, float probability, int children , bool forTuco, int step, bool* order, int missesA, int missesB)
{
    newNode = new node(children);
    newNode->setSitiuation(situation);
    newNode->updateProbability(probability);
    newNode->setLivingSituation(forTuco);
    newNode->updateCurrentStep(step);
    newNode->updateOrder(order[0], order[1], order[2]);
    newNode->setAngelEyesMisses(missesA);
    newNode->setBlondieMisses(missesB);
}

void tree::createProbabilityTree(node* current)
{

    if(!current->getWinSituation())
    {

        string situation = current->getSituation();
        bool* order = current->getOrder();
            if(situation == "root")
            {
                order[0] = true;
                createNode(current->getChild(0), "Tuco shoots", current->getProbability() * 0.333, 1, true, current->getCurrentStep() , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                cout << "Hi" << endl;
                order[0] = false; order[1] = true;
                createNode(current->getChild(1),"Angel Eyes shoots", current->getProbability() * 0.333, 2, true, current->getCurrentStep() , order,  current->getAngelEyesMisses(), current->getBlondieMisses());
                order[1] = false; order[2] = true;
                createNode(current->getChild(2),"Blondie shoots", current->getProbability() * 0.333, 1, true, current->getCurrentStep() , order,  current->getAngelEyesMisses(), current->getBlondieMisses());
            }
            if(situation == "Tuco shoots")
            {
                if(!order[1] && !order[2])
                    createNode(current->getChild(0),"Tuco misses", current->getProbability(), 2, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                else
                    createNode(current->getChild(0),"Tuco misses", current->getProbability(), 1, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
            }
            if(situation == "Tuco misses"){
                if(!order[1] && !order[2])
                {
                    order[1] = true;
                    createNode(current->getChild(0),"Angel Eyes shoots", current->getProbability() * 0.5, 2, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                    order[1] = false; order[2] = true;
                    createNode(current->getChild(1),"Blondie shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                }
                else
                {
                    if(order[1] && !order[2])
                    {
                        order[2] = true;
                        createNode(current->getChild(0),"Blondie shoots", current->getProbability(), 1, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                    }
                    else
                    {
                        if(order[1] && order[2])
                        {
                            order[0] = false; order[1] = false; order[2] = false;
                            createNode(current->getChild(0),"root", current->getProbability(), 3, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        }
                        else
                        {
                            if(!order[1] && order[2])
                            {
                                order[1] = true;
                                createNode(current->getChild(0),"Angel Eyes shoots", current->getProbability(), 2, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                            }
                        }
                    }
                }
            }

            if(situation == "Angel Eyes shoots"){
                if(current->getLivingSituation())
                {
                    if(25 - 5 * current->getAngelEyesMisses() != 0)
                    {
                        createNode(current->getChild(0),"shoots to Tuco", current->getProbability() * 0.15, 2, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        createNode(current->getChild(1),"shoots to Blondie", current->getProbability() * 0.85, 2, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                    }
                    else
                    {
                        createNode(current->getChild(0),"shoots to Tuco", current->getProbability() * 0.15, 1, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        createNode(current->getChild(1),"shoots to Blondie", current->getProbability() * 0.85, 1, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                    }

                }
                else
                {
                    if(25 - 5 * current->getAngelEyesMisses() != 0)
                        createNode(current->getChild(0),"shoots to Blondie", current->getProbability() * 0.85, 2, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                    else
                        createNode(current->getChild(0),"shoots to Blondie", current->getProbability() * 0.85, 1, true, current->getCurrentStep() + 1 , order, current->getAngelEyesMisses(), current->getBlondieMisses());
                }
            }

            if(situation == "shoots to Tuco"){
                if(current->getNumberOfChild() == 1)
                {
                    if(order[2])
                    {
                        order[1] = false; order[2] = false;
                        createNode(current->getChild(0),"Tuco Dies", current->getProbability(), 2, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                    }
                    else
                        createNode(current->getChild(0),"Tuco Dies", current->getProbability(), 1, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                }
                else
                {
                    if(order[0] && order[2])
                    {
                        createNode(current->getChild(0),"Tuco Dies", current->getProbability()*(0.75 + 0.05*current->getAngelEyesMisses()), 2, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        createNode(current->getChild(1),"Angel Eyes misses", current->getProbability()*(0.25 - 0.05*current->getAngelEyesMisses()), 1, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses() + 1, current->getBlondieMisses());
                    }
                    else
                    {
                        if(!order[0] && order[2])
                        {
                            createNode(current->getChild(0),"Tuco Dies", current->getProbability()*(0.75 + 0.05*current->getAngelEyesMisses()), 2, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                            createNode(current->getChild(1),"Angel Eyes misses", current->getProbability()*(0.25 - 0.05*current->getAngelEyesMisses()), 1, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses() + 1, current->getBlondieMisses());
                        }
                        else
                        {
                            if(order[0] && !order[2])
                            {
                                createNode(current->getChild(0),"Tuco Dies", current->getProbability()*(0.75 + 0.05*current->getAngelEyesMisses()), 1, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                                createNode(current->getChild(1),"Angel Eyes misses", current->getProbability()*(0.25 - 0.05*current->getAngelEyesMisses()), 1, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses() + 1, current->getBlondieMisses());
                            }
                        }
                    }
                }
            }
            if(situation == "shoots to Blondie"){
                if(current->getNumberOfChild() == 1)
                {
                    if(current->getLivingSituation())
                    {
                        createNode(current->getChild(0),"Blondie dies Angel Eyes and Tuco win", current->getProbability(), 0, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                    }
                    else
                    {
                        createNode(current->getChild(0),"Blondie dies Angel Eyes wins", current->getProbability(), 0, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                    }

                }
                else
                {
                    if(current->getLivingSituation())
                    {
                        createNode(current->getChild(0),"Blondie dies, Angel Eyes and Tuco win", current->getProbability()*(0.75 + 0.05*current->getAngelEyesMisses()), 0, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                        if(!order[0] && !order[2])
                            createNode(current->getChild(1),"Angel Eyes misses", current->getProbability()*(0.25 - 0.05*current->getAngelEyesMisses()), 2, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses() + 1, current->getBlondieMisses());
                        else
                            createNode(current->getChild(1),"Angel Eyes misses", current->getProbability()*(0.25 - 0.05*current->getAngelEyesMisses()), 1, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses() + 1, current->getBlondieMisses());
                    }
                    else
                    {
                        createNode(current->getChild(0),"Blondie dies Angel Eyes wins", current->getProbability(), 0, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                        if(!order[2])
                            createNode(current->getChild(1),"Angel Eyes misses", current->getProbability()*(0.25 - 0.05*current->getAngelEyesMisses()), 1, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses() + 1, current->getBlondieMisses());
                        else
                            createNode(current->getChild(1),"Angel Eyes misses", current->getProbability()*(0.25 - 0.05*current->getAngelEyesMisses()), 2, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses() + 1, current->getBlondieMisses());
                    }


                }
            }
            if(situation == "Angel Eyes misses"){
                    if(current->getLivingSituation())
                    {
                        if(order[0] && !order[2])
                        {
                            order[2] = true;
                            createNode(current->getChild(0),"Blondie shoots", current->getProbability(), 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        }
                        else
                        {
                            if(!order[0] && order[2])
                            {
                                order[0] = true;
                                createNode(current->getChild(0),"Tuco shoots", current->getProbability(), 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                            }
                            else
                            {
                                if(!order[0] && !order[2])
                                {
                                    order[0] = true;
                                    createNode(current->getChild(0),"Tuco shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                                    order[0] = false; order[2] = true;
                                    createNode(current->getChild(1),"Blondie shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                                }
                                else
                                {
                                    order[0] = false; order[1] = false; order[2] = false;
                                    createNode(current->getChild(0),"root", current->getProbability(), 3, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                                }

                            }

                        }

                    }
                    else
                    {
                        if(!order[2])
                        {
                            order[2] = true;
                            createNode(current->getChild(0),"Blondie shoots", current->getProbability(), 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        }
                        else
                        {
                            order[1] = true;
                            createNode(current->getChild(0),"Angel Eyes shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                            order[1] = false; order[2] = true;
                            createNode(current->getChild(1),"Blondie shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        }
                    }
                }
            if(situation == "Blondie shoots"){
                if(20 - 5*current->getBlondieMisses() == 0)
                    createNode(current->getChild(0),"shoots to Angel Eyes", current->getProbability(), 1, current->getLivingSituation(), current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                else
                    createNode(current->getChild(0),"shoots to Angel Eyes", current->getProbability(), 2, current->getLivingSituation(), current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
            }

            if(situation == "shoots to Angel Eyes"){
                if(20 - 5*current->getBlondieMisses() == 0)
                {
                    if(current->getLivingSituation())
                    {
                        createNode(current->getChild(0),"Angel Eyes dies, Blondie and Tuco win", current->getProbability(), 0, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                    }
                    else
                    {
                        createNode(current->getChild(0),"Angel Eyes dies, Blondie wins", current->getProbability(), 0, false, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                    }
                }
                else
                {
                    if(current->getLivingSituation())
                    {
                        createNode(current->getChild(0),"Angel Eyes dies, Blondie and Tuco win", current->getProbability()*(0.8+0.05*current->getBlondieMisses()), 0, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                        if(!order[0] && !order[1])
                            createNode(current->getChild(1),"Blondie misses", current->getProbability()*(0.2 - 0.05*current->getBlondieMisses()), 2, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses() + 1);
                        else
                            createNode(current->getChild(1),"Blondie misses", current->getProbability()*(0.2 - 0.05*current->getBlondieMisses()), 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses() + 1);
                    }
                    else
                    {
                        createNode(current->getChild(0),"Angel Eyes dies, Blondie wins", current->getProbability()*(0.8+0.05*current->getBlondieMisses()), 0, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        current->getChild(0)->updateWinSituation(true);
                        if(order[1])
                            createNode(current->getChild(1),"Blondie misses", current->getProbability()*(0.2 - 0.05*current->getBlondieMisses()), 2, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses() + 1);
                        else
                            createNode(current->getChild(1),"Blondie misses", current->getProbability()*(0.2 - 0.05*current->getBlondieMisses()), 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses() + 1);
                    }
                }
            }

            if(situation == "Blondie misses"){
                if(current->getLivingSituation())
                    {
                        if(order[0] && !order[1])
                        {
                            order[1] = true;
                            createNode(current->getChild(0),"Angel Eyes shoots", current->getProbability(), 2, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        }
                        else
                        {
                            if(!order[0] && order[2])
                            {
                                order[0] =true;
                                createNode(current->getChild(0),"Tuco shoots", current->getProbability(), 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                            }
                            else
                            {
                                if(!order[0] && !order[2])
                                {
                                    order[0] = true;
                                    createNode(current->getChild(0),"Tuco shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                                    order[0] = false; order[1] = true;
                                    createNode(current->getChild(1),"Angel Eyes shoots", current->getProbability() * 0.5, 2, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                                }
                                else
                                {
                                    order[0] = false; order[1] = false; order[2] = false;
                                    createNode(current->getChild(0),"root", current->getProbability(), 3, true, current->getCurrentStep() + 1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                                }

                            }

                        }

                    }
                    else
                    {
                        if(!order[1])
                        {
                            order[1] = true;
                            createNode(current->getChild(0),"Angel Eyes shoots", current->getProbability(), 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        }
                        else
                        {
                            order[1] = true;
                            createNode(current->getChild(0),"Angel Eyes shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                            order[1] = false; order[2] = true;
                            createNode(current->getChild(1),"Blondie shoots", current->getProbability() * 0.5, 1, true, current->getCurrentStep()+1, order, current->getAngelEyesMisses(), current->getBlondieMisses());
                        }
                    }
            }
            if(situation == "Tuco dies"){
                if(!order[2])
                {
                    order[2] = true;
                    createNode(current->getChild(0),"Blondie shoots", current->getProbability(), 1, false, current->getCurrentStep(), order, current->getAngelEyesMisses(), current->getBlondieMisses());
                }
                else
                {
                    order[1] = false; order[2] = false;
                    createNode(current->getChild(0),"Angel Eyes shoots", current->getProbability() * 0.5, 1, false, current->getCurrentStep(), order, current->getAngelEyesMisses(), current->getBlondieMisses());
                    createNode(current->getChild(1),"Blondie shoots", current->getProbability() * 0.5, 1, false, current->getCurrentStep(), order, current->getAngelEyesMisses(), current->getBlondieMisses());
                }
            }

        for(int i = 0; i < current->getNumberOfChild(); i++)
            createProbabilityTree(current->getChild(i));
    }
    else
    {
        average += current->getProbability() * current->getCurrentStep();
    }
}

void tree::tucoAnalyzsis(node* current, float& max, float& min)
{
    if(current->getWinSituation())
    {
        if(current->getSituation() == "Blondie dies, Angel Eyes and Tuco win" || current->getSituation() == "Angel Eyes dies, Blondie and Tuco win")
        {
            if(current->getProbability() < min)
                min = current->getProbability();
            if(current->getProbability() > max)
                max = current->getProbability();
        }
    }
    else
    {
        for(int i = 0; i < current->getNumberOfChild(); i++)
            tucoAnalyzsis(current->getChild(i), max, min);
    }
}

void tree::angelEyesAnalyzsis(node* current, float& max, float& min)
{
    if(current->getWinSituation())
    {
        if(current->getSituation() == "Blondie dies, Angel Eyes and Tuco win" || current->getSituation() == "Blondie dies, Angel Eyes wins")
        {
            if(current->getProbability() < min)
                min = current->getProbability();
            if(current->getProbability() > max)
                max = current->getProbability();
        }
    }
    else
    {
        for(int i = 0; i < current->getNumberOfChild(); i++)
            tucoAnalyzsis(current->getChild(i), max, min);
    }
}

void tree::blondieAnalyzsis(node* current, float& max, float& min)
{
    if(current->getWinSituation())
    {
        if(current->getSituation() == "Angel Eyes dies, Blondie wins" || current->getSituation() == "Angel Eyes dies, Blondie and Tuco win")
        {
            if(current->getProbability() < min)
                min = current->getProbability();
            if(current->getProbability() > max)
                max = current->getProbability();
        }
    }
    else
    {
        for(int i = 0; i < current->getNumberOfChild(); i++)
            tucoAnalyzsis(current->getChild(i), max, min);
    }
}

void tree::travel(node* current)
{
    if(current->getSituation() != "root")
    {
        cout << current->getSituation() << endl;
        cout << "Number of Step: " << current->getCurrentStep() << endl;
        cout << "Probability: " << current->getProbability() << endl;
        cout << endl;
    }
    for(int i = 0; i < current->getNumberOfChild(); i++)
        travel(current->getChild(i));
}

void tree::clearTree(node* current)
{
    if(!current->getWinSituation())
        for(int i = 0; i < current->getNumberOfChild(); i++)
            clearTree(current->getChild(i));
    delete current;
}

int tree::simulate()
{
    node* tmp = root;
    while(!tmp->getWinSituation())
    {
        if(tmp->getSituation() != "root")
        {
            cout << tmp->getSituation() << endl;
            cout << "Number of Step: " << tmp->getCurrentStep() << endl;
            cout << "Probability: " << tmp->getProbability() << endl;
            cout << endl;
        }
        if(tmp->getNumberOfChild() == 1)
            tmp = tmp->getChild(0);
        else
        {
            float key = random();
            if(tmp->getSituation() == "root")
            {
                if(key < 0.33)
                    tmp = tmp->getChild(0);
                else
                    if(key < 0.66)
                        tmp = tmp->getChild(1);
                    else
                        tmp = tmp->getChild(2);
            }
            else
            {
                if(tmp->getSituation() != "Angel Eyes shoots")
                {
                    if(key < 0.15)
                        tmp = tmp->getChild(0);
                    else
                        tmp = tmp->getChild(1);
                }
                else
                {
                    if(tmp->getSituation() != "shoots to Tuco" || tmp->getSituation() != "shoots to Blondie")
                    {
                        if(key < 0.75 + (tmp->getAngelEyesMisses()*0.05))
                            tmp = tmp->getChild(0);
                        else
                            tmp = tmp->getChild(1);
                    }
                    else
                    {
                        if(tmp->getSituation() != "shoots to Angel Eyes")
                        {
                            if(key < 0.80 + (tmp->getBlondieMisses()*0.05))
                                tmp = tmp->getChild(0);
                            else
                                tmp = tmp->getChild(1);
                        }
                        else
                        {
                            if(key < 0.5)
                                tmp = tmp->getChild(0);
                            else
                                tmp = tmp->getChild(1);
                        }
                    }
                }
            }
        }
    }
    cout << tmp->getSituation() << endl;
    cout << "Number of Step: " << tmp->getCurrentStep() << endl;
    cout << "Probability: " << tmp->getProbability() << endl;
    cout << endl;
    return tmp->getCurrentStep();
}

float tree::random()
{
    return (float)(rand()%100) / 100;
}


