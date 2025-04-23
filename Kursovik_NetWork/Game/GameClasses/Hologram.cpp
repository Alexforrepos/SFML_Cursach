#include "Hologram.h"


Hologram::Hologram(const sf::Vector2f& startPos, const std::string& type)
    : Object(static_cast<int>(Types::None)), plantType(type), Clicktime(200),position(startPos)
{
    //sprite.setTexture(R_Manager::get().access<sf::Texture>("shkibidiSanya.png"));
    //sprite.setPosition(50,50);
    //sprite.setColor(sf::Color(255, 255, 255, 150));
    Clicktime.restart();
    std::cout << "fff" << std::endl;
}




void Hologram::update()
{

}

void Hologram::sendMsg(Engine::MSG* msg)
{

}

void Hologram::draw(sf::RenderWindow& win)
{

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