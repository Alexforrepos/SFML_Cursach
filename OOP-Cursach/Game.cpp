#include "Game.h"

Game::Game(std::string res_filename)
{
	if (ResourceManager::getmger()->load_from_file(res_filename))
		throw "Res load err";
	rm = RUNMODE::RUNMODE_MENU;
}

void Game::operator()(sf::RenderWindow& win)
{
	main_beh_tree(win);
}
