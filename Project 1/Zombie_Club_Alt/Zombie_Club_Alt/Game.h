#ifndef GAME
#define GAME 1

class Arena;

int decodeDirection(char dir);

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nZombies);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;
};

#endif
