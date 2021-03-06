
#include <Game.h>

void MainGame::checkDestroyedItems()
{
	showDamagedZones = true;
	damageClock.restart();
	for (int y = 0, counter = 0; y < 11; y++)
	{
		for (int x = 0; x < 17; x++, counter++)
		{
			// check bomb explosion collision
			if (bomb.getGlobalBounds().intersects(grid[counter].getGlobalBounds()))
			{
				for (int i = 0; i < 3; i++)
				{
					if ((mapMatrix[y + i][x] == 2 || mapMatrix[y + i][x] == 1 || (mapMatrix[y + i][x] > 3 && mapMatrix[y + i][x] < 14)) && mapMatrix[y + 1][x] != 3)
					{

						if (mapMatrix[y + i][x] > 3 && mapMatrix[y + i][x] < 14)
						{
							enemy[mapMatrix[y + i][x]].setPosition(-60.f, -60.f);
							score += 200;
						}
						else
						{
							score += 100;
						}

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
					if ((mapMatrix[y][x + i] == 2 || mapMatrix[y][x + i] == 1 || (mapMatrix[y][x + i] > 3 && mapMatrix[y][x + i] < 14)) && mapMatrix[y][x + 1] != 3)
					{
						if (mapMatrix[y][x + i] > 3 && mapMatrix[y][x + i] < 14)
						{
							enemy[mapMatrix[y][x + i]].setPosition(-60.f, -60.f);
							score += 200;
						}
						else
						{
							score += 100;
						}
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
					if ((mapMatrix[y - i][x] == 2 || mapMatrix[y - i][x] == 1 || (mapMatrix[y - i][x] > 3 && mapMatrix[y - i][x] < 14)) && mapMatrix[y - 1][x] != 3)
					{
						if (mapMatrix[y - i][x] > 3 && mapMatrix[y - i][x] < 14)
						{
							enemy[mapMatrix[y - i][x]].setPosition(-60.f, -60.f);
							score += 200;
						}
						else
						{
							score += 100;
						}
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
					if ((mapMatrix[y][x - i] == 2 || mapMatrix[y][x - i] == 1 || (mapMatrix[y][x - i] > 3 && mapMatrix[y][x - i] < 14)) && mapMatrix[y][x - 1] != 3)
					{
						if (mapMatrix[y][x - i] > 3 && mapMatrix[y][x - i] < 14)
						{
							score += 200;
							enemy[mapMatrix[y][x - i]].setPosition(-60.f, -60.f);
						}
						else
						{
							score += 100;
						}

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
					updateObjects();
				}
				return;
			}
		}
	}
}
