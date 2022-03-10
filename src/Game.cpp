#include <Game.h>

Game::~Game()
{
	delete this->window;
}

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initEnemies();
	this->initPlayer();
}

bool Game::running()
{
	return this->window->isOpen();
}
// accessors

// functions
void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	// clear window
	this->window->clear();

	// draw game objects

	// draw enemies
	this->window->draw(this->enemy);
	// draw player
	this->window->draw(this->player);

	this->window->display();

	for (int i = 0; i < 16; i++)
	{
		this->window->draw(this->wall[i]);
	}
}

void Game::initializeVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1024;

	this->window = new RenderWindow(this->videoMode, "Bomberman", Style::Close);

	// set a framerate limit
	this->window->setFramerateLimit(144);
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
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
			case Event::Closed:
				this->window->close();
				break;

			default:
				break;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::W))
			player.move(0, -5);
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
			player.move(0, 5);
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
			player.move(5, 0);
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
			player.move(-5, 0);
	}
}

void Game::initEnemies()
{
	xPosition = rand() % 1024;
	yPosition = rand() % 720;
	this->enemy.setPosition(xPosition, yPosition);

	//this->enemy.setPosition(0,0);
	this->enemy.setSize(Vector2f(100.f, 100.f));
	this->enemy.setFillColor(Color::Cyan);
	this->enemy.setOutlineColor(Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

void Game::initPlayer()
{
	this->player.setPosition(200.f, 200.f);
	this->player.setSize(Vector2f(80.f, 80.f));
	this->player.setFillColor(Color::Red);
	this->player.setOutlineColor(Color::White);
	this->player.setOutlineThickness(1.f);
}

void Game::initWalls()
{
	for (int i = 0, pos = 80; i < 16; i++, pos += 80)
	{
		this->wall[i].setPosition(pos, pos);
		this->wall[i].setSize(Vector2f(80.f, 80.f));
		this->wall[i].setFillColor(Color::Magenta);
	}
}