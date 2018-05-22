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
#include "Raft.h"

Raft::Raft()
{
    numberOfPassenger = 0;
    atSide = false;
    onPeople[0] = NULL;
    onPeople[1] = NULL;
}

bool Raft::getOnPassenger(Person* p)
{
    if(numberOfPassenger == 2)
        return false;
    else
    {
        if(numberOfPassenger == 0)
        {
            onPeople[0] = p;
        }
        else
        {
            onPeople[1] = p;
        }

        numberOfPassenger++;
        return true;
    }

}

void Raft::removeAllPassenger()
{
    numberOfPassenger = 0;
}

void Raft::sailAcross()
{
    if(atSide){
        atSide = false;
		}
    atSide = true;
	onPeople[0]->setSide();
	if(onPeople[1])
		onPeople[1]->setSide();
}
