#include "logitree.h"
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

	ExprTreeNode* node = new ExprTreeNode(item, NULL, NULL);
	p = node;

	if (item == '+' || item == '*') {
		buildSub(p->left);
		buildSub(p->right);
	}
	else if (item == '-') {
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
	if (p == NULL) return;

	if (p->right != NULL) {
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

int ExprTree::evaluate() const
{
	if (root == NULL) return -1;

	return evaluateSub(root);;
}

int ExprTree::evaluateSub(ExprTreeNode* p) const
{
	char data = p->element;
	if (data == '+') {
		return (evaluateSub(p->left) == 1 || evaluateSub(p->right) == 1);
	}
	else if (data == '*') {
		return (evaluateSub(p->left) == 1 && evaluateSub(p->right) == 1);
	}
	else if (data == '-') {
		return 1-evaluateSub(p->right);
	}
	else {
		return p->element-'0';
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

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ExprTree::showSub(ExprTreeNode* p, int level) const

// Recursive partner of the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showSub(p->right, level + 1);        // Output right subtree
		for (j = 0; j < level; j++)   // Tab over to level
			cout << "\t";
		cout << " " << p->element;       // Output data item
		if ((p->left != 0) &&          // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);         // Output left subtree
	}
}