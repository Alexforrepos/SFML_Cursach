#include "Game.h"

using namespace std;
using namespace sf;


void Game::run()
{
    Event ev;
    win.pollEvent(ev);
    win.clear();

    if (getState() == State::Menu && !menu.getIsRun())
        menu.start();
    if (getState() == State::GameProcess && !gameproc.isRun())
        gameproc.start();

    switch (state)
    {
    case Game::State::None:
        break;
    case Game::State::Menu:
        menu.run();
        break;
    case Game::State::NetWait:
        break;
    case Game::State::Prepare:
        break;
    case Game::State::GameProcess:
        gameproc.run();
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

I_Serialize* Game::deserialize(std::vector<char> data)
{
    return nullptr;
}
