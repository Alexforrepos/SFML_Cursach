#include "Effect.h"

void Effect::Update()
{
	if (time_to_die())
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
}

void Effect::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
		case int(MSG_TYPE::MSG_TYPE_KILL):
			if (MSG_TYPE_KILL(*msg).victim == target)
				MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
	default:
		break;
	}
}

void Effect::Draw(sf::RenderWindow& win)
{

}

