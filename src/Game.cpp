#include <Game.h>

#include <stdio.h>	/* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>	/* time */

Game::~Game()
{
	delete window;
}

Game::Game()
{
	initializeVariables();
	initWindow();

	// init game objects
	initRandWalls();
	initGrid();
	initPlaneTable();
	initPlayer();
}

bool Game::running()
{
	return window->isOpen();
}

// functions
void Game::update()
{
	pollEvents();
}

void Game::initializeVariables()
{
	window = nullptr;
}

void Game::initWindow()
{
	videoMode.height = 730;
	videoMode.width = 1020;

	window = new RenderWindow(videoMode, "Bomberman", Style::Close);

	// set a framerate limit
	window->setFramerateLimit(144);
}

void Game::pollEvents()
{
	while (window->pollEvent(event))
	{
		for (int i = 0; i < 180; i++)
		{
			window->draw(grid[i]);
		}

		switch (event.type)
		{
			case Event::Closed:
				window->close();
				break;

			default:
				break;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		player.move(-1.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		player.move(0.0f, -1.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		player.move(0.0f, 1.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		player.move(1.0f, 0.0f);
	}
}

void Game::render()
{
	// clear window
	window->clear();

	// draw objects
	for (int i = 0; i < 187; i++)
	{
		window->draw(grid[i]);
	}

	window->draw(planeTable);
	window->draw(player);
	window->display();
}

void Game::initGrid()
{
	int yPos = 84, xPos = 0;
	for (int y = 0, counter = 0; y < 11; y++, yPos += 60, xPos = 0)
	{
		for (int x = 0; x < 17; x++, counter++, xPos += 60)
		{
			if (x % 2 == 0 && y % 2 == 0)
			{
				mapMatrix[y][x] = -1;
			}
			else if (y == 0 || x == 0 || x == 16 || y == 10)
			{
				mapMatrix[y][x] = -1;
			}

			switch (mapMatrix[y][x])
			{
				case -1:
					if (!wall.loadFromFile("./content/wall.png"))
					{
						cout << "Texture not found" << endl;
					}
					grid[counter].setTexture(pWall);
					break;
				case 3:
					grid[counter].setFillColor(Color::Yellow);
					break;
				case 0:
					grid[counter].setFillColor(Color(16, 122, 48));
					break;
				default:
					break;
			}
			grid[counter].setPosition(xPos, yPos);
			grid[counter].setSize(Vector2f(60, 60));
		}
	}
}

void Game::initPlaneTable()
{
	planeTable.setFillColor(Color(246, 129, 0));
	planeTable.setSize(Vector2f(1020, 100));
	planeTable.setOutlineColor(Color(128, 23, 17));
	planeTable.setOutlineThickness(2.f);
	planeTable.setPosition(Vector2f(0, 0));
}

void Game::initRandWalls()
{
	srand(time(NULL));
	int nWalls = 20, randPosX, randPosY;

	for (int i = 0; i < nWalls;)
	{
		randPosX = rand() % 15 + 1;
		randPosY = rand() % 9 + 1;
		if (mapMatrix[randPosY][randPosX] != -1 && mapMatrix[randPosY][randPosX] != 3)
		{
			mapMatrix[randPosY][randPosX] = 3;
			i++;
		}
	}
}

void Game::initPlayer()
{
	player.setFillColor(Color::Blue);
	player.setSize(Vector2f(60, 60));
	player.setPosition(60, 144);
}