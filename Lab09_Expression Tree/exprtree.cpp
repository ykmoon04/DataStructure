#include "exprtree.h"
#include <iostream>

using namespace std;
//--------------------------------------------------------------------

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
{
	element = elem;
	left = leftPtr;
	right = rightPtr;
}

//--------------------------------------------------------------------

ExprTree::ExprTree()
{
	root = NULL;
}

ExprTree::~ExprTree()
{
	clear();
}

//--------------------------------------------------------------------

void ExprTree::build()
{
	buildSub(root);
}

void ExprTree::buildSub(ExprTreeNode*& p)
{
	char item;
	cin >> item;

	ExprTreeNode* node = new ExprTreeNode(item, NULL,NULL);
	p = node;
	
	if (item == '+' || item == '-' || item == '/' || item == '*') {
		buildSub(p->left);
		buildSub(p->right);
	}

}


//--------------------------------------------------------------------

void ExprTree::expression() const
{
	exprSub(root);
}

void ExprTree::exprSub(ExprTreeNode* p) const
{
	//	infix form

	if (p->left != NULL) {
		cout << "(";
		exprSub(p->left);
		cout << p->element;
		exprSub(p->right);
		cout << ")";
	}
	else
		cout << p->element;
}

//--------------------------------------------------------------------

float ExprTree::evaluate() const
{
	// PRE: Not empty
	if (root == NULL)
		return NULL;
	
	return evaluateSub(root);;
}

float ExprTree::evaluateSub(ExprTreeNode* p) const
{ 
	char data = p->element;

	if(data=='+') {
		return evaluateSub(p->left) + evaluateSub(p->right);
	}
	else if (data == '-') {
		return evaluateSub(p->left) - evaluateSub(p->right);
	}
	else if (data == '*') {
		return evaluateSub(p->left) * evaluateSub(p->right);
	}
	else if (data == '/') {
		float dividend = evaluateSub(p->left);
		float divisor = evaluateSub(p->right);

		if ((int)divisor != 0) return dividend / divisor;
		else return NULL;
	}
	else {
		return (float)(p->element-'0');
	}
}

//--------------------------------------------------------------------

void ExprTree::clear()
{
	clearSub(root);
	root = NULL;
}

void ExprTree::clearSub(ExprTreeNode* p)
{
	if (p != NULL) {
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

//--------------------------------------------------------------------

void ExprTree::showStructure() const
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

void ExprTree::showSub(ExprTreeNode* p, int level) const
{
	int j;

	if (p != 0)
	{
		showSub(p->right, level + 1);
		for (j = 0; j < level; j++)
			cout << "\t";
		cout << " " << p->element;
		if ((p->left != 0) &&
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);
	}
}