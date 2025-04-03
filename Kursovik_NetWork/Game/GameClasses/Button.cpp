#include "Button.h"

// Обновление состояния кнопки: проверка наведения и нажатия мыши
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

        // Обработка клика только при:
        // 1) Нажатии кнопки мыши
        // 2) Отсутствии удержания (!wasPressed)
        // 3) Истекшем времени задержки
        if (isPressed && !wasPressed && click_delay())
        {
            f();                    // Вызов колбэка
            this->statistic_cliked++;
            click_delay.restart();  // Перезапуск таймера
            wasPressed = true;      // Блокировка повторного клика
        }
        // Сброс флага, когда кнопка мыши отпущена
        else if (!isPressed)
        {
            wasPressed = false;
        }
    }
    else
    {
        is_active = false;
        Intershape.setFillColor(passiveColor);
        wasPressed = false; // Сброс при уходе курсора
    }
}

void Button::sendMsg(MSG* msg)
{
	// В данном примере кнопка не обрабатывает сообщения.
	// Реализуйте, если нужно реагировать на внешние события.
}

void Button::draw(sf::RenderWindow& win)
{
	// Рисуем прямоугольник и текст кнопки
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
