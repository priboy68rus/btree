#include "btree.h"
#include <iostream>
#include "stdio.h"

int main() {
	BTree<int> * tree = new BTree<int>(2);
	int a [] = {1, 2, 3, 4, 5, 6, 7};
	int n = sizeof(a)/sizeof(a[0]);

	for (int i = 0; i < n; i++) {
		tree->insert(a[i]);
	}
	tree->print();
	delete tree;
	return 0;
}