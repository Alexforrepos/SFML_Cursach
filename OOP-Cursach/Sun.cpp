#include "Sun.h"
#include "Game_Proc.h"

void Sun::Update()
{
	if (sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())) && 
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Game_Proc::get().GetSunValue() += value;
		MSG_Manager::get().add(new MSG(MSG_TYPE_KILL(this, this)));
	}
	if (islay && dis_time())
	{
		MSG_Manager::get().add(new MSG(MSG_TYPE_KILL(this, this)));
	}
	if (!islay)
	{
		Position.y += velocity;
		if (Position.y > this->dis_level)
		{
			islay = true;
			this->dis_time.restart();
		}
	}
	
}

void Sun::SendMSG(MSG* msg)
{
}

void Sun::Draw(sf::RenderWindow& win)
{
	sprite.setPosition(Position);
	win.draw(sprite);
}
