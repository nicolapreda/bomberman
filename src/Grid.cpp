
#include <Game.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// initialize main grid
void MainGame::initGrid()
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

// initialize plane table
void MainGame::initPlaneTable()
{
	// draw plane table
	planeTable.setFillColor(Color(246, 129, 0));
	planeTable.setSize(Vector2f(1020, 100));
	planeTable.setOutlineColor(Color(128, 23, 17));
	planeTable.setOutlineThickness(2.f);
	planeTable.setPosition(Vector2f(0, 0));

	//load font
	if (!font.loadFromFile("./content/fonts/ArcadeClassic.ttf"))
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

void MainGame::updateGrid(Sprite entity, int type)
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
