#pragma once

#include <string>
using namespace std;

class ListNode {
private:
	//	Constructor
	ListNode(string* myFriend);

	//	Data members
	string* info;		
	ListNode* next;

	friend class List;
};

class List {
	//	Data members
	ListNode* head,
		* cursor;
	static int birth[12];	

public:
	//	Constructor
	List(int ignored = 0);

	//	Destructor
	~List();

	//	Operations
	void insert(string* newElement);
	void remove(const string& target);
	void readFile(const string& fileName);		
	void writeList(const string& fileName);		
	void countBirth(const string& month);			
	void summary();		
	void clear();	

	//	List status
	bool isEmpty();
	bool isFull();
};
