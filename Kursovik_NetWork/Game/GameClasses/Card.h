#pragma once
#include "./../../Engine/Object.h"
#include "./../../Engine/MSG_Manager.h"
#include "./../GameClasses/Plant.h"
#include <SFML/Graphics.hpp>
#include "./../Utils/Timer.h"
#include "./../../Engine/R_Manager.h"
#include "./../../Engine/O_Manager.h"
#include "./../Game.h"
class Card : public Object {
    sf::Sprite sprite;
    Timer clickTimer;
    std::string plantType;
    bool isActive;
    static sf::Vector2f basePosition; // Базовая позиция для первой карты
    static int cardCounter; // Счетчик карт для смещения

public:
    Card(const std::string& plantType);

    void update() override;
    void sendMsg(MSG* msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    int type() override { return static_cast<int>(Types::None); }
    std::vector<char> serialize() override { return {}; }
    std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char>, size_t&) override { return {}; }
};