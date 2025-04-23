#pragma once
#include "./../../Interfaces/I_Serialize.h"


class SpriteWrapper : public sf::Sprite, public I_Serialize
{
private:
    std::string textureId;
    sf::Color spriteColor;

public:
    template <class Archive>
    void serialize(Archive& ar) {
        sf::Vector2f pos = getPosition();
        sf::Vector2f scale = getScale();
        float rotation = getRotation();
        sf::IntRect textureRect = getTextureRect();
        sf::Color currentColor = getColor();

        ar(textureId, pos, scale, rotation, textureRect, currentColor);

        if constexpr (Archive::is_loading::value) {
            setPosition(pos);
            setScale(scale);
            setRotation(rotation);
            setTextureRect(textureRect);
            setColor(currentColor);
            // Текстура будет загружена позже через setTextureById()
        }
    }

    void setTextureById(const std::string& id, R_Manager& resManager) {
        textureId = id;
        const auto& texture = resManager.access<sf::Texture>(id);
        setTexture(texture, true);
    }

    SpriteWrapper(const sf::Sprite& spr) : sf::Sprite(spr) {}
    SpriteWrapper() = default;
    const std::string& getTextureId() const { return textureId; }
};