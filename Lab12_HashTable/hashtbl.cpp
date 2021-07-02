#include <iostream>
#include "hashtbl.h"

template < class DT, class KF >
HashTbl<DT, KF>::HashTbl(int initTableSize)
{
    tableSize = initTableSize;
    dataTable = new List<DT>[tableSize];
}

template < class DT, class KF >
HashTbl<DT, KF>::~HashTbl()
{
    delete[] dataTable;
}

template < class DT, class KF >
void HashTbl<DT, KF>::insert(const DT& newDataItem)
{
    if (isFull()) {
        cout << "Insert failed --The list is full" << endl;
        return;
    }

    int key = newDataItem.hash(newDataItem.getKey()) % tableSize;

    if (!dataTable[key].isEmpty()) { 
        dataTable[key].gotoBeginning();
        do {
            if (dataTable[key].getCursor().getKey() == newDataItem.getKey()) {
                dataTable[key].replace(newDataItem); //update
                return;
            }
        } while (dataTable[key].gotoNext());
    }

    dataTable[key].insert(newDataItem);

}

template < class DT, class KF >
 bool HashTbl<DT, KF>::remove(KF searchKey)
{
    DT test;
    int key = test.hash(searchKey) % tableSize;

    if (!dataTable[key].isEmpty()) {
        dataTable[key].gotoBeginning();
        do {
            if (dataTable[key].getCursor().getKey() == searchKey) {
                dataTable[key].remove();
                return true;
            }
        } while (dataTable[key].gotoNext());
    }

    return false;
}

template < class DT, class KF >
bool HashTbl<DT, KF>::retrieve(KF searchKey, DT& dataItem)
{
    DT test;
    int key = test.hash(searchKey) % tableSize;

    if (!dataTable[key].isEmpty()) {
        dataTable[key].gotoBeginning();
        do {
            if (dataTable[key].getCursor().getKey() == searchKey) {
                dataItem = dataTable[key].getCursor();
                return true;
            }
        } while (dataTable[key].gotoNext());
    }

    return false;
}

template < class DT, class KF >
void HashTbl<DT, KF>::clear()
{
    for (int i = 0; i < tableSize; i++) {
        dataTable[i].clear();
    }
}

template < class DT, class KF >
bool HashTbl<DT, KF>::isEmpty() const
{
    for (int i = 0; i < tableSize; i++) {
        if (!dataTable[i].isEmpty()) return false;
    }

    return true;
}

template < class DT, class KF >
bool HashTbl<DT, KF>::isFull() const
{
    return dataTable[0].isFull();
}

template < class DT, class KF >
void HashTbl<DT, KF>::showStructure() const
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << ": ";
        if (dataTable[i].isEmpty())
            cout << "_";
        else
        {
            dataTable[i].gotoBeginning();
            do
            {
                cout << dataTable[i].getCursor().getKey() << " ";
            } while (dataTable[i].gotoNext());
        }
        cout << endl << endl;
    }
}
