#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COUNT 10
int flag = 0;

typedef struct foo {
	int val;
	int height;

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

int height(Node* curr) {
	if (!curr)
		return 0;
	else
		return curr->height;
}


int treeBalance(Node* curr) {
	int temp;
	if (!curr)
		return 0;
	else {
		temp = height(curr->left) - height(curr->right);
		if (temp > 1 || temp < -1)
			flag = 1;
		curr->height = temp;
	}
	if (curr->right)
		treeBalance(curr->right);
	if (curr->left)
		treeBalance(curr->left);

}

//Create a new node
Node* newNode(int val) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->right = NULL;
	temp->left = NULL;
	temp->val = val;
	temp->height = 0;
	return temp;
}

//Functions for rotations in our tree
Node* LLrotate(Node *curr) {
	Node* newRoot = curr->left;
	Node* rightChild = newRoot->right;

	newRoot->right = curr;
	newRoot->right->left = rightChild;

	curr->height = 1 + max(height(curr->left), height(curr->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
	
	return newRoot;
	
}
Node* RRrotate(Node *curr) {
	Node* newRoot = curr->right;
	Node* leftChild = newRoot->left;

	newRoot->left = curr;
	newRoot->left->right = leftChild;

	curr->height = 1 + max(height(curr->left), height(curr->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
	

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

	curr->height = 1 + max(height(curr->left), height(curr->right));
	newRoot->left->height = 1 + max(height(newRoot->left->left), height(newRoot->left->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

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

	curr->height = 1 + max(height(curr->left), height(curr->right));
	newRoot->right->height = 1 + max(height(newRoot->right->left), height(newRoot->right->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

	return newRoot;
}


Node* balance(Node* curr, int val) {
	int bal;
	bal = height(curr->left) - height(curr->right);
	if (bal < -1) {//R
		if (val > curr->right->val) {//RR
			return RRrotate(curr);
		}
		else if (val < curr->right->val) {
			return RLrotate(curr);
		}
	}
	else if (bal > 1) {//L
		if (val < curr->left->val) {//LL
			return LLrotate(curr);
		}
		else if (val > curr->left->val) {
			return LRrotate(curr);
		}
	}
	else
		return curr;

	
}

//Insert function
Node* insert(Node *curr, int val) {
	//Simple binary tree insertion
	if (curr) {
		if (curr->val > val) {
			curr->left = insert(curr->left, val);
		}
		else if (curr->val < val) {
			curr->right = insert(curr->right, val);
		}
	}
	else {
		return newNode(val);
	}
	
	if (curr->val > val) {
		curr->height = max(height(curr->left) + 1, height(curr));
	}
	else if (curr->val < val) {
		curr->height = max(height(curr), height(curr->right) + 1);
	}

	curr = balance(curr, val);

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

void del_tree(Node* curr) {
	if (!curr)
		return;
	if (curr->left)
		del_tree(curr->left);
	if (curr->right)
		del_tree(curr->right);
	free(curr);
}

int main() {
	Node* start = NULL;

	int temp;
	
	srand(time(NULL));
	for (int i = 0; i < 1000000; i++) {
		temp = rando(0, 2000000);
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
	
	treeBalance(start);/*
	printf("\n____________\n");
	print2DUtil(start, 0);*/
	printf("%d", flag);

	del_tree(start);
	return 0;
}