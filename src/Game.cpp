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
	bombCountDown = false;
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

		player.move(-1.0f, 0.0f);
		if (checkGridCollision(player) || checkBombCollision(player))
		{
			player.move(1.0f, 0.0f);
		}
		lastKeyPressed = 0;
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{

		player.move(0.0f, -1.0f);
		if (checkGridCollision(player) || checkBombCollision(player))
		{
			player.move(0.0f, 1.0f);
		}
		lastKeyPressed = 1;
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{

		player.move(0.0f, 1.0f);
		if (checkGridCollision(player) || checkBombCollision(player))
		{
			player.move(0.0f, -1.0f);
		}
		lastKeyPressed = 2;
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{

		player.move(1.0f, 0.0f);
		if (checkGridCollision(player) || checkBombCollision(player))
		{
			player.move(-1.0f, 0.0f);
		}
		lastKeyPressed = 3;
		updateGrid(player, 1);
	}
	// unlock door
	if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
	{
		for (int y = 0, counter = 0; y < 11; y++)
		{
			for (int x = 0; x < 17; x++, counter++)
			{
				//check if collides the entire area of the grid
				if (player.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
				{
					isKeyUnlocked = true;
					if (!floor.loadFromFile("./content/grass.png"))
						cout << "Bomb texture not loaded!" << endl;
					grid[counter].setTexture(floor);
					mapMatrix[y][x] = 0;
				}
			}
		}
	}

	// place bomb
	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && bombCountDown == false)
	{
		switch (lastKeyPressed)
		{
			case 0:
				bomb.setPosition(player.getPosition().x - 60.f, player.getPosition().y);
				break;
			case 1:
				bomb.setPosition(player.getPosition().x, player.getPosition().y - 60.f);
				break;
			case 2:
				bomb.setPosition(player.getPosition().x, player.getPosition().y + 60.f);
				break;
			case 3:
				bomb.setPosition(player.getPosition().x + 60.f, player.getPosition().y);
				break;
			default:
				break;
		}
		if (!bombTexture.loadFromFile("./content/bomb.png"))
			cout << "Bomb texture not loaded!" << endl;
		bomb.setTexture(bombTexture);

		if (checkBombPlaceCollision() == false)
		{
			// start bomb countdown
			bombCountDown = true;
			bombClock.restart();
		}
		else
		{
			bomb.setPosition(-60.f, -60.f);
		}
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

	// check level win

	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (player.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))

				if (isKeyUnlocked == true && mapMatrix[y][x] == 11)
				{
					resultPage(0);
				}
		}
	}
}

