#pragma once
typedef struct hashNode {
	int val;
	hashNode* next;
}NodeH;
NodeH** insertHash(NodeH** table, int val);
NodeH* searchHash(NodeH** table, int val);
void freeTable(NodeH** table);
void showTable(NodeH** table);