#ifndef UTILITIES
#define UTILITIES 10
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cassert>
#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};

struct Item {
	Item(int start, std::string data) :
		len(data.size()), offset(start), content(data)
	{}
	int len;
	int offset;
	std::string content;
};

struct Instruction {
	Instruction(int wrong, int wrong2, int wrong3) :
		type('E'), length(wrong + wrong2 + wrong3) //error
	{}
	
	Instruction(int length, std::string newWord) :
		type('A'), length(length) //addition
	{
		info = newWord;
	}

	Instruction(int length, int offset) :
		type('C'), length(length) //copy
	{
		info = std::to_string(offset);
	}

	Instruction merge(const Instruction& later) {
		//please only use for add instructions
		return Instruction(length + later.length, info + later.info);
	}

	char type;
	int length;
	std::string info;
};

void takeString(std::istream& _source, std::string& _string);

int number(std::string s, int& index);
int number(std::string s);

Instruction compareInstructions(std::queue<Instruction>& temp_commands);
void printInstruction(std::ostream& _diff, const std::list<Instruction>& instructions);
bool doInstruction(std::string oldFile, std::ostream& _new, std::queue<Instruction> instructions);
Instruction readInstruction(const std::string& diff, int start, int& nextInstruction);

#endif