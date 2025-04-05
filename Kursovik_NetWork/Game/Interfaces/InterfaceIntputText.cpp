#include "InterfaceIntputText.h"

InterfaceInputField::InterfaceInputField(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, unsigned int charSize)
	: m_shape(size), m_text("", font, charSize), m_cursor(sf::Vector2f(2.f, charSize * 0.8f)) {
	m_shape.setPosition(position);
	m_shape.setFillColor(sf::Color::White);
	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(sf::Color(100, 100, 100));

	m_text.setPosition(position.x + 5.f, position.y + (size.y - charSize) / 2.f);
	m_text.setFillColor(sf::Color::Black);

	m_cursor.setFillColor(sf::Color::Black);
	m_cursor.setPosition(position.x + 5.f, position.y + (size.y - charSize * 0.8f) / 2.f);

	m_maxLength = static_cast<size_t>(size.x / (charSize * 0.6f));
}


