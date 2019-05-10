#include "Sequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence() :
	m_size(0), m_items(nullptr)
{}

Sequence::~Sequence() {
	while (!empty())
		erase(0);
}


Sequence::Node* Sequence::full_copy(Node* source, Node* target) {
	//TODO: where should default parameters be put?
	//the recursive function that copies one list to another
	if (source != nullptr) {
		Node* newGuy = new Node;
		newGuy->data = source->data;
		newGuy->previous = target;
		newGuy->next = full_copy(source->next, newGuy);
		return newGuy; //return the first element of the created list
	}
	else
		return nullptr;
}

Sequence::Sequence(const Sequence& other) {
	m_size = other.m_size;
	m_items = full_copy(other.m_items);
}

Sequence& Sequence::operator=(const Sequence& other) {
	//assignment operator
	//TODO: what happens the LHS is empty???
	if (this != &other) {
		while (!empty())
			erase(0); //free up the original list in this
		m_size = other.m_size; //copy the size
		m_items = full_copy(other.m_items);
	}

	return *this;
}

int Sequence::insert(int pos, const ItemType& value) {
	//find the position, create new Node, and reconnect the prev and nexts
	if (!check_pos(pos))
		//check the pos argument
		return -1;

	//create the new guy
	Node* newGuy = new Node;
	newGuy->data = value;

	if (m_size == 0) {
		newGuy->previous = nullptr;
		newGuy->next = nullptr;
		m_items = newGuy;

		m_size++;
		return pos;
	}

	if (pos == m_size) {
		//if we are adding one at the end
		newGuy->next = nullptr;
		Node* ex_end = locate(m_size-1);
		if (ex_end != nullptr)
			ex_end->next = newGuy;
		else
			m_items = newGuy;
		newGuy->previous = ex_end;

		m_size++;
		return pos;
	}
	
	//if we are adding before the end
	Node* target = locate(pos);
	Node* prev = target->previous; 

	//link him or her into the original link
	newGuy->previous = prev;
	//cant do this statement if prev is nullptr
	if (prev != nullptr)
		prev->next = newGuy;
	else
		m_items = newGuy;
	newGuy->next = target;
	target->previous = newGuy;

	//increment size
	m_size++;

	return pos;
}

int Sequence::insert(const ItemType& value) {
	//no -1 should be returned
	Node* target = m_items;
	int i = 0;
	while (target != nullptr && target->data < value) {
		//go through the list for a value <= item position
		target = target->next;
		i++;
	}

	//in case there's no match
	if (target == nullptr)
		return insert(m_size, value);

	//or just do normal job
	else
		return insert(i, value);
}

bool Sequence::erase(int pos) {
	//erase one element and reconnect it's before and after
	//see if pos is reasonable and less than size
	//or the set is empty
	if (!check_pos(pos) || pos >= m_size || m_size == 0)
		return false;

	//locate the cut points
	Node* target = locate(pos);
	//relink
	//TODO
	if (target->next != nullptr)
		target->next->previous = target->previous;
	if (target->previous != nullptr)
		target->previous->next = target->next;
	else
		m_items = target->next;

	//delete target
	delete target;
	m_size--;

	return true;
}

int Sequence::remove(const ItemType& value) {
	//remove all items with this value
	int count = 0;
	Node* target = m_items;
	
	//when it's empty
	if (m_size == 0)
		return 0;

	int curser = 0;

	while (target != nullptr) {
		if (target->data == value) {
			erase(curser);
			target = locate(curser);
			count++;
		}
		else {
			target = target->next;
			curser++;
		}
	}

	return count;
}

bool Sequence::get(int pos, ItemType& value) const {
	//check the validity of pos
	if (!check_pos(pos) || pos == m_size)
		return false;
	
	Node* target = locate(pos);
	value = target->data;
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	//check pos
	if (!check_pos(pos) || pos == size())
		return false;
	//set value
	Node* target = locate(pos);
	target->data = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	//first go through the whole list
	Node* target = m_items;
	int i = 0;
	while (target != nullptr && target->data != value) {
		//go through the list for a value <= item position
		target = target->next;
		i++;
	}
	//if we didn't find it
	if (target == nullptr)
		return -1;
	//else we find it
	else
		return i;
}

void Sequence::swap(Sequence& other) {
	//swap sizes, then swap items
	int temp;
	Node* temp_items;
	temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;

	temp_items = m_items;
	m_items = other.m_items;
	other.m_items = temp_items;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
	//checking if seq2 is a sub_sequence of seq1
	//start with checking their lengths
	if (seq1.empty() || seq2.size() > seq1.size() ||seq2.empty())
		return -1;

	//look for seq2's pos0 in seq1
	ItemType target;
	seq2.get(0, target);
	for (int i = 0; i <= (seq1.size() - seq2.size()); i++) {
		ItemType current;
		seq1.get(i, current);
		if (current == target) {
			int flag = 0;
			for (int j = i + 1; j < i + seq2.size(); j++) {
				ItemType seq2_next, seq1_next;
				seq2.get(j - i, seq2_next);
				seq1.get(j, seq1_next);
				if (seq2_next == seq1_next)
					flag = j;
				else {
					flag = -1;
					break;
				}
			}//after this loop we'll know if seq2 is found by reading flag
			if (flag != -1)
				return i;
		}
	}
	//after finish, it's a "not found" situation
	return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	//in case of aliasing, copies should be made of seq1 and seq2
	//and I do want to save some memory space
	const Sequence* seq1_;
	const Sequence* seq2_;
	seq1_ = &seq1;
	seq2_ = &seq2;
	if (&seq1 == &result) {
		seq1_ = new Sequence(seq1);
	}
	if (&seq2 == &result) {
		seq2_ = new Sequence(seq2);
	}

	//clear the result sequence
	//thinking of using a for loop and erase method
	if (!result.empty()) {
		while(!result.empty())
			result.erase(0);
	}

	//if there's nothing passed into
	if (seq1_->empty() && seq2_->empty())
		return;

	//if one of them is empty (two scenarios)
	//just copy and go
	if (seq1_->empty() && !seq2_->empty()) {
		result = *seq2_;
		return;
	}
	else if (seq2_->empty() && !seq1_->empty()) {
		result = *seq1_;
		return;
	}

	//finally: if there're stff to handle
	//I don't want to use two blocks of similar code, so:
	const Sequence* longer;
	//TODO: does this trick work?
	if (seq1_->size() >= seq2_->size()) {
		longer = seq1_;
	}
	else {
		longer = seq2_;
	}
	//go through shared length
	int i = 0;
	int result_pos = 0;
	for (; i < longer->size(); i++) {
		ItemType temp;
		if (seq1_->get(i, temp) != false) {
			result.insert(result_pos, temp);
			result_pos++;
		}
		if (seq2_->get(i, temp) != false) {
			result.insert(result_pos, temp);
			result_pos++;
		}
	}

	if (seq1_ != &seq1)
		delete seq1_;
	if (seq2_ != &seq2)
		delete seq2_;
}