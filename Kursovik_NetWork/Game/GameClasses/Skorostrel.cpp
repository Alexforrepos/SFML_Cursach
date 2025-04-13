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
    sf::Vector2i mousePos = sf::Mouse::getPosition(Game::get().getWindow());
    sf::Vector2f worldPos = Game::get().getWindow().mapPixelToCoords(mousePos);
    setPos(worldPos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer())
    {
        MSG_Manager::get().addMSG(std::make_shared<MSG_TYPE_KILL>(this, nullptr));
        clickTimer.restart();
    }
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
