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

	node* addLeaf(int input);

	node(int value)
	{
		val = value;
		left = NULL;
		right = NULL;
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
		}
		else {
			root->addLeaf(input);
		}
		printf("\n");
		/*
		for (int i = 0; i < 255; ++i)
		{
			SetConsoleTextAttribute(hConsole, i);
			std::cout << i << std::endl;
		}
		*/
		drawTree(root, 0, root);
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

	//if (currNode->color)
	//	SetConsoleTextAttribute(hConsole, 192);
	//else
	//	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "[" << currNode->val << "]";
	//SetConsoleTextAttribute(hConsole, 240);

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
			return right;
		}
		return right->addLeaf(input);
	}
	if (val > input)
	{
		if (left == NULL)
		{
			left = new node(input);
			return left;
		}
		return left->addLeaf(input);
	}
	return NULL;
}

