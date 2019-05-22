#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <windows.h>
#include <conio.h>
#endif

#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doBoardTests()
{
	Board b(3, 2);
	assert(b.holes() == 3 && b.totalBeans() == 12 &&
		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
	b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
		b.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
}

void doPlayerTests()
{
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge"  &&  hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	SmartPlayer sp("Lisa");
	assert(sp.name() == "Lisa" && !sp.isInteractive());
	Board b(3, 2);
	b.setBeans(SOUTH, 2, 0);
	//    
	//   2  2  2
	// 0         0
	//   2  0  2
	//    
	cout << "=========" << endl;
	int n = hp.chooseMove(b, SOUTH);
	cout << "=========" << endl;
	assert(n == 1 || n == 3);
	n = bp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
	n = sp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
}

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move();
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	g.display();
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);
}

void pve() {
	SmartPlayer bp1("Bart");
	HumanPlayer bp2("Homer");
	Board b(6, 4);


	Game g(b, &bp1, &bp2);

	g.play();
}

void pvp() {
	HumanPlayer bp1("Bart");
	HumanPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(SOUTH, 1, 1);
	Game g(b, &bp1, &bp2);

	g.play();
}

void demo() {
	SmartPlayer bp1("South");
	SmartPlayer bp2("North");
	Board b(6, 4);

	Game g(b, &bp1, &bp2);

	g.play();
}

void otherBoardTest() {
	//test on performence under multiple rounds
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 15);
	int endHole;
	Side endSide;
	b.sow(SOUTH, 1, endSide, endHole);
	assert(b.beans(SOUTH, 1) == 2);
	assert(b.beans(NORTH, POT) == 0);
	assert(b.beans(SOUTH, 2) == 3);
	assert(b.beans(SOUTH, 0) == 2);
	assert(endSide == SOUTH && endHole == 2);
	assert(b.totalBeans() == 15);
}

void otherGameTest() {
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 15);
	b.setBeans(NORTH, 2, 8);
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Game g(b, &bp1, &bp2);
	//capture with multiple rounds
	g.move();
	assert(g.beans(SOUTH, 1) == 2);
	assert(g.beans(NORTH, POT) == 0);
	assert(g.beans(NORTH, 2) == 0);
	assert(g.beans(SOUTH, 2) == 0);
	assert(g.beans(SOUTH, 0) == 15);
}

void extraRoundTest() {
	//extra round after multiple rounds
	Board c(3, 0);
	c.setBeans(SOUTH, 1, 17);
	c.setBeans(NORTH, 1, 1);
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Game g2(c, &bp1, &bp2);
	g2.move();
	assert(g2.beans(SOUTH, 1) == 0);
	assert(g2.beans(SOUTH, 2) == 4);
	assert(g2.beans(SOUTH, 3) == 4);
	assert(g2.beans(SOUTH, 0) == 3);
}

