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
	bool color;	//True = red, False = black
	std::string val;
	node* left;
	node* right;
	node* parent;

	node* insert(std::string val);
	void del();

	node* uncle();
	node* grandparent();
	node* successor();

	void leftRotate();
	void rightRotate();

	void rebalance();

	node(std::string  value)
	{
		val = value;
		left = NULL;
		right = NULL;
		parent = NULL;
		color = true; //Starts red
	}
};

void drawTree(node* currNode, node* root);

void deleteFixUp(node* n, node* p, bool nodeIsLeft);

int childCount(node* currNode);

long long int rand64();

HANDLE hConsole;

node* root;

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
	root = NULL;
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
		ifstream file("C:\\wordsEn.txt");
		if (!file.is_open()) {
			cout << "File not opened!" << endl;
			while (1);
		}
		//int lineCount = std::count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(), '\n') + 1;
		std::string input;
		std::vector<string> words;
		int nodeCount = 0;
		//while (getline(file, input)/*file.seekg(rand()%lineCount)*//* && nodeCount < 32766*/)
		while (std::getline(file, input))
		{
			words.push_back(input);
			/*
			//file >> input;
			if (root == NULL)
			{
				root = new node(input);
				root->color = false;
			}
			else {
				node* newNode = root->insert(input);
			}
			nodeCount++;
			//drawTree(root, root);
			//cout << endl << endl;
			*/
		}

		for (unsigned int i = 0; i < words.size(); ++i)
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

		//cout << childCount(root);
		drawTree(root, root);
		//cout << float(clock() - begin_time)/1000;
		while (1);

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

int childCount(node* currNode)
{
	if (currNode == NULL)
		return 0;
	int count = 1;
	if (currNode->left != NULL)
		count += childCount(currNode->left);
	if (currNode->right != NULL)
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
	if (this->parent != NULL)
	{
		if (grandparent() == NULL)
		{
			return NULL;
		}
		if (this->parent == grandparent()->left)
			return grandparent()->right;
		return grandparent()->left;
	}
	return NULL;
}

node* node::grandparent()
{
	if (this == NULL)
		return NULL;
	if (this->parent != NULL)
	{
		return this->parent->parent;
	}
	return NULL;
}

node* node::successor()
{
	if (right != NULL)
	{
		node* walker = this->right;
		while (walker->left != NULL)
		{
			walker = walker->left;
		}
		return walker;
	}
	node* n = this;
	node* p = n->parent;
	while (p != NULL && n == p->right)
	{
		n = p;
		p = p->parent;
	}
	return p;
}

void node::rebalance()
{
	node* n = this;
	if (n == NULL)
		return;
	node* p = n->parent;
	if (p == NULL)
	{
		n->color = false;
		return;
	}
	node* g = n->grandparent();
	if (g != NULL)
	{
		if (p->color == true)
		{
			node* u = n->uncle();
			if (u != NULL && u->color == true)
			{
				u->color = false;
				p->color = false;
				g->color = true;
				g->rebalance();
			}
			else if (u == NULL || u->color == false)
			{
				//Left-Left Case
				if (n == p->left && p == g->left)
				{
					g->rightRotate();
					p->color = g->color;
					g->color = true;
				}
				//Left-Right Case
				else if (n == p->right && p == g->left)
				{
					p->leftRotate();
					g->rightRotate();
					n->color = g->color;
					g->color = true;
				}
				//Right-Right Case
				else if (n == p->right && p == g->right)
				{
					g->leftRotate();
					p->color = g->color;
					g->color = true;
				}
				//Right-Left Case
				else if (n == p->left && p == g->right)
				{
					p->rightRotate();
					g->leftRotate();
					n->color = g->color;
					g->color = true;
				}
			}
		}
	}
	/*
	if (this == NULL)
		return;
	node* n = this;
	if (n->parent == NULL)
	{
		n->color = false;
		return;
	}
	if (n->parent->color == false)
	{
		n->color = true;
		return;
	}
	node* u = n->uncle();
	if ((u != NULL && u->color == false) || u == NULL)
	{
		node* p = n->parent;
		node* g = n->grandparent();
		node* A;
		node* B;
		node* C;
		if (g != NULL && p == g->left)
		{
			C = g;
			if (n == p->left)
			{
				A = n;
				B = p;
			}
			else {
				A = p;
				B = n;
			}
		}
		else {
			A = g;
			if (n == p->left)
			{
				B = n;
				C = p;
			}
			else {
				C = n;
				B = p;
			}
		}
		B->parent = g->parent;
		if (g->parent != NULL && g == g->parent->left)
			g->parent->left = B;
		else if (g->parent != NULL)
			g->parent->right = B;
		if (B->left != A)
		{
			if (B->left != NULL)
			{
				A->right = B->left;
				A->right->parent = A;
			}
			else {
				A->right = NULL;
			}
		}
		B->left = A;
		A->parent = B;
		if (B->right != C)
		{
			if (B->right != NULL)
			{
				C->left = B->right;
				C->left->parent = C;
			}
			else {
				C->left = NULL;
			}
			B->right = C;
			C->parent = B;
		}
		B->color = false;
		A->color = true;
		C->color = true;
	} else {
		if (u != NULL)
			u->color = false;
		n->parent->color = false;
		if (n->grandparent() != NULL && n->grandparent()->parent != NULL)
		{
			n->grandparent()->color = true;
			if (n->grandparent()->parent != NULL && n->grandparent()->parent->color == true)
			{
				n->grandparent()->rebalance();
			}
		}
	}
	*/
}

