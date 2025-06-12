#include "GameProcess.h"
#include "./../Game.h"
#include "GameClasses/Card.h"

void GameProcess::start(int levelNumber)
{
    O_Manager::get().clear();
    
    auto& config = Config::getInstance();
    auto& levelConfig = config["Level"]["Levels"][levelNumber - 1];

    O_Manager::get().addObject(std::make_shared<Surface>(config["Level"]["Levels"][levelNumber - 1]["Line_Q"]));
    Card::resetCounter();

    // Создаем карточки для доступных растений
    for (const auto& plant : (config["Level"]["Levels"][levelNumber - 1]["Avaliable_Plant"])) 
    {
        std::string plantType = plant.get<std::string>(); // Правильное преобразование
        O_Manager::get().addObject(std::make_shared<Card>(plantType));
    }
    m_isActive = true;
}

void GameProcess::run()
{
    static Timer escapeDelay(500);
    // Game logic here

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && escapeDelay())
    {
        escapeDelay.restart();
        MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_CREATE>(std::make_shared<Zombie>(rand() % 3), nullptr));
    }
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