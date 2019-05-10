#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void normal_Sequence_test();
void subsequence_tests();
void interleave_tests();
void extreme_pos_tests();
//void newTest();

int main() {
	normal_Sequence_test();
	subsequence_tests();
	interleave_tests();
	extreme_pos_tests();
	//newTest();

	cerr << "Pass." << endl;
	return 0;
}



void normal_Sequence_test() {
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
	assert(s.get(10000000, test) == false);

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
	s.swap(f); //TODO
	assert(f.size() == 2); //TODO
	assert(s.size() == 0);
	assert(f.find(test_in) == 0);
	assert(f.find(30) == 1);

	cerr << "Sequence class passed all tests" << endl;
}

void subsequence_tests() {
	//normal mode
	Sequence s1, s2;
	for (int i = 10; i <= 100; i += 10)
		s1.insert(i);
	assert(s1.size() == 10);
	for (int i = 40; i <= 70; i += 10)
		s2.insert(i);
	assert(s2.size() == 4);
	assert(subsequence(s1, s2) == 3);

	//lots of elements
	Sequence s3, s4;
	for (int i = 1; i <= 100; i += 1)
		s3.insert(i);
	assert(s3.size() == 100);
	for (int i = 40; i <= 70; i += 1)
		s4.insert(i);
	assert(s4.size() == 31);
	assert(subsequence(s3, s4) == 39);

	//empty seq2
	Sequence s5;
	assert(subsequence(s3, s5) == -1);

	//seq1 too short
	Sequence s6;
	for (int i = 1; i <= 10; i++)
		s6.insert(i);
	assert(s6.size() == 10);
	assert(subsequence(s6, s3) == -1);

	//not match
	assert(subsequence(s3, s1) == -1);


	cerr << "Subsequence passes all tests." << endl;
}

void interleave_tests() {
	//m == n
	Sequence s1, s2, s3, s4;
	ItemType item1, item2;
	for (int i = 1; i <= 100; i++) {
		s1.insert(i-1, i);
		s2.insert(i-1, i*10);
		s3.insert(2 * i - 2, i);
		s3.insert(2 * i - 1, i * 10);
	}
	interleave(s1, s2, s4);
	assert(s4.size() == s1.size() + s2.size());
	for (int i = 0; i < 200; i++) {
		s3.get(i, item1);
		s4.get(i, item2);
		assert(item1 == item2);
	}

	//m < n
	Sequence s5 = s2;
	Sequence s6 = s3;
	for (int i = 1; i <= 10; i++) {
		s5.insert(s5.size(), i * 100);
		s6.insert(s6.size(), i * 100);
	}
	interleave(s1, s5, s4);
	assert(s4.size() == s6.size());
	for (int i = 0; i < 210; i++) {
		s6.get(i, item1);
		s4.get(i, item2);
		assert(item1 == item2);
	}

	//m > n
	s5 = s1;
	s6 = s3;
	for (int i = 1; i <= 10; i++) {
		s5.insert(s5.size(), i * 100);
		s6.insert(s6.size(), i * 100);
	}
	interleave(s5, s2, s4);
	assert(s4.size() == s6.size());
	for (int i = 0; i < 210; i++) {
		s6.get(i, item1);
		s4.get(i, item2);
		assert(item1 == item2);
	}

	//m = 0
	int steps = s5.size();
	for (int i = 0; i < steps; i++)
		s5.erase(0);
	interleave(s5, s2, s4);
	assert(s4.size() == s2.size());
	for (int i = 0; i < s2.size(); i++) {
		s2.get(i, item1);
		s4.get(i, item2);
		assert(item1 == item2);
	}

	//n = 0
	interleave(s1, s5, s4);
	assert(s4.size() == s1.size());
	for (int i = 0; i < s1.size(); i++) {
		s1.get(i, item1);
		s4.get(i, item2);
		assert(item1 == item2);
	}

	//both are 0 and aliasing parameter
	interleave(s5, s5, s4);
	assert(s4.size() == 0);
	assert(s4.empty());

	//normal aliasing
	interleave(s1, s1, s4);
	ItemType item3;
	assert(s4.size() == s1.size()*2);
	for (int i = 0; i < s1.size(); i++) {
		s1.get(i, item1);
		s4.get(i*2, item2);
		s4.get(i * 2 + 1, item3);
		assert(item1 == item2);
		assert(item1 == item3);
	}

	//super-aliasing
	Sequence temp_aliasing = s1;
	assert(!s1.empty());
	interleave(s1, s1, s1);
	ItemType item4, item5, item6;
	assert(s1.size() == temp_aliasing.size() * 2);
	for (int i = 0; i < s1.size(); i++) {
		temp_aliasing.get(i, item4);
		s1.get(i * 2, item5);
		s1.get(i * 2 + 1, item6);
		assert(item4 == item5);
		assert(item4 == item6);
	}

	s1 = s4;

	cerr << "Interleave passes all tests." << endl;
}


