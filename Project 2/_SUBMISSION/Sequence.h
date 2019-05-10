#ifndef SEQUENCE
#define SEQUENCE 1

#include <string>

using ItemType = std::string; //type-alias

class Sequence
{
public:
	Sequence();
	//copy constructor, destructor, operator
	~Sequence();
	Sequence(const Sequence& other);
	Sequence& operator=(const Sequence& other);

	bool empty() const;
	int size() const;
	int insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);

private:
	struct Node {
		ItemType data;
		Node* previous;
		Node* next;
	};

	int m_size;
	Node* m_items;

	//tool method of copying all elements from other_items and return the first
	//item of new list. when called in driver
	Node* full_copy(Node* other_items, Node* this_items = nullptr);

	//tool method for checking position argument
	bool check_pos(int pos) const;

	//tool method to locate a certain node in the list
	Node* locate(int pos) const;

};


int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

inline
bool Sequence::empty() const {
	return (m_size == 0);
}

inline
int Sequence::size() const {
	return m_size;
}

inline
bool Sequence::check_pos(int pos) const {
	return (pos >= 0 && pos <= m_size);
}

inline
Sequence::Node* Sequence::locate(int pos) const {
	Node* target = m_items;
	for (int i = 1; i <= pos; i++)
		target = target->next;
	return target;
}

#endif