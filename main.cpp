#include "btree.h"
#include <iostream>
#include "stdio.h"

int main() {
	BTree<int> * tree = new BTree<int>(3);
	int a [] = {1, 3, 7, 10, 11, 13, 14,
		15, 18, 16, 19, 24, 25, 26, 21, 4,
		5, 20, 22, 2, 17, 12, 6};
	int n = sizeof(a)/sizeof(a[0]);

	for (int i = 0; i < n; i++) {
		tree->insert(a[i]);
	}

	int b [] = {6, 13, 7, 4, 2, 16};
	int m = 6;
	for (int i = 0; i < m; i++) {
		tree->remove(b[i]);
	}

	// std::cout << tree->root->c[0]->c[1]->keys[0] << std::endl;

	tree->print();
	delete tree;
	return 0;
}
