
#pragma once
#include <iostream>
#include "listlnk.cpp"
using namespace std;


class Person {
private:
	string name;
	List<Person>* f_list;

public:
	Person() { }
	Person(string name);
	string getName();

	friend class MicroFB;
};

class MicroFB {
public:
	void create(string name);	//	create Person object for the name.
	void addFriend(string name1, string name2);		//	Record that the two specified people are friends
	void delFriend(string name1, string name2);		//	Record that the two specified people are no longer friends. 
	void showFriend(string name);	//	Print out the friends of the specified person.
	bool isFriend(string name1, string name2);		//	Check weather the two people are friends
};
