#include <string>
#include "node.h"

int alphanumeric_strcmp(std::string* str1, std::string* str2)
{
	/*
	Compares two strings and returns >0 if the first string is larger, <0 if the second string is larger, and 0 if they're equal.
	The returned value equals the string index+1 at which they differ. +1 prevents the index from returning 0 if the first characters differ.
	Unlike strcmp, this interprets sequences of integer characters as whole numbers. For example, strcmp would claim "1234" is smaller than "2", because the first character is smaller.
	This function will compare the whole numbers against each other, so it will find "1234" to be larger than "2".
	*/
	unsigned int c1 = 0;
	unsigned int c2 = 0;
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
			}
			else {
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
			return -(int)c2;
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
			return -(int)c2;
		}
	}
	if (c1 < (*str1).size() && c2 >= (*str2).size())
	{
		return c1;
	}
	else if (c1 >= (*str1).size() && c2 < (*str2).size())
	{
		return -(int)c2;
	}
	return 0;
}

node** createQueue(int nodeCount, int* front, int* rear)
{
	node** queue = (node**)malloc(sizeof(node*) * nodeCount);
	*front = *rear = 0;
	return queue;
}

void enQueue(node** queue, int* rear, node* new_node)
{
	queue[*rear] = new_node;
	(*rear)++;
}

node* deQueue(node** queue, int* front)
{
	(*front)++;
	return queue[*front - 1];
}

long long int rand64()
{
	//Generates a random 64-bit signed integer using 4 16-bit random integers.
	int64_t rand64;
	int16_t* rand16 = (int16_t*)&rand64;
	*rand16 = rand() | rand() % 2 << 15;
	*(rand16 + 1) = rand() | rand() % 2 << 15;
	*(rand16 + 2) = rand() | rand() % 2 << 15;
	*(rand16 + 3) = rand() | rand() % 2 << 15;
	return rand64;
}