#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <functional>

/// <summary>
/// класс конпки в меню
/// </summary>
class Button : public Object
{
    // Флаг, показывающий, активна ли кнопка (курсор над ней)
    bool is_active;

    // Прямоугольник-контейнер кнопки
    sf::RectangleShape Intershape;
    // Текст кнопки
    sf::Text label;

    // Функция-колбэк, вызываемая при клике
    std::function<void(void)> f;

    // Цвета кнопки в активном и пассивном состояниях
    sf::Color activeColor;
    sf::Color passiveColor;

public:
    // Конструктор:
    // text - текст для кнопки (уже настроенный шрифт, размер и т.д.)
    // size - размер кнопки (ширина и высота)
    // position - позиция кнопки на экране
    // callback - функция, которая будет вызвана при нажатии на кнопку
    Button(const sf::Text& text, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void(void)> callback)
        : is_active(false), f(callback), label(text),Object(int(Types::None)
    {
        // Настройка прямоугольника-контейнера кнопки
        Intershape.setSize(size);
        Intershape.setPosition(position);
        // Устанавливаем начальные цвета (на ваш вкус)
        passiveColor = sf::Color(200, 200, 200); // светло-серый
        activeColor = sf::Color(150, 150, 150); // чуть темнее
        Intershape.setFillColor(passiveColor);

        // Центрирование текста внутри прямоугольника
        label.setPosition(
            position.x + (size.x - label.getLocalBounds().width) / 2.f,
            position.y + (size.y - label.getLocalBounds().height) / 2.f - 5.f  // небольшая корректировка по вертикали
        );
    }

    // Реализация методов Object
    virtual void update() override;
    virtual void sendMsg(MSG* msg) override;
    virtual void draw(sf::RenderWindow& win) override;

    // Унаследовано через Object
    sf::Vector2f getPos() override;
    void changePos(sf::Vector2f other) override;
    void setPos(sf::Vector2f other) override;
    int type() override;
};