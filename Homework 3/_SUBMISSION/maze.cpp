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