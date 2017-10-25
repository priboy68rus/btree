#include "btree.h"
#include <iostream>
#include "stdio.h"

int main() {
	BTree<int> * tree = new BTree<int>(3);
	int a [] = {1, 2, 3, 4, 5, 6, 7};
	int n = sizeof(a)/sizeof(a[0]);

	for (int i = 0; i < n; i++) {
		tree->insert(a[i]);
	}
	tree->remove(5);
	tree->remove(3);
	tree->remove(4);
	tree->print();
	std::cout << tree->root->keys[0] << std::endl;
	delete tree;
	return 0;
}