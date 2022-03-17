#include <Game.h>

Game::~Game()
{
	delete window;
}

Game::Game()
{
	initializeVariables();
	initWindow();
	initGrid();
}

bool Game::running()
{
	return window->isOpen();
}
// accessors

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
	videoMode.height = 720;
	videoMode.width = 1024;

	window = new RenderWindow(videoMode, "Bomberman", Style::Close);

	// set a framerate limit
	window->setFramerateLimit(60);
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
}

void Game::render()
{
	// clear window
	window->clear(Color::Yellow);

	for (int i = 0; i < 180; i++)
	{
		window->draw(grid[i]);
	}

	window->display();
}

void Game::initGrid()
{
	int yPos = 84, xPos = 0;
	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			if (x % 2 == 0 && y % 2 == 0)
			{
				mapMatrix[y][x] = -1;
			}
			else if (y == 0 || x == 0 || x == 16 || y == 10)
			{
				mapMatrix[y][x] = -1;
			}

			if (mapMatrix[y][x] == -1)
			{
				grid[counter].setFillColor(Color::Black);
			}
			else
			{
				grid[counter].setFillColor(Color::Green);
			}

			grid[counter].setPosition(xPos, yPos);
			grid[counter].setSize(Vector2f(60, 60));
			xPos += 60;
		}
		yPos += 60;
		xPos = 0;
	}
}
