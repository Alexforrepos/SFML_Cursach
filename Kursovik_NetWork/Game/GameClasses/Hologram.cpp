#include "Hologram.h"


Hologram::Hologram(const sf::Vector2f& startPos, const std::string& type)
    : Object(static_cast<int>(Types::None)), plantType(type), Clicktime(200),position(startPos)
{
    Clicktime.restart();
    
}




void Hologram::update()
{
    position = sf::Vector2f(sf::Mouse::getPosition());

}

void Hologram::sendMsg(Engine::MSG* msg)
{

}

void Hologram::draw(sf::RenderWindow& win)
{
    std::cout << "x=" << position.x << "\n y=" << position.y << std::endl;
}

sf::Vector2f Hologram::getPos()
{
    return position;
}

void Hologram::changePos(const sf::Vector2f& other)
{

}

void Hologram::setPos(sf::Vector2f other)
{

}


CEREAL_REGISTER_TYPE(Hologram);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Hologram);