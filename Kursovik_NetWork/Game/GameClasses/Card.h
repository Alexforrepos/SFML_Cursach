#pragma once

#include "./../GameClasses/Hologram.h"
class Card : public Object
{
    sf::Sprite sprite;
    Timer clickTimer;
    static sf::Vector2f basePosition; 
    static int cardCounter; 
    std::string plantType;

public:
    Card(const std::string& plantType);

    void update() override;
    void sendMsg(MSG* msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    static void resetCounter() { cardCounter = 0; }
    std::vector<char> serialize() override { return {}; }
    std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char>, size_t&) override { return {}; }
};