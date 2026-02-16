#pragma once
#include <utility>

using namespace std;

struct Node {
	int value;
	Node *lnode, *rnode;

	Node(const int val = -1);
};

struct AVL {
	Node* root;

	AVL();

	void add_recur(Node *&pNode, int x);
	bool contains_recur(Node* pNode, int x);
	void display_recur(Node* pNode);

	int height(Node *pNode);
	void add(int x);
	bool contains(int x);
	void display_LNR();

	// In developing
	void clear_recur(Node* pNode);
	void clear();

	bool balance_factor(Node* pNode);
};