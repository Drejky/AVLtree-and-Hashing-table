#pragma once
typedef struct hashNode {
	int val;
	hashNode* next;
}NodeH;
typedef struct table {
	int size;
	NodeH** hash_arr;
}HT;
HT* insertHash(HT* table, int val);
NodeH* searchHash(HT* table, int val);
void freeTable(HT* table);
void showTable(HT* table);