#include "GameProcess.h"
#include "./../Game.h"


void GameProcess::start()
{
	O_Manager::get().clear();
	O_Manager::get().addObject(std::shared_ptr<Object>(new Surface()));
	this->isActive = true;
}

void GameProcess::run()
{
	static Timer escape_delay(200);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escape_delay())
	{
		close();
		escape_delay.restart();
		O_Manager::get().clear();
		Game::get().setState(Game::State::Menu);
		return;
	}
}

void GameProcess::close()
{
	isActive = false;
}
