//#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

struct tree {
	struct node* root;
	int nodeCount;

	void drawTree(struct node* currNode);
	bool checkTree(node* n);
	struct node* search(std::string input);
	tree();
};

struct node
{
	std::string* val;
	bool isLeaf;
	bool color;	//True = red, False = black
	node* left;
	node* right;
	node* parent;

	void insert(std::string val, tree* Tree);
	
	int nodeHeight();
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

long long int rand64();

HANDLE hConsole;

tree* Tree = new tree();

int alphanumeric_strcmp(std::string* str1, std::string* str2);

int main()
{
	srand(time(NULL));	
	system("Color F0");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 240);
	_COORD coord;
	coord.X = 200;
	coord.Y = 32766;
	SetConsoleScreenBufferSize(hConsole, coord);
	
	while (1)
	{
		std::string input;
		do
		{

			std::cout << "Input: ";
			while (!std::getline(std::cin, input) || input.size() < 3 || input[0] == 0 ||
				(input[0] != 105 && input[0] != 73 //	i / I
					&& input[0] != 100 && input[0] != 68 //	d / D
					&& input[0] != 115 && input[0] != 83 //	s / S
					&& input[1] != 32))				  //	space
			{
				std::cout << "Invalid input. Try again: ";
			}
			if (input[0] == 115 || input[0] == 83) //Search
			{
				input.erase(0, 2);
				node* searchedNode = Tree->search(input);
				if (searchedNode != NULL)
				{
					std::cout << "Tree contains \"" << input << "\"" << std::endl;
				}
				else {
					std::cout << "Tree does not contain \"" << input << "\"" << std::endl;
				}
			}else if (input[0] == 105 || input[0] == 73) //Input
			{
				input.erase(0, 2);
				node* searchedNode = Tree->search(input);
				if (searchedNode != NULL)
				{
					std::cout << "Tree already contains \"" << input << "\"" << std::endl;
				}
				else {
					if (Tree->root->isLeaf == true)
					{
						Tree->root->isLeaf = false;
						Tree->root->val = new std::string(input);
						Tree->root->left = new node(Tree->root);
						Tree->root->right = new node(Tree->root);
						Tree->root->color = false;
					}
					else {
						Tree->root->insert(input, Tree);
					}
				}
			}
			else if (input[0] == 100 || input[0] == 68) //Delete
			{
				input.erase(0, 2);
				node* searchedNode = Tree->search(input);
				if (searchedNode == NULL)
				{
					std::cout << "Tree does not contain \"" << input << "\"" << std::endl;
				}
				else {
					searchedNode->del(Tree);
				}
			}
			Tree->drawTree(Tree->root);
			std::cout << std::endl;
		} while (Tree->checkTree(Tree->root));
		Tree->drawTree(Tree->root);
		std::cout << std::endl;
		while (1);
	}
}

tree::tree()
{
	root = new struct node(NULL);
	nodeCount = 0;
};

node::node(node* p)
{
	isLeaf = true;
	left = NULL;
	right = NULL;
	parent = p;
	color = false;	//Leaf is black.
}

