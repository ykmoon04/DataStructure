

template < class DT >
void swap(DT* keyList, int first, int last);

template < class DT >
void selectionSort(DT keyList[], int numKeys)

// Selection sort routine. Sorts the first numKeys keys in keyList
// into ascending order.

{
    // find the smallest element
    DT min;
    int idx = 0;
    for (int i = 0; i < numKeys-1; i++) {
        min = keyList[i];
        for (int j = numKeys - 1; j > i; j--) {
            if (keyList[j] < min) {
                min = keyList[j];
                idx = j;
            }
        }
        swap(keyList, i, idx);
    }

}

//--------------------------------------------------------------------

template < class DT >
void quickPartition(DT keyList[], int numKeys, int left, int right);

template < class DT >
void quickSort(DT keyList[], int numKeys)

// Quicksort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    quickPartition(keyList, numKeys, 0, numKeys - 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void quickPartition(DT keyList[], int numKeys,
    int left, int right)

    // Recursive partner of the quickSort routine. Partitions the array
    // entries between left and right into two subarrays. One subarray
    // contains the keys that are less than or equal to splitValue, and
    // the other contains the keys that are greater than splitValue.
    // Recursively sorts each of these subarrays.

{
    int pivot = keyList[left];
    int i = right + 1;

    if (left < right) {
        for (int j = right; j >= left + 1; j--) {
            if (keyList[j] > pivot) {
                i--;
                swap(keyList, i, j);
            }
        }
        swap(keyList, i - 1, left);
        pivot = i - 1;
        quickPartition(keyList, numKeys, left, pivot - 1);
        quickPartition(keyList, numKeys, pivot + 1, right);
    }
    
}

//--------------------------------------------------------------------

template < class DT >
void bubbleSort(DT keyList[], int numKeys)
{
    int start = 0;

    for (int i = 0; i < numKeys-1; i++) {
        int cnt = 0;
        for (int j = numKeys-1; j > i; j--) {
            if (keyList[j] < keyList[j - 1]) {
                swap(keyList, j, j - 1);
                cnt++;
            }
        }

        if (cnt == 0) break;
    }

    return;
}

template < class DT >
void swap(DT* keyList, int first, int last) {
    DT temp = keyList[first];
    keyList[first] = keyList[last];
    keyList[last] = temp;
}