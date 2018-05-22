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
#include "Person.h"

void Person::setSide()
{
    if(atSide)
        atSide = false;
    atSide = true;
}

bool Person::operator==(const Person& p)
{
    return name == p.getName();
}
