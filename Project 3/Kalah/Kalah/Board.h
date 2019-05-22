#ifndef BOARD
#define BOARD 1

#include "Side.h" //so this line is necessary?
#include <vector>

class Board {
public:
	Board(int nHoles, int nInitialBeansPerHole);

	int holes() const { 
		//getter for number of holes on each side
		return m_nHoles;
	}

	int beans(Side s, int hole) const { 
		//getter for beans
		if (hole > m_nHoles || hole < 0)
			return -1;
		else
			return m_holes[locate(s, hole, 0)];
	}
	
	int beansInPlay(Side s) const; //return total beans of one player in the holes
	int totalBeans() const; //return all beans in the game //total number of beans might change
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner); //operats on the number of beans in holes and pots
	bool setBeans(Side s, int hole, int beans);

private:
	std::vector<int> m_holes; //data storage

	int locate(Side side, int hole, int step) const; //should return the mapped location from side and hole num
	int m_nHoles; //how many holes on each side
	int m_totalHoles; //total number of holes, calculated from nHoles
};

#endif // !BOARD