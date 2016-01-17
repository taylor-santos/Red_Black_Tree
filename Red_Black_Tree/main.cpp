#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "tree.h"
#include "node.h"
#include "functions.h"

HANDLE hConsole;

tree* Tree = new tree();

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
	
	std::cout << "To manipulate individual nodes, input either 'I', 'D', or 'S' (Insert, Delete, Search) followed by an input string." << std::endl
		<< "To read from or write to a file, input 'file' followed by 'I', 'D', or 'save', followed by a directory." << std::endl
		<< "Input 'print' to print the tree to the console." << std::endl << std::endl;

	while (1)
	{
		std::string input;
		do
		{

			std::cout << "> ";
			//Prompt for an input until a valid one is given
			while (	!std::getline(std::cin, input) || 
					input.size() < 3 ||
					(input.compare(0, 5, "print") != 0 &&
					input.compare(0, 5, "file ") != 0 &&
					input.compare(0, 2, "i ") != 0 &&
					input.compare(0, 2, "I ") != 0 &&
					input.compare(0, 6, "input ") != 0 &&
					input.compare(0, 7, "insert ") != 0 &&
					input.compare(0, 2, "d ") != 0 &&
					input.compare(0, 2, "D ") != 0 &&
					input.compare(0, 7, "delete ") != 0 &&
					input.compare(0, 2, "s ") != 0 &&
					input.compare(0, 2, "S ") != 0 &&
					input.compare(0, 7, "search ") != 0))

			{
				std::cout << "Invalid input. Try again: ";
			}
			if (input.compare(0,5,"file ") == 0)
			{
				if (input.size() > 7)
				{
					input.erase(0, 5);
					if (input.compare(0, 1, "i") == 0 || input.compare(0, 1, "I") == 0)
					{
						if (input.compare(0, 6, "input ") == 0)
							input.erase(0, 6);
						else if (input.compare(0, 7, "insert ") == 0)
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
								if (Tree->root->isLeaf == true)
								{
									//If the tree is empty, add the new node as root
									Tree->root->isLeaf = false;
									Tree->root->val = new std::string(input);
									Tree->root->left = new node(Tree->root);
									Tree->root->right = new node(Tree->root);
									Tree->root->color = false;
								}
								else {
									//Otherwise, call the root's insert function
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
						std::cout << "Input the tree traversal method ('pre', 'in', 'post', or 'level'): ";
						std::string traverseType;
						while (!std::getline(std::cin, traverseType) || (traverseType.compare(0, 3, "pre") != 0 && traverseType.compare(0, 2, "in") != 0 && traverseType.compare(0, 4, "post") != 0 && traverseType.compare(0, 5, "level") != 0 && traverseType.compare(0, 7, "graphic") != 0))
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
						else if (traverseType.compare(0, 5, "level") == 0)
						{
							Tree->printLevelOrder(f);
						}
						else if (traverseType.compare(0, 7, "graphic") == 0)
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
					std::cout << "Tree contains \"" << *searchedNode->val << "\"" << std::endl;
					std::cout << "\"" << *searchedNode->val << "\" has a height of " << searchedNode->height() << " and a depth of " << searchedNode->depth(Tree) << "." << std::endl;
				}
				else {
					std::cout << "Tree does not contain \"" << input << "\"" << std::endl;
				}
			}
			else if (input.compare(0, 1, "i") == 0 || input.compare(0, 1, "I") == 0)
			{
				if (input.compare(0, 6, "input ") == 0)
					input.erase(0, 6);
				else if (input.compare(0, 7, "insert ") == 0)
					input.erase(0, 7);
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
			std::cout << "Tree contains " << Tree->root->childCount();
			if (Tree->root->childCount() != 1)
				std::cout << " nodes." << std::endl;
			else
				std::cout << " node." << std::endl;
		} while (Tree->checkTree(Tree->root));
		Tree->drawTree(Tree->root);
		std::cout << std::endl;
		while (1);
	}
}

