#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace std;
using namespace sf;

int main()
{
	Game& game = Game::Get();
	while (game.isRunning())
	{
		game.Run();
	}
}