#pragma once
typedef struct node {
	int val;
	int height;

	node* left;
	node* right;
}Node;
int max(int a, int b);
int height(Node* curr);
Node* newNode(int val);
Node* LLrotate(Node *curr);
Node* RRrotate(Node *curr);
Node* LRrotate(Node *curr);
Node* RLrotate(Node *curr);
Node* balance(Node* curr, int val);
Node* insertAVL(Node *curr, int val);
Node* searchAVL(Node* curr, int x);