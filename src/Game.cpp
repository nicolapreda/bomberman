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
	initGrid();
	initPlaneTable();
	initPlayer();
	initEnemies();

	// select enemies direction
	for (int i = 4; i < 10; i++)
	{
		//select random directions
		int randDirection = rand() % 4;
		//insert into enemiesDirection
		enemiesDirection[i] = randDirection;
	}

	//init respawn clock
	respawnClock.restart();
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
	// init main variables
	level = 1;
	life = 3;
	score = 0;
	window = new RenderWindow(videoMode, "Bomberman | Level " + to_string(level), Style::Close);

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

	for (int i = 4; i < 10; i++)
	{
		switch (enemiesDirection[i])
		{
			case 0:
				enemy[i].move(0, -1.f);
				//check collisions
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{
					enemy[i].move(0, 1.f);
					enemiesDirection[i] = rand() % 4;
				}

				// update grid
				updateGrid(enemy[i], i);

				break;
			case 1:
				enemy[i].move(0, 1.f);
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{
					enemy[i].move(0, -1.f);
					enemiesDirection[i] = rand() % 4;
				}

				// update grid
				updateGrid(enemy[i], i);
				break;
			case 2:
				enemy[i].move(-1.f, 0);
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{
					enemy[i].move(1.f, 0);
					enemiesDirection[i] = rand() % 4;
				}

				// update grid
				updateGrid(enemy[i], i);
				break;
			case 3:
				enemy[i].move(1.f, 0);
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{
					enemy[i].move(-1.f, 0);
					enemiesDirection[i] = rand() % 4;
				}
				// update grid
				updateGrid(enemy[i], i);
				break;
			default:
				break;
		}
	}

	//check if countdown is over
	if (bombClock.getElapsedTime().asSeconds() > 2 && bombCountDown == true)
	{
		checkDestroyedItems();
		bombCountDown = false;
		bomb.setPosition(-60.f, -60.f);
	}

	// check player movements

	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		if (checkPlayerBombCollision() == false)
		{

			player.move(-1.0f, 0.0f);
			if (checkGridCollision(player) || checkBombCollision(player) == true)
			{
				player.move(1.0f, 0.0f);
			}
		}
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		if (checkPlayerBombCollision() == false)
		{
			player.move(0.0f, -1.0f);
			if (checkGridCollision(player) || checkBombCollision(player) == true)
			{
				player.move(0.0f, 1.0f);
			}
		}

		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		if (checkPlayerBombCollision() == false)
		{

			player.move(0.0f, 1.0f);
			if (checkGridCollision(player) || checkBombCollision(player) == true)
			{
				player.move(0.0f, -1.0f);
			}
		}
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		if (checkPlayerBombCollision() == false)
		{

			player.move(1.0f, 0.0f);
			if (checkGridCollision(player) || checkBombCollision(player) == true)
			{
				player.move(-1.0f, 0.0f);
			}
		}
		updateGrid(player, 1);
	}

	// place bomb
	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && bombCountDown == false)
	{
		bomb.setPosition(player.getPosition().x, player.getPosition().y);
		if (!bombTexture.loadFromFile("./content/bomb.png"))
			cout << "Bomb texture not loaded!" << endl;
		bomb.setTexture(bombTexture);
		// start bomb countdown
		bombCountDown = true;
		bombClock.restart();
	}
}

void Game::render()
{
	// clear window
	window->clear();

	// draw grids
	for (int i = 0; i < 187; i++)
	{
		window->draw(grid[i]);
	}
	// draw enemies
	for (int i = 4; i < 10; i++)
	{
		window->draw(enemy[i]);
	}

	// check player collision with enemies
	for (int i = 4; i < 10; i++)
	{
		if (enemy[i].getGlobalBounds().intersects(player.getGlobalBounds()) && respawnClock.getElapsedTime().asSeconds() > 2)
		{
			life--;
			respawnClock.restart();
		}
	}

	// game over if life is 0
	if (life <= 0)
	{
		window->close();
	}

	// draw objects
	window->draw(planeTable);
	clockInt = gameClock.getElapsedTime().asSeconds();
	timer = 140;
	if (clockInt > timer)
	{
		window->close();
	}

	//set timer string
	timerString.setString("Time  " + to_string(timer - clockInt));
	window->draw(timerString);

	//set score string
	scoreString.setString("Score  " + to_string(score));
	window->draw(scoreString);

	//set life string
	lifeString.setString("Lifes  " + to_string(life));
	window->draw(lifeString);

	//set level string
	levelString.setString("Level  " + to_string(level));
	window->draw(levelString);

	window->draw(player);
	window->draw(bomb);

	window->display();

	//show mapmatrix
	cout << endl;

	for (int y = 0, counter = 0; y < 11; y++)
	{

		for (int x = 0; x < 17; x++, counter++)
		{
			cout << mapMatrix[y][x] << " ";
		}
		cout << endl;
	}
}

