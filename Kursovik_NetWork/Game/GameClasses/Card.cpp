
#include "Card.h"


sf::Vector2f Card::basePosition = { 50.f, 50.f }; 
int Card::cardCounter = 0;

Card::Card(const std::string& plantType)
    : Object(static_cast<int>(Types::None)),
    clickTimer(200)
{
    sf::Vector2f position = basePosition + sf::Vector2f(0.f, cardCounter * 120.f);
    cardCounter++;

    sprite.setTexture(R_Manager::get().access<sf::Texture>("ps.png"));
    sprite.setPosition(position);
    sprite.setScale(0.2f, 0.2f);
    sprite.setColor(sf::Color(255, 255, 255, 200)); 
}

void Card::update() 
{
    
}

void Card::draw(sf::RenderWindow& win) {
    win.draw(sprite);
}

sf::Vector2f Card::getPos() {
    return sprite.getPosition();
}

void Card::changePos(const sf::Vector2f& other) {
    setPos(getPos() + other);
}

void Card::setPos(sf::Vector2f other) {
    sprite.setPosition(other);
}

void Card::sendMsg(MSG* msg) {
   
}