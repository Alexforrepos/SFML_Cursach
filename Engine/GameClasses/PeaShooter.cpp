#include "PeaShooter.h"


PeaShooter::PeaShooter(const std::string& plantType, uint8_t line, uint8_t col)
    : Plant(line, col, Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["HP"]),
    plantType(plantType), shootTimer(300/*Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["CD"]*/)
{
    sprite.setTexture(R_Manager::get().access<sf::Texture>("PeaShooter.png"));
    sprite.setScale(2, 2);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    std::cout << ".675757";
    shootTimer.restart();
}

void PeaShooter::update() 
{
    if (shootTimer()) {
        // 1. Достаём из конфига параметры пули
        auto& cfg = Config::getInstance();
        unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
        unsigned velocity = 5; // либо тоже из конфига, если нужно

        // 2. Создаём shared_ptr на Projectile
        //    Конструктор: Projectile(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture)
        auto& tex = R_Manager::get().access<sf::Texture>("pea.jpg");
        auto proj = std::make_shared<Projectile>(
            static_cast<uint16_t>(velocity),
            line,                     // можно передавать реальную линию, если храните её в PeaShooter
            static_cast<uint16_t>(damage),
            tex
        );
        
        // 3. Устанавливаем стартовую позицию снаряда в точку PeaShooter
        proj->setPos(this->getPos());

        // 4. Кидаем сообщение о создании нового объекта
        O_Manager::get().addObject(proj);

        shootTimer.restart();
    }
    else
         ;
}

void PeaShooter::sendMsg(Engine::MSG* msg)
{

}

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

template <class Archive>
void serialize(Archive& ar) {
    // Сначала базовая Plant (line, col, HP)
    ar(cereal::base_class<Plant>(this));
    // Сохраняем свой plantType и состояние таймера
    ar(plantType, shootTimer);

    // Сериализуем визуальные параметры спрайта
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f scale = sprite.getScale();
    float          rotation = sprite.getRotation();
    sf::IntRect    textureRect = sprite.getTextureRect();
    sf::Color      color = sprite.getColor();
    // Тот же идентификатор, что вы используете для загрузки
    std::string    textureId = "PeaShooter.png";

    ar(position, scale, rotation, textureRect, color, textureId);

    if constexpr (Archive::is_loading::value) {
        // Восстанавливаем спрайт
        sprite.setPosition(position);
        sprite.setScale(scale);
        sprite.setRotation(rotation);
        sprite.setTextureRect(textureRect);
        sprite.setColor(color);
        sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
    }
}
CEREAL_REGISTER_TYPE(PeaShooter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, PeaShooter);
