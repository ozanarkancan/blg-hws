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

#include <iostream>
#include <list>
#include "person.h"

using namespace std;

typedef list<string> List;
typedef List::const_iterator Iter;

Person::Person(string name){
    this->name = name;
}

string Person::getName() const{return this->name;}

bool Person::canOperateTheRaft() const{return false;}

bool Person::canGetOnTheRaftWith(const Person &p, list<string> list) const{
	return false;
}

Mother::Mother(string name):Person(name){}

bool Mother::canOperateTheRaft() const{ return true; }

bool Mother::canGetOnTheRaftWith(const Person &p, list<string> list) const{
    if(!(p.getName() == "Father" || p.getName() == "Policeman" || p.getName().compare(0, 8, "Daughter") == 0)){
		cout << this->getName() << " can't accros the river with " << p.getName() << endl;
        return false;
	}
     else{
         //Mother and Father
         if(p.getName() == "Father"){
             return true;
         }

         //Mother and Daughter
         if(p.getName().compare(0,8, "Daughter") == 0){
             for(Iter i = list.begin(); i != list.end(); i++){
                 if(i->compare(0,8,"Daughter") == 0){
                     for(Iter j = list.begin(); j != list.end(); j++){
                         if(*j == "Father"){
							 cout << "Father is left with daughter without mother's presence." << endl;
                            return false;
						 }
                     }
                 }
             }
             return true;
         }

         //Mother and Policeman
         if(p.getName() == "Policeman"){
             for(Iter i = list.begin(); i != list.end(); i++){
                 if(*i == "Thief" && list.size() != 1){
					 cout << "Thief is left with a family member without policeman's presence." << endl;
                     return false;
                 }
             }
             return true;
         }
         }
     }


Father::Father(string name):Person(name){}

bool Father::canOperateTheRaft()const{ return true; }

bool Father::canGetOnTheRaftWith(const Person &p, list<string> list) const{
    if(!(p.getName() == "Mother" || p.getName() == "Policeman" || p.getName().compare(0, 3, "Son") == 0) ){
        cout << this->getName() << " can't accros the river with " << p.getName() << endl;
		return false;
	}
    else{
        //Father and Mother
        if(p.getName() == "Mother"){
            return true;
        }

        //Father and Son
        if(p.getName().compare(0,3,"Son") == 0){
            for(Iter i = list.begin(); i != list.end(); i++){
                if(i->compare(0,3,"Son") == 0){
                    for(Iter j = list.begin(); j != list.end(); j++){
                        if(*j == "Mother"){
							cout << "Mother is left with son without father's presence." << endl;
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        //Father  and Policeman
        if(p.getName() == "Policeman"){
            for(Iter i = list.begin(); i != list.end(); i++){
                if(*i == "Thief" && list.size() != 1){
					cout << "Thief is left with a family member without policeman's presence." << endl;
                    return false;
                }
            }
            return true;
        }
    }
}

Daughter::Daughter(string name):Person(name){}

bool Daughter::canGetOnTheRaftWith(const Person &p, list<string> list) const{
    if(!(p.getName() == "Mother" || p.getName() == "Policeman")){
        cout << this->getName() << " can't accros the river with " << p.getName() << endl;
		return false;
	}
    else{
        //Daughter and Mother
        if(p.getName() == "Mother"){
            for(Iter i = list.begin(); i != list.end(); i++){
                 if(i->compare(0,8,"Daughter") == 0){
                     for(Iter j = list.begin(); j != list.end(); j++){
                         if(*j == "Father")
							 cout << "Father is left with daughter without mother's presence." << endl;
                            return false;
                     }
                 }
             }
             return true;
        }

        //Daughter and Policeman
        if(p.getName() == "Policeman"){
            for(Iter i = list.begin(); i != list.end(); i++){
                if(*i == "Thief" && list.size() != 1){
					cout << "Thief is left with a family member without policeman's presence." << endl;
                    return false;
                }
            }
            return true;
        }
    }
}

Son::Son(string name):Person(name){}

bool Son::canGetOnTheRaftWith(const Person &p, list<string> list) const{
    if(!(p.getName() == "Father" || p.getName() == "Policeman")){
		cout << this->getName() << " can't accros the river with " << p.getName() << endl;
		return false;
	}
    else{
        //Son and Father
        if(p.getName() == "Father"){
            for(Iter i = list.begin(); i != list.end(); i++){
                 if(i->compare(0,3,"Son") == 0){
                     for(Iter j = list.begin(); j != list.end(); j++){
                         if(*j == "Mother"){
							 cout << "Mother is left with son without father's presence." << endl;
                            return false;
						 }
                     }
                 }
             }
             return true;
        }

        //Son and Policeman
        if(p.getName() == "Policeman"){
            for(Iter i = list.begin(); i != list.end(); i++){
                if(*i == "Thief" && list.size() != 1){
					cout << "Thief is left with a family member without policeman's presence." << endl;
                    return false;
                }
            }
            return true;
        }
    }
}

Policeman::Policeman(string name):Person(name){}

bool Policeman::canOperateTheRaft() const{ return true; }

bool Policeman::canGetOnTheRaftWith(const Person &p, list<string> list) const{
    //Policeman and Thief
    if(p.getName() == "Thief"){
        return true;
    }
    //Policeman and Family
    else{
        for(Iter i = list.begin(); i != list.end(); i++){
                if(*i == "Thief" && list.size() != 1){
					cout << "Thief is left with a family member without policeman's presence." << endl;
                    return false;
                }
            }
            return true;
        }
    }

Thief::Thief(string name):Person(name){}

bool Thief::canGetOnTheRaftWith(const Person &p, list<string> list) const{
    //Thief and Policeman
    if(p.getName() == "Policeman"){
        return true;
    }
    //Thief and Family
    else{
		cout << "Thief is left with a family member without policeman's presence." << endl;
        return false;
    }
}
