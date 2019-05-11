#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int c = 0; //comment out upon submission

// Return the number of ways that all n2 elements of a2 appear
	  // in the n1 element array a1 in the same order (though not
	  // necessarily consecutively).  The empty sequence appears in a
	  // sequence of length n1 in 1 way, even if n1 is 0.
	  // For example, if a1 is the 7 element array
	  //    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
	  // then for this value of a2            the function must return
	  //    "stan" "kenny" "cartman"                      1
	  //    "stan" "cartman" "butters"                    2
	  //    "kenny" "stan" "cartman"                      0
	  //    "kyle" "cartman" "butters"                    3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 <= 0)
		return 1;
	if (n1 <= 0)
		return 0;

	int count = 0;
	c++;
	if (a2[n2 - 1] == a1[n1 - 1]) 
		count += countIncludes(a1, n1 - 1, a2, n2 - 1);
	count += countIncludes(a1, n1 - 1, a2, n2);
	return count;
}

// Exchange two strings
void exchange(string& x, string& y)
{
	string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
	int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < separator
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > separator

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
	if (n > 1) {
		int firstnotless = 0;
		int firstgreater = n;

		separate(a, n, a[n - 1], firstnotless, firstgreater);

		if (firstgreater != n)
			order(a, n);
		else
			order(a, n - 1);
	}

	//c++;
	//if (n > 1) {
	//	int start = 0;
	//	int end = 0;

	//	separate(a, n, a[n / 2], end, start);
	//	order(a, end);
	//	order(a + start, n - start);
	//}
}


void countIncludesTest() {
	string a1[7] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
	string a2[3] = { "kyle", "cartman", "butters" };
	string a3[3] = { "kenny", "stan", "cartman" };
	string a4[3] = { "stan", "cartman", "butters" };
	string a5[3] = { "stan", "kenny", "cartman" };

	assert(countIncludes(a1, 7, a2, 3) == 3);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a1, 7, a3, 3) == 0);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a1, 7, a4, 3) == 2);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a1, 7, a5, 3) == 1);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a1, 7, a5, 0) == 1);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a1, 7, a5, -1) == 1);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a1, 0, a5, 3) == 0);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a1, -1, a5, 3) == 0);
	//cerr << c << endl;
	//c = 0;

	//aliasing, extreme situation
	string a11[1] = { "1" };
	string a15[5] = { "1", "2", "1", "2", "1" };
	assert(countIncludes(a11, 1, a15, 1) == 1);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a15, 5, a15, 1) == 3);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a15, 5, a15, 2) == 3);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a15, 5, a15, 3) == 4);
	//cerr << c << endl;
	//c = 0;
	assert(countIncludes(a15, 5, a15, 5) == 1);
	//cerr << c << endl;
	//c = 0;

	cout << "countIncludes passes all test cases" << endl;
}

void orderTest() {
	string a1[7] = { "6", "4", "5", "2", "1", "7", "3" };
	string a2[7] = { "1", "2", "3", "4", "5", "6", "7" };
	order(a1, 7);
	//cerr << c << endl;
	//c = 0;
	for (int i = 0; i < 7; i++)
		assert(a1[i] == a2[i]);
	
	string a3[11] = { "2", "2", "2", "1", "1", "3", "3", "4", "4", "5", "5" };
	string a4[11] = { "1", "1", "2", "2", "2", "3", "3", "4", "4", "5", "5" };
	order(a3, 11);
	//cerr << c << endl;
	//c = 0;
	for (int i = 0; i < 11; i++)
		assert(a3[i] == a4[i]);

	string a11[20] = { "6", "4", "5", "2", "1", "7", "3", "9", "8", "0", "6", "4", "5", "2", "1", "7", "3", "9", "8", "0" };
	string a22[20] = { "0", "0", "1", "1", "2", "2", "3", "3", "4", "4", "5", "5", "6", "6", "7", "7", "8", "8", "9", "9" };
	order(a11, 20);
	//cerr << c << endl;
	//c = 0;
	for (int i = 0; i < 20; i++)
		assert(a11[i] == a22[i]);

	string a111[100];
	string a222[100];
	for (int i = 0; i < 100; i++) {
		char temp = i;
		a222[i] = "";
		a222[i] += temp;
		a111[99 - i] = "";
		a111[99 - i] += temp;
	}
	order(a111, 100);
	//cerr << c << endl;
	//c = 0;
	for (int i = 0; i < 100; i++)
		assert(a111[i] == a222[i]);

	cout << "order passes all tests" << endl;
}

void extraTest() {
	string a1[3] = { "1", "2", "4" };
	string a2[3] = { "1", "2", "4" };
	string a3[6] = { "1", "1", "2", "4", "4", "5" };


	assert(countIncludes(a3, 6, a2, 3) == 4);
	assert(countIncludes(a2, 3, a3, 6) == 0);
	assert(countIncludes(a2, 3, a1, 3) == 1);
	assert(countIncludes(a3, 4, a2, 3) == 2);
	assert(countIncludes(a2, 3, a1, 0) == 1);
	assert(countIncludes(a3, 5, a2, 3) == 4);
	assert(countIncludes(a3, 3, a2, 2) == 2);

	//int size;
	//cout << "please enter the size of the array" << endl;
	//cin >> size;
	//string * arr = new string[size];
	//for (int i = 0; i < size; i++)
	//{
	//	arr[i] = ".";
	//}
	//for (int i = 0; i < size; i++)
	//{
	//	int position;
	//	cout << "please enter an interger" << endl;
	//	cin >> position;
	//	arr[i] = to_string(position);
	//}
	//order(arr, size);
	//for (int i = 1; i < size; i++)
	//{
	//	assert(arr[i - 1] <= arr[i]);
	//}

	//delete[] arr;

	cerr << "pass all extra tests" << endl;
}

int main() {
	countIncludesTest();
	orderTest();
	extraTest();

	string s1[] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
	string s2[] = { "stan", "kenny", "cartman" };
	string s3[] = { "stan", "cartman", "butters" };
	string s4[] = { "kenny", "stan", "cartman" };
	string s5[] = { "kyle", "cartman", "butters" };
	string s6[] = { "j","i","v","d","k","d","l","a","o","o","l","d" };
	string s7[] = { "a", "a", "a" ,"a" };
	string s8[] = { "a" };
	string s9[] = { "a", "a" };
	order(s6, 12);
	assert(s6[0] == "a" && s6[2] == "d" && s6[10] == "o");
	assert(countIncludes(s1, 7, s2, 3) == 1);
	assert(countIncludes(s1, 7, s3, 3) == 2);
	assert(countIncludes(s1, 7, s4, 3) == 0);
	assert(countIncludes(s1, 7, s5, 3) == 3);
	assert(countIncludes(s7, 4, s8, 1) == 4);
	assert(countIncludes(s7, 4, s9, 2) == 6);
	cout << "All tests passed!";

	cout << endl << "PASS" << endl;
	return 0;
}