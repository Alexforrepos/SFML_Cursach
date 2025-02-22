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
    if (time_to_die.getElapsedTime().asSeconds() > 20)
        MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));

}

void pea::SendMSG(MSG* msg)
{
    switch (msg->MSG_TYPE.index())
    {
    case (int)MSG_TYPE::MSG_TYPE_KILL:
        if(MSG_TYPE_KILL(*msg).victim == this)
            if (MSG_TYPE_KILL(*msg).killer->Serialize() == int(Serialize_Enum::Zombie))
                MSG_Manager::getmger()->add(new MSG(MSG_TYPE_DEAL_DAMAGE(MSG_TYPE_KILL(*msg).killer, this, this->damage)));
        break;
    default:
        break;
    }
}

void pea::Draw(sf::RenderWindow& win)
{
	sprite.setPosition(this->Position);
	win.draw(sprite);
}
