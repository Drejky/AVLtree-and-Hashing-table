#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct hashNode {
	int val;
	hashNode* next;
}NodeH;

//Hashing function
int hash(int val, int tSize) {
	int hash = 0;
	while (val > 0) {
		hash = (hash * 31) + (val % 10);
		val /= 10;
		hash %= tSize;
	}
	return hash;
}

//Function to check if a number is prime
int isPrime(int x) {
	for (int i = 2; i <= sqrt(x); i++)
		if (!(x % i))
			return 0;
	return 1;
}

//Function for creation of new nodes
NodeH* newNodeH(int val) {
	NodeH* temp = (NodeH*)malloc(sizeof(NodeH));
	temp->val = val;
	temp->next = NULL;
	return temp;
}

//Function to free existing table
void freeTable(NodeH** table) {
	NodeH* curr;
	NodeH* temp;

	//Size of table is stored in its first node (actual size is size + 1)
	int tSize = table[0]->val;		
	
	//Goes through every node and and frees them 
	for (int i = 1; i <= tSize; i++) {
		curr = table[i];
		while (curr) {
			temp = curr;
			curr = curr->next;
			free(temp);
		}
	}

	//Seperately frees the first node holding the size and the table itself
	free(table[0]);
	free(table);
}

//Forward decleration
NodeH** insertHash(NodeH** table, int val);

//Function to resize existing table
NodeH** resizeTable(NodeH** table, int newSize) {
	//Initializing new table
	NodeH** newTable = (NodeH**)calloc(newSize + 1, sizeof(NodeH*));
	newTable[0] = (NodeH*)malloc(sizeof(NodeH));
	newTable[0]->val = newSize;

	NodeH* curr;
	int tSize = table[0]->val;

	for (int i = 1; i <= tSize; i++) {
		curr = table[i];
		while (curr) {
			newTable = insertHash(newTable, curr->val);
			curr = curr->next;
		}
	}

	//Free the original table
	freeTable(table);
	
	//Return new table
	return newTable;
}

//Function to insert into the table (or if table doesnt exist create one with size 2)
NodeH** insertHash(NodeH** table, int val) {
	//If no table was created so far we make one with size 2
	if (!table) {
		table = (NodeH**)calloc(3, sizeof(NodeH*));
		table[0] = (NodeH*)malloc(sizeof(NodeH));
		table[0]->val = 2;
	}

	//Variables we will need for later
	int tSize = table[0]->val;
	int index = hash(val, tSize) + 1;
	int depth = 1;
	NodeH* curr;

	//Putting pointer on the index our hash function returned
	curr = table[index];
	
	//Checking if there are already existing nodes on the index, if not we simply insert it
	if (!curr)
		table[index] = newNodeH(val);
	//Otherwise we go through the linked list on given index and insert it at the end
	else {
		while (curr->next) {
			curr = curr->next;
			depth++;
		}
		curr->next = newNodeH(val);
	}

	//If needed we expand the table to the next prime nubmer bigger than 2*current size
	if ((float)depth / (float)tSize > 0.02) {
		int temp = 2 * tSize;
		while (!isPrime(temp++));
		table = resizeTable(table, --temp);
	}
	return table;
}

//Search function for the table
NodeH* searchHash(NodeH** table, int val) {
	if (!table)
		return NULL;

	int tSize = table[0]->val;
	int index = hash(val, tSize) + 1;
	NodeH* curr;

	curr = table[index];
	while (curr) {
		if (curr->val == val)
			return curr;
		else
			curr = curr->next;
	}

	return NULL;
}

//Function to print out the table
void showTable(NodeH** table) {
	printf("%d\n", table[0]->val);
	NodeH* curr;
	for (int i = 1; i <= table[0]->val; i++) {
		curr = table[i];
		while (curr) {
			printf("%d ", curr->val);
			curr = curr->next;
		}
		printf("\n");
	}
}