#include "listlnk.h"
#include <iostream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
    dataItem = nodeData;
    nextPtr = NULL;
}


template<class DT>
List<DT>::List(int ignored)
{
    head = NULL;
    cursor = NULL;
}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
    clear();
}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT& newData)
{
    //Pre : List is not full.
    if (isFull()) {
        cout << "Failed--The list is full" << endl;
        return;
    }

    ListNode<char>* location;
    location = new ListNode<char>(newData, NULL);

    if (isEmpty()) {
        head = location;
    }
    else{
        location->next = cursor->next;
        cursor->next = location;
    }

    cursor = location;
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
    if (isEmpty()) {
        cout << "Failed--The list is empty" << endl;
        return;
    }

    ListNode<char>* temp = cursor;

    if (head == cursor) {
        cursor = cursor->next;
        head = head->next;
        delete temp;
    }
    else {
        ListNode<char>* pre = head;

        while (pre->next != cursor)
            pre = pre->next;

        cursor = cursor->next;

        delete temp;
        pre->next = cursor;

        if (cursor == NULL)
            cursor = head;
    }

}


//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
    //Pre : List is not empty.
    if (isEmpty()) {
        cout << "Failed--The list is empty" << endl;
        return;
    }
    cursor->dataItem = newData;
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
    cursor = NULL;

    while (head != NULL) {
        ListNode<char>* temp;
        temp = head;
        head = head->next;
        delete temp;
    }
}

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
    return (head == NULL);
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
    ListNode<char>* location;
    location = new ListNode<char>(' ', NULL);

    if (location == NULL)
        return true;
    else {
        delete location;
        return false;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoBeginning()
{
    //Pre : List is not empty.
    if (isEmpty()) {
        cout << "Failed--The list is empty" << endl;
        return;
    }

    cursor = head;
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
    //Pre : List is not empty.
    if (isEmpty()) {
        cout << "Failed--The list is empty" << endl;
        return;
    }

    while (cursor->next != NULL) {
        cursor = cursor->next;
    }

    return;
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoNext()
{
    //Pre : List is not empty and the cursor is not at the end.
    if (isEmpty() || cursor->next == NULL) {
        return false;
    }

    cursor = cursor->next;
    return true;
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoPrior()
{
    //Pre : List is not empty and the cursor is not at the beginning.
    if (isEmpty() || cursor == head) {
        return false;
    }

    ListNode<char>* temp;
    temp = head;

    while (temp->next != cursor) {
        temp = temp->next;
    }

    cursor = temp;
    return true;
}

//------------------------------------------------


template<class DT>
DT List<DT>::getCursor() const
{
    //Pre : List is not empty.
    if (isEmpty()) {
        cout << "Failed--The list is empty" << endl;
        return NULL;
    }
    return cursor->dataItem;
}

template<class DT>
void List<DT>::showStructure() const
{
    if (isEmpty()) {
        cout << "The list is empty" << endl;
    }

    ListNode<char>* temp;
    temp = head;

    while (temp != NULL) {
        if (temp == cursor)
            cout << "[" << temp->dataItem << "] ";
        else
            cout << temp->dataItem << " ";
        temp = temp->next;
    }

    cout << endl;
}

//------------------------------------------------

//in-lab
template<class DT>
void List<DT>::moveToBeginning()
{
    // in-lab 2
    //Pre: The list is not empty
    if (isEmpty()) {
        cout << "Failed -- ";
        return;
    }
    if (cursor == head) return;


    ListNode<char>* pre = head;
    while (pre->next != cursor) {
        pre = pre->next;
    }

    pre->next = cursor->next; 
    cursor->next = head; 
    head = cursor;
}

template<class DT>
void List<DT>::insertBefore(const DT& newElement)
{
    // in-lab 3
    //Pre: The list is not full
    if (isFull()) {
        cout << "Failed -- The list is full" << endl;
        return;
    }

    if (isEmpty()) {
        insert(newElement);
        return;
    }

    ListNode<char>* tmp = new ListNode<char>(cursor->dataItem, NULL);
   
    tmp->next = cursor->next; 
    cursor->next = tmp; 
    cursor->dataItem = newElement; 
}