void extreme_pos_tests() {
	//insert empty
	Sequence s1, s0;
	s1.insert(0, 10);
	assert(s1.size() == 1);

	//insert end
	s1 = s0;
	for (int i = 0; i < 5; i++)
		assert(s1.insert(i) == s1.size() - 1);
	assert(s1.insert(s1.size(), 10) == s1.size() - 1);

	//insert head and erase end
	s1 = s0;
	for (int i = 5; i > 0; i--)
		assert(s1.insert(i) == 0);
	assert(s1.insert(0, 10) == 0);
	for (int i = 1; i <= 6; i++)
		assert(s1.erase(s1.size() - 1));

	//erase empty
	assert(!s0.erase(0));

	//get empty and set empty
	s1 = s0;
	ItemType temp = 0;
	assert(!s1.get(0, temp));
	assert(temp == 0);
	assert(!s1.set(0, temp));

	//remove empty
	s1 = s0;
	assert(s1.remove(0) == 0);

	//find empty
	s1 = s0;
	assert(s1.find(0) == -1);

	//swap empty
	//s1.swap(s0);
	assert(s1.empty());
	assert(s0.empty());
	
	cerr << "Sequence class passed all expreme-position tests." << endl;
}


/*
void newTest(){
	//testing copy constructor and insert
	Sequence first, second, third, fourth;
	assert(first.insert("1") == 0); // insert in empty
	assert(first.insert("2") == 1); // insert at end
	assert(first.insert("0") == 0); // insert at beginning
	second = first;
	assert(second.find("0") == 0);   // test copy constructor
	assert(second.find("1") == 1);
	assert(second.find("2") == 2);

	//testing = and insert
	assert(third.insert(2, "z") == -1); // insert in empty
	assert(third.insert(0, "z") == 0);
	assert(third.insert(2, "y") == -1);  // insert out of range
	assert(third.insert(-1, "y") == -1);
	assert(third.insert(1, "y") == 1);  // insert at end
	assert(third.insert(2, "x") == 2);
	first = third;   // assignment operator
	assert(first.find("z") == 0);
	assert(first.find("y") == 1);
	assert(first.find("x") == 2);

	//testing empty()
	assert(fourth.empty());
	assert(!first.empty());
	assert(!second.empty());
	assert(!third.empty());

	//testing erase and find
	assert(!fourth.erase(0));  // erase empty
	assert(first.erase(0));   // erase the first
	assert(first.find("y") == 0);
	assert(first.find("x") == 1);
	assert(first.find("z") == -1);
	assert(first.erase(1));  // erase the end
	assert(first.find("y") == 0);
	assert(first.find("x") == -1);
	assert(first.erase(0));  // erase the only node
	assert(first.empty());
	assert(first.size() == 0);


	//testing remove and erase and size
	assert(second.insert(2, "0") == 2);
	assert(second.size() == 4);  //test size
	assert(second.insert(4, "0") == 4);
	assert(second.size() == 5); // test size
	assert(second.remove("0") == 3);  // remove the head, the end and the middle
	assert(second.size() == 2); // test size
	assert(second.find("0") == -1);
	assert(second.find("1") == 0);
	assert(second.find("2") == 1);
	assert(second.insert("3") == 2);
	assert(second.erase(1));  // erase the middle
	assert(second.find("1") == 0);
	assert(second.find("2") == -1);
	assert(second.find("3") == 1); //second: "1" "3" first and fourth empty, third"z" "y" "x"

//testing get and set
	ItemType value;
	assert(!first.get(0, value)); // test empty
	assert(third.get(0, value));  // test first node
	assert(value == "z");
	assert(third.get(1, value)); // test middle node
	assert(value == "y");
	assert(third.get(2, value));  // test end node
	assert(value == "x");
	assert(!first.set(0, value)); // test empty
	assert(first.empty());
	assert(!third.get(-1, value)); // test out of range
	assert(value == "x");
	assert(!third.get(3, value));
	assert(value == "x");
	value = "2";
	assert(second.set(1, value));
	assert(second.find(value) == 1);

	//testing subsequence and interleave
	assert(subsequence(second, third) == -1);  // seq2 larger than seq1
	assert(subsequence(third, second) == -1); // can¡¯t find subset
	assert(subsequence(third, first) == -1); // seq2 empty
	first = second;
	first.insert("3");
	interleave(second, third, fourth);   // test interleave
	assert(fourth.find("1") == 0);
	assert(fourth.find("z") == 1);
	assert(fourth.find("2") == 2);
	assert(fourth.find("y") == 3);
	assert(fourth.find("x") == 4);
	interleave(third, second, fourth);
	assert(fourth.find("z") == 0);
	assert(fourth.find("1") == 1);
	assert(fourth.find("y") == 2);
	assert(fourth.find("2") == 3);
	assert(fourth.find("x") == 4);
	interleave(first, second, second);// second 1 1 2 2 3 first 1 2 3
	assert(subsequence(second, first) == -1); // test subsequence
	first.remove("1");
	assert(subsequence(second, first) == 3);
	assert(subsequence(first, second) == -1);
	second.set(0, "2");
	second.set(1, "3");
	assert(subsequence(second, first) == 0);

	cerr << "New tests pass." << endl; 
}
*/