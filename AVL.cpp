#include "AVL.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <stack>

using namespace std;

Node::Node(const int val)
{
	height = 1;
	value = val;
	lnode = nullptr;
	rnode = nullptr;
}

AVL::AVL()
{
	root = nullptr;
}

int AVL::get_height(Node * pNode){
	if (!pNode) return 0;
	int l = get_height(pNode->lnode);
	int r = get_height(pNode->rnode);
	return 1 + max(l, r);
}

void AVL::add_recur(Node *&pnode, int x)
{
	if (pnode == nullptr) {
		pnode = new Node(x);
		return;
	}
	if (x < pnode->value)
		add_recur(pnode->lnode, x);
	else
		add_recur(pnode->rnode, x);
	update(pnode);
	return;
}

void AVL::add(int x)
{
	add_recur(root, x);
}

void AVL::update_remove(Node *& pnode, Node * plast) {
	if (pnode != plast) {
		update_remove(pnode->rnode, plast);
	}
	update(pnode);
}

void AVL::remove__(Node *& pnode) {
	if (!pnode->lnode && !pnode->rnode) {  // Leaf node
		delete pnode;
		pnode = nullptr;
	}
	else if (!pnode->rnode) {			   // Only has left branch
		Node * pdel = pnode;
		pnode = pnode->lnode;
		delete pdel;
	}
	else if (!pnode->lnode) {			   // Only has right branch
		Node * pdel = pnode;
		pnode = pnode->rnode;
		delete pdel;
	}
	else {								   // Has both left and right branch
		Node * pcur = pnode->lnode;
		Node * ppre = pnode;
		while (pcur->rnode) {
			ppre = pcur;
			pcur = pcur->rnode;
		}
		if (pnode != ppre) {
			pnode->value = pcur->value;
			ppre->rnode = pcur->lnode;
			delete pcur;
			// Update height - balance factor (rotate)
			update_remove(pnode->lnode, ppre);
			update(pnode);
		}
		else {
			pnode->value = pcur->value;
			pnode->lnode = pcur->lnode;
			delete pcur;
			// Update height - balance factor (rotate)
			update(pnode);
		}
	}
}

void AVL::remove_recur(Node *& pnode, int x) {
	if (!pnode) return;
	if (pnode->value == x) {
		remove__(pnode);
		return;
	}
	if (x < pnode->value)
		remove_recur(pnode->lnode, x);
	else
		remove_recur(pnode->rnode, x);
	update(pnode);
}

void AVL::remove(int x) {
	remove_recur(root, x);
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
	root = nullptr;
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

void AVL::traversal(Node* pnode) {
	if (pnode->lnode) {
		cout << pnode->value << " " << pnode->lnode->value << "\n";
		traversal(pnode->lnode);
	}
	if (pnode->rnode) {
		cout << pnode->value << " " << pnode->rnode->value << "\n";
		traversal(pnode->rnode);
	}
}	

void AVL::display_edge(){
	traversal(root);
}

void AVL::update(Node *& pnode) {
	if (balance_factor(pnode)) {
		build_height(pnode);
	}
	else {
		rotate(pnode);
	}
}

bool AVL::balance_factor(Node * pNode){
	assert(pNode != nullptr);
	int l = 0, r = 0;
	if (pNode->lnode != nullptr)
		l = pNode->lnode->height;
	if (pNode->rnode != nullptr)
		r = pNode->rnode->height;
	return (abs(l - r) <= 1);
}

void AVL::build_height(Node * pNode){
	int l = 0, r = 0;
	if (pNode->lnode != nullptr)
		l = pNode->lnode->height;
	if (pNode->rnode != nullptr)
		r = pNode->rnode->height;
	pNode->height = max(l, r) + 1;
}

void AVL::rotate_left(Node *& pnode){
	assert(pnode->rnode != nullptr);
	Node* pcur = pnode;
	pnode = pcur->rnode;
	pcur->rnode = pnode->lnode;
	pnode->lnode = pcur;
	build_height(pcur);
	build_height(pnode);
}

void AVL::rotate_right(Node *& pnode) {
	assert(pnode->lnode != nullptr);
	Node* pcur = pnode;
	pnode = pcur->lnode;
	pcur->lnode = pnode->rnode;
	pnode->rnode = pcur;
	build_height(pcur);
	build_height(pnode);
}

int AVL::case_determine(Node * pnode){
	int l = 0, r = 0;
	if(pnode->lnode)
		l = pnode->lnode->height;
	if(pnode->rnode)
		r = pnode->rnode->height;
	Node* pcur = nullptr;
	if (l > r)
		pcur = pnode->lnode;
	else
		pcur = pnode->rnode;
	int ll = 0, rr = 0;
	if (pcur->lnode)
		ll = pcur->lnode->height;
	if (pcur->rnode)
		rr = pcur->rnode->height;
	if (l > r) {
		if (ll > rr)
			return 1;
		else
			return 3;
	}
	else {
		if (ll < rr)
			return 0;
		else
			return 2;
	}
	return 0;
}

void AVL::rotate(Node *& pnode){
	int t = case_determine(pnode);
	switch (t) {
		case 0:
			rotate_left(pnode);
			break;
		case 1:
			rotate_right(pnode);
			break;
		case 2:
			rotate_right(pnode->rnode);
			rotate_left(pnode);
			break;
		case 3:
			rotate_left(pnode->lnode);
			rotate_right(pnode);
			break;
		default:
			cerr << "This is not good!\n";
			assert(true);
	}
}
