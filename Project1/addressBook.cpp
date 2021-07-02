#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "addressBook.h"

using namespace std;


// Constructor
ListNode::ListNode(string* myFriend) {
	if (myFriend == NULL) return;

	info = new string[3];

	for (int i = 0; i < 3; i++) {
		info[i] = myFriend[i];
	}
	next = NULL;
}
 
int List::birth[12] = { 0, };

// Constructor
List::List(int ignored) {
	head = NULL;
	cursor = NULL;
}

//	Destructor
List::~List() {
	clear();
}


void List::insert(string* newElement) {
	if (isFull()) {
		cout << " The list is full" << endl;
		return;
	}
	ListNode* newNode = new ListNode(newElement);

	if (isEmpty()) {	
		head = newNode;
	}
	else {	
		cursor->next = newNode;
	}
	cursor = newNode;

	int month = stoi(newElement[2].substr(0, 2));
	birth[month - 1]++;

	return;
}

void List::remove(const string& target) {
	if (isEmpty()) {
		cout << "The list is empty" << endl;
		return;
	}

	ListNode* temp = head;
	while (temp != NULL) {
		if (temp->info[0] == target) break;		
		temp = temp->next;
	}


	if (temp == NULL) {
		cout << "There isn't such a person whose name is " << target << endl;
	}
	else {
		birth[stoi(temp->info[2].substr(0, 2))-1]--;
		if (temp == head) {
			head = temp->next;
		}
		else {
			ListNode* pre = head;
			while (pre->next != temp) pre = pre->next;

			if (temp->next != NULL) 
				pre->next = temp->next;			
			else 
				cursor = pre; 
		}
	}

	delete temp;
}


void List::readFile(const string& fileName) {
	ifstream in(fileName+".txt");
	string* myFriend = new string[3];

	if (in.fail()) {
		cout << "The file doesn't exist" << endl;
		return;
	}

	int i = 0;
	while (!in.eof()) {
		getline(in, myFriend[i]);			
		i++;
		if (i == 3) {		
			insert(myFriend); 
			string ignored;
			getline(in, ignored);	
			i = 0;
		}
	}
	in.close();
}

void List::writeList(const string& fileName) {
	ofstream out(fileName+".txt");

	ListNode* temp = head;
	while (temp != NULL) {
		string* myFriend = temp->info;

		for (int i = 0; i < 3; i++) {
			out << myFriend[i] << endl;
		}
		out << endl;
		temp = temp->next;
	}

	out.close();
}

void List::countBirth(const string& month) {
	int target;
	
	if (month == "January") target = 1;
	else if (month == "Fabruary") target = 2;
	else if (month == "March") target = 3;
	else if (month == "April") target = 4;
	else if (month == "May") target = 5;
	else if (month == "June") target = 6;
	else if (month == "July") target = 7;
	else if (month == "August") target = 8;
	else if (month == "September") target = 9;
	else if (month == "October") target = 10;
	else if (month == "November") target = 11;
	else if (month == "December") target = 12;
	else {
		cout << "Invalid Command" << endl;
		return;
	}

	
	ListNode* temp = head;
	cout << "Total number of birthdays in " << month << " : " <<birth[target - 1] <<endl;
	while (temp != NULL) {
		if (stoi(temp->info[2].substr(0, 2)) == target) {
			cout << temp->info[0] << endl;
			cout << temp->info[1] << endl;
			cout << temp->info[2] << endl;
		}
		cout << endl;
		temp = temp->next;
	}
}


void List::summary() {
	
	
	int len = 0;
	ListNode* temp = head;
	while (temp != NULL) {
		temp = temp->next;
		len++;
	}

	cout << "Total number of entries in the list : " << len << endl;
	cout << "Number of birthdays in" << endl;
	for (int i = 0; i < 12; i++) {
		if (birth[i] != 0) {
			switch (i)
			{
			case 0:
				cout << "\tJanuary: " << birth[i] <<endl; 
				break;
			case 1:
				cout << "\tFabruary: " << birth[i] << endl;
				break;
			case 2:
				cout << "\tMarch: " << birth[i] << endl;
				break;
			case 3:
				cout << "\tApril: " << birth[i] << endl;
				break;
			case 4:
				cout << "\tMay: " << birth[i] << endl;
				break;
			case 5:
				cout << "\tJune: " << birth[i] << endl;
				break;
			case 6:
				cout << "\tJuly: " << birth[i] << endl;
				break;
			case 7:
				cout << "\tAugust: " << birth[i] << endl;
				break;
			case 8: 
				cout << "\tSeptember: " << birth[i] << endl;
				break;
			case 9:
				cout << "\tOctober: " << birth[i] << endl;
				break;
			case 10:
				cout << "\tNovember: " << birth[i] << endl;
				break;
			case 11:
				cout << "\tDecember: " << birth[i] << endl;
				break;
			default:
				break;
			}
		}
	}

}

void List::clear() {
	cursor = NULL;
	
	while (head != NULL) {
		ListNode* temp = head;
		head = head->next;
		delete temp;
	}
}

bool List::isEmpty() {
	return (head == NULL);
}

bool List::isFull() {
	ListNode* location = new ListNode(NULL);
	if (location == NULL) return true;
	else {
		delete location;
		return false;
	}
}