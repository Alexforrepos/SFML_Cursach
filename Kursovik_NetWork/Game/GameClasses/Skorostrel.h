#pragma once
#include "Plant.h"
#include "./../../Engine/Object.h"
#include <SFML/Graphics.hpp>
#include "./../Utils/Timer.h"

class Skorostrel :
    public Plant
{
    sf::Sprite sprite;
    Timer clickTimer;
    std::string plantType;

public:

    //не использовать!!! нужно для сериализации
    Skorostrel() = default;

    Skorostrel(const std::string& plantType, uint8_t line, uint8_t col);


    void update() override;
    void sendMsg(Engine::MSG* msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;

    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::base_class<Plant>(this));
        ar(plantType);

        // Сериализация спрайта
        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f scale = sprite.getScale();
        float rotation = sprite.getRotation();
        sf::IntRect textureRect = sprite.getTextureRect();
        sf::Color color = sprite.getColor();
        std::string textureId = "shkibidiSanya.png";

        ar(position, scale, rotation, textureRect, color, textureId);

        // Сериализация таймера
        ar(clickTimer);

        if constexpr (Archive::is_loading::value) {
            sprite.setPosition(position);
            sprite.setScale(scale);
            sprite.setRotation(rotation);
            sprite.setTextureRect(textureRect);
            sprite.setColor(color);
            sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));

            // Таймер автоматически восстановится благодаря своей сериализации
        }
    }
};
    


