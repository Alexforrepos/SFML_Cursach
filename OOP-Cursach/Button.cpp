#include "Button.h"

// Обновление состояния кнопки: проверка наведения и нажатия мыши
void Button::Update()
{
    // Получаем позицию мыши относительно экрана и окна
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition();
    // Преобразуем в координаты окна (если используется вью или масштабирование, учтите это)
    sf::Vector2f mousePos(static_cast<float>(mousePixelPos.x), static_cast<float>(mousePixelPos.y));

    // Если курсор находится внутри прямоугольника кнопки...
    if (Intershape.getGlobalBounds().contains(mousePos))
    {
        // Переключаем кнопку в активное состояние (смена цвета)
        is_active = true;
        Intershape.setFillColor(activeColor);
        // Если нажата левая кнопка мыши, вызываем функцию-колбэк
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // Можно добавить защиту от многократного вызова, если требуется
            f();
        }
    }
    else
    {
        // Если курсор не над кнопкой – возвращаем пассивное состояние
        is_active = false;
        Intershape.setFillColor(passiveColor);
    }
}

void Button::SendMSG(MSG* msg)
{
    // В данном примере кнопка не обрабатывает сообщения.
    // Реализуйте, если нужно реагировать на внешние события.
}

void Button::Draw(sf::RenderWindow& win)
{
    // Рисуем прямоугольник и текст кнопки
    win.draw(Intershape);
    win.draw(label);
}
