#pragma once
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <memory>

#define BASE_SERIALIZATION template <class Archive> void serialize(Archive& ar) {};

#pragma region SerializeUtils


namespace cereal {
    // Сериализация sf::Vector2f
    template <class Archive>
    void serialize(Archive& ar, sf::Vector2f& vec) {
        ar(vec.x, vec.y);
    }

    // Сериализация sf::IntRect
    template <class Archive>
    void serialize(Archive& ar, sf::IntRect& rect) {
        ar(rect.left, rect.top, rect.width, rect.height);
    }

    // Сериализация sf::Color
    template <class Archive>
    void serialize(Archive& ar, sf::Color& color) {
        ar(color.r, color.g, color.b, color.a);
    }

    template <class Archive>
    void serialize(Archive& ar, sf::RectangleShape& rect)
    {
        sf::Vector2f size = rect.getSize();
        sf::Vector2f pos = rect.getPosition();
        sf::Color fillColor = rect.getFillColor();
        sf::Color outlineColor = rect.getOutlineColor();
        float outlineThickness = rect.getOutlineThickness();

        ar(
            size.x, size.y,
            pos.x, pos.y,
            fillColor.r, fillColor.g, fillColor.b, fillColor.a,
            outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a,
            outlineThickness
        );

        rect.setSize(size);
        rect.setPosition(pos);
        rect.setFillColor(fillColor);
        rect.setOutlineColor(outlineColor);
        rect.setOutlineThickness(outlineThickness);
    }
}
#pragma endregion