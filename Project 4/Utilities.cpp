#include <string>
#include <cassert>
#include <iostream>
#include <queue>
#include <list>
#include "Utilities.h"
using namespace std;

void takeString(istream& _source, string& _string) {
	_string = "";
	char temp;
	while (_source.get(temp)) {
		_string += temp;
	}
}

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
	else
		return -1; //return -1 when the input is invalid
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
	else
		return -1;
	return(result);
}

Instruction compareInstructions(queue<Instruction>& temp_commands) {
	Instruction chosen = temp_commands.front();
	temp_commands.pop();
	while (!temp_commands.empty()) {

		if (chosen.length < temp_commands.front().length)
			chosen = temp_commands.front();
		else if (chosen.length == temp_commands.front().length && number(chosen.info) > number(temp_commands.front().info))
			chosen = temp_commands.front();
		temp_commands.pop();
	}

	return chosen;
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
			//print the info part of this instruction into _new
			_new << thisInstruction.info;
		}
		else if (thisInstruction.type == 'C') {
			//TODO: use substr to get the copy segment
			int temp = 0;
			int offset = number(thisInstruction.info, temp);
			if (offset > -1 && offset + thisInstruction.length <= oldFile.size()) {
				string newSeg = oldFile.substr(offset, thisInstruction.length);
				_new << newSeg;
			}
			else
				return false;
		}
		else
			return false; //not supposed to be triggered
	}
	return true;
}

Instruction readInstruction(const string& diff, int start, int& nextPos) {
	//return a instruction from given string and index
	//also gives information about next index
	char thisChar = diff[start];
	int pos = start + 1;

	if (thisChar == 'A') {
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
		int thisLength = number(diff, pos);
		pos++;
		int thisInfo = number(diff, pos); //the offset part of copy instruction
		if (thisInfo > -1) {
			nextPos = pos;
			return Instruction(thisLength, thisInfo);
		}
	}
	return Instruction(1, 2, 3); //error message
}