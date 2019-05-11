#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	const char ENCOUNTERED = 'E';
	maze[sr][sc] = ENCOUNTERED;

	if (sr == er && sc == ec)
		return true;

	if (sr < 9 && maze[sr + 1][sc] == '.') {
		if (pathExists(maze, sr + 1, sc, er, ec))
			return true;
	}

	if (sc > 0 && maze[sr][sc - 1] == '.') {
		if (pathExists(maze, sr, sc - 1, er, ec))
			return true;
	}

	if (sr > 0 && maze[sr - 1][sc] == '.') {
		if (pathExists(maze, sr - 1, sc, er, ec))
			return true;
	}

	if (sc < 9 && maze[sr][sc + 1] == '.') {
		if (pathExists(maze, sr, sc + 1, er, ec))
			return true;
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
