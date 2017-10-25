#ifndef _BTREE
#define _BTREE

#include <iostream>
#include "stdio.h"

#define TMPL template <typename Key>


TMPL class BTree;

TMPL class BTree {
	public:
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
		void printTree(BNode * n);
		void removeRecursive(BNode * n, Key key);
		void removeFromInternal(BNode * n, Key key);
		void removeFindNext(BNode * n, Key key);
		int findKey(BNode * n, Key key);
		int findMax(BNode * n);
		int findMin(BNode * n);

	public:
		BTree(int t) { root = NULL; this->t = t;};
		~BTree();
		void print();
		void insert(Key key);
		void remove(Key key);
};


// ----------------------------------------------
// Construction and Destruction of B-tree
// ----------------------------------------------

TMPL BTree<Key>::~BTree() {
	destroyTree(root);
}

TMPL void BTree<Key>::destroyTree(BTree<Key>::BNode * n) {
	if (n == NULL) return;
	if (!n->isLeaf) {
		for (int i = 0; i < n->n; i++) {
			destroyTree(n->c[i]);
		}
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


// ----------------------------------------------
// Printing tree in ascending order
// ----------------------------------------------

TMPL void BTree<Key>::print() {
	printTree(root);
	std::cout << std::endl;
}

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


// ----------------------------------------------
// Insertion
// ----------------------------------------------

TMPL void BTree<Key>::insert(Key key) {
	if (root == NULL) {
		root = new BNode(t);
		root->keys[0] = key;
		root->n = 1;
		root->isLeaf = true;
	} else if (root->n == 2 * t - 1) {
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
	if (n->c[i]->n != 2 * t - 1) 
		return;
	BNode * m = n->c[i];
	BNode * l = new BNode(t);
	l->isLeaf = m->isLeaf;
	l->n = t - 1;

	for (int j = 0; j < t - 1; j++) {
		l->keys[j] = m->keys[j + t];
	}
	if (!m->isLeaf) {
		for (int j = 0; j < t; j++) {
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
	n->keys[i] = m->keys[t - 1];
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
			if (key > n->keys[i])
				i++;
		}
		insertNonFull(n->c[i], key);
	}
}

// ----------------------------------------------
// Removal
// ----------------------------------------------

TMPL int BTree<Key>::findKey(BNode * n, Key key) {
	int i = 0;
	while (key > n->keys[i] && i < n->n)
		i++;
	return i;
}

TMPL void BTree<Key>::remove(Key key) {
	removeRecursive(root, key);

	BNode * r = root;
	while (r->n == 0) {
		r = r->c[0];
		delete root;
		root = r;
	}
}

TMPL void BTree<Key>::removeRecursive(BNode * n, Key key) {
	if (n == NULL) return;

	int i = findKey(n, key);
	if (n->isLeaf) {
		if (i < n->n && n->keys[i] == key) {
			for (int j = i; j < n->n - 1; j++) {
				n->keys[j] = n->keys[j + 1];
			}
			n->n--;
		} else {
			std::cout << "no key " << key << " in tree" << std::endl;
		}
	} else {
		if (i < n->n && n->keys[i] == key) {
			removeFromInternal(n, key);
		} else {
			removeFindNext(n, key);
		}
	}
}

TMPL void BTree<Key>::removeFromInternal(BNode * n, Key key) {
	int i = findKey(n, key);
	int k = 0;
	BNode * m = n->c[i], * l = n->c[i + 1];
	if (m->n > t - 1) {
		// Case 2.1
		k = findMax(m);
		n->keys[i] = k;
		removeRecursive(m, k);
	} else if (l->n > t - 1) {
		// Case 2.2
		k = findMin(l);
		n->keys[i] = k;
		removeRecursive(l, k);
	} else {
		// Case 2.3
		m->n = 2 * t - 1;
		m->keys[t - 1] = n->keys[i];
		for (int j = 0; j < t - 1; j++) {
			m->keys[t + j] = l->keys[j];
			m->c[t + j] = l->c[j];
		}
		m->c[2 * t] = l->c[t];

		delete l;
		for (int j = i; j < n->n - 1; j++) {
			n->keys[j] = n->keys[j + 1];
			n->c[j + 1] = n->c[j + 2];
		}
		n->n--;
		removeRecursive(m, key);
	}
}

TMPL void BTree<Key>::removeFindNext(BNode * n, Key key) {
	int i = findKey(n, key);
	BNode * r, * l;
	if (n->c[i]->n > t - 1) {
		removeRecursive(n->c[i], key);
	} else {
		if (i < n->n - 2 && n->c[i + 1]->n > t - 1) {
			l = n->c[i];
			r = n->c[i + 1];
			l->keys[l->n] = n->keys[i];
			n->keys[i] = r->keys[0];
			l->c[l->n + 1] = r->c[0];
			r->n--;
			for (int j = 0; j < r->n; j++) {
				r->keys[j] = r->keys[j + 1];
				r->c[j] = r->c[j + 1];
			}
			r->c[r->n] = r->c[r->n] + 1;
			l->n++;
			removeRecursive(l, key);
		} else if (i > 0 && n->c[i - 1]->n > t - 1) {
			r = n->c[i];
			l = n->c[i - 1];
			r->c[r->n + 1] = r->c[r->n];
			for (int j = r->n - 1; j >= 0; j--) {
				r->keys[j + 1] = r->keys[j];
				r->c[j + 1] = r->c[j];
			}
			r->keys[0] = n->keys[i];
			n->keys[i] = l->keys[l->n - 1];
			r->c[0] = l->c[l->n];
			r->n++;
			l->n--;
			removeRecursive(r, key);
		} else {
			if (i > 0) {
				r = n->c[i];
				l = n->c[i - 1];
			} else {
				l = n->c[i];
				r = n->c[i + 1];
			}

			r->n = 2 * t - 1;
			r->keys[t - 1] = n->keys[i];
			for (int j = 0; j < t - 1; j++) {
				r->keys[t + j] = l->keys[j];
				r->c[t + j] = l->c[j];
			}
			r->c[2 * t] = l->c[t];

			delete l;
			for (int j = i; j < n->n - 1; j++) {
				n->keys[j] = n->keys[j + 1];
				n->c[j + 1] = n->c[j + 2];
			}
			n->n--;
			removeRecursive(r, key);
		}
	}
}

TMPL int BTree<Key>::findMax(BNode * n) {
	while (!n->isLeaf) {
		n = n->c[n->n];
	}
	return n->keys[n->n - 1];
}

TMPL int BTree<Key>::findMin(BNode * n) {
	while (!n->isLeaf) {
		n = n->c[0];
	}
	return n->keys[0];
}



#endif