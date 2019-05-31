#include "HashTable.h"
#include <iostream>
#include <string>
#include <functional>
#include <list>
#include <vector>
using namespace std;

HashTable::HashTable() {
	for (int i = 0; i < 999999999; i++) {
		vector<item> stuff; //the last digit of hash value
		m_items.push_back(stuff);
	}
}

int HashTable::push(int start, const string& newItem) {
	int value = hash<string>()(newItem);
	m_items[value / 10].push_back(item(start, newItem));
	return value;
}

bool HashTable::search(const std::string& seg, std::queue<item>& results) {
	bool yesFound = false;
	vector<item> found;
	found = m_items[hash<string>()(seg) / 10];

	//traverse the table bucket, find any matches
	for (vector<item>::iterator i = found.begin(); i != found.end(); i++) {
		if ((*i).content == seg) {
			results.push(*i);
			yesFound = true;
		}
	}
	
	return yesFound;
}