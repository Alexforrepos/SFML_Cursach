#include "Skorostrel.h"
#include "./../../Engine/R_Manager.h"
#include "./../../Engine/MSG_Manager.h"
#include "./../Game.h"

Skorostrel::Skorostrel(const std::string& plantType, uint8_t line, uint8_t col)
	: Plant(line, col, 50),clickTimer(100)
{
	sprite.setTexture(R_Manager::get().access<sf::Texture>("shkibidiSanya.png"));
	sprite.setColor(sf::Color(255, 255, 255, 150));
	clickTimer.restart();
}

// Реализация всех методов
void Skorostrel::update()
{

}

void Skorostrel::sendMsg(Engine::MSG* msg)
{

}

void Skorostrel::draw(sf::RenderWindow& win)
{

}

sf::Vector2f Skorostrel::getPos()
{
	return sprite.getPosition();
}

void Skorostrel::changePos(const sf::Vector2f& other)
{

}

void Skorostrel::setPos(sf::Vector2f other)
{
	this->sprite.setPosition(other);
}

CEREAL_REGISTER_TYPE(Skorostrel);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, Skorostrel);