int alphanumeric_strcmp(std::string* str1, std::string* str2)
{
	/*Compares two strings and returns >0 if the first string is larger, <0 if the second string is larger, and 0 if they're equal.
	The returned value equals the string index+1 at which they differ. +1 prevents the index from returning 0 if the first characters differ.
	Unlike strcmp, this interprets sequences of integer characters as whole numbers. For example, strcmp would claim 1234 is smaller than 2, because the first character is smaller.
	This will compare the whole numbers against each other, so it will claim 1234 is larger than 2.*/
	int c1 = 0;
	int c2 = 0;
	while (c1 < (*str1).size() && c2 < (*str2).size())
	{
		int weight1 = (*str1)[c1];
		int weight2 = (*str2)[c2];
		bool s1isNum = false;
		bool s2isNum = false;
		if (weight1 >= 48 && weight1 <= 57 || weight1 == 45)	
		{
			bool negative = false;
			int num = 0;
			if (weight1 == 45)
				negative = true;
			if (weight1 != 45){
				num = weight1 - 48;
				s1isNum = true;
			}
			c1++;
			while (c1 < (*str1).size() && ((*str1)[c1] >= 48 && (*str1)[c1] <= 57))
			{
				s1isNum = true;
				num *= 10;
				num += (*str1)[c1] - 48;
				c1++;
			}
			weight1 = negative ? -(num) : num;
		}
		else {
			c1++;
		}
		if (weight2 >= 48 && weight2 <= 57 || weight2 == 45)
		{
			bool negative = false;
			int num = 0;
			if (weight2 == 45)
				negative = true;
			if (weight2 != 45){
				s2isNum = true;
				num = weight2 - 48;
			}
			c2++;
			while (c2 < (*str2).size() && ((*str2)[c2] >= 48 && (*str2)[c2] <= 57))
			{
				s2isNum = true;
				num *= 10;
				num += (*str2)[c2] - 48;
				c2++;
			}
			weight2 = negative ? -(num) : num;
		}
		else {
			c2++;
		}
		if (s1isNum && !s2isNum)
		{
			return -c2;
		}
		if (!s1isNum && s2isNum)
		{
			return c1;
		}
		if (weight1 > weight2)
		{
			return c1;
		}
		else if (weight2 > weight1)
		{
			return -c2;
		}
	}
	if (c1 < (*str1).size() && c2 >= (*str2).size())
	{
		return c1;
	}
	else if (c1 >= (*str1).size() && c2 < (*str2).size())
	{
		return -c2;
	}
	return 0;
}

bool tree::checkTree(node* n)
{
	if (n->isLeaf == true)
	{
		if (n->color == true)
		{
			//Node is leaf, but colored red. Tree is not correct.
			printf("BROKEN TREE! Leaf is RED.\n");
			return false;
		}
		else {
			return true;
		}
	}
	if (n == NULL)
	{
		printf("BROKEN TREE! Not all nodes have instantiated children.\n");
		return false;
	}
	if (n->color == true)
	{
		if (n->parent == NULL)
		{
			//Node is root, but also red. Tree is not correct.
			printf("BROKEN TREE! Root is RED.\n");
			return false;
		}
		if (n->left->color == true)
		{
			//Node is red, but has red left child. Tree is not correct.
			printf("BROKEN TREE! Node is RED, but has RED left child.\n");
			return false;
		}
		if (n->right->color == true)
		{
			//Node is red, but has red right child. Tree is not correct.
			printf("BROKEN TREE! Node is RED, but has RED right child.\n");
			return false;
		}
		if ((n->right->isLeaf == false && n->left->isLeaf == true) || (n->right->isLeaf == true && n->left->isLeaf == false))
		{
			//Node is red, but has one single leaf child. Tree is not correct.
			printf("BROKEN TREE! Node is RED, but has one single leaf child.\n");
			return false;
		}
	}

	if (n->left->isLeaf == false)
	{
		//if (strcmp(&n->val[0], &n->left->val[0]) <= 0)
		//if (strcmp(&((*n->val)[0]), &((*n->left->val)[0])) <= 0)
		if (alphanumeric_strcmp(n->val,n->left->val) <= 0)
		{
			//Left node is larger than its parent. Tree is not correct.
			printf("BROKEN TREE! Node's left child is larger than its parent.\n");
			return false;
		}
	}
	if (n->right->isLeaf == false)
	{
		//if (strcmp(&n->val[0], &n->right->val[0]) >= 0)
		//if (strcmp(&((*n->val)[0]), &((*n->right->val)[0])) >= 0)
		if (alphanumeric_strcmp(n->val,n->right->val) >= 0)
		{
			//Right node is smaller than its parent. Tree is not correct.
			printf("BROKEN TREE! Node's right child is smaller than its parent.\n");
			return false;
		}
	}

	if (n->nodeHeight() == 0)
	{
		//Tree's black height unbalanced.
		printf("BROKEN TREE! Tree's black height is unbalanced.\n");
		return false;
	}
	if (checkTree(n->left) && checkTree(n->right))
	{
		//Node is correct, and node's two children are also correct.
		return true;
	}
	printf("BROKEN TREE! Unknown error.\n");
	return false;
}

