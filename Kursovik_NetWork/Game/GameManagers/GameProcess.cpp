#include "GameProcess.h"
#include "./../Game.h"
#include "./../GameClasses/Card.h"

void GameProcess::start(int levelnumber)
{
	O_Manager::get().clear();
	O_Manager::get().clear();

	// Создаем карты растений
	O_Manager::get().addObject(std::make_shared<Card>("Peashooter"));
	O_Manager::get().addObject(std::make_shared<Card>("Sunflower"));
	O_Manager::get().addObject(std::make_shared<Card>("Wallnut"));
	O_Manager::get().addObject(std::shared_ptr<Object>(new Surface(Config::getInstance()["Level"]["Levels"][levelnumber - 1]["Line_Q"])));
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
