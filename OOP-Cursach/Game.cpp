#include "Game.h"

Game* Game::game = nullptr;

void Game::Run()
{
	
}

bool Game::isRunning()
{
	return isRun;
}

Game::Game(std::string res_filename)
	:win(sf::VideoMode::VideoMode(sf::VideoMode::getDesktopMode()), "Plants vs Zombies", sf::Style::Fullscreen),
	OMg(*O_Manager::getmger()),
	MsMg(*MSG_Manager::getmger()),
	RMg(*Res_Manager::getmger())
{
	if (Res_Manager::getmger()->load_from_file(res_filename))
		throw "Res load err";
	rm = RUNMODE::RUNMODE_MENU;
	
}

void Game::operator()(sf::RenderWindow& win)
{
	Run();
}
