#include <iostream>
#include "InterfaceBase.h"



class InterfaceWindow : public InterfaceBase {
private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;
    std::vector<std::unique_ptr<InterfaceBase>> m_elements;

public:
    InterfaceWindow(const sf::Vector2f& size, const sf::Vector2f& position)
        : m_shape(size), m_position(position) {
        m_shape.setPosition(position);
        m_shape.setFillColor(sf::Color(50, 50, 50, 200));
        m_shape.setOutlineThickness(2);
        m_shape.setOutlineColor(sf::Color::White);
    }

    ~InterfaceWindow() {
     
        clearElements();
    }

  
    void clearElements() {
       
        while (!m_elements.empty()) {
            
            m_elements.pop_back();
        }
        m_elements.clear();
    }

    void addElement(std::unique_ptr<InterfaceBase> element) {
        m_elements.push_back(std::move(element));
    }

    void centerElementsVertically(float padding = 10.0f) {
        if (m_elements.empty()) return;

        float totalHeight = 0.0f;
        for (const auto& element : m_elements) {
            totalHeight += element->getGlobalBounds().height + padding;
        }
        totalHeight -= padding; // Убираем последний отступ

        float startY = m_position.y + (m_shape.getSize().y - totalHeight) / 2.0f;

        for (auto& element : m_elements) {
            sf::Vector2f newPos = element->getPosition();
            newPos.y = startY;
            element->setPosition(newPos);
            startY += element->getGlobalBounds().height + padding;
        }
    };

    void draw(sf::RenderWindow& window) const override {
        window.draw(m_shape);
        for (const auto& element : m_elements) {
            element->draw(window);
        }
    }

    int handleEvent(const sf::Event& event) override {
        for (auto& element : m_elements) {
            if (element->handleEvent(event)) return 1;
        }
        return 0;
    }

    void centerElementsHorizontally() {
        if (m_elements.empty()) return;

        for (auto& element : m_elements) {
            float elementWidth = element->getGlobalBounds().width;
            float windowWidth = m_shape.getSize().x;
            float centerX = m_position.x + (windowWidth - elementWidth) / 2.0f;

            sf::Vector2f newPos = element->getPosition();
            newPos.x = centerX;
            element->setPosition(newPos);
        }
    }

    void update(float dt) override {
        for (auto& element : m_elements) {
            element->update(dt);
        }
    }

    void setPosition(const sf::Vector2f& position) override {
        sf::Vector2f offset = position - m_position;
        m_position = position;
        m_shape.setPosition(position);

        // Обновляем позиции всех элементов с учетом смещения
        for (auto& element : m_elements) {
            element->setPosition(element->getPosition() + offset);
        }
    }

    sf::Vector2f getPosition() const override {
        return m_position;
    }

    sf::FloatRect getGlobalBounds() const override {
        return m_shape.getGlobalBounds();
    }

  
};
