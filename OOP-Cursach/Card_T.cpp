#include "Card_T.h"
#include "Game_Proc.h"

void Card_T::Update()
{
	if (shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isactive
		&& timer())
	{
		if (!Config_load::getconfig().get().at("FreePlants").get<int>())
			switch (PlT)
			{
			case Peashooter:
				if (Game_Proc::get().GetSunValue() < Plant::Peashooter)
					return;
				Game_Proc::get().TakeSun(Plant::Peashooter);
				break;
			case Sunflower:
				break;
			case Repeater:
				if (Game_Proc::get().GetSunValue() < Plant::Repeater)
					return;
				Game_Proc::get().TakeSun(Plant::Repeater);
				break;
			}

		isactive = true;
		this->g = new Hologram(sf::Vector2f(sf::Mouse::getPosition()), PlT);
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_CREATE(g, this)));
		shape.setFillColor(sf::Color::Cyan);
		timer.restart();
	}

	if (isactive)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			isactive = false;
			shape.setFillColor(sf::Color::Blue);
			if (g != nullptr)
				MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(g, this)));
			g = nullptr;
		}

	}
}

void Card_T::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_KILL:
		if (MSG_TYPE_KILL(*msg).victim == g)
		{
			g = nullptr;
			isactive = false;
			shape.setFillColor(sf::Color::Blue);
		}
	default:
		break;
	}
}

void Card_T::Draw(sf::RenderWindow& win)
{
	win.draw(shape);
}
