#include "Button_.h"


 void Button::centerText() {
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    sf::Vector2f pos = m_shape.getPosition();
    sf::Vector2f size = m_shape.getSize();
    m_text.setPosition(pos.x + size.x / 2.0f,
        pos.y + size.y / 2.0f);
}
