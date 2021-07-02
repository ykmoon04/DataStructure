#include "stackarr.h"
#include <iostream>

//--------------------------------------------------------------------

template <class DT>
Stack<DT>::Stack(int maxNumber)
{
	maxSize = maxNumber;
	top = maxSize;

	element = new DT[maxSize];
}

//--------------------------------------------------------------------

template <class DT>
Stack<DT>:: ~Stack()
{
	delete[] element;
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::push(const DT& newElement)
{
	if (isFull()) {
		cout << "Stack is full" << endl;
		return;
	}

	element[--top] = newElement;

	return;
}

//--------------------------------------------------------------------

template <class DT>
DT Stack<DT>::pop()
{
	if (isEmpty()) {
		cout << "Stack is empty" << endl;
		return NULL;
	}

	return element[top++];
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::clear()
{
	top = maxSize;

	return;
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isEmpty() const
{
	return (top == maxSize);
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isFull() const
{
	return (top == 0);
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::showStructure() const
{

	for (int i = 0; i < maxSize; i++) {
		cout << "|| ";
		if (i < top) cout << "Empty ";
		else cout << element[i] << " ";
	}

	cout << "||" << endl;

	return;
}