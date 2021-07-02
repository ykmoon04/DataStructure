#pragma once

#include <string>
#include <vector>
using namespace std;

class TreeNode {
private:
	string name;		
	vector<TreeNode*> children;	

public:
	TreeNode() {};
	TreeNode(string name);
	string getName();

	friend class HierarchyTree;
};

class HierarchyTree {
private:
	TreeNode* root;
	int cnt;

public:
	HierarchyTree();
	~HierarchyTree();

	void hire(string boss, string sub);	  //  insert 
	TreeNode* retrieve(TreeNode* curr, string target);	// find node with name 'target'

	void fire(string name);	//	remove
	TreeNode* superior(string name);  // find superior
	void promoted(TreeNode* target);	// rearrange Tree to fire target 

	void print(); 
	void printSub(TreeNode* curr, int level);

	void clear();
	bool isEmpty();
};
