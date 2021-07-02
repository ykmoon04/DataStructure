#include "ptyqueue.h"

template <class DT>
PtyQueue<DT>::PtyQueue(int maxNumber):Heap<DT>(maxNumber)
{
}

template<class DT>
void PtyQueue<DT>::enqueue(const DT& newDataItem)
{
	if (this->isFull()) {
		cout << "Failed -- queue is full" << endl;
		return;
	}
	this->insert(newDataItem);
}

template<class DT>
DT PtyQueue<DT>::dequeue()
{
	DT* test = new DT();
	test->setPty(-1);
	if (this->isEmpty()) {
		cout << "Failed -- queue is empty" << endl;
		return *test;
	}
	delete test;
	return this->removeMax();
}
