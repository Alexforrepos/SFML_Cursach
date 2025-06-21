#include "Projectile.h"
#include "GameClasses/Zombie.h"
#include "FreezeEffect.h"
#include "Engine/MSG_Manager.h"

class FreezeProjectile : public Projectile {
public:
    FreezeProjectile(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture, sf::Vector2f pos)
        : Projectile(velocity, line, damage, texture, pos)
    {
        spr.setColor(sf::Color(0, 0, 255, 200));  
    }

    void update() override {
        Projectile::update();
    }

   
};