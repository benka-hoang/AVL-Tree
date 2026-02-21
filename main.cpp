#include<iostream>
#include"AVL.h"

using namespace std;

int main() {
	AVL tree;
	tree.add(5);
	tree.add(15);
	tree.add(20);
	tree.add(4);
	tree.add(7);
	tree.add(9);
	tree.add(1);
	tree.add(8);
	tree.add(13);
	tree.add(6);
	tree.add(2);
	tree.add(18);
	tree.remove(15);
	tree.remove(13);
	tree.remove(2);
	tree.remove(6);
	tree.remove(18);
	tree.display_edge();
	cout << tree.root->height << "\n";
	return 0;
}