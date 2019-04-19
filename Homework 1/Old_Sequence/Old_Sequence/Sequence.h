#ifndef SEQUENCE
#define SEQUENCE 1

#include <iostream>
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Sequence
{
public:
	Sequence();
	bool empty() const;
	int size() const;
	int insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);

private:
	ItemType m_items[DEFAULT_MAX_ITEMS];
	int m_size;
	int m_max;
	//tool methods
	bool range_check(int pos) const;
	void move(int start_pos, int steps);
};


#endif