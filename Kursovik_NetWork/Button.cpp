#include "Button.h"

// ���������� ��������� ������: �������� ��������� � ������� ����
void Button::update()
{
    // �������� ������� ���� ������������ ������ � ����
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition();
    // ����������� � ���������� ���� (���� ������������ ��� ��� ���������������, ������ ���)
    sf::Vector2f mousePos(static_cast<float>(mousePixelPos.x), static_cast<float>(mousePixelPos.y));

    // ���� ������ ��������� ������ �������������� ������...
    if (Intershape.getGlobalBounds().contains(mousePos))
    {
        // ����������� ������ � �������� ��������� (����� �����)
        is_active = true;
        Intershape.setFillColor(activeColor);
        // ���� ������ ����� ������ ����, �������� �������-������
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // ����� �������� ������ �� ������������� ������, ���� ���������
            f();
        }
    }
    else
    {
        // ���� ������ �� ��� ������� � ���������� ��������� ���������
        is_active = false;
        Intershape.setFillColor(passiveColor);
    }
}

void Button::sendMsg(MSG* msg)
{
    // � ������ ������� ������ �� ������������ ���������.
    // ����������, ���� ����� ����������� �� ������� �������.
}

void Button::draw(sf::RenderWindow& win)
{
    // ������ ������������� � ����� ������
    win.draw(Intershape);
    win.draw(label);
}

sf::Vector2f Button::getPos()
{
    return Intershape.getPosition();
}

void Button::changePos(sf::Vector2f other)
{
    setPos(getPos() + other);
}

void Button::setPos(sf::Vector2f other)
{
    Intershape.setPosition(other);
    label.setPosition(
        getPos().x + (Intershape.getSize().x - label.getLocalBounds().width) / 2.f,
        getPos().y + (Intershape.getSize().y - label.getLocalBounds().height) / 2.f - 5.f  
    );
}

int Button::type()
{
    return (int)Types::None;
}
