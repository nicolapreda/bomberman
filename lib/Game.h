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

	//create enemy directions
	int enemiesDirection[4], score, level, lastGridEditedX = 1, lastGridEditedY = 1, lastKeyPressed, life;

	bool bombCountDown;
	RectangleShape planeTable;

	Sprite grid[187], player, bomb, enemy[4];
	//create a timer
	Clock gameClock, respawnClock;

	// main font
	Font font;
	// textures
	sf::Texture permWall, wall, playertexture, grass, bombTexture, enemyTexture, floor;
	sf::Text timerString, scoreString, levelString, lifeString;

	/*0 = terrain, 1 = player, 2 = enemies, 4 = perm walls, 3= walls*/
	int mapMatrix[11][17] = { 0 };

	// private functions
	void initGrid();
	void initRandWalls();
	void initPlayer();

	void initializeVariables();
	void initWindow();

	void initPlaneTable();
	void initEnemies();

	void checkDestroyedItems();
	void updateGrid(Sprite entity, int type);
	bool checkGridCollision(Sprite entity);
	bool checkBombCollision(Sprite entity);

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
