/****************************************
Name: Ozan Arkan CAN
Id: 040090573
Course Id: BLG252E
Course Name: Object Oriented Programming
Homework #1
****************************************/

#ifndef CLASSLIST_H
#define CLASSLIST_H

#include "Student.h"

class ClassList{
	int size;// Variable for setting size for student array(new)
    int counter;// Counter to count inserting student numbers
	Student *array;// Array for inserting students
	
public:
	ClassList(unsigned int);// ClassList class constructor
	ClassList(const ClassList&);// ClassList class copy constructor
	~ClassList();// ClassList class destructor
	bool insert(Student&);// Function for inserting new students
	void printAll();// Function to print all students in array
	Student *find(int);// Function to find student in array as giving parameter
};

#endif

