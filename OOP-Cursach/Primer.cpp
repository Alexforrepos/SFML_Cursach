#include "Primer.h"

void Primer::Update()
{
	static sf::Clock cl;
	if (cl.getElapsedTime().asMilliseconds() > 4000)
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
}

void Primer::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_KILL:
		std::cout << "бля убивают чувака по указателю:" << MSG_TYPE_KILL(*msg).victim << std::endl;
		break;
	default:
		break;
	}
}

void Primer::Draw(sf::RenderWindow& win)
{
	sf::RectangleShape r({ 300,300 });
	r.setFillColor(sf::Color::White);
	r.setPosition(300, 300);
	win.draw(r);
}