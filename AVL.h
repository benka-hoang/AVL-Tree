#pragma once
#include <utility>

using namespace std;

struct Node {
	int value;
	int height;
	Node *lnode, *rnode;

	Node(const int val = -1);
};

struct AVL {
	Node* root;

	AVL();

	void add_recur(Node *&pnode, int x);
	bool contains_recur(Node* pNode, int x);
	void display_recur(Node* pNode);
	void clear_recur(Node* pNode);
	void traversal(Node* pnode);

	int get_height(Node *pNode);
	void add(int x);
	bool contains(int x);
	void clear();
	void display_LNR();
	void display_edge();

	bool balance_factor(Node* pNode);
	void build_height(Node* pNode);
	void rotate_left(Node*& pnode);
	void rotate_right(Node*& pnode);
	int case_determine(Node* pnode);
	void rotate(Node*& pnode);

};

/* Case determination:
	0 : All in right              : Rotate left for root
	1 : All in left				  : Rotate right for root
	2 : right first, left second  : Rotate right for child, Rotate left for root
	3 : left first, right second  : Rotate left for child, Rotate right for root

*/