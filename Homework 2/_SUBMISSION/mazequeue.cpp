#include <queue>
#include <iostream>
#include <cassert>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	const char ENCOUNTERED = 'E';
	queue<Coord> trails;
	trails.push(Coord(sr, sc));
	maze[sr][sc] = ENCOUNTERED;
	while (!trails.empty()) {
		Coord current = trails.front();
		trails.pop();

		if (current.r() == er && current.c() == ec)
			return true;

		if (current.r() < 9 && maze[current.r() + 1][current.c()] == '.') {
			trails.push(Coord(current.r() + 1, current.c()));
			maze[current.r() + 1][current.c()] = ENCOUNTERED;
		}

		if (current.c() > 0 && maze[current.r()][current.c() - 1] == '.') {
			trails.push(Coord(current.r(), current.c() - 1));
			maze[current.r()][current.c() - 1] = ENCOUNTERED;
		}

		if (current.r() > 0 && maze[current.r() - 1][current.c()] == '.') {
			trails.push(Coord(current.r() - 1, current.c()));
			maze[current.r() - 1][current.c()] = ENCOUNTERED;
		}

		if (current.c() < 9 && maze[current.r()][current.c() + 1] == '.') {
			trails.push(Coord(current.r(), current.c() + 1));
			maze[current.r()][current.c() + 1] = ENCOUNTERED;
		}
	}

	return false;
}

int main()
{
	char maze[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','.','X','X','.','X','X','X','.','X' },
	{ 'X','X','X','.','.','.','.','X','.','X' },
	{ 'X','.','X','X','X','.','X','X','X','X' },
	{ 'X','.','X','.','.','.','X','.','.','X' },
	{ 'X','.','.','.','X','.','X','.','.','X' },
	{ 'X','X','X','X','X','.','X','.','X','X' },
	{ 'X','.','.','.','.','.','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

	char maze2[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	assert(pathExists(maze2, 3, 5, 9, 9) == false);


	char maze3[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','x','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	assert(pathExists(maze3, 3, 5, 8, 8) == false);

	char maze4[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','x','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	assert(pathExists(maze4, 4, 1, 8, 8) == true);

	char maze5[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','x','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','X','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	assert(pathExists(maze5, 4, 1, 8, 1) == false);

	char maze6[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','x','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	assert(pathExists(maze6, 4, 1, 8, 8) == true);
	
	cout << "PASS" << endl;

	return 0;
}

