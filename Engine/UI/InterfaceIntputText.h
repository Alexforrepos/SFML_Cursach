#pragma once
#include "InterfaceBase.h"

//  ласс пол€ ввода текста
class InterfaceInputField : public InterfaceBase
{
public:
	using Validator = std::function<bool(const std::string&)>;
private:
	sf::RectangleShape m_shape;
	sf::Text m_text;
	sf::RectangleShape m_cursor;
	sf::Clock m_cursorClock;
	bool m_showCursor = false;
	size_t m_maxLength;
	Validator m_validator;
public:

	InterfaceInputField(const sf::Vector2f& size, const sf::Vector2f& position,
		const sf::Font& font, unsigned int charSize = 20);

	void draw(sf::RenderWindow& window) const override {
		window.draw(m_shape);
		window.draw(m_text);

		// –исуем курсор только если поле активно и мигание в нужной фазе
		if (m_isActive && m_showCursor) {
			window.draw(m_cursor);
		}
	}

	int handleEvent(const sf::Event& event) override
	{
		if (event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left)
		{
			bool wasActive = m_isActive;
			m_isActive = m_shape.getGlobalBounds().contains(
				static_cast<float>(event.mouseButton.x),
				static_cast<float>(event.mouseButton.y));

			if (m_isActive && !wasActive) {
				m_cursorClock.restart();
				m_showCursor = true;
				updateCursorPosition();
				return 1;
			}
			return 0;
		}
		else if (m_isActive)
		{
			if (event.type == sf::Event::TextEntered)
			{
				// »гнорируем управл€ющие символы (кроме backspace)
				if (event.text.unicode == '\b') {
					return 0; // Backspace обрабатываетс€ в KeyPressed
				}
				else if (event.text.unicode < 32) {
					return 0;
				}

				if (m_text.getString().getSize() < m_maxLength) {
					std::string newText = m_text.getString() + static_cast<char>(event.text.unicode);
					if (!m_validator || m_validator(newText)) {
						m_text.setString(newText);
						updateCursorPosition();
					}
				}
				return 1;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace) {
					std::string current = m_text.getString();
					if (!current.empty()) {
						current.pop_back();
						m_text.setString(current);
						updateCursorPosition();
					}
					return 1;
				}
			}
		}
		return 0;
	}

	void update(float dt) override {
		if (m_isActive) {
			// ћигание курсора
			if (m_cursorClock.getElapsedTime().asSeconds() > 0.5f) {
				m_showCursor = !m_showCursor;
				m_cursorClock.restart();
			}
		}
	}

	void setPosition(const sf::Vector2f& position) override {
		sf::Vector2f offset = position - m_shape.getPosition();
		m_shape.setPosition(position);
		m_text.move(offset);
		m_cursor.move(offset);
	}

	sf::Vector2f getPosition() const override {
		return m_shape.getPosition();
	}

	sf::FloatRect getGlobalBounds() const override {
		return m_shape.getGlobalBounds();
	}

	std::string getText() const {
		return m_text.getString();
	}

	void setText(const std::string& text) {
		m_text.setString(text);
		updateCursorPosition();
	}

	void setValidator(Validator validator) {
		m_validator = validator;
	}

	bool isValid() const {
		if (m_validator) {
			return m_validator(m_text.getString());
		}
		return true;
	}

	void setActive(bool active) override {
		InterfaceBase::setActive(active);
		if (active) {
			m_cursorClock.restart();
			m_showCursor = true;
			m_shape.setOutlineColor(sf::Color::Blue);
		}
		else {
			m_showCursor = false;
			m_shape.setOutlineColor(m_isActive ? sf::Color(100, 100, 100) : sf::Color::Red);
		}
	}

private:
	void handleTextInput(const sf::Event::TextEvent& textEvent) {
		// »гнорируем управл€ющие символы (кроме backspace)
		if (textEvent.unicode == '\b') {
			return; // Backspace обрабатываетс€ в handleKeyPress
		}
		else if (textEvent.unicode < 32) {
			return;
		}

		if (m_text.getString().getSize() < m_maxLength) {
			std::string newText = m_text.getString() + static_cast<char>(textEvent.unicode);
			if (!m_validator || m_validator(newText)) {
				m_text.setString(newText);
				updateCursorPosition();
			}
		}
	}

	void handleKeyPress(const sf::Event::KeyEvent& keyEvent) {
		if (keyEvent.code == sf::Keyboard::BackSpace) {
			std::string current = m_text.getString();
			if (!current.empty()) {
				current.pop_back();
				m_text.setString(current);
				updateCursorPosition();
			}
		}
	}

	void updateCursorPosition() {
		float textWidth = m_text.getLocalBounds().width;
		m_cursor.setPosition(m_text.getPosition().x + textWidth + 2.f, m_cursor.getPosition().y);
		m_cursorClock.restart();
		m_showCursor = true;
	}


};