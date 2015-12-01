// Red_Black_Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>

struct node
{
	bool color;	//True = red, False = black
	int val;
	node* left;
	node* right;
	node* parent;

	node* addLeaf(int input);

	node* uncle();
	node* grandparent();

	void rotateLeft();
	void rotateRight();

	void rebalance();

	node(int value)
	{
		val = value;
		left = NULL;
		right = NULL;
		parent = NULL;
		color = true; //Starts red
	}
};

void drawTree(node* currNode, int indent, node* root);

int indentWidth = 0;
HANDLE hConsole;

int main()
{
	srand(time(NULL));
	system("Color F0");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 240);
	node* root = NULL;
	while (1)
	{
		using namespace std;
		int input = 0;
		
		cout << "Input value: ";
		while (!(cin >> input)) {
			cin.clear();
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input.  Try again: ";
		}
		
			int digits = 0;
			int inputCopy = input;
			if (inputCopy <= 0)
			{
				inputCopy *= -1;
				digits++;
			}
			while (inputCopy) {
				inputCopy /= 10;
				digits++;
			}
			if (digits > indentWidth)
				indentWidth = digits;
			if (root == NULL)
			{
				root = new node(input);
				root->rebalance();
			}
			else {
				node* newNode = root->addLeaf(input);
				newNode->rebalance();
				while (root->parent != NULL)
				{
					root = root->parent;
				}
			}
			root->color = false;
			printf("\n");
			drawTree(root, 0, root);
			printf("\n");

			/*for (int i = 0; i < 255; ++i)
			{
				SetConsoleTextAttribute(hConsole, i);
				std::cout << i << std::endl;
			}*/
	}
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
	if (this->parent != NULL)
	{
		return this->parent->parent;
	}
	return NULL;
}

void node::rotateLeft()
{
	if (parent != NULL)
		if (this == parent->left)
			return;
	node* P = parent;
	node* temp = left;
	if (P != NULL)
	{
		if (P->parent != NULL)
		{
			if (P == P->parent->right)
				P->parent->right = this;
			else
				P->parent->left = this;
		}
	}
	if (P != NULL)
		P->right = temp;
	if (temp != NULL)
		temp->parent = P;
	if (P != NULL)
		parent = P->parent;
	if (P != NULL)
		P->parent = this;
	left = P;
}

void node::rotateRight()
{
	if (this == parent->right)
		return;
	node* P = parent;
	node* temp = right;
	if (P->parent != NULL)
	{
		if (P == P->parent->left)
			P->parent->left = this;
		else
			P->parent->right = this;
	}
	if (P != NULL)
		P->left = temp;
	if (temp!=NULL)
		temp->parent = P;
	parent = P->parent;
	if (P!=NULL)
		P->parent = this;
	right = P;
}

void node::rebalance()
{
	node* n = this;
	if (n->parent == NULL)
		n->color = false;
	else {
		if (n->parent->color == true)
		{
			node* u = n->uncle();
			node* g;
			if (u != NULL && u->color == true)
			{
				n->parent->color = false;
				u->color = false;
				g = n->grandparent();
				g->color = true;
				g->rebalance();
			}
			else {
				g = n->grandparent();
				if (n == n->parent->right && n->parent == g->left)
				{
					n->parent->rotateLeft();
					n = n->left;
				}
				else if (n == n->parent->left && n->parent == g->right)
				{
					n->parent->rotateRight();
					n = n->right;
				}
				g = n->grandparent();
				n->parent->color = false;
				g->color = true;
				if (n == n->parent->left)
				{
					g->rotateRight();
				}
				else {
					g->rotateLeft();
				}
			}
		}
	}
}

void drawTree(node* currNode, int indent, node* root)
{
	if (currNode->right != NULL)
	{
		drawTree(currNode->right, indent + 1, root);
	}

	node* nodeWalker = root;

	while (nodeWalker != currNode)
	{
		for (int i = 0; i < indentWidth+2; ++i)
		{
			std::cout << " ";
		}

		if (nodeWalker->left == currNode)
			std::cout << (char)200;	//	?192	?200
		else if (nodeWalker->right == currNode)
			std::cout << (char)201;	//	?218	?201
		else if ((nodeWalker->val > currNode->val && nodeWalker->left->val < currNode->val) ||
			(nodeWalker->val < currNode->val && nodeWalker->right->val > currNode->val))
		{
			std::cout << (char)186;	//	?179	?186
		}
		else
			std::cout << " ";

		if (nodeWalker->val > currNode->val)
			nodeWalker = nodeWalker->left;
		else if (nodeWalker->val < currNode->val)
			nodeWalker = nodeWalker->right;
	}

	
	if (currNode->color)
		SetConsoleTextAttribute(hConsole, 79);
	else
		SetConsoleTextAttribute(hConsole, 15);
	std::cout << "[";
	std::cout << currNode->val;
	std::cout << "]";
	SetConsoleTextAttribute(hConsole, 240);


	int digits = 0;
	int inputCopy = currNode->val;
	if (inputCopy <= 0)
	{
		inputCopy *= -1;
		digits++;
	}
	while (inputCopy) {
		inputCopy /= 10;
		digits++;
	}
	if (currNode->right != NULL || currNode->left != NULL)
	{
		for (int i = digits; i < indentWidth; ++i)
		{
			std::cout << (char)205;	//	?196	?205
		}
	}
	

	if (currNode->right != NULL && currNode->left != NULL)
	{
		std::cout << (char)185;	//	?180	?185
	}
	else if (currNode->right != NULL)
	{
		std::cout << (char)188;	//	?217	?188
	}
	else if (currNode->left != NULL)
	{
		std::cout << (char)187;	//	?191	?187
	}

	std::cout << std::endl;

	if (currNode->left != NULL)
	{
		drawTree(currNode->left, indent + 1, root);
	}
}

node* node::addLeaf(int input)
{
	if (val == input)
	{
		return this;
	}
	if (val < input)
	{
		if (right == NULL)
		{
			right = new node(input);
			right->parent = this;
			return right;
		}
		return right->addLeaf(input);
	}
	if (val > input)
	{
		if (left == NULL)
		{
			left = new node(input);
			left->parent = this;
			return left;
		}
		return left->addLeaf(input);
	}
	return NULL;
}

