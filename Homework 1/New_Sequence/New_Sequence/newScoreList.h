#ifndef SCORELIST
#define SCORELIST 1

#include "newSequence.h"
#include <limits>

const unsigned long NO_SCORE = std::numeric_limits<unsigned long>::max();

class ScoreList
{
public:
	ScoreList();       // Create an empty score list.
	bool add(unsigned long score);
	bool remove(unsigned long score);
	int size() const;
	unsigned long minimum() const;
	unsigned long maximum() const;
private:
	// Some of your code goes here.
	Sequence m_sequence;
	bool score_check(unsigned long score);
};



#endif