#include <iostream>
#include "queueLnk.h"

using namespace std;

template <class DT>
QueueNode<DT>::QueueNode(const DT& nodeData, QueueNode* nextPtr) {
	dataItem = nodeData;
	next = nextPtr;
}


template< class DT>
Queue<DT>::Queue(int ignored) {
	front = NULL;
	rear = NULL;
}

template< class DT>
Queue<DT>::~Queue() {
	clear();
}

template< class DT>
void Queue<DT>::enqueue(const DT& newData) {
	//	Pre: NOT FULL 
	if (isFull()) {
		cout << "Failed -- Queue is full" << endl;
		return;
	}

	QueueNode<DT>* newNode = new QueueNode<DT>(newData, NULL);

	if (isEmpty()) {
		front = newNode; 
		rear = newNode;
	}
	else {
		rear->next = newNode;
		rear = newNode;
	}
	
	return;
}

template< class DT>
DT Queue<DT>::dequeue() {
	//	Pre: NOT EMPTY
	if (isEmpty()) {
		cout << "Failed -- Queue is empty" << endl;
		return NULL;
	}

	DT item = front->dataItem;

	if (front == rear) 	rear = NULL;	
	QueueNode<DT>* temp = front;
	front = front->next;
	delete temp;
	
	return item;
}

template< class DT>
void Queue<DT>::clear() {

	while (front != NULL) {
		QueueNode<DT>* temp = front;
		front = front->next;
		if (front == rear) {
			front = NULL;
			rear = NULL;
		}
		delete temp;
	}
}

template< class DT>
bool Queue<DT>::isEmpty() const {
	return (front == NULL);
}

template< class DT>
bool Queue<DT>::isFull() const {
	QueueNode<DT>* newNode = new QueueNode<DT>(' ', NULL);
	if (newNode == NULL) return true;
	else {
		delete newNode;
		return false;
	}
}

template< class DT>
void Queue<DT>::showStructure() const {
	if (isEmpty()) {
		cout << "Empty Queue" << endl;
		return;
	}

	QueueNode<DT>* temp = front;
	while (temp != NULL) {
		cout << temp->dataItem << '\t';
		temp = temp->next;
	}
	cout << endl;
	return;
}

template< class DT>
void Queue<DT>::putFront(const DT& newDataItem) {
	//	Pre: NOT FULL 
	if (isFull()) {
		cout << "Failed -- Queue is full" << endl;
		return;
	}

	QueueNode<DT>* newNode = new QueueNode<DT>(newDataItem, front);

	if (isEmpty()) rear = newNode;
	front = newNode;
}

template <class DT>
DT Queue<DT>::getRear() {
	if (isEmpty()) {
		cout << "Failed -- Queue is empty" << endl;
		return NULL;
	}

	DT item = rear->dataItem;
	QueueNode<DT>* temp = rear;

	if (front == rear) {
		front = NULL;
		rear = NULL;
	}
	else {
		QueueNode<DT>* preNode = front;

		while (preNode->next != rear)
			preNode = preNode->next;

		rear = preNode;
		preNode->next = NULL;
	}

	delete temp;

	return item;
}

template <class DT>
int Queue<DT>::getLength() const {
	int len = 0;

	QueueNode<DT>* temp = front;
	
	while (temp != NULL) {
		len++;
		temp = temp->next;
	}

	return len;
}