
#include "listlnk.h"
#include <iostream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
    dataItem = nodeData;
    next = nextPtr;
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
    if (isFull()) {
        cout << "Insert failed --The list is full" << endl;
        return;
    }

    ListNode<DT>* newNode = new ListNode<DT>(newData, NULL);
    if (isEmpty()) {
        head = newNode;
    }
    else {
        newNode->next = cursor->next;
        cursor->next = newNode;
    }

    cursor = newNode;
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
    if (isEmpty()) {
        cout << "Remove failed --The list is empty" << endl;
        return;
    }

    ListNode<DT>* temp = cursor;
    cursor = cursor->next;
    if (cursor == NULL) {
        cursor = head;
    }

    if (temp == head) {
        head = head->next;
    }
    else {
        ListNode<DT>* prior = head;
        while (prior->next!=temp)
        {
            prior = prior->next;
        }
        prior->next = temp->next;
    }

    delete temp;
}


//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
    if (isEmpty()) {
        cout << "Replace failed --The list is empty" << endl;
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
        ListNode<DT>* temp = head;
        head = head->next;
        delete temp;
    }
}

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
    return head == NULL;
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
    DT temp;
    ListNode<DT>* location = new ListNode<DT>(temp,NULL);
    if (location == NULL) return true;
    delete location;
    return false;
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoBeginning()
{
    if (isEmpty()) return;

    cursor = head;
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
    if (isEmpty()) return;
    while (cursor->next != NULL) {
        cursor = cursor->next;
    }
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoNext()
{
    if (isEmpty()||cursor->next==NULL) return false;

    cursor = cursor->next;
    return true;
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoPrior()
{
    if (isEmpty() || cursor==head) return false;
    ListNode<DT>* temp = head;
    while(temp->next != cursor) {
        temp = temp->next;
    }
    cursor = temp;
    return true;
}

//------------------------------------------------


template<class DT>
DT List<DT>::getCursor() const
{
    DT temp;
    if (isEmpty()) return temp;

    return cursor->dataItem;
}

template<class DT>
void List<DT>::showStructure() const
{
    if (isEmpty()) {
        cout << "Empty List" << endl;
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