/*
*
*	BLG252E
*	2011 Spring
*	2nd Homework
*
*/

/*
*
*	Student Name: Ozan Arkan CAN
*	Student ID: 040090573
*
*/

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <list>

using namespace std;

class Person{
    string name;
    public:
    Person(string );
    string getName() const;
	virtual bool canGetOnTheRaftWith(const Person &p, list<string> list) const;//It is not used, but it must be for polymorphism
    virtual bool canOperateTheRaft() const;
};

class Mother : public Person{
    public:
    Mother(string name);
    virtual bool canOperateTheRaft() const;
    bool canGetOnTheRaftWith(const Person &p, list<string> list) const;
};

class Father : public Person{
    public:
    Father(string name);
    virtual bool canOperateTheRaft() const;
    bool canGetOnTheRaftWith(const Person &p, list<string> list) const;
};

class Daughter : public Person{
    public:
    Daughter(string name);
    bool canGetOnTheRaftWith(const Person &p, list<string> list) const;
};

class Son : public Person{
    public:
    Son(string name);
    bool canGetOnTheRaftWith(const Person &p, list<string> list) const;
};

class Policeman : public Person{
    public:
    Policeman(string name);
    virtual bool canOperateTheRaft() const;
    bool canGetOnTheRaftWith(const Person &p, list<string> list) const;
};

class Thief : public Person{
    public:
    Thief(string name);
    bool canGetOnTheRaftWith(const Person &p, list<string> list) const;
};
#endif // PERSON_H_INCLUDED
