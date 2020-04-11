#pragma once
typedef struct node {
	int val;
	int height;

	node* left;
	node* right;
}Node;
Node* insertAVL(Node *curr, int val);
Node* searchAVL(Node* curr, int x);
void del_tree(Node* curr);