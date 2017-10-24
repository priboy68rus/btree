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
			BNode ** c, * parent;
			bool isLeaf;
			BNode();
		}
	public:
		BTree();
		~BTree();
}



#endif