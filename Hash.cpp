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

NodeH** insertHash(int val, NodeH** table) {
	if (!table) {
		table = (NodeH**)calloc(3, sizeof(NodeH*));
		table[0] = (NodeH*)malloc(sizeof(NodeH));
		table[0]->val = 2;
	}

	int tSize = table[0]->val;
	int index = hash(val, tSize) + 1;
	NodeH* curr;


	curr = table[index];
	if (!curr)
		table[index] = newNodeH(val);
	else {
		while (curr->next)
			curr = curr->next;
		curr->next = newNodeH(val);
	}

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
	
	for (int i = 4526; i < 4557; i++)
		start = insertHash(i, start);
	showTable(start);
	return 0;
}