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

	this->window->display();
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
	}
}

void Game::initEnemies()
{
	//this->enemy.setPosition(0,0);
	this->enemy.setSize(Vector2f(100.f, 100.f));
	this->enemy.setFillColor(Color::Cyan);
	this->enemy.setOutlineColor(Color::Green);
	this->enemy.setOutlineThickness(1.f);
}