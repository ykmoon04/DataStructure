
#include <iostream>
#include <string>
#include <queue>
#include "tree.h"
using namespace std;

TreeNode::TreeNode(string name) {
	this->name = name;
}

string TreeNode::getName() {
	return name;
}

HierarchyTree::HierarchyTree() {
	root = NULL;
	cnt = 0;
}

HierarchyTree::~HierarchyTree() {
	clear();
}

void HierarchyTree::hire(string boss, string sub) {

	if (cnt >= 1000) {
		cout << "Cannot hire more than 1000 people" << endl;
		return;
	}

	TreeNode* employee = new TreeNode(sub);
	
	if (isEmpty()) {
		root = employee;	
	}
	else {
		TreeNode* super = retrieve(root, boss);
		if (super!=NULL) {	
			super->children.push_back(employee);
			cnt++;
		}
		else {
			cout << "employee <" << boss << "> not exist" << endl;
		}
	}
}

TreeNode* HierarchyTree::retrieve(TreeNode* curr,string target) {

	if (curr->getName() == target) {
		return curr;
	}

	int num = curr->children.size();
	for (int i = 0; i < num; i++) {
		TreeNode* found = retrieve(curr->children.at(i), target);
		if (found != NULL) return found;
	}

	return NULL;
}



void HierarchyTree::fire(string name) {
	if (isEmpty()) return;

	TreeNode* target = retrieve(root, name);
	if (target==NULL) {
		cout << "employee <" << name << "> not exist" << endl;
		return;
	}
	
	TreeNode* super = superior(name);  

	if (target->children.size() == 0) {	// the victim had no subordinates
		if (super == NULL) {		// fire CEO
			root = NULL;
		}
		else {
			for (int i = 0; i < super->children.size(); i++) {
				if (super->children[i]->getName() == name) {
					super->children.erase(super->children.begin() + i);
				}
			}
		}
	}
	else {	//	the victim had subordinates
		promoted(target);
		if (super == NULL) {		//	fire CEO
			root = target->children[0];
			return;
		}

		for (int i = 0; i < target->children.size(); i++) {
			super->children.push_back(target->children[i]);
		}

		for (int i = 0; i < super->children.size(); i++) {
			if (super->children[i]->getName() == name) {
				super->children.erase(super->children.begin() + i);
			}
		}
		
	}

	delete target;
}

//	find superior
TreeNode* HierarchyTree::superior(string name) {

	if (root->getName() == name) return NULL;
	queue<TreeNode*> q;
	q.push(root);

	while (!q.empty()) {
		TreeNode* element = q.front();
		q.pop();
		for (int i = 0; i < element->children.size(); i++) {
			if (element->children[i]->getName() == name) return element;
			else q.push(element->children[i]);
		}
	}
}

void HierarchyTree::promoted(TreeNode* target) {
	
	if (target->children.size()!=0)
	{
		promoted(target->children[0]);
	}

	TreeNode* super = superior(target->getName());
	if (super == NULL) {	
		return; 
	}
	else {
		while (super->children.size() != 1) {
			target->children.push_back(super->children[1]);
			super->children.erase(super->children.begin() + 1);
		}
	}
}

void HierarchyTree::print() {
	if (isEmpty()) {
		cout << "No one hired" << endl;
		return;
	}

	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cout << endl;
	printSub(root, 0);
	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cout << endl;
}

void HierarchyTree::printSub(TreeNode* curr, int level) {

	for (int i = 0; i < level; i++) {
		cout << "+";
	}
	cout << curr->getName() << endl;

	for (int i = 0; i < curr->children.size(); i++) {
		printSub(curr->children[i], level+1);
	}
}

bool HierarchyTree::isEmpty() {
	return root == NULL;
}

void HierarchyTree::clear() {
	queue<TreeNode*> q;
	q.push(root);

	while (!q.empty()) {
		TreeNode* element = q.front();
		q.pop();
		for (int i = 0; i < element->children.size(); i++) {
			q.push(element->children[i]);
		}
		delete element;
	}
}