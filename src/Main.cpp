#include "Platform/Platform.hpp"
// custom lib
#include <Game.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace util;
using namespace std;
using namespace sf;

int main()
{
	// init game engine
	Game game;

	// initialize font, text and variables for main menu
	Font font;
	Text mainMenu[3];
	font.loadFromFile("./src/Assets/Fonts/ArcadeClassic.ttf");

	// load background
	Texture texture;
	texture.loadFromFile("./src/Assets/main_background.gif");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	float xPos = (float)1024 / 2;
	float yPos = (float)720 / 2;
	sprite.setPosition(xPos, yPos);

	for (int i = 0, h = 100; i < 3; i++, h += 200)
	{
		mainMenu[i].setFont(font);
		mainMenu[i].setOutlineThickness(2);
		mainMenu[i].setOutlineColor(Color::Black);

		mainMenu[i].setCharacterSize(60);
		mainMenu[i].setPosition(200, h);
		mainMenu[i].setFillColor(Color::Blue);
		switch (i)
		{
			case 0:
				mainMenu[i].setFillColor(Color::White);
				mainMenu[i].setString("Play");
				break;
			case 1:
				mainMenu[i].setString("Options");
				break;
			case 2:
				mainMenu[i].setString("Exit");
				break;
			default:
				break;
		}
	}

	while (game.running())
	{
		game.update();

		game.render();
	}
}