void Game::initGrid()
{
	srand(time(NULL));
	int nWalls = 20, randPosX, randPosY, randPosDoorX, randPosDoorY, randPosKeyY, randPosKeyX;

	int yPos = 84, xPos = 0;
	for (int y = 0, counter = 0; y < 11; y++, yPos += 60, xPos = 0)
	{
		for (int x = 0; x < 17; x++, counter++, xPos += 60)
		{
			// set permanent walls
			if (x % 2 == 0 && y % 2 == 0)
			{
				mapMatrix[y][x] = 3;
			}
			else if (y == 0 || x == 0 || x == 16 || y == 10)
			{
				mapMatrix[y][x] = 3;
			}

			switch (mapMatrix[y][x])
			{
				case 3:
					if (!permWall.loadFromFile("./content/perm_wall.png"))
					{
						cout << "Texture not loaded" << endl;
					}
					grid[counter].setTexture(permWall);
					break;
				case 0:
					if (!floor.loadFromFile("./content/grass.png"))
					{
						cout << "Texture not loaded" << endl;
					}
					grid[counter].setTexture(floor);
					break;

				default:
					break;
			}
			grid[counter].setPosition(xPos, yPos);
		}
	}
	for (int i = 0; i < nWalls;)
	{
		randPosX = rand() % 17;
		randPosY = rand() % 11;
		// exclude spawnpoint
		if ((randPosX != 1 && randPosY != 1) && (randPosX != 1 && randPosY != 2) && (randPosX != 2 && randPosY != 1))
		{
			if (mapMatrix[randPosY][randPosX] != 3 && mapMatrix[randPosY][randPosX] != 2)
			{
				mapMatrix[randPosY][randPosX] = 2;

				i++;
			}
		}
	}
	for (int y = 0, counter = 0; y < 11; y++, yPos += 60, xPos = 0)
	{
		for (int x = 0; x < 17; x++, counter++, xPos += 60)
		{
			randPosDoorX = rand() % 17;
			randPosDoorY = rand() % 11;

			randPosKeyY = rand() % 11;
			randPosKeyX = rand() % 17;

			if (mapMatrix[randPosDoorY][randPosDoorX] == 2 || isDoorPlaced == false)
			{
				if (!doorTexture.loadFromFile("./content/door.jpg"))
				{
					cout << "Texture not loaded" << endl;
				}
				door.setTexture(doorTexture);
				door.setPosition(xPos, yPos);
				isDoorPlaced = true;
			}
			if (mapMatrix[randPosKeyY][randPosKeyX] == 2 || isKeyPlaced == false)
			{
				if (!keyTexture.loadFromFile("./content/door.jpg"))
				{
					cout << "Texture not loaded" << endl;
				}
				key.setTexture(keyTexture);
				key.setPosition(xPos, yPos);
				isKeyPlaced = true;
			}
			if (mapMatrix[y][x] == 2)
			{
				if (!wall.loadFromFile("./content/wall.png"))
				{
					cout << "Texture not loaded" << endl;
				}
				grid[counter].setTexture(wall);
			}
		}
	}
}

void Game::initPlaneTable()
{
	// draw plane table
	planeTable.setFillColor(Color(246, 129, 0));
	planeTable.setSize(Vector2f(1020, 100));
	planeTable.setOutlineColor(Color(128, 23, 17));
	planeTable.setOutlineThickness(2.f);
	planeTable.setPosition(Vector2f(0, 0));

	//load font
	if (!font.loadFromFile("./content/ArcadeClassic.ttf"))
	{
		cout << "Font not loaded" << endl;
	}

	//set score string
	scoreString.setFont(font);
	scoreString.setPosition(Vector2f(10.f, 50.f));
	scoreString.setFillColor(Color::White);
	scoreString.setCharacterSize(30);

	//set timer string
	timerString.setFont(font);
	timerString.setPosition(Vector2f(10.f, 10.f));
	timerString.setFillColor(Color::White);
	timerString.setCharacterSize(30);
	gameClock.restart();

	//set life string
	lifeString.setFont(font);
	lifeString.setPosition(Vector2f(800.f, 10.f));
	lifeString.setFillColor(Color::White);
	lifeString.setCharacterSize(30);

	//set level string
	levelString.setFont(font);
	levelString.setPosition(Vector2f(800.f, 50.f));
	levelString.setFillColor(Color::White);
	levelString.setCharacterSize(30);
}

