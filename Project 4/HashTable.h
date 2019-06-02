#ifndef HASHTABLE
#define HASHTABLE 1
#include <string>
#include <vector>
#include <queue>
#include "Utilities.h"


class HashTable {
public:
	HashTable();
	~HashTable(); //the table only contains pointers to vectors
	//push the given segment into hash table, and return the hash value of this segment
	long long push(int start, const std::string& newItem);
	bool search(const std::string& seg, std::queue<Item>& results);

private:
	std::vector<std::vector<Item>*> m_items;
	long long m_capacity;
};

void fillTable(std::string s, HashTable& table, int SLICELEN);


#endif // !HASHTABLE