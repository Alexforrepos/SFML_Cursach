#pragma once
#include <sstream>
#include <memory>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include "Engine/R_Manager.h"
#include <SFML/Graphics.hpp>

#define BASE_SERIALIZATION template <class Archive> void serialize(Archive& ar) {};

#pragma region SerializeUtils

// Специализации для сериализации SFML-типов
template <class Archive>
void serialize(Archive& ar, sf::Vector2f& vec) {
    ar(vec.x, vec.y);
}

template <class Archive>
void serialize(Archive& ar, sf::IntRect& rect) {
    ar(rect.left, rect.top, rect.width, rect.height);
}

template <class Archive>
void serialize(Archive& ar, sf::Color& color) {
    ar(color.r, color.g, color.b, color.a);
}

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
}
#pragma endregion

class I_Serialize : public std::enable_shared_from_this<I_Serialize>
{
public:
    virtual ~I_Serialize() = default;

    // Виртуальный метод для сериализации
    template <class Archive>
    void serialize(Archive& ar)
    {// Базовая реализация (может быть пустой)
    };

    std::string serializeToStream() {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(cereal::make_nvp("object", shared_from_this()));
        }
        return ss.str();
    }

    void deserializeFromStream(const std::string& data) {
        std::stringstream ss(data);
        {
            cereal::BinaryInputArchive archive(ss);
            std::shared_ptr<I_Serialize> temp;
            archive(cereal::make_nvp("object", temp));
            if (temp) {
                this->serialize(archive); // или другая логика копирования
            }
        }
    }
};


