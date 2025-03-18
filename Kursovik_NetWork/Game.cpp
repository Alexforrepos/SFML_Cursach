#include "Game.h"

void Game::run()
{
    if (getState() == State::Menu && !menu.getIsRun())
        menu.start();

    omger.update();
    omger.draw(win);
    
}

std::vector<char> Game::serialize()
{
    return std::vector<char>();
}

I_Serialize* Game::deserialize(std::vector<char> data)
{
    return nullptr;
}
