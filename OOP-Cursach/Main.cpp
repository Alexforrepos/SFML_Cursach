#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"



int WinMain(int argc, char* argv[])
{
	Game& game = Game::Get();
	while (game.isRunning())
		game.Run();
}