#pragma once
#include "Engine/Object.h"
#include "Utils/Timer.h"
#include <SFML/Graphics.hpp>
#include "GameClasses/ScoreManager.h"
#include "Engine/MSG_Manager.h"
class Sun : public Object {
    sf::Sprite sprite;
    Timer lifetime{ 15000 };      // 15 сек
    Timer clickDelay{ 200 };      // антидребезг
    bool wasClicked = false;

public:
    // Конструктор по умолчанию — нужен для cereal и полиморфного создания
    Sun()
        : Object(int(Types::None))
        , sprite()
        , lifetime(15000)
        , clickDelay(200)
        , wasClicked(false)
    {
        // Текстуру и позицию установим позже в функции init()
    }

    // Основной конструктор для ручного создания
    Sun(const sf::Vector2f& pos, sf::Texture& tex)
        : Object(int(Types::None))
        , sprite(tex)
        , lifetime(15000)
        , clickDelay(200)
        , wasClicked(false)
    {
        sprite.setPosition(pos);
        sprite.setScale(0.1f, 0.1f);
        lifetime.restart();
        clickDelay.restart();
    }

    void init(const sf::Vector2f& pos, sf::Texture& tex) {
        // Вызывается сразу после Sun() для установки спрайта
        sprite.setTexture(tex);
        sprite.setPosition(pos);
        sprite.setScale(0.1f, 0.1f);
        lifetime.restart();
        clickDelay.restart();
    }

    void update() override {
        if (lifetime()) {
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_KILL>(this, this));
            return;
        }
        sf::Vector2i mp = sf::Mouse::getPosition();
        bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (sprite.getGlobalBounds().contains(sf::Vector2f(mp))
            && pressed && !wasClicked && clickDelay())
        {
            ScoreManager::get().addScore(25);
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_KILL>(this, this));
            wasClicked = true;
        }
        if (!pressed) wasClicked = false;
    }

    void draw(sf::RenderWindow& win) override {
        win.draw(sprite);
    }
    sf::Vector2f getPos() override { return sprite.getPosition(); }
    void changePos(const sf::Vector2f&) override {}
    void setPos(sf::Vector2f) override {}

    // cereal-сериализация
    template<class Archive>
    void serialize(Archive& ar) {
        ar(cereal::base_class<Object>(this),
            sprite,
            lifetime,
            clickDelay,
            wasClicked);
    }
};

