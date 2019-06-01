#ifndef UTILITIES
#define UTILITIES 10
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cassert>

struct Item {
	Item(int start, std::string data) :
		len(data.size()), offset(start), content(data)
	{}
	int len;
	int offset;
	std::string content;
};

struct Instruction {
	//a class marking each block of instruction
	Instruction(int length, std::string newWord) :
		type('A'), length(length)//, content("")
	{
		//content = "A" + std::to_string(length) + ':' + newWord;
		info = newWord;
	}

	Instruction(int length, int offset) :
		type('C'), length(length)//, content("")
	{
		//content = "C" + std::to_string(length) + ',' + std::to_string(offset);
		info = std::to_string(offset);
	}

	Instruction merge(const Instruction& later) {
		//please only use for add instructions
		//std::assert(type == later.type);
		return Instruction(length + later.length, info + later.info);
	}

	char type;
	int length;
	std::string info;
	//std::string content;
};

int number(std::string s, int& index);
void printInstruction(std::ostream& _diff, const std::list<Instruction>& instructions);
bool doInstruction(const std::queue<Instruction>& instructions);
Instruction readInstruction(const std::string& diff, int start, int& nextInstruction);

#endif