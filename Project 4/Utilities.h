#ifndef UTILITIES
#define UTILITIES 1
#include <string>

struct item {
	item(int start, std::string data) :
		len(data.size()), offset(start), content(data)
	{}
	int len;
	int offset;
	std::string content;
};

struct instruction {
	//a class marking each block of instruction
public:
	instruction(int length, std::string newWord) :
		m_type('A'), m_len(length), m_content("")
	{
		m_content += m_type + std::to_string(m_len) + ':' + newWord;
		m_info = newWord;
	}

	instruction(int length, int offset) :
		m_type('C'), m_len(length), m_content("")
	{
		m_content = "" + m_type + std::to_string(m_len) + ',' + std::to_string(offset);
		m_info = std::to_string(offset);
	}

	instruction merge(const instruction& later) {
		//please only use for add instructions
		return instruction(m_len + later.m_len, m_content + later.m_content);
	}

	inline
		char type() { return m_type; }
	inline
		int length() { return m_len; }
	inline
		std::string content() { return m_content; }
	inline
		std::string info() { return m_info; }

private:
	char m_type;
	int m_len;
	std::string m_info;
	std::string m_content;
};

#endif