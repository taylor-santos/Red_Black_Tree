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
	int findDepth(node* n);
	void preOrderSave(struct node* n, std::ofstream& file);
	void inOrderSave(struct node* n, std::ofstream& file);
	void postOrderSave(struct node* n, std::ofstream& file);
	void stylizedSave(struct node* n, std::ofstream& file);

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
	
	std::cout << "Input either 'I', 'D', or 'S' (Insert, Delete, Search) followed by an input string," << std::endl
		<< "or input 'file' followed by 'I', 'D', or 'save', followed by a directory." << std::endl;

	while (1)
	{
		std::string input;
		do
		{

			std::cout << "Input: ";
			while (	!std::getline(std::cin, input) || 
					input.size() < 3 ||
					(input.compare(0, 5, "print") != 0 &&
					input.compare(0, 5, "file ") != 0 &&
					input.compare(0, 2, "i ") != 0 &&
					input.compare(0, 2, "I ") != 0 &&
					input.compare(0, 6, "input ") != 0 &&
					input.compare(0, 2, "d ") != 0 &&
					input.compare(0, 2, "D ") != 0 &&
					input.compare(0, 7, "delete ") != 0 &&
					input.compare(0, 2, "s ") != 0 &&
					input.compare(0, 2, "S ") != 0 &&
					input.compare(0, 7, "search ") != 0))

			{
				std::cout << "Invalid input. Try again: ";
			}
			/*
			if (input.compare(0, 4, "file") == 0)
			{
				std::cout << "Please enter a file directory, or 'exit': ";
				std::string dir;
				while (!std::getline(std::cin, dir) ||
					dir.size() < 1)
				{
					std::cout << "Invalid input. Try again: ";
				}

				if (dir.compare(0, 4, "exit") != 0)
				{
					std::cout << "Please input 'I' or 'D' to add or delete the contents of the file to the tree." << std::endl
								<< "  Or, input 'save' followed by 'pre', 'in', or 'post' to save the tree to the file: ";
					while (!std::getline(std::cin, input) ||
						input.size() < 1 ||
						(input.compare(0, 1, "i") != 0 &&
						input.compare(0, 1, "I") != 0 &&
						input.compare(0, 1, "d") != 0 &&
						input.compare(0, 1, "D") != 0 &&
						input.compare(0, 5, "save ") != 0))
					{
						std::cout << "Invalid input. Try again: ";
					}
					if (input.compare(0, 1, "i") == 0 || input.compare(0, 1, "I") == 0)
					{
						std::ifstream file(dir);
						if (!file.is_open()) {
							std::cout << "File not found!" << std::endl;
						}
						else {
							while (std::getline(file, input))
							{
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
					}
					else if (input.compare(0, 1, "d") == 0 || input.compare(0, 1, "D") == 0)
					{
						std::ifstream file(dir);
						if (!file.is_open()) {
							std::cout << "File not found!" << std::endl;
						}
						else {
							while (std::getline(file, input))
							{
								node* searchedNode = Tree->search(input);
								if (searchedNode != NULL)
								{
									searchedNode->del(Tree);
								}
							}
						}
					}
					else if (input.compare(0, 5, "save ") == 0 && (input.compare(5, 3, "pre") == 0 || input.compare(5, 2, "in") == 0 || input.compare(5, 4, "post") == 0 || input.compare(5, 8, "stylized") == 0))
					{
						std::ifstream file(dir);
						if (file.is_open()) {
							std::cout << "File already exists, would you like to overwrite it? (y/n): ";
							std::string str;
							while (!std::getline(std::cin, str) || 
									(str.compare(0, 1, "y") != 0 &&
									str.compare(0, 1, "n") != 0))
							{
								std::cout << "Invalid input. Please enter 'y' or 'n': ";
							}
							if (str.compare(0, 1, "n") == 0)
							{
								file.close();
								continue;
							}
						}
						std::ofstream f(dir);
						if (input.compare(5, 3, "pre") == 0)
						{
							Tree->preOrderSave(Tree->root, f);
						}
						else if (input.compare(5, 2, "in") == 0)
						{
							Tree->inOrderSave(Tree->root, f);
						}
						else if (input.compare(5, 4, "post") == 0)
						{
							Tree->postOrderSave(Tree->root, f);
						}
						else if (input.compare(5, 8, "stylized") == 0)
						{
							//std::wofstream f(dir);
							Tree->stylizedSave(Tree->root, f);
						}
						file.close();
						f.close();
					}
				}
			}
			*/
			if (input.compare(0,5,"file ") == 0)
			{
				if (input.size() > 7)
				{
					input.erase(0, 5);
					if (input.compare(0, 1, "i") == 0 || input.compare(0, 1, "I") == 0)
					{
						if (input.compare(0, 6, "input ") == 0)
							input.erase(0, 6);
						else
							input.erase(0, 2);
						std::ifstream file(input);
						if (!file.is_open()) {
							std::cout << "File not found!" << std::endl;
						}
						else {
							while (std::getline(file, input))
							{
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
					}
					else if (input.compare(0, 1, "d") == 0 || input.compare(0, 1, "D") == 0)
					{
						if (input.compare(0, 7, "delete ") == 0)
							input.erase(0, 7);
						else
							input.erase(0, 2);
						std::ifstream file(input);
						if (!file.is_open()) {
							std::cout << "File not found!" << std::endl;
						}
						else {
							while (std::getline(file, input))
							{
								node* searchedNode = Tree->search(input);
								if (searchedNode != NULL)
								{
									searchedNode->del(Tree);
								}
							}
						}
					}
					else if (input.compare(0, 5, "save ") == 0)
					{
						input.erase(0, 5);
						std::cout << "Input the tree traversal method ('pre', 'in', or 'post'): ";
						std::string traverseType;
						while (!std::getline(std::cin, traverseType) || (traverseType.compare(0, 3, "pre") != 0 && traverseType.compare(0, 2, "in") != 0 && traverseType.compare(0, 4, "post") != 0 && traverseType.compare(0, 8, "stylized") != 0))
						{
							std::cout << "Invalid input. Try again: ";
						}
						std::ifstream file(input);
						if (file.is_open()) {
							std::cout << "File already exists, would you like to overwrite it? (y/n): ";
							std::string str;
							while (!std::getline(std::cin, str) ||
								(str.compare(0, 1, "y") != 0 &&
									str.compare(0, 1, "n") != 0))
							{
								std::cout << "Invalid input. Please enter 'y' or 'n': ";
							}
							if (str.compare(0, 1, "n") == 0)
							{
								file.close();
								continue;
							}
						}
						std::ofstream f(input);
						if (traverseType.compare(0, 3, "pre") == 0)
						{
							Tree->preOrderSave(Tree->root, f);
						}
						else if (traverseType.compare(0, 2, "in") == 0)
						{
							Tree->inOrderSave(Tree->root, f);
						}
						else if (traverseType.compare(0, 4, "post") == 0)
						{
							Tree->postOrderSave(Tree->root, f);
						}
						else if (traverseType.compare(0, 8, "stylized") == 0)
						{
							Tree->stylizedSave(Tree->root, f);
						}
						file.close();
						f.close();
					}
				}
				else {
					std::cout << "Invalid input." << std::endl;
				}
			}
			else if (input.compare(0, 1, "s") == 0 || input.compare(0, 1, "S") == 0)
			{
				if (input.compare(0, 7, "search ") == 0)
					input.erase(0, 7);
				else
					input.erase(0, 2);
				node* searchedNode = Tree->search(input);
				if (searchedNode != NULL)
				{
					std::cout << "Tree contains \"" << input << "\"" << std::endl;
				}
				else {
					std::cout << "Tree does not contain \"" << input << "\"" << std::endl;
				}
			}
			else if (input.compare(0, 1, "i") == 0 || input.compare(0, 1, "I") == 0)
			{
				if (input.compare(0, 6, "input ") == 0)
					input.erase(0, 6);
				else
					input.erase(0, 2);
				node* searchedNode = Tree->search(input);
				if (searchedNode != NULL)
				{
					std::cout << "Tree already contains \"" << *searchedNode->val << "\"" << std::endl;
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
			else if (input.compare(0, 1, "d") == 0 || input.compare(0, 1, "D") == 0)
			{
				if (input.compare(0, 7, "delete ") == 0)
					input.erase(0, 7);
				else
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
			else if (input.compare(0, 5, "print") == 0)
			{
				Tree->drawTree(Tree->root);
			}
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
		double weight1 = (*str1)[c1];
		double weight2 = (*str2)[c2];
		bool s1isNum = false;
		bool s2isNum = false;
		if (weight1 >= 48 && weight1 <= 57 || weight1 == 45 || weight1 == 46)	
		{
			bool negative = false;
			int decimal = 0;
			double num = 0;
			if (weight1 == 45)
				negative = true;
			else if (weight1 == 46)
			{
				decimal = 1;
			}else{
				num = weight1 - 48;
				s1isNum = true;
			}
			c1++;
			while ((c1 < (*str1).size() && ((*str1)[c1] >= 48 && (*str1)[c1] <= 57)) || ((*str1)[c1] == 46 && decimal == 0))
			{
				if ((*str1)[c1] == 46)
				{
						decimal++;
				}
				else {
					s1isNum = true;
					if (decimal == 0)
					{
						num *= 10;
						num += (*str1)[c1] - 48;
					}
					else {
						num += (double)((*str1)[c1] - 48) / pow(10, decimal);
						decimal++;
					}
				}
				c1++;
			}
			weight1 = negative ? -(num) : num;
		}
		else {
			c1++;
		}
		if (weight2 >= 48 && weight2 <= 57 || weight2 == 45 || weight2 == 46)
		{
			bool negative = false;
			int decimal = 0;
			double num = 0;
			if (weight2 == 45)
				negative = true;
			else if (weight2 == 46)
			{
				decimal = 1;
			}
			else {
				num = weight2 - 48;
				s2isNum = true;
			}
			c2++;
			while ((c2 < (*str2).size() && ((*str2)[c2] >= 48 && (*str2)[c2] <= 57)) || ((*str2)[c2] == 46 && decimal == 0))
			{
				if ((*str2)[c2] == 46)
				{
					decimal++;
				}
				else {
					s2isNum = true;
					if (decimal == 0)
					{
						num *= 10;
						num += (*str2)[c2] - 48;
					}
					else {
						num += (double)((*str2)[c2] - 48) / pow(10, decimal);
						decimal++;
					}
				}
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
			std::cout << "BROKEN TREE! Leaf is RED." << std::endl;
			return false;
		}
		else {
			return true;
		}
	}
	if (n == NULL)
	{
		std::cout << "BROKEN TREE! Not all nodes have instantiated children." << std::endl;
		return false;
	}
	if (n->color == true)
	{
		if (n->parent == NULL)
		{
			//Node is root, but also red. Tree is not correct.
			std::cout << "BROKEN TREE! Root is RED." << std::endl;
			return false;
		}
		if (n->left->color == true)
		{
			//Node is red, but has red left child. Tree is not correct.
			std::cout << "BROKEN TREE! Node is RED, but has RED left child." << std::endl;
			return false;
		}
		if (n->right->color == true)
		{
			//Node is red, but has red right child. Tree is not correct.
			std::cout << "BROKEN TREE! Node is RED, but has RED right child." << std::endl;
			return false;
		}
		if ((n->right->isLeaf == false && n->left->isLeaf == true) || (n->right->isLeaf == true && n->left->isLeaf == false))
		{
			//Node is red, but has one single leaf child. Tree is not correct.
			std::cout << "BROKEN TREE! Node is RED, but has one single leaf child." << std::endl;
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
			std::cout << "BROKEN TREE! Node's left child is larger than its parent." << std::endl;
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
			std::cout << "BROKEN TREE! Node's right child is smaller than its parent." << std::endl;
			return false;
		}
	}

	if (n->nodeHeight() == 0)
	{
		//Tree's black height unbalanced.
		std::cout << "BROKEN TREE! Tree's black height is unbalanced." << std::endl;
		return false;
	}
	if (checkTree(n->left) && checkTree(n->right))
	{
		//Node is correct, and node's two children are also correct.
		return true;
	}
	std::cout << "BROKEN TREE! Unknown error." << std::endl;
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

int tree::findDepth(node* n)
{
	int depth = 0;
	node* nodeWalker = root;
	int cmp = alphanumeric_strcmp(nodeWalker->val, n->val);
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
		cmp = alphanumeric_strcmp(nodeWalker->val, n->val);
	}
	return depth;
}

void tree::preOrderSave(node* n, std::ofstream& f)
{
	if (n->isLeaf == true)
		return;
	f << *n->val << std::endl;
	preOrderSave(n->left, f);
	preOrderSave(n->right, f);
}
void tree::inOrderSave(node* n, std::ofstream& f)
{
	if (n->isLeaf == true)
		return;
	inOrderSave(n->left, f);
	f << *n->val << std::endl;
	inOrderSave(n->right, f);
}
void tree::postOrderSave(node* n, std::ofstream& f)
{
	if (n->isLeaf == true)
		return;
	postOrderSave(n->left, f);
	postOrderSave(n->right, f);
	f << *n->val << std::endl;
}

void tree::stylizedSave(struct node* n, std::ofstream& file)
{
	if (n == NULL)
		return;
	if (n->isLeaf == true)
		return;
	if (n->right->isLeaf == false)
		stylizedSave(n->right, file);
	node* nodeWalker = root;
	if (n->parent == NULL)
		file << "-";
	else
		file << " ";
	int blackCount = 0;
	while (nodeWalker != n)
	{
		if (nodeWalker->color == false)
			blackCount++;
		int compare = alphanumeric_strcmp(n->val, nodeWalker->val);
		if (compare > 0) //Desired node is larger than walker
		{
			int compareNext = alphanumeric_strcmp(nodeWalker->right->val, n->val);
			if (compareNext > 0)
				file << "|" << " ";
			else if (compareNext != 0)
				file << "  ";
			nodeWalker = nodeWalker->right;
		}
		else if (compare < 0) //Desired node is smaller than walker
		{
			int compareNext = alphanumeric_strcmp(nodeWalker->left->val, n->val);
			if (compareNext < 0)
				file << "|" << " ";
			else if (compareNext != 0)
				file << "  ";
			nodeWalker = nodeWalker->left;
		}
		else
			break;
	}
	if (n->parent != NULL)
	{
		if (n == n->parent->left)
			file << "\\" << "-";
		else
			file << "/" << "-";
	}
	//if (n->color)
	//	SetConsoleTextAttribute(hConsole, 79);
	//else
	//	SetConsoleTextAttribute(hConsole, 15);
	file << "[";
	file << *n->val;
	file << "]";
	//SetConsoleTextAttribute(hConsole, 240);

	if (n->left->isLeaf == true || n->right->isLeaf == true)
	{
		if (n->color == false)
			blackCount++;
		//std::cout << "				" << blackCount;
	}
	file << std::endl;

	if (n->left->isLeaf == false)
	{
		stylizedSave(n->left, file);
	}
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
			Tree->nodeCount++;
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
			Tree->nodeCount++;
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
		Tree->nodeCount--;
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
			Tree->nodeCount--;
			return;
		}
		else {
			//m is black and its child is black, deleting m breaks black height.
			if (c2->isLeaf == false)
			delete c2;
			delete m->val;
			delete m;
			Tree->nodeCount--;
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

