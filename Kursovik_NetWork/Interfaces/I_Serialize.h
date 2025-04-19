#pragma once
#include <sstream>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <SFML/Graphics.hpp>
#include "./../Engine/R_Manager.h"

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
#pragma endregion

// Базовый интерфейс для сериализации (CRTP)
template <typename Derived>
class I_Serialize {
public:
    virtual ~I_Serialize() = default;

    template <class Archive>
    void serialize(Archive& ar) {
        static_cast<Derived*>(this)->serializeImpl(ar);
    }

    std::string serializeToStream() {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            serialize(archive);
        }
        return ss.str();
    }

    void deserializeFromStream(const std::string& data) {
        std::stringstream ss(data);
        {
            cereal::BinaryInputArchive archive(ss);
            serialize(archive);
        }
    }
};

// Обёртка для sf::Sprite
class SpriteWrapper :
    public sf::Sprite,
    public I_Serialize<SpriteWrapper> 
{
private:
    std::string textureId;

public:
    // Реализация сериализации
    template <class Archive>
    void serializeImpl(Archive& ar) {
        ar(
            textureId,
            getPosition(),
            getScale(),
            getRotation(),
            getTextureRect()
        );
    }

    // Установка текстуры через R_Manager
    void setTextureById(const std::string& id, R_Manager& resManager) {
        textureId = id;
        setTexture(resManager.access<sf::Texture>(id));
    }

    const std::string& getTextureId() const { return textureId; }
};

// Регистрация типа для полиморфной сериализации
CEREAL_REGISTER_TYPE(SpriteWrapper);