void DebTest() {
	//testing constructor of board
	Board test(6, 4);
	Board bad(-1, -1);
	assert(bad.beansInPlay(SOUTH) == 0);

	// testing holes
	assert(bad.holes() == 1);
	assert(test.holes() == 6);


	//testing beans()
	for (int i = 7; i < 100; i++)
	{
		assert(test.beans(SOUTH, i) == -1);
		assert(test.beans(NORTH, i) == -1);
	}
	assert(test.beans(SOUTH, -1) == -1);
	assert(test.beans(NORTH, -1) == -1);

	assert(test.beans(SOUTH, 0) == 0);
	assert(test.beans(NORTH, 0) == 0);
	assert(test.beans(NORTH, 1) == 4);
	Side endSide = NORTH;
	int endHole = 0;
	test.sow(NORTH, 1, endSide, endHole);
	assert(endSide == SOUTH);
	assert(endHole == 3);
	assert(test.beans(NORTH, 1) == 0);
	assert(test.beans(SOUTH, 1) == 5);
	assert(test.beans(SOUTH, 2) == 5);
	assert(test.beans(SOUTH, 3) == 5);
	test.sow(SOUTH, 5, endSide, endHole);
	assert(test.beans(SOUTH, POT) == 1);
	assert(endSide == NORTH);
	assert(endHole == 5);
	assert(test.moveToPot(NORTH, 4, SOUTH));
	assert(test.beans(NORTH, 4) == 0);
	assert(test.beans(SOUTH, POT) == 5);
	assert(test.setBeans(SOUTH, POT, 3));
	assert(test.beans(SOUTH, POT) == 3);


	Board test2(3, 2);
	assert(!test2.sow(SOUTH, POT, endSide, endHole));
	assert(endSide == NORTH);
	assert(endHole == 5);
	assert(!test2.sow(NORTH, POT, endSide, endHole));
	assert(endSide == NORTH);
	assert(endHole == 5);

	for (int i = 4; i < 100; i++)
	{
		assert(!test2.sow(SOUTH, POT, endSide, endHole));
		assert(endSide == NORTH);
		assert(endHole == 5);
		assert(!test2.sow(NORTH, POT, endSide, endHole));
		assert(endSide == NORTH);
		assert(endHole == 5);
	}

	assert(test2.sow(SOUTH, 1, endSide, endHole));
	assert(endSide == SOUTH);
	assert(endHole == 3);
	assert(test2.sow(NORTH, 1, endSide, endHole));
	assert(endSide == SOUTH);
	assert(endHole == 1);
	assert(test2.sow(SOUTH, 2, endSide, endHole));
	assert(endSide == NORTH);
	assert(endHole == 3);
	assert(test2.sow(NORTH, 2, endSide, endHole));
	assert(endSide == NORTH);
	assert(endHole == 0);

	Board test3(3, 10);
	assert(test3.sow(SOUTH, 1, endSide, endHole));
	assert(endSide == SOUTH);
	assert(endHole == 0);
	assert(test3.beans(SOUTH, 2) == 12);
	assert(test3.beans(SOUTH, 3) == 12);
	assert(test3.beans(endSide, endHole) == 2);
	assert(test3.beans(NORTH, 0) == 0);

	assert(test3.beans(NORTH, 1) == 11);
	assert(test3.beans(NORTH, 2) == 11);
	assert(test3.beans(NORTH, 3) == 11);

	//test moveToPot
	assert(!test3.moveToPot(NORTH, 0, SOUTH));
	assert(!test3.moveToPot(NORTH, 0, NORTH));
	assert(!test3.moveToPot(SOUTH, 0, NORTH));
	assert(!test3.moveToPot(SOUTH, 0, SOUTH));

	assert(test3.beans(SOUTH, 2) == 12);
	assert(test3.beans(SOUTH, 3) == 12);
	assert(test3.beans(endSide, endHole) == 2);
	assert(test3.beans(NORTH, 0) == 0);

	assert(test3.beans(NORTH, 1) == 11);
	assert(test3.beans(NORTH, 2) == 11);
	assert(test3.beans(NORTH, 3) == 11);
	assert(test3.beans(SOUTH, 1) == 1);
	assert(test3.moveToPot(NORTH, 1, NORTH));
	assert(test3.beans(NORTH, 1) == 0);
	assert(test3.beans(NORTH, 0) == 11);

	assert(!test3.moveToPot(NORTH, -1, SOUTH));
	assert(!test3.moveToPot(NORTH, -1, NORTH));
	assert(!test3.moveToPot(SOUTH, -1, NORTH));
	assert(!test3.moveToPot(SOUTH, -1, SOUTH));

	assert(test3.beans(NORTH, 1) == 0);
	assert(test3.beans(NORTH, 0) == 11);
	assert(test3.beans(NORTH, 2) == 11);
	assert(test3.beans(NORTH, 3) == 11);
	assert(test3.beans(SOUTH, 2) == 12);
	assert(test3.beans(SOUTH, 3) == 12);
	assert(test3.beans(SOUTH, 1) == 1);

	for (int i = 4; i < 50; i++)
	{
		assert(!test3.moveToPot(NORTH, i, SOUTH));
		assert(!test3.moveToPot(NORTH, i, NORTH));
		assert(!test3.moveToPot(SOUTH, i, NORTH));
		assert(!test3.moveToPot(SOUTH, i, SOUTH));

		assert(test3.beans(NORTH, 1) == 0);
		assert(test3.beans(NORTH, 0) == 11);
		assert(test3.beans(NORTH, 2) == 11);
		assert(test3.beans(NORTH, 3) == 11);
		assert(test3.beans(SOUTH, 2) == 12);
		assert(test3.beans(SOUTH, 3) == 12);
		assert(test3.beans(SOUTH, 1) == 1);
		assert(test3.beans(SOUTH, 0) == 2);
	}

	//test setBeans
	for (int i = -1; i < 100; i++)
	{

		assert(!test3.setBeans(SOUTH, i, 1));
		assert(!test3.setBeans(NORTH, i, 1));
		if (i == -1)
		{
			i = 3;
		}
	}

	assert(test3.beans(NORTH, 1) == 0);
	assert(test3.beans(NORTH, 0) == 11);
	assert(test3.beans(NORTH, 2) == 11);
	assert(test3.beans(NORTH, 3) == 11);
	assert(test3.beans(SOUTH, 2) == 12);
	assert(test3.beans(SOUTH, 3) == 12);
	assert(test3.beans(SOUTH, 1) == 1);
	assert(test3.beans(SOUTH, 0) == 2);
	for (int i = 1; i < 4; i++)
	{

		assert(!test3.setBeans(SOUTH, i, -1));
		assert(!test3.setBeans(NORTH, i, -1));

	}
	assert(test3.beans(NORTH, 1) == 0);
	assert(test3.beans(NORTH, 0) == 11);
	assert(test3.beans(NORTH, 2) == 11);
	assert(test3.beans(NORTH, 3) == 11);
	assert(test3.beans(SOUTH, 2) == 12);
	assert(test3.beans(SOUTH, 3) == 12);
	assert(test3.beans(SOUTH, 1) == 1);
	assert(test3.beans(SOUTH, 0) == 2);
	for (int i = 1; i < 4; i++)
	{

		assert(test3.setBeans(SOUTH, i, 2));
		assert(test3.setBeans(NORTH, i, 2));

	}

	SmartPlayer s("Smart");
	HumanPlayer h("Human");
	BadPlayer b("Bad");


	//test name and isinteractive;
	assert(s.name() == "Smart");
	assert(h.name() == "Human");
	assert(b.name() == "Bad");
	assert(!s.isInteractive());
	assert(!b.isInteractive());
	assert(h.isInteractive());



	/*SmartPlayer a("Adam");
	SmartPlayer b("Bob");
	Board board(6, 4);*/


	/*board.setBeans(NORTH, 0 ,9);
	board.setBeans(NORTH, 1, 1);
	board.setBeans(NORTH, 2, 1);
	board.setBeans(NORTH, 3, 50);
	board.setBeans(NORTH, 4, 4);
	board.setBeans(NORTH, 5, 3);
	board.setBeans(SOUTH, 0, 10);
	board.setBeans(SOUTH, 1, 4);
	board.setBeans(SOUTH, 2, 50);
	board.setBeans(SOUTH, 3, 50);
	board.setBeans(SOUTH, 4, 2);
	board.setBeans(SOUTH, 5, 0);*/

	Board New(6, 10);
	Board New2(3, 4);

	while (New.beansInPlay(SOUTH) != 0)
	{
		int hole = b.chooseMove(New, SOUTH);
		assert(hole > 0 && hole < 7);
		New.sow(SOUTH, hole, endSide, endHole);
	}
	New = New2;
	while (New.beansInPlay(NORTH) != 0 && New.beansInPlay(SOUTH) != 0)
	{
		int hole = s.chooseMove(New, NORTH);
		assert(hole > 0 && hole < 7);
		New.sow(NORTH, hole, endSide, endHole);
	}

	//test Game
	//test status
	Game a(New, &b, &s);
	bool over, haswinner;
	Side winner;
	a.status(over, haswinner, winner);
	assert(over);
	assert(haswinner);
	assert(SOUTH);

	Game x(bad, &s, &b);
	x.status(over, haswinner, winner);
	assert(over);
	assert(!haswinner);

	//test move
	Board y(3, 2);
	y.setBeans(SOUTH, 1, 1);
	y.setBeans(NORTH, 3, 1);
	//	    2  2  1
	//   0          0
	//      1  2  2


	Game k(y, &h, &b);
	k.move();
	//	    2  0  1
	//   0          4
	//      0  0  3
	assert(k.beans(SOUTH, 1) == 0);
	assert(k.beans(SOUTH, 2) == 0);
	assert(k.beans(SOUTH, 3) == 3);
	assert(k.beans(SOUTH, POT) == 4);
	assert(k.beans(NORTH, 2) == 0);

}

int main()
{
	//doBoardTests();
	//doPlayerTests();
	//doGameTests();
	//pve();
	//pvp();
	demo();

	//otherBoardTest();
	//otherGameTest();
	//extraRoundTest();

	//DebTest();

	cerr << "PASS" << endl;
	return 0;
}