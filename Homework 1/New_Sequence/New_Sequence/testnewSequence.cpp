#include "newScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

void test_ScoreList();

int main() {
	Sequence a(1000);   // a can hold at most 1000 items
	Sequence b(5);      // b can hold at most 5 items
	Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
	
	ItemType v = 1000;

	// No failures inserting 5 items into b
	for (int k = 0; k < 5; k++)
		assert(b.insert(v) != -1);

	// Failure if we try to insert a sixth item into b
	assert(b.insert(v) == -1);

	// When two Sequences' contents are swapped, their capacities are
	// swapped as well:
	a.swap(b);
	assert(a.insert(v) == -1 && b.insert(v) != -1);

	cerr << "newSequence class passed all tests." << endl;

	test_ScoreList();

	return 0;
}

void test_ScoreList() {
	ScoreList list;

	//test constructor
	assert(list.size() == 0);

	//test insert() and size()
	assert(list.add(10) == true);
	assert(list.add(100) == true);
	assert(list.add(95) == true);
	assert(list.add(80) == true);
	assert(list.size() == 4);
	assert(list.add(100) == true);
	assert(list.add(10000) == false);

	//test remove()
	assert(list.remove(100) == true);
	assert(list.remove(100) == true);
	assert(list.size() == 3);
	assert(list.remove(10000) == false);
	assert(list.remove(90) == false);

	//test minimum() and minimum()
	assert(list.minimum() == 10);
	assert(list.maximum() == 95);

	list.remove(10);
	list.remove(95);
	list.remove(80);

	assert(list.size() == 0);
	assert(list.maximum() == NO_SCORE);
	assert(list.minimum() == NO_SCORE);

	cerr << "ScoreList clss passed all tests." << endl;
}