#include <iostream>
#include "bstree.h"

using namespace std;

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE& elem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	element = elem;
	left = leftPtr;
	right = rightPtr;
}



template < class TE, class KF >
BSTree<TE, KF>::BSTree()
{
	root = NULL;
}

template < class TE, class KF >
BSTree<TE, KF>::~BSTree()
{
	clear();
}

// Insert

template < class TE, class KF >
void BSTree<TE, KF>::insert(const TE& newElement)
{
	if (isFull()) {
		cout << "Tree is full" << endl;
		return;
	}

	insertSub(root, newElement);
}

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement)
{

	if (p==NULL) {
		p = new BSTreeNode<TE, KF>(newElement, NULL, NULL);
	}
	else if (p->element.key() < newElement.key()) {
		insertSub(p->right, newElement);
	}
	else {
		insertSub(p->left, newElement);
	}
}

//--------------------------------------------------------------------

// Retrieve 

template < class TE, class KF >
bool BSTree<TE, KF>::retrieve(KF searchKey, TE& searchElement) const
{
	return retrieveSub(root, searchKey, searchElement);
}

template < class TE, class KF >
bool BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF>* p, KF searchKey, TE& searchElement) const
{

	if (p == NULL) {
		return false;
	}
	else if (p->element.key() == searchKey) {
		searchElement.setKey(searchKey);
		return true;
	}
	else if (p->element.key() > searchKey) {
		return retrieveSub(p->left, searchKey, searchElement);
	}
	else {
		return retrieveSub(p->right, searchKey, searchElement);
	}

}

//--------------------------------------------------------------------

// Remove

template < class TE, class KF >
bool BSTree<TE, KF>::remove(KF deleteKey)
{
	return removeSub(root, deleteKey);
}

template < class TE, class KF >
bool BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF>*& p, KF deleteKey)
{

	 if (p == NULL) {
		return false;
	}
	else	if (p->element.key() == deleteKey) {

		BSTreeNode<TE, KF>* tmp = p;
		if (p->left == NULL) {
			p = p->right;
		}
		else if (p->right == NULL) {
			p = p->left;
		}
		else {
			cutRightmost(p->left, tmp);
			p->element.setKey(tmp->element.key());
		}
		delete tmp;
		return true;
	}
	else if (p->element.key() > deleteKey) {
		return removeSub(p->left, deleteKey);
	}
	else {
		return removeSub(p->right, deleteKey);
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF>*& r, BSTreeNode<TE, KF>*& delPtr)
{
	if (r->right == NULL) {
		delPtr = r;
		r = NULL;
	}
	else {
		cutRightmost(r->right, delPtr);
	}
}

//--------------------------------------------------------------------

// Write Keys

template < class TE, class KF >
void BSTree<TE, KF>::writeKeys() const
{
	writeKeysSub(root);
}

template < class TE, class KF >
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF>* p) const
{
	if (p != NULL) {
		writeKeysSub(p->left);
		cout << p->element.key() << " ";
		writeKeysSub(p->right);
	}
}

//--------------------------------------------------------------------

// Clear

template < class TE, class KF >
void BSTree<TE, KF>::clear()
{
	clearSub(root);
	root = NULL;
}

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF>* p)
{
	if (p != NULL) {
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

//--------------------------------------------------------------------

// Empty / Full

template < class TE, class KF >
bool BSTree<TE, KF>::isEmpty() const
{
	return (root == NULL);
}

template < class TE, class KF >
bool BSTree<TE, KF>::isFull() const
{
	TE test;
	BSTreeNode<TE, KF>* tmp = new BSTreeNode<TE, KF>(test, NULL, NULL);
	if (tmp == NULL) return true;
	else {
		delete tmp;
		return false;
	}
}

//--------------------------------------------------------------------

// Show Structure

template < class TE, class KF >
void BSTree<TE, KF>::showStructure() const

{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF>* p,
	int level) const

{
	int j;   // Loop counter

	if (p != 0)
	{
		showSub(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->element.key();   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);          // Output left subtree
	}
}

// In-lab operations
template <class TE, class KF>
int BSTree<TE, KF>::getHeight() const
{
	//in-lab
	return getHeightSub(root);
}

template <class TE, class KF>
int BSTree<TE, KF>::getHeightSub(BSTreeNode<TE, KF>* p) const
{
	//in-lab
	if (p == NULL) return 0;

	int leftSub = getHeightSub(p->left);
	int rightSub = getHeightSub(p->right);
	return (leftSub > rightSub ? leftSub : rightSub) + 1;
}
