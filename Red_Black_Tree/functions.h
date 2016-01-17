#ifndef FUNCTIONS_H
#define FUNCTIONS_H

long long int rand64();

int alphanumeric_strcmp(std::string* str1, std::string* str2);

node** createQueue(int nodeCount, int* front, int* rear);

void enQueue(node** queue, int* rear, node* new_node);

node* deQueue(node** queue, int* front);

#endif
