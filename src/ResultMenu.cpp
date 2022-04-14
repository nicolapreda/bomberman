#include <Game.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Game::resultPage(int result, int level)
{
	// initialize button result selected
	buttonResultSelected = 1;

	sf::Text exitButton, nextLevelButton, resultString;
	sf::Font font;
	font.loadFromFile("./src/Assets/Fonts/ArcadeClassic.ttf");

	// initialize window
	RenderWindow resultView(VideoMode(1020, 730), "Bomberman", Style::Close);

	// set result string
	resultString.setFont(font);
	resultString.setCharacterSize(60);

	if (result == 0)
	{
		resultString.setString("You  passed  the  level  " + to_string(level) + " !!");
		resultString.setFillColor(Color::Green);
		level++;
	}
	else if (result == 1)
	{
		resultString.setString("You  failed  the  level  " + to_string(level) + " !!");
		resultString.setFillColor(Color::Red);

		level = 0;
	}
	sf::FloatRect textRect = resultString.getLocalBounds();
	resultString.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	resultString.setPosition(sf::Vector2f(1020 / 2.0f, 730 / 2.0f));

	exitButton.setFont(font);
	exitButton.setPosition(Vector2f(150.f, 500.f));
	exitButton.setFillColor(Color::White);
	exitButton.setCharacterSize(30);
	exitButton.setString("Exit");

	nextLevelButton.setFont(font);
	nextLevelButton.setPosition(Vector2f(650.f, 500.f));
	nextLevelButton.setFillColor(Color::Blue);
	nextLevelButton.setString("Go  to  level  " + to_string(level));
	nextLevelButton.setCharacterSize(30);

	while (resultView.isOpen())
	{
		Event event;

		while (resultView.waitEvent(event))
		{

			switch (event.type)
			{
				case Event::Closed:
					resultView.close();
					break;
				case Event::KeyReleased:
					if (event.key.code == Keyboard::Left)
					{
						if (buttonResultSelected == 1)
						{
							exitButton.setFillColor(Color::Blue);
							resultView.clear();
							buttonResultSelected = 0;
							nextLevelButton.setFillColor(Color::White);
						}
						break;
					}
					if (event.key.code == Keyboard::Right)
					{
						if (buttonResultSelected == 0)
						{
							nextLevelButton.setFillColor(Color::Blue);
							resultView.clear();
							buttonResultSelected = 1;

							exitButton.setFillColor(Color::White);
						}
						break;
					}
					if (event.key.code == Keyboard::Return)
					{
						if (buttonResultSelected == 1)
						{
							// init game engine
							Game game;
							resultView.close();
							while (game.running())
							{
								game.update();
								game.render();
							}
						}
						else
						{
							resultView.close();
						}
					}
					break;
				default:
					break;
			}
			resultView.clear();

			resultView.draw(resultString);
			resultView.draw(exitButton);
			resultView.draw(nextLevelButton);

			resultView.display();
		}
	}
}