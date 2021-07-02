#include <iostream>
#include "queueArr.h"

using namespace std;

template<class DT>
Queue<DT>::Queue(int maxNumber) {
	maxSize = maxNumber;
	front = 0;
	rear = 0;
	element = new DT[maxSize + 1];
}


template<class DT>
Queue<DT>::~Queue() {
	delete[] element;
}

template<class DT>
void Queue<DT>::enqueue(const DT& newData) {
	//PRE : not full
	if (isFull()) {
		cout << "Failed -- Queue is full" << endl;
		return;
	}

	rear = (rear + 1) % (maxSize + 1);
	element[rear] = newData;
}

template<class DT>
DT Queue<DT>::dequeue() {
	//PRE: not empty
	if (isEmpty()) {
		cout << "Failed -- Queue is empty." << endl;
		return NULL;
	}

	front = (front + 1) % (maxSize + 1);
	DT item = element[front];
	element[front] = NULL;
	return item;
}

template<class DT>
void Queue<DT>::clear() {
	front = 0;
	rear = 0;

	for (int i = 0; i < maxSize + 1; i++) {
		element[i] = NULL;
	}
}

template<class DT>
bool Queue<DT>::isEmpty() const {
	if (front == rear) return true;
	else return false;
}

template<class DT>
bool Queue<DT>::isFull() const {
	if ((rear + 1) % (maxSize + 1) == front) return true;
	else return false;
}

template<class DT>
void Queue<DT>::showStructure() const {
	int temp = (front + 1) % (maxSize + 1);
	cout << "front = " << front << " rear = " << rear << endl;

	for (int i = 0; i < maxSize + 1; i++) {
		cout << i << "\t";
	}
	cout << endl;

	for (int i = 0; i < maxSize + 1; i++) {
		if (i == front)
			cout << "*\t"; 
		else if (element[i] == NULL)
			cout << " \t"; 
		else
			cout << element[i] << "\t";
	}

	cout << endl;
}

//--------------------------------------------------------

//	In-Lab 2
template<class DT>
void Queue<DT>::putFront(const DT& newDataItem) {
	//PRE: not full
	if (isFull()) {
		cout << "Failed -- Queue is full" << endl;
		return;
	}

	front = front == 0 ? maxSize : front - 1;
	element[(front + 1)%(maxSize+1)] = newDataItem;
}

template<class DT>
DT Queue<DT>::getRear() {
	//PRE: not empty
	if (isEmpty()) {
		cout << "Failed -- Queue is empty" << endl;
		return NULL;
	}
	DT item = element[rear];
	element[rear] = NULL;
	rear = rear == 0 ? maxSize : rear - 1;

	return item;
}

//--------------------------------------------------------

//	In-Lab 3
template<class DT>
int Queue<DT>::getLength() const
{
	int len;
	if (front > rear) return maxSize + 1 - (front - rear);
	else return rear - front;
}