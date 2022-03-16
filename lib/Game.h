#include "Platform/Platform.hpp"

// rand libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace sf;
using namespace std;

class Game
{
private:
	// variables
	// window
	RenderWindow* window;
	Event event;
	VideoMode videoMode;

	// game objects
	float xVelocity = 3, yVelocity = 3, xPosition, yPosition;
	RectangleShape enemy, wall[27], permWall[30], player;

	int mapMatrix[4][6];

	// private functions
	void initDefWalls();
	void initRandWalls();

	void initializeVariables();
	void initWindow();
	void initEnemies();
	void initPlayer();

public:
	// constructors
	Game();
	virtual ~Game();
	// accessors
	bool running();

	// functions
	void update();
	void pollEvents();
	void render();
};
