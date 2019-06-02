#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

#include <iostream>
#include <sstream>  // for istringstream and ostringstream
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <functional>
#include <list>
#include <cmath>
#include "HashTable.h"
#include "Utilities.h"
using namespace std;

void createDiff(istream& _old, istream& _new, ostream& _diff) { //TODO
	const int SLICELEN = 8;
	
	//read file into the strings //reconstructed
	string oldFile(""), newFile("");
	takeString(_old, oldFile);
	takeString(_new, newFile);

	//slice the old string
	HashTable table;
	fillTable(oldFile, table, SLICELEN);

	//look for all matches
	list<Instruction> instructions;
	size_t index = 0;
	while (index < newFile.size()) {
		//find all matches in the table
		string seg = newFile.substr(index, SLICELEN);
		queue<Item> results;
		if (table.search(seg, results)) {
			//if found, start to loop deeper into the string
			queue<Instruction> temp_commands;
			while (!results.empty()) {
				size_t j = (results.front().offset + results.front().content.size());
				size_t k = index + results.front().content.size();
				while (j < oldFile.size() && k < newFile.size() && oldFile[j] == newFile[k]) {
					j++;
					k++;
				}
				temp_commands.push(Instruction(j - results.front().offset, results.front().offset)); //copy instruction
				results.pop();
			}
			//choose the longest copy instruction
				//TODO: add a new logic, combine length and offset
			Instruction chosen = compareInstructions(temp_commands);
			//finalize the copy instruction
			instructions.push_back(chosen);
			index += chosen.length;
		}
		else {
			//if not found, an ADD instruction will be added
			string temp = ""; 
			temp += newFile[index];
			Instruction newGuy(1, temp); //add instruction

			//merge two continuous ADD instructions
			if (!instructions.empty() && instructions.back().type == 'A') {
				newGuy = instructions.back().merge(newGuy);
				instructions.pop_back();
			}
			instructions.push_back(newGuy);
			index++;
		}
	}

	//output instructions to file
	printInstruction(_diff, instructions);
}

bool applyDiff(istream& _old, istream& _diff, ostream& _new) {
	//load diff file //reconstructed
	string oldFile(""), diffFile("");
	takeString(_old, oldFile);
	takeString(_diff, diffFile);
	
	//break the diff file into instructions
	queue<Instruction> instructions;
	int pos = 0;
	while (pos < diffFile.length()) {
		char thisChar = diffFile[pos];
		if (thisChar == 'A' || thisChar == 'C') {
			//process an intruction
			int start = pos;
			instructions.push(readInstruction(diffFile, start, pos));
			if (instructions.back().type == 'E')
				return false;
		}
		else
			return false; //it means something is wrong
	}

	//print new file using instructions
	return doInstruction(oldFile, _new, instructions);
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

void testRound(string oldName, string newName) {
	ifstream oldFile(oldName, ios::binary);
	ifstream newFile(newName, ios::binary);
	ofstream diffFile("_diff.txt", ios::binary);

	cerr << oldName << ":" << endl;

	Timer t;
	createDiff(oldFile, newFile, diffFile);
	cerr << "createDiff(): \n    " << t.elapsed() << " ms" << endl;
	diffFile.close();

	ifstream diffFile2("_diff.txt", ios::binary);
	int i = 0;
	char ttt;
	while (diffFile2.get(ttt)) {
		i += 1;
	}
	cerr << "File size:" << endl;
	cerr << "    " << i << " bytes." << endl;

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the stream

	diffFile2.clear();   // clear the end of file condition
	diffFile2.seekg(0);  // reset back to beginning of the stream

	ofstream newnew("_new2.txt", ios::binary);

	t.start();
	if (applyDiff(oldFile, diffFile2, newnew))
		cerr << "applyDiff(): \n    " << t.elapsed() << " ms" << endl << endl;
	else
		cerr << "diff file content error\n\n";
	newnew.close();
}

void myTest() {
	while (true) {
		cerr << "Select test case \n" <<
			"---------------------------------------------------------------------------\n" <<
			"|1 smallmart | 2 greeneggs | 3 warandpeace | 4 strange | 5 other | 0 quit |\n" <<
			"---------------------------------------------------------------------------\n";
		int num = 0;
		cin >> num;
		if (num == 1)
			testRound("testCases/smallmart1.txt", "testCases/smallmart2.txt");
		else if (num == 2)
			testRound("testCases/greeneggs1.txt", "testCases/greeneggs2.txt");
		else if (num == 3)
			testRound("testCases/warandpeace1.txt", "testCases/warandpeace2.txt");
		else if (num == 4)
			testRound("testCases/strange1.txt", "testCases/strange2.txt");
		else if (num == 5) {
			int other;
			string oldName, newName;
			cerr << "Select function\n" <<
				"-------------------------------------\n" <<
				"|1 createDiff | 2 applyDiff | 3 both|\n" <<
				"-------------------------------------\n";
			cin >> other;
			cerr << "old file name: ";
			cin >> oldName;
			if (other == 1) {
				cerr << "new file name: ";
				cin >> newName;
				ifstream oldFile(oldName, ios::binary);
				ifstream newFile(newName, ios::binary);
				ofstream diffFile("_diff.txt", ios::binary);
				Timer t;
				createDiff(oldFile, newFile, diffFile);
				cerr << "createDiff(): \n    " << t.elapsed() << " ms" << endl;
				diffFile.close();
				ifstream diffFile2("_diff.txt", ios::binary);
				int i = 0;
				char ttt;
				while (diffFile2.get(ttt)) {
					i += 1;
				}
				cerr << "File size:" << endl;
				cerr << "    " << i << " bytes.\n\n";
			}
			else if (other == 2) {
				ifstream oldFile(oldName, ios::binary);
				ifstream diffFile("_diff.txt", ios::binary);
				ofstream newnew("_new2.txt", ios::binary);
				Timer t;
				if (applyDiff(oldFile, diffFile, newnew))
					cerr << "applyDiff(): \n    " << t.elapsed() << " ms\n\n";
				else
					cerr << "diff file content error\n\n";
				newnew.close();
			}
			else if (other == 3) {
				cerr << "new file name: ";
				cin >> newName;
				testRound(oldName, newName);
			}
		}
		else if (num == 0)
			return;
		else
			cerr << "Invalid input." << endl;
	}
}

void profTest() {
	assert(runtest("testCases/smallmart1.txt", "testCases/smallmart2.txt", "_diff.txt", "_new2.txt"));
	cerr << "passes smallmart" << endl;
	assert(runtest("testCases/greeneggs1.txt", "testCases/greeneggs2.txt", "_diff.txt", "_new2.txt"));
	cerr << "passes greeneggs" << endl;
	assert(runtest("testCases/warandpeace1.txt", "testCases/warandpeace2.txt", "_diff.txt", "_new2.txt"));
	cerr << "passes warandpeace" << endl;
	//assert(runtest("testCases/strange1.txt", "testCases/strange2.txt", "_diff.txt", "_new2.txt"));
	//cerr << "passes strange" << endl;
	cerr << "Test PASSED" << endl;
}

int main()
{	
	myTest();
	//profTest(); //debug only
	return 0;
}