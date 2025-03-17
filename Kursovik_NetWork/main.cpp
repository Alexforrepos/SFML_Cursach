#include <iostream>
#include "Game.h"


int main()
{
	Game& game = Game::get();
	while (game.getRun())
	{
		game.run();
	}
	return 0;
}