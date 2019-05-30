#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "HashTable.h"
using namespace std;


void createDiff(istream& _old, istream& _new, ostream& _diff) {
	const int SLICELEN = 16;
	
	string oldFile, newFile;
	//TODO: read file into the strings
	while (_old) {
		string temp;
		getline(_old, temp);
		oldFile += temp;
		oldFile += '\n';
	}

	//TODO: slice the old string
		//the hash class looks unreliable
	HashTable table;
	{
		int remain = oldFile.size();
		int index = 0;
		while (remain > 0) {
			string temp;
			if (remain < SLICELEN) //slice the file into specified lengths
				temp = oldFile.substr(index, SLICELEN);
			else
				temp = oldFile.substr(index, remain);
			table.push(index, temp); //push it into the hash table
			
			remain -= temp.length();
			index += temp.length();
		}
		assert(remain == 0);
		assert(index == oldFile.size() - 1);
	} //delete all temporary variables here

	//TODO: compare the two strings


}

bool applyDiff(istream& _old, istream& _diff, ostream& _new) {


	return false;
}


bool runtest(string oldName, string newName, string diffName, string newName2)
{
	if (diffName == oldName || diffName == newName ||
		newName2 == oldName || newName2 == diffName ||
		newName2 == newName)
	{
		cerr << "Files used for output must have names distinct from other files" << endl;
		return false;
	}
	ifstream oldFile(oldName, ios::binary);
	if (!oldFile)
	{
		cerr << "Cannot open " << oldName << endl;
		return false;
	}
	ifstream newFile(newName, ios::binary);
	if (!newFile)
	{
		cerr << "Cannot open " << newName << endl;
		return false;
	}
	ofstream diffFile(diffName, ios::binary);
	if (!diffFile)
	{
		cerr << "Cannot create " << diffName << endl;
		return false;
	}
	createDiff(oldFile, newFile, diffFile);
	diffFile.close();

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the file
	ifstream diffFile2(diffName, ios::binary);
	if (!diffFile2)
	{
		cerr << "Cannot read the " << diffName << " that was just created!" << endl;
		return false;
	}
	ofstream newFile2(newName2, ios::binary);
	if (!newFile2)
	{
		cerr << "Cannot create " << newName2 << endl;
		return false;
	}
	assert(applyDiff(oldFile, diffFile2, newFile2));
	newFile2.close();

	newFile.clear();
	newFile.seekg(0);
	ifstream newFile3(newName2, ios::binary);
	if (!newFile)
	{
		cerr << "Cannot open " << newName2 << endl;
		return false;
	}
	if (!equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
		istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
	{

		cerr << newName2 << " is not identical to " << newName
			<< "; test FAILED" << endl;
			return false;
	}
	return true;
}

int main()
{
	//assert(runtest("myoldfile.txt", "mynewfile.txt", "mydifffile.txt", "mynewfile2.txt"));
	//cerr << "Test PASSED" << endl;
	

}