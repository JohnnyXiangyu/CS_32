#include "HashTable.h"
#include <iostream>
#include <string>
#include <functional>
#include <list>
#include <vector>
using namespace std;

HashTable::HashTable() :
	m_capacity(99991)
{
	
	for (int i = 0; i < m_capacity; i++) {
		m_items.push_back(nullptr);
	}
}

HashTable::~HashTable() 
{
	for (vector<vector<Item>*>::iterator i = m_items.begin(); i != m_items.end(); i++) {
		if ((*i) != nullptr)
			delete (*i);
	}
}

long long HashTable::push(int start, const string& newItem) {
	//TODO: sort the bucket by offset small to big
	if (m_items[hash<string>()(newItem) % m_capacity] == nullptr) {
		m_items[hash<string>()(newItem) % m_capacity] = new vector<Item>;
	}

	(*m_items[hash<string>()(newItem) % m_capacity]).push_back(Item(start, newItem));
	return hash<string>()(newItem);
}

bool HashTable::search(const std::string& seg, std::queue<Item>& results) {
	bool yesFound = false;
	vector<Item> found;
	int fInd = hash<string>()(seg) % m_capacity;
	if (*(m_items.begin() + fInd) == nullptr)
		return false;
	else
		found = *(*(m_items.begin() + fInd)); //this is ... kinda wierd

	//traverse the table bucket, find any matches
	for (vector<Item>::iterator i = found.begin(); i != found.end(); i++) {
		if ((*i).content == seg) {
			results.push(*i);
			yesFound = true;
		}
	}
	
	return yesFound;
}

void fillTable(std::string s, HashTable& table, int SLICELEN) {
	size_t pos = 0;
	while (pos + SLICELEN <= s.size()) {
		string temp = "";
		temp = s.substr(pos, SLICELEN);//slice the file into specified lengths
		table.push(pos, temp); //push it into the hash table

		pos ++;
	}
}