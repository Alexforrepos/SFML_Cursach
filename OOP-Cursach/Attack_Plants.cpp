#include "Attack_Plants.h"

void Attack_Plants::Update()
{
	if (isActive && cd_time_ms <= time_to_shoot.getElapsedTime().asMilliseconds())
	{

		pea* penis = new pea(this->Position);
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_CREATE(penis, this)));
		time_to_shoot.restart();
	}
}

void Attack_Plants::SendMSG(MSG* msg)
{
    if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_DEAL_DAMAGE)
    {
        if (MSG_TYPE_DEAL_DAMAGE(*msg).target == this)
        {
            HP -= MSG_TYPE_DEAL_DAMAGE(*msg).damage;
            if (HP <= 0)
            {
                HP = 0;
                MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
            }
        }
    }
}

void Attack_Plants::Draw(sf::RenderWindow& win)
{
	sprite.setPosition(this->Position);
	win.draw(sprite);
}

