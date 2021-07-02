#include <iostream>
#include "listdbl.h"
#include <string>

using namespace std;

template < class DT >
ListNode<DT>::ListNode(const DT& data, ListNode* priorPtr, ListNode* nextPtr)
{
	dataItem = data;
	prior = priorPtr;
	next = nextPtr;
}

// Constructor
template < class DT >
List<DT>::List(int ignored)
{
	head = NULL;
	cursor = NULL;
}

// Destructor
template < class DT >
List<DT>::~List()
{
	clear();
}


//------------ List manipulation operations ------------------

// Insert after cursor
template < class DT >
void List<DT>::insert(const DT& newDataItem)
{
	//		PRE: NOT FULL
	if (isFull()) {
		cout << "Failed -- the list is full" << endl;
		return;
	}


	ListNode<DT>* newNode = new ListNode<DT>(newDataItem, NULL, NULL);


	if (head == NULL) {
		head = newNode;
	}
	else {
		newNode->prior = cursor;
		newNode->next = cursor->next;
		if (cursor->next != NULL) cursor->next->prior = newNode;
		cursor->next = newNode;
	}
	cursor = newNode;

	return;
}

// Remove data item
template < class DT >
void List<DT>::remove()
{
	//		PRE: NOT EMPTY
	if (isEmpty()) {
		cout << "Failed -- the list is empty" << endl;
		return;
	}


	ListNode<DT>* temp = cursor;

	if (cursor->next == NULL) {
		if (cursor != head)	cursor->prior->next = NULL; 
		else head = NULL; 
		cursor = head;
	}
	else {
		cursor->next->prior = cursor->prior;
		if (cursor != head) cursor->prior->next = cursor->next;
		else head = cursor->next; 
		cursor = cursor->next;
	}


	delete temp;
	return;
}

// Replace data item
template < class DT >
void List<DT>::replace(const DT& newElement)
{
	//		PRE: NOT EMPTY
	if (isEmpty()) {
		cout << "Failed -- the list is empty" << endl;
		return;
	}

	cursor->dataItem = newElement;
	return;
}

// Clear list
template < class DT >
void List<DT>::clear()
{
	while (head != NULL) {
		ListNode<DT>* temp = head;
		head = head->next;
		delete temp;
	}
	return;
}


//------------ List status operations ------------------

// List is empty
template < class DT >
bool List<DT>::isEmpty() const
{
	return (head == NULL);
}

// List is full
template < class DT >
bool List<DT>::isFull() const
{
	ListNode<DT>* location = new ListNode<DT>(NULL, NULL, NULL);
	if (location == NULL) return true;
	else {
		delete location;
		return false;
	}

}


//------------ List manipulation operations ------------------

// Go to beginning
template < class DT >
void List<DT>::gotoBeginning()
{
	//		PRE: NOT EMPTY
	if (isEmpty()) {
		cout << "Failed -- the list is empty" << endl;
		return;
	}

	cursor = head;
	return;
}

// Go to end
template < class DT >
void List<DT>::gotoEnd()
{
	//		PRE: NOT EMPTY
	if (isEmpty()) {
		cout << "Failed -- the list is empty" << endl;
		return;
	}

	while (cursor->next != NULL) {
		cursor = cursor->next;
	}

	return;
}

// Go to next data item
template < class DT >
bool List<DT>::gotoNext()
{
	//		PRE: NOT EMPTY
	if (isEmpty() || cursor->next == NULL)
		return false;

	cursor = cursor->next;
	return true;
}

// Go to prior data item
template < class DT >
bool List<DT>::gotoPrior()
{
	//		PRE: NOT EMPTY
	if (isEmpty() || cursor == head) return false;

	cursor = cursor->prior;

	return true;
}


template < class DT >
DT List<DT>::getCursor() const
{
	//		PRE: NOT EMPTY
	if (isEmpty()) {
		cout << "Failed -- the list is empty" << endl;
		return NULL;
	}

	return cursor->dataItem;
}


//-----------------------------------------------------------

template < class DT >
void List<DT>::showStructure() const
{
	if (isEmpty()) cout << "EMPTY LIST" << endl;
	else {
		ListNode<DT>* temp = head;
		while (temp != NULL) {
			if (temp == cursor) 	cout << "  [ " << temp->dataItem << " ]";
			else cout << "  " << temp->dataItem;
			temp = temp->next;
		}
	}

	return;
}


//------------ Polynomial ------------------

template < class DT >
void List<DT>::findLocation(int* term, bool& found, int& opt) {
	if (isEmpty()) return;

	bool moreToSearch = true;
	found = false;
	ListNode<int*>* location = head;

	while (moreToSearch && !found) {

		if (location->dataItem[0] > term[0]) {
			if (location->next == NULL)
			{
				moreToSearch = false;
				opt = 1; 
			}
			else location = location->next;
		}
		else if (location->dataItem[0] == term[0]) { 
			location->dataItem[1] += term[1];
			found = true;
		}
		else {
			moreToSearch = false;
			opt = -1; 
		}
		cursor = location;
	}

}

template < class DT >
void List<DT>::showPolynomial() {
	if (isEmpty()) {
		cout << "Empty Polynomial" << endl << endl;
		return;
	}
	ListNode<int*>* temp = head;

	while (temp != NULL) {
		int expo = temp->dataItem[0];
		int coef = temp->dataItem[1];

		if (coef == 0) continue;

		if (temp == head) {
			if (coef < 0) {
				cout << "-";
				coef *= -1;
			}
		}
		else {
			if (coef > 0) cout << " + ";
			else {
				cout << " - ";
				coef *= -1;
			}
		}


		if (expo == 0) {
			if (coef == 1) cout << 1;
			else cout << coef;
		}
		else {
			if (coef == 1) cout << "x^" << expo;
			else cout << coef << "*x^" << expo;
		}

		temp = temp->next;
	}
	cout << endl << endl;
}


template <class DT>
void List<DT>::insertBefore(const DT& newDataItem) {
	if (isEmpty()) {
		insert(newDataItem);
		return;
	}

	ListNode<DT>* newNode = new ListNode<DT>(newDataItem, NULL, NULL);
	newNode->prior = cursor->prior;
	newNode->next = cursor;
	if (cursor->prior == NULL) head = newNode; 
	else cursor->prior->next = newNode;
	cursor->prior = newNode;
	cursor = newNode;

	return;
}