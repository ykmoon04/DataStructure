
#include <iostream>
#include "listrec.h"

using namespace std;

//--------------------------------------------------------------------
//
// Insert your singly linked list implementations (from Laboratory 7)
// of the following functions:
//
//   - The ListNode class constructor
//
//   - The List class constructor, destructor, insert(), clear(), and
//     showstructure() functions. You may also need to add empty()
//     full(), and others.
//
//--------------------------------------------------------------------

template < class DT >
ListNode<DT>::ListNode(const DT& initData, ListNode* nextPtr) {
    dataItem = initData;
    next = nextPtr;
}

template < class DT >
List<DT>::List(int ignored) {
    head = NULL;
    cursor = NULL;
}

template < class DT >
List<DT>::~List() {
    clear();
}

template < class DT >
void List<DT>::insert(const DT& newData) {

    ListNode<char>* location;
    location = new ListNode<char>(newData, NULL);

    if (head == NULL) {
        head = location;
    }

    else if (cursor->next != NULL) {
        location->next = cursor->next;
        cursor->next = location;
    }
    else {
        cursor->next = location;
    }

    cursor = location;
}

template < class DT >
void List<DT>::clear() {
    cursor = NULL;

    while (head != NULL) {
        ListNode<char>* temp;
        temp = head;
        head = head->next;
        delete temp;
    }
}

template < class DT >
void List<DT>::showStructure() const {
    if (head == NULL) {
        cout << "The list is empty" << endl;
    }

    ListNode<char>* temp;
    temp = head;

    while (temp != NULL) {
        if (temp == cursor)
            cout << "[" << temp->dataItem << "]";
        else
            cout << temp->dataItem;
        temp = temp->next;
    }

    cout << endl;
}



//--------------------------------------------------------------------
//
// Recursively implemented linked list functions used in the Prelab
// Exercise
//
//--------------------------------------------------------------------

template < class DT >
void List<DT>::write() const

// Outputs the data in a list from beginning to end. Assumes that
// objects of type DT can be output to the cout stream.

{
    cout << "List : ";
    writeSub(head);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::writeSub(ListNode<DT>* p) const

// Recursive partner of the write() function. Processes the sublist
// that begins with the node pointed to by p.

{
    if (p != 0)
    {
        cout << p->dataItem;      // Output data
        writeSub(p->next);    // Continue with next node
    }

}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::insertEnd(const DT& newDataItem)

// Inserts newDataItem at the end of a list. Moves the cursor to
// newDataItem.

{
    insertEndSub(head, newDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::insertEndSub(ListNode<DT>*& p,
    const DT& newDataItem)

    // Recursive partner of the insertEnd() function. Processes the
    // sublist that begins with the node pointed to by p.

{
    if (p != 0)
        insertEndSub(p->next, newDataItem);    // Continue searching for
    else                                     // end of list
    {
        p = new ListNode<DT>(newDataItem, 0);  // Insert new node
        cursor = p;                           // Move cursor
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::writeMirror() const

// Outputs the data in a list from beginning to end and back
// again. Assumes that objects of type DT can be output to the cout
// stream.

{
    cout << "Mirror : ";
    writeMirrorSub(head);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::writeMirrorSub(ListNode<DT>* p) const

// Recursive partner of the writeMirror() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if (p != 0)
    {
        cout << p->dataItem;           // Output data (forward)
        writeMirrorSub(p->next);   // Continue with next node
        cout << p->dataItem;           // Output data (backward)
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::reverse()

// Reverses the order of the data items in a list.

{
    reverseSub(0, head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::reverseSub(ListNode<DT>* p, ListNode<DT>* nextP)

// Recursive partner of the reverse() function. Processes the sublist
// that begins with the node pointed to by nextP.

{
    if (nextP != 0)
    {
        reverseSub(nextP, nextP->next);   // Continue with next node
        nextP->next = p;                 // Reverse link
    }
    else
        head = p;                        // Move head to end of list
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::deleteEnd()

// Deletes the data at the end of a list. Moves the cursor to the
// beginning of the list.

{
    deleteEndSub(head);
    cursor = head;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::deleteEndSub(ListNode<DT>*& p)

// Recursive partner of the deleteEnd() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if (p->next != 0)
        deleteEndSub(p->next);   // Continue looking for the last node
    else
    {
        delete p;                // Delete node
        p = 0;                   // Set p (link or head) to null
    }
}

//--------------------------------------------------------------------

template < class DT >
int List<DT>::getLength() const

// Returns the number of data items in a list.

{
    return getLengthSub(head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
int List<DT>::getLengthSub(ListNode<DT>* p) const

// Recursive partner of the length() function. Processes the sublist
// that begins with the node pointed to by p.

{
    int result;   // Result returned

    if (p == 0)
        result = 0;                            // End of list reached
    else
        result = (getLengthSub(p->next) + 1);   // Number of nodes after
                                               // this one + 1
    return result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template < class DT >
void List<DT>::cRemove()
{
    if (head == NULL) return;
    cRemoveSub(head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template < class DT >
void List<DT>::cRemoveSub(ListNode<DT>*& p)
{
    if (p == NULL) return;
    else cRemoveSub(p->next);

    if (p->dataItem == 'c') {
        ListNode<DT>* temp = p;
        if (p == head)
            head = head->next;
        else if (p->next == NULL) p = NULL;
        else p = p->next;

        delete temp;
        cursor = head;
    }




}