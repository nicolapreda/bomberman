#include <Game.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Game::resultPage(int result, int level)
{
	// main font
	Font font;

	sf::Text resultString, nextLevelButton;
	// initialize window
	RenderWindow resultView(VideoMode(1020, 730), "Bomberman", Style::Close);

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
					if (event.key.code == Keyboard::Up)
					{
						if (mainMenuSelected > 0)
						{
							mainMenu[mainMenuSelected].setFillColor(Color::Blue);
							MainMenu.clear();
							mainMenuSelected--;
							mainMenu[mainMenuSelected].setFillColor(Color::White);
						}
						break;
					}
					if (event.key.code == Keyboard::Down)
					{
						if (mainMenuSelected < 2)
						{
							mainMenu[mainMenuSelected].setFillColor(Color::Blue);
							MainMenu.clear();
							mainMenuSelected++;

							mainMenu[mainMenuSelected].setFillColor(Color::White);
						}
						break;
					}
					if (event.key.code == Keyboard::Return)
					{
						int x = mainMenuSelected;
						// init game engine
						Game game;

						switch (x)
						{
							case 0:
								MainMenu.close();
								while (game.running())
								{
									game.update();
									game.render();
								}

								break;
							case 1:
								MainMenu.close();
								while (game.running())
								{
									game.update();
									game.render();
								}

								break;
							case 2:
								MainMenu.close();
								break;
							default:
								break;
						}
					}

					break;
				default:
					break;
			}
			resultView.clear();

			switch (result)
			{
				case 0:
					// set result string
					resultString.setFont(font);
					resultString.setFillColor(Color::White);
					resultString.setCharacterSize(30);
					scoreString.setString("You passed the level  " + to_string(level) + "!!");
					sf::FloatRect textRect = resultString.getLocalBounds();
					resultString.setOrigin(textRect.left + textRect.width / 2.0f,
						textRect.top + textRect.height / 2.0f);
					resultString.setPosition(sf::Vector2f(1020 / 2.0f, 730 / 2.0f));
					resultView.draw(scoreString);

					// set next level button
					resultString.setFont(font);

					nextLevelButton.setPosition(Vector2f(800.f, 200.f));
					nextLevelButton.setFillColor(Color::White);
					nextLevelButton.setString("Go to level" + to_string(level));
					resultView.draw(nextLevelButton);

					// set exit button
					resultString.setFont(font);

					nextLevelButton.setPosition(Vector2f(800.f, 200.f));
					nextLevelButton.setFillColor(Color::White);
					nextLevelButton.setString("Exit" + to_string(level));
					resultView.draw(nextLevelButton);

					break;
				case 1:
					// set result string
					resultString.setFont(font);
					resultString.setPosition(Vector2f(800.f, 50.f));
					resultString.setFillColor(Color::White);
					resultString.setCharacterSize(30);
					scoreString.setString("You failed the level  " + to_string(level) + "!!");
					resultView.draw(scoreString);
					break;
				default:
					break;
			}

			resultView.display();
		}
	}
}