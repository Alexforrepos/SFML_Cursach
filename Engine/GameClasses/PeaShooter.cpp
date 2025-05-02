#include "PeaShooter.h"


PeaShooter::PeaShooter(const std::string& plantType, uint8_t line, uint8_t col)
    : Plant(line, col, Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["HP"]),
    plantType(plantType), shootTimer(Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["CD"])
{
    sprite.setTexture(R_Manager::get().access<sf::Texture>("Sun.png"));
    sprite.setScale(0.15f, 0.15f);
    sprite.setColor(sf::Color::White);
    shootTimer.restart();
}

void PeaShooter::update() {
    // Тут можешь реализовать логику стрельбы
}

void PeaShooter::sendMsg(Engine::MSG* msg) {}

void PeaShooter::draw(sf::RenderWindow& win) {
    win.draw(sprite);
}

sf::Vector2f PeaShooter::getPos() {
    return sprite.getPosition();
}

void PeaShooter::changePos(const sf::Vector2f& other) {
    setPos(getPos() + other);
}

void PeaShooter::setPos(sf::Vector2f other) {
    sprite.setPosition(other);
}


CEREAL_REGISTER_TYPE(PeaShooter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, PeaShooter);
