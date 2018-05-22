/****************************************
Name: Ozan Arkan CAN
Id: 040090573
Course Id: BLG252E
Course Name: Object Oriented Programming
Homework #1
****************************************/

#include <iostream>
#include "ClassList.h"

using namespace std;

ClassList::ClassList(unsigned int size){
	this->size = size;
	array = new Student[size];
	counter = 0;
}

ClassList::ClassList(const ClassList& copy)
{
	this->counter = 0;
	this->size = copy.size;
	this->array = new Student[this->size];
	for(int i = 0; i < this->counter; i++)
		this->insert(copy.array[i]);

}

ClassList::~ClassList()
{
	delete[] array;

}

void ClassList::printAll()
{
	for(int i = 0; i < this->counter ; i++)
		this->array[i].print();
}

bool ClassList::insert(Student& newStudent)
{
	if(counter >= size)
		return false;
	else{
		array[counter].setId(newStudent.getId());
		array[counter].setName(newStudent.getName());
		array[counter].setSurname(newStudent.getSurname());
		
		this->counter++;
		
		return true;
	}
}

Student *ClassList::find(int id)
{
	for(int i = 0; i < counter; i++)
		if(id == array[i].getId())
			return &array[i];
	return false;
}
