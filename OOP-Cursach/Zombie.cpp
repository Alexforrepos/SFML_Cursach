#include "Zombie.h"



void Zombie::Update()
{
    if (is_attack)
    {
        return;
    }

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

void Zombie::StartAttack(Plant& plant)
{
    target = &plant;
    is_attack = true;
}

void Zombie::StopAttack()
{
    is_attack = false;

}

void Zombie::Draw(sf::RenderWindow& win)
{
    win.draw(sprite);
}
