#pragma once
#include <sstream>
#include <memory>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include "./../Engine/R_Manager.h"
#include <SFML/Graphics.hpp>

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

class I_Serialize : public std::enable_shared_from_this<I_Serialize>
{
public:
    virtual ~I_Serialize() = default;

    // Виртуальный метод для сериализации
    template <class Archive>
    void serialize(Archive& ar)
    {
        // Базовая реализация (может быть пустой)
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

// Обёртка для sf::Sprite
class SpriteWrapper :
    public sf::Sprite,
    public I_Serialize
{
private:
    std::string textureId;
    sf::Color spriteColor;

public:
    template <class Archive>
    void serialize(Archive& ar)
    {
        sf::Vector2f pos = getPosition();
        sf::Vector2f scale = getScale();
        float rotation = getRotation();
        sf::IntRect textureRect = getTextureRect();

        ar(textureId, pos, scale, rotation, textureRect, spriteColor);

        if constexpr (Archive::is_loading::value)
        {
            setPosition(pos);
            setScale(scale);
            setRotation(rotation);
            setTextureRect(textureRect);
            setColor(spriteColor);
        }
    }

    void setTextureById(const std::string& id, R_Manager& resManager) {
        textureId = id;
        const auto& texture = resManager.access<sf::Texture>(id);
        setTexture(texture, true);
    }

    const std::string& getTextureId() const { return textureId; }
};