#pragma once
#include "InterfaceBase.h"

class Button 
    : public InterfaceBase 
{
public:
    using Callback = std::function<void()>;

    Button(const sf::Vector2f& size, const sf::Vector2f& position,
        const std::string& text, const sf::Font& font, unsigned int charSize = 20)
        : m_shape(size), m_text(text, font, charSize) 
    {
        m_shape.setPosition(position);
        m_shape.setFillColor(sf::Color(70, 70, 70));
        m_shape.setOutlineThickness(2);
        m_shape.setOutlineColor(sf::Color::White);

        centerText();
    }

    void setCallback(Callback callback) {
        m_callback = callback;
    }

    void draw(sf::RenderWindow& window) const override {
        window.draw(m_shape);
        window.draw(m_text);
    }

    int handleEvent(const sf::Event& event) override
    {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            if (m_shape.getGlobalBounds().contains(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y))) 
            {
                if (m_callback) {
                    m_callback();
                    return 1;
                }
            }
        }
        return 0;
    }

    void update(float dt) override
    {
       
    }

    void setPosition(const sf::Vector2f& position) override {
        sf::Vector2f size = m_shape.getSize();
        m_shape.setPosition(position);
        centerText();
    }

    sf::Vector2f getPosition() const override {
        return m_shape.getPosition();
    }

    sf::FloatRect getGlobalBounds() const override {
        return m_shape.getGlobalBounds();
    }

    void setText(const std::string& text) {
        m_text.setString(text);
        centerText();
    }

    void setCharacterSize(unsigned int size) {
        m_text.setCharacterSize(size);
        centerText();
    }

private:
    void centerText();

    sf::RectangleShape m_shape;
    sf::Text m_text;
    Callback m_callback;
};