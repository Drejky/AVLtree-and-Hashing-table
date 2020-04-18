#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLtree.h"
#include "Hash.h"
#include "RBtree.h"
#include "OpenHash.h"


int rando(int lim) {	//random numbers for testing
	return ((long long int)rand() * lim/RAND_MAX);
}

void test_hash_ascending(int lim) {
	HT* start = NULL;
	long int time = clock();
	NodeH* temp;

	for (int i = lim / 2 - lim; i < lim / 2; i++)
		start = insertHash(start, i);

	printf("Inserting %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = lim / 2 - lim; i < lim / 2; i++)
		temp = searchHash(start, i);
	
	printf("Searching %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);

	freeTable(start);
}

void test_hash_descending(int lim) {
	HT* start = NULL;
	long int time = clock();
	NodeH* temp;

	for (int i = lim/2 ; i >= lim/2 - lim; i--)
		start = insertHash(start, i);

	printf("Inserting %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = lim / 2; i >= lim / 2 - lim; i--)
		temp = searchHash(start, i);

	printf("Searching %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);

	freeTable(start);
}

void test_hash_random(int lim) {
	HT* start = NULL;
	int temp;
	long int time = clock();

	for (int i = lim; i > 0; i--) {
		temp = rando(4*lim);
		if (!searchHash(start, temp))
			start = insertHash(start, i);
		else
			i++;
	}
	printf("Inserting %d random nodes took %d miliseconds.\n", lim, clock() - time);

	freeTable(start);
}

void test_AVL_ascending(int lim) {
	NodeA* start = NULL;
	long int time = clock();

	for (int i = lim / 2 - lim; i < lim / 2; i++)
		start = insertAVL(start, i);
	printf("Inserting %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = lim / 2 - lim; i < lim / 2; i++)
		searchAVL(start, i);
	printf("Searching %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);

	del_tree(start);
}

void test_AVL_descending(int lim) {
	NodeA* start = NULL;
	long int time = clock();

	for (int i = lim / 2; i >= lim / 2 - lim; i--)
		start = insertAVL(start, i);
	printf("Inserting %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = lim / 2; i >= lim / 2 - lim; i--)
		searchAVL(start, i);
	printf("Searching %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);

	del_tree(start);
}

void test_AVL_random(int lim) {
	NodeA* start = NULL;
	int temp;
	long int time = clock();

	for (int i = lim; i > 0; i--) {
		temp = rando(4*lim);
		if (!searchAVL(start, temp))
			start = insertAVL(start, i);
		else
			i++;
	}
	printf("Inserting %d random nodes took %d miliseconds.\n", lim, clock() - time);

	del_tree(start);
}

void test_RB_ascending(int lim) {
	long int time = clock();
	struct Node* RBT = NULL;

	for (int i = lim/2 - lim; i < lim/2; i++)
		RBT = RB_insert(RBT, i);
	printf("Inserting %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	struct Node* x;
	for (int i = lim / 2 - lim; i < lim / 2; i++)
		x = BST_search(RBT, i);
	printf("Searching %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);

}

void test_RB_descending(int lim) {
	long int time = clock();
	struct Node* RBT = NULL;

	for (int i = lim / 2; i > lim / 2 - lim; i--)
		RBT = RB_insert(RBT, i);
	printf("Inserting %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	struct Node* x;
	for (int i = lim / 2; i > lim / 2 - lim; i--)
		x = BST_search(RBT, i);
	printf("Searching %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);

}

void test_RB_random(int lim) {
	int temp;
	long int time = clock();
	struct Node* start = NULL;

	for (int i = lim; i > 0; i--) {
		temp = rando(4 * lim);
		if (!BST_search(start, temp))
			start = RB_insert(start, i);
		else
			i++;
	}
	printf("Inserting %d random nodes took %d miliseconds.\n", lim, clock() - time);
}

void test_OH_ascending(int lim) {
	long int time = clock();
	struct DataItem *temp;

	for (int i = 0; i < lim ; i++)
		insert(i, 5);

	printf("Inserting %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = 0; i < lim; i++)
		temp = search(i);

	printf("Searching %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);

	free_for_test();
}

void test_OH_descending(int lim) {
	long int time = clock();
	struct DataItem *temp;

	for (int i = lim; i > 0; i--)
		insert(i, 5);

	printf("Inserting %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = lim; i > 0; i--)
		temp = search(i);

	printf("Searching %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);

	free_for_test();
}

void test_OH_random(int lim) {
	long int time = clock();
	int temp;

	for (int i = 0; i < lim; i++) {
		temp = rando(4 * lim);
		if (!search(temp))
			insert(temp, 5);
		else
			i++;
	}
	printf("Inserting %d random nodes took %d miliseconds.\n", lim, clock() - time);

	free_for_test();
}

void test_hash_addshow(int lim) {
	HT* start = NULL;
	int temp;
	for (int i = 0; i < lim; i++) {
		temp = rando(4 * lim);
		if (!searchHash(start, temp))
			start = insertHash(start, temp);
		else
			i--;
	}
	showTable(start);
}

int main() {
	long int currTime;
	srand(18042020);
	
	printf("===MY AVL TREE===\n");
	test_AVL_ascending(1000000);
	test_AVL_descending(1000000);
	test_AVL_random(1000000);
	printf("\n");

	printf("===CITED RB TREE===\n");
	test_RB_ascending(1000000);
	test_RB_descending(1000000);
	test_RB_random(1000000);
	printf("\n");
	
	printf("===MY HASH TABLE===\n");
	test_hash_ascending(1000000);
	test_hash_descending(1000000);
	test_hash_random(1000000);
	printf("\n");
	
	printf("===CITED OPEN HASH TABLE===\n");
	test_OH_ascending(1000000);
	test_OH_descending(1000000);
	
	test_OH_random(1000000);
	printf("\n");
	
	return 0;
}
