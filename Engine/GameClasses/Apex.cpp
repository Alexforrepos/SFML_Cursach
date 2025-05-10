#include "Apex.h"
Apex::Apex(const std::string& plantType, uint8_t line, uint8_t col)
    : Plant(line, col, Config::getInstance()["PlantParams"]["Plants"]["Apex"]["HP"]),
    plantType(plantType)
{
    sprite.setTexture(R_Manager::get().access<sf::Texture>("Apex.png"));
    sprite.setScale(0.2f, 0.2f);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    std::cout << ".675757";
   
}

void Apex::update()
{
  
}

void Apex::sendMsg(Engine::MSG* msg)
{

}

void Apex::draw(sf::RenderWindow& win) {
    win.draw(sprite);
}

sf::Vector2f Apex::getPos() {
    return sprite.getPosition();
}

void Apex::changePos(const sf::Vector2f& other) {
    setPos(getPos() + other);
}

void Apex::setPos(sf::Vector2f other) {
    sprite.setPosition(other);
}

//template <class Archive>
//void serialize(Archive& ar) {
//    // Сначала базовая Plant (line, col, HP)
//    ar(cereal::base_class<Plant>(this));
//    // Сохраняем свой plantType и состояние таймера
//    ar(plantType, shootTimer);
//
//    // Сериализуем визуальные параметры спрайта
//    sf::Vector2f position = sprite.getPosition();
//    sf::Vector2f scale = sprite.getScale();
//    float          rotation = sprite.getRotation();
//    sf::IntRect    textureRect = sprite.getTextureRect();
//    sf::Color      color = sprite.getColor();
//    // Тот же идентификатор, что вы используете для загрузки
//    std::string    textureId = "Apex.png";
//
//    ar(position, scale, rotation, textureRect, color, textureId);
//
//    if constexpr (Archive::is_loading::value) {
//        // Восстанавливаем спрайт
//        sprite.setPosition(position);
//        sprite.setScale(scale);
//        sprite.setRotation(rotation);
//        sprite.setTextureRect(textureRect);
//        sprite.setColor(color);
//        sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
//    }
//}
CEREAL_REGISTER_TYPE(Apex);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, Apex);
