#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLtree.h"
#include "Hash.h"

int rando(int low, int high) {	//random numbers for testing
	return rand() % (high - low + 1) + low;
}

void test_hash_mil_ascending() {
	NodeH** start = NULL;

	for (int i = 0; i < 1000000; i++)
		start = insertHash(start, i);

	freeTable(start);
}

void test_hash_mil_descending() {
	NodeH** start = NULL;

	for (int i = 1000000; i > 0; i--)
		start = insertHash(start, i);

	freeTable(start);
}

void test_hash_mil_random() {
	NodeH** start = NULL;
	int temp;

	for (int i = 1000000; i > 0; i--) {
		temp = rando(0, 4000000);
		if (!searchHash(start, temp))
			start = insertHash(start, i);
	}

	freeTable(start);
}

void test_AVL_mil_ascending() {
	Node* start = NULL;

	for (int i = 0; i < 1000000; i++)
		start = insertAVL(start, i);

	del_tree(start);
}

void test_AVL_mil_descending() {
	Node* start = NULL;

	for (int i = 1000000; i > 0; i--)
		start = insertAVL(start, i);

	del_tree(start);
}

void test_AVL_mil_random() {
	Node* start = NULL;
	int temp;

	for (int i = 100; i > 0; i--) {
		temp = rando(0, 4000000);
		//printf("%d\n", temp);
		if (!searchAVL(start, temp))
			start = insertAVL(start, i);
	}

	del_tree(start);
}

int main() {
	long int currTime;

	
	printf("===MY HASH TABLE===\n");
	currTime = clock();
	test_hash_mil_ascending();
	printf("Milion ascending nodes took %d miliseconds\n", clock() - currTime);

	currTime = clock();
	test_hash_mil_descending();
	printf("Milion descending nodes took %d miliseconds\n", clock() - currTime);

	currTime = clock();
	test_hash_mil_random();
	printf("Milion random nodes took %d miliseconds\n", clock() - currTime);
	
	printf("===MY AVL TREE===\n");
	currTime = clock();
	test_AVL_mil_ascending();
	printf("Milion ascending nodes took %d miliseconds\n", clock() - currTime);


	currTime = clock();
	test_AVL_mil_descending();
	printf("Milion descending nodes took %d miliseconds\n", clock() - currTime);
	
	currTime = clock();
	test_AVL_mil_random();
	printf("Milion random nodes took %d miliseconds\n", clock() - currTime);

	return 0;
}