void Game::initGrid()
{
	srand(time(NULL));
	int nWalls = 20, randPosX, randPosY, randPosDoorX, randPosDoorY, randPosKeyX, randPosKeyY;

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
			randPosDoorY = rand() % 11;
			randPosDoorX = rand() % 17;

			randPosKeyY = rand() % 11;
			randPosKeyX = rand() % 17;

			if (mapMatrix[randPosDoorY][randPosDoorX] == 2 && isDoorPlaced == false)
			{
				mapMatrix[randPosDoorY][randPosDoorX] = 11;
				isDoorPlaced = true;
			}
			if (mapMatrix[randPosKeyY][randPosKeyX] == 2 && isKeyPlaced == false)
			{
				mapMatrix[randPosKeyY][randPosKeyX] = 13;
				isKeyPlaced = true;
			}

			if (mapMatrix[y][x] == 2 || mapMatrix[y][x] == 11 || mapMatrix[y][x] == 13)
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
					if (mapMatrix[y + i][x] == 2 || (mapMatrix[y + i][x] > 3 && mapMatrix[y + i][x] < 13))
					{
						if (mapMatrix[y + i - 1][x] == 3)
							return;
						else
						{
							score += 100;
							enemy[mapMatrix[y + i][x]].setPosition(-60.f, -60.f);
							if (mapMatrix[y + i][x] == 11)
							{
								isDoorRevealed = true;
							}
							else if (mapMatrix[y + i][x] == 1)
							{
								life--;
							}
							else if (mapMatrix[y + i][x] == 13)
							{
								isKeyRevealed = true;
							}

							else
							{
								mapMatrix[y + i][x] = 0;
							}
						}
					}
					if (mapMatrix[y][x + i] == 2 || (mapMatrix[y][x + i] > 3 && mapMatrix[y][x + i] < 13))
					{
						if (mapMatrix[y][x + i - 1] == 3)
							return;
						else
						{
							score += 100;
							enemy[mapMatrix[y][x + i]].setPosition(-60.f, -60.f);
							if (mapMatrix[y][x + i] == 11)
							{
								isDoorRevealed = true;
							}
							else if (mapMatrix[y][x + i] == 13)
							{
								isKeyRevealed = true;
							}
							else if (mapMatrix[y][x + i] == 1)
							{
								life--;
							}
							else
							{
								mapMatrix[y][x + i] = 0;
							}
						}
					}
					if (mapMatrix[y - i][x] == 2 || (mapMatrix[y - i][x] > 3 && mapMatrix[y - i][x] < 14))
					{
						if (mapMatrix[y - i + 1][x] == 3)
							return;
						else
						{
							score += 100;
							enemy[mapMatrix[y - i][x]].setPosition(-60.f, -60.f);
							if (mapMatrix[y - i][x] == 11)
							{
								isDoorRevealed = true;
							}
							else if (mapMatrix[y - i][x] == 13)
							{
								isKeyRevealed = true;
							}
							else if (mapMatrix[y - i][x] == 1)
							{
								life--;
							}
							else
							{
								mapMatrix[y - i][x] = 0;
							}
						}
					}
					if (mapMatrix[y][x - i] == 2 || (mapMatrix[y][x - i] > 3 && mapMatrix[y][x - i] < 14))
					{
						if (mapMatrix[y][x - i + 1] == 3)
							return;
						else
						{

							score += 100;
							enemy[mapMatrix[y][x - i]].setPosition(-60.f, -60.f);
							if (mapMatrix[y][x - i] == 11)
							{
								isDoorRevealed = true;
							}
							else if (mapMatrix[y][x - i] == 13)
							{
								isKeyRevealed = true;
							}
							else if (mapMatrix[y][x - i] == 1)
							{
								life--;
							}
							else
							{
								mapMatrix[y][x - i] = 0;
							}
						}
					}
					updateObjects();
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

				if (mapMatrix[y][x] == 3 || mapMatrix[y][x] == 2 || (isDoorRevealed == false && mapMatrix[y][x] == 11) || (isKeyRevealed == false && mapMatrix[y][x] == 13))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Game::updateObjects()
{
	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{

			// update grass
			if (mapMatrix[y][x] == 0)
			{
				if (!floor.loadFromFile("./content/grass.png"))
				{
					cout << "Texture not loaded" << endl;
				}
				grid[counter].setTexture(floor);
			}
			else if (mapMatrix[y][x] == 11 && isDoorRevealed == true)
			{
				if (!doorTexture.loadFromFile("./content/door.jpg"))
				{
					cout << "Texture not loaded" << endl;
				}
				grid[counter].setTexture(doorTexture);
			}
			else if (mapMatrix[y][x] == 13 && isKeyRevealed == true)
			{
				if (!keyTexture.loadFromFile("./content/key.jpg"))
				{
					cout << "Texture not loaded" << endl;
				}
				grid[counter].setTexture(keyTexture);
			}
		}
	}
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

bool Game::checkBombPlaceCollision()
{
	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (bomb.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
			{

				if (mapMatrix[y][x] >= 2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Game::resultPage(int result)
{
	window->clear(Color::Black);
	switch (result)
	{
		case 0:
			// set result string
			resultString.setFont(font);
			resultString.setPosition(Vector2f(800.f, 50.f));
			resultString.setFillColor(Color::White);
			resultString.setCharacterSize(30);
			scoreString.setString("You passed the level  " + to_string(level) + "!!");
			window->draw(scoreString);

			// set next level button
			resultString.setFont(font);

			nextLevelButton.setPosition(Vector2f(800.f, 200.f));
			nextLevelButton.setFillColor(Color::White);
			nextLevelButton.setString("Go to level" + to_string(level));
			window->draw(nextLevelButton);

			// set exit button
			resultString.setFont(font);

			nextLevelButton.setPosition(Vector2f(800.f, 200.f));
			nextLevelButton.setFillColor(Color::White);
			nextLevelButton.setString("Exit" + to_string(level));
			window->draw(nextLevelButton);

			break;
		case 1:
			// set result string
			resultString.setFont(font);
			resultString.setPosition(Vector2f(800.f, 50.f));
			resultString.setFillColor(Color::White);
			resultString.setCharacterSize(30);
			scoreString.setString("You failed the level  " + to_string(level) + "!!");
			window->draw(scoreString);
			break;
		default:
			break;
	}
}