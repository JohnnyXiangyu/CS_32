#include <iostream>
#include <string>
#include "newSequence.h"
using namespace std;


Sequence::Sequence(int length)
{
	if (length < 0)
		exit(1);
	else {
		m_size = 0;
		m_max = length;
		m_items = new ItemType[m_max];
	}
}

Sequence::~Sequence() {
	delete[] m_items;
	//that must be the only thing dynamically allocated
}

Sequence::Sequence(const Sequence& other) :
	m_size(other.m_size), m_max(other.m_max), m_items(new ItemType[other.m_max])
{
	//copy everything into the new array's available part
	for (int i = 0; i < m_size; i++) {
		this->m_items[i] = other.m_items[i];
	}
}

Sequence& Sequence::operator=(const Sequence& other) {
	if (this != &other) {
		//free old array
		delete[] this->m_items;
		//some properties
		this->m_max = other.m_max;
		this->m_size = other.m_size;
		//re-allocate and copy
		this->m_items = new ItemType[this->m_max];
		for (int i = 0; i < this->m_size; i++)
			this->m_items[i] = other.m_items[i];
	}

	return *this;
}

//tool method that saves some typing (checking range of pos)
bool Sequence::range_check(int pos) const {
	if (pos >= 0 && pos <= m_size)
		return true;
	else
		return false;
}

//tool method (moving items)
void Sequence::move(int start_pos, int steps) {
	if (steps < m_size) { //range_check has already checked 
		                  //that pos would be reasonable
		if (steps > 0) {
			for (int i = m_size - 1; i >= start_pos; i--) {
				m_items[i + steps] = m_items[i];
			}
		}
		else {
			for (int i = start_pos; i < m_size; i++) {
				m_items[i + steps] = m_items[i];
			}
		}
	}
	//update m_size
	m_size += steps;
}

bool Sequence::empty() const {
	return (m_size == 0);
}

int Sequence::size() const {
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value) {
	if (!range_check(pos)) //check if the pos is reasonable 
		return -1;
	if (pos == this->m_max || m_size == this->m_max) //3-4 only, see if the sequence is full already
		return -1;
	//since the original sequence, from pos will all be moved one step
	//let's first move everything right, then insert
	move(pos, 1);
	m_items[pos] = value;
	return pos;
}

int Sequence::insert(const ItemType& value) {
	if (m_size == this->m_max)
		return -1;
	int p = 0;
	//so that p either becomes the pos where value <= m_items[p]
			  //or it becomes m_size, the end of sequence
	while (p < m_size && value > m_items[p]) {
		p++;
	}
	//insert value
	insert(p, value);
	return p;
}

bool Sequence::erase(int pos) {
	if (!range_check(pos) || pos >= m_size)
		return false;
	//move everything on the right side leftward
	if (pos == m_size - 1) {
		//removeing the last item don't require moving anything
		m_size--;
	}
	else {
		//need to move everything leftward
		move(pos + 1, -1);
	}
	
	return true;
}

int Sequence::remove(const ItemType& value) {
	int times = 0;
	int i = 0;
	//run through the whole list
	while (i < m_size) {
		if (value == m_items[i]) {
			//every time an equal is found
			erase(i); //erase this position
			times++; //and increment times
		}
		i++;
	}
	return times;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (!range_check(pos))
		return false;
	value = m_items[pos];
	return true;
}

bool Sequence::set(int pos, ItemType& value) {
	if (!range_check(pos))
		return false;
	m_items[pos] = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	for (int i = 0; i < m_size; i++) {
		//if found
		if (value == m_items[i])
			return i;
	}

	//if not found
	return -1;
}

void Sequence::swap(Sequence& other) {
	//this is the dynamic version
	//and should not loop
	//so im gonna just exchange the addresses
	ItemType* temp;
	int temp_size;
	int temp_max;

	temp_size = this->m_size;
	this->m_size = other.m_size;
	other.m_size = temp_size;

	temp_max = this->m_max;
	this->m_max = other.m_max;
	other.m_max = temp_max;

	//now exchange the addresses
	temp = this->m_items;
	this->m_items = other.m_items;
	other.m_items = temp;
}