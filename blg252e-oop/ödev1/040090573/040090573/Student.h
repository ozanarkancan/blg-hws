/****************************************
Name: Ozan Arkan CAN
Id: 040090573
Course Id: BLG252E
Course Name: Object Oriented Programming
Homework #1
****************************************/

#ifndef STUDENT_H
#define STUDENT_H

class Student{
	int id; // Variable for student id
	char *name; // Pointer for student name
	char *surname; // Pointer for student surname
public:
	~Student(); // Student class destructor
	void print() const; // Function for printing student information
	void setId(int); // Function for setting student id
	void setName(char *);// Function for setting student name
	void setSurname(char *);// Function for setting student surname
	int getId() const;// Function for getting student id
	char *getName() const;// Function for getting student name
	char *getSurname() const;// Function for getting student surname

};

#endif

