#include <iostream>
#include <string>

#include "Player.h"
#include "Board.h"
#include "Side.h"
using namespace std;

//only the chooseMove functions

int HumanPlayer::chooseMove(const Board& b, Side s) const {
	int nHoles = b.holes();
	int i = 1;
	for (; i <= nHoles; i++) {
		if (b.beans(s, i) != 0)
			break;
	}
	if (i > nHoles)
		return -1;
	else {
		while (true) {
			cout << "Select a hole, " << name() << ": ";
			cin >> i;
			int tempBeans = b.beans(s, i);
			if (tempBeans != 0 && tempBeans != -1)
				return i;
			else if (i < 1 || i > b.holes()) { //if invalid
				cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
			}
			else if (tempBeans == 0) { //if empty
				cout << "There are no beans in that hole." << endl;
			}
		}
	}
}

int BadPlayer::chooseMove(const Board& b, Side s) const {
	//some rules: 1. choose a hole
	//2. the hole must not be empty
	//start by checking if there's any legal hole
	int nHoles = b.holes();
	int i = 1;
	for (; i <= nHoles; i++) {
		if (b.beans(s, i) != 0)
			break;
	}
	//now this is the dumb computer so he just chooses the first valid choice
	//please test is check feature
	if (i > nHoles)
		return -1;
	else {
		/*cout << name() << " chooses hole #" << i << "." << endl;*/
		return i;
	}
}

int SmartPlayer::chooseMove(const Board& b, Side s) const {
	//set alarm
	AlarmClock ac(4900);
	//if game ended
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0) {
		return -1;
	}

	//loop legal choices
	int extreme = -1 * sideSwitch(s) * 100;
	int maxima = sideSwitch(s) * 99;
	int result = -1;


	for (int i = 1; i <= b.holes(); i++) {
		//conpare the scores of each move
		if (i == b.holes() && result == -1) {
			result = i;
			break;
		}

		Board tB = b;
		int score;
		int rounds = tB.beans(s, i) / (2 * tB.holes() + 1);
		Side endSide;
		int endHole;

		if (!tB.sow(s, i, endSide, endHole))
			continue;
		//extra round
		if (endHole == 0)
			score = evaluate(tB, s, ac, -1);
		//capture
		else if (endSide == s && tB.beans(opponent(s), endHole) > 0
			&& tB.beans(s, endHole) == (1 + rounds)) {

			tB.moveToPot(opponent(s), endHole, s);
			tB.moveToPot(s, endHole, s);
			score = evaluate(tB, opponent(s), ac, 0);
		}
		else
			score = evaluate(tB, opponent(s), ac, 0);

		if (sideSwitch(s) * score > (sideSwitch(s) * extreme) || result == -1) {
			result = i;
			extreme = score;

			//TODO
			if (extreme == maxima)
				break;
		}
	}

	return result;
}

int SmartPlayer::evaluate(const Board& b, Side s, AlarmClock& ac, int depth) const {
	//increment depth
	depth++;
	//if game ended
	if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0) {

		if ((b.beansInPlay(NORTH) + b.beans(NORTH, 0)) > (b.beansInPlay(SOUTH) + b.beans(SOUTH, 0))) {
			return 99;
		}
		else if ((b.beansInPlay(NORTH) + b.beans(NORTH, 0)) < (b.beansInPlay(SOUTH) + b.beans(SOUTH, 0))) {
			return -99;
		}
		else if ((b.beansInPlay(NORTH) + b.beans(NORTH, 0)) == (b.beansInPlay(SOUTH) + b.beans(SOUTH, 0)))
			return 0;

		//return (b.beansInPlay(NORTH) + b.beans(NORTH, 0)) - (b.beansInPlay(SOUTH) + b.beans(SOUTH, 0));
	}

	if (b.beans(NORTH, 0) > b.totalBeans() / 2)
		return 99;
	if (b.beans(SOUTH, 0) > b.totalBeans() / 2)
		return -99;

	//if it's too deep in the tree (too much time)
	if (depth >= maxDepth || ac.timedOut()) {
		return (b.beans(NORTH, 0) - b.beans(SOUTH, 0));
	}
	
	Side endSide;
	int endHole, score;

	//container for the maximized score
	int extreme = -1 * sideSwitch(s) * 100;
	int maxima = sideSwitch(s) * 99;


	for (int i = 1; i <= b.holes(); i++) {
		//make the virtual move
		Board tB = b;
		int rounds = tB.beans(s, i) / (2 * tB.holes() + 1);
		if (!tB.sow(s, i, endSide, endHole))
			continue;
		
		//extra round
		if (endHole == 0)
			score = evaluate(tB, s, ac, depth-1);
		//capture
		else if (endSide == s && tB.beans(opponent(s), endHole) > 0 
				 && tB.beans(s, endHole) == (1 + rounds)) {
			
			tB.moveToPot(opponent(s), endHole, s);
			tB.moveToPot(s, endHole, s);
			score = evaluate(tB, opponent(s), ac, depth);
		}
		else 
			score = evaluate(tB, opponent(s), ac, depth);

		//update "best" solution
		if ( (sideSwitch(s) * score) > (sideSwitch(s) * extreme) ) {
			extreme = score;

			//TODO
			if (extreme == sideSwitch(s)*99)
				break;
		}
	}
	
	return extreme;
}

