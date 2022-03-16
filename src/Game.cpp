#include <Game.h>

Game::~Game()
{
	delete window;
}

Game::Game()
{
	initializeVariables();
	initWindow();
	initEnemies();
	initPlayer();
	initDefWalls();
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

void Game::render()
{
	// clear window
	window->clear(Color(0, 148, 0));

	// draw walls
	for (int i = 0; i < 24; i++)
	{
		window->draw(wall[i]);
		window->draw(permWall[i]);
	}

	// draw enemies
	window->draw(enemy);
	// draw player
	window->draw(player);

	window->display();
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
	// left collision
	if (player.getPosition().x < 0.f)
		player.setPosition(0.f, player.getPosition().y);
	// top collision
	if (player.getPosition().y < 0.f)
		player.setPosition(player.getPosition().x, 0.f);
	// right collision
	if (player.getPosition().x + player.getGlobalBounds().width > 1024)
		player.setPosition(1024 - player.getGlobalBounds().width, player.getPosition().y);
	// bottom collision
	if (player.getPosition().y + player.getGlobalBounds().height > 720)
		player.setPosition(player.getPosition().x, 720 - player.getGlobalBounds().height);

	if (xPosition < 0.f || xPosition > 1024 - 100)
		xVelocity *= -1;
	if (yPosition < 0.f || yPosition > 720)
		yVelocity *= -1;

	xPosition += xVelocity;
	yPosition += yVelocity;

	enemy.setPosition(xPosition, yPosition);
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed:
				window->close();
				break;

			default:
				break;
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
			player.move(0, -6);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.move(0, 6);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.move(6, 0);
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.move(-6, 0);
	}
}

void Game::initEnemies()
{
	xPosition = rand() % 1024;
	yPosition = rand() % 720;
	enemy.setPosition(xPosition, yPosition);

	enemy.setSize(Vector2f(54.f, 48.f));
	enemy.setFillColor(Color::Cyan);
	enemy.setOutlineColor(Color::Green);
	enemy.setOutlineThickness(1.f);
}

void Game::initPlayer()
{
	player.setPosition(0, 0);
	player.setSize(Vector2f(54.f, 48.f));
	player.setFillColor(Color::Red);
	player.setOutlineColor(Color::White);
	player.setOutlineThickness(1.f);
}

void Game::initDefWalls()
{
	int counter = 0;

	for (int x = 0; x < 4; x++)
	{
		permWall[x].setFillColor(Color(186, 186, 186));
		permWall[x].setOutlineColor(Color::Black);
		permWall[x].setOutlineThickness(2.f);
	}

	permWall[0].setPosition(0, 108);
	permWall[0].setSize(Vector2f(53.f, 720));

	permWall[1].setPosition(0, 108);
	permWall[1].setSize(Vector2f(1024, 53.f));

	permWall[2].setPosition(971, 108);
	permWall[2].setSize(Vector2f(53.f, 720));

	permWall[3].setPosition(0, 666);
	permWall[3].setSize(Vector2f(1024, 53.f));

	for (int i = 0, yPos = 192; i < 4; i++, yPos += 96)
	{
		for (int x = 0, xPos = 108; x < 6; x++, xPos += 108, counter++)
		{
			wall[counter].setPosition(xPos, yPos);
			wall[counter].setSize(Vector2f(53.f, 53.f));
			wall[counter].setFillColor(Color(186, 186, 186));
			wall[counter].setOutlineColor(Color::Black);
			wall[counter].setOutlineThickness(2.f);
		}
	}
}

void Game::initRandWalls()
{
	//int walls = rand() % 20;
}