#include <iostream>
#include "node.h"
#include "tree.h"
#include "functions.h"

node::node(node* p)
{
	isLeaf = true;
	left = NULL;
	right = NULL;
	parent = p;
	color = false;	//Leaf is black.
}


int node::blackHeight()
{
	node* n = this;
	if (n->isLeaf == true)
		return 1;
	int leftH = n->left->blackHeight();
	if (leftH == 0)
		return 0;
	int rightH = n->right->blackHeight();
	if (rightH == 0)
		return 0;
	if (leftH != rightH)
		return 0;
	if (n->color == true)
		return leftH;
	else
		return leftH + 1;
}

int node::height()
{
	node* n = this;
	if (this->isLeaf == true)
		return 0;
	else {
		int LHeight = n->left->height();
		int RHeight = n->right->height();
		if (LHeight > RHeight)
			return LHeight + 1;
		else
			return RHeight + 1;
	}
}

int node::childCount()
{
	node* n = this;
	if (n->isLeaf == true)
		return 0;
	int count = 1;
	if (n->left->isLeaf == false)
		count += n->left->childCount();
	if (n->right->isLeaf == false)
		count += n->right->childCount();
	return count;
}

void node::leftRotate(tree* Tree)
{
	node* x = this;
	node* y = x->right;
	x->right = y->left;
	if (y->left)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent)
	{
		Tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void node::rightRotate(tree* Tree)
{
	node* x = this;
	node* y = x->left;
	x->left = y->right;
	if (y->right)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent)
	{
		Tree->root = y;
	}
	else if (x == x->parent->right)
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

int node::depth(tree* Tree)
{
	int depth = 0;
	node* nodeWalker = Tree->root;
	int cmp = alphanumeric_strcmp(nodeWalker->val, this->val);
	while (cmp != 0)
	{
		depth++;
		if (cmp < 0)
		{
			nodeWalker = nodeWalker->right;
		}
		else if (cmp > 0)
		{
			nodeWalker = nodeWalker->left;
		}
		if (nodeWalker->isLeaf == true)
		{
			return -1;
		}
		cmp = alphanumeric_strcmp(nodeWalker->val, this->val);
	}
	return depth;
}

node* node::uncle()
{
	if (this->parent == NULL)
	{
		//this is root.
		return NULL;
	}
	return this->parent->sibling();
}

node* node::grandparent()
{
	if (this->parent == NULL)
	{
		//this is root.
		return NULL;
	}
	return this->parent->parent;
}

node* node::sibling()
{
	if (this->parent == NULL)
	{
		//this is root.
		return NULL;
	}
	if (this == this->parent->left)
		return this->parent->right;
	else
		return this->parent->left;
}

void node::rebalance(tree* Tree)
{
	node* n = this;
	node* p = n->parent;
	node* g = n->grandparent();
	node* u = n->uncle();
	if (p == NULL)
	{
		//n is new root, thus is only node in tree.
		n->color = false;
		return;
	}
	if (p->color == false)
	{
		//parent is black, n is red. Black height is unaffected.
		return;
	}
	if (u != NULL && u->color == true)
	{
		//Both parent and uncle are red. Make them black and grandparent red, then balance grandparent.
		p->color = false;
		u->color = false;
		g->color = true;
		g->rebalance(Tree);
		return;
	}
	if (n == p->right && p == g->left)
	{
		//Left-Right case
		p->leftRotate(Tree);
		n = n->left;
	}
	else if (n == p->left && p == g->right)
	{
		//Right-Left case
		p->rightRotate(Tree);
		n = n->right;
	}
	g = n->grandparent();
	p = n->parent;
	p->color = false;
	g->color = true;
	if (n == p->left)
		g->rightRotate(Tree);
	else
		g->leftRotate(Tree);
}

void node::insert(std::string input, tree* Tree)
{
	if (this->isLeaf == true)
	{
		this->isLeaf = false;
		this->val = new std::string(input);
		if (this->left == NULL)
			this->left = new node(this);
		if (this->right == NULL)
			this->right = new node(this);
		this->color = true;
		this->rebalance(Tree);
	}
	//int compare = strcmp(&val[0], &input[0]);
	//int compare = strcmp(&((*val)[0]), &((input)[0]));
	int compare = alphanumeric_strcmp(val, &input);
	if (compare == 0)
	{
		return;
	}
	if (compare < 0)
	{
		if (right->isLeaf == true)
		{
			right->isLeaf = false;
			right->val = new std::string(input);
			if (right->left == NULL)
				right->left = new node(right);
			if (right->right == NULL)
				right->right = new node(right);
			right->color = true;
			right->rebalance(Tree);
			return;
		}
		right->insert(input, Tree);
		return;
	}
	if (compare > 0)
	{
		if (left->isLeaf == true)
		{
			left->isLeaf = false;
			left->val = new std::string(input);
			if (left->left == NULL)
				left->left = new node(left);
			if (left->right == NULL)
				left->right = new node(left);
			left->color = true;
			left->rebalance(Tree);
			return;
		}
		left->insert(input, Tree);
		return;
	}
	return;
}

void node::del(tree* Tree)
{
	if (this == NULL)
		return;
	node* n = this;
	node* m = this;
	if (n->left->isLeaf == false)
	{
		m = n->left;
		while (m->right->isLeaf == false)
			m = m->right;
	}
	else if (n->right->isLeaf == false)
	{
		m = n->right;
		while (m->left->isLeaf == false)
			m = m->left;
	}
	node* c = m->left;
	node* c2 = m->right;
	if (m->left->isLeaf == true)
	{
		c = m->right;
		c2 = m->left;
	}
	if (n != m)
	{
		delete n->val;
		n->val = new std::string(*m->val);
	}
	//Delete m:
	if (m->parent != NULL)
	{
		if (m == m->parent->left)
		{
			m->parent->left = c;
		}
		else {
			m->parent->right = c;
		}
		c->parent = m->parent;
	}
	else {
		c->parent = NULL;
	}
	if (m->color == true)
	{
		//If  m is red, replacing it with its child (black by definition) will not affect black height.
		delete c2;
		delete m->val;
		delete m;
		return;
	}
	else {
		//m is black.
		if (c->color == true)
		{
			//If m is black and its child is red, changing its child to black preserves black height.
			c->color = false;
			delete c2;
			delete m->val;
			delete m;
			return;
		}
		else {
			//m is black and its child is black, deleting m breaks black height.
			if (c2->isLeaf == false)
				delete c2;
			delete m->val;
			delete m;
			c->delete_rebalance(Tree);
		}
	}
}

void node::delete_rebalance(tree* Tree)
{
	node* n = this;
	if (n->parent == NULL)
	{
		//The child becomes the new root.
		Tree->root = n;
		return;
	}
	node* s = n->sibling(); //n must have a sibling, because it is black.
	if (s->color == true)
	{
		//n is black, but its sibling is red. 
		//Make their parent red, and the sibling black, then rotate the parent.
		n->parent->color = true;
		s->color = false;
		if (n == n->parent->left)
		{
			n->parent->leftRotate(Tree);
		}
		else {
			n->parent->rightRotate(Tree);
		}
	}
	s = n->sibling();
	if (n->parent->color == false && s->color == false && s->left->color == false && s->right->color == false)
	{
		//P, S, and S's children are all black.
		//Color S red, to reduce S's black height by 1. As long as its children are both black, it will not break the tree.
		s->color = true;
		//The black height of the parent is now changed, so delete_case1 needs to be called on it.
		n->parent->delete_rebalance(Tree);
	}
	else {
		s = n->sibling();
		if (n->parent->color == true && s->color == false && s->left->color == false && s->right->color == false)
		{
			//S and its children are black, and S's parent, P, is red. Making P black and S red does not affect S's black height, but increases N's black height by 1.
			s->color = true;
			n->parent->color = false;
		}
		else {
			s = n->sibling();
			if (s->color == false)
			{
				if (n == n->parent->left && s->right->color == false && s->left->color == true)
				{
					s->color = true;
					s->left->color = false;
					s->rightRotate(Tree);
				}
				else if (n == n->parent->right && s->left->color == false && s->right->color == true)
				{
					s->color = true;
					s->right->color = false;
					s->leftRotate(Tree);
				}
			}
			s = n->sibling();
			s->color = n->parent->color;
			n->parent->color = false;
			if (n == n->parent->left)
			{
				s->right->color = false;
				n->parent->leftRotate(Tree);
			}
			else {
				s->left->color = false;
				n->parent->rightRotate(Tree);
			}
		}
	}
}