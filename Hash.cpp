#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct hashNode {
	int val;
	hashNode* next;
}NodeH;

typedef struct table {
	int size;
	int num_of_nodes;
	NodeH** hash_arr;
}HT;

//Hashing function (polynomial accumulation)
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
void freeTable(HT* table) {
	NodeH* curr;
	NodeH* temp;

	int tSize = table->size;		
	
	//Goes through every node and and frees them 
	for (int i = 0; i < tSize; i++) {
		curr = table->hash_arr[i];
		while (curr) {
			temp = curr;
			curr = curr->next;
			free(temp);
		}
	}

	//Seperately frees the array and the table itself
	free(table->hash_arr);
	free(table);
}

//Forward decleration
HT* insertHash(HT* table, int val);

//Function to resize existing table
HT* resizeTable(HT* table, int newSize) {
	//Initializing new table
	HT* newTable = (HT*)calloc(1, sizeof(HT));
	newTable->hash_arr = (NodeH**)calloc(newSize, sizeof(NodeH*));
	newTable->size= newSize;
	newTable->num_of_nodes = 0;

	NodeH* curr;
	int tSize = table->size;

	for (int i = 0; i < tSize; i++) {
		curr = table->hash_arr[i];
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
HT* insertHash(HT* table, int val) {
	//If no table was created so far we make one with size 2
	if (!table) {
		table = (HT*)calloc(1, sizeof(HT));
		table->hash_arr = (NodeH**)calloc(2, sizeof(NodeH*));
		table->size = 2;	
		table->num_of_nodes = 0;
	}

	//Variables we will need for later
	int tSize = table->size;
	int index = hash(val, tSize);
	NodeH* curr;

	//Putting pointer on the index our hash function returned
	curr = table->hash_arr[index];
	
	//Checking if there are already existing nodes on the index, if not we simply insert it
	if (!curr)
		table->hash_arr[index] = newNodeH(val);
	//Otherwise we go through the linked list on given index and insert it at the end
	else {
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = newNodeH(val);
	}

	//Increasing the counter for nodes
	table->num_of_nodes++;

	//If needed we expand the table to the next prime nubmer bigger than 2*current size
	if ((float)table->num_of_nodes / (float)tSize > 2) {
		int temp = 2 * tSize;
		while (!isPrime(temp++));
		table = resizeTable(table, --temp);
	}
	return table;
}

//Search function for the table
NodeH* searchHash(HT* table, int val) {
	if (!table)
		return NULL;

	int index = hash(val, table->size);
	NodeH* curr;

	curr = table->hash_arr[index];
	while (curr) {
		if (curr->val == val)
			return curr;
		else
			curr = curr->next;
	}

	return NULL;
}

//Function to print out the table
void showTable(HT* table) {
	printf("%d\n", table->size);
	NodeH* curr;
	for (int i = 0; i < table->size; i++) {
		curr = table->hash_arr[i];
		while (curr) {
			printf("%d ", curr->val);
			curr = curr->next;
		}
		printf("\n");
	}
}