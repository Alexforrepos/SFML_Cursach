#include "pea.h"

void pea::Update()
{
    if (timer())
    {
        timer.restart();

        sf::Vector2f Move(5.0, 0.0);
        MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE(Move, this)));
        this->Position += Move;
        sprite.move(Move);
    }
}

void pea::SendMSG(MSG* msg)
{
}

void pea::Draw(sf::RenderWindow& win)
{
	sprite.setPosition(this->Position);
	win.draw(sprite);
}
