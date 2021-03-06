#pragma once

#include "Platform/Platform.hpp"

// libraries for "rand" function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace sf;
using namespace std;

class MainGame
{
private:
	// variables
	// window
	RenderWindow* window;
	Event event;
	VideoMode videoMode;
	Clock bombClock;

	//create enemy directions
	int enemiesDirection[10], score, lastGridEditedX = 1, lastGridEditedY = 1, life, clockInt, timer, enemiesDestroyed, lastKeyPressX, lastKeyPressed, buttonResultSelected;

	bool bombCountDown, isDoorPlaced, isKeyPlaced, isKeyRevealed, isDoorRevealed, isKeyUnlocked, showDamagedZones;
	RectangleShape planeTable;

	Sprite grid[187], player, bomb, enemy[10], door, key;
	//create a timer
	Clock gameClock, respawnClock, damageClock;

	// main font
	Font font;
	// textures
	sf::Texture permWall, wall, playerTexture, grass, bombTexture, enemyTexture, floor, doorTexture, keyTexture;
	sf::Text timerString, scoreString, levelString, lifeString;

	/*0 = terrain, 1 = player, 3 = perm walls, 2= walls, > 3 = enemies*/
	int mapMatrix[11][17] = { 0 };

	// private functions
	void initGrid();
	void initPlayer();

	void initializeVariables();
	void initWindow();

	void initPlaneTable();
	void initEnemies();
	void updateObjects();
	void resultPage(int result);

	void checkDestroyedItems();
	void updateGrid(Sprite entity, int type);
	bool checkGridCollision(Sprite entity);
	bool checkBombCollision(Sprite entity);

	// updated levels and enemies speed
	int updateLevel(int addLevel);
	float updateEnemySpeed(int addSpeed);

public:
	// constructors
	MainGame();
	virtual ~MainGame();
	// accessors
	bool running();

	// functions
	void update();
	void pollEvents();
	void render();
};
