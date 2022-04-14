#include <Game.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
