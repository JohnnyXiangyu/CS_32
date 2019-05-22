#include <iostream>
#include <string>
#include "Game.h"
#include "Side.h"
#include "Player.h"
#include "Board.h"
using namespace std;

Game::Game(const Board& b, Player* south, Player* north) 
	: m_south(south), m_north(north), m_board(b), curSide(SOUTH), curPlayer(m_south)
{
	//
}


void Game::display() const {
	cout << "          " << m_north->name() << endl;
	cout << "     ";
	//north player's holes
	for (int i = 1; i <= m_board.holes(); i++) 
		cout << m_board.beans(NORTH, i) << "     ";
	//pots
	int diPots = 4 * 2 + 6 * (m_board.holes() - 1) + 1;
	cout << endl << m_board.beans(NORTH, 0);
	for (int i = 0; i < diPots; i++)
		cout << " ";
	cout << m_board.beans(SOUTH, 0) << endl;
//south player's holes
cout << "     ";
for (int i = 1; i <= m_board.holes(); i++)
cout << m_board.beans(SOUTH, i) << "     ";

cout << endl << "          " << m_south->name() << endl; //last row
}


void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	if (m_board.beansInPlay(SOUTH) > 0 && m_board.beansInPlay(NORTH) > 0) {
		over = false;
		return;
	}

	//now we are in the situation when the game ended
	over = true;
	int northResult = m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH);
	int southResult = m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH);

	if (northResult < southResult) {
		hasWinner = true;
		winner = SOUTH;
	}
	else if (northResult > southResult) {
		hasWinner = true;
		winner = NORTH;
	}
	else
		hasWinner = false;
}


bool Game::move() {
	if (m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0) {
		return false; //return false if there's no move
	}

	Side opponent;
	//move it
	if (curSide == NORTH)
		opponent = SOUTH;
	else
		opponent = NORTH;

	while (true) {
		//TODO: decide whose turn is it, have him choose a spot
		int move = curPlayer->chooseMove(m_board, curSide);
		if (!curPlayer->isInteractive())
			cout << curPlayer->name() << " chooses hole #" << move << "." << endl;

		Side endSide;
		int endHole;
		int rounds = m_board.beans(curSide, move) / (2 * m_board.holes() + 1);

		//sow
		if (m_board.sow(curSide, move, endSide, endHole)) {
			//display();


			//is the game over?
			bool over, hasWinner;
			Side winner;
			status(over, hasWinner, winner);



			if (over) {
				if (m_board.beansInPlay(SOUTH) > 0 || m_board.beansInPlay(NORTH) > 0) {
					display();
					cout << "Game over, sweeping the remaining beans." << endl;
					//move all beans to pot
					for (int i = 1; i <= m_board.holes(); i++) {
						m_board.moveToPot(NORTH, i, NORTH);
						m_board.moveToPot(SOUTH, i, SOUTH);
					}
					display();
				}
				else
					display();
				break;
			}

			//is there another round or a capture?
			if (endSide == curSide && endHole == 0) {
				display();
				cout << curPlayer->name() << " gets another round." << endl;
				continue; //extra round
			}
			else if (endSide == curSide && m_board.beans(opponent, endHole) > 0
				&& m_board.beans(curSide, endHole) == (1 + rounds)) {
				//capture
				m_board.moveToPot(opponent, endHole, curSide);
				m_board.moveToPot(curSide, endHole, curSide);

				display();

				status(over, hasWinner, winner);
				if (over) {
					if (m_board.beansInPlay(SOUTH) > 0 || m_board.beansInPlay(NORTH) > 0) {
						cout << "Game over, sweeping the remaining beans." << endl;
						//move all beans to pot
						for (int i = 1; i <= m_board.holes(); i++) {
							m_board.moveToPot(NORTH, i, NORTH);
							m_board.moveToPot(SOUTH, i, SOUTH);
						}
						display();
					}
					break;
				}
				break;
			}
			else {
				display();
				break;
			}

		}
	}

	//last step: changing player
	//display();
	curSide = opponent;

	if (curSide == NORTH)
		curPlayer = m_north;
	else
		curPlayer = m_south;

	return true;
}


void Game::play() {
	display();
	bool gameOn = move();

	bool over, hasWinner;
	Side winner;
	

	if (gameOn) {
		while (true) {
			if (!m_north->isInteractive() && !m_south->isInteractive()) {
				cout << ">Press ENTER to cuntinue. ";
				cin.ignore(100000, '\n');
				cout << endl;
			}

			//normal routine, run the game until game stops
			move();
			status(over, hasWinner, winner);

			if (over) {
				break;
			}
		}
	}
	else {
		status(over, hasWinner, winner);
	}

	//terminate procedure
	if (hasWinner) {
		cout << "The winner is ";
		if (winner == SOUTH)
			cout << m_south->name() << "." << endl;
		else
			cout << m_north->name() << "." << endl;
	}
	else {
		cout << "The game ended in a tie." << endl;
	}
}


int Game::beans(Side s, int hole) const {
	return m_board.beans(s, hole);
}