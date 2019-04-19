#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
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

	return 0;
}