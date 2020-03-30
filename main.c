#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COUNT 10

typedef struct foo {
	int val;
	int balance;

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

//Calculates the balance factor for every node
void treeBalance(Node* curr) {
	curr->balance = height(curr->left, 0) - height(curr->right, 0);
	if (curr->left)
		treeBalance(curr->left);
	if (curr->right)
		treeBalance(curr->right);
}

//Create a new node
Node* newNode(int val) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->right = NULL;
	temp->left = NULL;
	temp->val = val;
	return temp;

}

//Functions for rotations in our tree
Node* LLrotate(Node *curr) {
	Node* newRoot = curr->left;
	Node* rightChild = newRoot->right;

	newRoot->right = curr;
	newRoot->right->left = rightChild;
	return newRoot;
	
}
Node* RRrotate(Node *curr) {
	Node* newRoot = curr->right;
	Node* leftChild = newRoot->left;

	newRoot->left = curr;
	newRoot->left->right = leftChild;
	return newRoot;

}
Node* LRrotate(Node *curr) {
	Node* newRoot = curr->left->right;
	Node* leftChild = newRoot->left;
	Node* rightChild = newRoot->right;
	newRoot->left = curr->left;
	newRoot->right = curr;
	newRoot->left->right = leftChild;
	newRoot->right->left = rightChild;
	return newRoot;
}
Node* RLrotate(Node *curr) {
	Node* newRoot = curr->right->left;
	Node* leftChild = newRoot->left;
	Node* rightChild = newRoot->right;
	newRoot->right = curr->right;
	newRoot->left = curr;
	newRoot->left->right = leftChild;
	newRoot->right->left = rightChild;
	return newRoot;
}

//Insert function
Node* insert(Node *curr, int val) {
	if (curr) {
		if (curr->val > val) {
			if (curr->left == NULL) {
				curr->left = newNode(val);
			}
			else {
				insert(curr->left, val);
			}
		}
		if (curr->val < val) {
			if (curr->right == NULL) {
				curr->right = newNode(val);
			}
			else {
				insert(curr->right, val);
			}
		}
	}
	else {
		curr = newNode(val);
	}
	return curr;
}

//Search function
Node* search(Node* curr, int x) {
	if (!curr)
		return NULL;
	if (curr->val == x)
		return curr;
	else if (curr = search(curr->left, x))
		return curr;
	else if (curr = search(curr->right, x))
		return curr;
	else
		return NULL;
}

//Random number generator for testing
int rando(int low, int high) {	//random numbers for testing
	return rand() % (high - low + 1) + low;
}

int main() {
	Node* start = NULL;

	start = insert(start, 10);
	start = insert(start, 30);
	start = insert(start, 20);
	
	/*
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
		start = insert(start, rando(0, 40));
	treeBalance(start);
	*/
	print2DUtil(start, 0);
	//temp = search(start, 30);
	start = RLrotate(start);

	//start->right = RRrotate(start->right);
	printf("\n____________\n");
	print2DUtil(start, 0);

	
	return 0;
}