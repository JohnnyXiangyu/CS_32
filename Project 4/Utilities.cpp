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
	if (s[index] >= '1' && s[index] <= '9')
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

bool doInstruction(const queue<Instruction>& instructions) {

	return false;
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
		nextPos = pos+1;
		return Instruction(thisLength, thisInfo);
	}
	else if (thisChar == 'C') {
		int pos = start + 1;
		int thisLength = number(diff, pos);
		pos++;
		int thisInfo = number(diff, pos);
		nextPos = pos;
		return Instruction(thisLength, number(diff, thisInfo));
	}
}