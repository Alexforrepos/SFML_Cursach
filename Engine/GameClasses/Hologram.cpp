#include "Hologram.h"


Hologram::Hologram(const sf::Vector2f& startPos, const std::string& type)
    : Object(static_cast<int>(Types::Hologram)), plantType(type), Clicktime(200),position(startPos)
{
    Clicktime.restart();
    sprite.setTexture(
        R_Manager::get().access<sf::Texture>(plantType == "Shovel" ? "Showel.png" : "Hand.png")
        
    );
    ObjectType = Types::BasePlantType;
    sprite.setColor(sf::Color(255, 255, 255, 150)); 
    sprite.setScale(0.15f, 0.15f); 
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); 
}


void Hologram::update()
{
    position = sf::Vector2f(sf::Mouse::getPosition());
    sprite.setPosition(position);
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    auto bf = Clicktime();

    if (isPressed && bf && !wasRightPressed)
    {
        std::cout << "MSG Send" << std::endl;
        MSG_Manager::get().addMSG(std::shared_ptr<Engine::MSG_TYPE_KILL>(new Engine::MSG_TYPE_KILL(
            this, this)));
        wasRightPressed = true; 
    }
    else if (!isPressed)
    {
        wasRightPressed = false; 
    }
}

void Hologram::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{

}

void Hologram::draw(sf::RenderWindow& win)
{
 // std::cout << "x=" << position.x << "\n y=" << position.y << std::endl;
    win.draw(sprite);
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

//
//CEREAL_REGISTER_TYPE(Hologram);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Hologram);