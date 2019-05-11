#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int cc = 0;

bool somePredicate(string s)
{
	//return s.size() == 4;
	return s.empty();
}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
	//terminate condition
	if (n > 0) {
		if (!somePredicate(a[n - 1]))
			return false;
		else if (!allTrue(a, n - 1))
			return false;
		//else
			//return true;
	}
	return true;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n > 0) {
		int count = 0;
		if (!somePredicate(a[n - 1]))
			count++;
		return (countFalse(a, n - 1) + count);
	}
	else
		return 0;
}

// Return the subscript of the first element in the array which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n > 0) {
		int result = firstFalse(a, n - 1);
		if (result == -1) {
			if (!somePredicate(a[n - 1]))
				return n - 1;
			else
				return -1;
		}
		else
			return result;
	}
	else
		return -1;
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] fur all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
	//c++; //comment out upon submission

	if (n <= 0)
		return -1;

	if (n == 1)
		return 0;
	else {
		int result = indexOfLeast(a, n - 1);
		cc++;
		if (a[n - 1] < a[result])
			return n - 1;
		else
			return result;
	}
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{

	//TODO: in case of a false result, an extra runtime presents
	if (n2 <= 0)
		return true;
	if (n1 <= 0 || n1 < n2)
		return false;

	cc++;
	if (a2[n2 - 1] != a1[n1 - 1])
		return includes(a1, n1 - 1, a2, n2);
	else
		return includes(a1, n1 -1, a2, n2 - 1);
}


void includesTest() {
	string a1[7] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
	string a2[3] = { "kyle", "cartman", "cartman" };
	string a3[3] = { "kyle", "kenny", "butters" };
	string a4[3] = { "kyle", "butters", "kenny" };
	string a5[3] = { "stan", "kenny", "kenny" };

	assert(includes(a1, 7, a2, 3));
	assert(cc <= 7);
	cc = 0;
	assert(includes(a1, 7, a3, 3));
	assert(cc <= 7);
	cc = 0;
	assert(!includes(a1, 7, a4, 3));
	assert(cc <= 7);
	cc = 0;
	assert(!includes(a1, 7, a5, 3));
	assert(cc <= 7);
	cc = 0;
	assert(!includes(a1, 0, a5, 3));
	assert(cc <= 0);
	cc = 0;
	assert(includes(a1, 0, a5, 0));
	assert(cc <= 0);
	cc = 0;
	for (int i = 0; i <= 7; i++) {
		assert(includes(a1, 7, a1, i));
		assert(cc <= 7);
		cc = 0;
	}

	string a[] = { "","","","","" };
	string b[] = { "1", "2", "3" };
	string c[] = { "2", "1", "3","1", "2", "3","" };

	assert(includes(a, 0, b, 0));
	assert(cc <= 0);
	cc = 0;
	assert(includes(c, 7, a, 1));
	assert(cc <= 7);
	cc = 0;
	for (int i = 0; i < 6; i++)
	{
		assert(!includes(c, i, b, 3));
		assert(cc <= i);
		cc = 0;
	}
	assert(includes(c, 6, b, 3));
	assert(cc <= 6);
	cc = 0;
	for (int i = 2; i < 8; i++)
	{
		assert(includes(c, i, b, 1));
		assert(cc <= i);
		cc = 0;
	}

	cout << "includes() passes all test cases" << endl;
}


void firstThreeTest() {
	//string a1[5] = { "4444", "4444", "4444", "4444", "4444" };
	//string a2[4] = { "4444", "4444", "333", "4444" };
	//string a3[3] = { "4444", "4444", "333" };
	//string a4[3] = { "333", "4444", "333" };

	//assert(allTrue(a1, 5));
	//assert(allTrue(a1, 0));
	//assert(!allTrue(a2, 4));
	//assert(countFalse(a2, 4) == 1);
	//assert(countFalse(a3, 3) == 1);
	//assert(countFalse(a4, 3) == 2);
	//assert(countFalse(a4, 0) == 0);
	//assert(countFalse(a1, 5) == 0);
	//assert(firstFalse(a2, 4) == 2);
	//assert(firstFalse(a3, 3) == 2);
	//assert(firstFalse(a4, 3) == 0);
	//assert(firstFalse(a1, 5) == -1);
	//assert(firstFalse(a1, 0) == -1);

	string a[] = { "","","","","" };
	string b[] = { "1", "2", "3" };
	string c[] = { "2", "1", "3","1", "2", "3","" };


	assert(allTrue(a, -1));
	assert(allTrue(a, 0));
	assert(allTrue(a, 3));
	assert(allTrue(b, 0));
	assert(!allTrue(b, 1));
	assert(allTrue(b, -1));
	assert(!allTrue(b, 3));


	assert(countFalse(a, -1) == 0);
	assert(countFalse(a, 0) == 0);
	assert(countFalse(a, 3) == 0);
	assert(countFalse(b, -1) == 0);
	for (int i = 0; i < 4; i++)
	{
		assert(countFalse(b, i) == i);
	}
	for (int i = 0; i < 7; i++)
	{
		assert(countFalse(c, i) == i);
	}
	assert(countFalse(c, 7) == 6);

	for (int i = 0; i < 4; i++)
	{
		assert(firstFalse(a, i) == -1);
	}
	for (int i = 1; i < 4; i++)
	{
		assert(firstFalse(b, i) == 0);
	}
	assert(firstFalse(b, 0) == -1);
	for (int i = 1; i < 8; i++)
	{
		assert(firstFalse(c, i) == 0);
	}
	assert(firstFalse(c, 0) == -1);

	cout << "first three functions pass all tests" << endl;
}

