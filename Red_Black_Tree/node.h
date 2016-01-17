#ifndef NODE_H
#define NODE_H

#include "tree.h"

struct node
{
	std::string* val;
	bool isLeaf;
	bool color;
	node* left;
	node* right;
	node* parent;

	void insert(std::string val, tree* Tree);

	int blackHeight();
	int height();
	int depth(tree* Tree);
	int childCount();

	node* uncle();
	node* grandparent();
	node* sibling();

	void leftRotate(tree* Tree);
	void rightRotate(tree* Tree);
	void rebalance(tree* Tree);
	void del(tree* Tree);
	void delete_rebalance(tree* Tree);

	node(node* p);
};
#endif
