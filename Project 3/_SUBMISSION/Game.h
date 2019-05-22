#ifndef GAME
#define GAME 1

#include "Board.h" //can't use imcomplete class here

class Player;
enum Side;

class Game {
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const;

private:
	Player* m_south;
	Player* m_north; //data members for players
	Board m_board;
	Side curSide;
	Player* curPlayer;
};


#endif
