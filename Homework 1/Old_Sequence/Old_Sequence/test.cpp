#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

void test_Sequence();
void test_ScoreList();

int main()
{
	test_Sequence();
	test_ScoreList();
}

void test_Sequence() {
	Sequence s;
	Sequence f;

	//test empty()
	assert(s.empty());
	assert(f.empty());

	//test insert() and her return value
	assert(s.insert(0, 10) == 0);
	assert(s.insert(20) == s.size() - 1);
	assert(s.insert(30) == s.size() - 1);
	assert(s.insert(40) == s.size() - 1); //these should be inserted at the end

	//test size()
	assert(s.size() == 4);

	//test insert()'s fail report feature
	assert(s.insert(10000, 1) == -1);

	//test erase() and remove
	assert(s.erase(3) == true);
	assert(s.size() == 3);
	assert(s.remove(10) == 1);
	assert(s.size() == 2);
	assert(s.remove(100000) == 0); //remove() should be able to return 0

	//test .get()
	ItemType test = 0;
	assert(s.get(0, test) == true);
	assert(test == 20);
	assert(s.get(10000000000, test) == false);

	//test set()
	ItemType test_in = 3500;
	assert(s.set(0, test_in) == true);
	s.get(0, test);
	assert(test == 3500);
	assert(s.set(1000000, test_in) == false);

	//test find()
	assert(s.find(test_in) == 0);
	assert(s.find(30) == 1);
	assert(s.find(5000) == -1);

	//test swap()
	assert(f.size() == 0);
	s.swap(f);
	assert(f.size() == 2);
	assert(s.size() == 0);
	assert(f.find(test_in) == 0);
	assert(f.find(30) == 1);

	cerr << "Sequence class passed all tests" << endl;
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

	cerr << "ScoreList class passed all tests." << endl;
}