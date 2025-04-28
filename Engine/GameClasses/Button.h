#pragma once
#include "Utils/Timer.h"
#include "Engine/Object.h"
#include <SFML/Graphics.hpp>
#include <functional>

/// <summary>
/// класс конпки в меню
/// </summary>
/// заменен на UI
/// 
class Button : public Object
{
    Timer click_delay;

    // Флаг, показывающий, активна ли кнопка (курсор над ней)
    bool is_active;
    bool wasPressed;
    // Прямоугольник-контейнер кнопки
    sf::RectangleShape Intershape;
    // Текст кнопки
    sf::Text label;

    // Функция-колбэк, вызываемая при клике
    std::function<void(void)> f;

    // Цвета кнопки в активном и пассивном состояниях
    sf::Color activeColor;
    sf::Color passiveColor;

    int statistic_cliked;

public:
    // Конструктор:
    // text - текст для кнопки (уже настроенный шрифт, размер и т.д.)
    // size - размер кнопки (ширина и высота)
    // position - позиция кнопки на экране
    // callback - функция, которая будет вызвана при нажатии на кнопку
    Button(const sf::Text& text, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void(void)> callback)
        : is_active(false), f(callback), label(text),Object(int(Types::None)),click_delay(200),wasPressed(false),statistic_cliked(0)
    {
       
        Intershape.setSize(size);
        Intershape.setPosition(position);
        // Устанавливаем начальные цвета (на ваш вкус)
        passiveColor = sf::Color::Transparent; // прозрачный цвет очень красивый
        activeColor = sf::Color(150, 150, 150); // чуть темнее
        Intershape.setFillColor(passiveColor);

        // Центрирование текста внутри прямоугольника
        label.setPosition(
            position.x + (size.x - label.getLocalBounds().width) / 2.f,
            position.y + (size.y - label.getLocalBounds().height) / 2.f - 5.f  // небольшая корректировка по вертикали
        );

        click_delay.restart();
    }

    ~Button()
    {
        std::cout << " was kliked: " << statistic_cliked << std::endl;
    }

    // Реализация методов Object
    virtual void update() override;
    virtual void sendMsg(Engine::MSG* msg) override;
    virtual void draw(sf::RenderWindow& win) override;

    // Унаследовано через Object
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    int type() override;

    // Унаследовано через Object
  
};