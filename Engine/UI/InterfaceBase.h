#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <string>

// Базовый виртуальный класс для всех элементов интерфейса
class InterfaceBase {
public:
    virtual ~InterfaceBase() = default;

    // Виртуальные методы, которые должны быть реализованы в производных классах
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual int handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void setPosition(const sf::Vector2f& position) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual void setActive(bool active) { m_isActive = active; }
    virtual bool isActive() const { return m_isActive; }

protected:
    bool m_isActive = false;
};

