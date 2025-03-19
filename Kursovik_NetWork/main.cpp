#include <iostream>
#include "Game.h"


int main()
{
	system("chcp 1251 > 0");
	Game& game = Game::get();
	while (game.getRun())
	{
		game.run();
	}
	return 0;
}