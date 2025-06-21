#include "Apex.h"
Apex::Apex(uint8_t line, uint8_t col)
    : Plant(
        "Apex",
        "Apex.png",   
        line,
        col,
        Config::getInstance()["PlantParams"]["Plants"]["Apex"]["HP"]
    )
{
    
    sprite.setScale(0.2, 0.2);
    sprite.setColor(sf::Color(255, 255, 255, 200));
}

void Apex::update()
{ }
void Apex::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{ }
//CEREAL_REGISTER_TYPE(Apex);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, Apex);
