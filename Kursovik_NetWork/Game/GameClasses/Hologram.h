// Hologram.h
#pragma once
#include "./../../Engine/Object.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <utility>

class Hologram : public Object {
private:
    sf::Sprite sprite;
    std::string plantType; // Тип растения, который должен быть создан
public:
    // Конструктор принимает текстуру, начальную позицию и тип растения
    Hologram(const sf::Texture& texture, const sf::Vector2f& startPos, const std::string& type);

    virtual void update() override;
    virtual void sendMsg(MSG* msg) override;
    virtual void draw(sf::RenderWindow& win) override;
    virtual sf::Vector2f getPos() override;
    virtual void changePos(const sf::Vector2f& other) override;
    virtual void setPos(sf::Vector2f other) override;

    virtual std::vector<char> serialize() override;
    virtual std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char> data, size_t& readpoint) override;

    const std::string& getPlantType() const;
};
