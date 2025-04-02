#include <iostream>
#include "./Game/Game.h"


int main()
{
	system("chcp 1251 > 0");
	Game& game = Game::get();
	while (game.isRunning())
	{
		game.run();
	}
	return 0;
}