int node::nodeHeight()
{
	node* n = this;
	if (n->isLeaf == true)
		return 1;
	int leftH = n->left->nodeHeight();
	if (leftH == 0)
		return 0;
	int rightH = n->right->nodeHeight();
	if (rightH == 0)
		return 0;
	if (leftH != rightH)
		return 0;
	if (n->color == true)
		return leftH;
	else
		return leftH + 1;
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

long long int rand64()
{
	int64_t rand64;
	int16_t* rand16 = (int16_t*)&rand64;
	*rand16 = rand() | rand() % 2 << 15;
	*(rand16 + 1) = rand() | rand() % 2 << 15;
	*(rand16 + 2) = rand() | rand() % 2 << 15;
	*(rand16 + 3) = rand() | rand() % 2 << 15;
	return rand64;
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

node* tree::search(std::string input) {
	if (root->isLeaf == true)
	{
		return NULL;
	}
	node* nodeWalker = root;
	int cmp = alphanumeric_strcmp(nodeWalker->val, &input);
	while (cmp != 0)
	{
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
			return NULL;
		}
		cmp = alphanumeric_strcmp(nodeWalker->val, &input);
	}
	return nodeWalker;
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

void tree::drawTree(node* currNode)
{
	if (currNode == NULL)
		return;
	if (currNode->isLeaf == true)
		return;
	if (currNode->right->isLeaf == false)
		drawTree(currNode->right);
	node* nodeWalker = root;
	if (currNode->parent == NULL)
		std::cout << (char)205;
	else
		std::cout << " ";
	int blackCount = 0;
	while (nodeWalker != currNode)
	{
		if (nodeWalker->color == false)
			blackCount++;
		//int compare = strcmp(&currNode->val[0], &nodeWalker->val[0]);
		//int compare = strcmp(&((*currNode->val)[0]), &((*nodeWalker->val)[0]));
		int compare = alphanumeric_strcmp(currNode->val, nodeWalker->val);
		if (compare > 0) //Desired node is larger than walker
		{
			//int compareNext = strcmp(&nodeWalker->right->val[0], &currNode->val[0]);
			//int compareNext = strcmp(&((*nodeWalker->right->val)[0]), &((*currNode->val)[0]));
			int compareNext = alphanumeric_strcmp(nodeWalker->right->val, currNode->val);
			if (compareNext > 0)
				std::cout << (char)186 << " ";
			else if (compareNext != 0)
				std::cout << "  ";
			nodeWalker = nodeWalker->right;
		}
		else if (compare < 0) //Desired node is smaller than walker
		{
			//int compareNext = strcmp(&nodeWalker->left->val[0], &currNode->val[0]);
			//int compareNext = strcmp(&((*nodeWalker->left->val)[0]), &((*currNode->val)[0]));
			int compareNext = alphanumeric_strcmp(nodeWalker->left->val, currNode->val);
			if (compareNext < 0)
				std::cout << (char)186 << " ";
			else if (compareNext != 0)
				std::cout << "  ";
			nodeWalker = nodeWalker->left;
		}
		else
			break;
	}
	if (currNode->parent != NULL)
	{
		if (currNode == currNode->parent->left)
			std::cout << (char)200 << (char)205;
		else
			std::cout << (char)201 << (char)205;
	}
	if (currNode->color)
		SetConsoleTextAttribute(hConsole, 79);
	else
		SetConsoleTextAttribute(hConsole, 15);
	std::cout << "[" << *currNode->val << "]";
	SetConsoleTextAttribute(hConsole, 240);

	if (currNode->left->isLeaf == true || currNode->right->isLeaf == true)
	{
		if (currNode->color == false)
			blackCount++;
		//std::cout << "				" << blackCount;
	}
	std::cout << std::endl;

	if (currNode->left->isLeaf == false)
	{
		drawTree(currNode->left);
	}
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
		if (c2->isLeaf == false)
		{
			printf("ERROR!\n");
			while (1);
		}
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
			if (c2->isLeaf == false)
			{
				printf("ERROR!\n");
				while (1);
			}
			delete c2;
			delete m->val;
			delete m;
			return;
		}
		else {
			//m is black and its child is black, deleting m breaks black height.
			if (c2->isLeaf == false)
			{
				printf("ERROR!\n");
				while (1);
			}
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

