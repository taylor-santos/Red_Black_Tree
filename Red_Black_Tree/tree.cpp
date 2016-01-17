#include <iostream>
#include "tree.h"
#include "node.h"
#include "functions.h"
#include <string>
#include <fstream>
#include <Windows.h>

extern HANDLE hConsole;

tree::tree()
{
	root = new struct node(NULL);
};

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
		if (alphanumeric_strcmp(n->val, n->left->val) <= 0)
		{
			//Left node is larger than its parent. Tree is not correct.
			std::cout << "BROKEN TREE! Node's left child is larger than its parent." << std::endl;
			return false;
		}
	}
	if (n->right->isLeaf == false)
	{
		if (alphanumeric_strcmp(n->val, n->right->val) >= 0)
		{
			//Right node is smaller than its parent. Tree is not correct.
			std::cout << "BROKEN TREE! Node's right child is smaller than its parent." << std::endl;
			return false;
		}
	}

	if (n->blackHeight() == 0)
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

void tree::givenLevelSave(node* n, int level, std::ofstream& file)
{
	if (n->isLeaf == true)
		return;
	if (level == 1)
		file << *n->val << std::endl;
	else if (level > 1)
	{
		givenLevelSave(n->left, level - 1, file);
		givenLevelSave(n->right, level - 1, file);
	}
}

void tree::printLevelOrder(std::ofstream& file)
{
	int rear, front;
	node** queue = createQueue(this->root->childCount(), &front, &rear);
	node* temp_node = root;

	while (temp_node != NULL)
	{
		file << *temp_node->val << std::endl;
		if (temp_node->left->isLeaf == false)
		{
			enQueue(queue, &rear, temp_node->left);
		}
		if (temp_node->right->isLeaf == false)
		{
			enQueue(queue, &rear, temp_node->right);
		}
		temp_node = deQueue(queue, &front);
	}
	free(queue);
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
	file << "[";
	file << *n->val;
	file << "]";

	if (n->left->isLeaf == true || n->right->isLeaf == true)
	{
		if (n->color == false)
			blackCount++;
	}
	file << std::endl;

	if (n->left->isLeaf == false)
	{
		stylizedSave(n->left, file);
	}
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
		int compare = alphanumeric_strcmp(currNode->val, nodeWalker->val);
		if (compare > 0) //Desired node is larger than walker
		{
			int compareNext = alphanumeric_strcmp(nodeWalker->right->val, currNode->val);
			if (compareNext > 0)
				std::cout << (char)186 << " ";
			else if (compareNext != 0)
				std::cout << "  ";
			nodeWalker = nodeWalker->right;
		}
		else if (compare < 0) //Desired node is smaller than walker
		{
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
	}
	std::cout << std::endl;

	if (currNode->left->isLeaf == false)
	{
		drawTree(currNode->left);
	}
}