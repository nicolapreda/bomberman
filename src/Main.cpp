#include "Platform/Platform.hpp"
// custom lib
#include <Game.h>

int main()
{

	// initialize window
	RenderWindow MainMenu(VideoMode(1020, 730), "Bomberman", Style::Close);

	// initialize font, text and variables for main menu
	Font font;
	Text mainMenu[3];
	font.loadFromFile("./src/Assets/Fonts/ArcadeClassic.ttf");
	int mainMenuSelected = 0;

	// load background
	Texture texture;
	texture.loadFromFile("./src/assets/background.png");
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
				mainMenu[i].setString("Settings");
				break;
			case 2:
				mainMenu[i].setString("Exit");
				break;
			default:
				break;
		}
	}

	while (MainMenu.isOpen())
	{
		Event event;

		while (MainMenu.waitEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
					MainMenu.close();
					break;
				case Event::KeyReleased:
					if (event.key.code == Keyboard::Up)
					{
						if (mainMenuSelected > 0)
						{
							mainMenu[mainMenuSelected].setFillColor(Color::Blue);
							MainMenu.clear();
							mainMenuSelected--;
							mainMenu[mainMenuSelected].setFillColor(Color::White);
						}
						break;
					}
					if (event.key.code == Keyboard::Down)
					{
						if (mainMenuSelected < 2)
						{
							mainMenu[mainMenuSelected].setFillColor(Color::Blue);
							MainMenu.clear();
							mainMenuSelected++;

							mainMenu[mainMenuSelected].setFillColor(Color::White);
						}
						break;
					}
					if (event.key.code == Keyboard::Return)
					{
						int x = mainMenuSelected;
						// init game engine
						Game game;

						switch (x)
						{
							case 0:
								MainMenu.close();
								while (game.running())
								{
									game.update();
									game.render();
								}

								break;
							case 1:
								MainMenu.close();
								while (game.running())
								{
									game.update();
									game.render();
								}

								break;
							case 2:
								MainMenu.close();
								break;
							default:
								break;
						}
					}
					break;
				default:
					break;
			}

			MainMenu.clear();
			// draw texture
			MainMenu.draw(sprite);

			MainMenu.draw(mainMenu[0]);
			MainMenu.draw(mainMenu[1]);
			MainMenu.draw(mainMenu[2]);

			MainMenu.display();
		}
	}

	// call main functions when the game is running
}