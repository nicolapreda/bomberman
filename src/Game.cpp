#include <Game.h>

MainGame::~MainGame()
{
	delete window;
}

MainGame::MainGame()
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
		srand(time(NULL));
		int randDirection = rand() % 3;
		//insert into enemiesDirection
		enemiesDirection[i] = randDirection;
	}

	//init respawn clock
	respawnClock.restart();
}

bool MainGame::running()
{
	return window->isOpen();
}

// functions
void MainGame::update()
{
	pollEvents();
}

void MainGame::initializeVariables()
{
	window = nullptr;
}

void MainGame::initWindow()
{
	// init height and width of the window
	videoMode.height = 730;
	videoMode.width = 1020;

	// init main variables

	life = 3;
	score = 0;
	bombCountDown = false;

	// init window
	window = new RenderWindow(videoMode, "Bomberman", Style::Close);

	// set a framerate limit
	window->setFramerateLimit(144);
}

void MainGame::pollEvents()
{
	while (window->pollEvent(event))
	{

		// manage events
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
				enemy[i].move(0, -updateEnemySpeed(0));
				//check collisions
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{
					srand(time(0));

					enemy[i].move(0, updateEnemySpeed(0));

					enemiesDirection[i] = rand() % 500;
					if (enemiesDirection[i] % 3 == 0)
					{
						enemiesDirection[i] = 3;
					}
					else if (enemiesDirection[i] % 2 == 0)
					{
						enemiesDirection[i] = 2;
					}
					else if (enemiesDirection[i] % 5 == 0)
					{
						enemiesDirection[i] = 1;
					}
					else
					{
						enemiesDirection[i] = 0;
					}
				}
				// update grid
				updateGrid(enemy[i], i);

				break;
			case 1:
				srand(time(NULL));

				enemy[i].move(0, updateEnemySpeed(0));
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{

					enemy[i].move(0, -updateEnemySpeed(0));
					enemiesDirection[i] = rand() % 500;
					if (enemiesDirection[i] % 3 == 0)
					{
						enemiesDirection[i] = 3;
					}
					else if (enemiesDirection[i] % 2 == 0)
					{
						enemiesDirection[i] = 2;
					}
					else if (enemiesDirection[i] % 5 == 0)
					{
						enemiesDirection[i] = 1;
					}
					else
					{
						enemiesDirection[i] = 0;
					}
				}

				// update grid
				updateGrid(enemy[i], i);
				break;
			case 2:
				srand(time(0));

				enemy[i].move(-updateEnemySpeed(0), 0);
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{

					enemy[i].move(updateEnemySpeed(0), 0);
					enemiesDirection[i] = rand() % 500;
					if (enemiesDirection[i] % 3 == 0)
					{
						enemiesDirection[i] = 3;
					}
					else if (enemiesDirection[i] % 2 == 0)
					{
						enemiesDirection[i] = 2;
					}
					else if (enemiesDirection[i] % 5 == 0)
					{
						enemiesDirection[i] = 1;
					}
					else
					{
						enemiesDirection[i] = 0;
					}
				}

				// update grid
				updateGrid(enemy[i], i);
				break;
			case 3:
				enemy[i].move(updateEnemySpeed(0), 0);
				if (checkGridCollision(enemy[i]) || checkBombCollision(enemy[i]))
				{
					srand(time(NULL));
					enemy[i].move(-updateEnemySpeed(0), 0);

					enemiesDirection[i] = rand() % 500;
					if (enemiesDirection[i] % 3 == 0)
					{
						enemiesDirection[i] = 3;
					}
					else if (enemiesDirection[i] % 2 == 0)
					{
						enemiesDirection[i] = 2;
					}
					else if (enemiesDirection[i] % 5 == 0)
					{
						enemiesDirection[i] = 1;
					}
					else
					{
						enemiesDirection[i] = 0;
					}
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
		if (checkGridCollision(player))
		{
			player.move(1.0f, 0.0f);
		}
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{

		player.move(0.0f, -1.0f);
		if (checkGridCollision(player))
		{
			player.move(0.0f, 1.0f);
		}
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{

		player.move(0.0f, 1.0f);
		if (checkGridCollision(player))
		{
			player.move(0.0f, -1.0f);
		}
		updateGrid(player, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{

		player.move(1.0f, 0.0f);
		if (checkGridCollision(player))
		{
			player.move(-1.0f, 0.0f);
		}
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
					updateObjects();
				}
			}
		}
	}

	// place bomb
	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && bombCountDown == false)
	{
		for (int y = 0, counter = 0; y < 11; y++)
		{
			for (int x = 0; x < 17; x++, counter++)
			{
				//check if collides the entire area of the grid
				if (player.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
				{
					bomb.setPosition(grid[counter].getPosition().x + 2, grid[counter].getPosition().y + 2);
				}
			}
		}

		if (!bombTexture.loadFromFile("./content/bomb.png"))
			cout << "Bomb texture not loaded!" << endl;
		bomb.setTexture(bombTexture);

		// start bomb countdown
		bombCountDown = true;
		bombClock.restart();
	}
}

void MainGame::render()
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
		resultPage(1);
	}

	// draw objects
	window->draw(planeTable);
	clockInt = gameClock.getElapsedTime().asSeconds();
	if (clockInt > timer)
	{
		window->close();
		resultPage(1);
	}
	timer = 200;
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
	levelString.setString("Level  " + to_string(updateLevel(0)));
	window->draw(levelString);

	window->draw(player);
	window->draw(bomb);

	window->display();

	// check level win

	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (player.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))

				if (isKeyUnlocked == true && mapMatrix[y][x] == 11)
				{
					window->close();
					resultPage(0);
				}
		}
	}
}

int MainGame::updateLevel(int addLevel)
{
	static int level = 1;
	if (addLevel == 1)
	{
		++level;
	}
	else if (addLevel == -1)
	{
		level = 1;
	}

	return level;
}

float MainGame::updateEnemySpeed(int addSpeed)
{
	static float enemySpeed = 0.6;
	if (addSpeed == -1)
	{
		enemySpeed = 0.6;
	}
	else if (addSpeed == 1)
	{
		enemySpeed += 0.3;
	}

	return enemySpeed;
}