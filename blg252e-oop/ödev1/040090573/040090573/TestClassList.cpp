/****************************************
Name: Ozan Arkan CAN
Id: 040090573
Course Id: BLG252E
Course Name: Object Oriented Programming
Homework #1
****************************************/

#include "Student.h"
#include "ClassList.h"
#include <iostream>
#include <cstdlib>

using namespace std;

const unsigned int MUX_NUM = 1;

int main(){
	Student students[MUX_NUM + 1];
	
	// Giving Students Information
	for(int i = 0; i < MUX_NUM + 1; i++){
		int id_new;
		char name_new[10], surname_new[20];
		cout << "Enter " << i + 1 << ". student information:" << endl;
		cout << "Id: "; cin >>id_new;
		cout << "Name: "; cin >> name_new;
		cout << "Surname: "; cin >> surname_new;
		students[i].setId(id_new);
		students[i].setName(name_new);
		students[i].setSurname(surname_new);
	}

	ClassList BLG252E(MUX_NUM);
	for(int i = 0; i < MUX_NUM + 1; i++)
		if(!BLG252E.insert(students[i]))
			cout << "Inserting the student info is failed" << endl;
	cout << "***************************************" << endl;
	BLG252E.printAll();
	cout << "***************************************" << endl;
	ClassList BLG312 = BLG252E;
	cout << "***************************************" << endl;
	int search_id;
	cout << "Searching for a student in the class BLG252E..." << endl
		<< "id: "; cin >> search_id;
	Student *s1 = BLG252E.find(search_id);
	if(s1 != NULL){
		s1->print();
		s1->setSurname("New Surname");
	}
	else
		cout << "Student does not exist int the class " << endl;
	cout << "***************************************" << endl;
	BLG252E.printAll();
	cout << "***************************************" << endl;
	BLG312.printAll();
	system("pause");
	return 0;
}
