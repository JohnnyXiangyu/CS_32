#ifndef PLAYER
#define PLAYER 1
#include <iostream>
#include <chrono>
#include <future>
#include <atomic>
#include "Side.h"
#include "Board.h"

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
		});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};


class Player {
public:
	Player(std::string name)
		: m_name(name)
	{}
	std::string name() const {
		return m_name;
	}
	virtual bool isInteractive() const {
		return false; //default: not human
	}

	virtual int chooseMove(const Board& b, Side s) const = 0;

	virtual ~Player() {}

private:
	std::string m_name; //only having this data member is okay?
};


class HumanPlayer : public Player 
{
public:
	HumanPlayer(std::string name)
		: Player(name)
	{} //really simple and beautiful

	virtual bool isInteractive() const {
		return true; //only for human
	}
	
	virtual int chooseMove(const Board& b, Side s) const; //how should I prompt the input ???

private:

};

class BadPlayer : public Player
{
public:
	BadPlayer(std::string name)
		: Player(name)
	{}
	
	virtual int chooseMove(const Board& b, Side s) const;
};



class SmartPlayer : public Player
{
public:
	SmartPlayer(std::string name)
		: Player(name), maxDepth(7) //plz change the depth to appropriate value!!!!!!!!!!!!!!!
	{}

	virtual ~SmartPlayer() {}

	virtual int chooseMove(const Board& b, Side s) const;

private:
	int evaluate(const Board& b, Side s, AlarmClock& ac, int depth = 0) const;
	int sideSwitch(Side s) const;
	int maxDepth;
};

#endif
