#include "SunFlower.h"

SunFlower::SunFlower(uint8_t line, uint8_t col)
    : Plant("SunFlower",
        Config::getInstance()["PlantParams"]["Plants"]["SunFlower"]["textureId"],
        line,
        col,
        Config::getInstance()["PlantParams"]["Plants"]["SunFlower"]["HP"]
    ),
    sunTimer(Config::getInstance()["PlantParams"]["Plants"]["SunFlower"]["CD"].get<int>() * 1000) 
{
    sprite.setScale(0.2f, 0.2f);
    sprite.setColor(sf::Color(255, 255, 150, 255));
    sunTimer.restart();
}


void SunFlower::update() {
    if (sunTimer()) {
        auto& tex = R_Manager::get().access<sf::Texture>("Sun.png");
        sf::Vector2f sunPos = getPos() + sf::Vector2f(20.f, -20.f); 
        auto sun = std::make_shared<Sun>(sunPos, tex);
        MSG_Manager::get().addMSG(
            std::make_shared<Engine::MSG_TYPE_CREATE>(sun, this)
        );
        sunTimer.restart();
    }
}