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
	RectangleShape enemy, grid[187], player, planeTable;

	// main matrix
	/*0 = terrain, 1 = player, 2 = enemies, -1 = perm walls, 3= walls*/
	int mapMatrix[11][17] = { 0 };
	// textures
	sf::Texture permWall;
	const sf::Texture* pWall = &permWall;

	sf::Texture wall;
	const sf::Texture* tWall = &wall;

	// private functions
	void initGrid();
	void initRandWalls();
	void initPlayer();

	void initializeVariables();
	void initWindow();
	void updateGrid();
	void initPlaneTable();

	bool checkCollision();

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
