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
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <functional>
#include <list>
#include "HashTable.h"
#include "Utilities.h"
using namespace std;

void printInstruction(ostream& _diff, const list<Instruction>& instructions) {
	for (list<Instruction>::const_iterator i = instructions.begin(); i != instructions.end(); i++) {
		_diff << (*i).type << (*i).length;
		if ((*i).type == 'A')
			_diff << ":" << (*i).info;
		else
			_diff << "," << (*i).info;
	}
}

void createDiff(istream& _old, istream& _new, ostream& _diff) {
	const int SLICELEN = 65;
	
	//read file into the strings
	string oldFile(""), newFile("");
	while (_old) {
		string temp;
		getline(_old, temp);
		oldFile += temp;
	}
	while (_new) {
		string temp;
		getline(_new, temp);
		newFile += temp;
	}

	//slice the old string
		//the hash class looks unreliable
	HashTable table;
	int pos = 0;
	while (pos < oldFile.size()) {
		string temp = oldFile.substr(pos, SLICELEN);//slice the file into specified lengths
		table.push(pos, temp); //push it into the hash table
		
		pos += temp.length();
	}


	//look for all matches
	//TODO: instruction has bugs
	list<Instruction> instructions;
	int index = 0;
	while (index < newFile.size()) {
		//find all matches in the original file
		string seg = newFile.substr(index, SLICELEN);
		queue<Item> results;
		if (table.search(seg, results)) {
			//if found, start to loop deeper into the string
			queue<Instruction> temp_commands;
			while (!results.empty()) {
				int j = (results.front().offset + results.front().content.size());
				int k = index + results.front().content.size();
				while (j < oldFile.size() && k < newFile.size() && oldFile[j] == newFile[k]) {
					j++;
					k++;
				}
				temp_commands.push(Instruction(j - results.front().offset, results.front().offset)); //copy instruction
				results.pop();
			}

			//choose the longest copy instruction
			Instruction chosen = temp_commands.front();
			temp_commands.pop();
			while (!temp_commands.empty()) {
				if (chosen.length < temp_commands.front().length)
					chosen = temp_commands.front();
				temp_commands.pop();
			}

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

	//TODO: output instructions to the file
	printInstruction(_diff, instructions);
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

void myTest() {
	ifstream oldFile("_old.txt", ios::binary);
	ifstream newFile("_new.txt", ios::binary);
	ofstream diffFile("_diff.txt", ios::binary);

	createDiff(oldFile, newFile, diffFile);
	diffFile.close();
}


int main()
{
	//assert(runtest("myoldfile.txt", "mynewfile.txt", "mydifffile.txt", "mynewfile2.txt"));
	//cerr << "Test PASSED" << endl;
	
	myTest();

	return 0;
}