void indexOfLeastTest() {
	string a1[5] = { "1", "2", "3", "4", "5" };
	string a2[4] = { "6", "5", "5", "6" };
	string a3[3] = { "1", "1", "1" };
	string a4[5] = { "5", "4", "5", "4", "5"};

	assert(indexOfLeast(a1, 5) == 0);
	assert(cc <= 5);
	cc = 0;
	assert(indexOfLeast(a2, 4) == 1);
	assert(cc <= 4);
	cc = 0;
	assert(indexOfLeast(a3, 3) == 0);
	assert(cc <= 3);
	cc = 0;
	assert(indexOfLeast(a4, 5) == 1);
	assert(cc <= 5);
	cc = 0;
	assert(indexOfLeast(a4, 0) == -1);
	assert(cc <= 0);
	cc = 0;
	assert(indexOfLeast(a4, -1) == -1);

	string a[] = { "","","","","" };
	string b[] = { "1", "2", "3" };
	string c[] = { "2", "1", "3","1", "2", "3","" };

	assert(indexOfLeast(a, 0) == -1);
	assert(cc <= 0);
	cc = 0;
	assert(indexOfLeast(b, 0) == -1);
	assert(cc <= 0);
	cc = 0;
	assert(indexOfLeast(c, 0) == -1);
	assert(cc <= 0);
	cc = 0;
	assert(indexOfLeast(a, -1) == -1);
	assert(cc <= 0);
	cc = 0;
	assert(indexOfLeast(b, -1) == -1);
	assert(cc <= 0);
	cc = 0;
	assert(indexOfLeast(c, -1) == -1);
	assert(cc <= 0);
	cc = 0;
	for (int i = 1; i < 4; i++)
	{
		assert(indexOfLeast(b, i) == 0);
		assert(cc <= i);
		cc = 0;
	}
	for (int i = 2; i < 7; i++)
	{
		assert(indexOfLeast(c, i) == 1);
		assert(cc <= i);
		cc = 0;
	}
	assert(indexOfLeast(c, 1) == 0);
	assert(cc <= 1);
	cc = 0;
	assert(indexOfLeast(c, 7) == 6);
	assert(cc <= 7);
	cc = 0;

	cout << "indexOfLeast() passes all tests" << endl;
}

int main() {
	includesTest();
	firstThreeTest();
	indexOfLeastTest();

	string s1[] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
	string s2[] = { "kyle", "kenny", "butters" };
	string s3[] = { "kyle" ,"cartman", "cartman" };
	string s4[] = { "kyle", "butters", "kenny" };
	string s5[] = { "stan" "kenny" "kenny" };
	assert(includes(s1, 7, s2, 3) == true);
	assert(includes(s1, 7, s3, 3) == true);
	assert(includes(s1, 7, s4, 3) == false);
	assert(includes(s1, 7, s5, 3) == false);
	assert(includes(s1, 7, s5, 0) == true);
	assert(includes(s1, 0, s5, 0) == true);
	//test includes

	string s6[] = { "","","","" };
	string s7[] = { "","","1","3","","4" };
	string s8[] = { "" };
	assert(allTrue(s6, 4) == true);
	assert(countFalse(s6, 4) == 0);
	assert(firstFalse(s6, 4) == -1);
	assert(allTrue(s7, 6) == false);
	assert(countFalse(s7, 6) == 3);
	assert(firstFalse(s7, 4) == 2);
	assert(firstFalse(s8, 1) == -1);
	assert(allTrue(s8, 1) == true);
	//test allTrue, countFalse, firstFalse

	string s9[] = { "b","t","a","d","a","f" };
	assert(indexOfLeast(s9, 6) == 2);
	assert(indexOfLeast(s9, 0) == -1);
	//test indexOfLeast

	cout << "all test passed!" << endl;

	cout << endl << "PASS" << endl;
	return 0;
}