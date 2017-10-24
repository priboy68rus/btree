#include "btree.h"
#include <iostream>
#include "stdio.h"

int main() {
	BTree<int> * tree = new BTree<int>();
	delete tree;
	return 0;
}