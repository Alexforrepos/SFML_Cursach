#include "Card.h"

sf::Vector2f Card::basePosition = { 50.f, 50.f };
int          Card::cardCounter = 0;
std::shared_ptr<Hologram> Card::holo = nullptr;

sf::Font Card::counterFont;
sf::Text Card::counterText;
bool     Card::counterInitialized = false;

void Card::initCounter()
{
   
    counterFont = R_Manager::get().access<sf::Font>("BantyBold.ttf");

    counterText.setFont(counterFont);
    counterText.setCharacterSize(24);
    counterText.setFillColor(sf::Color::Yellow);
    counterText.setStyle(sf::Text::Bold);

    counterInitialized = true;
}

Card::Card(const std::string& plantType)
    : Object(int(Types::Cart)),
    clickTimer(2000),
    plantType(plantType)
{
    if ((basePosition.y + cardCounter * 120.f) > 1000) {
        cardCounter = 0;
    }
    sf::Vector2f position = basePosition + sf::Vector2f(0.f, cardCounter * 120.f);
    cardCounter++;


    std::string texId = Config::getInstance()["PlantParams"]["Plants"][plantType]["textureId"];
    sf::Texture& tex = R_Manager::get().access<sf::Texture>(texId);
    sprite.setTexture(tex);

   
    sf::Vector2u tSize = tex.getSize();
    sprite.setScale(100.f / tSize.x, 100.f / tSize.y);

    sprite.setPosition(position);
    sprite.setColor({ 255,255,255,200 });
}

void Card::update()
{

    sf::Vector2i mpos = sf::Mouse::getPosition();
    if (sprite.getGlobalBounds().contains(sf::Vector2f(mpos))) {
        sprite.setColor(sf::Color::White);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && holo == nullptr) {
            int cost = Config::getInstance()["PlantParams"]["Plants"][plantType]["cost"];
            if (ScoreManager::get().spend(cost)) {
                holo = std::make_shared<Hologram>(basePosition, plantType);
                MSG_Manager::get().addMSG(
                    std::make_shared<Engine::MSG_TYPE_CREATE>(holo, this));
                clickTimer.restart();
            }
        }
    }
    else {
        sprite.setColor({ 255,255,255,200 });
    }
}

void Card::draw(sf::RenderWindow& win)
{
    if (!counterInitialized) initCounter();

    counterText.setString("Sun: " + std::to_string(ScoreManager::get().getScore()));

    float padding = 10.f;
    float y = basePosition.y + cardCounter * 120.f + padding;
    counterText.setPosition(basePosition.x, y);

    win.draw(sprite);

    win.draw(counterText);
}

sf::Vector2f Card::getPos() { return sprite.getPosition(); }
void Card::changePos(const sf::Vector2f& d) { setPos(getPos() + d); }
void Card::setPos(sf::Vector2f p) { sprite.setPosition(p); }

void Card::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{
    if (msg->getIndex() == Engine::MSG_TYPE::MSG_TYPE_KILL
        && static_cast<Engine::MSG_TYPE_KILL*>(msg.get())->victim == holo.get())
    {
        holo.reset();
    }
}
