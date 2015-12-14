// Red_Black_Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

struct node
{
	bool isLeaf;
	bool color;	//True = red, False = black
	std::string* val;
	node* left;
	node* right;
	node* parent;

	void insert(std::string val);
	

	node* uncle();
	node* grandparent();
	node* successor();
	node* sibling();

	void leftRotate();
	void rightRotate();
	void rebalance();
	void del();

	node(node* p)
	{
		val = new std::string();
		isLeaf = true;
		left = NULL;
		right = NULL;
		parent = p;
		color = false;	//Leaf is black.
	}
	~node()
	{
		delete val;
	}
};

void drawTree(node* currNode, node* root);

int childCount(node* currNode);

long long int rand64();

bool checkTree(node* n);

int nodeHeight(node* n);

void delete_case1(node* n);
void delete_case2(node* n);
void delete_case3(node* n);
void delete_case4(node* n);
void delete_case5(node* n);
void delete_case6(node* n);

HANDLE hConsole;

node* root = new node(NULL);

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
		clock_t begin_time = clock();
		using namespace std;
		/*
		cout << "Input file name: ";

		string fileName = "";
		while (!std::getline(cin, fileName) || fileName[0] == 0)
		{
			cout << "Invalid filename. Try again: ";
		}
		
		ifstream file(fileName);
		*/
		/*
		ifstream file("C:\\wordsEn.txt");
		if (!file.is_open()) {
			cout << "File not opened!" << endl;
			while (1);
		}
		//int lineCount = std::count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(), '\n') + 1;
		std::string input;
		std::vector<string> words;
		int nodeCount = 0;
		
		while (std::getline(file, input))
		{
			words.push_back(input);
		}
		

		random_shuffle(words.begin(), words.end());

		for (unsigned int i = 0; i < words.size() && i < 32766; ++i)
		{
			
			input = words.at(i);
			if (root == NULL)
			{
				root = new node(input);
				root->color = false;
			}
			else {
				node* newNode = root->insert(input);
			}
			nodeCount++;
			
		}
		*/
		/*
		string input;
		while (!std::getline(cin, input) || input[0] == 0)
		{
			cout << "Invalid filename. Try again: ";
		}
		//input = to_string(rand());
		
		while (checkTree(root))
		{
			string input = " ";
			if (root!=NULL && root->color == false && rand() % 10 == 1)
			{
				input = root->val;
				printf("					REMOVED ROOT\n");
			}else
				input[0] = (char)((int)(rand() % 26 + 65));
			if (root == NULL)
			{
				root = new node(input);
				root->color = false;
			}
			else {
				node* newNode = root->insert(input);
			}
			cout << input << endl;
			drawTree(root, root);
		}
		*/

		//while (1);
		//cout << childCount(root);

		/*
		string input;
		cout << "Input key (i/d/s) and string: ";
		while (!std::getline(cin, input) || input[0] == 0)
		{
			cout << "Invalid input. Try again: ";
		}
		if (root->isLeaf == true)
		{
			root = new node(NULL);
			root->isLeaf = false;
			root->val = input;
			root->left = new node(root);
			root->right = new node(root);
			root->color = false;
		}
		else {
			node* newNode = root->insert(input);
		}			

		drawTree(root, root);
		cout << endl;

		checkTree(root);
		*/
		int test = 1;
		bool increase = true;
		string input;
		do
		{
			
			/*
			cout << "Input string: ";
			while (!std::getline(cin, input) || input[0] == 0)
			{
				cout << "Invalid input. Try again: ";
			}
			cout << endl << input << endl;
			*/
			input = to_string(test);
			if (increase)
				test++;
			else
				test--;
			if (test == 1000)
			{
				drawTree(root, root);
				std::cout << endl;
				increase = !increase;
			}
			if (test == 0)
			{
				drawTree(root, root);
				std::cout << endl;
				increase = !increase;
			}
			if (root->isLeaf == true)
			{
				root = new node(NULL);
				root->isLeaf = false;
				root->val = new string(input);
				root->left = new node(root);
				root->right = new node(root);
				root->color = false;
			}
			else {
				root->insert(input);
			}
			//drawTree(root, root);
			//cout << endl;
		} while (checkTree(root));
		drawTree(root, root);
		std::cout << endl;
		while (1);
		//cout << float(clock() - begin_time)/1000;
		//while (1);

		//string input = "";
		/*
		
		cout << "Input value: ";

		while (!std::getline(cin, input) || input[0] == 0)
		{
			cout << "Invalid input. Try again: ";
		}

		*/
	}
}

bool checkTree(node* n)
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
		if (strcmp(&((*n->val)[0]), &((*n->left->val)[0])) <= 0)
		{
			//Left node is larger than its parent. Tree is not correct.
			printf("BROKEN TREE! Node's left child is larger than its parent.\n");
			return false;
		}
	}
	if (n->right->isLeaf == false)
	{
		//if (strcmp(&n->val[0], &n->right->val[0]) >= 0)
		if (strcmp(&((*n->val)[0]), &((*n->right->val)[0])) >= 0)
		{
			//Right node is smaller than its parent. Tree is not correct.
			printf("BROKEN TREE! Node's right child is smaller than its parent.\n");
			return false;
		}
	}

	if (nodeHeight(n) == 0)
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

