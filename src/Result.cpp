#include <Game.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Game::resultPage(int result, int level)
{
	// initialize window
	RenderWindow resultView(VideoMode(1020, 730), "Bomberman sus version", Style::Close);

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
				default:
					break;
			}

			if (result == 0)
			{
				// set result string
				resultString.setFont(font);
				resultString.setFillColor(Color::White);
				resultString.setCharacterSize(30);
				resultString.setString("You passed the level  " + to_string(level) + "!!");
				sf::FloatRect textRect = resultString.getLocalBounds();
				resultString.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				resultString.setPosition(sf::Vector2f(1020 / 2.0f, 730 / 2.0f));

				resultView.draw(resultString);

				nextLevelButton.setFont(font);
				nextLevelButton.setPosition(Vector2f(800.f, 200.f));
				nextLevelButton.setFillColor(Color::White);
				nextLevelButton.setString("Go to level" + to_string(level));
				nextLevelButton.setCharacterSize(30);
				resultView.draw(nextLevelButton);

				exitButton.setFont(font);
				exitButton.setPosition(Vector2f(800.f, 200.f));
				exitButton.setFillColor(Color::White);
				exitButton.setCharacterSize(30);
				exitButton.setString("Exit" + to_string(level));
				resultView.draw(exitButton);
			}
			else if (result == 1)
			{
				// set result string
				resultString.setFont(font);
				resultString.setPosition(Vector2f(800.f, 50.f));
				resultString.setFillColor(Color::White);
				resultString.setCharacterSize(30);
				resultString.setString("You failed the level  " + to_string(level) + "!!");
				resultView.draw(resultString);
			}

			resultView.display();
		}
	}
}