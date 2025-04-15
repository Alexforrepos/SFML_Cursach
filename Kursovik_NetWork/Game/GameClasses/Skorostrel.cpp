#include "Skorostrel.h"
#include <SFML/Graphics.hpp>



void Skorostrel::update() {
    
}
void Skorostrel::draw(sf::RenderWindow& win) {
    sf::RectangleShape rect(sf::Vector2f(100.f, 100.f)); 
    rect.setFillColor(sf::Color(0, 255, 0, 150));           
    rect.setPosition(getPos());
    win.draw(rect);
}


void Skorostrel::sendMsg(MSG* ) {
    
}