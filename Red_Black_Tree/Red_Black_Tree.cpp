// Red_Black_Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>

struct node
{
	bool color;	//True = red, False = black
	long long int val;
	node* left;
	node* right;
	node* parent;

	node* insert(long long int input);
	void del();

	node* uncle();
	node* grandparent();

	void rebalance();

	node(long long int value)
	{
		val = value;
		left = NULL;
		right = NULL;
		parent = NULL;
		color = true; //Starts red
	}
};

void drawTree(node* currNode, int indent, node* root);

long long int rand64();

int indentWidth = 0;
HANDLE hConsole;

int main()
{
	srand(time(NULL));
	long long int max = 0;
	long long int randInt = 0;
	long long int count = 0;
	long long int min = LLONG_MAX;
	do
	{
		randInt = rand64();
		if (abs(randInt) < abs(min))
		{
			printf("%lld\n						Count:%lld\n", abs(randInt), count);
			min = randInt;
		}
		count++;
	}while (randInt < -1000000000 || randInt > 1000000000);
	printf("%lld\n%lld\n", randInt, count);
	while (1);
	
	system("Color F0");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 240);
	node* root = NULL;
	while (1)
	{
		using namespace std;
		long long int input = 0;
		
		/*cout << "Input value: ";
		while (!(cin >> input)) {
			cin.clear();
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input.  Try again: ";
		}*/
		for (int i = 0; i < 1000; ++i)
		{
			input = (long long int)(rand() - RAND_MAX/2) * (long long int)(rand() - RAND_MAX / 2) * (long long int)(rand() - RAND_MAX / 2) * (long long int)(rand() - RAND_MAX / 2) * 10;
			int digits = 0;
			long long int inputCopy = input;
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
				node* newNode = root->insert(input);
				if (newNode != NULL)
				{
					newNode->rebalance();
					while (root->parent != NULL)
					{
						root = root->parent;
					}
				}
			}
		}
			printf("\n");
			drawTree(root, 0, root);
			printf("\n");
			while (1);
			/*for (int i = 0; i < 255; ++i)
			{
				SetConsoleTextAttribute(hConsole, i);
				std::cout << i << std::endl;
			}*/
	}
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

void node::rebalance()
{
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
		if (p == g->left)
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
	long long int inputCopy = currNode->val;
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

node* node::insert(long long int input)
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
		return right->insert(input);
	}
	if (val > input)
	{
		if (left == NULL)
		{
			left = new node(input);
			left->parent = this;
			return left;
		}
		return left->insert(input);
	}
	return NULL;
}

void node::del()
{
	std::cout << "Deleting Node: " << val << std::endl;
	if (parent == NULL)
	{
		delete(this);
		return;
	}
	bool leftChild = false;
	if (this == parent->left)
		leftChild = true;
	if (left == NULL && right == NULL)
	{
		if (leftChild)
		{
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
		delete(this);
		return;
	}
	delete(this);
}

