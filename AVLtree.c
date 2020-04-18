#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode {
	int val;
	int height;

	AVLNode* left;
	AVLNode* right;
}NodeA;

//Simple function for comparing ints
int max(int a, int b) {
	if (a >= b)
		return a;
	else if (a < b)
		return b;
}

//Returns the height of a node, needed to return 0 if there is no node
int height(NodeA* curr) {
	if (!curr)
		return 0;
	else
		return curr->height;
}

//Create a new node
NodeA* newNode(int val) {
	NodeA* temp = (NodeA*)malloc(sizeof(NodeA));
	temp->right = NULL;
	temp->left = NULL;
	temp->val = val;
	temp->height = 1;
	return temp;
}

//Fixes the height of given node
NodeA* fixHeight(NodeA* curr) {
	curr->height = 1 + max(height(curr->left), height(curr->right));
	return curr;
}

//Functions for rotations in our tree
NodeA* LLrotate(NodeA*curr) {
	//Save nodes that would otherwise be lost in temporary variables
	NodeA* newRoot = curr->left;
	NodeA* rightChild = newRoot->right;

	//Preform the LL rotation
	newRoot->right = curr;
	newRoot->right->left = rightChild;

	//Fix the heights of nodes that are affected
	curr = fixHeight(curr);
	newRoot = fixHeight(newRoot);
	
	//Return the root after rotation
	return newRoot;
}

NodeA* RRrotate(NodeA*curr) {
	//Save nodes that would otherwise be lost in temporary variables
	NodeA* newRoot = curr->right;
	NodeA* leftChild = newRoot->left;

	//Preform the RR rotation
	newRoot->left = curr;
	newRoot->left->right = leftChild;

	//Fix the heights of nodes that are affected
	curr = fixHeight(curr);
	newRoot = fixHeight(newRoot);
	
	//Return the root after rotation
	return newRoot;
}

NodeA* LRrotate(NodeA*curr) {
	//Save nodes that would otherwise be lost in temporary variables
	NodeA* newRoot = curr->left->right;
	NodeA* leftChild = newRoot->left;
	NodeA* rightChild = newRoot->right;

	//Preform the LR rotation
	newRoot->left = curr->left;
	newRoot->right = curr;
	newRoot->left->right = leftChild;
	newRoot->right->left = rightChild;

	//Fix the heights of nodes that are affected
	curr = fixHeight(curr);
	newRoot = fixHeight(newRoot->left);
	newRoot = fixHeight(newRoot);

	//Return the root after rotation
	return newRoot;
}

NodeA* RLrotate(NodeA*curr) {
	//Save nodes that would otherwise be lost in temporary variables
	NodeA* newRoot = curr->right->left;
	NodeA* leftChild = newRoot->left;
	NodeA* rightChild = newRoot->right;

	//Preform the RL rotation
	newRoot->right = curr->right;
	newRoot->left = curr;
	newRoot->left->right = leftChild;
	newRoot->right->left = rightChild;

	//Fix the heights of nodes that are affected
	curr = fixHeight(curr);
	newRoot = fixHeight(newRoot->right);
	newRoot = fixHeight(newRoot);

	//Return the root after rotation
	return newRoot;
}

//Function to check whether a node is ballanced and preform rotation if it isnt
NodeA* balance(NodeA* curr, int val) {
	//Calculating the balance factor for node
	int bal = height(curr->left) - height(curr->right);

	//If node is unbalanced
	if (bal > 1 || bal < -1) {
		if (val > curr->val) {//R
			if (val > curr->right->val) {//RR
				return RRrotate(curr);
			}
			else if (val < curr->right->val) {//RL
				return RLrotate(curr);
			}
		}
		else if (val < curr->val) {//L
			if (val < curr->left->val) {//LL
				return LLrotate(curr);
			}
			else if (val > curr->left->val) {//LR
				return LRrotate(curr);
			}
		}
	}
	//Otherwise return the node without performing rotations
	else
		return curr;
}

//Insert function
NodeA* insertAVL(NodeA*curr, int val) {
	//Recursively insert node until we find free spot for it
	if (curr) {
		if (curr->val > val) {
			curr->left = insertAVL(curr->left, val);
		}
		else if (curr->val < val) {
			curr->right = insertAVL(curr->right, val);
		}
	}
	else {
		return newNode(val);
	}
	
	//After the node has been added, this code will be executed for every perent node of new node
	//Fixing heights of all parent nodes
	if (curr->val > val) {
		curr->height = max(height(curr->left) + 1, height(curr));
	}
	else if (curr->val < val) {
		curr->height = max(height(curr), height(curr->right) + 1);
	}

	//Checking whether node is balanced, performing rotation otherwise
	curr = balance(curr, val);

	//returning possibly rotated node
	return curr;
}

//The trees search function
NodeA* searchAVL(NodeA* curr, int x) {
	while (curr) {
		if (curr->val == x)
			return curr;
		else if (curr->val < x)
			curr = curr->right;
		else
			curr = curr->left;
	}
	return NULL;
}

//To free the entire tree
void del_tree(NodeA* curr) {
	if (!curr)
		return;
	if (curr->left)
		del_tree(curr->left);
	if (curr->right)
		del_tree(curr->right);
	free(curr);
}