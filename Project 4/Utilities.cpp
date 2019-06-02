#include <string>
#include <cassert>
#include <iostream>
#include <queue>
#include <list>
#include "Utilities.h"
using namespace std;

int number(std::string s, int& index)
{
	int result = 0;
	if (s[index] >= '0' && s[index] <= '9')
	{
		while (index < s.size() && s[index] >= '0' && s[index] <= '9')
		{
			result = (result * 10) + (s[index] - '0');
			index = index + 1;
		}
	}
	return(result);
}

int number(std::string s)
{
	int index = 0;
	int result = 0;
	if (s[index] >= '0' && s[index] <= '9')
	{
		while (index < s.size() && s[index] >= '0' && s[index] <= '9')
		{
			result = (result * 10) + (s[index] - '0');
			index = index + 1;
		}
	}
	return(result);
}

void printInstruction(ostream& _diff, const list<Instruction>& instructions) {
	for (list<Instruction>::const_iterator i = instructions.begin(); i != instructions.end(); i++) {
		_diff << (*i).type << (*i).length;
		if ((*i).type == 'A')
			_diff << ":" << (*i).info;
		else
			_diff << "," << (*i).info;
	}
}

bool doInstruction(std::string oldFile, ostream& _new, queue<Instruction> instructions) {
	//print content to new file
	while (!instructions.empty()) {
		Instruction thisInstruction = instructions.front();
		instructions.pop();
		if (thisInstruction.type == 'A') {
			//TODO: print the info part of this instruction into _new
			_new << thisInstruction.info;
		}
		else if (thisInstruction.type == 'C') {
			//TODO: use substr to get the copy segment
			int temp = 0;
			string newSeg = oldFile.substr(number(thisInstruction.info, temp), thisInstruction.length);
			_new << newSeg;
		}
		else
			return false;
	}
	return true;
}

Instruction readInstruction(const string& diff, int start, int& nextPos) {
	//return a instruction from given string and index
	//also gives information about next index
	char thisChar = diff[start];

	if (thisChar == 'A') {
		int pos = start + 1;
		int thisLength = number(diff, pos);
		string thisInfo("");
		for (int i = 0; i < thisLength; i++) {
			pos++;
			thisInfo += diff[pos];
		}
		nextPos = pos + 1;
		return Instruction(thisLength, thisInfo);
	}
	else if (thisChar == 'C') {
		int pos = start + 1;
		int thisLength = number(diff, pos);
		pos++;
		int thisInfo = number(diff, pos); //the offset part of copy instruction
		nextPos = pos;
		return Instruction(thisLength, thisInfo);
	}
	else
		return Instruction(1, 2, 3);
}