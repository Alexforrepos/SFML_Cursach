#pragma once
#include "Projectile.h"

class IceP : public Projectile 
{
public:

    IceP() = default;
   
    IceP(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture, sf::Vector2f pos)
        : Projectile(velocity, line, damage, texture, pos)
    {
      
        spr.setColor(sf::Color(200, 200, 255, 200));
    }

    
    template <class Archive>
    void serialize(Archive& ar) 
    {
        ar(cereal::base_class<Projectile>(this));
    }
};