void Game::initPlayer()
{
	// load texture
	if (!playerTexture.loadFromFile("./content/main-Sheet.png"))
	{
		cout << "Texture player not loaded" << endl;
	}
	player.setTexture(playerTexture);
	player.setPosition(61.f, 144.f);
}

void Game::initEnemies()
{
	for (int i = 0; i < 5; i++)
	{
		if (!enemyTexture.loadFromFile("./content/enemy.png"))
		{
			cout << "Texture not loaded" << endl;
		}
		enemy[i + 4].setTexture(enemyTexture);

		// set a random position
		int randPosX = rand() % 17, randPosY = rand() % 11;
		if (mapMatrix[randPosY][randPosX] != 3 && mapMatrix[randPosY][randPosX] != 2)
		{
			enemy[i + 4].setPosition(randPosX * 60, (randPosY * 60) + 84);
		}
		else
		{
			i--;
		}
	}
}

void Game::checkDestroyedItems()
{
	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (bomb.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
			{
				for (int i = 1; i < 3; i++)
				{
					if (mapMatrix[y + i][x] == 2 || mapMatrix[y + i][x] > 3)
					{
						score += 100;
						enemy[mapMatrix[y + i][x]].setPosition(-60.f, -60.f);
						enemiesDestroyed++;
						mapMatrix[y + i][x] = 0;
					}
					if (mapMatrix[y][x + i] == 2 || mapMatrix[y][x + i] > 3)
					{
						score += 100;
						enemy[mapMatrix[y][x + i]].setPosition(-60.f, -60.f);
						enemiesDestroyed++;
						mapMatrix[y][x + i] = 0;
					}
					if (mapMatrix[y - i][x] == 2 || mapMatrix[y - i][x] > 3)
					{
						score += 100;
						enemy[mapMatrix[y - i][x]].setPosition(-60.f, -60.f);
						enemiesDestroyed++;
						mapMatrix[y - i][x] = 0;
					}
					if (mapMatrix[y][x - i] == 2 || mapMatrix[y][x - i] > 3)
					{
						score += 100;
						enemy[mapMatrix[y][x - i]].setPosition(-60.f, -60.f);
						enemiesDestroyed++;
						mapMatrix[y][x - i] = 0;
					}

					if (mapMatrix[y + i][x] == 1)
					{
						life--;
					}
					if (mapMatrix[y][x + i] == 1)
					{
						life--;
					}
					if (mapMatrix[y - i][x] == 1)
					{
						life--;
					}
					if (mapMatrix[y][x - i] == 1)
					{
						life--;
					}
					initGrid();
				}
				return;
			}
		}
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

				if (mapMatrix[y][x] == 3 || mapMatrix[y][x] == 2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Game::updateGrid(Sprite entity, int type)
{

	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (entity.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
			{

				if (mapMatrix[y][x] == 0)
				{
					mapMatrix[y][x] = type;
				}

				if (mapMatrix[y - 1][x] == type)
				{
					mapMatrix[y - 1][x] = 0;
				}
				if (mapMatrix[y][x - 1] == type)
				{
					mapMatrix[y][x - 1] = 0;
				}
				if (mapMatrix[y + 1][x] == type)
				{
					mapMatrix[y + 1][x] = 0;
				}
				if (mapMatrix[y][x + 1] == type)
				{
					mapMatrix[y][x + 1] = 0;
				}
			}
		}
	}
}

bool Game::checkBombCollision(Sprite entity)
{
	if (entity.getGlobalBounds().intersects(bomb.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

bool Game::checkPlayerBombCollision()
{
	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (bomb.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
			{

				if (player.getGlobalBounds().intersects(bomb.getGlobalBounds()))
				{
					if (mapMatrix[y - 1][x] == 1)
					{
						return true;
					}
					if (mapMatrix[y][x - 1] == 1)
					{
						return true;
					}
					if (mapMatrix[y + 1][x] == 1)
					{
						return true;
					}
					if (mapMatrix[y][x + 1] == 1)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
