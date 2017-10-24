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
			int n; // number of keys
			BNode ** c;
			bool isLeaf;
			BNode(int t);
			~BNode();
		};
		BNode * root;
		int t;
		void destroyTree(BNode * n);
		void insertFullRoot(Key key);
		void insertNonFull(BNode * n, Key key);
		void splitChild(BNode * n, int i);

	public:
		BTree(int t) { root = NULL; this->t = t;};
		~BTree();
		void printTree(BNode * n);
		void insert(Key key);
};


// Construction and Destruction of B-tree

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

TMPL BTree<Key>::BNode::BNode(int t) {
	keys = new int[2 * t - 1];
	c = new BNode * [2 * t]; 
}

TMPL BTree<Key>::BNode::~BNode() {
	delete keys;
	delete c;
}


// Printing tree in ascending order

TMPL void BTree<Key>::printTree(BNode * n) {
	if (n == NULL) return;
	for (int i = 0; i < n->n; i++) {
		if (!n->isLeaf)
			printTree(n->c[i]);
		std::cout << n->keys[i] << " ";
	}
	if (!n->isLeaf)
		printTree(n->c[n->n]);
}



// Insertion

TMPL void BTree<Key>::insert(Key key) {
	if (root->n == 2 * t - 1) {
		insertFullRoot(key);
	} else {
		insertNonFull(root, key);
	}
}

TMPL void BTree<Key>::insertFullRoot(Key key) {
	BNode * s = new BNode(t);
	BNode * r = root;
	root = s;
	s->isLeaf = false;
	s->n = 0;
	s->c[0] = r;
	splitChild(s, 0);
	insertNonFull(s, key);
}

TMPL void BTree<Key>::splitChild(BNode * n, int i) {
	if (n->c[i]->n == 2 * t - 1) 
		return;
	BNode * m = n->c[i];
	BNode * l = new BNode(t);
	l->isLeaf = m->isLeaf;
	l->n = t - 1;

	for (int j = 0; j < t - 1; j++) {
		l->keys[j] = m->keys[j + t];
	}
	if (!m->isLeaf) {
		for (int j = 0; j < t - 1; j++) {
			l->c[j] = m->c[j + t];
		}
	}
	m->n = t - 1;

	for (int j = n->n; j > i; j--) {
		n->c[j + 1] = n->c[j];
	}
	n->c[i + 1] = l;
	for (int j = n->n - 1; j >= i; j--) {
		n->keys[j + 1] = n->keys[j];
	}
	n->keys[i] = l->keys[t];
	n->n++;
}

TMPL void BTree<Key>::insertNonFull(BNode * n, Key key) {
	int i = n->n - 1;
	if (n->isLeaf) {
		while (i >= 0 && key < n->keys[i]) {
			n->keys[i + 1] = n->keys[i];
			i--;
		}
		n->keys[i + 1] = key;
		n->n++;
	} else {
		while (i >= 0 && key < n->keys[i]) {
			i--;
		}
		i++;
		if (n->c[i]->n == 2 * t - 1) {
			splitChild(n, i);
		}
		if (key > n->c[i])
			i++;
		insertNonFull(n->c[i], key);
	}
}


#endif