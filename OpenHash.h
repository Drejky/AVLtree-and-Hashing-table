#pragma once
struct DataItem {
	int data;
	int key;
};

struct DataItem *search(int key);
void insert(int key, int data);
struct DataItem* Delete(struct DataItem* item);
void free_for_test();