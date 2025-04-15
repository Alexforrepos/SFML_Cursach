// Hologram.cpp
#include "Hologram.h"
#include "./../../Engine/MSG_Manager.h"
#include "./../../Engine/MSG.h"
#include "Surface.h"       // Для проверки свободного места
#include "Skorostrel.h"     // Используем заглушку вместо реального растения
#include "./../Game.h"

Hologram::Hologram(const sf::Texture& texture, const sf::Vector2f& startPos, const std::string& type)
    : Object(static_cast<int>(Types::None)), plantType(type)
{
    sprite.setTexture(texture);
    sprite.setPosition(startPos);
    sprite.setColor(sf::Color(255, 255, 255, 150));
}

const std::string& Hologram::getPlantType() const {
    return plantType;
}

void Hologram::update() {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(Game::get().getWindow());
    sf::Vector2f mousePos = Game::get().getWindow().mapPixelToCoords(mousePixelPos);
    setPos(mousePos);

    bool freeField = Surface::getInstance().isFreeField(mousePos);

    if (freeField)
        sprite.setColor(sf::Color(255, 255, 255, 200));
    else
        sprite.setColor(sf::Color(255, 100, 100, 150));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && freeField) {
        // Пример вычисления строки и колонки на основе позиции
        uint8_t line = static_cast<uint8_t>(mousePos.y / 100);
        uint8_t col = static_cast<uint8_t>((mousePos.x - 300) / 100);
        uint16_t HP = 100; // базовое значение здоровья

     
        //Plant* newPlant = new Skorostrel(line, col, HP, mousePos);
        //MSG_Manager::get().addMSG(std::make_shared<MSG_TYPE_CREATE>(newPlant, this));
        //MSG_Manager::get().addMSG(std::make_shared<MSG_TYPE_KILL>(this, nullptr));
    }
}

void Hologram::sendMsg(MSG* /*msg*/) {
    // Реакция на сообщения по необходимости
}

void Hologram::draw(sf::RenderWindow& win) {
    win.draw(sprite);
}

sf::Vector2f Hologram::getPos() {
    return sprite.getPosition();
}

void Hologram::changePos(const sf::Vector2f& other) {
    setPos(sprite.getPosition() + other);
}

void Hologram::setPos(sf::Vector2f other) {
    sprite.setPosition(other);
}

std::vector<char> Hologram::serialize() {
    return std::vector<char>();
}

std::pair<Types, std::pair<void*, int>> Hologram::deserialize(std::vector<char> /*data*/, size_t& /*readpoint*/) {
    return std::pair<Types, std::pair<void*, int>>();
}
