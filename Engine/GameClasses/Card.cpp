#include "Card.h"

sf::Vector2f Card::basePosition = { 50.f, 100.f };
int Card::cardCounter = 0;
std::shared_ptr<Hologram> Card::holo = nullptr;

// Initialize static sun text members
sf::Font Card::sunFont;
sf::Text Card::sunText;
bool Card::sunTextInitialized = false;

Card::Card(const std::string& plantType)
    : Object(int(Types::Cart)),
    clickTimer(2000),
    plantType(plantType)
{
   
    if (!sunTextInitialized) {
        sunFont = R_Manager::get().access<sf::Font>("BantyBold.ttf"); 
        sunText.setCharacterSize(24);
        sunText.setFillColor(sf::Color::Yellow);
        
        sunText.setPosition(basePosition.x, basePosition.y - 40.f);
        sunTextInitialized = true;
    }

    if ((basePosition.y + cardCounter * 120.f) > 1000) {
        cardCounter = 0;
    }
    sf::Vector2f position = basePosition + sf::Vector2f(0.f, cardCounter * 120.f);
    cardCounter++;

    std::string textureId = Config::getInstance()["PlantParams"]["Plants"][plantType]["textureId"].get<std::string>();
    sf::Texture& texture = R_Manager::get().access<sf::Texture>(textureId);

    sprite.setTexture(texture);
    sprite.setScale(100.f / texture.getSize().x, 100.f / texture.getSize().y);
    sprite.setPosition(position);
    sprite.setColor(sf::Color(255, 255, 255, 200));
}

void Card::update() {
    
    sunText.setString("Sun: " + std::to_string(ScoreManager::get().getScore()));

    sf::Vector2i mousePixelPos = sf::Mouse::getPosition();
    if (sprite.getGlobalBounds().contains(sf::Vector2f(mousePixelPos))) {
        sprite.setColor(sf::Color::White);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && holo == nullptr) {
            int cost = Config::getInstance()["PlantParams"]["Plants"][plantType]["cost"].get<int>();
            if (ScoreManager::get().spend(cost)) {
                holo = std::make_shared<Hologram>(basePosition, plantType);
                MSG_Manager::get().addMSG(
                    std::make_shared<Engine::MSG_TYPE_CREATE>(holo, this));
                clickTimer.restart();
            }
        }
    }
    else {
        sprite.setColor(sf::Color(255, 255, 255, 200));
    }
}

void Card::draw(sf::RenderWindow& win)
{
    // Draw sun counter above cards
    win.draw(sunText);
    // Draw the plant card
    win.draw(sprite);
}

sf::Vector2f Card::getPos() { return sprite.getPosition(); }
void Card::changePos(const sf::Vector2f& other) { sprite.setPosition(getPos() + other); }
void Card::setPos(sf::Vector2f other) { sprite.setPosition(other); }

void Card::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{
    if (msg->getIndex() == Engine::MSG_TYPE::MSG_TYPE_KILL &&
        static_cast<Engine::MSG_TYPE_KILL*>(msg.get())->victim == holo.get())
    {
        holo.reset();
    }
}
