/*
*
*	BLG 252E
*	2011 Spring
*	3rd Homework
*
*
*
*
*	Student Name: Ozan Arkan Can
*	Student ID  : 040090573
*
*
*/
#include "Game.h"

Game::Game()
{
    left = new Array<Person*>(8);
    right = new Array<Person*>(8);
    
    // Initilizing people at which side
    left->setElement(0, &m);
    left->setElement(1, &f);
    left->setElement(2, &s[0]);
    left->setElement(3, &s[1]);
    left->setElement(4, &d[0]);
    left->setElement(5, &d[1]);
    left->setElement(6, &p);
    left->setElement(7, &t);
    right->setElement(0, NULL);
    right->setElement(1, NULL);
    right->setElement(2, NULL);
    right->setElement(3, NULL);
    right->setElement(4, NULL);
    right->setElement(5, NULL);
    right->setElement(6, NULL);
    right->setElement(7, NULL);
}

Game::~Game()
{
    delete left;
    delete right;
}
bool Game::isInArray(Array<Person*> a, string name)
{
    for(int i = 0; i < a.getSize() ; i++)
    {
        if(a[i]->getName() == name)
            return true;
    }
    return false;
}

bool Game::motherSonInconsistency(Array<Person*> a)
{
    if(isInArray(a, "Mother") && !isInArray(a, "Father"))
            if(isInArray(a, "Son"))
                throw "Mother Son Inconsistency";
    return false;
}

bool Game::fatherDaughterInconsistency(Array<Person*> a)
{
    if(!isInArray(a, "Mother") && isInArray(a, "Father"))
            if(isInArray(a, "Daughter"))
                throw "Father Daughter Inconsistency";
    return false;
}

bool Game::thiefFamilyInconsistency(Array<Person*> a)
{
    if(isInArray(a, "Thief") && !isInArray(a, "Policeman"))
            if(a.numberOfElement() > 1)
                throw "Thief Family Inconsistency";
    return false;
}

bool Game::checkRules()
{
    try
    {
        // Checking Person/People who on the raft can operate the raft
        if(!raft.onPeople[0]->canOperateTheRaft())
            return false;
        if(!raft.onPeople[1])
                if(!raft.onPeople[1]->canOperateTheRaft())
                    return false;
        if(!motherSonInconsistency(*left) && !motherSonInconsistency(*right) && !fatherDaughterInconsistency(*left) && !fatherDaughterInconsistency(*right) && !thiefFamilyInconsistency(*left) && !thiefFamilyInconsistency(*right))
            return true;
    }
    catch(const char* exception)
    {
        cout << exception << endl;
    }
}

void Game::store(Person* p1, Person* p2)
{
    storePeople[0] = p1;
    storePeople[1] = p2;
}

