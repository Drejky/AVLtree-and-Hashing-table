#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLtree.h"
#include "Hash.h"

int rando(int lim) {	//random numbers for testing
	return ((long long int)rand() * lim/RAND_MAX);
}

void test_hash_ascending(int lim) {
	HT* start = NULL;
	long int time = clock();
	NodeH* temp;

	for (int i = 0; i < lim; i++)
		start = insertHash(start, i);

	printf("Inserting %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = 0; i < lim; i++) 
		temp = searchHash(start, i);
	
	printf("Searching %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);

	freeTable(start);
}

void test_hash_descending(int lim) {
	HT* start = NULL;
	long int time = clock();
	NodeH* temp;

	for (int i = lim; i >= 0; i--)
		start = insertHash(start, i);

	printf("Inserting %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = lim; i >= 0; i--)
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
	Node* start = NULL;
	long int time = clock();

	for (int i = 0; i < lim; i++)
		start = insertAVL(start, i);
	printf("Inserting %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = 0; i < lim; i++)
		searchAVL(start, i);
	printf("Searching %d nodes in ascending order took %d miliseconds.\n", lim, clock() - time);

	del_tree(start);
}

void test_AVL_descending(int lim) {
	Node* start = NULL;
	long int time = clock();

	for (int i = lim; i >= 0; i--)
		start = insertAVL(start, i);
	printf("Inserting %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);
	time = clock();

	for (int i = lim; i >= 0; i--)
		searchAVL(start, i);
	printf("Searching %d nodes in descending order took %d miliseconds.\n", lim, clock() - time);

	del_tree(start);
}

void test_AVL_random(int lim) {
	Node* start = NULL;
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

int main() {
	long int currTime;

	
	printf("===MY HASH TABLE===\n");
	test_hash_ascending(1000000);
	test_hash_descending(1000000);
	test_hash_random(1000000);
	
	
	printf("===MY AVL TREE===\n");
	test_AVL_ascending(1000000);
	test_AVL_descending(1000000);
	test_AVL_random(1000000);
	
	
	
	
	return 0;
}