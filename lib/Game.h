#include "Platform/Platform.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace util;
using namespace std;
using namespace sf;

class Game
{
private:
	// variables
	// window
	RenderWindow* window;
	Event event;
	VideoMode videoMode;

	// game objects
	RectangleShape enemy;

	// private functions
	void initializeVariables();
	void initWindow();
	void initEnemies();

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
