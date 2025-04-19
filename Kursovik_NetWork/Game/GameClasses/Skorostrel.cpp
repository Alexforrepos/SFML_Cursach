#include "Skorostrel.h"
#include "./../../Engine/R_Manager.h"
#include "./../../Engine/MSG_Manager.h"
#include "./../Game.h"

Skorostrel::Skorostrel(const std::string& plantType, sf::Vector2f pos)
    : Object(static_cast<int>(Types::None)), plantType(plantType), clickTimer(200)
{
    sprite.setTexture(R_Manager::get().access<sf::Texture>("shkibidiSanya.png"));
    sprite.setPosition(pos);
    sprite.setColor(sf::Color(255, 255, 255, 150));
    clickTimer.restart();
}

// Реализация всех методов
void Skorostrel::update()
{
   
}

void Skorostrel::sendMsg(MSG* msg)
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
   
}
