#pragma once
#include "./../../Engine/Object.h"
#include "./../../Engine/MSG_Manager.h"
#include "./../GameClasses/Plant.h"
#include <SFML/Graphics.hpp>
#include "./../Utils/Timer.h"
#include "./../../Engine/R_Manager.h"
#include "./../../Engine/O_Manager.h"
#include "./../Game.h"
class Hologram : public Object
{
private:
   //sf::Sprite sprite;
    std::string plantType; // Тип растения, который должен быть создан
    Timer Clicktime;
    sf::Vector2f position;
public:	
    Hologram(const sf::Vector2f& startPos, const std::string& type);
    void update() override;
    void sendMsg(MSG* msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    std::vector<char> serialize() override { return {}; }
    std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char>, size_t&) override { return {}; }
};

