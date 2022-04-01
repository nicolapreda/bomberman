#include <Game.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	initEnemies();
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
	// move enemies
	for (int i = 0; i < 4; i++)
	{
		//select a random enemy direction and check every collision
		switch (enemiesDirection[i])
		{
			case 0:

				enemy[i].move(0.f, -1.f);
				// check collision
				if (checkGridCollision(enemy[i]))
				{
					cout << "collision detected" << endl;
					enemiesDirection[i] = 1;
				}

				break;
			case 1:

				enemy[i].move(0.f, 1.f);
				// check collision
				if (checkGridCollision(enemy[i]))
				{
					cout << "collision detected" << endl;

					enemiesDirection[i] = 0;
				}
				break;
			case 2:

				enemy[i].move(-1.f, 0);
				// check collision
				if (checkGridCollision(enemy[i]))
				{
					cout << "collision detected" << endl;

					enemiesDirection[i] = 3;
				}
				break;
			case 3:

				enemy[i].move(1.f, 0);
				// check collision
				if (checkGridCollision(enemy[i]))
				{
					cout << "collision detected" << endl;

					enemiesDirection[i] = 2;
				}
				break;
			default:
				break;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		player.move(-1.0f, 0.0f);
		if (checkGridCollision(player))
		{
			player.move(1.0f, 0.0f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		player.move(0.0f, -1.0f);
		if (checkGridCollision(player))
		{
			player.move(0.0f, 1.0f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		player.move(0.0f, 1.0f);
		if (checkGridCollision(player))
		{
			player.move(0.0f, -1.0f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		player.move(1.0f, 0.0f);
		if (checkGridCollision(player))
		{
			player.move(-1.0f, 0.0f);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Space))
	{
		bomb.setPosition(player.getPosition().x, player.getPosition().y);
		if (!bombTexture.loadFromFile("./content/bomb.png"))
		{
			cout << "Texture not loaded" << endl;
		}
		bomb.setTexture(bombTexture);
		//add a 2 seconds timer
		bombClock.restart();
	}
}

void Game::render()
{
	// clear window
	window->clear(Color(16, 122, 48));

	// draw grids
	for (int i = 0; i < 187; i++)
	{
		window->draw(grid[i]);
	}
	// draw enemies
	for (int i = 0; i < 4; i++)
	{
		window->draw(enemy[i]);
		//select random directions
		int randDirection = rand() % 4;
		//insert into enemiesDirection
		enemiesDirection[i] = randDirection;
	}

	window->draw(planeTable);

	window->draw(player);
	window->draw(bomb);

	//set timer string
	timerString.setString("Time: " + to_string(gameClock.getElapsedTime().asSeconds()));
	window->draw(timerString);

	//set score string
	scoreString.setString("Score: " + to_string(score));
	window->draw(scoreString);

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
					if (!permWall.loadFromFile("./content/perm_wall.png"))
					{
						cout << "Texture not loaded" << endl;
					}
					grid[counter].setTexture(permWall);
					break;
				case 3:
					if (!wall.loadFromFile("./content/wall.png"))
					{
						cout << "Texture not loaded" << endl;
					}
					grid[counter].setTexture(wall);
					break;

				default:
					break;
			}
			grid[counter].setPosition(xPos, yPos);
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

	//draw the timer
	//load font
	if (!font.loadFromFile("./content/ArcadeClassic.ttf"))
	{
		cout << "Font not loaded" << endl;
	}
	//set the text
	timerString.setFont(font);
	timerString.setPosition(Vector2f(10, 10));
	timerString.setFillColor(Color::White);
	timerString.setCharacterSize(30);
	gameClock.restart();

	//set score string
	scoreString.setFont(font);
	scoreString.setPosition(Vector2f(10, 50));
	scoreString.setFillColor(Color::White);
	scoreString.setCharacterSize(30);
}

void Game::initRandWalls()
{
	srand(time(NULL));
	int nWalls = 20, randPosX, randPosY;

	for (int i = 0; i < nWalls;)
	{
		randPosX = rand() % 15 + 1;
		randPosY = rand() % 9 + 1;
		if (mapMatrix[randPosY][randPosX] != -1 && mapMatrix[randPosY][randPosX] != 3 && mapMatrix[randPosY][randPosX] != 1)
		{
			mapMatrix[randPosY][randPosX] = 3;
			i++;
		}
	}
}

void Game::initPlayer()
{
	if (!playertexture.loadFromFile("./content/main-Sheet.png"))
	{
		cout << "Texture not loaded" << endl;
	}
	player.setTexture(playertexture);
	player.setPosition(65, 150);
}

void Game::initEnemies()
{
	for (int i = 0, xPos = 180, yPos = 145; i < 4; i++, xPos += 120, yPos += 120)
	{
		if (!enemyTexture.loadFromFile("./content/enemy.png"))
		{
			cout << "Texture not loaded" << endl;
		}
		enemy[i].setTexture(enemyTexture);
		enemy[i].setPosition(xPos, yPos);
	}
}

bool Game::checkGridCollision(Sprite entity)
{

	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (entity.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
			{

				if (mapMatrix[y][x] == -1 || mapMatrix[y][x] == 3)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return false;
}
