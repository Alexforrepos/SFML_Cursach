#include "Button.h"

// ���������� ��������� ������: �������� ��������� � ������� ����
void Button::Update()
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

void Button::SendMSG(MSG* msg)
{
    // � ������ ������� ������ �� ������������ ���������.
    // ����������, ���� ����� ����������� �� ������� �������.
}

void Button::Draw(sf::RenderWindow& win)
{
    // ������ ������������� � ����� ������
    win.draw(Intershape);
    win.draw(label);
}
