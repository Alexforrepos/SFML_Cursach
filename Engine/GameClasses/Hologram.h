#pragma once
#include "Engine/Object.h"
#include "Engine/MSG_Manager.h"
#include "GameClasses/Plant.h"
#include <SFML/Graphics.hpp>
#include "Utils/Timer.h"
#include "Engine/R_Manager.h"
#include "Engine/O_Manager.h"



class Hologram :
    public Object
{
private:
   sf::Sprite sprite;
    std::string plantType; // Тип растения, который должен быть создан
    Timer Clicktime;
    sf::Vector2f position;
public:	
    Hologram()
        :Clicktime(100)
    {
    };

    Hologram(const sf::Vector2f& startPos, const std::string& type);
    void update() override;
    void sendMsg(Engine::MSG* msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    ~Hologram()
    {
        //std::cout << "САНЯ ЧИНИ" << std::endl;
    };
    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::base_class<Object>(this));
        ar(plantType, Clicktime, position);


        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f scale = sprite.getScale();
        float rotation = sprite.getRotation();
        sf::IntRect textureRect = sprite.getTextureRect();
        sf::Color color = sprite.getColor();
        std::string textureId = "ps.png";

        ar(position, scale, rotation, textureRect, color, textureId);
        
        if constexpr (Archive::is_loading::value)
        {
            sprite.setPosition(position);
            sprite.setScale(scale);
            sprite.setRotation(rotation);
            sprite.setTextureRect(textureRect);
            sprite.setColor(color);
            sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
        }
    };
};