int SmartPlayer::sideSwitch(Side s) const {
	//switch (s) {
	//case NORTH:
	//	return 1;
	//	break;
	//case SOUTH:
	//	return -1;
	//	break;
	//}
	return (1 - 2 * s);
}



//int DebPlayer::chooseMove(const Board& b, Side s) const
//{
//	int difference = -999;
//	int bestHole = -1;
//	int depth = 0;
//	AlarmClock ac(4900);
//	choose(s, b, bestHole, difference, depth, ac);
//	return bestHole;
//
//} //-1?????
//
//void DebPlayer::choose(Side s, const Board& b, int& bestHole, int& difference, const int& depth, AlarmClock& ac) const
//{
//	if (b.beansInPlay(s) == 0 || b.beansInPlay(opponent(s)) == 0)
//	{
//		bestHole = -1;
//		difference = evaluate(b, s, depth);
//		return;
//	}
//
//	if ((b.beans(s, POT) > b.totalBeans() / 2
//		|| b.beans(opponent(s), POT) > b.totalBeans() / 2) && depth > 0) 
//	{
//		bestHole = -1;
//		difference = evaluate(b, s, depth);
//		return;
//	}
//
//	if ( depth >= m_depth || ac.timedOut())
//	{
//		bestHole = -1;
//		difference = evaluate(b, s, depth);
//		return;
//	}
//
//	Board temp = b;
//	Side endSide;
//	int endHole;
//	int capture;
//	int compare = (-100) * whichSide(depth);
//	int nextD, nextBest;
//	for (int i = 1; i <= b.holes(); i++)
//	{
//		if (temp.beans(s, i) == 0)
//		{
//			continue;
//		}
//
//		temp.sow(s, i, endSide, endHole);
//		while (endHole == 0) // if there is an extra round
//		{
//			choose(s, temp, nextBest, nextD, depth, ac);
//			if (!temp.sow(s, nextBest, endSide, endHole))
//			{
//				break;
//			}
//		}
//		capture = 1 + temp.beans(endSide, endHole) / (2 * temp.holes() + 1);
//		if (temp.beans(endSide, endHole) == capture && endSide == s && temp.beans(opponent(endSide), endHole) != 0)
//		{
//			temp.moveToPot(endSide, endHole, s);
//			temp.moveToPot(opponent(endSide), endHole, s);
//		}
//		///make a complete move
//
//		difference = evaluate(temp, s, depth);
//		if (difference == whichSide(depth) * 99)
//		{
//			bestHole = i;
//			return;
//		}
//		choose(opponent(s), temp, nextBest, nextD, depth + 1, ac);
//		temp = b;
//		if (whichSide(depth) > 0 && nextD > compare)
//		{
//			bestHole = i;
//			difference = nextD;
//			compare = nextD;
//		}
//		else if (whichSide(depth) < 0 && nextD < compare)
//		{
//			bestHole = i;
//			difference = nextD;
//			compare = nextD;
//		}
//
//	}
//	return;
//}
//
//int DebPlayer::evaluate(const Board& b, const Side& s, const int& depth) const
//{
//	if (b.beansInPlay(s) == 0 || b.beansInPlay(opponent(s)) == 0)
//	{
//		if ((b.beans(s, POT) - b.beans(opponent(s), POT) + b.beansInPlay(s) - b.beansInPlay(opponent(s))) > 0
//			|| b.beans(s, POT) > b.totalBeans()/2)
//		{
//			return 99 * whichSide(depth);
//		}
//		else if ((b.beans(s, POT) - b.beans(opponent(s), POT) + b.beansInPlay(s) - b.beansInPlay(opponent(s))) < 0
//			|| b.beans(opponent(s), POT) > b.totalBeans() / 2)
//		{
//			return -99 * whichSide(depth);
//		}
//	}
//
//	return (b.beans(s, POT) - b.beans(opponent(s), POT))*whichSide(depth);
//}
//
//int DebPlayer::whichSide(const int& depth) const
//{
//	return (2 * depth - (((depth + 1) / 2) * 4 - 1));
//	//return 1 if its sp's turn, -1 if its sp's opponent's turn
//}