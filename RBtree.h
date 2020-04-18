#pragma once
enum type { RED, BLACK };
struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	enum type color;
};
void levelorder(struct Node* root);
void preorder(struct Node* root);
struct Node* RB_delete(struct Node *T, struct Node* z);
struct Node* RB_insert(struct Node* T, int data);
struct Node* BST_search(struct Node* root, int x);