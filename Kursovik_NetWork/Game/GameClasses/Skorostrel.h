
#pragma once
#include "./../GameClasses/Plant.h"
#include <SFML/Graphics.hpp>


class Skorostrel : public Plant {
private:
    sf::Vector2f pos; 
public:
    
    Skorostrel(uint8_t line, uint8_t col, uint16_t HP, const sf::Vector2f& startPos)
        : Plant(line, col, HP), pos(startPos)
    {
    }

   
    void update() override;
    void draw(sf::RenderWindow& win) override;
    void sendMsg(MSG* msg) override;


    sf::Vector2f getPos() const { return pos; }
    void setPos(const sf::Vector2f& newPos) { pos = newPos; }
};
