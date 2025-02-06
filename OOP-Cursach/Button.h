#pragma once
#include "I_Object.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public Object
{
    // ����, ������������, ������� �� ������ (������ ��� ���)
    bool is_active;

    // �������������-��������� ������
    sf::RectangleShape Intershape;
    // ����� ������
    sf::Text label;

    // �������-������, ���������� ��� �����
    std::function<void(void)> f;

    // ����� ������ � �������� � ��������� ����������
    sf::Color activeColor;
    sf::Color passiveColor;

public:
    // �����������:
    // text - ����� ��� ������ (��� ����������� �����, ������ � �.�.)
    // size - ������ ������ (������ � ������)
    // position - ������� ������ �� ������
    // callback - �������, ������� ����� ������� ��� ������� �� ������
    Button(const sf::Text& text, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void(void)> callback)
        : is_active(false), f(callback), label(text)
    {
        // ��������� ��������������-���������� ������
        Intershape.setSize(size);
        Intershape.setPosition(position);
        // ������������� ��������� ����� (�� ��� ����)
        passiveColor = sf::Color(200, 200, 200); // ������-�����
        activeColor = sf::Color(150, 150, 150); // ���� ������
        Intershape.setFillColor(passiveColor);

        // ������������� ������ ������ ��������������
        label.setPosition(
            position.x + (size.x - label.getLocalBounds().width) / 2.f,
            position.y + (size.y - label.getLocalBounds().height) / 2.f - 5.f  // ��������� ������������� �� ���������
        );
    }

    // ���������� ������� I_Object
    virtual void Update() override;
    virtual void SendMSG(MSG* msg) override;
    virtual void Draw(sf::RenderWindow& win) override;
};
