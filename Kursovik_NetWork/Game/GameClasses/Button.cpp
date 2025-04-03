#include "Button.h"

// ���������� ��������� ������: �������� ��������� � ������� ����
void Button::update()
{
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition();
    sf::Vector2f mousePos(static_cast<float>(mousePixelPos.x), static_cast<float>(mousePixelPos.y));

    bool isHovered = Intershape.getGlobalBounds().contains(mousePos);
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isHovered)
    {
        is_active = true;
        Intershape.setFillColor(activeColor);

        // ��������� ����� ������ ���:
        // 1) ������� ������ ����
        // 2) ���������� ��������� (!wasPressed)
        // 3) �������� ������� ��������
        if (isPressed && !wasPressed && click_delay())
        {
            f();                    // ����� �������
            this->statistic_cliked++;
            click_delay.restart();  // ���������� �������
            wasPressed = true;      // ���������� ���������� �����
        }
        // ����� �����, ����� ������ ���� ��������
        else if (!isPressed)
        {
            wasPressed = false;
        }
    }
    else
    {
        is_active = false;
        Intershape.setFillColor(passiveColor);
        wasPressed = false; // ����� ��� ����� �������
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

void Button::changePos(const sf::Vector2f& other)
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

std::vector<char> Button::serialize()
{
    return std::vector<char>();
}

std::pair<Types, std::pair<void*, int>> Button::deserialize(std::vector<char> data, size_t& readpoint)
{
    return std::pair<Types, std::pair<void*, int>>();
}