void drawTree(node* currNode, node* root)
{
	if (currNode == NULL)
		return;
	if (currNode->right != NULL)
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
		int compare = strcmp(&currNode->val[0], &nodeWalker->val[0]);
		if (compare > 0) //Desired node is larger than walker
		{
			int compareNext = strcmp(&nodeWalker->right->val[0], &currNode->val[0]);
			if (compareNext > 0)
				std::cout << (char)186 << " ";
			else if (compareNext != 0)
				std::cout << "  ";
			nodeWalker = nodeWalker->right;
		}
		else if (compare < 0) //Desired node is smaller than walker
		{
			int compareNext = strcmp(&nodeWalker->left->val[0], &currNode->val[0]);
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
	std::cout << "[" << currNode->val << "]";
	SetConsoleTextAttribute(hConsole, 240);

	if (currNode->left == NULL && currNode->right == NULL)
	{
		if (currNode->color == false)
			blackCount++;
		std::cout << "			" << blackCount;
	}
	std::cout << std::endl;

	if (currNode->left != NULL)
	{
		drawTree(currNode->left, root);
	}
}

node* node::insert(std::string input)
{
	int compare = strcmp(&val[0], &input[0]);
	if (compare == 0)
	{
		//del();
		return this;
	}
	if (compare < 0)
	{
		if (right == NULL)
		{
			right = new node(input);
			right->color = true;
			right->parent = this;
			right->rebalance();
			return right;
		}
		return right->insert(input);
	}
	if (compare > 0)
	{
		if (left == NULL)
		{
			left = new node(input);
			left->color = true;
			left->parent = this;
			left->rebalance();
			return left;
		}
		return left->insert(input);
	}
	return NULL;
}

void node::del()
{
	node* y;
	if (left == NULL || right == NULL)
	{
		y = this;
	}
	else {
		y = successor();
	}
	node* x;
	if (y->left != NULL)
	{
		x = y->left;
	}
	else {
		x = y->right;
	}
	if (x != NULL)
	{
		x->parent = y->parent;
	}
	node* xParent = y->parent;

	bool yIsLeft = false;
	if (y->parent == NULL)
	{
		root = x;
		root->color = false;
		//std::cout << std::endl << "Root is " << x->val << std::endl;
	}
	else if (y == y->parent->left)
	{
		y->parent->left = x;
		yIsLeft = true;
	}
	else {
		y->parent->right = x;
		yIsLeft = false;
	}
	if (y != this)
		this->val = y->val;
	if (y->color == true && x != NULL)
	{
		deleteFixUp(x, xParent, yIsLeft);
	}
}

void deleteFixUp(node* n, node* p, bool nodeIsLeft)
{
	std::cout << std::endl << "Fixup " << n->val << std::endl;
}

