#pragma once
#include "Utils/Timer.h"
#include "Engine/Object.h"
#include <SFML/Graphics.hpp>
#include <functional>

/// <summary>
/// ����� ������ � ����
/// </summary>
/// ������� �� UI
/// 
class Button : public Object
{
    Timer click_delay;

    // ����, ������������, ������� �� ������ (������ ��� ���)
    bool is_active;
    bool wasPressed;
    // �������������-��������� ������
    sf::RectangleShape Intershape;
    // ����� ������
    sf::Text label;

    // �������-������, ���������� ��� �����
    std::function<void(void)> f;

    // ����� ������ � �������� � ��������� ����������
    sf::Color activeColor;
    sf::Color passiveColor;

    int statistic_cliked;

public:
    // �����������:
    // text - ����� ��� ������ (��� ����������� �����, ������ � �.�.)
    // size - ������ ������ (������ � ������)
    // position - ������� ������ �� ������
    // callback - �������, ������� ����� ������� ��� ������� �� ������
    Button(const sf::Text& text, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void(void)> callback)
        : is_active(false), f(callback), label(text),Object(int(Types::None)),click_delay(200),wasPressed(false),statistic_cliked(0)
    {
       
        Intershape.setSize(size);
        Intershape.setPosition(position);
        // ������������� ��������� ����� (�� ��� ����)
        passiveColor = sf::Color::Transparent; // ���������� ���� ����� ��������
        activeColor = sf::Color(150, 150, 150); // ���� ������
        Intershape.setFillColor(passiveColor);

        // ������������� ������ ������ ��������������
        label.setPosition(
            position.x + (size.x - label.getLocalBounds().width) / 2.f,
            position.y + (size.y - label.getLocalBounds().height) / 2.f - 5.f  // ��������� ������������� �� ���������
        );

        click_delay.restart();
    }

    ~Button()
    {
        std::cout << " was kliked: " << statistic_cliked << std::endl;
    }

    // ���������� ������� Object
    virtual void update() override;
    virtual void sendMsg(Engine::MSG* msg) override;
    virtual void draw(sf::RenderWindow& win) override;

    // ������������ ����� Object
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    int type() override;

    // ������������ ����� Object
  
};