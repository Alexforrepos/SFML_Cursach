#include "GameProcess.h"
#include "./../Game.h"
#include "./../GameClasses/Card.h"

void GameProcess::start(int levelnumber)
{
	O_Manager::get().clear();
	O_Manager::get().clear();
	Card::resetCounter();

	auto& config = Config::getInstance();
	auto& levelConfig = config["Level"]["Levels"][levelnumber - 1];

	// Создаем карточки из конфига
	for (auto& plant : levelConfig["Avaliable_Plant"]) {
		std::string plantName = plant.get<std::string>();
		O_Manager::get().addObject(std::make_shared<Card>(plantName));
	}

	O_Manager::get().addObject(std::shared_ptr<Object>(new Surface(levelConfig["Line_Q"])));
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
