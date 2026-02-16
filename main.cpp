#include<iostream>
#include"AVL.h"

using namespace std;

int main() {
	AVL tree;
	tree.add(5);
	tree.add(4);
	tree.add(1);
	tree.add(3);
	tree.add(2);
	tree.add(10);
	tree.add(6);
	tree.add(8);
	tree.add(7);
	tree.add(9);
	cout << tree.balance_factor(tree.root) << "\n";
	return 0;
}