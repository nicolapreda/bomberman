#include "Platform/Platform.hpp"
// custom lib
#include <Game.h>

int main()
{
	// init game engine
	Game game;

	// call main functions when the game is running
	while (game.running())
	{
		game.update();
		game.render();
	}
}