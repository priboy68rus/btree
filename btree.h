#ifndef _BTREE
#define _BTREE

#include <iostream>
#include "stdio.h"

#define TMPL template <typename Key>


TMPL class BTree;

TMPL class BTree {
	private:
		class BNode {
		public:
			Key * keys;
			int n;
			BNode ** c, * parent;
			bool isLeaf;
			BNode();
		};
		BNode * root;
		void destroyTree(BNode * n);

	public:
		BTree() { root = NULL; };
		~BTree();
		void printTree(BNode * n);
};


TMPL BTree<Key>::~BTree() {
	destroyTree(root);
}

TMPL void BTree<Key>::destroyTree(BTree<Key>::BNode * n) {
	if (n == NULL) return;
	for (int i = 0; i < n->n; i++) {
		if (n->c[i] != NULL)
			destroyTree(n->c[i]);
	}
	if (n != NULL) delete n;
}



#endif