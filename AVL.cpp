#include "AVL.h"
#include <iostream>
#include <algorithm>

using namespace std;

Node::Node(const int val)
{
	value = val;
	lnode = nullptr;
	rnode = nullptr;
}

AVL::AVL()
{
	root = nullptr;
}

int AVL::height(Node * pNode){
	if (!pNode) return 0;
	int l = height(pNode->lnode);
	int r = height(pNode->rnode);
	return 1 + max(l, r);
}

void AVL::add_recur(Node *&pNode, int x)
{
	if (pNode == nullptr) {
		pNode = new Node(x);
		return;
	}
	if (pNode->value == x)
		return;
	if (x < pNode->value) {
		add_recur(pNode->lnode, x);
	}
	else {
		add_recur(pNode->rnode, x);
	}
	return;
}

void AVL::add(int x)
{
	add_recur(root, x);
	return;
}

bool AVL::contains_recur(Node * pNode, int x)
{
	if (pNode->value == x) return true;
	if (pNode->lnode != nullptr && contains_recur(pNode->lnode, x)) return true;
	if (pNode->rnode != nullptr && contains_recur(pNode->rnode, x)) return true;
	return false;
}

bool AVL::contains(int x)
{
	if (root == nullptr) return false;
	return contains_recur(root, x);
}


void AVL::clear_recur(Node * pNode)
{
	if (pNode->lnode)
		clear_recur(pNode->lnode);
	if (pNode->rnode)
		clear_recur(pNode->rnode);
	delete pNode;
}

void AVL::clear()
{
	clear_recur(root);
}


void AVL::display_recur(Node * pNode)
{
	if (pNode->lnode != nullptr)
		display_recur(pNode->lnode);
	cout << pNode->value << " ";
	if (pNode->rnode != nullptr) 
		display_recur(pNode->rnode);
	return;
}

void AVL::display_LNR()
{
	if (root == nullptr) {
		cout << "Empty AVL!\n";
	}
	else {
		display_recur(root);
	}
}

bool AVL::balance_factor(Node * pNode){
	if (!pNode) return true;
	int l = height(pNode->lnode);
	int r = height(pNode->rnode);
	return abs(l - r) <= 1;
}
