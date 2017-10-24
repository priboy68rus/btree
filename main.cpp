#include "btree.h"
#include <iostream>
#include "stdio.h"

int main() {
	BTree<int> * tree = new BTree<int>(3);
	delete tree;
	return 0;
}