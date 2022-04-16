#include <Game.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool Game::checkGridCollision(Sprite entity)
{

	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			//check if collides the entire area of the grid
			if (entity.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
			{

				if (mapMatrix[y][x] == 2 || mapMatrix[y][x] == 3 || (isDoorRevealed == false && mapMatrix[y][x] == 11) || (isKeyRevealed == false && mapMatrix[y][x] == 13))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::checkBombCollision(Sprite entity)
{
	if (entity.getGlobalBounds().intersects(bomb.getGlobalBounds()))
	{
		return true;
	}
	return false;
}
