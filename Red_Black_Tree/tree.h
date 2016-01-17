#ifndef TREE_H
#define TREE_H
struct tree {
	struct node* root;

	void drawTree(struct node* currNode);
	bool checkTree(node* n);
	struct node* search(std::string input);
	void preOrderSave(struct node* n, std::ofstream& file);
	void inOrderSave(struct node* n, std::ofstream& file);
	void postOrderSave(struct node* n, std::ofstream& file);
	void givenLevelSave(node* n, int level, std::ofstream& file);
	void printLevelOrder(std::ofstream& file);
	void stylizedSave(struct node* n, std::ofstream& file);
	tree();
};
#endif