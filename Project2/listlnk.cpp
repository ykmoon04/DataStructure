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


    ListNode<DT>* location;
    location = new ListNode<DT>(newData, NULL);

    if (isEmpty()) {
        head = location;
    }
    else {
        location->next = cursor->next;
        cursor->next = location;
    }

    cursor = location;
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
    //Pre : List is not empty.
    if (isEmpty()) {
        cout << "Failed--The list is empty" << endl;
        return;
    }

    ListNode<DT>* temp = cursor;

    if (head == cursor) {
        cursor = cursor->next;
        head = head->next;
        delete temp;
    }
    else {
        ListNode<DT>* pre = head;

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
        ListNode<DT>* temp;
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
    DT item;
    ListNode<DT>* location;
    location = new ListNode<DT>(item, NULL);

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

    ListNode<DT>* temp;
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

    ListNode<DT>* temp;
    temp = head;

    while (temp != NULL) {
        cout << temp->dataItem.getName() << " ";
        temp = temp->next;
    }

    cout << endl;
}

//------------------------------------------------

//in-lab
template<class DT>
void List<DT>::moveToBeginning()
{
    //Pre: The list is not empty
    if (isEmpty()) {
        cout << "Failed -- ";
        return;
    }
    if (cursor == head) return;

    ListNode<DT>* pre = head;
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
    //Pre: The list is not full
    if (isFull()) {
        cout << "Failed -- The list is full" << endl;
        return;
    }

    if (isEmpty()) {
        insert(newElement);
        return;
    }
    ListNode<DT>* tmp = new ListNode<DT>(cursor->dataItem, NULL);

    tmp->next = cursor->next;
    cursor->next = tmp; 
    cursor->dataItem = newElement; 
}

template<class DT>
void List<DT>::setCursor(string name) {
    ListNode<DT>* tmp = head;
    while (tmp != NULL) {
        if (tmp->dataItem.getName() == name) {
            cursor = tmp;
            return;
        }
        tmp = tmp->next;
    }
    cout << name << " is not in the list." << endl;
}

template<class DT>
void List<DT>::printReverse() {
    if (isEmpty()) {
        return;
    }
    
    printSub(head);
}

template<class DT>
void List<DT>::printSub(ListNode<DT>* p) {
    if (p == NULL) return;

    printSub(p->next);
    cout << p->dataItem.getName() << " ";
}