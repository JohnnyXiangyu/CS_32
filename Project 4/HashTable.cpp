#include "HashTable.h"
#include <iostream>
#include <string>
#include <functional>
using namespace std;

HashTable::HashTable() {
	for (int i = 0; i < 999999999; i++) {
		vector<item> stuff; //the last digit of hash value
		m_items.push_back(stuff);
	}
}

int HashTable::push(int start, string newItem) {
	int value = hash<string>()(newItem);
	m_items[value / 10].push_back(item(newItem.length(), start, newItem));
	return value;
}