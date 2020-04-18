#pragma once
typedef struct AVLNode {
	int val;
	int height;

	AVLNode* left;
	AVLNode* right;
}NodeA;
NodeA* insertAVL(NodeA* curr, int val);
NodeA* searchAVL(NodeA* curr, int x);
void del_tree(NodeA* curr);