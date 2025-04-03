#include "./Game.h"

using namespace std;
using namespace sf;


void Game::run()
{
    Event ev;
    win.pollEvent(ev);
    win.clear();

    

    if (getState() == State::Menu && !menu->getIsRun())
        menu->start();
    if (getState() == State::GameProcess && !gameProcess.isRun())
        gameProcess.start();

    switch (this->currentState)
    {
    case Game::State::None:
        break;
    case Game::State::Menu:
        menu->run();
        break;
    case Game::State::NetWait:
        
        break;
    case Game::State::GameProcess:
        gameProcess.run();
        break;
    default:
        break;
    }
    omger.update();
    omger.draw(win);
    
    
    win.display();
}

std::vector<char> Game::serialize()
{
    return std::vector<char>();
}

std::pair<Types, std::pair<void*, int>> Game::deserialize(std::vector<char> data, size_t& readpoint)
{
    return std::pair<Types, std::pair<void*, int>>();
}
