#include <iostream>
#include< unordered_map >
#include "MicroFB.h"

using namespace std;
unordered_map<string, Person*> userMap;
unordered_map<string, bool> FriendMap;

//	============= Implementation of Person class =============

//	Constructor
Person::Person(string name) {
	this->name = name;
	f_list = new List<Person>();
}

string Person::getName() {
	return this->name;
}

//------------------------------------------------------------------------------------

//	============= Implementation of MicroFB class =============

void MicroFB::create(string name) {
	Person* newUser = new Person(name);
	userMap.insert(make_pair(name, newUser));
}

//------------------------------------------------------------------------------------

void MicroFB::addFriend(string name1, string name2) {
	// friends oneself
	if (name1 == name2) return;

	//	get the pointer to person object from userMap
	Person* first = userMap[name1];
	Person* sec = userMap[name2];

	//	if either name1 or name2 does not create first, return;
	if (first == NULL || sec == NULL) return;

	//	insert each other to f_list
	first->f_list->gotoBeginning();
	first->f_list->insertBefore(*sec);
	sec->f_list->gotoBeginning();
	sec->f_list->insertBefore(*first);


	//	insert two person key to the FriendMap
	string key;
	if (name1.compare(name2) < 0) key = name1 + "-" + name2;	// sort name and construct key
	else key = name2 + "-" + name1;
	FriendMap.insert(make_pair(key, true));
}

//------------------------------------------------------------------------------------

void MicroFB::delFriend(string name1, string name2) {
	//	unfriend oneself
	if (name1 == name2) return;

	// Construct key for search FriendMap
	string key;
	if (name1.compare(name2) < 0) key = name1 + "-" + name2;
	else key = name2 + "-" + name1;

	//	unfriends someone who is not a friend
	if (FriendMap[key] == NULL) return;

	//	get the pointer to person object from userMap
	Person* first = userMap[name1];
	Person* sec = userMap[name2];

	first->f_list->setCursor(name2);
	first->f_list->remove();

	sec->f_list->setCursor(name1);
	sec->f_list->remove();

	FriendMap[key] = false;
}

//------------------------------------------------------------------------------------

void MicroFB::showFriend(string name) {
	Person* user = userMap[name];
	cout << "[" << name << "] -> ";
	user->f_list->printReverse();
	cout << endl;
}

//------------------------------------------------------------------------------------

bool MicroFB::isFriend(string name1, string name2) {
	string key;
	if (name1.compare(name2) < 0) key = name1 + "-" + name2;
	else key = name2 + "-" + name1;

	if (FriendMap[key] == NULL) return false;	// is not friend
	else return FriendMap[key];
}

//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------

void helper() {
	cout << endl << "==========MICRO FACEBOOK==========" << endl;
	cout << "  H   : Help (displays this message)" << endl;
	cout << "  P   :  create Person" << endl;
	cout << "  F   : make friend" << endl;
	cout << "  U   : delete friend" << endl;
	cout << "  L   : show friends" << endl;
	cout << "  Q   : check weather theh two people are friends" << endl;
	cout << "  X   : exit" << endl << endl;
}

int main() {
	MicroFB facebook;
	char cmd;
	string name1, name2;
	helper();

	do {
		cout << "Command >> ";
		cin >> cmd;
		switch (cmd) {
		case 'P': case 'p':
			cin >> name1;
			facebook.create(name1);
			break;
		case 'F': case 'f':
			cin >> name1 >> name2;
			facebook.addFriend(name1, name2);
			break;
		case 'U': case 'u':
			cin >> name1 >> name2;
			facebook.delFriend(name1, name2);
			break;
		case 'L': case 'l':
			cin >> name1;
			facebook.showFriend(name1);
			break;
		case 'Q': case 'q':
			cin >> name1 >> name2;
			if (facebook.isFriend(name1, name2)) cout << "Yes" << endl;
			else cout << "No" << endl;
			break;
		case 'X': case 'x':
			return 0;
			break;
		case 'H': case 'h':
			helper();
			break;
		default:
			cout << "Invalid Command" << endl;
			break;
		}
	} while (cmd != 'X');
}