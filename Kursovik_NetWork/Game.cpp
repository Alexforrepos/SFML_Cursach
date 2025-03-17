#include "Game.h"

void Game::run()
{
    
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
