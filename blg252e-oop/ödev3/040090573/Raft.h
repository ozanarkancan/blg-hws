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
#ifndef RAFT_H
#define RAFT_H

#include "Person.h"

class Raft
{
    Person *onPeople[2];
    int numberOfPassenger;
    bool atSide;// 0 for left, 1 for right
    public:
        Raft();
        bool getOnPassenger(Person*);
        void removeAllPassenger();
        void sailAcross();
        friend class Game;

};

#endif // RAFT_H
