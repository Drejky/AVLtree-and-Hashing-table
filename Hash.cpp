#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct hashNode {
	int val;
	hashNode* next;
}NodeH;

int hash(int val, int tSize) {
	int hash = 0;
	while (val > 0) {
		hash = (hash * 31) + (val % 10);
		val /= 10;
		hash %= tSize;
	}
	return hash;
}

NodeH* newNodeH(int val) {
	NodeH* temp = (NodeH*)malloc(sizeof(NodeH));
	temp->val = val;
	temp->next = NULL;
	return temp;
}

NodeH** insertHash(int val, NodeH** table);

NodeH** resizeTable(NodeH** table, int newSize) {
	NodeH** newTable = (NodeH**)calloc(newSize + 1, sizeof(NodeH*));
	newTable[0] = (NodeH*)malloc(sizeof(NodeH));
	newTable[0]->val = newSize;

	NodeH* curr;
	NodeH* temp;
	for (int i = 1; i <= table[0]->val; i++) {
		curr = table[i];
		while (curr) {
			newTable = insertHash(curr->val, newTable);
			temp = curr;
			curr = curr->next;
			free(temp);
		}
	}
	return newTable;
}

NodeH** insertHash(int val, NodeH** table) {
	//If no table was created so far we make one with size 2
	if (!table) {
		table = (NodeH**)calloc(3, sizeof(NodeH*));
		table[0] = (NodeH*)malloc(sizeof(NodeH));
		table[0]->val = 2;
	}

	//Variables we will need for alter
	int tSize = table[0]->val;
	int index = hash(val, tSize) + 1;
	int depth = 1;
	NodeH* curr;


	curr = table[index];
	if (!curr)
		table[index] = newNodeH(val);
	else {
		while (curr->next) {
			curr = curr->next;
			depth++;
		}
		curr->next = newNodeH(val);
	}

	if (depth / tSize > 1)
		table = resizeTable(table, tSize * 2);

	return table;

}


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
int main() {
	NodeH** start = NULL;
	
	for (int i = 0; i < 500; i++)
		start = insertHash(i, start);
	showTable(start);
	return 0;
}