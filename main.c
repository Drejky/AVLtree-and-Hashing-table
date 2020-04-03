#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COUNT 10

typedef struct foo {
	int val;
	int height;

	foo* parent;
	foo* left;
	foo* right;
}Node;

//Taken from geeks for geeks for testing, delete later
void print2DUtil(Node *root, int space)
{
	// Base case 
	if (root == NULL)
		return;

	// Increase distance between levels 
	space += COUNT;

	// Process right child first 
	print2DUtil(root->right, space);

	// Print current node after space 
	// count 
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->val);

	// Process left child 
	print2DUtil(root->left, space);
}

//Simple function for comparing ints
int max(int a, int b) {
	if (a >= b)
		return a;
	else if (a < b)
		return b;
}

//Gets the length of the longest branch in tree
int height(Node* curr, int bal) {
	if (!curr)
		return bal;
	return max(height(curr->left, bal+1), height(curr->right, bal+1));

}

int getBalance(Node* curr) {
	return height(curr->left, 0) - height(curr->right, 0);
}

void fixParent(Node* curr) {
	if (!curr->parent)
		return;
	if (curr->parent->val < curr->val)
		curr->parent->right = curr;
	else
		curr->parent->left = curr;
}

//Create a new node
Node* newNode(Node* parent, int val) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->right = NULL;
	temp->left = NULL;
	temp->val = val;
	temp->parent = parent;
	return temp;
}

//Functions for rotations in our tree
Node* LLrotate(Node *curr) {
	Node* newRoot = curr->left;
	Node* rightChild = newRoot->right;

	newRoot->right = curr;
	newRoot->right->left = rightChild;
	newRoot->parent = curr->parent;
	curr->parent = newRoot;
	fixParent(newRoot);
	return newRoot;
	
}
Node* RRrotate(Node *curr) {
	Node* newRoot = curr->right;
	Node* leftChild = newRoot->left;

	newRoot->left = curr;
	newRoot->left->right = leftChild;
	newRoot->parent = curr->parent;
	curr->parent = newRoot;
	fixParent(newRoot);
	return newRoot;

}
Node* LRrotate(Node *curr) {
	Node* newRoot = curr->left->right;
	Node* leftChild = newRoot->left;
	Node* rightChild = newRoot->right;
	newRoot->left = curr->left;
	newRoot->left->parent = newRoot;
	newRoot->right = curr;
	newRoot->left->right = leftChild;
	newRoot->right->left = rightChild;
	newRoot->parent = curr->parent;
	curr->parent = newRoot;
	fixParent(newRoot);
	return newRoot;
}
Node* RLrotate(Node *curr) {
	Node* newRoot = curr->right->left;
	Node* leftChild = newRoot->left;
	Node* rightChild = newRoot->right;
	newRoot->right = curr->right;
	curr->right->parent = newRoot;
	newRoot->left = curr;
	newRoot->left->right = leftChild;
	newRoot->right->left = rightChild;
	newRoot->parent = curr->parent;
	curr->parent = newRoot;
	fixParent(newRoot);
	return newRoot;
}

Node* balance(Node* curr, int val) {
	int bal;
	while (curr->parent) {
		curr = curr->parent;
		bal = getBalance(curr);
		if (bal < -1) {//R
			if (val > curr->right->val) {//RR
				return curr = RRrotate(curr);
			}
			else {
				return curr = RLrotate(curr);
			}
		}
		else if (bal > 1) {//L
			if (val < curr->left->val) {//LL
				return curr = LLrotate(curr);
			}
			else {
				return curr = LRrotate(curr);
			}
		}
	}
}

//Insert function
Node* insert(Node *curr, int val) {
	//Simple binary tree insertion
	if (curr) {
		if (curr->val > val) {
			if (curr->left == NULL) {
				curr->left = newNode(curr, val);
				curr = balance(curr, val);
			}
			else {
				curr = insert(curr->left, val);
			}
		}
		else if (curr->val < val) {
			if (curr->right == NULL) {
				curr->right = newNode(curr, val);
				curr = balance(curr, val);
			}
			else {
				curr = insert(curr->right, val);
			}
		}
	}
	else {
		curr = newNode(NULL, val);
	}
	
	while (curr->parent)
		curr = curr->parent;

	
	/*
	printf("\n____________%d\n",val);
	print2DUtil(curr, 0);
	*/
	return curr;
}

//Search function
Node* search(Node* curr, int x) {
	if (!curr) {
		return NULL;
	}
	else {
		if (curr->val == x)
			return curr;
		if (curr->left)
			return curr = search(curr->left, x);
		if (curr->right)
			return curr = search(curr->right, x);
		else
			return NULL;
	}
}

//Random number generator for testing
int rando(int low, int high) {	//random numbers for testing
	return rand() % (high - low + 1) + low;
}

int main() {
	Node* start = NULL;

	int temp;
	
	for (int i = 0; i < 1000; i++) {
		temp = rando(0, 1000);
		if (!(search(start, temp)))
			start = insert(start, temp);
	}
	

	
	/*
	start = insert(start, 1);
	start = insert(start, 3);
	start = insert(start, 2);
	start = RLrotate(start);
	start = insert(start, 50);
	start = insert(start, 51);
	start->right = RRrotate(start->right);

	printf("\n____________\n");
	print2DUtil(start, 0);
	*/
	//RRrotate(start);
	
	
	printf("\n____________%d\n", start->parent);
	print2DUtil(start, 0);
	

	
	return 0;
}