#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cmath>
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole) {
	if (nHoles < 1)
		nHoles = 1;
	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;

	m_nHoles = nHoles;
	m_totalHoles = (nHoles + 1) * 2;

	//m_holes = new int[2 * m_nHoles + 2];
	//this sequence is fucked up
	//has nothing to do with actual mapping
	for (int i = 0; i < m_totalHoles; i++)
		m_holes.push_back(nInitialBeansPerHole);
	for (int i = 0; i < 2; i++)
		m_holes[i*m_totalHoles / 2] = 0;
}


int Board::beansInPlay(Side s) const {
	//return total beans of one player
	int count = 0;
	for (int i = 1; i <= m_nHoles; i++)
		count += m_holes[locate(s, i, 0)];

	return count;
}


int Board::totalBeans() const {
	//return all beans in the game //total number of beans might change
	int count = 0;
	for (int i = 0; i < m_totalHoles; i++)
		count += m_holes[i];

	return count;
}


bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	if (hole < 1 || hole > m_nHoles || beans(s, hole) == 0)
		return false;

	hole = locate(s, hole, 0);
	int nBeans = m_holes[hole];
	m_holes[hole] = 0; //remove beans
	
	int oPot = (1 - s) * (m_nHoles + 1);

	for (int i = 0; i < nBeans; i++) {
		hole = (hole + 1) % m_totalHoles; //moving to next spot
		if (hole != oPot) //if it's not opponent pot
			m_holes[hole]++;
		else
			i--; //skip this location
	}

	//set endside
	if (hole <= m_totalHoles/2 && hole > 0)
		endSide = SOUTH;
	else
		endSide = NORTH;

	//set endHole
	endHole = abs((1 - endSide) * m_totalHoles - hole) % (m_totalHoles/2); 
	//hey this is a function for converting actual location to hole number!
	//it's stupid since the endSide is required, even though the side is determined by each location

	return true;
}


bool Board::moveToPot(Side s, int hole, Side potOwner) {
	if (hole > m_nHoles || hole < 1)
		return false;
	else {
		hole = locate(s, hole, 0); //find hole
		int nBeans = m_holes[hole];
		m_holes[hole] = 0; //remove beans

		m_holes[locate(potOwner, 0, 0)] += nBeans; //hope it works

		return true;
	}
}


bool Board::setBeans(Side s, int hole, int beans) {
	if (hole < 0 || hole > m_nHoles || beans < 0)
		return false;
	else {
		m_holes[locate(s, hole, 0)] = beans;
		return true;
	}
}


int Board::locate(Side side, int hole, int step) const {
	//returns the actual location of the element in array
	hole = abs((1 - side) * m_totalHoles - hole);
	if (hole == 0)
		hole += side * m_totalHoles / 2;
	return ((hole + step) % m_totalHoles);
}