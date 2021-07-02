

template < class DT >
void moveDown ( DT dataItem [], int root, int size )

// Restores the binary tree that is rooted at root to a heap by moving
// dataItem[root] downward until the tree satisfies the heap property.
// Parameter size is the number of data items in the array.

{
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    int maxIdx;
    if (left >= size) {
        return;
    }
    else if (right >= size) {
        maxIdx = left;
    }
    else {
        maxIdx = dataItem[left].pty() > dataItem[right].pty() ? left : right;
    }

    if (dataItem[maxIdx].pty() > dataItem[root].pty()) {
        DT tmp;
        tmp = dataItem[maxIdx];
        dataItem[maxIdx] = dataItem[root];
        dataItem[root] = tmp;
        moveDown(dataItem, maxIdx, size);
    }
}

//--------------------------------------------------------------------

template < class DT >
void heapSort ( DT dataItems [], int size )

// Heap sort routine. Sorts the data items in the array in ascending
// order based on priority.

{
    DT temp;   // Temporary storage
    int j;     // Loop counter

    // Build successively larger heaps within the array until the
    // entire array is a heap.

    for ( j = (size-1)/2 ; j >= 0 ; j-- )
        moveDown(dataItems,j,size);

    // Swap the root data item from each successively smaller heap with
    // the last unsorted data item in the array. Restore the heap after
    // each exchange.

    for ( j = size-1 ; j > 0 ; j-- )
    {
        temp = dataItems[j];
        dataItems[j] = dataItems[0];
        dataItems[0] = temp;
        moveDown(dataItems,0,j);
    }
}

