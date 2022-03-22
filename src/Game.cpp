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
	initPlaneTable();
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
	videoMode.height = 730;
	videoMode.width = 1020;

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
	window->clear();

	for (int i = 0; i < 187; i++)
	{
		window->draw(grid[i]);
	}

	// draw plane table
	window->draw(planeTable);

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

			if (mapMatrix[y][x] == -1)
			{
				if (!wall.loadFromFile("./content/wall.png"))
				{
					cout << "sussy" << endl;
				}

				grid[counter].setTexture(pWall);
			}
			else if (mapMatrix[y][x] == -1)
			{
				grid[counter].setFillColor(Color::Black);
			}
			else
			{
				grid[counter].setFillColor(Color(16, 122, 48));
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
