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
	const int SLICELEN = 1;
	
	//read file into the strings
	string oldFile(""), newFile("");
	char temp;
	while (_old.get(temp)) {
		oldFile += temp;
	}
	while (_new.get(temp)) {
		newFile += temp;
	}

	//slice the old string
		//the hash class looks unreliable
	HashTable table;
	size_t pos = 0;
	while (pos < oldFile.size()) {
		string temp = "";
		temp = oldFile.substr(pos, SLICELEN);//slice the file into specified lengths
		table.push(pos, temp); //push it into the hash table
		
		pos += temp.length();
	}


	//look for all matches
	list<Instruction> instructions;
	size_t index = 0;
	while (index < newFile.size()) {
		//find all matches in the original file
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
			Instruction chosen = temp_commands.front();
			temp_commands.pop();
			while (!temp_commands.empty()) {

				if (chosen.length < temp_commands.front().length)
					chosen = temp_commands.front();
				else if (chosen.length == temp_commands.front().length && number(chosen.info) > number(temp_commands.front().info))
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

	//output instructions to the file
	printInstruction(_diff, instructions);
}

bool applyDiff(istream& _old, istream& _diff, ostream& _new) {
	//load diff file
	string oldFile(""), diffFile("");
	char temp;
	while (_old.get(temp)) {
		oldFile += temp;
	}
	while (_diff.get(temp)) {
		diffFile += temp;
	}
	
	queue<Instruction> instructions;
	//break the diff file into instructions
	int pos = 0;
	while (pos < diffFile.length()) {
		char thisChar = diffFile[pos];
		if (thisChar == 'A' || thisChar == 'C') {
			//process an intruction
			int start = pos;
			instructions.push(readInstruction(diffFile, start, pos));
			assert(instructions.back().type != 'E');
		}
		else
			return false; //it means something is wrong
	}

	//print new file using instructions
	return doInstruction(oldFile, _new, instructions);
}

void runtest(string oldtext, string newtext)
{
	istringstream oldFile(oldtext);
	istringstream newFile(newtext);
	ostringstream diffFile;
	createDiff(oldFile, newFile, diffFile);
	string result = diffFile.str();
	cout << "The diff file length is " << result.size()
		<< " and its text is " << endl;
	cout << result << endl;

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the stream
	istringstream diffFile2(result);
	ostringstream newFile2;
	assert(applyDiff(oldFile, diffFile2, newFile2));
	assert(newtext == newFile2.str());
}

void myTest() {
	ifstream oldFile("_old.txt", ios::binary);
	ifstream newFile("_new.txt", ios::binary);
	ofstream diffFile("_diff.txt", ios::binary);

	createDiff(oldFile, newFile, diffFile);
	diffFile.close();

	ifstream diffFile2("_diff.txt", ios::binary);
	int i = 0;
	char ttt;
	while (diffFile2.get(ttt)) {
		i += 1;
	}
	cerr << i << endl;

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the stream

	diffFile2.clear();   // clear the end of file condition
	diffFile2.seekg(0);  // reset back to beginning of the stream

	ofstream newnew("_new2.txt", ios::binary);

	if (applyDiff(oldFile, diffFile2, newnew))
		cerr << "    It's fine." << endl << endl;
	newnew.close();
}


int main()
{
	//runtest("There's a bathroom on the right.",
	//	"There's a bad moon on the rise.");
	//runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
	//	"XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
	//cerr << "All tests passed" << endl;
	
	myTest();

	//for (int i = 1; i <= 100; i++) {
	//	cerr << i << ": \n";
	//	myTest(i);
	//}

	
	return 0;
}