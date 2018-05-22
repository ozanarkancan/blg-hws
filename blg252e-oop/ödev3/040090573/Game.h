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
#ifndef GAME_H
#define GAME_H

#include "Array.h"
#include "Raft.h"
#include "Person.h"

class Game
{
    //People for game
    Mother m;
    Father f;
    Son s[2];
    Daughter d[2];
    Policeman p;
    Thief t;
    Array<Person*> *left; // Array for people who are at left side
    Array<Person*> *right; // Array for people who are at right side
    Raft raft; // Raft for game
    Person *storePeople[2]; // For backtracking
    public:
        bool checkRules();
        bool isInArray(Array<Person*>, string);
        bool motherSonInconsistency(Array<Person*>);
        bool fatherDaughterInconsistency(Array<Person*>);
        bool thiefFamilyInconsistency(Array<Person*>);
		void store(Person*, Person*);
		Person** getStoredPeople() {return storePeople;}
		void solve();
        Game();
        ~Game();

};

#endif // GAME_H
