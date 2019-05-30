#ifndef HASHTABLE
#define HASHTABLE 1
#include <string>
#include <vector>

class HashTable {
public:
	HashTable();
	//~HashTable();
	int push(int start, std::string newItem);
	//push the given segment into hash table, and return the hash value of this segment

private:
	struct item {
		item(int length, int start, std::string data):
			len(length), offset(start), content(data)
		{}
		int len;
		int offset;
		std::string content;
	};
	std::vector<std::vector<item>> m_items;
};


#endif // !HASHTABLE