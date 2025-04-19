#include "GameProcess.h"
#include "./../Game.h"
#include "./../GameClasses/Card.h"

void GameProcess::start(int levelNumber)
{
    O_Manager::get().clear();
    Card::resetCounter();

    auto& config = Config::getInstance();
    auto& levelConfig = config["Level"]["Levels"][levelNumber - 1];

    for (auto& plant : levelConfig["Avaliable_Plant"]) {
        std::string plantName = plant.get<std::string>();
        O_Manager::get().addObject(std::make_shared<Object<void>>(plantName));
    }

    O_Manager::get().addObject(std::make_shared<Object<void>>(levelConfig["Line_Q"]));
    m_isActive = true;
}

void GameProcess::run()
{
    static Timer escapeDelay(200);
    // Game logic here
}

void GameProcess::close()
{
    m_isActive = false;
    O_Manager::get().clear();
}

void GameProcess::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        close();
        Game::get().setState(Game::State::Menu);
    }
}