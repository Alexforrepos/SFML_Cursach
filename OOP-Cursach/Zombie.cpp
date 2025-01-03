#include "Zombie.h"



void Zombie::Update()
{
	
    if (timer())
    {
        timer.restart();

        sf::Vector2f Move(-5.0, 0.0);
        sprite.move(Move);
    }
}

void Zombie::SendMSG(MSG* msg)
{
  
}

void Zombie::Draw(sf::RenderWindow& win)
{
    win.draw(sprite);
}
