#include "HashTable.h"
#include <iostream>
#include <string>
#include <functional>
#include <list>
#include <vector>
using namespace std;

HashTable::HashTable() {
	
	for (long long i = 0; i < 99999989; i++) {
		m_items.push_back(nullptr);
	}
}

int HashTable::push(int start, const string& newItem) {
	long long value = hash<string>()(newItem);
	if (m_items[value % 99999989] == nullptr) {
		m_items[value % 99999989] = new vector<Item>;
	}

	(*m_items[value % 99999989]).push_back(Item(start, newItem));
	return value;
}

bool HashTable::search(const std::string& seg, std::queue<Item>& results) {
	bool yesFound = false;
	vector<Item> found;
	long long fInd = hash<string>()(seg);
	fInd %= 99999989;
	if (m_items[fInd] == nullptr)
		return false;
	else
		found = *m_items[fInd];

	//traverse the table bucket, find any matches
	for (vector<Item>::iterator i = found.begin(); i != found.end(); i++) {
		if ((*i).content == seg) {
			results.push(*i);
			yesFound = true;
		}
	}
	
	return yesFound;
}