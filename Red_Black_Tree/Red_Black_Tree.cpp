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
	

	node* uncle();
	node* grandparent();
	node* successor();
	node* sibling();

	void leftRotate();
	void rightRotate();
	void rebalance();
	void del();

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

bool checkTree(node* n);

int nodeHeight(node* n);

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

		string input;
		cout << "Input value: ";
		while (!std::getline(cin, input) || input[0] == 0)
		{
			cout << "Invalid input. Try again: ";
		}
		if (root == NULL)
		{
			root = new node(input);
			root->color = false;
		}
		else {
			node* newNode = root->insert(input);
		}
		drawTree(root, root);
		


		if (checkTree(root) == false)
			printf("BROKEN TREE!\n");
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
	if (n == NULL)
		return true;
	if (n->color == true)
	{
		if (n->parent == false)
		{
			return false;
		}
		if (n->left != NULL && n->left->color == true)
		{
			return false;
		}
		if (n->right != NULL && n->right->color == true)
		{
			return false;
		}
		if ((n->right != NULL && n->left == NULL) || (n->right == NULL && n->left != NULL))
		{
			return false;
		}
	}
	if (nodeHeight(n) == 0)
		return false;
	if (checkTree(n->left) && checkTree(n->right))
		return true;
	return false;
}

int nodeHeight(node* n)
{
	if (n == NULL)
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

node* node::sibling()
{
	if (this == NULL)
		return NULL;
	if (parent == NULL)
		return NULL;
	if (this == parent->left)
		return parent->right;
	else
		return parent->left;
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

	if (currNode->left == NULL || currNode->right == NULL)
	{
		if (currNode->color == false)
			blackCount++;
		//std::cout << "				" << blackCount;
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
		del();
		return NULL;
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

bool isBlack(node* n)
{
	if (n == NULL)
		return true;
	if (n->color == false)
		return true;
	return false;
}

bool delete_case2(node* n)
{
	if (n == NULL)
		return false;
	std::cout << "Deletion Case 2." << std::endl;
	node* s = n->sibling();
	if (s != NULL && s->color == true)
	{
		n->parent->color = true;
		s->color = false;
		if (n == n->parent->left)
			n->parent->leftRotate();
		else
			n->parent->rightRotate();
	}
}

bool delete_case1(node* n)
{
	if (n == NULL)
		return false;
	std::cout << "Deletion Case 1." << std::endl;
	if (n->parent != NULL)
	{
		if (delete_case2(n))
			return true;
		else
			return false;
	}
}

void node::del()
{
	if (this == NULL)
		return;
	//std::cout << "Deleting \"" << this->val << "\"." << std::endl;
	node* nodeToDelete = NULL;
	if (this->left != NULL)
	{
		nodeToDelete = this->left;
		while (nodeToDelete->right != NULL)
			nodeToDelete = nodeToDelete->right;
	}else if (this->right != NULL)
	{
		nodeToDelete = this->right;
		while (nodeToDelete->left != NULL)
			nodeToDelete = nodeToDelete->left;
	}
	if (nodeToDelete != NULL)
	{
		std::cout << "Replacing \"" << this->val << "\" with ";
		this->val = nodeToDelete->val;
		if (nodeToDelete == nodeToDelete->parent->left)
		{
			std::cout << "predecessor \"" << nodeToDelete->val << "\"" << std::endl;
			nodeToDelete->parent->left = nodeToDelete->right;
			if (nodeToDelete->right != NULL)
			{
				std::cout << "\"" << nodeToDelete->val << "\" has a right child, moving it to child of \"" << nodeToDelete->parent->val << "\"." << std::endl;
				nodeToDelete->right->parent = nodeToDelete->parent;
			}else if (nodeToDelete->left != NULL)
			{
				std::cout << "\"" << nodeToDelete->val << "\" has a left child (special case where predecessor is also child), moving it to child of \"" << nodeToDelete->parent->val << "\"." << std::endl;
				nodeToDelete->parent->left = nodeToDelete->left;
				nodeToDelete->left->parent = nodeToDelete->parent;
			}
		}
		else
		{
			std::cout << "successor \"" << nodeToDelete->val << "\"" << std::endl;
			nodeToDelete->parent->right = nodeToDelete->left;
			if (nodeToDelete->left != NULL)
			{
				std::cout << "\"" << nodeToDelete->val << "\" has a left child, moving it to child of \"" << nodeToDelete->parent->val << "\"." << std::endl;
				nodeToDelete->left->parent = nodeToDelete->parent;
			}else if (nodeToDelete->right != NULL)
			{
				std::cout << "\"" << nodeToDelete->val << "\" has a right child (special case where predecessor is also child), moving it to child of \"" << nodeToDelete->parent->val << "\"." << std::endl;
				nodeToDelete->parent->right = nodeToDelete->right;
				nodeToDelete->right->parent = nodeToDelete->parent;
			}
		}
		if (nodeToDelete->color == true)
		{
			std::cout << "\"" << nodeToDelete->val << "\" is RED, deleting it will not break black-height." << std::endl;
		}
		else {
			node* childOfDeletedNode = NULL;
			if (nodeToDelete->left != NULL)
				childOfDeletedNode = nodeToDelete->left;
			else
				childOfDeletedNode = nodeToDelete->right;
			if (childOfDeletedNode != NULL)
			{
				std::cout << "\"" << nodeToDelete->val << "\" has a child, \"" << childOfDeletedNode->val << "\", which is ";
				
			}
			else {
				std::cout << "\"" << nodeToDelete->val << "\" has no children, so its child is considered ";
			}
			if (childOfDeletedNode == NULL || childOfDeletedNode != NULL && childOfDeletedNode->color == false)
			{
				std::cout << "BLACK." << std::endl;
				std::cout << "This is the complex case of BLACK followed by BLACK. Deleting \"" << nodeToDelete->val << "\" will result in a black-imbalance." << std::endl;
				if (delete_case1(childOfDeletedNode))
				{
					return;
				}
			}
			else {
				std::cout << "RED." << std::endl;
				std::cout << "This is a simple case of BLACK followed by RED, which can be fixed by coloring \"" << childOfDeletedNode->val << "\" BLACK." << std::endl;
				childOfDeletedNode->color = false;
			}
		}
	}
	else {
		std::cout << "\"" << this->val << "\" has no successors, removing it completely." << std::endl;
		if (this->parent == NULL)
		{
			std::cout << "\"" << this->val << "\" is the root, so the tree is now empty." << std::endl;
			root = NULL;
			return;
		}
		if (this->color == false)
		{
			std::cout << "\"" << this->val << "\" is BLACK with only leaf nodes as children, deletion will result in black-imbalance." << std::endl;
		}
		if (this == this->parent->right)
			this->parent->right = NULL;
		else
			this->parent->left = NULL;
	}
}

