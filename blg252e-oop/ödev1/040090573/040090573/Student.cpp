/****************************************
Name: Ozan Arkan CAN
Id: 040090573
Course Id: BLG252E
Course Name: Object Oriented Programming
Homework #1
****************************************/

#include "Student.h"
#include <cstring>
#include <iostream>

using namespace std;

Student::~Student()
{
	delete[] this->name;
	delete[] this->surname;
}

void Student::setId(int id)
{
	this->id = id;
}

void Student::setName(char *Name){
	this->name = new char[strlen(Name)];
	strcpy(this->name, Name);
}

void Student::setSurname(char *Surname)
{
	this->surname = new char[strlen(Surname)];
	strcpy(this->surname , Surname);
}

int Student::getId() const
{
	return this->id;
}

char *Student::getName() const
{
	return name;
}

char *Student::getSurname() const
{
	return surname;
}


void Student::print() const{
cout << "Id: " << this->id << endl;
cout << "Name: " << this->name << endl;
cout << "Surname: " << this->surname << endl << endl;
}