int nodeHeight(node* n)
{
	if (n->isLeaf == true)
		return 1;
	int leftH = nodeHeight(n->left);
	if (leftH == 0)
		return 0;
	int rightH = nodeHeight(n->right);
	if (rightH == 0)
		return 0;
	if (leftH != rightH)
		return 0;
	if (n->color == true)
		return leftH;
	else
		return leftH + 1;
}

int childCount(node* currNode)
{
	if (currNode->isLeaf == true)
		return 0;
	int count = 1;
	if (currNode->left->isLeaf == false)
		count += childCount(currNode->left);
	if (currNode->right->isLeaf == false)
		count += childCount(currNode->right);
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

void node::leftRotate()
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
		root = y;
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

void node::rightRotate()
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
		root = y;
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

void node::rebalance()
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
		g->rebalance();
		return;
	}
	if (n == p->right && p == g->left)
	{
		//Left-Right case
		p->leftRotate();
		n = n->left;
	}
	else if (n == p->left && p == g->right)
	{
		//Right-Left case
		p->rightRotate();
		n = n->right;
	}
	g = n->grandparent();
	p = n->parent;
	p->color = false;
	g->color = true;
	if (n == p->left)
		g->rightRotate();
	else
		g->leftRotate();
}

void drawTree(node* currNode, node* root)
{
	if (currNode == NULL)
		return;
	if (currNode->isLeaf == true)
		return;
	if (currNode->right->isLeaf == false)
		drawTree(currNode->right, root);
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
		int compare = strcmp(&((*currNode->val)[0]), &((*nodeWalker->val)[0]));
		if (compare > 0) //Desired node is larger than walker
		{
			//int compareNext = strcmp(&nodeWalker->right->val[0], &currNode->val[0]);
			int compareNext = strcmp(&((*nodeWalker->right->val)[0]), &((*currNode->val)[0]));
			if (compareNext > 0)
				std::cout << (char)186 << " ";
			else if (compareNext != 0)
				std::cout << "  ";
			nodeWalker = nodeWalker->right;
		}
		else if (compare < 0) //Desired node is smaller than walker
		{
			//int compareNext = strcmp(&nodeWalker->left->val[0], &currNode->val[0]);
			int compareNext = strcmp(&((*nodeWalker->left->val)[0]), &((*currNode->val)[0]));
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
		drawTree(currNode->left, root);
	}
}

void node::insert(std::string input)
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
		this->rebalance();
	}
	//int compare = strcmp(&val[0], &input[0]);
	int compare = strcmp(&((*val)[0]), &((input)[0]));
	if (compare == 0)
	{
		del();
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
			right->rebalance();
			return;
		}
		right->insert(input);
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
			left->rebalance();
			return;
		}
		left->insert(input);
		return;
	}
	return;
}

void node::del()
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
	if (m->right->isLeaf == false)
		c = m->right;
	delete n->val;
	n->val = new std::string(*m->val);
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
		delete m;
		return;
	}
	else {
		//m is black.
		if (c->color == true)
		{
			//If m is black and its child is red, changing its child to black preserves black height.
			c->color = false;
			delete m;
			return;
		}
		else {
			//m is black and its child is black, deleting m breaks black height.
			delete m;
			delete_case1(c);
		}
	}
}

void delete_case1(node* n)
{
	if (n->parent == NULL)
	{
		//The child becomes the new root.
		root = n;
		return;
	}
	delete_case2(n);
}

void delete_case2(node* n)
{
	node* s = n->sibling(); //n must have a sibling, because it is black.
	if (s->color == true)
	{
		//n is black, but its sibling is red. 
		//Make their parent red, and the sibling black, then rotate the parent.
		n->parent->color = true;
		s->color = false;
		if (n == n->parent->left)
		{
			n->parent->leftRotate();
		}
		else {
			n->parent->rightRotate();
		}
	}
	delete_case3(n);
}

void delete_case3(node* n)
{
	node* s = n->sibling();
	if (n->parent->color == false && s->color == false && s->left->color == false && s->right->color == false)
	{
		//P, S, and S's children are all black.
		//Color S red, to reduce S's black height by 1. As long as its children are both black, it will not break the tree.
		s->color = true;
		//The black height of the parent is now changed, so delete_case1 needs to be called on it.
		delete_case1(n->parent);
	}
	else {
		delete_case4(n);
	}
}

void delete_case4(node* n)
{
	node* s = n->sibling();
	if (n->parent->color == true && s->color == false && s->left->color == false && s->right->color == false)
	{
		//S and its children are black, and S's parent, P, is red. Making P black and S red does not affect S's black height, but increases N's black height by 1.
		s->color = true;
		n->parent->color = false;
	}
	else {
		delete_case5(n);
	}
}

void delete_case5(node* n)
{
	node* s = n->sibling();
	if (s->color == false)
	{
		if (n == n->parent->left && s->right->color == false && s->left->color == true)
		{
			s->color = true;
			s->left->color = false;
			s->rightRotate();
		}
		else if (n == n->parent->right && s->left->color == false && s->right->color == true)
		{
			s->color = true;
			s->right->color = false;
			s->leftRotate();
		}
	}
	delete_case6(n);
}

void delete_case6(node* n)
{
	node* s = n->sibling();
	s->color = n->parent->color;
	n->parent->color = false;
	if (n == n->parent->left)
	{
		s->right->color = false;
		n->parent->leftRotate();
	}
	else {
		s->left->color = false;
		n->parent->rightRotate();
	}
}

