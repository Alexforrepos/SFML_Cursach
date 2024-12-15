#include "Primer.h"

void Primer::Update()
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		this->SetPos((sf::Vector2f)sf::Mouse::getPosition());
	
}

void Primer::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_KILL:
		std::cout << "��� ������� ������ �� ���������:" << MSG_TYPE_KILL(*msg).victim << std::endl;
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE(sf::Vector2f(10, 10), this)));
		break;
	case (int)MSG_TYPE::MSG_TYPE_MOVE:
		if (MSG_TYPE_MOVE(*msg).obj == this)
		{
			this->Position += MSG_TYPE_MOVE(*msg).dir;
		}
		break;
	default:
		break;
	}
}

void Primer::Draw(sf::RenderWindow& win)
{
	sf::RectangleShape r({ 300,300 });
	r.setFillColor(sf::Color::White);
	r.setPosition(this->Position);
	win.draw(r);
}

