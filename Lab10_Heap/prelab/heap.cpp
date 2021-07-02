//--------------------------------------------------------------------
//
//  Laboratory 13                                             heap.cpp
//
//  Actual implementation of class in the Heap ADT
//--------------------------------------------------------------------

#include "heap.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------------


template<class DT>
Heap<DT>::Heap(int maxNumber)
{
    maxSize = maxNumber;
    dataItems = new DT[maxSize];
    size = 0;
}

template < class DT >
Heap<DT>::~Heap()
{
    delete[] dataItems;
}

//--------------------------------------------------------------------

template < class DT >
void Heap<DT>::insert(const DT& newElement)
{
    // pre: is not full
    if (isFull()) {
        cout << "Failed -- Heap is full";
        return;
    }
    // Insert newElement as the bottom rightmost data item in the heap
    dataItems[size] = newElement;
    size++;

    // moves newElement upward
    int bottom = size-1;
    while (size>1&&bottom!=0) {
        int parent = (bottom - 1) / 2;
        if (dataItems[parent].pty() < dataItems[bottom].pty()) {
            // swap
            DT tmp = dataItems[bottom];
            dataItems[bottom] = dataItems[parent];
            dataItems[parent] = tmp;
            bottom = parent;
        }
        else
            break;
    }

}

template < class DT >
DT Heap<DT>::removeMax()
{
    // pre: is not empty
    if (isEmpty()) {
        cout << "Failed -- Heap is empty";
        DT* test = new DT();
        test->setPty(-1);
        return *test;
    }

    DT item = dataItems[0];

    // replace the root data item with the bottom rightmost data item
    dataItems[0] = dataItems[size - 1];
    size--;
    int root = 0;

    while (true) {
        int left = 2 * root + 2;
        int right = 2 * root + 1;
        // no child
        if (left>=size) {
            break;
        }
        // one child
        else if (right >= size) {
            if (dataItems[left].pty() > dataItems[root].pty()) {
                // swap
                DT tmp = dataItems[left];
                dataItems[left] = dataItems[root];
                dataItems[root] = tmp;
                break;
            }
        }
        // two children
        else {
            int max = dataItems[left].pty() > dataItems[right].pty() ? left : right;
            if (dataItems[max].pty() > dataItems[root].pty()) {
                // swap
                DT tmp = dataItems[max];
                dataItems[max] = dataItems[root];
                dataItems[root] = tmp;
                root = max;
            }
        }
    }
    return item;
}

template < class DT >
void Heap<DT>::clear()
{
    size = 0;
}

//--------------------------------------------------------------------

template < class DT >
bool Heap<DT>::isEmpty() const
{
    return (size == 0);
}

template < class DT >
bool Heap<DT>::isFull() const
{
    return (size == maxSize);
}

//--------------------------------------------------------------------

template < class HD >
void Heap<HD>::showStructure() const

// Outputs the priorities of the data in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if (size == 0)
        cout << "Empty heap" << endl;
    else
    {
        cout << "size = " << size << endl;       // Output array form
        for (j = 0; j < maxSize; j++)
            cout << j << "\t";
        cout << endl;
        for (j = 0; j < size; j++)
            cout << dataItems[j].pty() << "\t";
        cout << endl << endl;
        showSubtree(0, 0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void Heap<DT>::showSubtree(int index, int level) const

// Recursive partner of the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
    int j;   // Loop counter

    if (index < size)
    {
        showSubtree(2 * index + 2, level + 1);        // Output right subtree
        for (j = 0; j < level; j++)        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].pty();   // Output dataItems's pty
        if (2 * index + 2 < size)                // Output "connector"
            cout << "<";
        else if (2 * index + 1 < size)
            cout << "\\";
        cout << endl;
        showSubtree(2 * index + 1, level + 1);        // Output left subtree
    }
}