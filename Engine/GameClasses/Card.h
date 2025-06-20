#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/Object.h"
#include "Engine/MSG_Manager.h"
#include "GameClasses/Hologram.h"
#include "Utils/Timer.h"
#include "Engine/R_Manager.h"
#include "ScoreManager.h"
#include "Utils/Config.h"

class Card : public Object
{
    sf::Sprite sprite;
    Timer clickTimer;
    static sf::Vector2f basePosition;
    static int cardCounter;
    std::string plantType;
    static std::shared_ptr<Hologram> holo;

    static sf::Font counterFont;
    static sf::Text  counterText;
    static bool     counterInitialized;

    static void initCounter();

public:
    Card() = default;
    Card(const std::string& plantType);

    void update() override;
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;

    static void resetCounter() { cardCounter = 0; }

    BASE_SERIALIZATION
};
