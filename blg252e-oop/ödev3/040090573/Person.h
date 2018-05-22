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
#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person
{
    string name;
    bool atSide; // 0 for left, 1 for right
    public:
	Person() {}
        Person(string newName) { name = newName; atSide = false; }
        string getName() const { return name; }
        void setSide();
        bool getSide() const { return atSide; }
        virtual bool canOperateTheRaft() const { return false;}
        bool operator==(const Person&);
};

class Operator: public Person
{
    public:
        Operator(string newName):Person(newName){}
        bool canOperateTheRaft() { return true; }
};

class NonOperator: public Person
{
    public:
        NonOperator(string newName):Person(newName){}
        bool canOperateTheRaft() { return false; }
};

class Father: public Operator
{
    public:
        Father() : Operator("Father") {}
};

class Mother: public Operator
{
    public:
        Mother(): Operator("Mother") {}
};

class Policeman: public Operator
{
    public:
        Policeman() : Operator("Policeman") {}
};

class Son: public NonOperator
{
    public:
        Son(): NonOperator("Son") {}
};

class Daughter: public NonOperator
{
    public:
        Daughter(): NonOperator("Daughter") {}
};

class Thief: public NonOperator
{
    public:
        Thief(): NonOperator("Thief") {}
};


#endif // PERSON_H

