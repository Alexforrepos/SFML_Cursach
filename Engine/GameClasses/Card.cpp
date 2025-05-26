#include "Card.h"

sf::Vector2f Card::basePosition = { 50.f, 50.f };
int Card::cardCounter = 0;
std::shared_ptr<Hologram> Card::holo = nullptr; 

Card::Card(const std::string& plantType)
    :Object(int(Types::Cart)),
    clickTimer(2000),
    plantType(plantType)
{
    if ((basePosition.y + cardCounter * 120.f) > 1000) {
        cardCounter = 0;
    }
    sf::Vector2f position = basePosition + sf::Vector2f(0.f, cardCounter * 120.f);
    cardCounter++;

    sprite.setTexture(R_Manager::get().access<sf::Texture>("ps.png"));
    sprite.setPosition(position);
    sprite.setScale(0.2f, 0.2f);
    sprite.setColor(sf::Color(255, 255, 255, 200));
}

void Card::update() {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition();
    if (sprite.getGlobalBounds().contains(sf::Vector2f(mousePixelPos))) {
        sprite.setColor(sf::Color::White);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && holo == nullptr) {
            // стоимость из config
            int cost = Config::getInstance()["PlantParams"]
                ["Plants"][plantType]["cost"].get<int>();
            if (ScoreManager::get().spend(cost)) {
                holo = std::make_shared<Hologram>(basePosition, plantType);
                MSG_Manager::get().addMSG(
                    std::make_shared<Engine::MSG_TYPE_CREATE>(holo, this));
                clickTimer.restart();
            }
            else {
                // можно проиграть звук отказа или визуал
            }
        }
    }
    else {
        sprite.setColor(sf::Color(255, 255, 255, 200));
    }
}

void Card::draw(sf::RenderWindow& win)
{
    win.draw(sprite);
}

sf::Vector2f Card::getPos()
{
    return sprite.getPosition();
}

void Card::changePos(const sf::Vector2f& other)
{
    setPos(getPos() + other);
}

void Card::setPos(sf::Vector2f other)
{
    sprite.setPosition(other);
}

void Card::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{
    if (msg->getIndex() == Engine::MSG_TYPE::MSG_TYPE_KILL && ((Engine::MSG_TYPE_KILL*)(msg.get()))->victim == holo.get())
    {
        holo.reset(); // Освободить голограмму при её уничтожении
    }
}

CEREAL_REGISTER_TYPE(Card);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Card);