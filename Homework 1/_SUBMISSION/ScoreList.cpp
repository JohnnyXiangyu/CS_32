#include <iostream>
#include "ScoreList.h"
using namespace std;

ScoreList::ScoreList() {}

bool ScoreList::score_check(unsigned long score) {
	//just checking if the score is in reasonable range
	return (score <= 100);
}

bool ScoreList::add(unsigned long score) {
	//check score first
	if (!score_check(score) || m_sequence.size() == DEFAULT_MAX_ITEMS)
		return false;
	//insert an item at the end of sequence
	m_sequence.insert(m_sequence.size(), score);
	return true;
}

bool ScoreList::remove(unsigned long score) {
	//find the first position of target score
	//or check if it's not found
	int position = m_sequence.find(score);
	if (position == -1)
		return false;
	//erase the found item
	m_sequence.erase(position);
	return true;
}

int ScoreList::size() const {
	//return size of the sequence data member
	return m_sequence.size();
}

unsigned long ScoreList::minimum() const {
	//check if there is score
	if (this->size() == 0)
		return NO_SCORE;
	//let candidate go from max to the lowest score in the list
	unsigned long candidate = 100;
	for (int i = 0; i < this->size(); i++) {
		unsigned long temp;
		m_sequence.get(i, temp);
		//enumeration method
		if (temp < candidate)
			candidate = temp;
	}
	return candidate;
}

unsigned long ScoreList::maximum() const {
	//check if there is score
	if (this->size() == 0)
		return NO_SCORE;
	//let candidate go from max to the lowest score in the list
	unsigned long candidate = 0;
	for (int i = 0; i < this->size(); i++) {
		unsigned long temp;
		m_sequence.get(i, temp);
		//enumeration method
		if (temp > candidate)
			candidate = temp;
	}
	return candidate;
}