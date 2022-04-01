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
	Clock bombClock;

	// game objects
	float xEnemyVelocity = 0.4, yEnemyVelocity = 0.4, xPosition, yPosition;
	//create enemy directions
	int enemiesDirection[4];

	int score;
	RectangleShape planeTable;

	Sprite grid[187], player, bomb, enemy[4];
	//create a timer
	Clock gameClock;

	// main font
	Font font;
	// textures
	sf::Texture permWall, wall, playertexture, grass, bombTexture, enemyTexture;
	sf::Text timerString, scoreString;

	/*0 = terrain, 1 = player, 2 = enemies, -1 = perm walls, 3= walls*/
	int mapMatrix[11][17] = { 0 };

	// private functions
	void initGrid();
	void initRandWalls();
	void initPlayer();

	void initializeVariables();
	void initWindow();
	void updateGrid();
	void initPlaneTable();
	void initEnemies();

	bool checkGridCollision(Sprite entity);

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
