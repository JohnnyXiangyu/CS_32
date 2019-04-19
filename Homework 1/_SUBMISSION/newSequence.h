#ifndef SEQUENCE
#define SEQUENCE 1

#include <iostream>
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Sequence
{
public:
	//the new constructor that takes a length parameter
	Sequence(int length = DEFAULT_MAX_ITEMS);
	//the destructor that deletes the array
	~Sequence();

	//the new copy constructor
	Sequence(const Sequence& other);
	//the new assignment operator
	Sequence& operator=(const Sequence& other);

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
	int m_size;
	int m_max;
	ItemType* m_items;
	//tool methods
	bool range_check(int pos) const;
	void move(int start_pos, int steps);
};


#endif